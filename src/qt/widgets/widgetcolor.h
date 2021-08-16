/*!
 * \file qt/widgets/widgetcolor.h
 * \author Michal Steller
 * \brief The QT color widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETCOLOR_H
#define UNIVERSE1_WIDGETS_WIDGETCOLOR_H

#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Single \c QColor selection widget
 */
class WidgetColor : public QWidget
{
    Q_OBJECT
 public:
    WidgetColor(const QColor _color,
                const QString &_name,
                const Qt::Orientation _orientation,
                QWidget *_parent = nullptr);

    inline WidgetColor(const QColor _color, const QString &_name, QWidget *_parent = nullptr);
    inline WidgetColor(const QColor _color, const Qt::Orientation _orientation, QWidget *_parent = nullptr);
    inline WidgetColor(const QColor _color, QWidget *_parent = nullptr);

    ~WidgetColor();

    inline QColor color() const;

 protected:
    void updateLabColor();

    void connectAll();
    void disconnectAll();

 public slots:
    void setColor(QColor _color);

 protected slots:
    void sliderRedChanged(int _value);
    void sliderGreenChanged(int _value);
    void sliderBlueChanged(int _value);

    void boxRedChanged(int _value);
    void boxGreenChanged(int _value);
    void boxBlueChanged(int _value);

    void fromQColorDialog();

 signals:
    /*!
     * \brief Emits when color was changed
     * \param _color New color value
     */
    void changed(QColor _color);

 protected:
    QColor m_color;             //!< Current color
    QSlider *m_sliderRed;       //!< Red slider
    QSlider *m_sliderGreen;     //!< Green slider
    QSlider *m_sliderBlue;      //!< Blue slider
    QSpinBox *m_boxRed;         //!< Red spin box
    QSpinBox *m_boxGreen;       //!< Green spin box
    QSpinBox *m_boxBlue;        //!< Blue spin box
    QPushButton *m_buttonName;  //!< Button for select color using native Qt color dialog
    QLabel *m_labelColor;       //!< Label with current color in background
};

/*!
 * \brief Constructor
 * \param _color Color
 * \param _name Color name displayed on GUI
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetColor::WidgetColor(const QColor _color, const QString &_name, QWidget *_parent)
    : WidgetColor(_color, _name, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _color Color
 * \param _orientation Orientation
 * \param _parent Parent \c QWidget
 */
inline WidgetColor::WidgetColor(const QColor _color, const Qt::Orientation _orientation, QWidget *_parent)
    : WidgetColor(_color, QString(), _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _color Color
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetColor::WidgetColor(const QColor _color, QWidget *_parent)
    : WidgetColor(_color, QString(), Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current color
 * \return Current color
 */
inline QColor WidgetColor::color() const
{
    return m_color;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETCOLOR_H
