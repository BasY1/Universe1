/*!
 * \file src/Data3D/data3dpointssize.h
 * \brief Open GL point-cloud object with per vertex point size
 */

#include "data3dpointssize.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsSize::vs =              //
    Data3D::VS_Header +                               //
    "layout (location = 1) in float pointSize; \n" +  //
    Data3D::VS_Uniforms +                             //
    "void main() {\n" +                               //
    " gl_PointSize = pointSize;\n" +                  //
    Data3D::VS_InMain +                               //
    "}\n";

const std::string Data3DPointsSize::fs =     //
    Data3D::GLSL_Version +                   //
    "uniform vec3 pointColor;\n" +           //
    "uniform float alpha;\n" +               //
    "out vec4 color;\n" +                    //
    "void main() {\n" +                      //
    " color = vec4(pointColor, alpha);\n" +  //
    "}\n";

Data3DPointsSize::Data3DPointsSize(const size_t _vertexCount,
                                   const size_t _indexCount,
                                   const Math::ColorRGB &_color,
                                   const uint8_t _alpha)
    : Data3D(GL_POINTS_Size, GL_POINTS, _vertexCount, _indexCount)
    , m_color(_color)
    , m_alpha(_alpha)
{
    if (vertexCount > 0UL)
        m_pointSizeData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
}

Data3DPointsSize::Data3DPointsSize(const size_t _vertexCount,
                                   const size_t _indexCount,
                                   const Math::Vec3F *_vertexData,
                                   const float *_pointSizeData,
                                   const uint *_indexData,
                                   const Math::ColorRGB &_color,
                                   const uint8_t _alpha)
    : Data3D(GL_POINTS_Size, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_color(_color)
    , m_alpha(_alpha)
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
            std::cerr << "[Data3DPointsSize::constructor] Can't create m_pointSizeBuffer !\n";
        }
    }
}

Data3DPointsSize::~Data3DPointsSize()
{
    if (m_pointSizeData != nullptr)
        std::free(m_pointSizeData);

    if (m_pointSizeBuffer != nullptr)
    {
        if (m_pointSizeBuffer->isCreated())
            m_pointSizeBuffer->destroy();
        delete m_pointSizeBuffer;
    }
}

bool Data3DPointsSize::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DPointsSize::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("pointColor", m_color.toQVec3());
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DPointsSize::createBuffersImpl()
{
    m_pointSizeBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_pointSizeBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_pointSizeBuffer->create())
    {
        std::cerr << "[Data3DPointsSize::createBuffersImpl] Can't create m_pointSizeBuffer !\n";
        return false;
    }

    m_pointSizeBuffer->bind();
    m_pointSizeBuffer->allocate(m_pointSizeData, vertexCount * sizeof(float));
    m_pointSizeBuffer->release();

    return true;
}

bool Data3DPointsSize::destroyBuffersImpl()
{
    if (m_pointSizeBuffer->isCreated())
        m_pointSizeBuffer->destroy();

    delete m_pointSizeBuffer;
    m_pointSizeBuffer = nullptr;

    return true;
}

bool Data3DPointsSize::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_pointSizeBuffer->bind())
    {
        std::cerr << "[Data3DPointsSize::bindBuffersImpl] m_pointSizeBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DPointsSize::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_pointSizeBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
