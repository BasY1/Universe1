/*!
 * \file src/Data3D/data3dmaterialnormal.cpp
 * \brief Open GL object with per vertex normals and uniform material and alpha
 */

#include "data3dmaterialnormal.h"

#include "../Math/sphere.h"
#include "../Math/ellipsoid.h"
#include "../Math/irregellipsoid.h"
#include "../Math/cylinder.h"
#include "../Math/cylinderarc.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialNormal::vs =     //
    Data3D::VS_Header +                          //
    "layout (location = 1) in vec3 normal;\n" +  //
    Data3D::VS_Uniforms +                        //
    "out vec3 posOut;\n" +                       //
    "out vec3 norOut;\n" +                       //
    "void main() {\n" +                          //
    " posOut = pos;\n" +                         //
    " norOut = normal;\n" +                      //
    Data3D::VS_InMain +                          //
    "}\n";

const std::string Data3DMaterialNormal::fs =                 //
    Data3D::FS_Header +                                      //
    "uniform vec3 ambient;\n" +                              //
    "uniform vec3 diffuse;\n" +                              //
    "uniform vec3 specular;\n" +                             //
    "uniform float shine;\n" +                               //
    "uniform float alpha;\n" +                               //
    "in vec3 posOut;\n" +                                    //
    "in vec3 norOut;\n" +                                    //
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
    "              alpha);\n" +                              //
    "}\n";

Data3DMaterialNormal::Data3DMaterialNormal(const GLuint _glPrimitive,
                                           const size_t _vertexCount,
                                           const size_t _indexCount,
                                           const Math::MaterialRGB &_material,
                                           const uint8_t _alpha)
    : Data3D(GL_MATERIAL_SINGLE_Normal, _glPrimitive, _vertexCount, _indexCount)
    , m_material(_material)
    , m_alpha(_alpha)
{
    if (vertexCount > 0UL)
        m_normalData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
}

Data3DMaterialNormal::Data3DMaterialNormal(const GLuint _glPrimitive,
                                           const size_t _vertexCount,
                                           const size_t _indexCount,
                                           const Math::Vec3F *_vertexData,
                                           const Math::Vec3F *_normalData,
                                           const uint *_indexData,
                                           const Math::MaterialRGB &_material,
                                           const uint8_t _alpha)
    : Data3D(GL_MATERIAL_SINGLE_Normal, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
    , m_material(_material)
    , m_alpha(_alpha)
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
            std::cerr << "[Data3DMaterialNormal::constructor] Can't create m_normalBuffer !\n";
        }
    }
}

bool Data3DMaterialNormal::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DMaterialNormal::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("ambient", m_material.ambient.toQVec3());
    _program->setUniformValue("diffuse", m_material.diffuse.toQVec3());
    _program->setUniformValue("specular", m_material.specular.toQVec3());
    _program->setUniformValue("shine", m_material.shine);
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DMaterialNormal::createBuffersImpl()
{
    m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_normalBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_normalBuffer->create())
    {
        std::cerr << "[Data3DMaterialNormal::createBuffersImpl] Can't create m_normalBuffer !\n";
        return false;
    }

    m_normalBuffer->bind();
    m_normalBuffer->allocate(m_normalData, vertexCount * sizeof(Math::Vec3F));
    m_normalBuffer->release();

    return true;
}

bool Data3DMaterialNormal::destroyBuffersImpl()
{
    if (m_normalBuffer->isCreated())
        m_normalBuffer->destroy();

    delete m_normalBuffer;
    m_normalBuffer = nullptr;

    return true;
}

bool Data3DMaterialNormal::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_normalBuffer->bind())
    {
        std::cerr << "[Data3DMaterialNormal::bindBuffersImpl] m_normalBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    return true;
}

bool Data3DMaterialNormal::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    m_normalBuffer->release();
    return true;
}

