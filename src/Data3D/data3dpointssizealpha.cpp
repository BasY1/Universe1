/*!
 * \file src/Data3D/data3dpointssizealpha.h
 * \brief Open GL point-cloud object with per vertex point size and alpha
 */

#include "data3dpointssizealpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsSizeAlpha::vs =         //
    Data3D::VS_Header +                               //
    "layout (location = 1) in float pointSize; \n" +  //
    "layout (location = 2) in float alpha; \n" +      //
    Data3D::VS_Uniforms +                             //
    "out float alphaOut;\n" +                         //
    "void main() {\n" +                               //
    " alphaOut = alpha;\n" +                          //
    " gl_PointSize = pointSize;\n" +                  //
    Data3D::VS_InMain +                               //
    "}\n";

const std::string Data3DPointsSizeAlpha::fs =   //
    Data3D::GLSL_Version +                      //
    "uniform vec3 pointColor;\n" +              //
    "in float alphaOut;\n" +                    //
    "out vec4 color;\n" +                       //
    "void main() {\n" +                         //
    " color = vec4(pointColor, alphaOut);\n" +  //
    "}\n";

Data3DPointsSizeAlpha::Data3DPointsSizeAlpha(const size_t _vertexCount,
                                             const size_t _indexCount,
                                             const Math::ColorRGB &_color)
    : Data3D(GL_POINTS_SizeAlpha, GL_POINTS, _vertexCount, _indexCount)
    , m_color(_color)
{
    if (vertexCount > 0UL)
    {
        m_pointSizeData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DPointsSizeAlpha::Data3DPointsSizeAlpha(const size_t _vertexCount,
                                             const size_t _indexCount,
                                             const Math::Vec3F *_vertexData,
                                             const float *_pointSizeData,
                                             const float *_alphaData,
                                             const uint *_indexData,
                                             const Math::ColorRGB &_color)
    : Data3D(GL_POINTS_SizeAlpha, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_color(_color)
{
    if (vertexCount > 0UL)
    {
        m_pointSizeBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_pointSizeBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_pointSizeBuffer->create())
        {
            m_pointSizeBuffer->bind();
            m_pointSizeBuffer->allocate(_pointSizeData, vertexCount * sizeof(float));
            m_pointSizeBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DPointsSizeAlpha::constructor] Can't create m_pointSizeBuffer !\n";
        }

        m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_alphaBuffer->create())
        {
            m_alphaBuffer->bind();
            m_alphaBuffer->allocate(_alphaData, vertexCount * sizeof(float));
            m_alphaBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DPointsSizeAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

bool Data3DPointsSizeAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DPointsSizeAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("pointColor", m_color.toQVec3());
    return true;
}

bool Data3DPointsSizeAlpha::createBuffersImpl()
{
    m_pointSizeBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_pointSizeBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_pointSizeBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeAlpha::createBuffersImpl] Can't create m_pointSizeBuffer !\n";
        return false;
    }

    m_pointSizeBuffer->bind();
    m_pointSizeBuffer->allocate(m_pointSizeData, vertexCount * sizeof(float));
    m_pointSizeBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DPointsSizeAlpha::destroyBuffersImpl()
{
    if (m_pointSizeBuffer->isCreated())
        m_pointSizeBuffer->destroy();

    delete m_pointSizeBuffer;
    m_pointSizeBuffer = nullptr;

    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DPointsSizeAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_pointSizeBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeAlpha::bindBuffersImpl] m_pointSizeBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DPointsSizeAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    m_pointSizeBuffer->release();
    m_alphaBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
