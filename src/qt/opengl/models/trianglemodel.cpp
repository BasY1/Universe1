/*!
 * \file qt/opengl/models/trianglemodel.h
 * \author Michal Steller
 * \brief Open GL single triangle model with material class implementation
 */

#include "trianglemodel.h"

/*!
 * \brief Constructor
 * \param _material Material
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::TriangleModel::TriangleModel(const Material &_material, QObject *_parent)
    : MaterialModel(_material, _parent)
    , m_ccw(true)
    , m_vertex1(-0.5F, -0.5F, 0.0F)
    , m_vertex2(0.5F, -0.5F, 0.0F)
    , m_vertex3(0.0F, 0.5F, 0.0F)
    , m_normal1(0.0F, 0.0F, 1.0F)
    , m_normal2(0.0F, 0.0F, 1.0F)
    , m_normal3(0.0F, 0.0F, 1.0F)
{
}

/*!
 * \brief Constructor
 * \param _vertex1 Vertex 1 position
 * \param _vertex2 Vertex 2 position
 * \param _vertex3 Vertex 3 position
 * \param _normalAll Vertex normal for all three vertices
 * \param _material Material
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::TriangleModel::TriangleModel(QVector3D _vertex1,
                                                        QVector3D _vertex2,
                                                        QVector3D _vertex3,
                                                        QVector3D _normalAll,
                                                        const Material &_material,
                                                        QObject *_parent)
    : MaterialModel(_material, _parent)
    , m_ccw(true)
    , m_vertex1(_vertex1)
    , m_vertex2(_vertex2)
    , m_vertex3(_vertex3)
    , m_normal1(_normalAll)
    , m_normal2(_normalAll)
    , m_normal3(_normalAll)
{
}

/*!
 * \brief Constructor
 * \param _vertex1 Vertex 1 position
 * \param _vertex2 Vertex 2 position
 * \param _vertex3 Vertex 3 position
 * \param _normal1 Vertex 1 normal
 * \param _normal2 Vertex 2 normal
 * \param _normal3 Vertex 3 normal
 * \param _material Material
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::TriangleModel::TriangleModel(QVector3D _vertex1,
                                                        QVector3D _vertex2,
                                                        QVector3D _vertex3,
                                                        QVector3D _normal1,
                                                        QVector3D _normal2,
                                                        QVector3D _normal3,
                                                        const Material &_material,
                                                        QObject *_parent)
    : MaterialModel(_material, _parent)
    , m_ccw(true)
    , m_vertex1(_vertex1)
    , m_vertex2(_vertex2)
    , m_vertex3(_vertex3)
    , m_normal1(_normal1)
    , m_normal2(_normal2)
    , m_normal3(_normal3)
{
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::TriangleModel::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Rebuild triangle
 */
void Universe1::OpenGL::Models::TriangleModel::rebuild()
{
    const std::vector<QVector3D> vertexData = {m_vertex1, m_vertex2, m_vertex3};
    const std::vector<QVector3D> normalData = {m_normal1, m_normal2, m_normal3};
    const std::vector<uint> linesData = {0U, 1U, 1U, 2U, 2U, 3U};

    if (m_ccw)
        initBuffers(vertexData, normalData, {0U, 1U, 2U}, linesData);
    else
        initBuffers(vertexData, normalData, {0U, 2U, 1U}, linesData);
}

/*!
 * \brief Setter for counter-clockwise flag
 * \param _value New counter-clockwise flag value
 */
void Universe1::OpenGL::Models::TriangleModel::setCcw(bool _value)
{
    m_ccw = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setup triangle
 * \param _vertex1 Vertex 1 position
 * \param _vertex2 Vertex 2 position
 * \param _vertex3 Vertex 3 position
 * \param _normalAll Vertex normal for all three vertices
 */
void Universe1::OpenGL::Models::TriangleModel::setTriangle(QVector3D _vertex1,
                                                           QVector3D _vertex2,
                                                           QVector3D _vertex3,
                                                           QVector3D _normalAll)
{
    setTriangle(_vertex1, _vertex2, _vertex3, _normalAll, _normalAll, _normalAll);
}

/*!
 * \brief Setup triangle
 * \param _vertex1 Vertex 1 position
 * \param _vertex2 Vertex 2 position
 * \param _vertex3 Vertex 3 position
 * \param _normal1 Vertex 1 normal
 * \param _normal2 Vertex 2 normal
 * \param _normal3 Vertex 3 normal
 */
void Universe1::OpenGL::Models::TriangleModel::setTriangle(QVector3D _vertex1,
                                                           QVector3D _vertex2,
                                                           QVector3D _vertex3,
                                                           QVector3D _normal1,
                                                           QVector3D _normal2,
                                                           QVector3D _normal3)
{
    m_vertex1 = _vertex1;
    m_vertex2 = _vertex2;
    m_vertex3 = _vertex3;
    m_normal1 = _normal1;
    m_normal2 = _normal2;
    m_normal3 = _normal3;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 1 position
 * \param _value New vertex 1 position value
 */
void Universe1::OpenGL::Models::TriangleModel::setVertex1(QVector3D _value)
{
    m_vertex1 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 2 position
 * \param _value New vertex 2 position value
 */
void Universe1::OpenGL::Models::TriangleModel::setVertex2(QVector3D _value)
{
    m_vertex2 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 3 position
 * \param _value New vertex 3 position value
 */
void Universe1::OpenGL::Models::TriangleModel::setVertex3(QVector3D _value)
{
    m_vertex3 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 1 normal
 * \param _value New vertex 1 normal value
 */
void Universe1::OpenGL::Models::TriangleModel::setNormal1(QVector3D _value)
{
    m_normal1 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 2 normal
 * \param _value New vertex 2 normal value
 */
void Universe1::OpenGL::Models::TriangleModel::setNormal2(QVector3D _value)
{
    m_normal2 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for vertex 3 normal
 * \param _value New vertex 3 normal value
 */
void Universe1::OpenGL::Models::TriangleModel::setNormal3(QVector3D _value)
{
    m_normal3 = _value;
    rebuild();
    emit changed();
}

/*!
 * \brief Setter for normal for all vertices
 * \param _value New normal value
 */
void Universe1::OpenGL::Models::TriangleModel::setNormalAll(QVector3D _value)
{
    m_normal1 = _value;
    m_normal2 = _value;
    m_normal3 = _value;
    rebuild();
    emit changed();
}
