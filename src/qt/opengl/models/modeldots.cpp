/*!
 * \file qt/opengl/models/modeldots.cpp
 * \author Michal Steller
 * \brief Open GL dots point-cloud model with material class implementation
 */

#include "modeldots.h"

/*!
 * \brief Constructor
 * \param _materials Initial materials
 * \param _vertexData Initial vertex positions
 * \param _normalData Initial vertex normals
 * \param _materialData Initial vertex materials
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelDots::ModelDots(const std::vector<Material> &_materials,
                                                const std::vector<QVector3D> &_vertexData,
                                                const std::vector<QVector3D> &_normalData,
                                                const std::vector<uint8_t> &_materialData,
                                                QObject *_parent)
    : GLModel(_materials, _parent)
    , m_vertexData(_vertexData)
    , m_normalData()
    , m_normalSingle()
    , m_materialData()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_materialBuffer()
    , m_dotsCount(0)
{
    if (_normalData.size() == m_vertexData.size())
        m_normalData = _normalData;
    else
        m_normalSingle = QVector3D(0.0F, 0.0F, 1.0F);

    if (_materialData.size() == m_vertexData.size())
        m_materialData = _materialData;
}

/*!
 * \brief Constructor
 * \param _materials Initial materials
 * \param _vertexData Initial vertex positions
 * \param _normalSingle Initial single normal
 * \param _materialData Initial vertex materials
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelDots::ModelDots(const std::vector<Material> &_materials,
                                                const std::vector<QVector3D> &_vertexData,
                                                const QVector3D &_normalSingle,
                                                const std::vector<uint8_t> &_materialData,
                                                QObject *_parent)
    : GLModel(_materials, _parent)
    , m_vertexData(_vertexData)
    , m_normalData()
    , m_normalSingle(qFuzzyCompare(QVector3D(), _normalSingle) ? QVector3D(0.0F, 0.0F, 1.0F)
                                                               : _normalSingle.normalized())
    , m_materialData()
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_materialBuffer()
    , m_dotsCount(0)
{
    if (_materialData.size() == m_vertexData.size())
        m_materialData = _materialData;
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
    if (m_materialBuffer.isCreated())
        m_materialBuffer.destroy();
}

/*!
 * \brief Getter for OpenGL buffers initialized flag
 * \returns OpenGL buffers initialized flag
 */
bool Universe1::OpenGL::Models::ModelDots::isInit() const
{
    return m_vertexBuffer.isCreated();
}

/*!
 * \brief Rebuild buffers
 * \returns
 */
void Universe1::OpenGL::Models::ModelDots::rebuild()
{
    clearRange();
    m_memoryUsage = 0U;
    m_dotsCount = 0;

    if (!m_vertexBuffer.isCreated())
    {
        if (m_vertexBuffer.create())
        {
            if (!m_normalBuffer.create())
            {
                m_vertexBuffer.destroy();
                return;
            }
            if (!m_materialBuffer.create())
            {
                m_vertexBuffer.destroy();
                m_normalBuffer.destroy();
                return;
            }
        }
        else
        {
            return;
        }
    }

    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertexData.data(), m_vertexData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    prepareRange(m_vertexData);
    m_memoryUsage += m_vertexData.size() * sizeof(QVector3D);

    if (m_normalData.empty())
    {
        const std::vector<QVector3D> normalData(m_vertexData.size(), m_normalSingle);
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

    m_dotsCount = m_vertexData.size();
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

    m_materialBuffer.bind();
    _program->enableAttributeArray(_program->attrMaterial());
    _program->setAttributeBuffer(_program->attrMaterial(), GL_FLOAT, 0, 1);

    glDrawArrays(GL_POINTS, 0, m_dotsCount);

    m_materialBuffer.release();
    m_normalBuffer.release();
    m_vertexBuffer.release();
}

/*!
 * \brief Setup dots data
 * \param _vertexData New vertex positions
 * \param _normalData New vertex normals
 * \param _materialData New vertex materials
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_vertexData,
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
 * \brief Setup dots data
 * \param _vertexData New vertex positions
 * \param _materialData New vertex materials
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_vertexData,
                                                   const std::vector<uint8_t> &_materialData)
{
    m_vertexData = _vertexData;

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
 * \brief Setup dots data
 * \param _vertexData New vertex positions
 * \param _normalData New vertex normals
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_vertexData,
                                                   const std::vector<QVector3D> &_normalData)
{
    m_vertexData = _vertexData;

    if (_normalData.size() == m_vertexData.size())
        m_normalData = _normalData;
    else
        m_normalData.clear();

    m_materialData.clear();

    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setup dots data
 * \param _vertexData New vertex positions
 * \param _normalSingle New single normal
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_vertexData,
                                                   const QVector3D &_normalSingle)
{
    m_vertexData = _vertexData;

    m_normalData.clear();
    m_normalSingle =
        qFuzzyCompare(QVector3D(), _normalSingle) ? QVector3D(0.0F, 0.0F, 1.0F) : _normalSingle.normalized();

    m_materialData.clear();

    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setup dots data
 * \param _vertexData New vertex positions
 */
void Universe1::OpenGL::Models::ModelDots::setDots(const std::vector<QVector3D> &_vertexData)
{
    m_vertexData = _vertexData;
    m_normalData.clear();
    m_materialData.clear();

    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setup dots in X-Y plane
 * \param minX Minimum X
 * \param minY Minimum Y
 * \param maxX Maximum X
 * \param maxY Maximum Y
 */
void Universe1::OpenGL::Models::ModelDots::setPlaneXY(const int minX, const int minY, const int maxX, const int maxY)
{
    m_vertexData.clear();
    m_normalData.clear();
    m_materialData.clear();

    if (minX <= maxX && minY <= maxY)
    {
        m_vertexData.reserve((maxX - minX + 1) * (maxY - minY + 1));
        for (int x = minX; x <= maxX; ++x)
            for (int y = minY; y <= maxY; ++y)
                m_vertexData.push_back(QVector3D(x, y, 0.0F));
    }

    if (isInit())
        rebuild();
    emit changed();
}
