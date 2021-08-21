/*!
 * \file qt/opengl/models/modelsphere.cpp
 * \author Michal Steller
 * \brief Open GL single sphere model with material class implementation
 */

#include "modelsphere.h"
#include <cmath>

/*!
 * \brief Constructor
 * \param _material Material
 * \param _position Sphere position
 * \param _toPole Sphere normal 1 (direction from center to pole)
 * \param _toEquator Sphere normal 2 (direction from center to equator)
 * \param _radius Sphere radius
 * \param _equatorPointCount Point count on equator
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelSphere::ModelSphere(const Material &_material,
                                                    const QVector3D &_position,
                                                    const QVector3D &_toPole,
                                                    const QVector3D &_toEquator,
                                                    const float _radius,
                                                    const int _equatorPointCount,
                                                    QObject *_parent)
    : MeshModel(_material, _parent)
    , m_position(_position)
    , m_toPole(_toPole)
    , m_toEquator(_toEquator)
    , m_radius(_radius)
    , m_equatorPointCount(std::min(1024, std::max(4, _equatorPointCount)))
{
    if (m_equatorPointCount % 2 != 0)
        ++m_equatorPointCount;
    initNormals(m_toPole, m_toEquator);
}

/*!
 * \brief Setter for sphere position
 * \param _value New sphere position
 */
void Universe1::OpenGL::Models::ModelSphere::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for sphere normal
 * \param _toPole New sphere normal 1 (direction from center to pole)
 * \param _toEquator New sphere normal 2 (direction from center to equator)
 */
void Universe1::OpenGL::Models::ModelSphere::setNormal(const QVector3D &_toPole, const QVector3D &_toEquator)
{
    m_toPole = _toPole;
    m_toEquator = _toEquator;
    initNormals(m_toPole, m_toEquator);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for sphere radius
 * \param _value New sphere radius
 */
void Universe1::OpenGL::Models::ModelSphere::setRadius(float _value)
{
    m_radius = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for sphere point count on equator
 * \param _value New sphere point count on equator
 */
void Universe1::OpenGL::Models::ModelSphere::setEquatorPointCount(int _value)
{
    int newValue = std::min(1024, std::max(4, _value));
    if (newValue % 2 != 0)
        ++newValue;
    if (m_equatorPointCount != newValue)
    {
        m_equatorPointCount = newValue;
        if (isInit())
            rebuild();
        emit changed();
    }
}

/*!
 * \brief Returns rotated point around normal by angle (right-handed rotation)
 * \param _p Point to rotate
 * \param _n Rotation normal (axis)
 * \param _sa Sinus angle in radians
 * \param _ca Cosinus angle in radians
 * \return
 */
static QVector3D rotate(const QVector3D &_p, const QVector3D &_n, const float _sa, const float _ca)
{
    const QVector3D u = _n.x() * _p;
    const QVector3D v = _n.y() * _p;
    const QVector3D w = _n.z() * _p;
    return QVector3D(_n.x() * u.x() + _sa * (v.z() - w.y()) + _ca * _p.x() * (_n.y() * _n.y() + _n.z() * _n.z()),
                     _n.y() * v.y() + _sa * (w.x() - u.z()) + _ca * _p.y() * (_n.x() * _n.x() + _n.z() * _n.z()),
                     _n.z() * w.z() + _sa * (u.y() - v.x()) + _ca * _p.z() * (_n.x() * _n.x() + _n.y() * _n.y()));
}

/*!
 * \brief Rebuild sphere
 */
void Universe1::OpenGL::Models::ModelSphere::rebuild()
{
    const float angle = 2.0 * M_PI / static_cast<float>(m_equatorPointCount);
    const float sa = std::sin(angle);
    const float ca = std::cos(angle);
    const int rows = m_equatorPointCount / 2 - 1;
    const size_t pointCount = rows * m_equatorPointCount + 2;

    std::vector<QVector3D> vertexData;
    std::vector<QVector3D> normalData;

    vertexData.reserve(pointCount);
    normalData.reserve(pointCount);
    vertexData.push_back(m_position + m_toPole * m_radius);
    normalData.push_back(m_toPole);

    float ar = angle;
    for (int r = 0; r < rows; ++r, ar += angle)
    {
        QVector3D arm = rotate(m_toPole, m_toEquator, std::sin(ar), std::cos(ar)).normalized();
        for (int p = 0; p < m_equatorPointCount; ++p)
        {
            vertexData.push_back(m_position + arm * m_radius);
            normalData.push_back(arm);
            arm = rotate(arm, m_toPole, sa, ca).normalized();
        }
    }

    vertexData.push_back(m_position - m_toPole * m_radius);
    normalData.push_back(-m_toPole);

    std::vector<uint> triangData;
    std::vector<uint> linesData;
    triangData.reserve(6 * m_equatorPointCount * rows);
    linesData.reserve(2 * m_equatorPointCount * (2 * rows + 1));

    uint prevIdx = 1U, idx = 1U;
    for (int i = 0; i < m_equatorPointCount - 1; ++i)
    {
        triangData.push_back(0U);
        triangData.push_back(idx);
        triangData.push_back(idx + 1U);

        linesData.push_back(0U);
        linesData.push_back(idx);

        linesData.push_back(idx);
        linesData.push_back(idx + 1U);

        ++idx;
    }

    triangData.push_back(0U);
    triangData.push_back(idx);
    triangData.push_back(prevIdx);

    linesData.push_back(0U);
    linesData.push_back(idx);

    linesData.push_back(idx);
    linesData.push_back(prevIdx);

    idx = 1U;

    const uint stepR = m_equatorPointCount;
    for (int r = 0; r < rows - 1; ++r)
    {
        prevIdx = idx;
        for (int i = 0; i < m_equatorPointCount - 1; ++i)
        {
            triangData.push_back(idx);
            triangData.push_back(idx + stepR);
            triangData.push_back(idx + stepR + 1U);

            triangData.push_back(idx);
            triangData.push_back(idx + stepR + 1U);
            triangData.push_back(idx + 1U);

            linesData.push_back(idx);
            linesData.push_back(idx + stepR);

            linesData.push_back(idx);
            linesData.push_back(idx + 1U);

            ++idx;
        }

        triangData.push_back(idx);
        triangData.push_back(idx + stepR);
        triangData.push_back(prevIdx + stepR);

        triangData.push_back(idx);
        triangData.push_back(prevIdx + stepR);
        triangData.push_back(prevIdx);

        linesData.push_back(idx);
        linesData.push_back(idx + stepR);

        linesData.push_back(idx);
        linesData.push_back(prevIdx);

        ++idx;
    }

    const uint last = pointCount - 1U;
    prevIdx = idx;
    for (int i = 0; i < m_equatorPointCount - 1; ++i)
    {
        triangData.push_back(last);
        triangData.push_back(idx + 1U);
        triangData.push_back(idx);

        linesData.push_back(last);
        linesData.push_back(idx);

        ++idx;
    }

    triangData.push_back(last);
    triangData.push_back(prevIdx);
    triangData.push_back(idx);

    linesData.push_back(last);
    linesData.push_back(idx);

    initBuffers(vertexData, normalData, triangData, linesData);
}
