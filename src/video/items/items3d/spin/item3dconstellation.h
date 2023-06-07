#ifndef UNIVERSE1_VIDEO_ITEM3DCONSTELLATION_H
#define UNIVERSE1_VIDEO_ITEM3DCONSTELLATION_H

#include "item3dspin.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Particle constellation item */
struct Item3DConstellation : public Item3D
{
    // clang-format off
    static const uint16_t _SPIN          = 0b0000000000000001; //!< Main spin visible
    static const uint16_t _SPIN_VECTOR   = 0b0000000000000010; //!< Show spin vector
    static const uint16_t _SPIN_AXIS     = 0b0000000000000100; //!< Show spin axis
    static const uint16_t _SPIN_ARROWS   = 0b0000000000001000; //!< Show spin arrows
    static const uint16_t _SPIN_DOTS     = 0b0000000000010000; //!< Show spin dots
    static const uint16_t _SPIN_SPHERE   = 0b0000000000100000; //!< Show spin sphere
    static const uint16_t _SPIN_TEXT     = 0b0000000001000000; //!< Show spin text
    static const uint16_t _VELOCITY      = 0b0000000010000000; //!< Show velocity 
    static const uint16_t _VELOCITY_TEXT = 0b0000000100000000; //!< Show velocity text
    static const uint16_t _CENTER_POINT  = 0b0000001000000000; //!< Show center point
    static const uint16_t _CENTER_TEXT   = 0b0000010000000000; //!< Show center point text
    static const uint16_t _CENTER_DOTS   = 0b0000100000000000; //!< Show center point position (text)
    static const uint16_t _SPHERE_OUT    = 0b0001000000000000; //!< Show outer transparent sphere
    static const uint16_t _SPHERE_IN     = 0b0010000000000000; //!< Show inner transparent sphere
    static const uint16_t _ANGLES        = 0b0100000000000000; //!< Show angles
    static const uint16_t _ANGLES_TEXT   = 0b1000000000000000; //!< Show angle labels
    // clang-format on

    static const Material matV1;   //!< Default material for generation 1 velocity
    static const Material matV2;   //!< Default material for generation 2 velocity
    static const Material matV3;   //!< Default material for generation 3 velocity
    static const Material matOI;   //!< Default material for color red spin
    static const Material matOJ;   //!< Default material for color green spin
    static const Material matOK;   //!< Default material for color blue spin
    static const Material matOM;   //!< Default material for massive spin
    static const Material matOT;   //!< Default material for temperature spin
    static const Material matOG1;  //!< Default material for generation 1 curving path spin
    static const Material matOG2;  //!< Default material for generation 2 curving path spin
    static const Material matOG3;  //!< Default material for generation 3 curving path spin
    static const Material matHR;   //!< Default material for right-handed helicity
    static const Material matH0;   //!< Default material for zero helicity
    static const Material matHL;   //!< Default material for left-handed helicity

    static const Material matAngles;     //!< Default material for angle dimensions
    static const Material matCenter;     //!< Default material for central point
    static const Material matSphereIn;   //!< Default material inner sphere (transparent sphere)
    static const Material matSphereOut;  //!< Default material outer sphere (transparent sphere)

    static const std::array<QString, 4U> spTxt;  //!< Major spin names
    static const float offsetAxis1;              //!< Offset for axis line (far points)
    static const float offsetAxis2;              //!< Offset for axis line (from vector end)

    DynamicBool showSpin;          //!< Main spin visible
    DynamicBool showSpinVector;    //!< Show spin vector
    DynamicBool showSpinAxis;      //!< Show spin axis
    DynamicBool showSpinArrows;    //!< Show spin arrows
    DynamicBool showSpinDots;      //!< Show spin dots
    DynamicBool showSpinSphere;    //!< Show spin sphere
    DynamicBool showSpinText;      //!< Show spin text
    DynamicBool showVelocity;      //!< Show velocity arrow
    DynamicBool showVelocityText;  //!< Show velocity text
    DynamicBool showCenter;        //!< Show center point
    DynamicBool showCenterText;    //!< Show center point text
    DynamicBool showCenterDots;    //!< Show center point height dots (from zero XY plane)
    DynamicBool showSphereOuter;   //!< Show outer transparent sphere
    DynamicBool showSphereInner;   //!< Show inner transparent sphere
    DynamicBool showAngles;        //!< Show angles
    DynamicBool showAngleText;     //!< Show angle labels

    DynamicEnum<Math::ConstellationType> type;  //!< Constellation type

    DynamicVec3 center;  //!< Center point
    DynamicVec3 normal;  //!< Main normal
    DynamicVec3 arm;     //!< Arm direction

    DynamicValue<float> phaseDeg;  //!< Main rotation phase for spin
    DynamicValue<float> R1;        //!< Main sphere radius

    DynamicValue<float> velocityRadiusLine;          //!< Velocity radius line
    DynamicValue<float> velocityArrowLength;         //!< Velocity arrow length
    DynamicValue<float> velocityArrowRadius;         //!< Velocity arrow header radius
    DynamicEnum<TextPosition> velocityTextPosition;  //!< Velocity text position
    DynamicValue<float> velocityTextSize;            //!< Velocity text size multiplier
    DynamicAlign velocityTextAlign;                  //!< Velocity text align property

    DynamicValue<float> centerRadius;      //!< Center cross radius
    DynamicValue<float> centerRadiusLine;  //!< Center cross radius line
    DynamicValue<uint> centerDotsMult;     //!< Center dot line space multiplier
    DynamicTextGroup centerText;           //!< Center text group

    DynamicValue<uint> qualityLatLong;  //!< Quality for wire-frame sphere latitude-longitude steps
    DynamicValue<uint> qualitySphere;   //!< Quality for sphere circle
    DynamicValue<uint> qualityLine;     //!< Quality for line circle

    DynamicMaterialGroup materialVelocity;   //!< Material velocity sphere
    DynamicMaterialGroup materialCenter;     //!< Material center point
    DynamicMaterialGroup materialSphereIn;   //!< Material outer sphere
    DynamicMaterialGroup materialSphereOut;  //!< Material inner sphere

