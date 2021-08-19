/*!
 * \file qt/widgets/gui/guifloat.h
 * \author Michal Steller
 * \brief The QT \c float value GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUIFLOAT_H
#define UNIVERSE1_WIDGETS_GUI_GUIFLOAT_H

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QSlider>

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Single \c float value GUI
 */
class GuiFloat : public QObject
{
    Q_OBJECT
 public:
    GuiFloat(const float _value,
             const int _minimum,
             const int _maximum,
             const int _decimals,
             const Qt::Orientation _orientation,
             QObject *_parent = nullptr);

    inline GuiFloat(const float _value,
                    const int _minimum,
                    const int _maximum,
                    const Qt::Orientation _orientation,
                    QObject *_parent = nullptr);

    inline GuiFloat(
        const float _value, const int _minimum, const int _maximum, const int _decimals, QObject *_parent = nullptr);
    inline GuiFloat(const float _value, const int _minimum, const int _maximum, QObject *_parent = nullptr);

    ~GuiFloat();

    inline float value() const;
    inline QSlider *slider();
    inline QDoubleSpinBox *box();

    void layoutRow(const QString &_name, QGridLayout *_lay, int &_row);

 public slots:
    void setValue(float _value);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);
    void setToolTip(QString _toolTip);

 protected slots:
    void sliderChanged(int _value);
    void boxChanged(double _value);

 signals:
    /*!
     * \brief Emits when value was changed
     * \param _value New value
     */
    void changed(float _value);

 protected:
    const int m_decimals;        //!< Used decimal count
    const int m_mult;            //!< Slider integral value multiplication
    const float m_multF;         //!< Slider integral value multiplication as \c float holder
    const float m_minimum;       //!< Minimum possible value
    const float m_maximum;       //!< Maximum possible value
    const float m_rangeF;        //!< Maximum possible value
    const float m_sliderRangeF;  //!< Slider integral range as \c float holder

    float m_value;  //!< Current value

    QSlider *m_slider;      //!< Slider
    QDoubleSpinBox *m_box;  //!< Spin box
};

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _decimals Decimal count (range 0 to 6)
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiFloat::GuiFloat(
    const float _value, const int _minimum, const int _maximum, const int _decimals, QObject *_parent)
    : GuiFloat(_value, _minimum, _maximum, _decimals, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 */
inline GuiFloat::GuiFloat(
    const float _value, const int _minimum, const int _maximum, const Qt::Orientation _orientation, QObject *_parent)
    : GuiFloat(_value, _minimum, _maximum, 3, _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 * \note Default decimal count 3
 */
inline GuiFloat::GuiFloat(const float _value, const int _minimum, const int _maximum, QObject *_parent)
    : GuiFloat(_value, _minimum, _maximum, 3, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current value
 * \returns Current value
 */
inline float GuiFloat::value() const
{
    return m_value;
}

/*!
 * \brief Getter for slider widget
 * \returns Slider widget
 */
inline QSlider *GuiFloat::slider()
{
    return m_slider;
}

/*!
 * \brief Getter for spin box widget
 * \returns Spin box widget
 */
inline QDoubleSpinBox *GuiFloat::box()
{
    return m_box;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUIFLOAT_H
