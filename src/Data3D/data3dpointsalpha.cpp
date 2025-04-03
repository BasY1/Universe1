/*!
 * \file src/Data3D/data3dpointsalpha.h
 * \brief Base Open GL point-cloud object
 */

#include "data3dpointsalpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsAlpha::vs =        //
    Data3D::VS_Header +                          //
    "layout (location = 1) in float alpha;\n" +  //
    Data3D::VS_Uniforms +                        //
    "uniform float pointSize;\n" +               //
    "out float alphaOut;\n" +                    //
    "void main() {\n" +                          //
    " alphaOut = alpha;\n" +                     //
    " gl_PointSize = pointSize;\n" +             //
    Data3D::VS_InMain +                          //
    "}\n";

const std::string Data3DPointsAlpha::fs =       //
    Data3D::GLSL_Version +                      //
    "uniform vec3 pointColor;\n" +              //
    "in float alphaOut;\n" +                    //
    "out vec4 color;\n" +                       //
    "void main() {\n" +                         //
    " color = vec4(pointColor, alphaOut);\n" +  //
    "}\n";

Data3DPointsAlpha::Data3DPointsAlpha(const size_t _vertexCount,
                                     const size_t _indexCount,
                                     const Math::ColorRGB &_color,
                                     const float _pointSize)
    : Data3D(GL_POINTS_Alpha, GL_POINTS, _vertexCount, _indexCount)
    , m_color(_color)
    , m_pointSize(_pointSize)
{
    if (vertexCount > 0UL)
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
}

Data3DPointsAlpha::Data3DPointsAlpha(const size_t _vertexCount,
                                     const size_t _indexCount,
                                     const Math::Vec3F *_vertexData,
                                     const float *_alphaData,
                                     const uint *_indexData,
                                     const Math::ColorRGB &_color,
                                     const float _pointSize)
    : Data3D(GL_POINTS_Alpha, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_color(_color)
    , m_pointSize(_pointSize)
{
    if (vertexCount > 0UL)
    {
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
            std::cerr << "[Data3DPointsAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

Data3DPointsAlpha::~Data3DPointsAlpha()
{
    if (m_alphaData != nullptr)
        std::free(m_alphaData);

    if (m_alphaBuffer != nullptr)
    {
        if (m_alphaBuffer->isCreated())
            m_alphaBuffer->destroy();
        delete m_alphaBuffer;
    }
}

bool Data3DPointsAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DPointsAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("pointColor", m_color.toQVec3());
    _program->setUniformValue("pointSize", m_pointSize);
    return true;
}

bool Data3DPointsAlpha::createBuffersImpl()
{
    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DPointsAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DPointsAlpha::destroyBuffersImpl()
{
    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DPointsAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DPointsAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DPointsAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_alphaBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
