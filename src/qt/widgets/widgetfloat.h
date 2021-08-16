/*!
 * \file qt/widgets/widgetfloat.h
 * \author Michal Steller
 * \brief The QT \c float value widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETFLOAT_H
#define UNIVERSE1_WIDGETS_WIDGETFLOAT_H

#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Single \c float value editor widget
 */
class WidgetFloat : public QWidget
{
    Q_OBJECT
 public:
    WidgetFloat(const float _value,
                const int _minimum,
                const int _maximum,
                const int _decimals,
                const QString &_name,
                const Qt::Orientation _orientation,
                QWidget *_parent = nullptr);

    inline WidgetFloat(
        const float _value, const int _minimum, const int _maximum, const QString &_name, QWidget *_parent = nullptr);

    inline WidgetFloat(const float _value,
                       const int _minimum,
                       const int _maximum,
                       const Qt::Orientation _orientation,
                       QWidget *_parent = nullptr);

    inline WidgetFloat(const float _value, const int _minimum, const int _maximum, QWidget *_parent = nullptr);

    inline WidgetFloat(const float _value,
                       const int _minimum,
                       const int _maximum,
                       const int _decimals,
                       const QString &_name,
                       QWidget *_parent = nullptr);

    inline WidgetFloat(const float _value,
                       const int _minimum,
                       const int _maximum,
                       const int _decimals,
                       const Qt::Orientation _orientation,
                       QWidget *_parent = nullptr);

    inline WidgetFloat(
        const float _value, const int _minimum, const int _maximum, const int _decimals, QWidget *_parent = nullptr);

    ~WidgetFloat();

    inline float value() const;

 public slots:
    void setValue(float _value);

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

    QSlider *m_slider;          //!< Slider
    QDoubleSpinBox *m_box;      //!< Spin box
    QLabel *m_labelName;        //!< Button for select color using native Qt color dialog
    QLabel *m_labelColor;       //!< Label with current color in background
};

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _name Value name displayed on GUI
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 * \note Default decimal count 3
 */
inline WidgetFloat::WidgetFloat(
    const float _value, const int _minimum, const int _maximum, const QString &_name, QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, 3, _name, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _orientation Orientation
 * \param _parent Parent \c QWidget
 * \note Default decimal count 3
 */
inline WidgetFloat::WidgetFloat(
    const float _value, const int _minimum, const int _maximum, const Qt::Orientation _orientation, QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, 3, QString(), _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 * \note Default decimal count 3
 */
inline WidgetFloat::WidgetFloat(const float _value, const int _minimum, const int _maximum, QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, 3, QString(), Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _decimals Decimal count (range 1 to 6)
 * \param _name Value name displayed on GUI
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetFloat::WidgetFloat(const float _value,
                                const int _minimum,
                                const int _maximum,
                                const int _decimals,
                                const QString &_name,
                                QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, _decimals, _name, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _decimals Decimal count (range 1 to 6)
 * \param _orientation Orientation
 * \param _parent Parent \c QWidget
 */
inline WidgetFloat::WidgetFloat(const float _value,
                                const int _minimum,
                                const int _maximum,
                                const int _decimals,
                                const Qt::Orientation _orientation,
                                QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, _decimals, QString(), _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _decimals Decimal count (range 1 to 6)
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetFloat::WidgetFloat(
    const float _value, const int _minimum, const int _maximum, const int _decimals, QWidget *_parent)
    : WidgetFloat(_value, _minimum, _maximum, _decimals, QString(), Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current value
 * \return Current value
 */
inline float WidgetFloat::value() const
{
    return m_value;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETFLOAT_H
