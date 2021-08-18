/*!
 * \file qt/widgets/widgetbgcolor.h
 * \author Michal Steller
 * \brief The QT Background color widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETBGCOLOR_H
#define UNIVERSE1_WIDGETS_WIDGETBGCOLOR_H

#include <QWidget>

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Background color widget
 */
class WidgetBGColor : public QWidget
{
    Q_OBJECT
 public:
    WidgetBGColor(const QColor _color, QWidget *_parent = nullptr);

    inline QColor color() const;

 public slots:
    void setColor(QColor _color);

 protected:
    void paintEvent(QPaintEvent *_event) override;
    void mouseDoubleClickEvent(QMouseEvent *_event) override;

 signals:
    void doubleClicked();  //!< Widget double clicked signal

 protected:
    QColor m_color;  //!< Current color
};

/*!
 * \brief Getter for current color
 * \returns Current color
 */
inline QColor WidgetBGColor::color() const
{
    return m_color;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETBGCOLOR_H
