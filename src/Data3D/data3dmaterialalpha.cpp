/*!
 * \file src/Data3D/data3dmaterialalpha.cpp
 * \brief Open GL object with per vertex alpha, and uniform material and normal
 */

#include "data3dmaterialalpha.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialAlpha::vs =      //
    Data3D::VS_Header +                          //
    "layout (location = 1) in float alpha;\n" +  //
    Data3D::VS_Uniforms +                        //
    "out vec3 posOut;\n" +                       //
    "out float alphaOut;\n" +                    //
    "void main() {\n" +                          //
    " posOut = pos;\n" +                         //
    " alphaOut = alpha;\n" +                     //
    Data3D::VS_InMain +                          //
    "}\n";

const std::string Data3DMaterialAlpha::fs =                  //
    Data3D::FS_Header +                                      //
    "uniform vec3 normal;\n" +                               //
    "uniform vec3 ambient;\n" +                              //
    "uniform vec3 diffuse;\n" +                              //
    "uniform vec3 specular;\n" +                             //
    "uniform float shine;\n" +                               //
    "in float alphaOut;\n" +                                 //
    "in vec3 posOut;\n" +                                    //
    "out vec4 color;\n" +                                    //
    "void main() {\n" +                                      //
    " vec3 norm = normalize(normal);\n" +                    //
    " vec3 lDir = normalize(-lightDir);\n" +                 //
    " vec3 vDir = normalize(camera - posOut);\n" +           //
    " vec3 rDir = reflect(-lDir, norm);\n" +                 //
    " float d = max(dot(norm, lDir), 0.0);\n" +              //
    " float s = pow(max(dot(vDir, rDir), 0.0), shine);\n" +  //
    " color = vec4(lightAmbient * ambient +\n" +             //
    "              d * lightColor * diffuse +\n" +           //
    "              s * lightColor * specular,\n" +           //
    "              alphaOut);\n" +                           //
    "}\n";

Data3DMaterialAlpha::Data3DMaterialAlpha(const GLuint _glPrimitive,
                                         const size_t _vertexCount,
                                         const size_t _indexCount,
                                         const Math::Vec3F &_normal,
                                         const Math::MaterialRGB &_material)
    : Data3D(GL_MATERIAL_SINGLE_Alpha, _glPrimitive, _vertexCount, _indexCount)
    , m_normal(_normal)
    , m_material(_material)
{
    if (vertexCount > 0UL)
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
}

Data3DMaterialAlpha::Data3DMaterialAlpha(const GLuint _glPrimitive,
                                         const size_t _vertexCount,
                                         const size_t _indexCount,
                                         const Math::Vec3F *_vertexData,
                                         const float *_alphaData,
                                         const uint *_indexData,
                                         const Math::Vec3F &_normal,
                                         const Math::MaterialRGB &_material)
    : Data3D(GL_MATERIAL_SINGLE_Alpha, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_normal(_normal)
    , m_material(_material)
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
            std::cerr << "[Data3DMaterialAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

bool Data3DMaterialAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DMaterialAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("normal", m_normal.toQVector3D());
    _program->setUniformValue("ambient", m_material.ambient.toQVec3());
    _program->setUniformValue("diffuse", m_material.diffuse.toQVec3());
    _program->setUniformValue("specular", m_material.specular.toQVec3());
    _program->setUniformValue("shine", m_material.shine);
    return true;
}

bool Data3DMaterialAlpha::createBuffersImpl()
{
    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DMaterialAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DMaterialAlpha::destroyBuffersImpl()
{
    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DMaterialAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DMaterialAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DMaterialAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_alphaBuffer->release();
    return true;
}


}  // namespace OpenGL
}  // namespace U1
