#ifndef UNIVERSE1_VIDEO_ITEM3DHAND_H
#define UNIVERSE1_VIDEO_ITEM3DHAND_H

#include "../path/item3dpath.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D hand item */
struct Item3DHand : public Item3DBase
{
    static const Material defMat;    //!< Default material
    static const float defSize;      //!< Default hand size
    static const float defLine;      //!< Default line radius
    const bool rightHand;            //!< Is right hand flag
    DynamicVec3 center;              //!< Main circle center point
    DynamicVec3 normal;              //!< Main circle normal direction
    DynamicVec3 arm;                 //!< Main circle arm direction
    DynamicValue<float> distance;    //!< Distance from center
    DynamicValue<float> handSize;    //!< Hand size
    DynamicValue<float> lineRadius;  //!< Line radius
    DynamicValue<uint> qualityHand;  //!< Main circle quality
    DynamicValue<uint> qualityLine;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _rightHand Initial is right hand flag
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name
     */
    Item3DHand(const bool _rightHand,
               const QVector3D &_center,
               const QVector3D &_normal,
               const QVector3D &_arm,
               const float _distance,
               const float _handSize,
               const float _lineRadius,
               const uint _qualityHand,
               const uint _qualityLine,
               const bool _visible,
               const Material &_material,
               const std::string &_name);

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _rightHand Is right hand flag
     * \param _center Main circle center point
     * \param _normal Main circle normal direction
     * \param _arm Main circle arm direction
     * \param _distance Distance from center
     * \param _handSize Hand size
     * \param _lineRadius Line radius
     * \param _qualityHand Main circle quality
     * \param _qualityLine Line circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const bool _rightHand,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _distance,
                          const float _handSize,
                          const float _lineRadius,
                          const uint _qualityHand,
                          const uint _qualityLine,
                          const Material &_material);

    /*!
     * \brief Add spinning movement
     * \param _timeStepStart Begin time-step
     * \param _timeStepEnd End time-step
     * \param _spinDur Spin duration
     * \param _spinBackDur Spin back move duration
     * \param _getClosserDur Get closer with hand duration
     * \param _rotAngleDeg Rotation angle in degrees
     * \param _distanceMult Distance multiplier
     */
    inline void addSpins(const uint64_t _timeStepStart,
                         const uint64_t _timeStepEnd,
                         const uint64_t _spinDur = 1000UL,
                         const uint64_t _spinBackDur = 1000UL,
                         const uint64_t _getClosserDur = 1000UL,
                         const float _rotAngleDeg = 60.0f,
                         const float _distanceMult = 0.4f)
    {
        const float d0 = distance.values.front().second;
        const QVector3D n0 = normal.values.front().second;
        const QVector3D a0 = arm.values.front().second;
        const uint64_t dur = _spinDur + _spinBackDur;
        uint64_t t = _timeStepStart + _getClosserDur;
        distance.add(_timeStepStart, d0);
        distance.add(t, d0 * _distanceMult);
        arm.add(t, a0);
        while (t + dur <= _timeStepEnd)
        {
            t += _spinDur;
            arm.addArcAccel(t, QVector3D(), n0, _rotAngleDeg);
            t += _spinBackDur;
            arm.addArcAccel(t, QVector3D(), n0, -_rotAngleDeg);
        }
    }
};

