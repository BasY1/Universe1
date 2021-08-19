/*!
 * \file qt/widgets/horizontallinespacer.cpp
 * \author Michal Steller
 * \brief The QT Horizontal line spacer class implementations
 */

#include "horizontallinespacer.h"

/*!
 * \brief Constructor
 * \param _color Color
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::HorizontalLineSpacer::HorizontalLineSpacer(const QColor _color, QWidget *_parent)
    : QWidget(_parent)
{
    setMinimumSize(1, 1);
    setStyleSheet(QString("background: %1").arg(_color.name()));
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
