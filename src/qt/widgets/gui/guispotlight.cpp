/*!
 * \file qt/widgets/gui/guispotlight.cpp
 * \author Michal Steller
 * \brief The QT spot light GUI classes implementations
 */

#include "guispotlight.h"

#include "../horizontallinespacer.h"

/*!
 * \brief Constructor
 * \param _index Light index
 * \param _light Initialization light
 * \param _sceneRange Scene range - light position range will be + 50% greater
 * \param _decimals Decimal count (range 0 to 6)
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiSpotLight::GuiSpotLight(const int _index,
                                                    const OpenGL::SpotLight &_light,
                                                    const std::pair<QVector3D, QVector3D> &_sceneRange,
                                                    const int _decimals,
                                                    const Qt::Orientation _orientation,
                                                    QObject *_parent)
    : QObject(_parent)
    , m_index(_index)
    , m_light(_light)
    , m_lightMode(new QComboBox())
    , m_position(new GuiVector3D(m_light.position, _sceneRange, _decimals, _orientation))
    , m_direction(new GuiVector3D(m_light.direction, _orientation))
    , m_cutOffWidgets(new GuiFloat(m_light.cutOffDeg(), 0, 90, 1, _orientation))
    , m_outerCutOffWidgets(new GuiFloat(m_light.outerCutOffDeg(), 0, 90, 1, _orientation))
    , m_constantWidgets(new GuiFloat(m_light.constant, 0, 2, 3, _orientation))
    , m_linearWidgets(new GuiFloat(m_light.linear, 0, 2, 4, _orientation))
    , m_quadraticWidgets(new GuiFloat(m_light.quadratic, 0, 2, 5, _orientation))
    , m_colors(new GuiColorADS(m_light, _orientation))
{
    m_position->setToolTip(tr("Light position"));
    m_constantWidgets->setToolTip(tr("Constant attenuation factor"));
    m_linearWidgets->setToolTip(tr("Linear attenuation factor"));
    m_quadraticWidgets->setToolTip(tr("Quadratic attenuation factor"));

    m_lightMode->addItem(tr("Off"), static_cast<int>(OpenGL::SpotLight::LightOff));
    m_lightMode->addItem(tr("Fixed"), static_cast<int>(OpenGL::SpotLight::LightFixed));
    m_lightMode->addItem(tr("Scalar"), static_cast<int>(OpenGL::SpotLight::LightScalar));
    m_lightMode->addItem(tr("Linear"), static_cast<int>(OpenGL::SpotLight::LightLinear));
    m_lightMode->addItem(tr("Quadratic"), static_cast<int>(OpenGL::SpotLight::LightQuadratic));

    m_lightMode->setCurrentIndex(m_lightMode->findData(static_cast<int>(m_light.mode)));

    m_position->setEnabled(m_light.mode != OpenGL::SpotLight::LightOff);
    m_direction->setEnabled(m_light.mode != OpenGL::SpotLight::LightOff);
    m_cutOffWidgets->setEnabled(m_light.mode != OpenGL::SpotLight::LightOff);
    m_outerCutOffWidgets->setEnabled(m_light.mode != OpenGL::SpotLight::LightOff);
    m_colors->setEnabled(m_light.mode != OpenGL::SpotLight::LightOff);

    m_constantWidgets->setEnabled(m_light.mode == OpenGL::SpotLight::LightScalar ||
                                  m_light.mode == OpenGL::SpotLight::LightLinear ||
                                  m_light.mode == OpenGL::SpotLight::LightQuadratic);

    m_linearWidgets->setEnabled(m_light.mode == OpenGL::SpotLight::LightLinear ||
                                m_light.mode == OpenGL::SpotLight::LightQuadratic);

    m_quadraticWidgets->setEnabled(m_light.mode == OpenGL::SpotLight::LightQuadratic);

    connectAll();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiSpotLight::~GuiSpotLight()
{
    disconnectAll();

    delete m_position;
    delete m_direction;
    delete m_cutOffWidgets;
    delete m_outerCutOffWidgets;
    delete m_constantWidgets;
    delete m_linearWidgets;
    delete m_quadraticWidgets;
    delete m_colors;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _addSingleColor Layout object
 * \param _startCol Starting column index
 */
