/*!
 * \file src/Data3D/data3dmaterialnormalalpha.cpp
 * \brief Open GL object with per vertex normals and alpha and uniform material
 */

#include "data3dmaterialnormalalpha.h"

#include "../Math/cylinder.h"
#include "../Math/cylinderarc.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialNormalAlpha::vs =  //
    Data3D::VS_Header +                            //
    "layout (location = 1) in vec3 normal;\n" +    //
    "layout (location = 2) in float alpha;\n" +    //
    Data3D::VS_Uniforms +                          //
    "out vec3 posOut;\n" +                         //
    "out vec3 norOut;\n" +                         //
    "out float alphaOut;\n" +                      //
    "void main() {\n" +                            //
    " posOut = pos;\n" +                           //
    " norOut = normal;\n" +                        //
    " alphaOut = alpha;\n" +                       //
    Data3D::VS_InMain +                            //
    "}\n";

const std::string Data3DMaterialNormalAlpha::fs =            //
    Data3D::FS_Header +                                      //
    "uniform vec3 ambient;\n" +                              //
    "uniform vec3 diffuse;\n" +                              //
    "uniform vec3 specular;\n" +                             //
    "uniform float shine;\n" +                               //
    "in vec3 posOut;\n" +                                    //
    "in vec3 norOut;\n" +                                    //
    "in float alphaOut;\n" +                                 //
    "out vec4 color;\n" +                                    //
    "void main() {\n" +                                      //
    " vec3 norm = normalize(norOut);\n" +                    //
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

Data3DMaterialNormalAlpha::Data3DMaterialNormalAlpha(const GLuint _glPrimitive,
                                                     const size_t _vertexCount,
                                                     const size_t _indexCount,
                                                     const Math::MaterialRGB &_material)
    : Data3D(GL_MATERIAL_SINGLE_Normal, _glPrimitive, _vertexCount, _indexCount)
    , m_material(_material)
{
    if (vertexCount > 0UL)
    {
        m_normalData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_alphaData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DMaterialNormalAlpha::Data3DMaterialNormalAlpha(const GLuint _glPrimitive,
                                                     const size_t _vertexCount,
                                                     const size_t _indexCount,
                                                     const Math::Vec3F *_vertexData,
                                                     const Math::Vec3F *_normalData,
                                                     const float *_alphaData,
                                                     const uint *_indexData,
                                                     const Math::MaterialRGB &_material)
    : Data3D(GL_MATERIAL_SINGLE_Normal, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_material(_material)
{
    if (vertexCount > 0UL)
    {
        m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_normalBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_normalBuffer->create())
        {
            m_normalBuffer->bind();
            m_normalBuffer->allocate(_normalData, vertexCount * sizeof(Math::Vec3F));
            m_normalBuffer->release();
        }
        else
        {
            std::cerr << "[Data3DMaterialNormalAlpha::constructor] Can't create m_normalBuffer !\n";
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
            std::cerr << "[Data3DMaterialNormalAlpha::constructor] Can't create m_alphaBuffer !\n";
        }
    }
}

bool Data3DMaterialNormalAlpha::isTransparent() const
{
    return m_isTransparent;
}

bool Data3DMaterialNormalAlpha::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("ambient", m_material.ambient.toQVec3());
    _program->setUniformValue("diffuse", m_material.diffuse.toQVec3());
    _program->setUniformValue("specular", m_material.specular.toQVec3());
    _program->setUniformValue("shine", m_material.shine);
    return true;
}

bool Data3DMaterialNormalAlpha::createBuffersImpl()
{
    m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_normalBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_normalBuffer->create())
    {
        std::cerr << "[Data3DMaterialNormalAlpha::createBuffersImpl] Can't create m_normalBuffer !\n";
        return false;
    }

    m_normalBuffer->bind();
    m_normalBuffer->allocate(m_normalData, vertexCount * sizeof(Math::Vec3F));
    m_normalBuffer->release();

    m_alphaBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_alphaBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_alphaBuffer->create())
    {
        std::cerr << "[Data3DMaterialNormalAlpha::createBuffersImpl] Can't create m_alphaBuffer !\n";
        return false;
    }

    m_alphaBuffer->bind();
    m_alphaBuffer->allocate(m_alphaData, vertexCount * sizeof(float));
    m_alphaBuffer->release();

    return true;
}

bool Data3DMaterialNormalAlpha::destroyBuffersImpl()
{
    if (m_normalBuffer->isCreated())
        m_normalBuffer->destroy();

    delete m_normalBuffer;
    m_normalBuffer = nullptr;

    if (m_alphaBuffer->isCreated())
        m_alphaBuffer->destroy();

    delete m_alphaBuffer;
    m_alphaBuffer = nullptr;

    return true;
}

