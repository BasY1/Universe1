/*!
 * \file qt/widgets/widgetcolor.cpp
 * \author Michal Steller
 * \brief The QT color widget class implementations
 */

#include "widgetcolor.h"

#include <QColorDialog>
#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _color Color
 * \param _name Color name displayed on GUI
 * \param _orientation Orientation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetColor::WidgetColor(const QColor _color,
                                             const QString &_name,
                                             const Qt::Orientation _orientation,
                                             QWidget *_parent)
    : QWidget(_parent)
    , m_color(_color)
    , m_sliderRed(new QSlider(_orientation))
    , m_sliderGreen(new QSlider(_orientation))
    , m_sliderBlue(new QSlider(_orientation))
    , m_boxRed(new QSpinBox())
    , m_boxGreen(new QSpinBox())
    , m_boxBlue(new QSpinBox())
    , m_buttonName(new QPushButton(_name.isEmpty() ? tr("Color") : _name))
    , m_labelColor(new QLabel(" "))
{
    m_sliderRed->setRange(0, 255);
    m_sliderGreen->setRange(0, 255);
    m_sliderBlue->setRange(0, 255);

    m_sliderRed->setValue(m_color.red());
    m_sliderGreen->setValue(m_color.green());
    m_sliderBlue->setValue(m_color.blue());

    m_boxRed->setRange(0, 255);
    m_boxGreen->setRange(0, 255);
    m_boxBlue->setRange(0, 255);

    m_boxRed->setValue(m_color.red());
    m_boxGreen->setValue(m_color.green());
    m_boxBlue->setValue(m_color.blue());

    m_boxRed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_boxGreen->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_boxBlue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_buttonName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_labelColor->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGridLayout *lay = new QGridLayout();

    if (_orientation == Qt::Horizontal)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_sliderRed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_sliderGreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_sliderBlue->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        lay->addWidget(m_buttonName, 0, 0);
        lay->addWidget(m_labelColor, 1, 0, 2, 1);

        lay->addWidget(new QLabel(tr("R:")), 0, 1);
        lay->addWidget(m_boxRed, 0, 2);
        lay->addWidget(m_sliderRed, 0, 3);

        lay->addWidget(new QLabel(tr("G:")), 1, 1);
        lay->addWidget(m_boxGreen, 1, 2);
        lay->addWidget(m_sliderGreen, 1, 3);

        lay->addWidget(new QLabel(tr("B:")), 2, 1);
        lay->addWidget(m_boxBlue, 2, 2);
        lay->addWidget(m_sliderBlue, 2, 3);

        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), 3, 0, 1, 4);
    }
    else
    {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        m_sliderRed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        m_sliderGreen->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        m_sliderBlue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay->addWidget(m_buttonName, 0, 0, 1, 3);
        lay->addWidget(m_labelColor, 1, 0, 1, 3);

        lay->addWidget(new QLabel(tr("R:")), 2, 0);
        lay->addWidget(new QLabel(tr("G:")), 2, 1);
        lay->addWidget(new QLabel(tr("B:")), 2, 2);

        lay->addWidget(m_boxRed, 3, 0);
        lay->addWidget(m_boxGreen, 3, 1);
        lay->addWidget(m_boxBlue, 3, 2);

        lay->addWidget(m_sliderRed, 4, 0);
        lay->addWidget(m_sliderGreen, 4, 1);
        lay->addWidget(m_sliderBlue, 4, 2);

        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 3, 4, 1);
    }

    setLayout(lay);

    updateLabColor();

    connect(m_buttonName, &QPushButton::clicked, this, &WidgetColor::fromQColorDialog);
    connectAll();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::WidgetColor::~WidgetColor()
{
    disconnect(m_buttonName, &QPushButton::clicked, this, &WidgetColor::fromQColorDialog);
    disconnectAll();
}

/*!
 * \brief Setup background color on label \a m_labelColor
 */
void Universe1::Widgets::WidgetColor::updateLabColor()
{
    m_labelColor->setStyleSheet("background:" + m_color.name());
}

/*!
 * \brief Connect all color property slots
 */
void Universe1::Widgets::WidgetColor::connectAll()
{
    connect(m_sliderRed, &QSlider::valueChanged, this, &WidgetColor::sliderRedChanged);
    connect(m_sliderGreen, &QSlider::valueChanged, this, &WidgetColor::sliderGreenChanged);
    connect(m_sliderBlue, &QSlider::valueChanged, this, &WidgetColor::sliderBlueChanged);

    connect(m_boxRed, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxRedChanged);
    connect(
        m_boxGreen, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxGreenChanged);
    connect(
        m_boxBlue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxBlueChanged);
}

