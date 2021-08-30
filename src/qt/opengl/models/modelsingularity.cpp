/*!
 * \file qt/opengl/models/modelsingularity.cpp
 * \author Michal Steller
 * \brief Singularity model with material class implementation
 */

#include "modelsingularity.h"

/*!
 * \brief Constructor
 * \param _materialLineOut Initial material for lines outer vertex
 * \param _materialLineIn Initial material for lines inner vertex
 * \param _materialDot Initial material for dot
 * \param _position Initial position
 * \param _radius Initial radius
 * \param _ratioLine Initial line length ratio
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::ModelSingularity::ModelSingularity(const Material &_materialLineOut,
                                                              const Material &_materialLineIn,
                                                              const Material &_materialDot,
                                                              const QVector3D &_position,
                                                              const float _radius,
                                                              const float _ratioLine,
                                                              QObject *_parent)
    : GLModel({_materialLineOut, _materialLineIn, _materialDot}, _parent)
    , m_isInit(false)
    , m_position(_position)
    , m_radius(_radius)
    , m_ratioLine(_ratioLine)
    , m_vertexBuffer()
    , m_normalBuffer()
    , m_materialBuffer()
{
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::Models::ModelSingularity::~ModelSingularity()
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
bool Universe1::OpenGL::Models::ModelSingularity::isInit() const
{
    return m_isInit;
}

/*!
 * \brief Setter for singularity position
 * \param _value New singularity position
 */
void Universe1::OpenGL::Models::ModelSingularity::setPosition(const QVector3D &_value)
{
    m_position = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for singularity radius
 * \param _value New singularity radius
 */
void Universe1::OpenGL::Models::ModelSingularity::setRadius(float _value)
{
    m_radius = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for singularity line length ratio
 * \param _value New singularity line length ratio
 */
void Universe1::OpenGL::Models::ModelSingularity::setRatioLine(float _value)
{
    m_ratioLine = _value;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Setter for singularity model
 * \param _position New singularity position
 * \param _radius New singularity radius
 * \param _ratioLine New singularity line length ratio
 */
void Universe1::OpenGL::Models::ModelSingularity::setup(const QVector3D &_position,
                                                        const float _radius,
                                                        const float _ratioLine)
{
    m_position = _position;
    m_radius = _radius;
    m_ratioLine = _ratioLine;
    if (isInit())
        rebuild();
    emit changed();
}

/*!
 * \brief Rebuild model
 */
void Universe1::OpenGL::Models::ModelSingularity::rebuild()
{
    static const std::vector<float> materialData = {
        0.1F, 1.1F, 0.1F, 1.1F, 0.1F, 1.1F, 0.1F, 1.1F, 0.1F, 1.1F, 0.1F, 1.1F, 2.1F};

    static const std::vector<QVector3D> normalData = {QVector3D(1.0F, 0.0F, 0.0F),
                                                      QVector3D(-1.0F, 0.0F, 0.0F),
                                                      QVector3D(-1.0F, 0.0F, 0.0F),
                                                      QVector3D(1.0F, 0.0F, 0.0F),
                                                      QVector3D(0.0F, 1.0F, 0.0F),
                                                      QVector3D(0.0F, -1.0F, 0.0F),
                                                      QVector3D(0.0F, -1.0F, 0.0F),
                                                      QVector3D(0.0F, 1.0F, 0.0F),
                                                      QVector3D(0.0F, 0.0F, 1.0F),
                                                      QVector3D(0.0F, 0.0F, -1.0F),
                                                      QVector3D(0.0F, 0.0F, -1.0F),
                                                      QVector3D(0.0F, 0.0F, 1.0F),
                                                      QVector3D(0.0F, 0.0F, 1.0F)};

    const float offset = m_radius * (1.0F - m_ratioLine);
    const std::vector<QVector3D> vertexData = {QVector3D(m_position.x() + m_radius, m_position.y(), m_position.z()),
                                               QVector3D(m_position.x() + offset, m_position.y(), m_position.z()),
                                               QVector3D(m_position.x() - m_radius, m_position.y(), m_position.z()),
                                               QVector3D(m_position.x() - offset, m_position.y(), m_position.z()),
                                               QVector3D(m_position.x(), m_position.y() + m_radius, m_position.z()),
                                               QVector3D(m_position.x(), m_position.y() + offset, m_position.z()),
                                               QVector3D(m_position.x(), m_position.y() - m_radius, m_position.z()),
                                               QVector3D(m_position.x(), m_position.y() - offset, m_position.z()),
                                               QVector3D(m_position.x(), m_position.y(), m_position.z() + m_radius),
                                               QVector3D(m_position.x(), m_position.y(), m_position.z() + offset),
                                               QVector3D(m_position.x(), m_position.y(), m_position.z() - m_radius),
                                               QVector3D(m_position.x(), m_position.y(), m_position.z() - offset),
                                               m_position};

    m_isInit = false;
    m_memoryUsage = 0U;
    clearRange();

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
    m_vertexBuffer.allocate(vertexData.data(), vertexData.size() * sizeof(QVector3D));
    m_vertexBuffer.release();
    prepareRange(vertexData);
    m_memoryUsage += vertexData.size() * sizeof(QVector3D);

    m_normalBuffer.bind();
    m_normalBuffer.allocate(normalData.data(), normalData.size() * sizeof(QVector3D));
    m_normalBuffer.release();
    m_memoryUsage += normalData.size() * sizeof(QVector3D);

    m_materialBuffer.bind();
    m_materialBuffer.allocate(materialData.data(), materialData.size() * sizeof(float));
    m_materialBuffer.release();
    m_memoryUsage += materialData.size() * sizeof(float);

    m_isInit = true;
}

/*!
 * \brief Initialize Open GL
 */
void Universe1::OpenGL::Models::ModelSingularity::initGLImlp()
{
    rebuild();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 */
void Universe1::OpenGL::Models::ModelSingularity::paintGLImlp(ShaderProgram *_program)
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

    glDrawArrays(GL_LINES, 0, 12);
    glDrawArrays(GL_POINTS, 12, 1);

    m_materialBuffer.release();
    m_normalBuffer.release();
    m_vertexBuffer.release();
}