void Universe1::Widgets::GUI::GuiSpotLight::layoutRow(QGridLayout *_lay,
                                                      int &_row,
                                                      const bool _addSingleColor,
                                                      const int _startCol)
{
    _lay->addWidget(new QLabel(tr("Mode")), _row, _startCol, 1, 2);
    _lay->addWidget(m_lightMode, _row++, _startCol + 2, 1, 2);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);

    m_colors->layoutRow(_lay, _row, _addSingleColor, _startCol);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);

    m_position->layoutRow(tr("Position"), _lay, _row, _startCol);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);

    m_direction->layoutRow(tr("Direction"), _lay, _row, _startCol);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);

    m_cutOffWidgets->layoutRow(tr("Cut-Off"), _lay, _row, _startCol);
    m_outerCutOffWidgets->layoutRow(tr("Outer cut-Off"), _lay, _row, _startCol);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);

    m_constantWidgets->layoutRow(tr("Scalar"), _lay, _row, _startCol);
    m_linearWidgets->layoutRow(tr("Linear"), _lay, _row, _startCol);
    m_quadraticWidgets->layoutRow(tr("Quadratic"), _lay, _row, _startCol);
}

/*!
 * \brief Create widget with this GUI
 * \returns Widget with spot light GUI
 */
QWidget *Universe1::Widgets::GUI::GuiSpotLight::createWidget()
{
    QGridLayout *lay = new QGridLayout();
    int row = 0;
    layoutRow(lay, row, true);
    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);
    QWidget *result = new QWidget();
    result->setLayout(lay);
    return result;
}

/*!
 * \brief Tool function, connect all widgets
 */
void Universe1::Widgets::GUI::GuiSpotLight::connectAll()
{
    connect(m_lightMode,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &GuiSpotLight::modeChanged);

    connect(m_position, &GuiVector3D::changed, this, &GuiSpotLight::positionChanged);
    connect(m_direction, &GuiVector3D::changed, this, &GuiSpotLight::directionChanged);
    connect(m_cutOffWidgets, &GuiFloat::changed, this, &GuiSpotLight::cutOffChanged);
    connect(m_outerCutOffWidgets, &GuiFloat::changed, this, &GuiSpotLight::outerCutOffChanged);
    connect(m_constantWidgets, &GuiFloat::changed, this, &GuiSpotLight::constantChanged);
    connect(m_linearWidgets, &GuiFloat::changed, this, &GuiSpotLight::linearChanged);
    connect(m_quadraticWidgets, &GuiFloat::changed, this, &GuiSpotLight::quadraticChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiSpotLight::adsChanged);
}

/*!
 * \brief Tool function, disconnect all widgets
 */
void Universe1::Widgets::GUI::GuiSpotLight::disconnectAll()
{
    disconnect(m_lightMode,
               static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this,
               &GuiSpotLight::modeChanged);

    disconnect(m_position, &GuiVector3D::changed, this, &GuiSpotLight::positionChanged);
    disconnect(m_direction, &GuiVector3D::changed, this, &GuiSpotLight::directionChanged);
    disconnect(m_cutOffWidgets, &GuiFloat::changed, this, &GuiSpotLight::cutOffChanged);
    disconnect(m_outerCutOffWidgets, &GuiFloat::changed, this, &GuiSpotLight::outerCutOffChanged);
    disconnect(m_constantWidgets, &GuiFloat::changed, this, &GuiSpotLight::constantChanged);
    disconnect(m_linearWidgets, &GuiFloat::changed, this, &GuiSpotLight::linearChanged);
    disconnect(m_quadraticWidgets, &GuiFloat::changed, this, &GuiSpotLight::quadraticChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiSpotLight::adsChanged);
}

/*!
 * \brief Setter for light
 * \param _light New light
 */
