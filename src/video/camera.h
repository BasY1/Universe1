#ifndef UNIVERSE1_VIDEO_CAMERA_H
#define UNIVERSE1_VIDEO_CAMERA_H

#include "dynamicproperty/dynamictextgroup.h"

namespace Universe1 {
namespace Video {

/*! \brief Open GL camera */
struct Camera
{
    DynamicVec3 pos;     //!< Camera position property
    DynamicVec3 lookAt;  //!< Look at position property
    DynamicVec3 up;      //!< Camera up vector

    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _pos Initial camera position
     * \param _lookAt Initial look at position
     * \param _up Initial up vector
     */
    Camera(const std::string &_footageName,
           const QVector3D &_pos = QVector3D(1, -8, 3),
           const QVector3D &_lookAt = QVector3D(0, 0, 2),
           const QVector3D &_up = QVector3D(0, 0, 1));

    /*!
     * \brief Initialize object
     * \param _duration Total footage duration ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Add same values as last stored
     * \param _timeStep Time-step
     * \param _addUp Apply to up vector property flag
     */
    inline void addSame(const uint64_t _timeStep, const bool _addUp = false)
    {
        pos.addSame(_timeStep);
        lookAt.addSame(_timeStep);
        if (_addUp)
            up.addSame(_timeStep);
    }

    /*!
     * \brief Getter for MVP matrix at given time-step
     * \param _timeStep Time-step
     * \return MVP matrix at given time-step
     */
    inline QMatrix4x4 getMvp(const uint64_t _timeStep) const
    {
        return makeMvp(pos.getValue(_timeStep), lookAt.getValue(_timeStep), up.getValue(_timeStep));
    }

    /*!
     * \brief Getter for full camera statistics (position and MVP matrix)
     * \param _timeStep Time-step
     * \return Camera statistics at given time-step
     */
    inline std::pair<QVector3D, QMatrix4x4> getStats(const uint64_t _timeStep) const
    {
        const QVector3D curPos = pos.getValue(_timeStep);
        return {curPos, makeMvp(curPos, lookAt.getValue(_timeStep), up.getValue(_timeStep))};
    }

    /*!
     * \brief Make MVP matrix
     * \param _pos Camera position
     * \param _lookAt Camera look at
     * \param _up Camera up vector
     * \return MVP matrix
     */
    static QMatrix4x4 makeMvp(const QVector3D &_pos, const QVector3D &_lookAt, const QVector3D &_up);

    /*!
     * \brief Getter for last stored position and look at vectors
     * \return Last stored position and look at vectors
     */
    inline std::pair<QVector3D, QVector3D> getLastState() const
    {
        return {pos.values.back().second, lookAt.values.back().second};
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_CAMERA_H
