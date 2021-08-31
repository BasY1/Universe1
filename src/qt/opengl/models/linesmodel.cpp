/*!
 * \file qt/opengl/models/linesmodel.cpp
 * \author Michal Steller
 * \brief Base Open GL lines model with material class implementation
 */

#include "linesmodel.h"

/*!
 * \brief Constructor
 * \param _materials Initial materials collection
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::LinesModel::LinesModel(const std::vector<Material> &_materials, QObject *_parent)
    : GLModel(_materials, _parent)
    , m_hasIndexes(false)
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_materialBuffer()
    , m_linesIndexes(QOpenGLBuffer::IndexBuffer)
    , m_linesCount(0)
{
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::Models::LinesModel::~LinesModel()
{
    if (m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if (m_normalBuffer.isCreated())
        m_normalBuffer.destroy();
    if (m_materialBuffer.isCreated())
        m_materialBuffer.destroy();
    if (m_linesIndexes.isCreated())
        m_linesIndexes.destroy();
}

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
bool Universe1::OpenGL::Models::LinesModel::isInit() const
{
    return m_vertexBuffer.isCreated();
}

/*!
 * \brief Initialize buffers
 * \param _vertexData Vertex buffer
 * \param _normalData Normal buffer
 * \param _materialData material buffer
 * \param _linesData Line index buffer
 * \returns Success flag
 */
bool Universe1::OpenGL::Models::LinesModel::initBuffers(const std::vector<QVector3D> &_vertexData,
                                                        const std::vector<QVector3D> &_normalData,
                                                        const std::vector<uint8_t> &_materialData,
                                                        const std::vector<uint> &_linesData)
{
    m_linesCount = 0;
    clearRange();
    m_memoryUsage = 0U;

    m_hasIndexes = !_linesData.empty();

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

    if (!m_materialBuffer.isCreated())
    {
        if (!m_materialBuffer.create())
            return false;
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
    prepareRange(_vertexData);
    m_memoryUsage += _vertexData.size() * sizeof(QVector3D);

    m_normalBuffer.bind();
    m_normalBuffer.allocate(_normalData.data(), _normalData.size() * sizeof(QVector3D));
    m_normalBuffer.release();
    m_memoryUsage += _normalData.size() * sizeof(QVector3D);

    if (_materialData.empty())
    {
        const std::vector<float> materialData(_vertexData.size(), 0.1F);
        m_materialBuffer.bind();
        m_materialBuffer.allocate(materialData.data(), materialData.size() * sizeof(float));
        m_materialBuffer.release();
        m_memoryUsage += materialData.size() * sizeof(float);
    }
    else
    {
        std::vector<float> materialData;
        materialData.reserve(_vertexData.size());
        for (const uint8_t md : _materialData)
            materialData.push_back(static_cast<float>(md) + 0.1F);

        m_materialBuffer.bind();
        m_materialBuffer.allocate(materialData.data(), materialData.size() * sizeof(float));
        m_materialBuffer.release();
        m_memoryUsage += materialData.size() * sizeof(float);
    }

    if (m_hasIndexes)
    {
        m_linesIndexes.bind();
        m_linesIndexes.allocate(_linesData.data(), _linesData.size() * sizeof(uint));
        m_linesIndexes.release();
        m_memoryUsage += _linesData.size() * sizeof(uint);
        m_linesCount = _linesData.size();
    }
    else
    {
        m_linesCount = _vertexData.size();
    }

    return true;
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::LinesModel::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 */
void Universe1::OpenGL::Models::LinesModel::paintGLImlp(ShaderProgram *_program)
{
    m_vertexBuffer.bind();
    _program->enableAttributeArray(_program->attrVertex());
    _program->setAttributeBuffer(_program->attrVertex(), GL_FLOAT, 0, 3);

    m_normalBuffer.bind();
    _program->enableAttributeArray(_program->attrNormal());
    _program->setAttributeBuffer(_program->attrNormal(), GL_FLOAT, 0, 3);

    m_materialBuffer.bind();
    _program->enableAttributeArray(_program->attrMaterial());
    _program->setAttributeBuffer(_program->attrMaterial(), GL_FLOAT, 0, 1);

    if (m_hasIndexes)
    {
        m_linesIndexes.bind();
        glDrawElements(GL_LINES, m_linesCount, GL_UNSIGNED_INT, nullptr);
        m_linesIndexes.release();
    }
    else
    {
        glDrawArrays(GL_LINES, 0, m_linesCount);
    }

    m_materialBuffer.release();
    m_normalBuffer.release();
    m_vertexBuffer.release();
}