/*! \brief Footage 3D hand database */
struct DBItem3DHand : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DHand(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D hand item
     * \param _rightHand Initial is right hand flag
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DHand *add(const bool _rightHand,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const float _distance,
                    const float _handSize,
                    const float _lineRadius,
                    const uint _qualityHand,
                    const uint _qualityLine,
                    const bool _visible,
                    const Material &_material);

    /*!
     * \brief Add visible 3D hand item
     * \param _rightHand Initial is right hand flag
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *add(const bool _rightHand,
                           const QVector3D &_center,
                           const QVector3D &_normal,
                           const QVector3D &_arm,
                           const float _distance,
                           const float _handSize,
                           const float _lineRadius,
                           const uint _qualityHand,
                           const uint _qualityLine,
                           const Material &_material)
    {
        return add(_rightHand,
                   _center,
                   _normal,
                   _arm,
                   _distance,
                   _handSize,
                   _lineRadius,
                   _qualityHand,
                   _qualityLine,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D left hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *addLeft(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _distance,
                               const float _handSize,
                               const float _lineRadius,
                               const uint _qualityHand,
                               const uint _qualityLine,
                               const Material &_material)
    {
        return add(
            false, _center, _normal, _arm, _distance, _handSize, _lineRadius, _qualityHand, _qualityLine, _material);
    }

    /*!
     * \brief Add visible 3D left hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \return Created item
     */
    inline Item3DHand *
    addLeft(const QVector3D &_center, const QVector3D &_normal, const QVector3D &_arm, const float _distance)
    {
        return addLeft(_center,
                       _normal,
                       _arm,
                       _distance,
                       Item3DHand::defSize,
                       Item3DHand::defLine,
                       Config::cfg().qualitySphere,
                       Config::cfg().qualityLine,
                       Item3DHand::defMat);
    }

    /*!
     * \brief Add visible 3D right hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *addRight(const QVector3D &_center,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const float _distance,
                                const float _handSize,
                                const float _lineRadius,
                                const uint _qualityHand,
                                const uint _qualityLine,
                                const Material &_material)
    {
        return add(
            true, _center, _normal, _arm, _distance, _handSize, _lineRadius, _qualityHand, _qualityLine, _material);
    }

    /*!
     * \brief Add visible 3D right hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \return Created item
     */
    inline Item3DHand *
    addRight(const QVector3D &_center, const QVector3D &_normal, const QVector3D &_arm, const float _distance)
    {
        return addRight(_center,
                        _normal,
                        _arm,
                        _distance,
                        Item3DHand::defSize,
                        Item3DHand::defLine,
                        Config::cfg().qualitySphere,
                        Config::cfg().qualityLine,
                        Item3DHand::defMat);
    }

    //

    /*!
     * \brief Add hidden 3D hand item
     * \param _rightHand Initial is right hand flag
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *addHidden(const bool _rightHand,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const QVector3D &_arm,
                                 const float _distance,
                                 const float _handSize,
                                 const float _lineRadius,
                                 const uint _qualityHand,
                                 const uint _qualityLine,
                                 const Material &_material)
    {
        return add(_rightHand,
                   _center,
                   _normal,
                   _arm,
                   _distance,
                   _handSize,
                   _lineRadius,
                   _qualityHand,
                   _qualityLine,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D left hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *addHiddenLeft(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const QVector3D &_arm,
                                     const float _distance,
                                     const float _handSize,
                                     const float _lineRadius,
                                     const uint _qualityHand,
                                     const uint _qualityLine,
                                     const Material &_material)
    {
        return addHidden(
            false, _center, _normal, _arm, _distance, _handSize, _lineRadius, _qualityHand, _qualityLine, _material);
    }

    /*!
     * \brief Add hidden 3D left hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \return Created item
     */
    inline Item3DHand *
    addHiddenLeft(const QVector3D &_center, const QVector3D &_normal, const QVector3D &_arm, const float _distance)
    {
        return addHiddenLeft(_center,
                             _normal,
                             _arm,
                             _distance,
                             Item3DHand::defSize,
                             Item3DHand::defLine,
                             Config::cfg().qualitySphere,
                             Config::cfg().qualityLine,
                             Item3DHand::defMat);
    }

    /*!
     * \brief Add hidden 3D right hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \param _handSize Initial hand size
     * \param _lineRadius Initial line radius
     * \param _qualityHand Initial main circle quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DHand *addHiddenRight(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _distance,
                                      const float _handSize,
                                      const float _lineRadius,
                                      const uint _qualityHand,
                                      const uint _qualityLine,
                                      const Material &_material)
    {
        return addHidden(
            true, _center, _normal, _arm, _distance, _handSize, _lineRadius, _qualityHand, _qualityLine, _material);
    }

    /*!
     * \brief Add hidden 3D right hand item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal direction
     * \param _arm Initial main circle arm direction
     * \param _distance Initial distance from center
     * \return Created item
     */
    inline Item3DHand *
    addHiddenRight(const QVector3D &_center, const QVector3D &_normal, const QVector3D &_arm, const float _distance)
    {
        return addHiddenRight(_center,
                              _normal,
                              _arm,
                              _distance,
                              Item3DHand::defSize,
                              Item3DHand::defLine,
                              Config::cfg().qualitySphere,
                              Config::cfg().qualityLine,
                              Item3DHand::defMat);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DHAND_H
