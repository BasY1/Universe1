/*!
 * \file qt/widgets/gui/guimaterial.cpp
 * \author Michal Steller
 * \brief The QT material GUI class implementations
 */

#include "guimaterial.h"

#include "../horizontallinespacer.h"

/*!
 * \brief Constructor
 * \param _material Initialization material
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 */
Universe1::Widgets::GUI::GuiMaterial::GuiMaterial(const OpenGL::Material &_material,
                                                  const Qt::Orientation _orientation,
                                                  QObject *_parent)
    : QObject(_parent)
    , m_material(_material)
    , m_alpha(new GuiFloat(m_material.alpha, 0, 1, 3, _orientation))
    , m_shininess(new GuiFloat(m_material.shininess, 0, 100, 1, _orientation))
    , m_colors(new GuiColorADS(m_material, _orientation))
{
    connect(m_alpha, &GuiFloat::changed, this, &GuiMaterial::alphaChanged);
    connect(m_shininess, &GuiFloat::changed, this, &GuiMaterial::shininessChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiMaterial::adsChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::GUI::GuiMaterial::~GuiMaterial()
{
    disconnect(m_alpha, &GuiFloat::changed, this, &GuiMaterial::alphaChanged);
    disconnect(m_shininess, &GuiFloat::changed, this, &GuiMaterial::shininessChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiMaterial::adsChanged);

    delete m_shininess;
    delete m_colors;
}

/*!
 * \brief Fill new layout row with widgets
 * \param _lay Layout object
 * \param _row Current row within layout
 * \param _addSingleColor Layout object
 * \param _startCol Starting column index
 */
void Universe1::Widgets::GUI::GuiMaterial::layoutRow(QGridLayout *_lay,
                                                     int &_row,
                                                     const bool _addSingleColor,
                                                     const int _startCol)
{
    m_colors->layoutRow(_lay, _row, _addSingleColor, _startCol);
    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);
    m_shininess->layoutRow(tr("Shininess"), _lay, _row, _startCol);
    _lay->addWidget(new HorizontalLineSpacer(), _row++, _startCol, 1, 4);
    m_alpha->layoutRow(tr("Color alpha"), _lay, _row, _startCol);
}

/*!
 * \brief Setter for material
 * \param _material New material
 */
void Universe1::Widgets::GUI::GuiMaterial::setMaterial(const OpenGL::Material &_material)
{
    m_material = _material;

    disconnect(m_alpha, &GuiFloat::changed, this, &GuiMaterial::alphaChanged);
    disconnect(m_shininess, &GuiFloat::changed, this, &GuiMaterial::shininessChanged);
    disconnect(m_colors, &GuiColorADS::changed, this, &GuiMaterial::adsChanged);

    m_colors->setColorsADS(m_material);
    m_shininess->setValue(m_material.shininess);
    m_alpha->setValue(m_material.alpha);

    connect(m_alpha, &GuiFloat::changed, this, &GuiMaterial::alphaChanged);
    connect(m_shininess, &GuiFloat::changed, this, &GuiMaterial::shininessChanged);
    connect(m_colors, &GuiColorADS::changed, this, &GuiMaterial::adsChanged);

    emit changed(m_material);
}

/*!
 * \brief Setup new orientation
 * \param _orientation New orientation
 */
void Universe1::Widgets::GUI::GuiMaterial::setOrientation(Qt::Orientation _orientation)
{
    m_alpha->setOrientation(_orientation);
    m_shininess->setOrientation(_orientation);
    m_colors->setOrientation(_orientation);
}

/*!
 * \brief Setup widget enabled
 * \param _value Enabled value
 */
void Universe1::Widgets::GUI::GuiMaterial::setEnabled(bool _value)
{
    m_alpha->setEnabled(_value);
    m_shininess->setEnabled(_value);
    m_colors->setEnabled(_value);
}

/*!
 * \brief Ambient - diffuse - specular widget changed value
 * \param _value New colors
 */
void Universe1::Widgets::GUI::GuiMaterial::adsChanged(const OpenGL::ADSColors &_value)
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
void Universe1::Widgets::GUI::GuiMaterial::shininessChanged(float _value)
{
    m_material.shininess = _value;
    emit changed(m_material);
}

/*!
 * \brief Alpha widget changed value
 * \param _value New alpha value
 */
void Universe1::Widgets::GUI::GuiMaterial::alphaChanged(float _value)
{
    m_material.alpha = _value;
    emit changed(m_material);
}
