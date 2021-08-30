/*!
 * \file qt/widgets/gui/guipointlight.cpp
 * \author Michal Steller
 * \brief The QT point light GUI classes implementations
 */

#include "guipointlight.h"

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
Universe1::Widgets::GUI::GuiPointLight::GuiPointLight(const int _index,
                                                      const OpenGL::PointLight &_light,
                                                      const std::pair<QVector3D, QVector3D> &_sceneRange,
                                                      const int _decimals,
                                                      const Qt::Orientation _orientation,
                                                      QObject *_parent)
    : QObject(_parent)
    , m_index(_index)
    , m_light(_light)
    , m_lightMode(new QComboBox())
    , m_position(new GuiVector3D(m_light.position, _sceneRange, _decimals, _orientation))
    , m_constantWidgets(new GuiFloat(m_light.constant, 0, 2, 3, _orientation))
    , m_linearWidgets(new GuiFloat(m_light.linear, 0, 2, 4, _orientation))
    , m_quadraticWidgets(new GuiFloat(m_light.quadratic, 0, 2, 5, _orientation))
    , m_colors(new GuiColorADS(m_light, _orientation))
{
    m_position->setToolTip(tr("Light position"));
    m_constantWidgets->setToolTip(tr("Constant attenuation factor"));
    m_linearWidgets->setToolTip(tr("Linear attenuation factor"));
    m_quadraticWidgets->setToolTip(tr("Quadratic attenuation factor"));

    m_lightMode->addItem(tr("Off"), static_cast<int>(OpenGL::PointLight::LightOff));
    m_lightMode->addItem(tr("Fixed"), static_cast<int>(OpenGL::PointLight::LightFixed));
    m_lightMode->addItem(tr("Scalar"), static_cast<int>(OpenGL::PointLight::LightScalar));
    m_lightMode->addItem(tr("Linear"), static_cast<int>(OpenGL::PointLight::LightLinear));
    m_lightMode->addItem(tr("Quadratic"), static_cast<int>(OpenGL::PointLight::LightQuadratic));

    m_lightMode->setCurrentIndex(m_lightMode->findData(static_cast<int>(m_light.mode)));

    m_position->setEnabled(m_light.mode != OpenGL::PointLight::LightOff);
    m_colors->setEnabled(m_light.mode != OpenGL::PointLight::LightOff);

    m_constantWidgets->setEnabled(m_light.mode == OpenGL::PointLight::LightScalar ||
                                  m_light.mode == OpenGL::PointLight::LightLinear ||
                                  m_light.mode == OpenGL::PointLight::LightQuadratic);

    m_linearWidgets->setEnabled(m_light.mode == OpenGL::PointLight::LightLinear ||
                                m_light.mode == OpenGL::PointLight::LightQuadratic);

    m_quadraticWidgets->setEnabled(m_light.mode == OpenGL::PointLight::LightQuadratic);

    connectAll();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiPointLight::~GuiPointLight()
{
    disconnectAll();

    delete m_position;
    delete m_colors;
    delete m_constantWidgets;
    delete m_linearWidgets;
    delete m_quadraticWidgets;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _addSingleColor Layout object
 */
void Universe1::Widgets::GUI::GuiPointLight::layoutRow(QGridLayout *_lay, int &_row, const bool _addSingleColor)
{
    _lay->addWidget(new QLabel(tr("Mode")), _row, 0, 1, 2);
    _lay->addWidget(m_lightMode, _row++, 2, 1, 2);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, 0, 1, 4);

    m_colors->layoutRow(_lay, _row, _addSingleColor);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, 0, 1, 4);

    m_position->layoutRow(tr("Position"), _lay, _row);

    _lay->addWidget(new HorizontalLineSpacer(), _row++, 0, 1, 4);

    m_constantWidgets->layoutRow(tr("Scalar"), _lay, _row);
    m_linearWidgets->layoutRow(tr("Linear"), _lay, _row);
    m_quadraticWidgets->layoutRow(tr("Quadratic"), _lay, _row);
}

/*!
 * \brief Create widget with this GUI
 * \return Widget with point light GUI
 */
QWidget *Universe1::Widgets::GUI::GuiPointLight::createWidget()
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
void Universe1::Widgets::GUI::GuiPointLight::connectAll()
{
    connect(m_lightMode,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &GuiPointLight::modeChanged);

    connect(m_position, &GuiVector3D::changed, this, &GuiPointLight::positionChanged);
    connect(m_constantWidgets, &GuiFloat::changed, this, &GuiPointLight::constantChanged);
    connect(m_linearWidgets, &GuiFloat::changed, this, &GuiPointLight::linearChanged);
    connect(m_quadraticWidgets, &GuiFloat::changed, this, &GuiPointLight::quadraticChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiPointLight::adsChanged);
}

/*!
 * \brief Tool function, disconnect all widgets
 */
