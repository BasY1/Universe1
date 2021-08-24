/*!
 * \file qt/opengl/models/modelspotlight.cpp
 * \author Michal Steller
 * \brief Open GL spot light model with material class implementation
 */

#include "modelspotlight.h"
#include <cmath>

/*!
 * \brief Constructor
 * \param _light Spot light data
 * \param _radius Spot light radius
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelSpotLight::ModelSpotLight(const SpotLight &_light,
                                                          const float _radius,
                                                          const int _circlePointCount,
                                                          QObject *_parent)
    : LinesModel({Material(_light.ambient, _light.ambient, _light.ambient),
                  Material(_light.diffuse, _light.diffuse, _light.diffuse),
                  Material(_light.specular, _light.specular, _light.specular)},
                 _parent)
    , m_position(_light.position)
    , m_direction(_light.direction.normalized())
    , m_cutOffRad(_light.cutOffRad)
    , m_outerCutOffRad(_light.outerCutOffRad)
    , m_radius(_radius)
    , m_circlePointCount(prepareCirclePointCount(_circlePointCount))
{
    m_enabled = _light.mode != SpotLight::LightOff;

    GLModel::m_materials.at(0).mode = Material::MaterialAmbient;
    GLModel::m_materials.at(1).mode = Material::MaterialAmbient;
    GLModel::m_materials.at(2).mode = Material::MaterialAmbient;
}

/*!
 * \brief Setter for spot light values
 * \param _light New spot light values
 */
