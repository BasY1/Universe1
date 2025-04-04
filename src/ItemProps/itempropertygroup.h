/*!
 * \file src/ItemProps/itempropertygroup.h
 * \brief Base class for dynamic item property groups
 */

#ifndef PROPS_ITEMPROPERTYGROUP_H
#define PROPS_ITEMPROPERTYGROUP_H

#include "itemproperty.h"

#include <vector>

namespace U1 {
namespace Props {

/*! \brief Base class for dynamic item property groups */
class ItemPropertyGroup : public ItemProperty
{
 protected:
    std::vector<ItemProperty *> m_itemProperties;  //!< Collection of item properties

    /*!
     * \brief Constructor
     * \param _name Item property name
     */
    inline ItemPropertyGroup(const std::string &_name)
        : ItemProperty(_name)
    {
    }

 public:
    ~ItemPropertyGroup();  //!< Destructor delete all item properties

    /*!
     * \brief Getter for collection of item properties
     * \return Getter for collection of item properties
     */
    inline const std::vector<ItemProperty *> &itemProperties()
    {
        return m_itemProperties;
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;

 protected:
    /*!
     * \brief Setup properties database
     * \param _itemProperties Collection of item properties
     */
    inline void setupProperties(const std::vector<ItemProperty *> &_itemProperties)
    {
        m_itemProperties = _itemProperties;
    }

    /*!
     * \brief Add property to database
     * \param _itemProperty Item property to add
     */
    inline void addProperty(ItemProperty *_itemProperty)
    {
        m_itemProperties.push_back(_itemProperty);
    }
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYGROUP_H