bool Data3DMaterialNormalAlpha::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_normalBuffer->bind())
    {
        std::cerr << "[Data3DMaterialNormalAlpha::bindBuffersImpl] m_normalBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    if (!m_alphaBuffer->bind())
    {
        std::cerr << "[Data3DMaterialNormalAlpha::bindBuffersImpl] m_alphaBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DMaterialNormalAlpha::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    m_normalBuffer->release();
    m_alphaBuffer->release();
    return true;
}

Data3DMaterialNormalAlpha *Data3DMaterialNormalAlpha::cylinder(const Math::OrientF &_orientation,
                                                               const float _length,
                                                               const float _radius1,
                                                               const float _radius2,
                                                               const size_t _quality,
                                                               const Math::MaterialRGB &_material,
                                                               const uint8_t _alpha1,
                                                               const uint8_t _alpha2)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    float *t3 = reinterpret_cast<float *>(N * sizeof(float));

    Math::CylinderF::fillCylinderOuter(t1,
                                       t2,
                                       t3,
                                       _orientation,
                                       float(_alpha1) / 255.0f,
                                       float(_alpha2) / 255.0f,
                                       _length,
                                       _radius1,
                                       _radius2,
                                       _quality);

    Data3DMaterialNormalAlpha *result = new Data3DMaterialNormalAlpha(GL_QUAD_STRIP, N, t1, t2, t3, _material);

    std::free(t1);
    std::free(t2);
    std::free(t3);

    return result;
}

Data3DMaterialNormalAlpha *Data3DMaterialNormalAlpha::cylinderInn(const Math::OrientF &_orientation,
                                                                  const float _length,
                                                                  const float _radius1,
                                                                  const float _radius2,
                                                                  const size_t _quality,
                                                                  const Math::MaterialRGB &_material,
                                                                  const uint8_t _alpha1,
                                                                  const uint8_t _alpha2)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    float *t3 = reinterpret_cast<float *>(N * sizeof(float));

    Math::CylinderF::fillCylinderInner(t1,
                                       t2,
                                       t3,
                                       _orientation,
                                       float(_alpha1) / 255.0f,
                                       float(_alpha2) / 255.0f,
                                       _length,
                                       _radius1,
                                       _radius2,
                                       _quality);

    Data3DMaterialNormalAlpha *result = new Data3DMaterialNormalAlpha(GL_QUAD_STRIP, N, t1, t2, t3, _material);

    std::free(t1);
    std::free(t2);
    std::free(t3);

    return result;
}

Data3DMaterialNormalAlpha *Data3DMaterialNormalAlpha::cylinderArc(const Math::OrientF &_orientation,
                                                                  const float _length,
                                                                  const float _radiusArc,
                                                                  const float _radius1,
                                                                  const float _radius2,
                                                                  const size_t _qualityArc,
                                                                  const size_t _qualityCylinder,
                                                                  const Math::MaterialRGB &_material,
                                                                  const uint8_t _alpha1,
                                                                  const uint8_t _alpha2,
                                                                  const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    float *t3 = reinterpret_cast<float *>(N * sizeof(float));
    uint *t4 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::CylinderArcF::fillCylinderOuter(t1,
                                          t2,
                                          t3,
                                          t4,
                                          _orientation,
                                          float(_alpha1) / 255.0f,
                                          float(_alpha2) / 255.0f,
                                          _radiusArc,
                                          _radius1,
                                          _radius2,
                                          _qualityCylinder,
                                          a);

    Data3DMaterialNormalAlpha *result = new Data3DMaterialNormalAlpha(GL_QUADS, N, I, t1, t2, t3, t4, _material);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    return result;
}

Data3DMaterialNormalAlpha *Data3DMaterialNormalAlpha::cylinderArcInn(const Math::OrientF &_orientation,
                                                                     const float _length,
                                                                     const float _radiusArc,
                                                                     const float _radius1,
                                                                     const float _radius2,
                                                                     const size_t _qualityArc,
                                                                     const size_t _qualityCylinder,
                                                                     const Math::MaterialRGB &_material,
                                                                     const uint8_t _alpha1,
                                                                     const uint8_t _alpha2,
                                                                     const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    float *t3 = reinterpret_cast<float *>(N * sizeof(float));
    uint *t4 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::CylinderArcF::fillCylinderInner(t1,
                                          t2,
                                          t3,
                                          t4,
                                          _orientation,
                                          float(_alpha1) / 255.0f,
                                          float(_alpha2) / 255.0f,
                                          _radiusArc,
                                          _radius1,
                                          _radius2,
                                          _qualityCylinder,
                                          a);

    Data3DMaterialNormalAlpha *result = new Data3DMaterialNormalAlpha(GL_QUADS, N, I, t1, t2, t3, t4, _material);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    return result;
}

}  // namespace OpenGL
}  // namespace U1
