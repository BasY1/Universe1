/*!
 * \file qt/widgets/horizontallinespacer.h
 * \author Michal Steller
 * \brief The QT Horizontal line spacer class declarations
 */

#ifndef UNIVERSE1_WIDGETS_HORIZONTALLINESPACER_H
#define UNIVERSE1_WIDGETS_HORIZONTALLINESPACER_H

#include <QWidget>

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Horizontal line spacer item
 */
class HorizontalLineSpacer : public QWidget
{
    Q_OBJECT
 public:
    HorizontalLineSpacer(const QColor _color = Qt::black, QWidget *_parent = nullptr);
    inline QColor color() const;

 public slots:
    void setColor(QColor _color);

 protected:
    void paintEvent(QPaintEvent *_event) override;

 protected:
    QColor m_color;  //!< Current color
};

/*!
 * \brief Getter for current color
 * \returns Current color
 */
inline QColor HorizontalLineSpacer::color() const
{
    return m_color;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_HORIZONTALLINESPACER_H
