/*!
 * \file src/Data3D/data3dtexturealpha.h
 * \brief Open GL object with texture and per vertex alpha
 */

#include "data3dtexturealpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DTextureAlpha::vs =          //
    Data3D::VS_Header +                             //
    "layout (location = 1) in vec2 textCoord;\n" +  //
    "layout (location = 2) in float alpha;\n" +     //
    Data3D::VS_Uniforms +                           //
    "out vec2 textCoordOut;\n" +                    //
    "out float alphaOut;\n" +                       //
    "void main() {\n" +                             //
    " textCoordOut = textCoord;\n" +                //
    " alphaOut = alpha;\n" +                        //
    Data3D::VS_InMain +                             //
    "}\n";

const std::string Data3DTextureAlpha::fs =            //
    Data3D::GLSL_Version +                            //
    "uniform sampler2D texture;\n" +                  //
    "in vec2 textCoordOut;\n" +                       //
    "in float alphaOut;\n" +                          //
    "out vec4 color;\n" +                             //
    "void main() {\n" +                               //
    " color = texture2D(texture, textCoordOut);\n" +  //
    " color.a = alphaOut;\n" +                        //
    "}\n";

Data3DTextureAlpha::Data3DTextureAlpha(QOpenGLTexture *_texture,
                                       const GLuint _glPrimitive,
                                       const size_t _vertexCount,
                                       const size_t _indexCount)
    : Data3D(GL_TEXTURE_Base, _glPrimitive, _vertexCount, _indexCount)
    , m_texture(_texture)
{
    if (vertexCount > 0UL)
    {
        m_coordData = reinterpret_cast<Math::Vec2F *>(std::malloc(vertexCount * sizeof(Math::Vec2F)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DTextureAlpha::Data3DTextureAlpha(QOpenGLTexture *_texture,
                                       const GLuint _glPrimitive,
                                       const size_t _vertexCount,
                                       const size_t _indexCount,
                                       const Math::Vec3F *_vertexData,
                                       const Math::Vec2F *_coordData,
                                       const float *_alphaData,
                                       const uint *_indexData)
    : Data3D(GL_TEXTURE_Base, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_texture(_texture)
{
    if (vertexCount > 0UL)
    {
        m_coordBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_coordBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_coordBuffer->create())
        {
            m_coordBuffer->bind();
            m_coordBuffer->allocate(_coordData, vertexCount * sizeof(Math::Vec2F));
            m_coordBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DTextureAlpha::constructor] Can't create m_coordBuffer !\n";
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
            std::cerr << "[Data3DTextureAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

Data3DTextureAlpha::~Data3DTextureAlpha()
{
    if (m_coordData != nullptr)
        std::free(m_coordData);
    if (m_alphaData != nullptr)
        std::free(m_alphaData);

    if (m_coordBuffer != nullptr)
    {
        if (m_coordBuffer->isCreated())
            m_coordBuffer->destroy();
        delete m_coordBuffer;
    }

    if (m_alphaBuffer != nullptr)
    {
        if (m_alphaBuffer->isCreated())
            m_alphaBuffer->destroy();
        delete m_alphaBuffer;
    }
}

bool Data3DTextureAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DTextureAlpha::createBuffersImpl()
{
    m_coordBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_coordBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_coordBuffer->create())
    {
        std::cerr << "[Data3DTextureAlpha::createBuffersImpl] Can't create m_coordBuffer !\n";
        return false;
    }

    m_coordBuffer->bind();
    m_coordBuffer->allocate(m_coordData, vertexCount * sizeof(Math::Vec2F));
    m_coordBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DTextureAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DTextureAlpha::destroyBuffersImpl()
{
    if (m_coordBuffer->isCreated())
        m_coordBuffer->destroy();

    delete m_coordBuffer;
    m_coordBuffer = nullptr;

    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DTextureAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_coordBuffer->bind())
    {
        std::cerr << "[Data3DTextureAlpha::bindBuffersImpl] m_coordBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 2);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DTextureAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 1);

    m_texture->bind();

    return true;
}

bool Data3DTextureAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    m_coordBuffer->release();
    m_alphaBuffer->release();
    m_texture->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
