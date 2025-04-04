/*!
 * \file src/Audio/itemaudio.h
 * \brief Audio item
 */

#ifndef AUDIO_ITEMAUDIO_H
#define AUDIO_ITEMAUDIO_H

#include <QString>

namespace U1 {
namespace Audio {

/*! \brief Single sample audio item */
struct ItemAudio
{
    QString fileName;       //!< Audio file name
    QString subs;           //!< Subtitle text
    size_t timeStart;       //!< Start time step
    size_t timeOffsetSubs;  //!< Subtitle duration after audio finishes
    size_t audioDuration;   //!< Audio duration

    /*!
     * \brief Latest active time-step
     * \return Latest active time-step
     */
    inline size_t latestTimeStep() const
    {
        return timeStart + audioDuration + (subs.isEmpty() ? 0UL : timeOffsetSubs);
    }

    /*!
     * \brief Test if this item is active at given time step
     * \param _timeStep Time step
     * \return \c true if this item is active at given time step
     */
    inline bool isActive(const size_t _timeStep) const
    {
        return _timeStep >= timeStart && _timeStep < latestTimeStep();
    }
};

}  // namespace Audio
}  // namespace U1

#endif  // AUDIO_ITEMAUDIO_H
