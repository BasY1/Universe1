/*!
 * \file qt/widgets/horizontallinespacer.cpp
 * \author Michal Steller
 * \brief The QT Horizontal line spacer class implementations
 */

#include "horizontallinespacer.h"
#include <QPainter>

/*!
 * \brief Constructor
 * \param _color Color
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::HorizontalLineSpacer::HorizontalLineSpacer(const QColor _color, QWidget *_parent)
    : QWidget(_parent)
    , m_color(_color)
{
    setMinimumSize(1, 1);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

/*!
 * \brief Setter for color
 * \param _color New color
 */
void Universe1::Widgets::HorizontalLineSpacer::setColor(QColor _color)
{
    m_color = _color;
    update();
}

/*!
 * \brief Paint event
 * \param _event Event data
 */
void Universe1::Widgets::HorizontalLineSpacer::paintEvent(QPaintEvent *_event)
{
    Q_UNUSED(_event)
    QPainter painter(this);
    painter.fillRect(rect(), m_color);
}
