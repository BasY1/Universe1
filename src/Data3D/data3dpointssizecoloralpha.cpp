/*!
 * \file src/Data3D/data3dpointssizecoloralpha.h
 * \brief Open GL point-cloud object with per vertex point size, color and alpha
 */

#include "data3dpointssizecoloralpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DPointsSizeColorAlpha::vs =    //
    Data3D::VS_Header +                               //
    "layout (location = 1) in float pointSize; \n" +  //
    "layout (location = 2) in vec3 color; \n" +       //
    "layout (location = 3) in float alpha; \n" +      //
    Data3D::VS_Uniforms +                             //
    "out vec3 colorOut;\n" +                          //
    "out float alphaOut;\n" +                         //
    "void main() {\n" +                               //
    " colorOut = color;\n" +                          //
    " alphaOut = alpha;\n" +                          //
    " gl_PointSize = pointSize;\n" +                  //
    Data3D::VS_InMain +                               //
    "}\n";

const std::string Data3DPointsSizeColorAlpha::fs =  //
    Data3D::GLSL_Version +                          //
    "in vec3 colorOut;\n" +                         //
    "in float alphaOut;\n" +                        //
    "out vec4 color;\n" +                           //
    "void main() {\n" +                             //
    " color = vec4(colorOut, alphaOut);\n" +        //
    "}\n";

Data3DPointsSizeColorAlpha::Data3DPointsSizeColorAlpha(const size_t _vertexCount, const size_t _indexCount)
    : Data3D(GL_POINTS_SizeColorAlpha, GL_POINTS, _vertexCount, _indexCount)
{
    if (vertexCount > 0UL)
    {
        m_pointSizeData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
        m_colorData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DPointsSizeColorAlpha::Data3DPointsSizeColorAlpha(const size_t _vertexCount,
                                                       const size_t _indexCount,
                                                       const Math::Vec3F *_vertexData,
                                                       const Math::Vec3F *_colorData,
                                                       const float *_alphaData,
                                                       const float *_pointSizeData,
                                                       const uint *_indexData)
    : Data3D(GL_POINTS_SizeColorAlpha, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
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
            std::cerr << "[Data3DPointsSizeColorAlpha::constructor] Can't create m_pointSizeBuffer !\n";
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
            std::cerr << "[Data3DPointsSizeColorAlpha::constructor] Can't create m_colorBuffer !\n";
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
            std::cerr << "[Data3DPointsSizeColorAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

Data3DPointsSizeColorAlpha::~Data3DPointsSizeColorAlpha()
{
    if (m_pointSizeData != nullptr)
        std::free(m_pointSizeData);
    if (m_colorData != nullptr)
        std::free(m_colorData);
    if (m_alphaData != nullptr)
        std::free(m_alphaData);

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

    if (m_alphaBuffer != nullptr)
    {
        if (m_alphaBuffer->isCreated())
            m_alphaBuffer->destroy();
        delete m_alphaBuffer;
    }
}

bool Data3DPointsSizeColorAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DPointsSizeColorAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    Q_UNUSED(_program)
    glEnable(GL_PROGRAM_POINT_SIZE);
    return true;
}

bool Data3DPointsSizeColorAlpha::createBuffersImpl()
{
    m_pointSizeBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_pointSizeBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_pointSizeBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::createBuffersImpl] Can't create m_pointSizeBuffer !\n";
        return false;
    }

    m_pointSizeBuffer->bind();
    m_pointSizeBuffer->allocate(m_pointSizeData, vertexCount * sizeof(float));
    m_pointSizeBuffer->release();

    m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_colorBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_colorBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::createBuffersImpl] Can't create m_colorBuffer !\n";
        return false;
    }

    m_colorBuffer->bind();
    m_colorBuffer->allocate(m_colorData, vertexCount * sizeof(Math::Vec3F));
    m_colorBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DPointsSizeColorAlpha::destroyBuffersImpl()
{
    if (m_pointSizeBuffer->isCreated())
        m_pointSizeBuffer->destroy();

    delete m_pointSizeBuffer;
    m_pointSizeBuffer = nullptr;

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

bool Data3DPointsSizeColorAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_pointSizeBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::bindBuffersImpl] m_pointSizeBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    if (!m_colorBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::bindBuffersImpl] m_colorBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 3);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DPointsSizeColorAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(3);
    _program->setAttributeBuffer(3, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DPointsSizeColorAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    _program->disableAttributeArray(3);
    m_pointSizeBuffer->release();
    m_colorBuffer->release();
    m_alphaBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
