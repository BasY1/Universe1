/*!
 * \file qt/widgets/gui/guiint.h
 * \author Michal Steller
 * \brief The QT \c int value GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUIINT_H
#define UNIVERSE1_WIDGETS_GUI_GUIINT_H

#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Single \c int value GUI
 */
class GuiInt : public QObject
{
    Q_OBJECT
 public:
    GuiInt(const int _value,
           const int _minimum,
           const int _maximum,
           const Qt::Orientation _orientation,
           QObject *_parent = nullptr);

    inline GuiInt(const int _value, const int _minimum, const int _maximum, QObject *_parent = nullptr);
    inline GuiInt(const int _value, const Qt::Orientation _orientation, QObject *_parent = nullptr);
    inline GuiInt(const int _value, QObject *_parent = nullptr);

    ~GuiInt();

    inline int value() const;

    inline QSlider *slider();
    inline QSpinBox *box();

    void layoutRow(const QString &_name, QGridLayout *_lay, int &_row, const int _startCol = 0);

 public slots:
    void setValue(int _value);
    void setRange(int _minimum, int _maximum);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);
    void setToolTip(QString _toolTip);

 protected slots:
    void sliderChanged(int _value);
    void boxChanged(int _value);

 signals:
    /*!
     * \brief Emits when value was changed
     * \param _value New value
     */
    void changed(int _value);

 protected:
    int m_value;  //!< Current value

    QSlider *m_slider;  //!< Slider
    QSpinBox *m_box;    //!< Spin box
};

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiInt::GuiInt(const int _value, const int _minimum, const int _maximum, QObject *_parent)
    : GuiInt(_value, _minimum, _maximum, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default range 0 to 255
 */
inline GuiInt::GuiInt(const int _value, const Qt::Orientation _orientation, QObject *_parent)
    : GuiInt(_value, 0, 255, _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _parent Parent \c QObject
 * \note Default range 0 to 255
 * \note Default horizontal orientation
 */
inline GuiInt::GuiInt(const int _value, QObject *_parent)
    : GuiInt(_value, 0, 255, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current value
 * \returns Current value
 */
inline int GuiInt::value() const
{
    return m_value;
}

/*!
 * \brief Getter for slider widget
 * \returns Slider widget
 */
inline QSlider *GuiInt::slider()
{
    return m_slider;
}

/*!
 * \brief Getter for spin box widget
 * \returns Spin box widget
 */
inline QSpinBox *GuiInt::box()
{
    return m_box;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUIINT_H
