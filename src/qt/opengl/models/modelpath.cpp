/*!
 * \file qt/opengl/models/modelpath.cpp
 * \author Michal Steller
 * \brief Base Open GL line path model with material class implementation
 */

#include "modelpath.h"

/*!
 * \brief Constructor
 * \param _pathData Initial path vertex position data
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelPath::ModelPath(const std::vector<QVector3D> &_pathData,
                                                const Material &_material,
                                                QObject *_parent)
    : GLModel(_material, _parent)
    , m_isInit(false)
    , m_pathData(_pathData)
    , m_memoryUsage(0U)
    , m_minimum()
    , m_maximum()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_linesCount(0)
{
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::Models::ModelPath::~ModelPath()
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
bool Universe1::OpenGL::Models::ModelPath::isInit() const
{
    return m_isInit;
}

/*!
 * \brief Returns size of allocated memory within OpenGL context
 * \returns Size of allocated memory within OpenGL context
 */
size_t Universe1::OpenGL::Models::ModelPath::memoryUsage() const
{
    return m_memoryUsage;
}

/*!
 * \brief Returns object range
 * \returns Object range (pair of 3D vectors minimum [x, y, z] and maximum [x, y, z])
 */
std::pair<QVector3D, QVector3D> Universe1::OpenGL::Models::ModelPath::range() const
{
    return {m_minimum, m_maximum};
}

/*!
 * \brief Rebuild buffers
 * \returns
 */
void Universe1::OpenGL::Models::ModelPath::rebuild()
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
    m_vertexBuffer.allocate(m_pathData.data(), m_pathData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    if (!m_pathData.empty())
    {
        m_minimum = m_pathData.front();
        m_maximum = m_minimum;
        for (const QVector3D &v : m_pathData)
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
    m_memoryUsage += m_pathData.size() * sizeof(QVector3D);

    std::vector<QVector3D> normalData;

    if (m_pathData.size() > 1U && !qFuzzyCompare(m_pathData[0], m_pathData[1]))
    {
        QVector3D lastNormal = (m_pathData[1] - m_pathData[0]).normalized();
        normalData.reserve(m_pathData.size());
        normalData.push_back(lastNormal);

        size_t lastID = 1;
        for (size_t i = 2; i < m_pathData.size(); ++i)
        {
            if (!qFuzzyCompare(m_pathData[i], m_pathData[lastID]))
            {
                lastNormal = (m_pathData[i] - m_pathData[lastID]).normalized();
                lastID = i;
            }
            normalData.push_back(lastNormal);
        }
        normalData.push_back(lastNormal);
    }
    else
    {
        normalData = std::vector<QVector3D>(m_pathData.size(), QVector3D(1.0F, 0.0F, 0.0F));
    }

    m_normalBuffer.bind();
    m_normalBuffer.allocate(normalData.data(), normalData.size() * sizeof(QVector3D));
    m_normalBuffer.release();
    m_memoryUsage += normalData.size() * sizeof(QVector3D);

    m_linesCount = m_pathData.size();

    m_isInit = true;
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::ModelPath::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 */
void Universe1::OpenGL::Models::ModelPath::paintGLImlp(ShaderProgram *_program)
{
    if (!m_isInit)
        return;

    _program->setupMaterial(m_material);

    m_vertexBuffer.bind();
    _program->enableAttributeArray(_program->attrVertex());
    _program->setAttributeBuffer(_program->attrVertex(), GL_FLOAT, 0, 3);

    m_normalBuffer.bind();
    _program->enableAttributeArray(_program->attrNormal());
    _program->setAttributeBuffer(_program->attrNormal(), GL_FLOAT, 0, 3);

    glDrawArrays(GL_LINE_STRIP, 0, m_linesCount);

    m_normalBuffer.release();
    m_vertexBuffer.release();
}

/*!
 * \brief Setter Path vertex data
 * \param _pathData New path vertices
 */
void Universe1::OpenGL::Models::ModelPath::setPath(const std::vector<QVector3D> &_pathData)
{
    m_pathData = _pathData;
    if (isInit())
        rebuild();
    emit changed();
}
