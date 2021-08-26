/*!
 * \file qt/opengl/models/modeltorus.cpp
 * \author Michal Steller
 * \brief Open GL torus model with material class implementation
 */

#include "modeltorus.h"

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Torus position
 * \param _toPole Torus normal 1 (direction from center to pole)
 * \param _toEquator Torus normal 2 (direction from center to equator)
 * \param _radiusRing Torus radius of Ring
 * \param _radiusBody Torus radius of torus body
 * \param _circlePointCount Point count on circle
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelTorus::ModelTorus(const Material &_material,
                                                  const RenderMode _renderMode,
                                                  const bool _invertedFaces,
                                                  const QVector3D &_position,
                                                  const QVector3D &_toPole,
                                                  const QVector3D &_toEquator,
                                                  const float _radiusRing,
                                                  const float _radiusBody,
                                                  const int _circlePointCount,
                                                  QObject *_parent)
    : MeshModel(_material, _renderMode, _invertedFaces, _parent)
    , m_position(_position)
    , m_toPole(_toPole)
    , m_toEquator(_toEquator)
    , m_radiusRing(_radiusRing)
    , m_radiusBody(_radiusBody)
    , m_circlePointCount(prepareCirclePointCount(_circlePointCount))
{
    prepareNormals(m_toPole, m_toEquator);
}

/*!
 * \brief Setter for torus position
 * \param _value New torus position
 */
void Universe1::OpenGL::Models::ModelTorus::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for torus normal
 * \param _toPole New torus normal 1 (direction from center to pole)
 * \param _toEquator New torus normal 2 (direction from center to equator)
 */
void Universe1::OpenGL::Models::ModelTorus::setNormal(const QVector3D &_toPole, const QVector3D &_toEquator)
{
    m_toPole = _toPole;
    m_toEquator = _toEquator;
    prepareNormals(m_toPole, m_toEquator);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for torus radiusRing
 * \param _value New torus radiusRing
 */
void Universe1::OpenGL::Models::ModelTorus::setRadiusRing(float _value)
{
    m_radiusRing = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for torus radiusBody
 * \param _value New torus radiusBody
 */
void Universe1::OpenGL::Models::ModelTorus::setRadiusBody(float _value)
{
    m_radiusBody = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for torus point count on circle
 * \param _value New torus point count on circle
 */
void Universe1::OpenGL::Models::ModelTorus::setCirclePointCount(int _value)
{
    m_circlePointCount = prepareCirclePointCount(_value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Rebuild torus
 */
void Universe1::OpenGL::Models::ModelTorus::rebuild()
{
    const float angle = 2.0 * M_PI / static_cast<float>(m_circlePointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);

    const uint loopCnt = m_circlePointCount;
    const size_t pointCount = loopCnt * loopCnt;

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    std::vector<uint> triangData;
    std::vector<uint> linesData;

    vertexData.reserve(pointCount);
    normalData.reserve(pointCount);
    triangData.reserve(pointCount * 4U);
    linesData.reserve(pointCount * 6U);

    QVector3D normal1 = m_toEquator;
    for (uint i = 0U; i < loopCnt; ++i)
    {
        const QVector3D rotNormal = QVector3D::crossProduct(m_toPole, normal1).normalized();
        const QVector3D bodyCenter = m_position + normal1 * m_radiusRing;
        QVector3D normal2 = normal1;
        for (uint j = 0U; j < loopCnt; ++j)
        {
            vertexData.push_back(bodyCenter + normal2 * m_radiusBody);
            normalData.push_back(normal2);
            normal2 = rotate(normal2, rotNormal, sa, ca).normalized();
        }
        normal1 = rotate(normal1, m_toPole, sa, ca).normalized();
    }

    for (uint i = 0U; i < loopCnt - 1U; ++i)
    {
        for (uint j = 0U; j < loopCnt - 1U; ++j)
        {
            triangData.push_back(i * loopCnt + j);
            triangData.push_back((i + 1U) * loopCnt + j + 1U);
            triangData.push_back((i + 1U) * loopCnt + j);

            triangData.push_back(i * loopCnt + j);
            triangData.push_back(i * loopCnt + j + 1U);
            triangData.push_back((i + 1U) * loopCnt + j + 1U);

            linesData.push_back(i * loopCnt + j);
            linesData.push_back(i * loopCnt + j + 1U);

            linesData.push_back(i * loopCnt + j);
            linesData.push_back((i + 1U) * loopCnt + j);
        }

        triangData.push_back((i + 1U) * loopCnt - 1U);
        triangData.push_back(i * loopCnt);
        triangData.push_back((i + 1U) * loopCnt);

        triangData.push_back((i + 1U) * loopCnt - 1U);
        triangData.push_back((i + 1U) * loopCnt);
        triangData.push_back((i + 2U) * loopCnt - 1U);

        linesData.push_back((i + 1) * loopCnt - 1);
        linesData.push_back(i * loopCnt);

        linesData.push_back((i + 1) * loopCnt - 1);
        linesData.push_back((i + 2) * loopCnt - 1);
    }

    for (uint j = 0U; j < loopCnt - 1U; ++j)
    {
        triangData.push_back((loopCnt - 1U) * loopCnt + j);
        triangData.push_back(j + 1U);
        triangData.push_back(j);

        triangData.push_back((loopCnt - 1U) * loopCnt + j);
        triangData.push_back((loopCnt - 1U) * loopCnt + j + 1U);
        triangData.push_back(j + 1U);

        linesData.push_back((loopCnt - 1U) * loopCnt + j);
        linesData.push_back((loopCnt - 1U) * loopCnt + j + 1U);

        linesData.push_back((loopCnt - 1U) * loopCnt + j);
        linesData.push_back(j);
    }

    triangData.push_back(loopCnt * loopCnt - 1U);
    triangData.push_back(0U);
    triangData.push_back(loopCnt - 1U);

    triangData.push_back(loopCnt * loopCnt - 1U);
    triangData.push_back((loopCnt - 1U) * loopCnt);
    triangData.push_back(0U);

    linesData.push_back(loopCnt * loopCnt - 1U);
    linesData.push_back((loopCnt - 1U) * loopCnt);

    linesData.push_back(loopCnt * loopCnt - 1U);
    linesData.push_back(loopCnt - 1U);

    initBuffers(vertexData, normalData, {}, triangData, linesData);
}
