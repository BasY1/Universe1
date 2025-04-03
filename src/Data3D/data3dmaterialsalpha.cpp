/*!
 * \file src/Data3D/data3dmaterialsalpha.cpp
 * \brief Open GL object with per vertex material and alpha, and uniform normal
 */

#include "data3dmaterialsalpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialsAlpha::vs =       //
    Data3D::VS_Header +                            //
    "layout (location = 1) in vec3 ambient;\n" +   //
    "layout (location = 2) in vec3 diffuse;\n" +   //
    "layout (location = 3) in vec3 specular;\n" +  //
    "layout (location = 4) in float shine;\n" +    //
    "layout (location = 5) in float alpha;\n" +    //
    Data3D::VS_Uniforms +                          //
    "out vec3 posOut;\n" +                         //
    "out vec3 ambientOut;\n" +                     //
    "out vec3 diffuseOut;\n" +                     //
    "out vec3 specularOut;\n" +                    //
    "out float shineOut;\n" +                      //
    "out float alphaOut;\n" +                      //
    "void main() {\n" +                            //
    " posOut = pos;\n" +                           //
    " ambientOut = ambient;\n" +                   //
    " diffuseOut = diffuse;\n" +                   //
    " specularOut = specular;\n" +                 //
    " shineOut = shine;\n" +                       //
    " alphaOut = alpha;\n" +                       //
    Data3D::VS_InMain +                            //
    "}\n";

const std::string Data3DMaterialsAlpha::fs =                    //
    Data3D::FS_Header +                                         //
    "uniform vec3 normal;\n" +                                  //
    "in vec3 posOut;\n" +                                       //
    "in vec3 ambientOut;\n" +                                   //
    "in vec3 diffuseOut;\n" +                                   //
    "in vec3 specularOut;\n" +                                  //
    "in float shineOut;\n" +                                    //
    "in float alphaOut;\n" +                                    //
    "out vec4 color;\n" +                                       //
    "void main() {\n" +                                         //
    " vec3 norm = normalize(normal);\n" +                       //
    " vec3 lDir = normalize(-lightDir);\n" +                    //
    " vec3 vDir = normalize(camera - posOut);\n" +              //
    " vec3 rDir = reflect(-lDir, norm);\n" +                    //
    " float d = max(dot(norm, lDir), 0.0);\n" +                 //
    " float s = pow(max(dot(vDir, rDir), 0.0), shineOut);\n" +  //
    " color = vec4(lightAmbient * ambientOut +\n" +             //
    "              d * lightColor * diffuseOut +\n" +           //
    "              s * lightColor * specularOut,\n" +           //
    "              alphaOut);\n" +                              //
    "}\n";

Data3DMaterialsAlpha::Data3DMaterialsAlpha(const GLuint _glPrimitive,
                                           const size_t _vertexCount,
                                           const size_t _indexCount,
                                           const Math::Vec3F &_normal)
    : Data3D(GL_MATERIAL_VERTEX_Alpha, _glPrimitive, _vertexCount, _indexCount)
    , m_normal(_normal)
{
    if (vertexCount > 0UL)
    {
        m_ambientData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_diffuseData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_specularData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_shineData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DMaterialsAlpha::Data3DMaterialsAlpha(const GLuint _glPrimitive,
                                           const size_t _vertexCount,
                                           const size_t _indexCount,
                                           const Math::Vec3F *_vertexData,
                                           const Math::Vec3F *_ambientData,
                                           const Math::Vec3F *_diffuseData,
                                           const Math::Vec3F *_specularData,
                                           const float *_shineData,
                                           const float *_alphaData,
                                           const uint *_indexData,
                                           const Math::Vec3F &_normal)
    : Data3D(GL_MATERIAL_VERTEX_Alpha, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_normal(_normal)
{
    if (vertexCount > 0UL)
    {
        m_ambientBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_ambientBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_ambientBuffer->create())
        {
            m_ambientBuffer->bind();
            m_ambientBuffer->allocate(_ambientData, vertexCount * sizeof(Math::Vec3F));
            m_ambientBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DMaterialsAlpha::constructor] Can't create m_ambientBuffer !\n";
        }

        m_diffuseBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_diffuseBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_diffuseBuffer->create())
        {
            m_diffuseBuffer->bind();
            m_diffuseBuffer->allocate(_diffuseData, vertexCount * sizeof(Math::Vec3F));
            m_diffuseBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DMaterialsAlpha::constructor] Can't create m_diffuseBuffer !\n";
        }

        m_specularBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_specularBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_specularBuffer->create())
        {
            m_specularBuffer->bind();
            m_specularBuffer->allocate(_specularData, vertexCount * sizeof(Math::Vec3F));
            m_specularBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DMaterialsAlpha::constructor] Can't create m_specularBuffer !\n";
        }

        m_shineBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_shineBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_shineBuffer->create())
        {
            m_shineBuffer->bind();
            m_shineBuffer->allocate(_shineData, vertexCount * sizeof(float));
            m_shineBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DMaterialsAlpha::constructor] Can't create m_shineBuffer !\n";
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
            std::cerr << "[Data3DMaterialsAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

