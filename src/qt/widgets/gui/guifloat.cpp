/*!
 * \file qt/widgets/gui/guifloat.cpp
 * \author Michal Steller
 * \brief The QT \c float value GUI class implementations
 */

#include "guifloat.h"
#include <QLabel>

/*!
 * \brief Power of 10 tool function
 * \param _exponent Exponent value
 * \returns \f$10^{exponent}\f$
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
 * \param _decimals Decimal count (range 0 to 6)
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiFloat::GuiFloat(const float _value,
                                            const float _minimum,
                                            const float _maximum,
                                            const int _decimals,
                                            const Qt::Orientation _orientation,
                                            QObject *_parent)
    : QObject(_parent)
    , m_decimals(std::min(6, std::max(0, _decimals)))
    , m_mult(pow10(m_decimals))
    , m_multF(m_mult)
    , m_minimum(_minimum)
    , m_maximum(_maximum)
    , m_rangeF(m_maximum - m_minimum)
    , m_sliderRangeF(0.0F)
    , m_value(std::min(m_maximum, std::max(m_minimum, _value)))
    , m_slider(new QSlider(_orientation))
    , m_box(new QDoubleSpinBox())
{
    m_slider->setRange(static_cast<int>(_minimum * m_multF), static_cast<int>(_maximum * m_multF));
    m_slider->setValue(static_cast<int>(m_multF * m_value));
    m_sliderRangeF = static_cast<float>(m_slider->maximum() - m_slider->minimum());

    m_box->setDecimals(m_decimals);
    m_box->setRange(m_minimum, m_maximum);
    m_box->setValue(m_value);
    m_box->setSingleStep(1.0F / m_multF);

    m_box->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    if (_orientation == Qt::Horizontal)
        m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    else
        m_slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);
    connect(m_box,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &GuiFloat::boxChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiFloat::~GuiFloat()
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &GuiFloat::boxChanged);
}

/*!
 * \brief Fill new layout row with widgets
 * \param _name Property name
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _startCol Starting column index
 */
void Universe1::Widgets::GUI::GuiFloat::layoutRow(const QString &_name,
                                                  QGridLayout *_lay,
                                                  int &_row,
                                                  const int _startCol)
{
    _lay->addWidget(new QLabel(_name), _row, _startCol, 1, 2);
    _lay->addWidget(m_box, _row, _startCol + 2);
    _lay->addWidget(m_slider, _row, _startCol + 3);
    ++_row;
}

/*!
 * \brief Setup new value
 * \param _value New value
 */
void Universe1::Widgets::GUI::GuiFloat::setValue(float _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &GuiFloat::boxChanged);

    m_value = std::min(m_maximum, std::max(m_minimum, _value));

    m_slider->setValue(static_cast<int>(m_multF * m_value));

    m_box->setValue(m_value);

    connect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);
    connect(m_box,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &GuiFloat::boxChanged);

    emit changed(m_value);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiFloat::setOrientation(Qt::Orientation _orientation)
{
    m_slider->setOrientation(_orientation);
    if (_orientation == Qt::Horizontal)
        m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    else
        m_slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiFloat::setEnabled(bool _value)
{
    m_slider->setEnabled(_value);
    m_box->setEnabled(_value);
}

/*!
 * \brief Setup widgets tool-tip
 * \param _toolTip Tool tip text
 */
void Universe1::Widgets::GUI::GuiFloat::setToolTip(QString _toolTip)
{
    m_slider->setToolTip(_toolTip);
    m_box->setToolTip(_toolTip);
}

/*!
 * \brief Slider changed handler
 * \param _value New slider value
 */
void Universe1::Widgets::GUI::GuiFloat::sliderChanged(int _value)
{
    disconnect(m_box,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &GuiFloat::boxChanged);

    m_value = m_minimum + m_rangeF * (static_cast<float>(_value - m_slider->minimum()) / m_sliderRangeF);
    m_box->setValue(m_value);

    connect(m_box,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &GuiFloat::boxChanged);

    emit changed(m_value);
}

/*!
 * \brief Box changed handler
 * \param _value New value
 */
void Universe1::Widgets::GUI::GuiFloat::boxChanged(double _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);

    m_value = _value;
    m_slider->setValue(static_cast<int>(m_multF * m_value));

    connect(m_slider, &QSlider::valueChanged, this, &GuiFloat::sliderChanged);

    emit changed(m_value);
}

/*!
 * \brief Setup new range for widgets
 * \param _minimum Minimum value (If higher then current value, then current value is used)
 * \param _maximum Maximum value (If lower then current value, then current value is used)
 */
void Universe1::Widgets::GUI::GuiFloat::setRange(const float _minimum, const float _maximum)
{
    m_minimum = std::min(_minimum, m_value);
    m_maximum = std::max(_maximum, m_value);
    m_rangeF = m_maximum - m_minimum;

    m_box->setRange(m_minimum, m_maximum);
    m_slider->setRange(static_cast<int>(m_minimum * m_multF), static_cast<int>(m_maximum * m_multF));
    m_sliderRangeF = static_cast<float>(m_slider->maximum() - m_slider->minimum());
}
