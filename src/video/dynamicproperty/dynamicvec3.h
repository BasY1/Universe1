#ifndef UNIVERSE1_VIDEO_DYNAMICVEC3_H
#define UNIVERSE1_VIDEO_DYNAMICVEC3_H

#include "dynamicbool.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic 3D vector property
 */
struct DynamicVec3 : public DynamicProperty
{
    std::list<std::pair<uint64_t, QVector3D>> values;  //!< Values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _name Property name
     */
    DynamicVec3(const QVector3D &_value, const std::string &_name);

    /*!
     * \brief Initialize 3D vector property
     * \param _duration Footage duration
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Returns 3D vector value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    QVector3D getValue(const uint64_t _timeStep) const;

    /*!
     * \brief Returns value at specific time-step as string
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    QString getValueText(const uint64_t _timeStep) const;

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _value Value to set
     * \return This object
     */
    inline DynamicVec3 &operator=(const QVector3D &_value)
    {
        if (!values.empty())
            values.back().second = _value;
        return *this;
    }

    /*!
     * \brief Add same value as last stored at time-step
     * \param _timeStep Time-step
     * \return Value at time-step
     */
    QVector3D addSame(const uint64_t _timeStep);

    /*!
     * \brief Add new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void add(const uint64_t _timeStep, const QVector3D &_value);

    /*!
     * \brief Add same value as last stored at start time-step and new value at end time-step
     * \param _timeStepStart Jump start time
     * \param _timeStepEnd Jump end time
     * \param _value New value
     */
    void addJump(const uint64_t _timeStepStart, const uint64_t _timeStepEnd, const QVector3D &_value);

    /*!
     * \brief Add accelerated movement
     * \param _timeStepStart Movement start time
     * \param _timeStepEnd Movement end time
     * \param _value Final value
     * \param _acceleration Acceleration duration according to total movement time
     * \param _deceleration Deceleration duration according to total movement time
     */
    void addAccel(const uint64_t _timeStepStart,
                  const uint64_t _timeStepEnd,
                  const QVector3D &_value,
                  const float _acceleration = 0.1f,
                  const float _deceleration = 0.1f);

    /*!
     * \brief Add accelerated movement
     * \param _timeStepEnd Movement end time
     * \param _value Final value
     * \param _acceleration Acceleration duration according to total movement time
     * \param _deceleration Deceleration duration according to total movement time
     */
    void addAccel(const uint64_t _timeStepEnd,
                  const QVector3D &_value,
                  const float _acceleration = 0.1f,
                  const float _deceleration = 0.1f);

    /*!
     * \brief Add movement over circle
     * \param _timeStepStart Movement start time
     * \param _timeStepEnd Movement end time
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _angleDeg Arc angle in degrees
     */
    void addArc(const uint64_t _timeStepStart,
                const uint64_t _timeStepEnd,
                const QVector3D &_rotationCenter,
                const QVector3D &_rotationNormal,
                const float _angleDeg);

    /*!
     * \brief Add movement over circle
     * \param _timeStepEnd Movement end time
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _angleDeg Arc angle in degrees
     */
    void addArc(const uint64_t _timeStepEnd,
                const QVector3D &_rotationCenter,
                const QVector3D &_rotationNormal,
                const float _angleDeg);

    /*!
     * \brief Add accelerated movement over circle
     * \param _timeStepStart Movement start time
     * \param _timeStepEnd Movement end time
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _angleDeg Arc angle in degrees
     * \param _acceleration Acceleration duration according to total movement time
     * \param _deceleration Deceleration duration according to total movement time
     */
    void addArcAccel(const uint64_t _timeStepStart,
                     const uint64_t _timeStepEnd,
                     const QVector3D &_rotationCenter,
                     const QVector3D &_rotationNormal,
                     const float _angleDeg,
                     const float _acceleration = 0.1f,
                     const float _deceleration = 0.1f);

    /*!
     * \brief Add accelerated movement over circle
     * \param _timeStepEnd Movement end time
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _angleDeg Arc angle in degrees
     * \param _acceleration Acceleration duration according to total movement time
     * \param _deceleration Deceleration duration according to total movement time
     */
    void addArcAccel(const uint64_t _timeStepEnd,
                     const QVector3D &_rotationCenter,
                     const QVector3D &_rotationNormal,
                     const float _angleDeg,
                     const float _acceleration = 0.1f,
                     const float _deceleration = 0.1f);

    /*!
     * \brief Add movement over bezier curve
     * \param _timeStepStart Movement start time
     * \param _timeStepEnd Movement end time
     * \param _value Final value
     * \param _beginDir Begin direction
     * \param _endDir End direction
     */
    void addBezier(const uint64_t _timeStepStart,
                   const uint64_t _timeStepEnd,
                   const QVector3D &_value,
                   const QVector3D &_beginDir,
                   const QVector3D &_endDir);

    /*!
     * \brief Add movement over bezier curve
     * \param _timeStepEnd Movement end time
     * \param _value Final value
     * \param _beginDir Begin direction
     * \param _endDir End direction
     */
    void addBezier(const uint64_t _timeStepEnd,
                   const QVector3D &_value,
                   const QVector3D &_beginDir,
                   const QVector3D &_endDir);

 protected:
    /*! \brief Helper structure for acceleration */
    struct Accel
    {
        uint64_t dur1 = 0UL;  //!< Duration acceleration
        uint64_t dur2 = 0UL;  //!< Duration constant movement
        uint64_t dur3 = 0UL;  //!< Duration deceleration
        float v0 = 0.0f;      //!< Velocity
        float a1 = 0.0f;      //!< Acceleration
        float a3 = 0.0f;      //!< Deceleration
        float l1 = 0.0f;      //!< Length acceleration
        float l3 = 0.0f;      //!< Length deceleration
    };

    /*!
     * \brief Initialize acceleration structure
     * \param _out Output object
     * \param _duration Duration in ms
     * \param _length Total movement length
     * \param _acceleration Acceleration duration according to total movement time
     * \param _deceleration Deceleration duration according to total movement time
     * \return Success flag
     */
    bool initAccel(Accel &_out,
                   const uint64_t _duration,
                   const float _length,
                   const float _acceleration,
                   const float _deceleration);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICVEC3_H
