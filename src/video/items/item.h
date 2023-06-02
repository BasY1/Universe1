#ifndef UNIVERSE1_VIDEO_ITEM_H
#define UNIVERSE1_VIDEO_ITEM_H

#include "../shader.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Base visible item structure
 */
struct Item
{
    const std::string name;  //!< Item name

 protected:
    std::list<DynamicProperty *> props;  //!< Dynamic properties

 public:
    /*!
     * \brief Constructor
     * \param _name Item name
     */
    Item(const std::string &_name);

    virtual ~Item() = default;  //!< Destructor

    /*!
     * \brief Initialize item properties
     * \param _duration Total footage duration
     * \return Success flag
     */
    virtual bool initialize(const uint64_t _duration);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM2D_H
