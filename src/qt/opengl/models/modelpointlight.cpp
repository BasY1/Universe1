/*!
 * \file qt/opengl/models/modelpointlight.h
 * \author Michal Steller
 * \brief Open GL point light model with material class implementation
 */

#include "modelpointlight.h"
#include <cmath>

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Point light position
 * \param _radius Point light radius
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelPointLight::ModelPointLight(const Material &_material,
                                                            const QVector3D &_position,
                                                            const float _radius,
                                                            QObject *_parent)
    : LinesModel(_material, _parent)
    , m_position(_position)
    , m_radius(_radius)
{
}

/*!
 * \brief Setter for point light values
 * \param _light New point light values
 */
void Universe1::OpenGL::Models::ModelPointLight::setPointLight(const PointLight &_light)
{
    m_enabled = _light.mode != PointLight::LightOff;

    m_position = _light.position;

    m_material.ambient = _light.ambient;
    m_material.diffuse = _light.diffuse;
    m_material.specular = _light.specular;

    if (isInit())
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
    static const std::vector<QVector3D> normalData = {
        QVector3D(-1.0F, 0.0F, 0.0F),
        QVector3D(+1.0F, 0.0F, 0.0F),

        QVector3D(0.0F, -1.0F, 0.0F),
        QVector3D(0.0F, +1.0F, 0.0F),

        QVector3D(0.0F, 0.0F, -1.0F),
        QVector3D(0.0F, 0.0F, +1.0F),

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
    vertexData.reserve(14);
    for (size_t i = 0; i < 14; ++i)
        vertexData.push_back(m_position + normalData[i] * m_radius);

    initBuffers(vertexData, normalData);
}