void Universe1::Widgets::GUI::GuiSpotLight::setLight(const OpenGL::SpotLight &_light)
{
    m_light = _light;
    disconnectAll();

    m_lightMode->setCurrentIndex(m_lightMode->findData(static_cast<int>(m_light.mode)));

    m_position->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_direction->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_cutOffWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_outerCutOffWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);

    m_colors->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);

    m_constantWidgets->setEnabled(m_lightMode->isEnabled() &&
                                  (m_light.mode == OpenGL::SpotLight::LightScalar ||
                                   m_light.mode == OpenGL::SpotLight::LightLinear ||
                                   m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        m_lightMode->isEnabled() &&
        (m_light.mode == OpenGL::SpotLight::LightLinear || m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode == OpenGL::SpotLight::LightQuadratic);

    m_position->setValue(m_light.position);
    m_direction->setValue(m_light.direction);
    m_cutOffWidgets->setValue(m_light.cutOffDeg());
    m_outerCutOffWidgets->setValue(m_light.outerCutOffDeg());
    m_direction->setValue(m_light.direction);
    m_constantWidgets->setValue(m_light.constant);
    m_linearWidgets->setValue(m_light.linear);
    m_quadraticWidgets->setValue(m_light.quadratic);
    m_colors->setColorsADS(m_light);

    connectAll();

    emit changed(m_index, m_light);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiSpotLight::setOrientation(Qt::Orientation _orientation)
{
    m_position->setOrientation(_orientation);
    m_direction->setOrientation(_orientation);
    m_cutOffWidgets->setOrientation(_orientation);
    m_outerCutOffWidgets->setOrientation(_orientation);
    m_constantWidgets->setOrientation(_orientation);
    m_linearWidgets->setOrientation(_orientation);
    m_quadraticWidgets->setOrientation(_orientation);
    m_colors->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiSpotLight::setEnabled(bool _value)
{
    m_lightMode->setEnabled(_value);

    m_position->setEnabled(_value && m_light.mode != OpenGL::SpotLight::LightOff);
    m_direction->setEnabled(_value && m_light.mode != OpenGL::SpotLight::LightOff);
    m_cutOffWidgets->setEnabled(_value && m_light.mode != OpenGL::SpotLight::LightOff);
    m_outerCutOffWidgets->setEnabled(_value && m_light.mode != OpenGL::SpotLight::LightOff);
    m_colors->setEnabled(_value && m_light.mode != OpenGL::SpotLight::LightOff);

    m_constantWidgets->setEnabled(_value &&
                                  (m_light.mode == OpenGL::SpotLight::LightScalar ||
                                   m_light.mode == OpenGL::SpotLight::LightLinear ||
                                   m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        _value &&
        (m_light.mode == OpenGL::SpotLight::LightLinear || m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(_value && m_light.mode == OpenGL::SpotLight::LightQuadratic);
}

/*!
 * \brief Light mode changed handler
 * \param _idx New mode index
 */
void Universe1::Widgets::GUI::GuiSpotLight::modeChanged(int _idx)
{
    m_light.mode = static_cast<OpenGL::SpotLight::Mode>(m_lightMode->itemData(_idx).toInt());

    m_position->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_direction->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_cutOffWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_outerCutOffWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);
    m_colors->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::SpotLight::LightOff);

    m_constantWidgets->setEnabled(m_lightMode->isEnabled() &&
                                  (m_light.mode == OpenGL::SpotLight::LightScalar ||
                                   m_light.mode == OpenGL::SpotLight::LightLinear ||
                                   m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        m_lightMode->isEnabled() &&
        (m_light.mode == OpenGL::SpotLight::LightLinear || m_light.mode == OpenGL::SpotLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode == OpenGL::SpotLight::LightQuadratic);

    emit changed(m_index, m_light);
}

/*!
 * \brief Position widget changed value
 * \param _value New position value
 */
void Universe1::Widgets::GUI::GuiSpotLight::positionChanged(const QVector3D &_value)
{
    m_light.position = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Direction widget changed value
 * \param _value New direction value
 */
void Universe1::Widgets::GUI::GuiSpotLight::directionChanged(const QVector3D &_value)
{
    m_light.direction = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Cut-off widget changed value (degrees)
 * \param _value New cut-off value
 */
void Universe1::Widgets::GUI::GuiSpotLight::cutOffChanged(float _value)
{
    m_light.cutOffRad = qDegreesToRadians(_value);
    emit changed(m_index, m_light);
}

/*!
 * \brief Outer cut-off widget changed value (degrees)
 * \param _value New outer cut-off value
 */
void Universe1::Widgets::GUI::GuiSpotLight::outerCutOffChanged(float _value)
{
    m_light.outerCutOffRad = qDegreesToRadians(_value);
    emit changed(m_index, m_light);
}

/*!
 * \brief Constant attenuation factor widget changed value
 * \param _value New constant attenuation factor value
 */
void Universe1::Widgets::GUI::GuiSpotLight::constantChanged(float _value)
{
    m_light.constant = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Linear attenuation factor widget changed value
 * \param _value New linear attenuation factor value
 */
void Universe1::Widgets::GUI::GuiSpotLight::linearChanged(float _value)
{
    m_light.linear = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Quadratic attenuation factor widget changed value
 * \param _value New quadratic attenuation factor value
 */
void Universe1::Widgets::GUI::GuiSpotLight::quadraticChanged(float _value)
{
    m_light.quadratic = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Ambient - diffuse - specular widget changed value
 * \param _value New colors
 */
void Universe1::Widgets::GUI::GuiSpotLight::adsChanged(const OpenGL::ADSColors &_value)
{
    m_light.ambient = _value.ambient;
    m_light.diffuse = _value.diffuse;
    m_light.specular = _value.specular;
    emit changed(m_index, m_light);
}


