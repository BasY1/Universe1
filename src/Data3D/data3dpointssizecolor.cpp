/*!
 * \file src/Data3D/data3dpointssizecolor.h
 * \brief Open GL point-cloud object with per vertex point size and color
 */

#include "data3dpointssizecolor.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsSizeColor::vs =         //
    Data3D::VS_Header +                               //
    "layout (location = 1) in float pointSize; \n" +  //
    "layout (location = 2) in vec3 color; \n" +       //
    Data3D::VS_Uniforms +                             //
    "out vec3 colorOut;\n" +                          //
    "void main() {\n" +                               //
    " colorOut = color;\n" +                          //
    " gl_PointSize = pointSize;\n" +                  //
    Data3D::VS_InMain +                               //
    "}\n";

const std::string Data3DPointsSizeColor::fs =  //
    Data3D::GLSL_Version +                     //
    "uniform float alpha;\n" +                 //
    "in vec3 colorOut;\n" +                    //
    "out vec4 color;\n" +                      //
    "void main() {\n" +                        //
    " color = vec4(colorOut, alpha);\n" +      //
    "}\n";

Data3DPointsSizeColor::Data3DPointsSizeColor(const size_t _vertexCount, const size_t _indexCount, const uint8_t _alpha)
    : Data3D(GL_POINTS_SizeColor, GL_POINTS, _vertexCount, _indexCount)
    , m_alpha(_alpha)
{
    if (vertexCount > 0UL)
    {
        m_pointSizeData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
        m_colorData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
    }
}

Data3DPointsSizeColor::Data3DPointsSizeColor(const size_t _vertexCount,
                                             const size_t _indexCount,
                                             const Math::Vec3F *_vertexData,
                                             const Math::Vec3F *_colorData,
                                             const float *_pointSizeData,
                                             const uint *_indexData,
                                             const uint8_t _alpha)
    : Data3D(GL_POINTS_SizeColor, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
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
            std::cerr << "[Data3DPointsSizeColor::constructor] Can't create m_pointSizeBuffer !\n";
        }

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
            std::cerr << "[Data3DPointsSizeColor::constructor] Can't create m_colorBuffer !\n";
        }
    }
}

Data3DPointsSizeColor::~Data3DPointsSizeColor()
{
    if (m_pointSizeData != nullptr)
        std::free(m_pointSizeData);
    if (m_colorData != nullptr)
        std::free(m_colorData);

    if (m_pointSizeBuffer != nullptr)
    {
        if (m_pointSizeBuffer->isCreated())
            m_pointSizeBuffer->destroy();
        delete m_pointSizeBuffer;
    }

    if (m_colorBuffer != nullptr)
    {
        if (m_colorBuffer->isCreated())
            m_colorBuffer->destroy();
        delete m_colorBuffer;
    }
}

bool Data3DPointsSizeColor::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DPointsSizeColor::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    glEnable(GL_PROGRAM_POINT_SIZE);
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DPointsSizeColor::createBuffersImpl()
{
    m_pointSizeBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_pointSizeBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_pointSizeBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeColor::createBuffersImpl] Can't create m_pointSizeBuffer !\n";
        return false;
    }

    m_pointSizeBuffer->bind();
    m_pointSizeBuffer->allocate(m_pointSizeData, vertexCount * sizeof(float));
    m_pointSizeBuffer->release();

    m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_colorBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_colorBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeColor::createBuffersImpl] Can't create m_colorBuffer !\n";
        return false;
    }

    m_colorBuffer->bind();
    m_colorBuffer->allocate(m_colorData, vertexCount * sizeof(Math::Vec3F));
    m_colorBuffer->release();

    return true;
}

bool Data3DPointsSizeColor::destroyBuffersImpl()
{
    if (m_pointSizeBuffer->isCreated())
        m_pointSizeBuffer->destroy();

    delete m_pointSizeBuffer;
    m_pointSizeBuffer = nullptr;

    if (m_colorBuffer->isCreated())
        m_colorBuffer->destroy();

    delete m_colorBuffer;
    m_colorBuffer = nullptr;

    return true;
}

bool Data3DPointsSizeColor::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_pointSizeBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeColor::bindBuffersImpl] m_pointSizeBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    if (!m_colorBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeColor::bindBuffersImpl] m_colorBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 3);

    return true;
}

bool Data3DPointsSizeColor::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    m_pointSizeBuffer->release();
    m_colorBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