    DynamicSpinGroup spinI;  //!< Spin I group
    DynamicSpinGroup spinJ;  //!< Spin J group
    DynamicSpinGroup spinK;  //!< Spin K group
    DynamicSpinGroup spinM;  //!< Spin M group

    DynamicAngleGroup angleIJ;  //!< Angle I->J group
    DynamicAngleGroup angleJK;  //!< Angle J->K group
    DynamicAngleGroup angleKI;  //!< Angle K->I group
    DynamicAngleGroup angleIM;  //!< Angle I->M group
    DynamicAngleGroup angleJM;  //!< Angle J->M group
    DynamicAngleGroup angleKM;  //!< Angle K->M group

    /*!
     * \brief Constructor
     * \param _showFlags Initial show flags as bit buffer
     * \param _type Initial constellation type
     * \param _center Initial center point
     * \param _normal Initial Main normal
     * \param _arm Initial arm direction
     * \param _text Initial center text
     * \param _visible Initial visible flag
     * \param _name Item name
     */
    Item3DConstellation(const uint16_t _showFlags,
                        const Math::ConstellationType _type,
                        const QVector3D &_center,
                        const QVector3D &_normal,
                        const QVector3D &_arm,
                        const QString &_text,
                        const bool _visible,
                        const std::string &_name);

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;

 protected:
    /*!
     * \brief Create 3D data for center point
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _quality Line quality
     */
    void addData3DCenter(std::list<Data3D> &_out,
                         const Shader *_shader,
                         const uint64_t _timeStep,
                         const QVector3D &_center,
                         const QVector3D &_normal,
                         const QVector3D &_arm,
                         const uint _quality) const;

    /*!
     * \brief Create 3D data for velocity arrow
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Normal
     * \param _r1 Particle radius
     * \param _quality Line quality
     */
    void addData3DVelocity(std::list<Data3D> &_out,
                           const Shader *_shader,
                           const uint64_t _timeStep,
                           const QVector3D &_center,
                           const QVector3D &_normal,
                           const float _r1,
                           const uint _quality) const;

    /*!
     * \brief Create 3D data for velocity arrow
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _r1 Particle radius
     * \param _quality Line quality
     */
    void addData3DSpheres(std::list<Data3D> &_out,
                          const uint64_t _timeStep,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _r1,
                          const uint _quality) const;

    /*!
     * \brief Create 3D data for single spin
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _normal Spin normal direction
     * \param _phase Spin phase (arm) direction
     * \param _isData Show spin sub-flags
     * \param _group Spin property group
     * \param _spinName Spin name
     * \param _helicity Major spin helicity
     */
    void addData3DSpin(std::list<Data3D> &_out,
                       const Shader *_shader,
                       const uint64_t _timeStep,
                       const QVector3D &_center,
                       const float _r1,
                       const uint _qll,
                       const uint _qs,
                       const uint _ql,
                       const QVector3D &_normal,
                       const QVector3D &_phase,
                       const std::array<bool, 6U> &_isData,
                       const DynamicSpinGroup &_group,
                       const QString &_spinName,
                       const Math::Helicity _helicity = Math::_HelicityZero) const;

    /*!
     * \brief Create 3D data for all 4 spins
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _constellation Constellation spin normal
     * \param _isData Show sub-flags
     * \param _helicity Major helicity of all spins
     */
    inline void addData3DSpinAll(std::list<Data3D> &_out,
                                 const Shader *_shader,
                                 const uint64_t _timeStep,
                                 const QVector3D &_center,
                                 const float _r1,
                                 const uint _qll,
                                 const uint _qs,
                                 const uint _ql,
                                 const Math::Constellation<float> &_constellation,
                                 const std::array<std::array<bool, 6U>, 4U> &_isData,
                                 const std::array<Math::Helicity, 4U> &_helicity) const
    {
        for (uint8_t i = 0U; i < 4U; ++i)
            addData3DSpin(_out,
                          _shader,
                          _timeStep,
                          _center,
                          _r1,
                          _qll,
                          _qs,
                          _ql,
                          _constellation.qSpin(i),
                          _constellation.qPhase(i),
                          _isData[i],
                          *spin(i),
                          spTxt[i],
                          _helicity[i]);
    }

    /*!
     * \brief Create 3D data for spin twist vector
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _phase Spin phase (arm) direction
     * \param _r1 Particle radius
     * \param _length Spin size
     * \param _ql Quality for line circle
     * \param _group Spin properties group
     * \param _material1 Material
     * \param _material2 Material second
     */
    inline void addData3DSpinVector(std::list<Data3D> &_out,
                                    const uint64_t _timeStep,
                                    const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const QVector3D &_phase,
                                    const float _r1,
                                    const float _length,
                                    const uint _ql,
                                    const DynamicSpinGroup &_group,
                                    const Material &_material1,
                                    const Material &_material2) const
    {
        const float tw = _group.twistStep.getValue(_timeStep) * _r1;
        const float lr = _group.radiusVector.getValue(_timeStep);
        Item3DLineTwist::buildData(
            _out, _center, _normal, _phase, _length * _r1, tw, lr, _ql, {_material1, _material2});
    }

    /*!
     * \brief Create 3D data for axis
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _ql Quality for line circle
     * \param _group Spin properties group
     * \param _material Material
     */
    inline void addData3DSpinAxis(std::list<Data3D> &_out,
                                  const uint64_t _timeStep,
                                  const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const float _r1,
                                  const uint _ql,
                                  const DynamicSpinGroup &_group,
                                  const Material &_material) const
    {
        const QVector3D pb = _center + _normal * (_r1 * (1.0 + offsetAxis1));
        const QVector3D pe = _center - _normal * (_r1 * (1.0 + offsetAxis1));
        const float lra = _group.radiusLineAxis.getValue(_timeStep);
        const uint mult = _group.multAxis.getValue(_timeStep);
        Item3DLineDashSegment::buildData(_out, pb, pe, lra, mult, mult, 2U, _ql, _material);
    }

