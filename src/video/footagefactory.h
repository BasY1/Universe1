#ifndef UNIVERSE1_VIDEO_FOOTAGEFACTORY_H
#define UNIVERSE1_VIDEO_FOOTAGEFACTORY_H

#include "footage.h"

namespace Universe1 {
namespace Video {

/*! \brief Footage factory interface */
class FootageFactoryInterface
{
 public:
    /*!
     * \brief Create footage
     * \param _footageId Footage ID
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     * \return Created object
     */
    virtual Footage *create(const uint64_t _footageId,
                            const uint64_t _footageStartTime,
                            const std::pair<QVector3D, QVector3D> &_lastCamera) const = 0;
};

/*!
 * \brief Footage factory
 * \tparam T Footage class
 */
template <typename T>
class FootageFactory : public FootageFactoryInterface
{
 public:
    /*!
     * \brief Constructor
     */
    template <typename = std::enable_if<std::is_base_of<Footage, T>::value>>
    inline FootageFactory()
    {
    }

    /*!
     * \brief Create footage
     * \param _footageId Footage ID
     * \param _footageStartTime Footage starting time within overall video in ms
     * \param _lastCamera Last camera position from previous footage
     * \return Created object
     */
    Footage *create(const uint64_t _footageId,
                    const uint64_t _footageStartTime,
                    const std::pair<QVector3D, QVector3D> &_lastCamera) const
    {
        return new T(_footageId, _footageStartTime, _lastCamera);
    }
};

/*!
 * \brief Footage database
 */
struct Footages
{
    static std::list<FootageFactoryInterface *> sequence;  //!< Sequence of footage classes

    /*!
     * \brief Append footage class to sequence
     * \return
     */
    template <typename T>
    static void add()
    {
        sequence.push_back(new FootageFactory<T>());
    }

    /*!
     * \brief Initialize footage
     * \param _footages Output footage objects
     * \return Total video duration in ms
     */
    static uint64_t init(std::list<Footage *> &_footages);

    /*!
     * \brief Save HTML file with subtitles
     * \param _footages Footage objects
     * \param _fileName File name
     * \return Success flag
     */
    static bool saveSubsHtml(const std::list<Footage *> &_footages, const QString &_fileName);

    /*!
     * \brief Save video frames index file
     * \param _footages Footage objects
     * \param _fileName File name
     * \return Success flag
     */
    static bool saveIndexes(const std::list<Footage *> &_footages, const QString &_fileName);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_FOOTAGEFACTORY_H
