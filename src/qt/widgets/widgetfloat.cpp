/*!
 * \file qt/widgets/widgetfloat.cpp
 * \author Michal Steller
 * \brief The QT \c float value widget class implementations
 */

#include "widgetfloat.h"

#include <QGridLayout>

/*!
 * \brief Power of 10 tool function
 * \param _exponent Exponent value
 * \return \f$10^{exponent}\f$
 */
static int pow10(int _exponent)
{
    int value = 10;
    int result = 1;
    while (_exponent)
    {
        if (_exponent & 1)
            result *= value;
        value *= value;
        _exponent >>= 1;
    }
    return result;
}

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _name Color name displayed on GUI
 * \param _orientation Orientation
 * \param _decimals Decimal count (range 1 to 6)
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetFloat::WidgetFloat(const float _value,
                                             const int _minimum,
                                             const int _maximum,
                                             const int _decimals,
                                             const QString &_name,
                                             const Qt::Orientation _orientation,
                                             QWidget *_parent)
    : QWidget(_parent)
    , m_decimals(std::min(6, std::max(1, _decimals)))
    , m_mult(pow10(m_decimals))
    , m_multF(m_mult)
    , m_minimum(_minimum)
    , m_maximum(_maximum)
    , m_rangeF(m_maximum - m_minimum)
    , m_sliderRangeF((_maximum - _minimum) * m_mult)
    , m_value(std::min(m_maximum, std::max(m_minimum, _value)))
    , m_slider(new QSlider(_orientation))
    , m_box(new QDoubleSpinBox())
    , m_labelName(new QLabel(_name.isEmpty() ? QString(" ") : _name))
    , m_labelColor(new QLabel(" "))
{
    m_slider->setRange(_minimum * m_mult, _maximum * m_mult);
    m_slider->setValue(static_cast<int>(m_multF * m_value));

    m_box->setDecimals(m_decimals);
    m_box->setRange(m_minimum, m_maximum);
    m_box->setValue(m_value);

    m_box->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_labelName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_labelColor->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGridLayout *lay = new QGridLayout();

    if (_orientation == Qt::Horizontal)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        lay->addWidget(m_labelName, 0, 0);
        // lay->addWidget(m_labelColor, 0, 1);
        lay->addWidget(m_box, 0, 1);
        lay->addWidget(m_slider, 0, 2);

        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, 1, 3);
    }
    else
    {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        m_slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay->addWidget(m_labelName, 0, 0);
        lay->addWidget(m_labelColor, 1, 0);
        lay->addWidget(m_box, 2, 0);
        lay->addWidget(m_slider, 3, 0);

        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 1, 4, 1);
    }

    setLayout(lay);

    connect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);
    connect(m_box,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &WidgetFloat::boxChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::WidgetFloat::~WidgetFloat()
{
    disconnect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetFloat::boxChanged);
}

/*!
 * \brief Setup new value
 * \param _value New value
 */
void Universe1::Widgets::WidgetFloat::setValue(float _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetFloat::boxChanged);

    m_value = std::min(m_maximum, std::max(m_minimum, _value));

    m_slider->setValue(static_cast<int>(m_multF * m_value));

    m_box->setValue(m_value);

    connect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);
    connect(m_box,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &WidgetFloat::boxChanged);
}

/*!
 * \brief Slider changed handler
 * \param _value New slider value
 */
void Universe1::Widgets::WidgetFloat::sliderChanged(int _value)
{
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetFloat::boxChanged);

    m_value = m_minimum + m_rangeF * (static_cast<float>(_value - m_slider->minimum()) / m_sliderRangeF);
    m_box->setValue(m_value);

    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetFloat::boxChanged);

    emit changed(m_value);
}

/*!
 * \brief Box changed handler
 * \param _value New value
 */
void Universe1::Widgets::WidgetFloat::boxChanged(double _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);

    m_value = _value;
    m_slider->setValue(static_cast<int>(m_multF * m_value));

    connect(m_slider, &QSlider::valueChanged, this, &WidgetFloat::sliderChanged);

    emit changed(m_value);
}