void Universe1::Widgets::GUI::GuiPointLight::disconnectAll()
{
    disconnect(m_lightMode,
               static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this,
               &GuiPointLight::modeChanged);

    disconnect(m_position, &GuiVector3D::changed, this, &GuiPointLight::positionChanged);
    disconnect(m_constantWidgets, &GuiFloat::changed, this, &GuiPointLight::constantChanged);
    disconnect(m_linearWidgets, &GuiFloat::changed, this, &GuiPointLight::linearChanged);
    disconnect(m_quadraticWidgets, &GuiFloat::changed, this, &GuiPointLight::quadraticChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiPointLight::adsChanged);
}

/*!
 * \brief Setter for light
 * \param _light New light
 */
void Universe1::Widgets::GUI::GuiPointLight::setLight(const OpenGL::PointLight &_light)
{
    m_light = _light;
    disconnectAll();

    m_lightMode->setCurrentIndex(m_lightMode->findData(static_cast<int>(m_light.mode)));

    m_position->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::PointLight::LightOff);
    m_colors->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::PointLight::LightOff);

    m_constantWidgets->setEnabled(m_lightMode->isEnabled() &&
                                  (m_light.mode == OpenGL::PointLight::LightScalar ||
                                   m_light.mode == OpenGL::PointLight::LightLinear ||
                                   m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        m_lightMode->isEnabled() &&
        (m_light.mode == OpenGL::PointLight::LightLinear || m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode == OpenGL::PointLight::LightQuadratic);

    m_position->setValue(m_light.position);
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
void Universe1::Widgets::GUI::GuiPointLight::setOrientation(Qt::Orientation _orientation)
{
    m_position->setOrientation(_orientation);
    m_constantWidgets->setOrientation(_orientation);
    m_linearWidgets->setOrientation(_orientation);
    m_quadraticWidgets->setOrientation(_orientation);
    m_colors->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiPointLight::setEnabled(bool _value)
{
    m_lightMode->setEnabled(_value);

    m_position->setEnabled(_value && m_light.mode != OpenGL::PointLight::LightOff);
    m_colors->setEnabled(_value && m_light.mode != OpenGL::PointLight::LightOff);

    m_constantWidgets->setEnabled(_value &&
                                  (m_light.mode == OpenGL::PointLight::LightScalar ||
                                   m_light.mode == OpenGL::PointLight::LightLinear ||
                                   m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        _value &&
        (m_light.mode == OpenGL::PointLight::LightLinear || m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(_value && m_light.mode == OpenGL::PointLight::LightQuadratic);
}

/*!
 * \brief Light mode changed handler
 * \param _idx New mode index
 */
void Universe1::Widgets::GUI::GuiPointLight::modeChanged(int _idx)
{
    m_light.mode = static_cast<OpenGL::PointLight::Mode>(m_lightMode->itemData(_idx).toInt());

    m_position->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::PointLight::LightOff);
    m_colors->setEnabled(m_lightMode->isEnabled() && m_light.mode != OpenGL::PointLight::LightOff);

    m_constantWidgets->setEnabled(m_lightMode->isEnabled() &&
                                  (m_light.mode == OpenGL::PointLight::LightScalar ||
                                   m_light.mode == OpenGL::PointLight::LightLinear ||
                                   m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_linearWidgets->setEnabled(
        m_lightMode->isEnabled() &&
        (m_light.mode == OpenGL::PointLight::LightLinear || m_light.mode == OpenGL::PointLight::LightQuadratic));

    m_quadraticWidgets->setEnabled(m_lightMode->isEnabled() && m_light.mode == OpenGL::PointLight::LightQuadratic);

    emit changed(m_index, m_light);
}

/*!
 * \brief Position widget changed value
 * \param _value New position value
 */
void Universe1::Widgets::GUI::GuiPointLight::positionChanged(const QVector3D &_value)
{
    m_light.position = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Constant attenuation factor widget changed value
 * \param _value New constant attenuation factor value
 */
void Universe1::Widgets::GUI::GuiPointLight::constantChanged(float _value)
{
    m_light.constant = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Linear attenuation factor widget changed value
 * \param _value New linear attenuation factor value
 */
void Universe1::Widgets::GUI::GuiPointLight::linearChanged(float _value)
{
    m_light.linear = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Quadratic attenuation factor widget changed value
 * \param _value New quadratic attenuation factor value
 */
void Universe1::Widgets::GUI::GuiPointLight::quadraticChanged(float _value)
{
    m_light.quadratic = _value;
    emit changed(m_index, m_light);
}

/*!
 * \brief Ambient - diffuse - specular widget changed value
 * \param _value New colors
 */
void Universe1::Widgets::GUI::GuiPointLight::adsChanged(const OpenGL::ADSColors &_value)
{
    m_light.ambient = _value.ambient;
    m_light.diffuse = _value.diffuse;
    m_light.specular = _value.specular;
    emit changed(m_index, m_light);
}