Data3DMaterialNormal *Data3DMaterialNormal::sphere(const Math::OrientF &_orientation,
                                                   const float _radius,
                                                   const size_t _quality,
                                                   const Math::MaterialRGB &_material,
                                                   const uint8_t _alpha)
{
    const size_t N = Math::SphereF::sphereVertexCount(_quality);
    const size_t I = Math::SphereF::sphereIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::SphereF::fillSphereOuter(t1, t2, t3, _orientation, _radius, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::sphereInn(const Math::OrientF &_orientation,
                                                      const float _radius,
                                                      const size_t _quality,
                                                      const Math::MaterialRGB &_material,
                                                      const uint8_t _alpha)
{
    const size_t N = Math::SphereF::sphereVertexCount(_quality);
    const size_t I = Math::SphereF::sphereIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::SphereF::fillSphereInner(t1, t2, t3, _orientation, _radius, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::sphereArc(const Math::OrientF &_orientation,
                                                      const float _angleLonStart,
                                                      const float _angleLonEnd,
                                                      const float _angleLatStart,
                                                      const float _angleLatEnd,
                                                      const float _radius,
                                                      const size_t _quality,
                                                      const Math::MaterialRGB &_material,
                                                      const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::SphereF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::SphereF::fillSphereArcOuter(t1, t2, t3, _orientation, _radius, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::sphereArcInn(const Math::OrientF &_orientation,
                                                         const float _angleLonStart,
                                                         const float _angleLonEnd,
                                                         const float _angleLatStart,
                                                         const float _angleLatEnd,
                                                         const float _radius,
                                                         const size_t _quality,
                                                         const Math::MaterialRGB &_material,
                                                         const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::SphereF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::SphereF::fillSphereArcInner(t1, t2, t3, _orientation, _radius, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::ellipsoid(const Math::OrientF &_orientation,
                                                      const float _radius1,
                                                      const float _radius2,
                                                      const float _radius3,
                                                      const size_t _quality,
                                                      const Math::MaterialRGB &_material,
                                                      const uint8_t _alpha)
{
    const size_t N = Math::EllipsoidF::ellipsoidVertexCount(_quality);
    const size_t I = Math::EllipsoidF::ellipsoidIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::EllipsoidF::fillEllipsoidOuter(t1, t2, t3, _orientation, _radius1, _radius2, _radius3, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::ellipsoidInn(const Math::OrientF &_orientation,
                                                         const float _radius1,
                                                         const float _radius2,
                                                         const float _radius3,
                                                         const size_t _quality,
                                                         const Math::MaterialRGB &_material,
                                                         const uint8_t _alpha)
{
    const size_t N = Math::EllipsoidF::ellipsoidVertexCount(_quality);
    const size_t I = Math::EllipsoidF::ellipsoidIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::EllipsoidF::fillEllipsoidInner(t1, t2, t3, _orientation, _radius1, _radius2, _radius3, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::ellipsoidArc(const Math::OrientF &_orientation,
                                                         const float _angleLonStart,
                                                         const float _angleLonEnd,
                                                         const float _angleLatStart,
                                                         const float _angleLatEnd,
                                                         const float _radius1,
                                                         const float _radius2,
                                                         const float _radius3,
                                                         const size_t _quality,
                                                         const Math::MaterialRGB &_material,
                                                         const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::EllipsoidF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::EllipsoidF::fillEllipsoidArcOuter(t1, t2, t3, _orientation, _radius1, _radius2, _radius3, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::ellipsoidArcInn(const Math::OrientF &_orientation,
                                                            const float _angleLonStart,
                                                            const float _angleLonEnd,
                                                            const float _angleLatStart,
                                                            const float _angleLatEnd,
                                                            const float _radius1,
                                                            const float _radius2,
                                                            const float _radius3,
                                                            const size_t _quality,
                                                            const Math::MaterialRGB &_material,
                                                            const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::EllipsoidF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::EllipsoidF::fillEllipsoidArcInner(t1, t2, t3, _orientation, _radius1, _radius2, _radius3, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::irregEllipsoid(const Math::OrientF &_orientation,
                                                           const float _radius1P,
                                                           const float _radius1M,
                                                           const float _radius2P,
                                                           const float _radius2M,
                                                           const float _radius3P,
                                                           const float _radius3M,
                                                           const size_t _quality,
                                                           const Math::MaterialRGB &_material,
                                                           const uint8_t _alpha)
{
    const size_t N = Math::IrregEllipsoidF::ellipsoidVertexCount(_quality);
    const size_t I = Math::IrregEllipsoidF::ellipsoidIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::IrregEllipsoidF::fillEllipsoidOuter(
        t1, t2, t3, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::irregEllipsoidInn(const Math::OrientF &_orientation,
                                                              const float _radius1P,
                                                              const float _radius1M,
                                                              const float _radius2P,
                                                              const float _radius2M,
                                                              const float _radius3P,
                                                              const float _radius3M,
                                                              const size_t _quality,
                                                              const Math::MaterialRGB &_material,
                                                              const uint8_t _alpha)
{
    const size_t N = Math::IrregEllipsoidF::ellipsoidVertexCount(_quality);
    const size_t I = Math::IrregEllipsoidF::ellipsoidIndexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::IrregEllipsoidF::fillEllipsoidInner(
        t1, t2, t3, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::irregEllipsoidArc(const Math::OrientF &_orientation,
                                                              const float _angleLonStart,
                                                              const float _angleLonEnd,
                                                              const float _angleLatStart,
                                                              const float _angleLatEnd,
                                                              const float _radius1P,
                                                              const float _radius1M,
                                                              const float _radius2P,
                                                              const float _radius2M,
                                                              const float _radius3P,
                                                              const float _radius3M,
                                                              const size_t _quality,
                                                              const Math::MaterialRGB &_material,
                                                              const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::IrregEllipsoidF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::IrregEllipsoidF::fillEllipsoidArcOuter(
        t1, t2, t3, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::irregEllipsoidArcInn(const Math::OrientF &_orientation,
                                                                 const float _angleLonStart,
                                                                 const float _angleLonEnd,
                                                                 const float _angleLatStart,
                                                                 const float _angleLatEnd,
                                                                 const float _radius1P,
                                                                 const float _radius1M,
                                                                 const float _radius2P,
                                                                 const float _radius2M,
                                                                 const float _radius3P,
                                                                 const float _radius3M,
                                                                 const size_t _quality,
                                                                 const Math::MaterialRGB &_material,
                                                                 const uint8_t _alpha)
{
    std::vector<float> alo, ala;
    Math::IrregEllipsoidF::arcAngles(alo, ala, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);

    const size_t N = alo.size() * ala.size();
    const size_t I = (alo.size() - 1UL) * (ala.size() - 1UL) * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::IrregEllipsoidF::fillEllipsoidArcInner(
        t1, t2, t3, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, alo, ala);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::cylinder(const Math::OrientF &_orientation,
                                                     const float _length,
                                                     const float _radius1,
                                                     const float _radius2,
                                                     const size_t _quality,
                                                     const Math::MaterialRGB &_material,
                                                     const uint8_t _alpha)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));

    Math::CylinderF::fillCylinderOuter(t1, t2, _orientation, _length, _radius1, _radius2, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUAD_STRIP, N, t1, t2, _material, _alpha);

    std::free(t1);
    std::free(t2);

    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::cylinderInn(const Math::OrientF &_orientation,
                                                        const float _length,
                                                        const float _radius1,
                                                        const float _radius2,
                                                        const size_t _quality,
                                                        const Math::MaterialRGB &_material,
                                                        const uint8_t _alpha)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));

    Math::CylinderF::fillCylinderInner(t1, t2, _orientation, _length, _radius1, _radius2, _quality);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUAD_STRIP, N, t1, t2, _material, _alpha);

    std::free(t1);
    std::free(t2);

    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::cylinderArc(const Math::OrientF &_orientation,
                                                        const float _length,
                                                        const float _radiusArc,
                                                        const float _radius1,
                                                        const float _radius2,
                                                        const size_t _qualityArc,
                                                        const size_t _qualityCylinder,
                                                        const Math::MaterialRGB &_material,
                                                        const uint8_t _alpha,
                                                        const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::CylinderArcF::fillCylinderOuter(
        t1, t2, t3, _orientation, _radiusArc, _radius1, _radius2, _qualityCylinder, a);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

Data3DMaterialNormal *Data3DMaterialNormal::cylinderArcInn(const Math::OrientF &_orientation,
                                                           const float _length,
                                                           const float _radiusArc,
                                                           const float _radius1,
                                                           const float _radius2,
                                                           const size_t _qualityArc,
                                                           const size_t _qualityCylinder,
                                                           const Math::MaterialRGB &_material,
                                                           const uint8_t _alpha,
                                                           const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
    uint *t3 = reinterpret_cast<uint *>(I * sizeof(uint));

    Math::CylinderArcF::fillCylinderInner(
        t1, t2, t3, _orientation, _radiusArc, _radius1, _radius2, _qualityCylinder, a);

    Data3DMaterialNormal *result = new Data3DMaterialNormal(GL_QUADS, N, I, t1, t2, t3, _material, _alpha);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    return result;
}

}  // namespace OpenGL
}  // namespace U1
