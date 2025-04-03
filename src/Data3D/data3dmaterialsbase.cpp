/*!
 * \file src/Data3D/data3dmaterialsbase.cpp
 * \brief Open GL object with per vertex material, and uniform alpha and normal
 */

#include "data3dmaterialsbase.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialsBase::vs =        //
    Data3D::VS_Header +                            //
    "layout (location = 1) in vec3 ambient;\n" +   //
    "layout (location = 2) in vec3 diffuse;\n" +   //
    "layout (location = 3) in vec3 specular;\n" +  //
    "layout (location = 4) in float shine;\n" +    //
    Data3D::VS_Uniforms +                          //
    "out vec3 posOut;\n" +                         //
    "out vec3 ambientOut;\n" +                     //
    "out vec3 diffuseOut;\n" +                     //
    "out vec3 specularOut;\n" +                    //
    "out float shineOut;\n" +                      //
    "void main() {\n" +                            //
    " posOut = pos;\n" +                           //
    " ambientOut = ambient;\n" +                   //
    " diffuseOut = diffuse;\n" +                   //
    " specularOut = specular;\n" +                 //
    " shineOut = shine;\n" +                       //
    Data3D::VS_InMain +                            //
    "}\n";

const std::string Data3DMaterialsBase::fs =                     //
    Data3D::FS_Header +                                         //
    "uniform vec3 normal;\n" +                                  //
    "uniform float alpha;\n" +                                  //
    "in vec3 posOut;\n" +                                       //
    "in vec3 ambientOut;\n" +                                   //
    "in vec3 diffuseOut;\n" +                                   //
    "in vec3 specularOut;\n" +                                  //
    "in float shineOut;\n" +                                    //
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
    "              alpha);\n" +                                 //
    "}\n";

Data3DMaterialsBase::Data3DMaterialsBase(const GLuint _glPrimitive,
                                         const size_t _vertexCount,
                                         const size_t _indexCount,
                                         const Math::Vec3F &_normal,
                                         const uint8_t _alpha)
    : Data3D(GL_MATERIAL_VERTEX_Base, _glPrimitive, _vertexCount, _indexCount)
    , m_normal(_normal)
    , m_alpha(_alpha)
{
    if (vertexCount > 0UL)
    {
        m_ambientData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_diffuseData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_specularData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_shineData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DMaterialsBase::Data3DMaterialsBase(const GLuint _glPrimitive,
                                         const size_t _vertexCount,
                                         const size_t _indexCount,
                                         const Math::Vec3F *_vertexData,
                                         const Math::Vec3F *_ambientData,
                                         const Math::Vec3F *_diffuseData,
                                         const Math::Vec3F *_specularData,
                                         const float *_shineData,
                                         const uint *_indexData,
                                         const Math::Vec3F &_normal,
                                         const uint8_t _alpha)
    : Data3D(GL_MATERIAL_VERTEX_Base, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_normal(_normal)
    , m_alpha(_alpha)
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
            std::cerr << "[Data3DMaterialsBase::constructor] Can't create m_ambientBuffer !\n";
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
            std::cerr << "[Data3DMaterialsBase::constructor] Can't create m_diffuseBuffer !\n";
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
            std::cerr << "[Data3DMaterialsBase::constructor] Can't create m_specularBuffer !\n";
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
            std::cerr << "[Data3DMaterialsBase::constructor] Can't create m_shineBuffer !\n";
        }
    }
}

bool Data3DMaterialsBase::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DMaterialsBase::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("normal", m_normal.toQVector3D());
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DMaterialsBase::createBuffersImpl()
{
    m_ambientBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_ambientBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_ambientBuffer->create())
    {
        std::cerr << "[Data3DMaterialsBase::createBuffersImpl] Can't create m_ambientBuffer !\n";
        return false;
    }

    m_ambientBuffer->bind();
    m_ambientBuffer->allocate(m_ambientData, vertexCount * sizeof(Math::Vec3F));
    m_ambientBuffer->release();

    m_diffuseBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_diffuseBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_diffuseBuffer->create())
    {
        std::cerr << "[Data3DMaterialsBase::createBuffersImpl] Can't create m_diffuseBuffer !\n";
        return false;
    }

    m_diffuseBuffer->bind();
    m_diffuseBuffer->allocate(m_diffuseData, vertexCount * sizeof(Math::Vec3F));
    m_diffuseBuffer->release();

    m_specularBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_specularBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_specularBuffer->create())
    {
        std::cerr << "[Data3DMaterialsBase::createBuffersImpl] Can't create m_specularBuffer !\n";
        return false;
    }

    m_specularBuffer->bind();
    m_specularBuffer->allocate(m_specularData, vertexCount * sizeof(Math::Vec3F));
    m_specularBuffer->release();

    m_shineBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_shineBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_shineBuffer->create())
    {
        std::cerr << "[Data3DMaterialsBase::createBuffersImpl] Can't create m_shineBuffer !\n";
        return false;
    }

    m_shineBuffer->bind();
    m_shineBuffer->allocate(m_shineData, vertexCount * sizeof(float));
    m_shineBuffer->release();

    return true;
}

bool Data3DMaterialsBase::destroyBuffersImpl()
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
    return true;
}

bool Data3DMaterialsBase::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_ambientBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsBase::bindBuffersImpl] m_ambientBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    if (!m_diffuseBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsBase::bindBuffersImpl] m_diffuseBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 3);

    if (!m_specularBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsBase::bindBuffersImpl] m_specularBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(3);
    _program->setAttributeBuffer(3, GL_FLOAT, 0, 3);

    if (!m_shineBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsBase::bindBuffersImpl] m_shineBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(4);
    _program->setAttributeBuffer(4, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DMaterialsBase::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    _program->disableAttributeArray(3);
    _program->disableAttributeArray(4);
    m_ambientBuffer->release();
    m_diffuseBuffer->release();
    m_specularBuffer->release();
    m_shineBuffer->release();
    return true;
}

}  // namespace OpenGL
}  // namespace U1
