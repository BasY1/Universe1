/*!
 * \file qt/opengl/models/modelpath.cpp
 * \author Michal Steller
 * \brief Base Open GL line path model with material class implementation
 */

#include "modelpath.h"

/*!
 * \brief Constructor
 * \param _materials Initial materials
 * \param _vertexData Initial vertex positions
 * \param _normalData Initial vertex normals
 * \param _materialData Initial vertex materials
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelPath::ModelPath(const std::vector<Material> &_materials,
                                                const std::vector<QVector3D> &_vertexData,
                                                const std::vector<QVector3D> &_normalData,
                                                const std::vector<uint8_t> &_materialData,
                                                QObject *_parent)
    : GLModel(_materials, _parent)
    , m_vertexData(_vertexData)
    , m_normalData()
    , m_materialData()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_materialBuffer()
    , m_linesCount(0)
{
    if (_normalData.size() == m_vertexData.size())
        m_normalData = _normalData;

    if (_materialData.size() == m_vertexData.size())
        m_materialData = _materialData;
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
    if (m_materialBuffer.isCreated())
        m_materialBuffer.destroy();
}

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
bool Universe1::OpenGL::Models::ModelPath::isInit() const
{
    return m_vertexBuffer.isCreated();
}

/*!
 * \brief Rebuild buffers
 * \returns
 */
void Universe1::OpenGL::Models::ModelPath::rebuild()
{
    clearRange();
    m_memoryUsage = 0U;
    m_linesCount = 0;

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

    if (!m_materialBuffer.isCreated())
    {
        if (!m_materialBuffer.create())
            return;
    }

    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertexData.data(), m_vertexData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    prepareRange(m_vertexData);
    m_memoryUsage += m_vertexData.size() * sizeof(QVector3D);

    if (m_normalData.empty())
    {
        std::vector<QVector3D> normalData;
        if (m_vertexData.size() > 1U && !qFuzzyCompare(m_vertexData[0], m_vertexData[1]))
        {
            QVector3D lastNormal = (m_vertexData[1] - m_vertexData[0]).normalized();
            normalData.reserve(m_vertexData.size());
            normalData.push_back(lastNormal);

            size_t lastID = 1;
            for (size_t i = 2; i < m_vertexData.size(); ++i)
            {
                if (!qFuzzyCompare(m_vertexData[i], m_vertexData[lastID]))
                {
                    lastNormal = (m_vertexData[i] - m_vertexData[lastID]).normalized();
                    lastID = i;
                }
                normalData.push_back(lastNormal);
            }
            normalData.push_back(lastNormal);
        }
        else
        {
            normalData = std::vector<QVector3D>(m_vertexData.size(), QVector3D(1.0F, 0.0F, 0.0F));
        }

        m_normalBuffer.bind();
        m_normalBuffer.allocate(normalData.data(), normalData.size() * sizeof(QVector3D));
        m_normalBuffer.release();
        m_memoryUsage += normalData.size() * sizeof(QVector3D);
    }
    else
    {
        m_normalBuffer.bind();
        m_normalBuffer.allocate(m_normalData.data(), m_normalData.size() * sizeof(QVector3D));
        m_normalBuffer.release();
        m_memoryUsage += m_normalData.size() * sizeof(QVector3D);
    }

    if (m_materialData.empty())
    {
        const std::vector<float> materialData(m_vertexData.size(), 0.1F);
        m_materialBuffer.bind();
        m_materialBuffer.allocate(materialData.data(), materialData.size() * sizeof(float));
        m_materialBuffer.release();
        m_memoryUsage += materialData.size() * sizeof(float);
    }
    else
    {
        std::vector<float> materialData;
        materialData.reserve(m_materialData.size());
        for (const uint8_t md : m_materialData)
            materialData.push_back(static_cast<float>(md) + 0.1F);

        m_materialBuffer.bind();
        m_materialBuffer.allocate(m_materialData.data(), m_materialData.size() * sizeof(float));
        m_materialBuffer.release();
        m_memoryUsage += m_materialData.size() * sizeof(float);
    }

    m_linesCount = m_vertexData.size();
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
    m_vertexBuffer.bind();
    _program->enableAttributeArray(_program->attrVertex());
    _program->setAttributeBuffer(_program->attrVertex(), GL_FLOAT, 0, 3);

    m_normalBuffer.bind();
    _program->enableAttributeArray(_program->attrNormal());
    _program->setAttributeBuffer(_program->attrNormal(), GL_FLOAT, 0, 3);

    m_materialBuffer.bind();
    _program->enableAttributeArray(_program->attrMaterial());
    _program->setAttributeBuffer(_program->attrMaterial(), GL_UNSIGNED_BYTE, 0, 1);

    glDrawArrays(GL_LINE_STRIP, 0, m_linesCount);

    m_materialBuffer.release();
    m_normalBuffer.release();
    m_vertexBuffer.release();
}

/*!
 * \brief Setup path data
 * \param _vertexData New vertex positions
 * \param _normalData New vertex normals
 * \param _materialData New vertex materials
 */
void Universe1::OpenGL::Models::ModelPath::setPath(const std::vector<QVector3D> &_vertexData,
                                                   const std::vector<QVector3D> &_normalData,
                                                   const std::vector<uint8_t> &_materialData)
{
    m_vertexData = _vertexData;

    if (_normalData.size() == m_vertexData.size())
        m_normalData = _normalData;
    else
        m_normalData.clear();

    if (_materialData.size() == m_vertexData.size())
        m_materialData = _materialData;
    else
        m_materialData.clear();

    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setup path data
 * \param _vertexData New vertex positions
 * \param _materialData New vertex materials
 */
void Universe1::OpenGL::Models::ModelPath::setPath(const std::vector<QVector3D> &_vertexData,
                                                   const std::vector<uint8_t> &_materialData)
{
    setPath(_vertexData, {}, _materialData);
}

/*!
 * \brief Setup path data
 * \param _vertexData New vertex positions
 * \param _normalData New vertex normals
 */
void Universe1::OpenGL::Models::ModelPath::setPath(const std::vector<QVector3D> &_vertexData,
                                                   const std::vector<QVector3D> &_normalData)
{
    setPath(_vertexData, _normalData, {});
}

/*!
 * \brief Setup path data
 * \param _vertexData New vertex positions
 */
void Universe1::OpenGL::Models::ModelPath::setPath(const std::vector<QVector3D> &_vertexData)
{
    setPath(_vertexData, {}, {});
}
