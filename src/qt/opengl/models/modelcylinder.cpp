/*!
 * \file qt/opengl/models/modelcylinder.cpp
 * \author Michal Steller
 * \brief Open GL cylinder model with material class implementation
 */

#include "modelcylinder.h"

/*!
 * \brief Constructor
 * \param _material Initial material
 * \param _renderMode Initial render mode
 * \param _invertedFaces Initial inverted faces flag
 * \param _position Cylinder position
 * \param _toPole Cylinder normal 1 (direction from center to pole)
 * \param _toEquator Cylinder normal 2 (direction from center to equator)
 * \param _radius Cylinder radius
 * \param _height Cylinder height
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelCylinder::ModelCylinder(const Material &_material,
                                                        const RenderMode _renderMode,
                                                        const bool _invertedFaces,
                                                        const QVector3D &_position,
                                                        const QVector3D &_toPole,
                                                        const QVector3D &_toEquator,
                                                        const float _radius,
                                                        const float _height,
                                                        const int _equatorPointCount,
                                                        QObject *_parent)
    : MeshModel(_material, _renderMode, _invertedFaces, _parent)
    , m_position(_position)
    , m_toPole(_toPole)
    , m_toEquator(_toEquator)
    , m_radius(_radius)
    , m_height(_height)
    , m_equatorPointCount(prepareCirclePointCount(_equatorPointCount))
{
    prepareNormals(m_toPole, m_toEquator);
}

/*!
 * \brief Setter for cylinder position
 * \param _value New cylinder position
 */
void Universe1::OpenGL::Models::ModelCylinder::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for cylinder normal
 * \param _toPole New cylinder normal 1 (direction from center to pole)
 * \param _toEquator New cylinder normal 2 (direction from center to equator)
 */
void Universe1::OpenGL::Models::ModelCylinder::setNormal(const QVector3D &_toPole, const QVector3D &_toEquator)
{
    m_toPole = _toPole;
    m_toEquator = _toEquator;
    prepareNormals(m_toPole, m_toEquator);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for cylinder radius
 * \param _value New cylinder radius
 */
void Universe1::OpenGL::Models::ModelCylinder::setRadius(float _value)
{
    m_radius = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for cylinder height
 * \param _value New cylinder height
 */
void Universe1::OpenGL::Models::ModelCylinder::setHeight(float _value)
{
    m_height = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for cylinder point count on equator
 * \param _value New cylinder point count on equator
 */
void Universe1::OpenGL::Models::ModelCylinder::setEquatorPointCount(int _value)
{
    m_equatorPointCount = prepareCirclePointCount(_value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Rebuild cylinder
 */
void Universe1::OpenGL::Models::ModelCylinder::rebuild()
{
    const float angle = 2.0 * M_PI / static_cast<float>(m_equatorPointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);

    const QVector3D pBottom = m_position - m_toPole * (0.5F * m_height);
    const QVector3D pTop = m_position + m_toPole * (0.5F * m_height);

    const size_t pointCount = 2 + 4 * m_equatorPointCount;

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;
    vertexData.reserve(pointCount);
    normalData.reserve(pointCount);

    vertexData.push_back(pBottom);
    vertexData.push_back(pTop);

    normalData.push_back(-m_toPole);
    normalData.push_back(m_toPole);

    QVector3D dir = m_toEquator;
    for (int i = 0; i < m_equatorPointCount; ++i)
    {
        const QVector3D arm = dir * m_radius;

        vertexData.push_back(pBottom + arm);
        normalData.push_back(-m_toPole);

        vertexData.push_back(pBottom + arm);
        normalData.push_back(dir);

        vertexData.push_back(pTop + arm);
        normalData.push_back(dir);

        vertexData.push_back(pTop + arm);
        normalData.push_back(m_toPole);

        dir = rotate(dir, m_toPole, sa, ca).normalized();
    }

    std::vector<uint> triangData;
    std::vector<uint> linesData;
    triangData.reserve(12 * m_equatorPointCount);
    linesData.reserve(10 * m_equatorPointCount);

    for (int i = 0; i < m_equatorPointCount - 1; ++i)
    {
        triangData.push_back(0U);
        triangData.push_back(2U + (i + 1) * 4);
        triangData.push_back(2U + i * 4);

        triangData.push_back(1U);
        triangData.push_back(2U + i * 4 + 3);
        triangData.push_back(2U + (i + 1) * 4 + 3);

        triangData.push_back(2U + i * 4 + 1);
        triangData.push_back(2U + (i + 1) * 4 + 1);
        triangData.push_back(2U + (i + 1) * 4 + 2);

        triangData.push_back(2U + i * 4 + 1);
        triangData.push_back(2U + (i + 1) * 4 + 2);
        triangData.push_back(2U + i * 4 + 2);

        linesData.push_back(0U);
        linesData.push_back(2U + i * 4);

        linesData.push_back(2U + i * 4 + 1);
        linesData.push_back(2U + i * 4 + 2);

        linesData.push_back(2U + i * 4 + 1);
        linesData.push_back(2U + (i + 1) * 4 + 1);

        linesData.push_back(2U + i * 4 + 2);
        linesData.push_back(2U + (i + 1) * 4 + 2);

        linesData.push_back(2U + i * 4 + 3);
        linesData.push_back(1U);
    }

    triangData.push_back(0U);
    triangData.push_back(2U);
    triangData.push_back(m_equatorPointCount * 4 - 2);

    triangData.push_back(1U);
    triangData.push_back(m_equatorPointCount * 4 + 1);
    triangData.push_back(5U);

    triangData.push_back(3U);
    triangData.push_back(m_equatorPointCount * 4);
    triangData.push_back(m_equatorPointCount * 4 - 1);

    triangData.push_back(3U);
    triangData.push_back(4U);
    triangData.push_back(m_equatorPointCount * 4);

    linesData.push_back(0U);
    linesData.push_back(m_equatorPointCount * 4 - 2);

    linesData.push_back(m_equatorPointCount * 4 - 1);
    linesData.push_back(m_equatorPointCount * 4);

    linesData.push_back(m_equatorPointCount * 4 + 1);
    linesData.push_back(5U);

    linesData.push_back(3U);
    linesData.push_back(m_equatorPointCount * 4 - 1);

    linesData.push_back(4U);
    linesData.push_back(m_equatorPointCount * 4);

    initBuffers(vertexData, normalData, {}, triangData, linesData);
}
