/*!
 * \file qt/widgets/widgetmaterial.cpp
 * \author Michal Steller
 * \brief The QT material widget class implementations
 */

#include "widgetmaterial.h"

#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _material Initialization material
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetMaterial::WidgetMaterial(const OpenGL::Material &_material,
                                                   const Qt::Orientation _orientation,
                                                   QWidget *_parent)
    : QWidget(_parent)
    , m_material(_material)
    , m_shininess(new WidgetFloat(m_material.shininess, 0, 1, 3, tr("shininess"), _orientation))
    , m_colors(new WidgetColorADS(m_material, _orientation))
{
    QGridLayout *lay = new QGridLayout();
    int tmp = 0;
    if (_orientation == Qt::Horizontal)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        lay->addWidget(m_shininess, tmp++, 0);
        lay->addWidget(m_colors, tmp++, 0);
        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding), tmp++, 0);
    }
    else
    {
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        lay->addWidget(m_shininess, 0, tmp++);
        lay->addWidget(m_colors, 0, tmp++);
        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, tmp++);
    }

    setLayout(lay);

    connect(m_colors, &WidgetColorADS::changed, this, &WidgetMaterial::adsChanged);
    connect(m_shininess, &WidgetFloat::changed, this, &WidgetMaterial::shininessChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::WidgetMaterial::~WidgetMaterial()
{
    disconnect(m_colors, &WidgetColorADS::changed, this, &WidgetMaterial::adsChanged);
    disconnect(m_shininess, &WidgetFloat::changed, this, &WidgetMaterial::shininessChanged);
}

/*!
 * \brief Setter for material
 * \param _material New material
 */
void Universe1::Widgets::WidgetMaterial::setMaterial(const OpenGL::Material &_material)
{
    m_material = _material;

    disconnect(m_colors, &WidgetColorADS::changed, this, &WidgetMaterial::adsChanged);
    disconnect(m_shininess, &WidgetFloat::changed, this, &WidgetMaterial::shininessChanged);

    m_colors->setColorsADS(m_material);
    m_shininess->setValue(m_material.shininess);

    connect(m_colors, &WidgetColorADS::changed, this, &WidgetMaterial::adsChanged);
    connect(m_shininess, &WidgetFloat::changed, this, &WidgetMaterial::shininessChanged);
}

/*!
 * \brief Ambient - diffuse - specular widget changed value
 * \param _value New colors
 */
void Universe1::Widgets::WidgetMaterial::adsChanged(const OpenGL::ADSColors &_value)
{
    m_material.ambient = _value.ambient;
    m_material.diffuse = _value.diffuse;
    m_material.specular = _value.specular;
    emit changed(m_material);
}

/*!
 * \brief Shininess widget changed value
 * \param _value New shininess value
 */
void Universe1::Widgets::WidgetMaterial::shininessChanged(float _value)
{
    m_material.shininess = _value;
    emit changed(m_material);
}
