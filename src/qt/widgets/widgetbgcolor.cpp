/*!
 * \file qt/widgets/widgetbgcolor.cpp
 * \author Michal Steller
 * \brief The QT Background color widget class implementations
 */

#include "widgetbgcolor.h"

#include <QMouseEvent>
#include <QPainter>

/*!
 * \brief Constructor
 * \param _color Color
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetBGColor::WidgetBGColor(const QColor _color, QWidget *_parent)
    : QWidget(_parent)
    , m_color(_color)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(fontMetrics().height(), fontMetrics().height());
}

/*!
 * \brief Setter for background color
 * \param _color Background color
 */
void Universe1::Widgets::WidgetBGColor::setColor(QColor _color)
{
    m_color = _color;
    update();
}

/*!
 * \brief Paint event
 * \param _event Event data
 */
void Universe1::Widgets::WidgetBGColor::paintEvent(QPaintEvent *_event)
{
    Q_UNUSED(_event)

    static const int offset = 2;
    QPainter painter(this);
    painter.fillRect(offset, offset, width() - 2 * offset, height() - 2 * offset, m_color);
}

/*!
 * \brief Mouse double click event
 * \param _event Event data
 */
void Universe1::Widgets::WidgetBGColor::mouseDoubleClickEvent(QMouseEvent *_event)
{
    if (_event->buttons().testFlag(Qt::LeftButton))
        emit doubleClicked();
}