Data3DMaterialsAlpha::~Data3DMaterialsAlpha()
{
    if (m_ambientData != nullptr)
        std::free(m_ambientData);
    if (m_diffuseData != nullptr)
        std::free(m_diffuseData);
    if (m_specularData != nullptr)
        std::free(m_specularData);
    if (m_shineData != nullptr)
        std::free(m_shineData);
    if (m_alphaData != nullptr)
        std::free(m_alphaData);

    if (m_ambientBuffer != nullptr)
    {
        if (m_ambientBuffer->isCreated())
            m_ambientBuffer->destroy();
        delete m_ambientBuffer;
    }

    if (m_diffuseBuffer != nullptr)
    {
        if (m_diffuseBuffer->isCreated())
            m_diffuseBuffer->destroy();
        delete m_diffuseBuffer;
    }

    if (m_specularBuffer != nullptr)
    {
        if (m_specularBuffer->isCreated())
            m_specularBuffer->destroy();
        delete m_specularBuffer;
    }

    if (m_shineBuffer != nullptr)
    {
        if (m_shineBuffer->isCreated())
            m_shineBuffer->destroy();
        delete m_shineBuffer;
    }

    if (m_alphaBuffer != nullptr)
    {
        if (m_alphaBuffer->isCreated())
            m_alphaBuffer->destroy();
        delete m_alphaBuffer;
    }
}

bool Data3DMaterialsAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DMaterialsAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("normal", m_normal.toQVector3D());
    return true;
}

bool Data3DMaterialsAlpha::createBuffersImpl()
{
    m_ambientBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_ambientBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_ambientBuffer->create())
    {
        std::cerr << "[Data3DMaterialsAlpha::createBuffersImpl] Can't create m_ambientBuffer !\n";
        return false;
    }

    m_ambientBuffer->bind();
    m_ambientBuffer->allocate(m_ambientData, vertexCount * sizeof(Math::Vec3F));
    m_ambientBuffer->release();

    m_diffuseBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_diffuseBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_diffuseBuffer->create())
    {
        std::cerr << "[Data3DMaterialsAlpha::createBuffersImpl] Can't create m_diffuseBuffer !\n";
        return false;
    }

    m_diffuseBuffer->bind();
    m_diffuseBuffer->allocate(m_diffuseData, vertexCount * sizeof(Math::Vec3F));
    m_diffuseBuffer->release();

    m_specularBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_specularBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_specularBuffer->create())
    {
        std::cerr << "[Data3DMaterialsAlpha::createBuffersImpl] Can't create m_specularBuffer !\n";
        return false;
    }

    m_specularBuffer->bind();
    m_specularBuffer->allocate(m_specularData, vertexCount * sizeof(Math::Vec3F));
    m_specularBuffer->release();

    m_shineBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_shineBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_shineBuffer->create())
    {
        std::cerr << "[Data3DMaterialsAlpha::createBuffersImpl] Can't create m_shineBuffer !\n";
        return false;
    }

    m_shineBuffer->bind();
    m_shineBuffer->allocate(m_shineData, vertexCount * sizeof(float));
    m_shineBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DMaterialsAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DMaterialsAlpha::destroyBuffersImpl()
{
    if (m_ambientBuffer->isCreated())
        m_ambientBuffer->destroy();

    delete m_ambientBuffer;
    m_ambientBuffer = nullptr;

    if (m_diffuseBuffer->isCreated())
        m_diffuseBuffer->destroy();

    delete m_diffuseBuffer;
    m_diffuseBuffer = nullptr;

    if (m_specularBuffer->isCreated())
        m_specularBuffer->destroy();

    delete m_specularBuffer;
    m_specularBuffer = nullptr;

    if (m_shineBuffer->isCreated())
        m_shineBuffer->destroy();

    delete m_shineBuffer;
    m_shineBuffer = nullptr;

    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DMaterialsAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_ambientBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsAlpha::bindBuffersImpl] m_ambientBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    if (!m_diffuseBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsAlpha::bindBuffersImpl] m_diffuseBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 3);

    if (!m_specularBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsAlpha::bindBuffersImpl] m_specularBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(3);
    _program->setAttributeBuffer(3, GL_FLOAT, 0, 3);

    if (!m_shineBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsAlpha::bindBuffersImpl] m_shineBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(4);
    _program->setAttributeBuffer(4, GL_FLOAT, 0, 1);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(5);
    _program->setAttributeBuffer(5, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DMaterialsAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    _program->disableAttributeArray(3);
    _program->disableAttributeArray(4);
    _program->disableAttributeArray(5);
    m_ambientBuffer->release();
    m_diffuseBuffer->release();
    m_specularBuffer->release();
    m_shineBuffer->release();
    m_alphaBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
