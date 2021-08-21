/*!
 * \file qt/opengl/models/modeldots.cpp
 * \author Michal Steller
 * \brief Open GL dots point-cloud model with material class implementation
 */

#include "modeldots.h"

/*!
 * \brief Constructor
 * \param _dotsData Initial dots vertex position data
 * \param _normal Initial normal
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelDots::ModelDots(const std::vector<QVector3D> &_dotsData,
                                                const QVector3D &_normal,
                                                const Material &_material,
                                                QObject *_parent)
    : GLModel(_material, _parent)
    , m_isInit(false)
    , m_normal(_normal)
    , m_dotsData(_dotsData)
    , m_memoryUsage(0U)
    , m_minimum()
    , m_maximum()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_dotsCount(0)
{
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::Models::ModelDots::~ModelDots()
{
    if (m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if (m_normalBuffer.isCreated())
        m_normalBuffer.destroy();
}

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
bool Universe1::OpenGL::Models::ModelDots::isInit() const
{
    return m_isInit;
}

/*!
 * \brief Returns size of allocated memory within OpenGL context
 * \returns Size of allocated memory within OpenGL context
 */
size_t Universe1::OpenGL::Models::ModelDots::memoryUsage() const
{
    return m_memoryUsage;
}

/*!
 * \brief Returns object range
 * \returns Object range (pair of 3D vectors minimum [x, y, z] and maximum [x, y, z])
 */
std::pair<QVector3D, QVector3D> Universe1::OpenGL::Models::ModelDots::range() const
{
    return {m_minimum, m_maximum};
}

/*!
 * \brief Rebuild buffers
 * \returns
 */
void Universe1::OpenGL::Models::ModelDots::rebuild()
{
    m_isInit = false;
    m_minimum = QVector3D();
    m_maximum = QVector3D();

    if (!m_vertexBuffer.isCreated())
    {
        if (!m_vertexBuffer.create())
            return;
    }

    if (!m_normalBuffer.isCreated())
    {
        if (!m_normalBuffer.create())
            return;
    }

    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_dotsData.data(), m_dotsData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    if (!m_dotsData.empty())
    {
        m_minimum = m_dotsData.front();
        m_maximum = m_minimum;
        for (const QVector3D &v : m_dotsData)
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
    m_memoryUsage += m_dotsData.size() * sizeof(QVector3D);

    const std::vector<QVector3D> normalData(m_dotsData.size(), m_normal);

    m_normalBuffer.bind();
    m_normalBuffer.allocate(normalData.data(), normalData.size() * sizeof(QVector3D));
    m_normalBuffer.release();
    m_memoryUsage += normalData.size() * sizeof(QVector3D);

    m_dotsCount = m_dotsData.size();

    m_isInit = m_dotsCount > 0;
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::ModelDots::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 */
void Universe1::OpenGL::Models::ModelDots::paintGLImlp(ShaderProgram *_program)
{
    m_vertexBuffer.bind();
    _program->enableAttributeArray(_program->attrVertex());
    _program->setAttributeBuffer(_program->attrVertex(), GL_FLOAT, 0, 3);

    m_normalBuffer.bind();
    _program->enableAttributeArray(_program->attrNormal());
    _program->setAttributeBuffer(_program->attrNormal(), GL_FLOAT, 0, 3);

    glDrawArrays(GL_POINTS, 0, m_dotsCount);

    m_normalBuffer.release();
    m_vertexBuffer.release();
}

/*!
 * \brief Setter for dots vertex data
 * \param _dotsData New dots vertices
 * \param _normal New normal
 */
void Universe1::OpenGL::Models::ModelDots::setData(const std::vector<QVector3D> &_dotsData, const QVector3D &_normal)
{
    m_normal = _normal;
    m_dotsData = _dotsData;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots vertex normal
 * \param _normal New dots vertex normal
 */
void Universe1::OpenGL::Models::ModelDots::setNormal(const QVector3D &_normal)
{
    m_normal = _normal;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for dots vertex data
 * \param _dotsData New dots vertices
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_dotsData)
{
    m_dotsData = _dotsData;
    if (isInit())
        rebuild();
    emit changed();
}
