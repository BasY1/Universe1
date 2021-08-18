/*!
 * \file qt/widgets/gui/guicolorads.cpp
 * \author Michal Steller
 * \brief The QT color ambient - diffuse - specular GUI class implementations
 */

#include "guicolorads.h"

/*!
 * \brief Constructor
 * \param _colors Initialization colors
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiColorADS::GuiColorADS(const OpenGL::ADSColors &_colors,
                                                  const Qt::Orientation _orientation,
                                                  QObject *_parent)
    : QObject(_parent)
    , m_colors(_colors)
    , m_singleColor(new QCheckBox())
    , m_ambient(new GuiColor(m_colors.ambient, _orientation, this))
    , m_diffuse(new GuiColor(m_colors.diffuse, _orientation, this))
    , m_specular(new GuiColor(m_colors.specular, _orientation, this))
{
    connect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
    connect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
    connect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiColorADS::~GuiColorADS()
{
    disconnect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
    disconnect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
    disconnect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);
}

/*!
 * \brief Setter for ambient color
 * \param _color New ambient color value
 */
void Universe1::Widgets::GUI::GuiColorADS::setColorAmbient(QColor _color)
{
    setColors(_color, m_colors.diffuse, m_colors.specular);
}

/*!
 * \brief Setter for diffuse color
 * \param _color New diffuse color value
 */
void Universe1::Widgets::GUI::GuiColorADS::setColorDiffuse(QColor _color)
{
    setColors(m_colors.ambient, _color, m_colors.specular);
}

/*!
 * \brief Setter for specular color
 * \param _color New specular color value
 */
void Universe1::Widgets::GUI::GuiColorADS::setColorSpecular(QColor _color)
{
    setColors(m_colors.ambient, m_colors.diffuse, _color);
}

/*!
 * \brief Setter for colors
 * \param _colors New color values
 */
void Universe1::Widgets::GUI::GuiColorADS::setColorsADS(const OpenGL::ADSColors &_colors)
{
    setColors(_colors.ambient, _colors.diffuse, _colors.specular);
}

/*!
 * \brief Setter for colors
 * \param _colorAmbient New ambient color
 * \param _colorDiffuse New diffuse color
 * \param _colorSpecular New specular color
 */
void Universe1::Widgets::GUI::GuiColorADS::setColors(const QColor _colorAmbient,
                                                     const QColor _colorDiffuse,
                                                     const QColor _colorSpecular)
{
    m_colors.ambient = _colorAmbient;
    m_colors.diffuse = _colorDiffuse;
    m_colors.specular = _colorSpecular;

    disconnect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
    disconnect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
    disconnect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

    m_ambient->setColor(m_colors.ambient);
    m_diffuse->setColor(m_colors.diffuse);
    m_specular->setColor(m_colors.specular);

    connect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
    connect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
    connect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

    emit changed(m_colors);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiColorADS::setOrientation(Qt::Orientation _orientation)
{
    m_ambient->setOrientation(_orientation);
    m_diffuse->setOrientation(_orientation);
    m_specular->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiColorADS::setEnabled(bool _value)
{
    m_ambient->setEnabled(_value);
    m_diffuse->setEnabled(_value);
    m_specular->setEnabled(_value);
}

/*!
 * \brief Single color flag changed
 * \param _value New single color flag value
 */
void Universe1::Widgets::GUI::GuiColorADS::singleColorChanged(bool _value)
{
    if (_value)
    {
        disconnect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
        disconnect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

        m_colors.diffuse = m_colors.ambient;
        m_colors.specular = m_colors.ambient;
        m_diffuse->setColor(m_colors.diffuse);
        m_specular->setColor(m_colors.specular);

        connect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
        connect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

        emit changed(m_colors);
    }
}

/*!
 * \brief Ambient widget changed value
 * \param _value New ambient color
 */
void Universe1::Widgets::GUI::GuiColorADS::ambientChanged(QColor _value)
{
    m_colors.ambient = _value;
    if (m_singleColor->isChecked())
    {
        m_colors.diffuse = _value;
        m_colors.specular = _value;

        disconnect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
        disconnect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

        m_diffuse->setColor(m_colors.diffuse);
        m_specular->setColor(m_colors.specular);

        connect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
        connect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);
    }
    emit changed(m_colors);
}

/*!
 * \brief Diffuse widget changed value
 * \param _value New diffuse color
 */
void Universe1::Widgets::GUI::GuiColorADS::diffuseChanged(QColor _value)
{
    m_colors.diffuse = _value;
    if (m_singleColor->isChecked())
    {
        m_colors.ambient = _value;
        m_colors.specular = _value;

        disconnect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
        disconnect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);

        m_ambient->setColor(m_colors.ambient);
        m_specular->setColor(m_colors.specular);

        connect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
        connect(m_specular, &GuiColor::changed, this, &GuiColorADS::specularChanged);
    }
    emit changed(m_colors);
}

/*!
 * \brief Specular widget changed value
 * \param _value New specular color
 */
void Universe1::Widgets::GUI::GuiColorADS::specularChanged(QColor _value)
{
    m_colors.specular = _value;
    if (m_singleColor->isChecked())
    {
        m_colors.ambient = _value;
        m_colors.diffuse = _value;

        disconnect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
        disconnect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);

        m_ambient->setColor(m_colors.ambient);
        m_diffuse->setColor(m_colors.diffuse);

        connect(m_ambient, &GuiColor::changed, this, &GuiColorADS::ambientChanged);
        connect(m_diffuse, &GuiColor::changed, this, &GuiColorADS::diffuseChanged);
    }
    emit changed(m_colors);
}
