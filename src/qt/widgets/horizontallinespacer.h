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
};

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_HORIZONTALLINESPACER_H
