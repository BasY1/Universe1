#ifndef UNIVERSE1_VIDEO_TUTORIAL_DEMO3DTEXT_H
#define UNIVERSE1_VIDEO_TUTORIAL_DEMO3DTEXT_H

#include "../footage.h"

namespace Universe1 {
namespace Video {
namespace Tutorial {

/*! \brief Demo for 3D Text */
class Demo3DText : public Footage
{
 public:
    /*!
     * \brief Constructor
     * \param _footageId Footage index
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     */
    Demo3DText(const uint64_t _footageId,
               const uint64_t _footageStartTime,
               const std::pair<QVector3D, QVector3D> &_lastCamera);
};

}  // namespace Tutorial
}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_TUTORIAL_DEMO3DTEXT_H