    /*!
     * \brief Create 3D data for 2 mixing axis
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _ql Quality for line circle
     * \param _group1 Spin 1 properties group
     * \param _group2 Spin 2 properties group
     * \param _material1 Spin 1 material
     * \param _material2 Spin 2 material
     */
    inline void addData3DSpinAxisMix(std::list<Data3D> &_out,
                                     const uint64_t _timeStep,
                                     const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _r1,
                                     const uint _ql,
                                     const DynamicSpinGroup &_group1,
                                     const DynamicSpinGroup &_group2,
                                     const Material &_material1,
                                     const Material &_material2) const
    {
        const QVector3D pb = _center + _normal * (_r1 * (1.0 + offsetAxis1));
        const QVector3D pe = _center - _normal * (_r1 * (1.0 + offsetAxis1));
        const float lra =
            std::max(_group1.radiusLineAxis.getValue(_timeStep), _group2.radiusLineAxis.getValue(_timeStep));
        const uint mult = std::max(_group1.multAxis.getValue(_timeStep), _group2.multAxis.getValue(_timeStep));
        Item3DLineDashSegment::buildMultiColor(_out, pb, pe, lra, mult, mult, 2U, _ql, {_material1, _material2});
    }

    /*!
     * \brief Create 3D data for axis cutted
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _length Spin size
     * \param _ql Quality for line circle
     * \param _group Spin properties group
     * \param _material Material
     */
    inline void addData3DSpinAxisCut(std::list<Data3D> &_out,
                                     const uint64_t _timeStep,
                                     const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _r1,
                                     const float _length,
                                     const uint _ql,
                                     const DynamicSpinGroup &_group,
                                     const Material &_material) const
    {
        const QVector3D pb1 = _center + _normal * (_r1 * (_length + offsetAxis2));
        const QVector3D pe1 = _center + _normal * (_r1 * (1.0 + offsetAxis1));
        const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
        const QVector3D pe2 = _center - _normal * (_r1 * (1.0 + offsetAxis1));
        const float lra = _group.radiusLineAxis.getValue(_timeStep);
        const uint mult = _group.multAxis.getValue(_timeStep);
        const Material m1d = _material.darker();
        Item3DLineDashSegment::buildData(_out, pb1, pe1, lra, mult, mult, 2U, _ql, m1d);
        Item3DLineDashSegment::buildData(_out, pb2, pe2, lra, mult, mult, 2U, _ql, m1d);
    }

