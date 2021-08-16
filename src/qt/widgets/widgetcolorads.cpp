/*!
 * \file qt/widgets/widgetcolorads.cpp
 * \author Michal Steller
 * \brief The QT color ambient - diffuse - specular widget class implementations
 */

#include "widgetcolorads.h"

#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _colors Initialization colors
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetColorADS::WidgetColorADS(const OpenGL::ADSColors &_colors,
                                                   const Qt::Orientation _orientation,
                                                   QWidget *_parent)
    : QWidget(_parent)
    , m_colors(_colors)
    , m_ambient(new WidgetColor(m_colors.ambient, tr("Ambient"), _orientation))
    , m_diffuse(new WidgetColor(m_colors.diffuse, tr("Diffuse"), _orientation))
    , m_specular(new WidgetColor(m_colors.specular, tr("Specular"), _orientation))
{
    QGridLayout *lay = new QGridLayout();
    int tmp = 0;
    if (_orientation == Qt::Horizontal)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        lay->addWidget(m_ambient, tmp++, 0);
        lay->addWidget(m_diffuse, tmp++, 0);
        lay->addWidget(m_specular, tmp++, 0);
        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), tmp++, 0);
    }
    else
    {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        lay->addWidget(m_ambient, 0, tmp++);
        lay->addWidget(m_diffuse, 0, tmp++);
        lay->addWidget(m_specular, 0, tmp++);
        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, tmp++);
    }

    setLayout(lay);

    connect(m_ambient, &WidgetColor::changed, this, &WidgetColorADS::ambientChanged);
    connect(m_diffuse, &WidgetColor::changed, this, &WidgetColorADS::diffuseChanged);
    connect(m_specular, &WidgetColor::changed, this, &WidgetColorADS::specularChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::WidgetColorADS::~WidgetColorADS()
{
    disconnect(m_ambient, &WidgetColor::changed, this, &WidgetColorADS::ambientChanged);
    disconnect(m_diffuse, &WidgetColor::changed, this, &WidgetColorADS::diffuseChanged);
    disconnect(m_specular, &WidgetColor::changed, this, &WidgetColorADS::specularChanged);
}

/*!
 * \brief Setter for ambient color
 * \param _color New ambient color value
 */
void Universe1::Widgets::WidgetColorADS::setColorAmbient(QColor _color)
{
    setColors(_color, m_colors.diffuse, m_colors.specular);
}

/*!
 * \brief Setter for diffuse color
 * \param _color New diffuse color value
 */
void Universe1::Widgets::WidgetColorADS::setColorDiffuse(QColor _color)
{
    setColors(m_colors.ambient, _color, m_colors.specular);
}

/*!
 * \brief Setter for specular color
 * \param _color New specular color value
 */
void Universe1::Widgets::WidgetColorADS::setColorSpecular(QColor _color)
{
    setColors(m_colors.ambient, m_colors.diffuse, _color);
}

/*!
 * \brief Setter for colors
 * \param _colors New color values
 */
void Universe1::Widgets::WidgetColorADS::setColorsADS(const OpenGL::ADSColors &_colors)
{
    setColors(_colors.ambient, _colors.diffuse, _colors.specular);
}

/*!
 * \brief Setter for colors
 * \param _colorAmbient New ambient color
 * \param _colorDiffuse New diffuse color
 * \param _colorSpecular New specular color
 */
void Universe1::Widgets::WidgetColorADS::setColors(const QColor _colorAmbient,
                                                   const QColor _colorDiffuse,
                                                   const QColor _colorSpecular)
{
    m_colors.ambient = _colorAmbient;
    m_colors.diffuse = _colorDiffuse;
    m_colors.specular = _colorSpecular;

    disconnect(m_ambient, &WidgetColor::changed, this, &WidgetColorADS::ambientChanged);
    disconnect(m_diffuse, &WidgetColor::changed, this, &WidgetColorADS::diffuseChanged);
    disconnect(m_specular, &WidgetColor::changed, this, &WidgetColorADS::specularChanged);

    m_ambient->setColor(m_colors.ambient);
    m_diffuse->setColor(m_colors.diffuse);
    m_specular->setColor(m_colors.specular);

    connect(m_ambient, &WidgetColor::changed, this, &WidgetColorADS::ambientChanged);
    connect(m_diffuse, &WidgetColor::changed, this, &WidgetColorADS::diffuseChanged);
    connect(m_specular, &WidgetColor::changed, this, &WidgetColorADS::specularChanged);
}

/*!
 * \brief Ambient widget changed value
 * \param _value New ambient color
 */
void Universe1::Widgets::WidgetColorADS::ambientChanged(QColor _value)
{
    m_colors.ambient = _value;
    emit changed(m_colors);
}

/*!
 * \brief Diffuse widget changed value
 * \param _value New diffuse color
 */
void Universe1::Widgets::WidgetColorADS::diffuseChanged(QColor _value)
{
    m_colors.diffuse = _value;
    emit changed(m_colors);
}

/*!
 * \brief Specular widget changed value
 * \param _value New specular color
 */
void Universe1::Widgets::WidgetColorADS::specularChanged(QColor _value)
{
    m_colors.specular = _value;
    emit changed(m_colors);
}
