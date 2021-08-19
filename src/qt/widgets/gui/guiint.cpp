/*!
 * \file qt/widgets/gui/guiint.cpp
 * \author Michal Steller
 * \brief The QT \c int value GUI class implementations
 */

#include "guiint.h"
#include <QLabel>

/*!
 * \brief Constructor
 * \param _value Value
 * \param _minimum Minimum possible value
 * \param _maximum Maximum possible value
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiInt::GuiInt(
    const int _value, const int _minimum, const int _maximum, const Qt::Orientation _orientation, QObject *_parent)
    : QObject(_parent)
    , m_value(std::min(_maximum, std::max(_minimum, _value)))
    , m_slider(new QSlider(_orientation))
    , m_box(new QSpinBox())
{
    m_slider->setRange(_minimum, _maximum);
    m_slider->setValue(m_value);

    m_box->setRange(_minimum, _maximum);
    m_box->setValue(m_value);
    m_box->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    if (_orientation == Qt::Horizontal)
        m_slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    else
        m_slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);
    connect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiInt::~GuiInt()
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);
    disconnect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);
}

/*!
 * \brief Fill new layout row with widgets
 * \param _name Property name
 * \param _lay Layout object
 * \param _row Current row within layout
 */
void Universe1::Widgets::GUI::GuiInt::layoutRow(const QString &_name, QGridLayout *_lay, int &_row)
{
    _lay->addWidget(new QLabel(_name), _row, 0, 1, 2);
    _lay->addWidget(m_box, _row, 2);
    _lay->addWidget(m_slider, _row, 3);
    ++_row;
}

/*!
 * \brief Setup new value
 * \param _value New value
 */
void Universe1::Widgets::GUI::GuiInt::setValue(int _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);
    disconnect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);

    m_value = std::min(m_box->maximum(), std::max(m_box->minimum(), _value));
    m_slider->setValue(m_value);

    m_box->setValue(m_value);

    connect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);
    connect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);

    emit changed(m_value);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiInt::setOrientation(Qt::Orientation _orientation)
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
void Universe1::Widgets::GUI::GuiInt::setEnabled(bool _value)
{
    m_slider->setEnabled(_value);
    m_box->setEnabled(_value);
}

/*!
 * \brief Setup widgets tool-tip
 * \param _toolTip Tool tip text
 */
void Universe1::Widgets::GUI::GuiInt::setToolTip(QString _toolTip)
{
    m_slider->setToolTip(_toolTip);
    m_box->setToolTip(_toolTip);
}

/*!
 * \brief Setup new range
 * \param _minimum New minimum value
 * \param _maximum New maximum value
 */
void Universe1::Widgets::GUI::GuiInt::setRange(int _minimum, int _maximum)
{
    m_slider->setRange(_minimum, _maximum);
    m_box->setRange(_minimum, _maximum);
}

/*!
 * \brief Slider changed handler
 * \param _value New slider value
 */
void Universe1::Widgets::GUI::GuiInt::sliderChanged(int _value)
{
    disconnect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);

    m_value = std::min(m_box->maximum(), std::max(m_box->minimum(), _value));
    m_box->setValue(m_value);

    connect(m_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GuiInt::boxChanged);

    emit changed(m_value);
}

/*!
 * \brief Box changed handler
 * \param _value New value
 */
void Universe1::Widgets::GUI::GuiInt::boxChanged(int _value)
{
    disconnect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);

    m_value = std::min(m_box->maximum(), std::max(m_box->minimum(), _value));
    m_slider->setValue(m_value);

    connect(m_slider, &QSlider::valueChanged, this, &GuiInt::sliderChanged);

    emit changed(m_value);
}