    /*!
     * \brief Create 3D data for spin axis within photon merging spins
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _ql Quality for line circle
     * \param _is1 Show sub-flags merging spin 1
     * \param _is2 Show sub-flags merging spin 2
     * \param _group1 Merging spin 1 properties group
     * \param _group2 Merging spin 2 properties group
     * \param _material1 Merging spin 1 material
     * \param _material2 Merging spin 2 material
     */
    inline void addData3DSpinAxisCutPhoton(std::list<Data3D> &_out,
                                           const uint64_t _timeStep,
                                           const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _r1,
                                           const uint _ql,
                                           const std::array<bool, 6U> &_is1,
                                           const std::array<bool, 6U> &_is2,
                                           const DynamicSpinGroup &_group1,
                                           const DynamicSpinGroup &_group2,
                                           const Material &_material1,
                                           const Material &_material2) const
    {
        if (_is1[1] && _is2[1])  // axis
        {
            const QVector3D pb1 = _center + _normal * (_r1 * (1.0f + offsetAxis2));
            const QVector3D pe1 = _center + _normal * (_r1 * (1.0f + offsetAxis1));
            const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - _normal * (_r1 * (1.0f + offsetAxis1));
            const float lra =
                std::max(_group1.radiusLineAxis.getValue(_timeStep), _group2.radiusLineAxis.getValue(_timeStep));
            const uint mult = std::max(_group1.multAxis.getValue(_timeStep), _group2.multAxis.getValue(_timeStep));
            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mult, mult, 2U, _ql, {_material1, _material2});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mult, mult, 2U, _ql, {_material1, _material2});
        }
        else if (_is1[1])
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, _normal, _r1, 1.0f, _ql, _group1, _material1);
        }
        else if (_is2[1])
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, _normal, _r1, 1.0f, _ql, _group2, _material2);
        }
    }

    /*!
     * \brief Create 3D data for spin arrows within photon merging spins
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _phase1 Spin 1 phase
     * \param _phase2 Spin 2 phase
     * \param _r1 Particle radius
     * \param _ql Quality for line circle
     * \param _is1 Show sub-flags merging spin 1
     * \param _is2 Show sub-flags merging spin 2
     * \param _group1 Merging spin 1 properties group
     * \param _group2 Merging spin 2 properties group
     * \param _material1 Merging spin 1 material
     * \param _material2 Merging spin 2 material
     * \param _material3 Helicity material
     */
    inline void addData3DSpinArrowsPhoton(std::list<Data3D> &_out,
                                          const uint64_t _timeStep,
                                          const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const QVector3D &_phase1,
                                          const QVector3D &_phase2,
                                          const float _r1,
                                          const uint _ql,
                                          const std::array<bool, 6U> &_is1,
                                          const std::array<bool, 6U> &_is2,
                                          const DynamicSpinGroup &_group1,
                                          const DynamicSpinGroup &_group2,
                                          const Material &_material1,
                                          const Material &_material2,
                                          const Material &_material3) const
    {
        if (_is1[2] && _is2[2])  // arrows
        {
            const float ad1 = _group1.arrowDirOffset.getValue(_timeStep);
            const float ad2 = _group2.arrowDirOffset.getValue(_timeStep);
            if (qFuzzyCompare(ad1, ad2))
            {
                const QVector3D cc = _center + _normal * (_r1 * (1.0f + ad1));
                const float ao1 = _group1.arrowArmOffset.getValue(_timeStep);
                const float al1 = _group1.arrowLength.getValue(_timeStep);
                const float ar1 = _group1.arrowRadius.getValue(_timeStep);
                const float ao2 = _group2.arrowArmOffset.getValue(_timeStep);
                const float al2 = _group2.arrowLength.getValue(_timeStep);
                const float ar2 = _group2.arrowRadius.getValue(_timeStep);
                const float ao3 = (ao1 + ao2) * 0.5f;
                const float al3 = (al1 + al2) * 0.5f;
                const float ar3 = (ar1 + ar2) * 0.5f;
                const QVector3D _p1r1 = QQuaternion::fromAxisAndAngle(_normal, 120).rotatedVector(_phase1).normalized();
                const QVector3D _p1r2 = QQuaternion::fromAxisAndAngle(_normal, 240).rotatedVector(_phase1).normalized();
                Item3DArcArrow::buildData(
                    _out, cc, _normal, _phase1, ao1, al1, ar1, _ql, _material1, _material1.darker());
                Item3DArcArrow::buildData(
                    _out, cc, _normal, _p1r1, ao2, al2, ar2, _ql, _material2, _material2.darker());
                Item3DArcArrow::buildData(
                    _out, cc, _normal, _p1r2, ao3, al3, ar3, _ql, _material3, _material3.darker());
            }
            else
            {
                addData3DSpinArrows(
                    _out, _timeStep, _center, _normal, _phase1, _r1, 1.0, _ql, _group1, _material1, _material3);
                addData3DSpinArrows(
                    _out, _timeStep, _center, _normal, _phase2, _r1, 1.0, _ql, _group2, _material2, _material3);
            }
        }
        else if (_is1[2])  // arrows
        {
            addData3DSpinArrows(
                _out, _timeStep, _center, _normal, _phase1, _r1, 1.0, _ql, _group1, _material1, _material3);
        }
        else if (_is2[2])  // arrows
        {
            addData3DSpinArrows(
                _out, _timeStep, _center, _normal, _phase2, _r1, 1.0, _ql, _group2, _material2, _material3);
        }
    }

    /*!
     * \brief Create 3D data for spin text within photon merging spins
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _is1 Show sub-flags merging spin 1
     * \param _is2 Show sub-flags merging spin 2
     * \param _group1 Merging spin 1 properties group
     * \param _group2 Merging spin 2 properties group
     * \param _material1 Merging spin 1 material
     * \param _material2 Merging spin 2 material
     * \param _material3 Helicity material
     * \param _name1 Spin 1 name
     * \param _name2 Spin 2 name
     */
    inline void addData3DSpinTextPhoton(std::list<Data3D> &_out,
                                        const Shader *_shader,
                                        const uint64_t _timeStep,
                                        const QVector3D &_center,
                                        const QVector3D &_normal,
                                        const float _r1,
                                        const std::array<bool, 6U> &_is1,
                                        const std::array<bool, 6U> &_is2,
                                        const DynamicSpinGroup &_group1,
                                        const DynamicSpinGroup &_group2,
                                        const Material &_material1,
                                        const Material &_material2,
                                        const Material &_material3,
                                        const QString &_name1,
                                        const QString &_name2) const
    {
        if (_is1[5] && _is2[5])  // text
        {
            const TextPosition tp1 = _group1.textPosition.getValue(_timeStep);
            const TextPosition tp2 = _group2.textPosition.getValue(_timeStep);
            if (tp1 != tp2)
            {
                addData3DSpinText(_out, _shader, _timeStep, _center, _normal, _name1, _r1, 1.0, _group1, _material1);
                addData3DSpinText(_out, _shader, _timeStep, _center, _normal, _name2, _r1, 1.0, _group2, _material2);
            }
            else
            {
                const float ts = std::max(_group1.textSize.getValue(_timeStep), _group2.textSize.getValue(_timeStep));
                const Qt::Alignment ta = _group1.textAlign.getValue(_timeStep);
                const QString sn = _name1 + "<br/>" + _name2;
                switch (tp1)
                {
                case _TextAtPointFrom:
                    Item3DText::buildData(_out, _shader, sn, ts, ta, _center + _normal * 0.1f, _material3);
                    break;
                case _TextMiddle:
                    Item3DText::buildData(_out, _shader, sn, ts, ta, _center + _normal * (_r1 * 0.5f), _material3);
                    break;
                case _TextAtPointTo:
                    Item3DText::buildData(_out, _shader, sn, ts, ta, _center + _normal * (_r1 * (0.9f)), _material3);
                    break;
                }
            }
        }
        else if (_is1[5])  // text
        {
            addData3DSpinText(_out, _shader, _timeStep, _center, _normal, _name1, _r1, 1.0, _group1, _material1);
        }
        else if (_is2[5])  // text
        {
            addData3DSpinText(_out, _shader, _timeStep, _center, _normal, _name2, _r1, 1.0, _group2, _material2);
        }
    }

    /*!
     * \brief Create 3D data for spin axis within photon merging spins
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _r1 Particle radius
     * \param _ql Quality for line circle
     * \param _is1 Show sub-flags merging spin I
     * \param _is2 Show sub-flags merging spin J
     * \param _is3 Show sub-flags merging spin K
     * \param _material1 Merging spin I material
     * \param _material2 Merging spin J material
     * \param _material3 Merging spin K material
     */
    inline void addData3DSpinAxisCutGraviton(std::list<Data3D> &_out,
                                             const uint64_t _timeStep,
                                             const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const float _r1,
                                             const uint _ql,
                                             const std::array<bool, 6U> &_is1,
                                             const std::array<bool, 6U> &_is2,
                                             const std::array<bool, 6U> &_is3,
                                             const Material &_material1,
                                             const Material &_material2,
                                             const Material &_material3) const
    {
        if (_is1[1] && _is2[1] && _is3[1])
        {
            const QVector3D pb1 = _center + _normal * (_r1 * (1.0f + offsetAxis2));
            const QVector3D pe1 = _center + _normal * (_r1 * (1.0f + offsetAxis1));
            const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - _normal * (_r1 * (1.0f + offsetAxis1));
            const float lra = (spinI.radiusLineAxis.getValue(_timeStep) + spinJ.radiusLineAxis.getValue(_timeStep) +
                               spinK.radiusLineAxis.getValue(_timeStep)) /
                3.0f;
            const uint mult = (spinI.multAxis.getValue(_timeStep) + spinJ.multAxis.getValue(_timeStep) +
                               spinK.multAxis.getValue(_timeStep)) /
                3U;
            Item3DLineDashSegment::buildMultiColor(
                _out, pb1, pe1, lra, mult, mult, 2U, _ql, {_material1, _material2, _material3});
            Item3DLineDashSegment::buildMultiColor(
                _out, pb2, pe2, lra, mult, mult, 2U, _ql, {_material1, _material2, _material3});
        }
        else if (_is1[1] && _is2[1])
        {
            const QVector3D pb1 = _center + _normal * (_r1 * (1.0f + offsetAxis2));
            const QVector3D pe1 = _center + _normal * (_r1 * (1.0f + offsetAxis1));
            const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - _normal * (_r1 * (1.0f + offsetAxis1));
            const float lra =
                std::max(spinI.radiusLineAxis.getValue(_timeStep), spinJ.radiusLineAxis.getValue(_timeStep));
            const uint mult = std::max(spinI.multAxis.getValue(_timeStep), spinJ.multAxis.getValue(_timeStep));
            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mult, mult, 2U, _ql, {_material1, _material2});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mult, mult, 2U, _ql, {_material1, _material2});
        }
        else if (_is1[1] && _is3[1])
        {
            const QVector3D pb1 = _center + _normal * (_r1 * (1.0f + offsetAxis2));
            const QVector3D pe1 = _center + _normal * (_r1 * (1.0f + offsetAxis1));
            const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - _normal * (_r1 * (1.0f + offsetAxis1));
            const float lra =
                std::max(spinI.radiusLineAxis.getValue(_timeStep), spinK.radiusLineAxis.getValue(_timeStep));
            const uint mult = std::max(spinI.multAxis.getValue(_timeStep), spinK.multAxis.getValue(_timeStep));
            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mult, mult, 2U, _ql, {_material3, _material1});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mult, mult, 2U, _ql, {_material3, _material1});
        }
        else if (_is2[1] && _is3[1])
        {
            const QVector3D pb1 = _center + _normal * (_r1 * (1.0f + offsetAxis2));
            const QVector3D pe1 = _center + _normal * (_r1 * (1.0f + offsetAxis1));
            const QVector3D pb2 = _center - _normal * (_r1 * offsetAxis2);
            const QVector3D pe2 = _center - _normal * (_r1 * (1.0f + offsetAxis1));
            const float lra =
                std::max(spinJ.radiusLineAxis.getValue(_timeStep), spinK.radiusLineAxis.getValue(_timeStep));
            const uint mult = std::max(spinJ.multAxis.getValue(_timeStep), spinK.multAxis.getValue(_timeStep));
            Item3DLineDashSegment::buildMultiColor(_out, pb1, pe1, lra, mult, mult, 2U, _ql, {_material2, _material3});
            Item3DLineDashSegment::buildMultiColor(_out, pb2, pe2, lra, mult, mult, 2U, _ql, {_material2, _material3});
        }
        else if (_is1[1])
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, _normal, _r1, 1.0f, _ql, spinI, _material1);
        }
        else if (_is2[1])
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, _normal, _r1, 1.0f, _ql, spinJ, _material2);
        }
        else if (_is3[1])
        {
            addData3DSpinAxisCut(_out, _timeStep, _center, _normal, _r1, 1.0f, _ql, spinK, _material2);
        }
    }

    /*!
     * \brief Create 3D data for spin vector arrows
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _phase Spin phase (arm) direction
     * \param _r1 Particle radius
     * \param _length Spin size
     * \param _ql Quality for line circle
     * \param _group Spin properties group
     * \param _material Material
     * \param _materialCircle Material back circle
     */
    inline void addData3DSpinArrows(std::list<Data3D> &_out,
                                    const uint64_t _timeStep,
                                    const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const QVector3D &_phase,
                                    const float _r1,
                                    const float _length,
                                    const uint _ql,
                                    const DynamicSpinGroup &_group,
                                    const Material &_material,
                                    const Material &_materialCircle) const
    {
        const QVector3D cc = _center + _normal * (_r1 * (_length + _group.arrowDirOffset.getValue(_timeStep)));
        const float ao = _group.arrowArmOffset.getValue(_timeStep) * _length;
        const float al = _group.arrowLength.getValue(_timeStep) * _length;
        const float ar = _group.arrowRadius.getValue(_timeStep) * _length;
        Item3DArcArrows::buildData(_out, 3U, cc, _normal, _phase, ao, al, ar, _ql, _material, _materialCircle);
    }

    /*!
     * \brief Create 3D data for spin vector text
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _spinName Spin name
     * \param _r1 Particle radius
     * \param _length Spin size
     * \param _group Spin properties group
     * \param _material Material
     */
    inline void addData3DSpinText(std::list<Data3D> &_out,
                                  const Shader *_shader,
                                  const uint64_t _timeStep,
                                  const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const QString &_spinName,
                                  const float _r1,
                                  const float _length,
                                  const DynamicSpinGroup &_group,
                                  const Material &_material) const
    {
        const float ts = _group.textSize.getValue(_timeStep);
        const Qt::Alignment ta = _group.textAlign.getValue(_timeStep);
        switch (_group.textPosition.getValue(_timeStep))
        {
        case _TextAtPointFrom:
            Item3DText::buildData(_out, _shader, _spinName, ts, ta, _center + _normal * (_length * 0.1f), _material);
            break;
        case _TextMiddle:
            Item3DText::buildData(
                _out, _shader, _spinName, ts, ta, _center + _normal * (_r1 * _length * 0.5f), _material);
            break;
        case _TextAtPointTo:
            Item3DText::buildData(
                _out, _shader, _spinName, ts, ta, _center + _normal * (_r1 * (_length - 0.1f)), _material);
            break;
        }
    }

    /*!
     * \brief Create 3D data for spin equator dots
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _phase Spin phase (arm) direction
     * \param _r1 Particle radius
     * \param _qs Quality for sphere circle
     * \param _groups Spin properties groups
     * \param _materials Materials
     */
    inline void addData3DSpinDots(std::list<Data3D> &_out,
                                  const uint64_t _timeStep,
                                  const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const QVector3D &_phase,
                                  const float _r1,
                                  const uint _qs,
                                  const std::vector<const DynamicSpinGroup *> &_groups,
                                  const std::vector<Material> &_materials) const
    {
        std::vector<uint> cnts(_groups.size());
        for (size_t i = 0U; i < _groups.size(); ++i)
            cnts[i] = _groups.at(i)->dotsCount.getValue(_timeStep);

        const uint cnt = std::accumulate(cnts.cbegin(), cnts.cend(), 0U);
        if (cnt == 0U)
            return;

        const QQuaternion rot = QQuaternion::fromAxisAndAngle(_normal, 360.0f / static_cast<float>(cnt));

        std::vector<float> rds(_groups.size());
        for (size_t i = 0U; i < _groups.size(); ++i)
            rds[i] = _groups.at(i)->radiusDots.getValue(_timeStep);

        QVector3D aa = _phase;
        uint end = 0U;

        uint ii = 0U;
        for (size_t i = 0U; i < _groups.size(); ++i)
        {
            end += cnts[i];
            for (; ii < end; ++ii, aa = rot.rotatedVector(aa).normalized())
                Item3DSphere::buildData(_out, _center + aa * _r1, rds[i], _qs, _materials[i]);
        }
    }

    /*!
     * \brief Create 3D data for spin wire-sphere
     * \param _out Output 3D data list
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _normal Spin normal
     * \param _phase Spin phase (arm) direction
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _group Spin properties group
     * \param _material Material
     */
    inline void addData3DSpinSphere(std::list<Data3D> &_out,
                                    const uint64_t _timeStep,
                                    const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const QVector3D &_phase,
                                    const float _r1,
                                    const uint _qll,
                                    const uint _qs,
                                    const uint _ql,
                                    const DynamicSpinGroup &_group,
                                    const Material &_material) const
    {
        const float lr = _group.radiusLineSphere.getValue(_timeStep);
        Item3DWireSphere::buildData(_out, _center, _normal, _phase, _r1, lr, _qll, _qs, _ql, _material);
    }

    /*!
     * \brief Create 3D data for down quark opposite spins
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _constellation Constellation spin normal
     * \param _isData Show sub-flags
     * \param _spinIdx1 First spin index
     * \param _spinIdx2 Second spin index
     * \param _helicity1 First spin helicity
     * \param _helicity2 Second spin helicity
     */
    void addData3DQuark(std::list<Data3D> &_out,
                        const Shader *_shader,
                        const uint64_t _timeStep,
                        const QVector3D &_center,
                        const float _r1,
                        const uint _qll,
                        const uint _qs,
                        const uint _ql,
                        const Math::Constellation<float> &_constellation,
                        const std::array<std::array<bool, 6U>, 4U> &_isData,
                        const uint _spinIdx1,
                        const uint _spinIdx2,
                        const Math::Helicity _helicity1,
                        const Math::Helicity _helicity2) const;

    /*!
     * \brief Create 3D data for photon merging spins
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _constellation Constellation spin normal
     * \param _isData Show sub-flags
     * \param _spinIdx1 First merging spin index
     * \param _spinIdx2 Second merging spin index
     */
    void addData3DPhoton(std::list<Data3D> &_out,
                         const Shader *_shader,
                         const uint64_t _timeStep,
                         const QVector3D &_center,
                         const float _r1,
                         const uint _qll,
                         const uint _qs,
                         const uint _ql,
                         const Math::Constellation<float> &_constellation,
                         const std::array<std::array<bool, 6U>, 4U> &_isData,
                         const uint _spinIdx1,
                         const uint _spinIdx2) const;

    /*!
     * \brief Create 3D data for graviton merging spins
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _r1 Particle radius
     * \param _qll Quality for wire-frame sphere latitude-longitude steps
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _constellation Constellation spin normal
     * \param _isData Show sub-flags
     */
    void addData3DGraviton(std::list<Data3D> &_out,
                           const Shader *_shader,
                           const uint64_t _timeStep,
                           const QVector3D &_center,
                           const float _r1,
                           const uint _qll,
                           const uint _qs,
                           const uint _ql,
                           const Math::Constellation<float> &_constellation,
                           const std::array<std::array<bool, 6U>, 4U> &_isData) const;

    /*!
     * \brief Create 3D data for angle dimension
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _angleText Angle text
     * \param _center Center point
     * \param _normal Main angle normal
     * \param _normal1 First direction
     * \param _normal2 Second direction
     * \param _group Angle properties group
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _canShowText Major can show angle text flag
     */
    inline void addData3DAngle(std::list<Data3D> &_out,
                               const Shader *_shader,
                               const uint64_t _timeStep,
                               const QString &_angleText,
                               const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_normal1,
                               const QVector3D &_normal2,
                               const DynamicAngleGroup &_group,
                               const uint _qs,
                               const uint _ql,
                               const bool _canShowText) const
    {
        if (_group.show.getValue(_timeStep))
            Item3DAngleDim::buildData(_out,
                                      _shader,
                                      _center,
                                      _normal,
                                      _normal1,
                                      _normal2,
                                      _group.angleOffset.getValue(_timeStep),
                                      _group.radiusLine.getValue(_timeStep),
                                      _group.arrowLength.getValue(_timeStep),
                                      _group.arrowRadius.getValue(_timeStep),
                                      true,
                                      true,
                                      _canShowText && _group.showText.getValue(_timeStep),
                                      _angleText,
                                      _group.textPosition.getValue(_timeStep),
                                      _group.textSize.getValue(_timeStep),
                                      _group.textAlign.getValue(_timeStep),
                                      _qs,
                                      _ql,
                                      _group.material.getValue(_timeStep));
    }

    /*!
     * \brief Create 3D data for angle dimension
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _angleText Angle text
     * \param _center Center point
     * \param _normal1 First direction
     * \param _normal2 Second direction
     * \param _group Angle properties group
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _canShowText Major can show angle text flag
     */
    inline void addData3DAngle(std::list<Data3D> &_out,
                               const Shader *_shader,
                               const uint64_t _timeStep,
                               const QString &_angleText,
                               const QVector3D &_center,
                               const QVector3D &_normal1,
                               const QVector3D &_normal2,
                               const DynamicAngleGroup &_group,
                               const uint _qs,
                               const uint _ql,
                               const bool _canShowText) const
    {
        addData3DAngle(_out,
                       _shader,
                       _timeStep,
                       _angleText,
                       _center,
                       QVector3D::crossProduct(_normal1, _normal2).normalized(),
                       _normal1,
                       _normal2,
                       _group,
                       _qs,
                       _ql,
                       _canShowText);
    }

    /*!
     * \brief Create 3D data for angle dimensions (I-J-K)
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _constellation Constellation spin normal
     * \param _isData Show spin-flags
     * \param _canShowText Major can show angle text flag
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _angleIJText Angle I-J text
     * \param _angleJKText Angle J-K text
     * \param _angleKIText Angle K-I text
     */
    inline void addData3DAnglesIJK(std::list<Data3D> &_out,
                                   const Shader *_shader,
                                   const uint64_t _timeStep,
                                   const QVector3D &_center,
                                   const Math::Constellation<float> &_constellation,
                                   const std::array<std::array<bool, 6U>, 4U> &_isData,
                                   const bool _canShowText,
                                   const uint _qs,
                                   const uint _ql,
                                   const QString &_angleIJText,
                                   const QString &_angleJKText,
                                   const QString &_angleKIText) const
    {
        if ((_isData[0][0] || _isData[0][1]) && (_isData[1][0] || _isData[1][1]))
            addData3DAngle(_out,
                           _shader,
                           _timeStep,
                           _angleIJText,
                           _center,
                           _constellation.qI(),
                           _constellation.qJ(),
                           angleIJ,
                           _qs,
                           _ql,
                           _canShowText);
        if ((_isData[1][0] || _isData[1][1]) && (_isData[2][0] || _isData[2][1]))
            addData3DAngle(_out,
                           _shader,
                           _timeStep,
                           _angleJKText,
                           _center,
                           _constellation.qJ(),
                           _constellation.qK(),
                           angleJK,
                           _qs,
                           _ql,
                           _canShowText);
        if ((_isData[2][0] || _isData[2][1]) && (_isData[0][0] || _isData[0][1]))
            addData3DAngle(_out,
                           _shader,
                           _timeStep,
                           _angleKIText,
                           _center,
                           _constellation.qK(),
                           _constellation.qI(),
                           angleKI,
                           _qs,
                           _ql,
                           _canShowText);
    }

    /*!
     * \brief Create 3D data for all angle dimensions
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \param _center Center point
     * \param _constellation Constellation spin normal
     * \param _isData Show spin-flags
     * \param _canShowText Major can show angle text flag
     * \param _qs Quality for sphere circle
     * \param _ql Quality for line circle
     * \param _angleIJText Angle I-J text
     * \param _angleJKText Angle J-K text
     * \param _angleKIText Angle K-I text
     * \param _angleIMText Angle I-M text
     * \param _angleJMText Angle J-M text
     * \param _angleKMText Angle K-M text
     */
    inline void addData3DAngles(std::list<Data3D> &_out,
                                const Shader *_shader,
                                const uint64_t _timeStep,
                                const QVector3D &_center,
                                const Math::Constellation<float> &_constellation,
                                const std::array<std::array<bool, 6U>, 4U> &_isData,
                                const bool _canShowText,
                                const uint _qs,
                                const uint _ql,
                                const QString &_angleIJText,
                                const QString &_angleJKText,
                                const QString &_angleKIText,
                                const QString &_angleIMText,
                                const QString &_angleJMText,
                                const QString &_angleKMText) const
    {
        addData3DAnglesIJK(_out,
                           _shader,
                           _timeStep,
                           _center,
                           _constellation,
                           _isData,
                           _canShowText,
                           _qs,
                           _ql,
                           _angleIJText,
                           _angleJKText,
                           _angleKIText);

        if (_isData[3][0] || _isData[3][1])
        {
            if ((_isData[0][0] || _isData[0][1]))
                addData3DAngle(_out,
                               _shader,
                               _timeStep,
                               _angleIMText,
                               _center,
                               _constellation.qI(),
                               _constellation.qM(),
                               angleIM,
                               _qs,
                               _ql,
                               _canShowText);
            if ((_isData[1][0] || _isData[1][1]))
                addData3DAngle(_out,
                               _shader,
                               _timeStep,
                               _angleJMText,
                               _center,
                               _constellation.qJ(),
                               _constellation.qM(),
                               angleJM,
                               _qs,
                               _ql,
                               _canShowText);
            if ((_isData[2][0] || _isData[2][1]))
                addData3DAngle(_out,
                               _shader,
                               _timeStep,
                               _angleKMText,
                               _center,
                               _constellation.qK(),
                               _constellation.qM(),
                               angleKM,
                               _qs,
                               _ql,
                               _canShowText);
        }
    }

 public:
    /*!
     * \brief Getter for spin by index
     * \param _idx Spin index
     * \return Spin at index
     */
    inline DynamicSpinGroup *spin(const uint8_t _idx)
    {
        switch (_idx)
        {
        case 0U: return &spinI;
        case 1U: return &spinJ;
        case 2U: return &spinK;
        default: break;
        }
        return &spinM;
    }

    /*!
     * \brief Getter for spin by index
     * \param _idx Spin index
     * \return Spin at index
     */
    inline const DynamicSpinGroup *spin(const uint8_t _idx) const
    {
        switch (_idx)
        {
        case 0U: return &spinI;
        case 1U: return &spinJ;
        case 2U: return &spinK;
        default: break;
        }
        return &spinM;
    }

    /*!
     * \brief Getter for angle by index
     * \param _idx Angle index
     * \return Angle at index
     */
    inline DynamicAngleGroup *angle(const uint8_t _idx)
    {
        switch (_idx)
        {
        case 0U: return &angleIJ;
        case 1U: return &angleJK;
        case 2U: return &angleKI;
        case 3U: return &angleIM;
        case 4U: return &angleJM;
        case 5U: return &angleKM;
        default: break;
        }
        return &angleIJ;
    }

    /*!
     * \brief Getter for angle by index
     * \param _idx Angle index
     * \return Angle at index
     */
    inline const DynamicAngleGroup *angle(const uint8_t _idx) const
    {
        switch (_idx)
        {
        case 0U: return &angleIJ;
        case 1U: return &angleJK;
        case 2U: return &angleKI;
        case 3U: return &angleIM;
        case 4U: return &angleJM;
        case 5U: return &angleKM;
        default: break;
        }
        return &angleIJ;
    }

    /*!
     * \brief Add spin circles grow in loops
     * \param _timeStepStart Start time in ms
     * \param _timeStepEnd End time in ms
     * \param _durationGrowRadius Duration grow/switch
     * \param _durationSingle Duration stay single color
     */
    inline void addLoopSpinCircles(const uint64_t _timeStepStart,
                                   const uint64_t _timeStepEnd,
                                   const uint64_t _durationGrowRadius = 1000UL,
                                   const uint64_t _durationSingle = 1000UL)
    {
        const uint64_t timeStepStart = Config::cfg().fixedTime(_timeStepStart);
        const uint64_t timeStepEnd = Config::cfg().fixedTime(_timeStepEnd);

        if (timeStepStart != _timeStepStart && Config::cfg().verbose)
            std::cout << "Info[" + name + "]: addLoopSpinCircles(): Using aligned start time " << timeStepStart
                      << "ms !" << std::endl;

        if (timeStepEnd != _timeStepEnd && Config::cfg().verbose)
            std::cout << "Info[" + name + "]: addLoopSpinCircles(): Using aligned end time " << timeStepEnd << "ms !"
                      << std::endl;

        if (timeStepStart >= timeStepEnd)
        {
            std::cerr << "Error[" + name + "]: addLoopSpinCircles(" + std::to_string(timeStepStart) + ", " +
                    std::to_string(timeStepEnd) + "): Ignored, invalid Start/End time !"
                      << std::endl;
            return;
        }

        const float lr = Config::cfg().lineRadius;
        const float lrL = lr * 0.1;
        const float lrH = lr * 2.0;
        const uint64_t fd = Config::cfg().frameDuration;
        const uint64_t t1 = _durationGrowRadius + _durationSingle;
        const uint64_t t2 = _durationGrowRadius + t1;

        uint64_t tt = timeStepStart;
        uint8_t spinIdx = 0U;
        bool firstLoop = true;

        if (!showSpinSphere.values.empty() && !showSpinSphere.values.back().second)
            showSpinSphere.addOn(tt);

        spinJ.showSphere.addOff(tt);
        spinK.showSphere.addOff(tt);

        while (true)
        {
            if (tt + t1 >= timeStepEnd)
                break;

            DynamicSpinGroup *sp = spin(spinIdx);

            if (firstLoop)
                firstLoop = false;
            else
                sp->showSphere.addOn(tt);
            sp->radiusLineSphere.add(tt, lrL);
            sp->radiusLineSphere.add(tt + _durationGrowRadius, lrH);
            sp->radiusLineSphere.addSame(tt + t1);
            sp->radiusLineSphere.add(tt + t2 - fd, lrL);
            sp->radiusLineSphere.add(tt + t2, lr);
            sp->showSphere.addOff(tt + t2);

            tt += t1;

            spinIdx++;
            if (spinIdx == 3U)
                spinIdx = 0U;
        }

        showSpinSphere.addOff(tt + _durationGrowRadius);
    }

    /*!
     * \brief Getter for material by helicity type
     * \param _helicity Helicity type
     * \return Material by helicity type
     */
    inline static const Material &getHelicityMaterial(const Math::Helicity _helicity)
    {
        switch (_helicity)
        {
        case Math::_HelicityLeft: return matHR;
        case Math::_HelicityZero: return matH0;
        case Math::_HelicityRight: return matHL;
        }
        return matH0;
    }

    /*!
     * \brief Getter for material by helicity type
     * \param _spinIdx Spin index
     * \return Material by spin
     */
    inline static const Material &getSpinMaterial(const uint8_t _spinIdx)
    {
        switch (_spinIdx)
        {
        case 0U: return matOI;
        case 1U: return matOJ;
        case 2U: return matOK;
        default: break;
        }
        return matOM;
    }
};

