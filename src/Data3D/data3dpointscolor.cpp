/*!
 * \file src/Data3D/data3dpointscolor.h
 * \brief Base Open GL point-cloud object
 */

#include "data3dpointscolor.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsColor::vs =       //
    Data3D::VS_Header +                         //
    "layout (location = 1) in vec3 color;\n" +  //
    Data3D::VS_Uniforms +                       //
    "uniform float pointSize;\n" +              //
    "out vec3 colorOut;\n" +                    //
    "void main() {\n" +                         //
    " colorOut = color;\n" +                    //
    " gl_PointSize = pointSize;\n" +            //
    Data3D::VS_InMain +                         //
    "}\n";

const std::string Data3DPointsColor::fs =  //
    Data3D::GLSL_Version +                 //
    "uniform float alpha;\n" +             //
    "in vec3 colorOut;\n" +                //
    "out vec4 color;\n" +                  //
    "void main() {\n" +                    //
    " color = vec4(colorOut, alpha);\n" +  //
    "}\n";

Data3DPointsColor::Data3DPointsColor(const size_t _vertexCount,
                                     const size_t _indexCount,
                                     const uint8_t _alpha,
                                     const float _pointSize)
    : Data3D(GL_POINTS_Color, GL_POINTS, _vertexCount, _indexCount)
    , m_alpha(_alpha)
    , m_pointSize(_pointSize)
{
    if (vertexCount > 0UL)
        m_colorData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
}

Data3DPointsColor::Data3DPointsColor(const size_t _vertexCount,
                                     const size_t _indexCount,
                                     const Math::Vec3F *_vertexData,
                                     const Math::Vec3F *_colorData,
                                     const uint *_indexData,
                                     const uint8_t _alpha,
                                     const float _pointSize)
    : Data3D(GL_POINTS_Color, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_alpha(_alpha)
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
    }
}

bool Data3DPointsColor::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DPointsColor::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
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

    return true;
}

bool Data3DPointsColor::destroyBuffersImpl()
{
    if (m_colorBuffer->isCreated())
        m_colorBuffer->destroy();

    delete m_colorBuffer;
    m_colorBuffer = nullptr;

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

    return true;
}

bool Data3DPointsColor::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_colorBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
