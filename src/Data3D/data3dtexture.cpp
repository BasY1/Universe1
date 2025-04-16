/*!
 * \file src/Data3D/data3dtexture.h
 * \brief Open GL object with texture
 */

#include "data3dtexture.h"

#include "../Math/sphere.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DTexture::vs =               //
    Data3D::VS_Header +                             //
    "layout (location = 1) in vec2 textCoord;\n" +  //
    Data3D::VS_Uniforms +                           //
    "out vec2 textCoordOut;\n" +                    //
    "void main() {\n" +                             //
    " textCoordOut = textCoord;\n" +                //
    Data3D::VS_InMain +                             //
    "}\n";

const std::string Data3DTexture::fs =                 //
    Data3D::GLSL_Version +                            //
    "uniform sampler2D texture;\n" +                  //
    "uniform float alpha;\n" +                        //
    "in vec2 textCoordOut;\n" +                       //
    "out vec4 color;\n" +                             //
    "void main() {\n" +                               //
    " color = texture2D(texture, textCoordOut);\n" +  //
    " color.a = alpha;\n" +                           //
    "}\n";

Data3DTexture::Data3DTexture(QOpenGLTexture *_texture,
                             const GLuint _glPrimitive,
                             const size_t _vertexCount,
                             const size_t _indexCount,
                             const uint8_t _alpha)
    : Data3D(GL_TEXTURE_Base, _glPrimitive, _vertexCount, _indexCount)
    , m_alpha(_alpha)
    , m_texture(_texture)
{
    if (vertexCount > 0UL)
        m_coordData = reinterpret_cast<Math::Vec2F *>(std::malloc(vertexCount * sizeof(Math::Vec2F)));
}

Data3DTexture::Data3DTexture(QOpenGLTexture *_texture,
                             const GLuint _glPrimitive,
                             const size_t _vertexCount,
                             const size_t _indexCount,
                             const Math::Vec3F *_vertexData,
                             const Math::Vec2F *_coordData,
                             const uint *_indexData,
                             const uint8_t _alpha)
    : Data3D(GL_TEXTURE_Base, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_alpha(_alpha)
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
            std::cerr << "[Data3DTexture::constructor] Can't create m_coordBuffer !\n";
        }
    }
}

Data3DTexture::~Data3DTexture()
{
    if (m_coordData != nullptr)
        std::free(m_coordData);

    if (m_coordBuffer != nullptr)
    {
        if (m_coordBuffer->isCreated())
            m_coordBuffer->destroy();
        delete m_coordBuffer;
    }

    if (m_texture != nullptr)
        delete m_texture;
}

bool Data3DTexture::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DTexture::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DTexture::createBuffersImpl()
{
    m_coordBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_coordBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_coordBuffer->create())
    {
        std::cerr << "[Data3DTexture::createBuffersImpl] Can't create m_coordBuffer !\n";
        return false;
    }

    m_coordBuffer->bind();
    m_coordBuffer->allocate(m_coordData, vertexCount * sizeof(Math::Vec2F));
    m_coordBuffer->release();

    return true;
}

bool Data3DTexture::destroyBuffersImpl()
{
    if (m_coordBuffer->isCreated())
        m_coordBuffer->destroy();

    delete m_coordBuffer;
    m_coordBuffer = nullptr;

    return true;
}

bool Data3DTexture::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_coordBuffer->bind())
    {
        std::cerr << "[Data3DTexture::bindBuffersImpl] m_coordBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 2);

    m_texture->bind();

    return true;
}

bool Data3DTexture::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_coordBuffer->release();
    m_texture->release();
    return true;
}

Data3DTexture *Data3DTexture::sphere(QOpenGLTexture *_texture,
                                     const Math::OrientF &_orientation,
                                     const float _radius,
                                     const size_t _quality,
                                     const uint8_t _alpha)
{
    const size_t N = Math::SphereF::sphereVertexCount(_quality);
    const size_t I = Math::SphereF::sphereIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec2F *t2 = reinterpret_cast<Math::Vec2F *>(std::malloc(N * sizeof(Math::Vec2F)));
    uint *t3 = reinterpret_cast<uint *>(std::malloc(I * sizeof(uint)));

    Math::SphereF::fillSphereOuter(t1, t2, t3, _orientation, _radius, _quality);

    Data3DTexture *result = new Data3DTexture(_texture, GL_QUADS, N, I, t1, t2, t3, _alpha);
    result->setCentralPoint(_orientation.center);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DTexture *Data3DTexture::sphereInn(QOpenGLTexture *_texture,
                                        const Math::OrientF &_orientation,
                                        const float _radius,
                                        const size_t _quality,
                                        const uint8_t _alpha)
{
    const size_t N = Math::SphereF::sphereVertexCount(_quality);
    const size_t I = Math::SphereF::sphereIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec2F *t2 = reinterpret_cast<Math::Vec2F *>(std::malloc(N * sizeof(Math::Vec2F)));
    uint *t3 = reinterpret_cast<uint *>(std::malloc(I * sizeof(uint)));

    Math::SphereF::fillSphereInner(t1, t2, t3, _orientation, _radius, _quality);

    Data3DTexture *result = new Data3DTexture(_texture, GL_QUADS, N, I, t1, t2, t3, _alpha);
    result->setCentralPoint(_orientation.center);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

}  // namespace OpenGL
}  // namespace U1