/*! \brief Footage 3D constellation database */
struct DBItem3DConstellation : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DConstellation(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D constellation item
     * \param _showFlags Initial show flags as bit buffer
     * \param _type Initial constellation type
     * \param _center Initial center point
     * \param _normal Initial Main normal
     * \param _arm Initial arm direction
     * \param _visible Initial visible flag
     * \param _text Initial text
     * \return Created item
     */
    Item3DConstellation *add(const uint16_t _showFlags,
                             const Math::ConstellationType _type,
                             const QVector3D &_center,
                             const QVector3D &_normal,
                             const QVector3D &_arm,
                             const bool _visible,
                             const QString &_text = "");

    /*!
     * \brief Add visible 3D constellation item
     * \param _showFlags Initial show flags as bit buffer
     * \param _type Initial constellation type
     * \param _center Initial center point
     * \param _normal Initial Main normal
     * \param _arm Initial arm direction
     * \param _text Initial text
     * \return Created item
     */
    Item3DConstellation *add(const uint16_t _showFlags,
                             const Math::ConstellationType _type,
                             const QVector3D &_center,
                             const QVector3D &_normal,
                             const QVector3D &_arm,
                             const QString &_text = "")
    {
        return add(_showFlags, _type, _center, _normal, _arm, true, _text);
    }

    /*!
     * \brief Add hidden 3D constellation item
     * \param _showFlags Initial show flags as bit buffer
     * \param _type Initial constellation type
     * \param _center Initial center point
     * \param _normal Initial Main normal
     * \param _arm Initial arm direction
     * \param _text Initial text
     * \return Created item
     */
    Item3DConstellation *addHidden(const uint16_t _showFlags,
                                   const Math::ConstellationType _type,
                                   const QVector3D &_center,
                                   const QVector3D &_normal,
                                   const QVector3D &_arm,
                                   const QString &_text = "")
    {
        return add(_showFlags, _type, _center, _normal, _arm, false, _text);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DCONSTELLATION_H
