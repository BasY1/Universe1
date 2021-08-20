/*!
 * \file qt/widgets/gui/guidirectionlight.cpp
 * \author Michal Steller
 * \brief The QT directional light GUI class implementations
 */

#include "guidirectionlight.h"

#include "../horizontallinespacer.h"

/*!
 * \brief Constructor
 * \param _light Initialization light
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiDirectionLight::GuiDirectionLight(const OpenGL::DirectionLight &_light,
                                                              const Qt::Orientation _orientation,
                                                              QObject *_parent)
    : QObject(_parent)
    , m_light(_light)
    , m_lightOnOff(new QCheckBox())
    , m_direction(new GuiVector3D(m_light.direction, 3, _orientation))
    , m_colors(new GuiColorADS(m_light, _orientation))
{
    m_lightOnOff->setChecked(m_light.mode == OpenGL::DirectionLight::LightOn);

    m_direction->setEnabled(m_lightOnOff->isChecked());
    m_colors->setEnabled(m_lightOnOff->isChecked());

    connect(m_lightOnOff, &QCheckBox::toggled, this, &GuiDirectionLight::onOffChanged);
    connect(m_direction, &GuiVector3D::changed, this, &GuiDirectionLight::directionChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiDirectionLight::adsChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiDirectionLight::~GuiDirectionLight()
{
    disconnect(m_lightOnOff, &QCheckBox::toggled, this, &GuiDirectionLight::onOffChanged);
    disconnect(m_direction, &GuiVector3D::changed, this, &GuiDirectionLight::directionChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiDirectionLight::adsChanged);

    delete m_direction;
    delete m_colors;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _addSingleColor Layout object
 */
void Universe1::Widgets::GUI::GuiDirectionLight::layoutRow(QGridLayout *_lay, int &_row, const bool _addSingleColor)
{
    _lay->addWidget(new QLabel(tr("Enabled")), _row, 0, 1, 2);
    _lay->addWidget(m_lightOnOff, _row, 2, 1, 2);
    _row++;

    _lay->addWidget(new HorizontalLineSpacer(), _row++, 0, 1, 4);

    m_colors->layoutRow(_lay, _row, _addSingleColor);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, 0, 1, 4);

    m_direction->layoutRow(tr("Direction"), _lay, _row);
    m_direction->setToolTip(tr("Light direction normal vector"));
}

/*!
 * \brief Setter for light
 * \param _light New light
 */
void Universe1::Widgets::GUI::GuiDirectionLight::setLight(const OpenGL::DirectionLight &_light)
{
    m_light = _light;

    disconnect(m_lightOnOff, &QCheckBox::toggled, this, &GuiDirectionLight::onOffChanged);
    disconnect(m_direction, &GuiVector3D::changed, this, &GuiDirectionLight::directionChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiDirectionLight::adsChanged);

    m_lightOnOff->setChecked(m_light.mode == OpenGL::DirectionLight::LightOn);
    m_colors->setColorsADS(m_light);
    m_direction->setValue(m_light.direction);
    m_direction->setEnabled(m_lightOnOff->isChecked());
    m_colors->setEnabled(m_lightOnOff->isChecked());

    connect(m_lightOnOff, &QCheckBox::toggled, this, &GuiDirectionLight::onOffChanged);
    connect(m_direction, &GuiVector3D::changed, this, &GuiDirectionLight::directionChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiDirectionLight::adsChanged);

    emit changed(m_light);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiDirectionLight::setOrientation(Qt::Orientation _orientation)
{
    m_direction->setOrientation(_orientation);
    m_colors->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiDirectionLight::setEnabled(bool _value)
{
    m_lightOnOff->setEnabled(_value);
    m_direction->setEnabled(m_lightOnOff->isChecked() && _value);
    m_colors->setEnabled(m_lightOnOff->isChecked() && _value);
}

/*!
 * \brief Ambient - diffuse - specular widget changed value
 * \param _value New colors
 */
void Universe1::Widgets::GUI::GuiDirectionLight::adsChanged(const OpenGL::ADSColors &_value)
{
    m_light.ambient = _value.ambient;
    m_light.diffuse = _value.diffuse;
    m_light.specular = _value.specular;
    emit changed(m_light);
}

/*!
 * \brief Direction widget changed value
 * \param _value New direction value
 */
void Universe1::Widgets::GUI::GuiDirectionLight::directionChanged(const QVector3D &_value)
{
    m_light.direction = _value;
    emit changed(m_light);
}

/*!
 * \brief On/off changed value
 * \param _value New enabled value
 */
void Universe1::Widgets::GUI::GuiDirectionLight::onOffChanged(bool _value)
{
    m_light.mode = _value ? OpenGL::DirectionLight::LightOn : OpenGL::DirectionLight::LightOff;
    m_direction->setEnabled(m_lightOnOff->isEnabled() && _value);
    m_colors->setEnabled(m_lightOnOff->isEnabled() && _value);
    emit changed(m_light);
}