/*!
 * \brief Disconnect all color property slots
 */
void Universe1::Widgets::WidgetColor::disconnectAll()
{
    disconnect(m_sliderRed, &QSlider::valueChanged, this, &WidgetColor::sliderRedChanged);
    disconnect(m_sliderGreen, &QSlider::valueChanged, this, &WidgetColor::sliderGreenChanged);
    disconnect(m_sliderBlue, &QSlider::valueChanged, this, &WidgetColor::sliderBlueChanged);

    disconnect(
        m_boxRed, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxRedChanged);
    disconnect(
        m_boxGreen, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxGreenChanged);
    disconnect(
        m_boxBlue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxBlueChanged);
}

/*!
 * \brief Setup new color
 * \param _color New color
 */
void Universe1::Widgets::WidgetColor::setColor(QColor _color)
{
    disconnectAll();

    m_color = _color;

    m_sliderRed->setValue(m_color.red());
    m_sliderGreen->setValue(m_color.green());
    m_sliderBlue->setValue(m_color.blue());

    m_boxRed->setValue(m_color.red());
    m_boxGreen->setValue(m_color.green());
    m_boxBlue->setValue(m_color.blue());

    connectAll();

    updateLabColor();
}

/*!
 * \brief Red slider changed handler
 * \param _value New red value
 */
void Universe1::Widgets::WidgetColor::sliderRedChanged(int _value)
{
    disconnect(
        m_boxRed, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxRedChanged);

    m_boxRed->setValue(_value);

    connect(m_boxRed, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxRedChanged);

    m_color.setRed(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Green slider changed handler
 * \param _value New green value
 */
void Universe1::Widgets::WidgetColor::sliderGreenChanged(int _value)
{
    disconnect(
        m_boxGreen, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxGreenChanged);

    m_boxGreen->setValue(_value);

    connect(
        m_boxGreen, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxGreenChanged);

    m_color.setGreen(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Blue slider changed handler
 * \param _value New blue value
 */
void Universe1::Widgets::WidgetColor::sliderBlueChanged(int _value)
{
    disconnect(
        m_boxBlue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxBlueChanged);

    m_boxBlue->setValue(_value);

    connect(
        m_boxBlue, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &WidgetColor::boxBlueChanged);

    m_color.setBlue(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Red box changed handler
 * \param _value New red value
 */
void Universe1::Widgets::WidgetColor::boxRedChanged(int _value)
{
    disconnect(m_sliderRed, &QSlider::valueChanged, this, &WidgetColor::sliderRedChanged);

    m_sliderRed->setValue(_value);

    connect(m_sliderRed, &QSlider::valueChanged, this, &WidgetColor::sliderRedChanged);

    m_color.setRed(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Green box changed handler
 * \param _value New green value
 */
void Universe1::Widgets::WidgetColor::boxGreenChanged(int _value)
{
    disconnect(m_sliderGreen, &QSlider::valueChanged, this, &WidgetColor::sliderGreenChanged);

    m_sliderGreen->setValue(_value);

    connect(m_sliderGreen, &QSlider::valueChanged, this, &WidgetColor::sliderGreenChanged);

    m_color.setGreen(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Blue box changed handler
 * \param _value New blue value
 */
void Universe1::Widgets::WidgetColor::boxBlueChanged(int _value)
{
    disconnect(m_sliderBlue, &QSlider::valueChanged, this, &WidgetColor::sliderBlueChanged);

    m_sliderBlue->setValue(_value);

    connect(m_sliderBlue, &QSlider::valueChanged, this, &WidgetColor::sliderBlueChanged);

    m_color.setBlue(_value);

    updateLabColor();

    emit changed(m_color);
}

/*!
 * \brief Call native Qt color dialog to select color
 */
void Universe1::Widgets::WidgetColor::fromQColorDialog()
{
    const QColor newColor = QColorDialog::getColor(m_color, this, m_buttonName->text());
    if (!newColor.isValid() || newColor == m_color)
        return;

    disconnectAll();

    m_color = newColor;

    m_sliderRed->setValue(m_color.red());
    m_sliderGreen->setValue(m_color.green());
    m_sliderBlue->setValue(m_color.blue());

    m_boxRed->setValue(m_color.red());
    m_boxGreen->setValue(m_color.green());
    m_boxBlue->setValue(m_color.blue());

    connectAll();

    updateLabColor();

    emit changed(m_color);
}
