/*!
 * \file src/Data3D/data3dpointscoloralpha.h
 * \brief Base Open GL point-cloud object and alpha
 */

#include "data3dpointscoloralpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsColor::vs =        //
    Data3D::VS_Header +                          //
    "layout (location = 1) in vec3 color;\n" +   //
    "layout (location = 2) in float alpha;\n" +  //
    Data3D::VS_Uniforms +                        //
    "uniform float pointSize;\n" +               //
    "out vec3 colorOut;\n" +                     //
    "out float alphaOut;\n" +                    //
    "void main() {\n" +                          //
    " colorOut = color;\n" +                     //
    " alphaOut = alpha;\n" +                     //
    " gl_PointSize = pointSize;\n" +             //
    Data3D::VS_InMain +                          //
    "}\n";

const std::string Data3DPointsColor::fs =     //
    Data3D::GLSL_Version +                    //
    "in vec3 colorOut;\n" +                   //
    "in float alphaOut;\n" +                  //
    "out vec4 color;\n" +                     //
    "void main() {\n" +                       //
    " color = vec4(colorOut, alphaOut);\n" +  //
    "}\n";

Data3DPointsColor::Data3DPointsColor(const size_t _vertexCount, const size_t _indexCount, const float _pointSize)
    : Data3D(GL_POINTS_ColorAlpha, GL_POINTS, _vertexCount, _indexCount)
    , m_pointSize(_pointSize)
{
    if (vertexCount > 0UL)
    {
        m_colorData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DPointsColor::Data3DPointsColor(const size_t _vertexCount,
                                     const size_t _indexCount,
                                     const Math::Vec3F *_vertexData,
                                     const Math::Vec3F *_colorData,
                                     const float *_alphaData,
                                     const uint *_indexData,
                                     const float _pointSize)
    : Data3D(GL_POINTS_ColorAlpha, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_pointSize(_pointSize)
{
    if (vertexCount > 0UL)
    {
        m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_colorBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_colorBuffer->create())
        {
            m_colorBuffer->bind();
            m_colorBuffer->allocate(_colorData, vertexCount * sizeof(Math::Vec3F));
            m_colorBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DPointsColor::constructor] Can't create m_colorBuffer !\n";
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
            std::cerr << "[Data3DPointsColor::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

bool Data3DPointsColor::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DPointsColor::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("pointSize", m_pointSize);
    return true;
}

bool Data3DPointsColor::createBuffersImpl()
{
    m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_colorBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_colorBuffer->create())
    {
        std::cerr << "[Data3DPointsColor::createBuffersImpl] Can't create m_colorBuffer !\n";
        return false;
    }

    m_colorBuffer->bind();
    m_colorBuffer->allocate(m_colorData, vertexCount * sizeof(Math::Vec3F));
    m_colorBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DPointsColor::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DPointsColor::destroyBuffersImpl()
{
    if (m_colorBuffer->isCreated())
        m_colorBuffer->destroy();

    delete m_colorBuffer;
    m_colorBuffer = nullptr;

    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DPointsColor::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_colorBuffer->bind())
    {
        std::cerr << "[Data3DPointsColor::bindBuffersImpl] m_colorBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DPointsColor::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DPointsColor::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    m_colorBuffer->release();
    m_alphaBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
