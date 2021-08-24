/*!
 * \file qt/opengl/models/modelpointlight.cpp
 * \author Michal Steller
 * \brief Open GL point light model with material class implementation
 */

#include "modelpointlight.h"
#include <cmath>

/*!
 * \brief Constructor
 * \param _light Point light data
 * \param _radius Point light radius
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelPointLight::ModelPointLight(const PointLight &_light,
                                                            const float _radius,
                                                            QObject *_parent)
    : LinesModel({Material(_light.ambient, _light.ambient, _light.ambient),
                  Material(_light.diffuse, _light.diffuse, _light.diffuse),
                  Material(_light.specular, _light.specular, _light.specular)},
                 _parent)
    , m_position(_light.position)
    , m_radius(_radius)
{
    m_enabled = _light.mode != PointLight::LightOff;

    GLModel::m_materials.at(0).mode = Material::MaterialAmbient;
    GLModel::m_materials.at(1).mode = Material::MaterialAmbient;
    GLModel::m_materials.at(2).mode = Material::MaterialAmbient;
}

/*!
 * \brief Setter for point light values
 * \param _light New point light values
 */
void Universe1::OpenGL::Models::ModelPointLight::setPointLight(const PointLight &_light)
{
    const bool needRebuild = !qFuzzyCompare(m_position, _light.position);

    m_enabled = _light.mode != PointLight::LightOff;
    m_position = _light.position;

    GLModel::m_materials.at(0).ambient = _light.ambient;
    GLModel::m_materials.at(0).diffuse = _light.ambient;
    GLModel::m_materials.at(0).specular = _light.ambient;

    GLModel::m_materials.at(1).ambient = _light.diffuse;
    GLModel::m_materials.at(1).diffuse = _light.diffuse;
    GLModel::m_materials.at(1).specular = _light.diffuse;

    GLModel::m_materials.at(2).ambient = _light.specular;
    GLModel::m_materials.at(2).diffuse = _light.specular;
    GLModel::m_materials.at(2).specular = _light.specular;

    if (isInit() && needRebuild)
        rebuild();

    emit changed();
}

/*!
 * \brief Setter for point light position
 * \param _value New point light position
 */
void Universe1::OpenGL::Models::ModelPointLight::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for point light radius
 * \param _value New point light radius
 */
void Universe1::OpenGL::Models::ModelPointLight::setRadius(float _value)
{
    m_radius = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Rebuild point light
 */
void Universe1::OpenGL::Models::ModelPointLight::rebuild()
{
    static const float _1_sqrt3 = 1.0F / std::sqrt(3.0F);
    static const float _1_sqrt2 = 1.0F / std::sqrt(2.0F);

    static const std::vector<QVector3D> normalData = {
        QVector3D(-1.0F, 0.0F, 0.0F),
        QVector3D(+1.0F, 0.0F, 0.0F),

        QVector3D(0.0F, -1.0F, 0.0F),
        QVector3D(0.0F, +1.0F, 0.0F),

        QVector3D(0.0F, 0.0F, -1.0F),
        QVector3D(0.0F, 0.0F, +1.0F),

        QVector3D(-_1_sqrt2, -_1_sqrt2, 0.0F),
        QVector3D(+_1_sqrt2, +_1_sqrt2, 0.0F),
        QVector3D(-_1_sqrt2, +_1_sqrt2, 0.0F),
        QVector3D(+_1_sqrt2, -_1_sqrt2, 0.0F),

        QVector3D(-_1_sqrt2, 0.0F, -_1_sqrt2),
        QVector3D(+_1_sqrt2, 0.0F, +_1_sqrt2),
        QVector3D(-_1_sqrt2, 0.0F, +_1_sqrt2),
        QVector3D(+_1_sqrt2, 0.0F, -_1_sqrt2),

        QVector3D(0.0F, -_1_sqrt2, -_1_sqrt2),
        QVector3D(0.0F, +_1_sqrt2, +_1_sqrt2),
        QVector3D(0.0F, -_1_sqrt2, +_1_sqrt2),
        QVector3D(0.0F, +_1_sqrt2, -_1_sqrt2),

        QVector3D(-_1_sqrt3, -_1_sqrt3, -_1_sqrt3),
        QVector3D(+_1_sqrt3, +_1_sqrt3, +_1_sqrt3),

        QVector3D(-_1_sqrt3, -_1_sqrt3, +_1_sqrt3),
        QVector3D(+_1_sqrt3, +_1_sqrt3, -_1_sqrt3),

        QVector3D(-_1_sqrt3, +_1_sqrt3, +_1_sqrt3),
        QVector3D(+_1_sqrt3, -_1_sqrt3, -_1_sqrt3),

        QVector3D(-_1_sqrt3, +_1_sqrt3, -_1_sqrt3),
        QVector3D(+_1_sqrt3, -_1_sqrt3, +_1_sqrt3),
    };

    std::vector<QVector3D> vertexData;
    vertexData.reserve(normalData.size());
    for (size_t i = 0; i < normalData.size(); ++i)
        vertexData.push_back(m_position + normalData[i] * m_radius);

    initBuffers(
        vertexData,
        normalData,
        {0U, 0U, 0U, 0U, 0U, 0U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 2U, 2U, 2U, 2U, 2U, 2U, 2U, 2U},
        {});
}
