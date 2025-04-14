/*!
 * \file src/Items/item.h
 * \brief Basic video 2D item
 */

#ifndef ITEMS_ITEM2D_H
#define ITEMS_ITEM2D_H

#include "item.h"

#include <QPainter>
#include <QSize>

namespace U1 {
namespace Items {

/*! \brief Basic video 2D item */
class Item2D : public Item
{
 protected:
    /*!
     * \brief Protected constructor
     * \param _name Item name
     * \param _alpha Initial alpha factor
     * \param _visible Initial visible flag
     */
    inline Item2D(const std::string &_name, const uint8_t _alpha = 255U, const bool _visible = true)
        : Item(_name, _alpha, _visible)
    {
    }

 public:
    /*!
     * \brief Paint item
     * \param _painter Painter
     * \param _screenSize Screen size
     * \param _timeStep Time-step
     * \return
     */
    virtual void paintItem(QPainter &_painter, const QSize &_screenSize, const size_t _timeStep) const = 0;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM2D_H
