/*!
 * \file qt/opengl/models/modelplane.cpp
 * \author Michal Steller
 * \brief Open GL 3D plane model with material class implementation
 */

#include "modelplane.h"

/*!
 * \brief Constructor
 * \param _material Material
 * \param _center Plane center position
 * \param _normal1 First plane normal
 * \param _normal2 Second plane normal
 * \param _dots1 Dots count over normal 1
 * \param _dots2 Dots count over normal 2
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelPlane::ModelPlane(const Material &_material,
                                                  const QVector3D &_center,
                                                  const QVector3D &_normal1,
                                                  const QVector3D &_normal2,
                                                  const int _dots1,
                                                  const int _dots2,
                                                  QObject *_parent)
    : MeshModel(_material, _parent)
    , m_center(_center)
    , m_normal1(_normal1)
    , m_normal2(_normal2)
    , m_dots1(_dots1)
    , m_dots2(_dots2)
{
}

/*!
 * \brief Rebuild plane
 */
void Universe1::OpenGL::Models::ModelPlane::rebuild()
{
    const QVector3D norm = normal();
    const int vertexCount = 2 * (m_dots1 + m_dots2 + 2);
    const int linesCount = 2 * (m_dots1 + m_dots2 + 4);

    QVector3D step = m_normal2 / static_cast<float>(m_dots2 + 1);
    QVector3D tmp1 = m_center - 0.5F * (m_normal1 + m_normal2);
    QVector3D tmp2 = tmp1 + m_normal1;

    const std::vector<QVector3D> normalData(vertexCount, norm);
    std::vector<QVector3D> vertexData;
    std::vector<uint> linesData;

    vertexData.reserve(vertexCount);
    linesData.reserve(linesCount);

    uint idx = 0U;
    for (int i1 = 0; i1 <= m_dots2 + 1; ++i1)
    {
        vertexData.push_back(tmp1);
        vertexData.push_back(tmp2);
        linesData.push_back(idx++);
        linesData.push_back(idx++);
        tmp1 += step;
        tmp2 += step;
    }

    const std::vector<uint> triangData = {0U, idx - 1U, 1U, 0U, idx - 2U, idx - 1U};

    linesData.push_back(0U);
    linesData.push_back(idx - 2U);
    linesData.push_back(1U);
    linesData.push_back(idx - 1U);

    step = m_normal1 / static_cast<float>(m_dots1 + 1);
    tmp1 = m_center - 0.5F * (m_normal1 + m_normal2) + step;
    tmp2 = tmp1 + m_normal2;

    for (int i1 = 0; i1 < m_dots1; ++i1)
    {
        vertexData.push_back(tmp1);
        vertexData.push_back(tmp2);
        linesData.push_back(idx++);
        linesData.push_back(idx++);
        tmp1 += step;
        tmp2 += step;
    }

    initBuffers(vertexData, normalData, {}, triangData, linesData);
}

/*!
 * \brief Setter for plane both normals
 * \param _normal1 New plane normal 1
 * \param _normal2 New plane normal 2
 */
void Universe1::OpenGL::Models::ModelPlane::setNormals(const QVector3D &_normal1, const QVector3D &_normal2)
{
    // TODO make sure not parallel maybe not null ??
    m_normal1 = _normal1;
    m_normal2 = _normal2;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for plane normal 1
 * \param _value New plane normal 1
 */
void Universe1::OpenGL::Models::ModelPlane::setNormal1(const QVector3D &_value)
{
    setNormals(_value, m_normal2);
}

/*!
 * \brief Setter for plane normal 2
 * \param _value New plane normal 2
 */
void Universe1::OpenGL::Models::ModelPlane::setNormal2(const QVector3D &_value)
{
    setNormals(m_normal1, _value);
}

/*!
 * \brief Setter for plane center position
 * \param _value New plane center position
 */
void Universe1::OpenGL::Models::ModelPlane::setCenter(const QVector3D &_value)
{
    m_center = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots count for both normal
 * \param _value New dots count for both normal
 */
void Universe1::OpenGL::Models::ModelPlane::setDots(int _value)
{
    m_dots1 = std::max(0, _value);
    m_dots2 = m_dots1;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots count for both normal
 * \param _dots1 New dots count over normal 1
 * \param _dots2 New dots count over normal 2
 */
void Universe1::OpenGL::Models::ModelPlane::setDots(int _dots1, int _dots2)
{
    m_dots1 = std::max(0, _dots1);
    m_dots2 = std::max(0, _dots2);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots count for normal 1
 * \param _value New dots count for normal 1
 */
void Universe1::OpenGL::Models::ModelPlane::setDots1(int _value)
{
    m_dots1 = std::max(0, _value);
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots count for normal 2
 * \param _value New dots count for normal 2
 */
void Universe1::OpenGL::Models::ModelPlane::setDots2(int _value)
{
    m_dots2 = std::max(0, _value);
    if (isInit())
        rebuild();
    emit changed();
}
