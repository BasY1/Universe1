/*!
 * \file qt/opengl/models/meshmodel.cpp
 * \author Michal Steller
 * \brief Base Open GL mesh model with material class implementation
 */

#include "meshmodel.h"

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::MeshModel::MeshModel(const Material &_material, QObject *_parent)
    : GLModel(_material, _parent)
    , m_isInit(false)
    , m_canSwitchDrawWireFrame(false)
    , m_drawWireFrame(false)
    , m_memoryUsage(0U)
    , m_minimum()
    , m_maximum()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_triangsIndexes(QOpenGLBuffer::IndexBuffer)
    , m_linesIndexes(QOpenGLBuffer::IndexBuffer)
    , m_triangsCount(0)
    , m_linesCount(0)
{
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::Models::MeshModel::~MeshModel()
{
    if (m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if (m_normalBuffer.isCreated())
        m_normalBuffer.destroy();
    if (m_triangsIndexes.isCreated())
        m_triangsIndexes.destroy();
    if (m_linesIndexes.isCreated())
        m_linesIndexes.destroy();
}

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
bool Universe1::OpenGL::Models::MeshModel::isInit() const
{
    return m_isInit;
}

/*!
 * \brief Getter for is possible to switch value of draw wire-framed flag
 * \returns Is possible to switch value of draw wire-framed flag
 */
bool Universe1::OpenGL::Models::MeshModel::canSwitchDrawWireFrame() const
{
    return m_canSwitchDrawWireFrame;
}

/*!
 * \brief Getter draw wire-framed flag
 * \returns Draw wire-framed flag
 */
bool Universe1::OpenGL::Models::MeshModel::drawWireFrame() const
{
    return m_drawWireFrame;
}

/*!
 * \brief Returns size of allocated memory within OpenGL context
 * \returns Size of allocated memory within OpenGL context
 */
size_t Universe1::OpenGL::Models::MeshModel::memoryUsage() const
{
    return m_memoryUsage;
}

/*!
 * \brief Returns object range
 * \returns Object range (pair of 3D vectors minimum [x, y, z] and maximum [x, y, z])
 */
std::pair<QVector3D, QVector3D> Universe1::OpenGL::Models::MeshModel::range() const
{
    return {m_minimum, m_maximum};
}

/*!
 * \brief Initialize buffers
 * \param _vertexData Vertex buffer
 * \param _normalData Normal buffer
 * \param _triangsData Triangles faces index buffer
 * \param _linesData Line index buffer
 * \returns Success flag
 */
bool Universe1::OpenGL::Models::MeshModel::initBuffers(const std::vector<QVector3D> &_vertexData,
                                                       const std::vector<QVector3D> &_normalData,
                                                       const std::vector<uint> &_triangsData,
                                                       const std::vector<uint> &_linesData)
{
    m_isInit = false;
    m_canSwitchDrawWireFrame = false;
    m_triangsCount = 0;
    m_linesCount = 0;
    m_minimum = QVector3D();
    m_maximum = QVector3D();

    if (!m_vertexBuffer.isCreated())
    {
        if (!m_vertexBuffer.create())
            return false;
    }

    if (!m_normalBuffer.isCreated())
    {
        if (!m_normalBuffer.create())
            return false;
    }

    if (!_triangsData.empty())
    {
        if (!m_triangsIndexes.isCreated())
        {
            if (!m_triangsIndexes.create())
                return false;
        }
    }

    if (!_linesData.empty())
    {
        if (!m_linesIndexes.isCreated())
        {
            if (!m_linesIndexes.create())
                return false;
        }
    }

    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(_vertexData.data(), _vertexData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    m_memoryUsage += _vertexData.size() * sizeof(QVector3D);
    if (!_vertexData.empty())
    {
        m_minimum = _vertexData.front();
        m_maximum = m_minimum;
        for (const QVector3D &v : _vertexData)
        {
            if (m_minimum.x() > v.x())
                m_minimum.setX(v.x());
            if (m_minimum.y() > v.y())
                m_minimum.setY(v.y());
            if (m_minimum.z() > v.z())
                m_minimum.setZ(v.z());
            if (m_maximum.x() < v.x())
                m_maximum.setX(v.x());
            if (m_maximum.y() < v.y())
                m_maximum.setY(v.y());
            if (m_maximum.z() < v.z())
                m_maximum.setZ(v.z());
        }
    }

    m_normalBuffer.bind();
    m_normalBuffer.allocate(_normalData.data(), _normalData.size() * sizeof(QVector3D));
    m_normalBuffer.release();
    m_memoryUsage += _normalData.size() * sizeof(QVector3D);

    if (!_triangsData.empty())
    {
        m_triangsIndexes.bind();
        m_triangsIndexes.allocate(_triangsData.data(), _triangsData.size() * sizeof(uint));
        m_triangsIndexes.release();
        m_memoryUsage += _triangsData.size() * sizeof(uint);
        m_triangsCount = _triangsData.size();
    }

    if (!_linesData.empty())
    {
        m_linesIndexes.bind();
        m_linesIndexes.allocate(_linesData.data(), _linesData.size() * sizeof(uint));
        m_linesIndexes.release();
        m_memoryUsage += _linesData.size() * sizeof(uint);
        m_linesCount = _linesData.size();
    }

    m_isInit = true;

    m_canSwitchDrawWireFrame = (!_triangsData.empty() && !_linesData.empty());

    if (!_triangsData.empty() && _linesData.empty())
        m_drawWireFrame = false;
    else if (_triangsData.empty() && !_linesData.empty())
        m_drawWireFrame = true;

    return true;
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::MeshModel::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 */
void Universe1::OpenGL::Models::MeshModel::paintGLImlp(ShaderProgram *_program)
{
    m_vertexBuffer.bind();
    _program->enableAttributeArray(_program->attrVertex());
    _program->setAttributeBuffer(_program->attrVertex(), GL_FLOAT, 0, 3);

    m_normalBuffer.bind();
    _program->enableAttributeArray(_program->attrNormal());
    _program->setAttributeBuffer(_program->attrNormal(), GL_FLOAT, 0, 3);

    if (m_drawWireFrame)
    {
        m_linesIndexes.bind();
        glDrawElements(GL_LINES, m_linesCount, GL_UNSIGNED_INT, nullptr);
        m_linesIndexes.release();
    }
    else
    {
        m_triangsIndexes.bind();
        glDrawElements(GL_TRIANGLES, m_triangsCount, GL_UNSIGNED_INT, nullptr);
        m_triangsIndexes.release();
    }

    m_normalBuffer.release();
    m_vertexBuffer.release();
}

/*!
 * \brief Setter for draw wire-framed flag
 * \param _value New draw wire-framed flag value
 * \note Updates only when allowed by \a m_canSwitchDrawWireFrame = \c true
 */
void Universe1::OpenGL::Models::MeshModel::setDrawWireFrame(bool _value)
{
    if (m_canSwitchDrawWireFrame && m_drawWireFrame != _value)
    {
        m_drawWireFrame = _value;
        emit changed();
    }
}

