/*!
 * \file qt/widgets/gui/guicolor.cpp
 * \author Michal Steller
 * \brief The QT color GUI class implementations
 */

#include "guicolor.h"

#include <QColorDialog>
#include <QLabel>

/*!
 * \brief Constructor
 * \param _color Color
 * \param _orientation Orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiColor::GuiColor(const QColor _color, const Qt::Orientation _orientation, QObject *_parent)
    : QObject(_parent)
    , m_color(_color)
    , m_red(new GuiInt(m_color.red(), _orientation))
    , m_green(new GuiInt(m_color.green(), _orientation))
    , m_blue(new GuiInt(m_color.blue(), _orientation))
    , m_bgWidget(new WidgetBGColor(m_color))
{
    m_red->setToolTip(tr("Red"));
    m_green->setToolTip(tr("Green"));
    m_blue->setToolTip(tr("Blue"));

    m_red->slider()->setStyleSheet("   QSlider::handle:horizontal { background: red   ; border-radius: 3px; }");
    m_green->slider()->setStyleSheet(" QSlider::handle:horizontal { background: green ; border-radius: 3px; }");
    m_blue->slider()->setStyleSheet("  QSlider::handle:horizontal { background: blue  ; border-radius: 3px; }");
    connect(m_bgWidget, &WidgetBGColor::doubleClicked, this, &GuiColor::fromQColorDialog);
    connectAll();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiColor::~GuiColor()
{
    disconnect(m_bgWidget, &WidgetBGColor::doubleClicked, this, &GuiColor::fromQColorDialog);
    disconnectAll();
    delete m_red;
    delete m_green;
    delete m_blue;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _name Property name
 * \param _lay Layout object
 * \param _row Current row within layout
 */
void Universe1::Widgets::GUI::GuiColor::layoutRow(const QString &_name, QGridLayout *_lay, int &_row)
{
    _lay->addWidget(new QLabel(_name), _row, 0);
    _lay->addWidget(new QLabel("<b>" + tr("R") + "</b>"), _row, 1, Qt::AlignRight);
    _lay->addWidget(m_red->box(), _row, 2);
    _lay->addWidget(m_red->slider(), _row, 3);
    ++_row;

    _lay->addWidget(m_bgWidget, _row, 0, 2, 1);

    _lay->addWidget(new QLabel("<b>" + tr("G") + "</b>"), _row, 1, Qt::AlignRight);
    _lay->addWidget(m_green->box(), _row, 2);
    _lay->addWidget(m_green->slider(), _row, 3);
    ++_row;

    _lay->addWidget(new QLabel("<b>" + tr("B") + "</b>"), _row, 1, Qt::AlignRight);
    _lay->addWidget(m_blue->box(), _row, 2);
    _lay->addWidget(m_blue->slider(), _row, 3);
    ++_row;
}

/*!
 * \brief Connect all color property slots
 */
void Universe1::Widgets::GUI::GuiColor::connectAll()
{
    connect(m_red, &GuiInt::changed, this, &GuiColor::redChanged);
    connect(m_green, &GuiInt::changed, this, &GuiColor::greenChanged);
    connect(m_blue, &GuiInt::changed, this, &GuiColor::blueChanged);
}

/*!
 * \brief Disconnect all color property slots
 */
void Universe1::Widgets::GUI::GuiColor::disconnectAll()
{
    disconnect(m_red, &GuiInt::changed, this, &GuiColor::redChanged);
    disconnect(m_green, &GuiInt::changed, this, &GuiColor::greenChanged);
    disconnect(m_blue, &GuiInt::changed, this, &GuiColor::blueChanged);
}

/*!
 * \brief Setup new color
 * \param _color New color
 */
void Universe1::Widgets::GUI::GuiColor::setColor(QColor _color)
{
    disconnectAll();

    m_color = _color;
    m_bgWidget->setColor(m_color);

    m_red->setValue(m_color.red());
    m_green->setValue(m_color.green());
    m_blue->setValue(m_color.blue());

    connectAll();

    emit changed(m_color);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiColor::setOrientation(Qt::Orientation _orientation)
{
    m_red->setOrientation(_orientation);
    m_green->setOrientation(_orientation);
    m_blue->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiColor::setEnabled(bool _value)
{
    m_red->setEnabled(_value);
    m_green->setEnabled(_value);
    m_blue->setEnabled(_value);
}

/*!
 * \brief Setup widgets tool-tip
 * \param _toolTip Tool tip text
 */
void Universe1::Widgets::GUI::GuiColor::setToolTip(QString _toolTip)
{
    m_red->setToolTip(_toolTip + " - " + tr("Red"));
    m_green->setToolTip(_toolTip + " - " + tr("Green"));
    m_blue->setToolTip(_toolTip + " - " + tr("Blue"));
}

/*!
 * \brief Red changed handler
 * \param _value New red value
 */
void Universe1::Widgets::GUI::GuiColor::redChanged(int _value)
{
    m_color.setRed(_value);
    m_bgWidget->setColor(m_color);
    emit changed(m_color);
}

/*!
 * \brief Green changed handler
 * \param _value New green value
 */
void Universe1::Widgets::GUI::GuiColor::greenChanged(int _value)
{
    m_color.setGreen(_value);
    m_bgWidget->setColor(m_color);
    emit changed(m_color);
}

/*!
 * \brief Blue changed handler
 * \param _value New blue value
 */
void Universe1::Widgets::GUI::GuiColor::blueChanged(int _value)
{
    m_color.setBlue(_value);
    m_bgWidget->setColor(m_color);
    emit changed(m_color);
}

/*!
 * \brief Call native Qt color dialog to select color
 */
void Universe1::Widgets::GUI::GuiColor::fromQColorDialog()
{
    const QColor newColor = QColorDialog::getColor(m_color, m_bgWidget);
    if (!newColor.isValid() || newColor == m_color)
        return;

    disconnectAll();

    m_color = newColor;
    m_bgWidget->setColor(m_color);

    m_red->setValue(m_color.red());
    m_green->setValue(m_color.green());
    m_blue->setValue(m_color.blue());

    connectAll();

    emit changed(m_color);
}
