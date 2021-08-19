/*!
 * \file qt/widgets/gui/guicolor.h
 * \author Michal Steller
 * \brief The QT color GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUICOLOR_H
#define UNIVERSE1_WIDGETS_GUI_GUICOLOR_H

#include "../widgetbgcolor.h"
#include "guiint.h"

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Single \c QColor GUI
 */
class GuiColor : public QObject
{
    Q_OBJECT
 public:
    GuiColor(const QColor _color, const Qt::Orientation _orientation, QObject *_parent = nullptr);
    inline GuiColor(const QColor _color, QObject *_parent = nullptr);

    ~GuiColor();

    inline QColor color() const;
    inline GuiInt *redGui();
    inline GuiInt *greenGui();
    inline GuiInt *blueGui();
    inline WidgetBGColor *bgWidget();

    void layoutRow(const QString &_name, QGridLayout *_lay, int &_row);

 protected:
    void connectAll();
    void disconnectAll();

 public slots:
    void setColor(QColor _color);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);
    void setToolTip(QString _toolTip);

 protected slots:
    void redChanged(int _value);
    void greenChanged(int _value);
    void blueChanged(int _value);

    void fromQColorDialog();

 signals:
    /*!
     * \brief Emits when color was changed
     * \param _color New color value
     */
    void changed(QColor _color);

 protected:
    QColor m_color;             //!< Current color
    GuiInt *m_red;              //!< Red slider
    GuiInt *m_green;            //!< Green slider
    GuiInt *m_blue;             //!< Blue slider
    WidgetBGColor *m_bgWidget;  //!< Painted current color widget
};

/*!
 * \brief Constructor
 * \param _color Color
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiColor::GuiColor(const QColor _color, QObject *_parent)
    : GuiColor(_color, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current color
 * \returns Current color
 */
inline QColor GuiColor::color() const
{
    return m_color;
}

/*!
 * \brief Getter for red widgets
 * \returns Red widgets
 */
inline GuiInt *GuiColor::redGui()
{
    return m_red;
}

/*!
 * \brief Getter for green widgets
 * \returns Green widgets
 */
inline GuiInt *GuiColor::greenGui()
{
    return m_green;
}

/*!
 * \brief Getter for blue widgets
 * \returns Blue widgets
 */
inline GuiInt *GuiColor::blueGui()
{
    return m_blue;
}

/*!
 * \brief Getter for color widget
 * \returns Color widget
 */
inline WidgetBGColor *GuiColor::bgWidget()
{
    return m_bgWidget;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUICOLOR_H