void Universe1::OpenGL::Models::ModelSpotLight::setSpotLight(const SpotLight &_light)
{
    const bool needRebuild =
        (!qFuzzyCompare(m_position, _light.position) || !qFuzzyCompare(m_direction, _light.direction) ||
         !qFuzzyCompare(m_cutOffRad, _light.cutOffRad) || !qFuzzyCompare(m_outerCutOffRad, _light.outerCutOffRad));

    m_enabled = _light.mode != SpotLight::LightOff;
    m_position = _light.position;
    m_direction = _light.direction.normalized();
    m_cutOffRad = _light.cutOffRad;
    m_outerCutOffRad = _light.outerCutOffRad;

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
 * \brief Setter for spot light position
 * \param _value New spot light position
 */
void Universe1::OpenGL::Models::ModelSpotLight::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for spot light direction
 * \param _value New spot light direction
 */
void Universe1::OpenGL::Models::ModelSpotLight::setDirection(const QVector3D &_value)
{
    m_direction = _value.normalized();
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for spot light cut-off angle
 * \param _value New spot light cut-off angle
 */
void Universe1::OpenGL::Models::ModelSpotLight::setCutOffRad(float _value)
{
    m_cutOffRad = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for spot light outer cut-off angle
 * \param _value New spot light outer cut-off angle
 */
void Universe1::OpenGL::Models::ModelSpotLight::setOuterCutOffRad(float _value)
{
    m_outerCutOffRad = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for spot light radius
 * \param _value New spot light radius
 */
void Universe1::OpenGL::Models::ModelSpotLight::setRadius(float _value)
{
    m_radius = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for circle point count
 * \param _value New circle point count
 */
void Universe1::OpenGL::Models::ModelSpotLight::setCirclePointCount(int _value)
{
    m_circlePointCount = prepareCirclePointCount(_value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Rebuild point light
 */
void Universe1::OpenGL::Models::ModelSpotLight::rebuild()
{
    static const QVector3D _x(1.0F, 0.0F, 0.0F);
    static const QVector3D _y(0.0F, 1.0F, 0.0F);
    static const QVector3D _z(0.0F, 0.0F, 1.0F);

    static const float starRatio = 0.1F;

    const float angle = 2.0 * M_PI / static_cast<float>(m_circlePointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);

    const int vCnt = 17 + 2 * m_circlePointCount;
    const int lCnt = 24 + 4 * m_circlePointCount;

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    std::vector<uint8_t> materialData;
    std::vector<uint> linesData;

    vertexData.reserve(vCnt);
    normalData.reserve(vCnt);
    materialData.reserve(vCnt);
    linesData.reserve(lCnt);

    const QVector3D _perp1 = perpendicularVector(m_direction);
    const QVector3D _perp2 = QVector3D::crossProduct(m_direction, _perp1).normalized();

    const float radiusCircle1 = std::sin(0.5F * m_cutOffRad) * m_radius;
    const float radiusCircle2 = std::sin(0.5F * m_outerCutOffRad) * m_radius;

    const QVector3D circleCenter1 = m_position + m_direction * m_radius * std::cos(0.5F * m_cutOffRad);
    const QVector3D circleCenter2 = m_position + m_direction * m_radius * std::cos(0.5F * m_outerCutOffRad);

    QVector3D circleArm = _perp1;

#ifndef DOXYGEN_SKIP
#define __SET_VERTEX(COL, NORM, POS)                                                                                   \
    vertexData.push_back(POS);                                                                                         \
    normalData.push_back(NORM);                                                                                        \
    materialData.push_back(COL)
#endif  // DOXYGEN_SKIP

    __SET_VERTEX(0U, _x, m_position + _x * starRatio * m_radius);
    __SET_VERTEX(0U, -_x, m_position - _x * starRatio * m_radius);
    __SET_VERTEX(0U, _y, m_position + _y * starRatio * m_radius);
    __SET_VERTEX(0U, -_y, m_position - _y * starRatio * m_radius);
    __SET_VERTEX(0U, _z, m_position + _z * starRatio * m_radius);
    __SET_VERTEX(0U, -_z, m_position - _z * starRatio * m_radius);
    __SET_VERTEX(0U, -m_direction, m_position);
    __SET_VERTEX(0U, m_direction, m_position + m_direction * m_radius * (1.0F + starRatio));

    __SET_VERTEX(1U, -m_direction, m_position);
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp1, 0.5F * m_cutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp1, -0.5F * m_cutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp2, 0.5F * m_cutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp2, -0.5F * m_cutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp1, 0.5F * m_outerCutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp1, -0.5F * m_outerCutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp2, 0.5F * m_outerCutOffRad));
    __SET_VERTEX(1U, m_direction, m_position + m_radius * rotate(m_direction, _perp2, -0.5F * m_outerCutOffRad));

    for (int i = 0; i < m_circlePointCount; ++i)
    {
        __SET_VERTEX(2U, m_direction, circleCenter1 + circleArm * radiusCircle1);
        circleArm = rotate(circleArm, m_direction, sa, ca).normalized();
    }

    circleArm = _perp1;
    for (int i = 0; i < m_circlePointCount; ++i)
    {
        __SET_VERTEX(2U, m_direction, circleCenter2 + circleArm * radiusCircle2);
        circleArm = rotate(circleArm, m_direction, sa, ca).normalized();
    }

#undef __SET_VERTEX

    uint idx = 0;
    for (int i = 0; i < 8; ++i)
        linesData.push_back(idx++);

    for (uint i = 9U; i < 17U; ++i)
    {
        linesData.push_back(8U);
        linesData.push_back(i);
    }

    idx = 17U;
    for (int i = 0; i < m_circlePointCount - 1; ++i)
    {
        linesData.push_back(idx + i);
        linesData.push_back(idx + i + 1);
    }

    linesData.push_back(idx + m_circlePointCount - 1);
    linesData.push_back(idx);

    idx += m_circlePointCount;
    for (int i = 0; i < m_circlePointCount - 1; ++i)
    {
        linesData.push_back(idx + i);
        linesData.push_back(idx + i + 1);
    }

    linesData.push_back(idx + m_circlePointCount - 1);
    linesData.push_back(idx);

    initBuffers(vertexData, normalData, materialData, linesData);
}
