/*!
 * \file src/Data3D/data3dmaterialsnormal.cpp
 * \brief Open GL object with per vertex material, and uniform alpha and normal
 */

#include "data3dmaterialsnormal.h"

#include "../Math/cylinder.h"
#include "../Math/cylinderarc.h"

namespace U1 {
namespace OpenGL {

const std::string Data3DMaterialsNormal::vs =      //
    Data3D::VS_Header +                            //
    "layout (location = 1) in vec3 normal;\n" +    //
    "layout (location = 2) in vec3 ambient;\n" +   //
    "layout (location = 3) in vec3 diffuse;\n" +   //
    "layout (location = 4) in vec3 specular;\n" +  //
    "layout (location = 5) in float shine;\n" +    //
    Data3D::VS_Uniforms +                          //
    "out vec3 posOut;\n" +                         //
    "out vec3 norOut;\n" +                         //
    "out vec3 ambientOut;\n" +                     //
    "out vec3 diffuseOut;\n" +                     //
    "out vec3 specularOut;\n" +                    //
    "out float shineOut;\n" +                      //
    "void main() {\n" +                            //
    " posOut = pos;\n" +                           //
    " norOut = normal;\n" +                        //
    " ambientOut = ambient;\n" +                   //
    " diffuseOut = diffuse;\n" +                   //
    " specularOut = specular;\n" +                 //
    " shineOut = shine;\n" +                       //
    Data3D::VS_InMain +                            //
    "}\n";

const std::string Data3DMaterialsNormal::fs =                   //
    Data3D::FS_Header +                                         //
    "uniform float alpha;\n" +                                  //
    "in vec3 posOut;\n" +                                       //
    "in vec3 norOut;\n" +                                       //
    "in vec3 ambientOut;\n" +                                   //
    "in vec3 diffuseOut;\n" +                                   //
    "in vec3 specularOut;\n" +                                  //
    "in float shineOut;\n" +                                    //
    "out vec4 color;\n" +                                       //
    "void main() {\n" +                                         //
    " vec3 norm = normalize(norOut);\n" +                       //
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

Data3DMaterialsNormal::Data3DMaterialsNormal(const GLuint _glPrimitive,
                                             const size_t _vertexCount,
                                             const size_t _indexCount,
                                             const uint8_t _alpha)
    : Data3D(GL_MATERIAL_VERTEX_Normal, _glPrimitive, _vertexCount, _indexCount)
    , m_alpha(_alpha)
{
    if (vertexCount > 0UL)
    {
        m_normalData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_ambientData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_diffuseData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_specularData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));
        m_shineData = reinterpret_cast<float *>(std::malloc(vertexCount * sizeof(float)));
    }
}

Data3DMaterialsNormal::Data3DMaterialsNormal(const GLuint _glPrimitive,
                                             const size_t _vertexCount,
                                             const size_t _indexCount,
                                             const Math::Vec3F *_vertexData,
                                             const Math::Vec3F *_normalData,
                                             const Math::Vec3F *_ambientData,
                                             const Math::Vec3F *_diffuseData,
                                             const Math::Vec3F *_specularData,
                                             const float *_shineData,
                                             const uint *_indexData,
                                             const uint8_t _alpha)
    : Data3D(GL_MATERIAL_VERTEX_Normal, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
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
            std::cerr << "[Data3DMaterialsNormal::constructor] Can't create m_normalBuffer !\n";
        }

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
            std::cerr << "[Data3DMaterialsNormal::constructor] Can't create m_ambientBuffer !\n";
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
            std::cerr << "[Data3DMaterialsNormal::constructor] Can't create m_diffuseBuffer !\n";
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
            std::cerr << "[Data3DMaterialsNormal::constructor] Can't create m_specularBuffer !\n";
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
            std::cerr << "[Data3DMaterialsNormal::constructor] Can't create m_shineBuffer !\n";
        }
    }
}

Data3DMaterialsNormal::~Data3DMaterialsNormal()
{
    if (m_normalData != nullptr)
        std::free(m_normalData);
    if (m_ambientData != nullptr)
        std::free(m_ambientData);
    if (m_diffuseData != nullptr)
        std::free(m_diffuseData);
    if (m_specularData != nullptr)
        std::free(m_specularData);
    if (m_shineData != nullptr)
        std::free(m_shineData);

    if (m_normalBuffer != nullptr)
    {
        if (m_normalBuffer->isCreated())
            m_normalBuffer->destroy();
        delete m_normalBuffer;
    }

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
}

bool Data3DMaterialsNormal::isTransparent() const
{
    return m_alpha != 255U;
}

bool Data3DMaterialsNormal::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    _program->setUniformValue("alpha", float(m_alpha) / 255.0f);
    return true;
}

bool Data3DMaterialsNormal::createBuffersImpl()
{
    m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_normalBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_normalBuffer->create())
    {
        std::cerr << "[Data3DMaterialsNormal::createBuffersImpl] Can't create m_normalBuffer !\n";
        return false;
    }

    m_normalBuffer->bind();
    m_normalBuffer->allocate(m_normalData, vertexCount * sizeof(Math::Vec3F));
    m_normalBuffer->release();

    m_ambientBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_ambientBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_ambientBuffer->create())
    {
        std::cerr << "[Data3DMaterialsNormal::createBuffersImpl] Can't create m_ambientBuffer !\n";
        return false;
    }

    m_ambientBuffer->bind();
    m_ambientBuffer->allocate(m_ambientData, vertexCount * sizeof(Math::Vec3F));
    m_ambientBuffer->release();

    m_diffuseBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_diffuseBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_diffuseBuffer->create())
    {
        std::cerr << "[Data3DMaterialsNormal::createBuffersImpl] Can't create m_diffuseBuffer !\n";
        return false;
    }

    m_diffuseBuffer->bind();
    m_diffuseBuffer->allocate(m_diffuseData, vertexCount * sizeof(Math::Vec3F));
    m_diffuseBuffer->release();

    m_specularBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_specularBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_specularBuffer->create())
    {
        std::cerr << "[Data3DMaterialsNormal::createBuffersImpl] Can't create m_specularBuffer !\n";
        return false;
    }

    m_specularBuffer->bind();
    m_specularBuffer->allocate(m_specularData, vertexCount * sizeof(Math::Vec3F));
    m_specularBuffer->release();

    m_shineBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_shineBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_shineBuffer->create())
    {
        std::cerr << "[Data3DMaterialsNormal::createBuffersImpl] Can't create m_shineBuffer !\n";
        return false;
    }

    m_shineBuffer->bind();
    m_shineBuffer->allocate(m_shineData, vertexCount * sizeof(float));
    m_shineBuffer->release();

    return true;
}

bool Data3DMaterialsNormal::destroyBuffersImpl()
{
    if (m_normalBuffer->isCreated())
        m_normalBuffer->destroy();

    delete m_normalBuffer;
    m_normalBuffer = nullptr;

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

bool Data3DMaterialsNormal::bindBuffersImpl(QOpenGLShaderProgram *_program)
{
    if (!m_normalBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsNormal::bindBuffersImpl] m_normalBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(1, GL_FLOAT, 0, 3);

    if (!m_ambientBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsNormal::bindBuffersImpl] m_ambientBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(2);
    _program->setAttributeBuffer(2, GL_FLOAT, 0, 3);

    if (!m_diffuseBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsNormal::bindBuffersImpl] m_diffuseBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(3);
    _program->setAttributeBuffer(3, GL_FLOAT, 0, 3);

    if (!m_specularBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsNormal::bindBuffersImpl] m_specularBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(4);
    _program->setAttributeBuffer(4, GL_FLOAT, 0, 3);

    if (!m_shineBuffer->bind())
    {
        std::cerr << "[Data3DMaterialsNormal::bindBuffersImpl] m_shineBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(5);
    _program->setAttributeBuffer(5, GL_FLOAT, 0, 1);

    return true;
}

bool Data3DMaterialsNormal::releaseBuffersImpl(QOpenGLShaderProgram *_program)
{
    _program->disableAttributeArray(1);
    _program->disableAttributeArray(2);
    _program->disableAttributeArray(3);
    _program->disableAttributeArray(4);
    _program->disableAttributeArray(5);
    m_normalBuffer->release();
    m_ambientBuffer->release();
    m_diffuseBuffer->release();
    m_specularBuffer->release();
    m_shineBuffer->release();
    return true;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::cylinder(const Math::OrientF &_orientation,
                                                       const float _length,
                                                       const float _radius1,
                                                       const float _radius2,
                                                       const size_t _quality,
                                                       const Math::MaterialRGB &_material1,
                                                       const Math::MaterialRGB &_material2,
                                                       const uint8_t _alpha)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    Math::CylinderF::fillCylinderOuter(t1,
                                       t2,
                                       t3,
                                       t4,
                                       t5,
                                       t6,
                                       _orientation,
                                       _material1.ambient.toVec3F(),
                                       _material2.ambient.toVec3F(),
                                       _material1.diffuse.toVec3F(),
                                       _material2.diffuse.toVec3F(),
                                       _material1.specular.toVec3F(),
                                       _material2.specular.toVec3F(),
                                       _material1.shine,
                                       _material2.shine,
                                       _length,
                                       _radius1,
                                       _radius2,
                                       _quality);

    Data3DMaterialsNormal *result = new Data3DMaterialsNormal(GL_QUAD_STRIP, N, t1, t2, t3, t4, t5, t6, _alpha);
    result->setCentralPoint(_orientation.center + _orientation.normal1 * (_length * 0.5f));

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::cylinderInn(const Math::OrientF &_orientation,
                                                          const float _length,
                                                          const float _radius1,
                                                          const float _radius2,
                                                          const size_t _quality,
                                                          const Math::MaterialRGB &_material1,
                                                          const Math::MaterialRGB &_material2,
                                                          const uint8_t _alpha)
{
    const size_t N = Math::CylinderF::cylinderVertexCount(_quality);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    Math::CylinderF::fillCylinderInner(t1,
                                       t2,
                                       t3,
                                       t4,
                                       t5,
                                       t6,
                                       _orientation,
                                       _material1.ambient.toVec3F(),
                                       _material2.ambient.toVec3F(),
                                       _material1.diffuse.toVec3F(),
                                       _material2.diffuse.toVec3F(),
                                       _material1.specular.toVec3F(),
                                       _material2.specular.toVec3F(),
                                       _material1.shine,
                                       _material2.shine,
                                       _length,
                                       _radius1,
                                       _radius2,
                                       _quality);

    Data3DMaterialsNormal *result = new Data3DMaterialsNormal(GL_QUAD_STRIP, N, t1, t2, t3, t4, t5, t6, _alpha);
    result->setCentralPoint(_orientation.center + _orientation.normal1 * (_length * 0.5f));

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::cylinderArc(const Math::OrientF &_orientation,
                                                          const float _length,
                                                          const float _radiusArc,
                                                          const float _radius1,
                                                          const float _radius2,
                                                          const size_t _qualityArc,
                                                          const size_t _qualityCylinder,
                                                          const Math::MaterialRGB &_material1,
                                                          const Math::MaterialRGB &_material2,
                                                          const uint8_t _alpha,
                                                          const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));
    uint *t7 = reinterpret_cast<uint *>(std::malloc(I * sizeof(uint)));

    Math::CylinderArcF::fillCylinderOuter(t1,
                                          t2,
                                          t3,
                                          t4,
                                          t5,
                                          t6,
                                          t7,
                                          _orientation,
                                          _material1.ambient.toVec3F(),
                                          _material2.ambient.toVec3F(),
                                          _material1.diffuse.toVec3F(),
                                          _material2.diffuse.toVec3F(),
                                          _material1.specular.toVec3F(),
                                          _material2.specular.toVec3F(),
                                          _material1.shine,
                                          _material2.shine,
                                          _radiusArc,
                                          _radius1,
                                          _radius2,
                                          _qualityCylinder,
                                          a);

    Data3DMaterialsNormal *result = new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, t7, _alpha);
    result->setCentralPoint(_orientation.center);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);
    std::free(t7);
    return result;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::cylinderArcInn(const Math::OrientF &_orientation,
                                                             const float _length,
                                                             const float _radiusArc,
                                                             const float _radius1,
                                                             const float _radius2,
                                                             const size_t _qualityArc,
                                                             const size_t _qualityCylinder,
                                                             const Math::MaterialRGB &_material1,
                                                             const Math::MaterialRGB &_material2,
                                                             const uint8_t _alpha,
                                                             const float _offsetAngle)
{
    std::vector<float> a;
    Math::CylinderArcF::cylinderArcAngles(a, _radiusArc, _length, _qualityArc, _offsetAngle);

    const size_t C = Math::circlePointCount(_qualityCylinder);
    const size_t N = a.size() * (C + 1UL);
    const size_t I = (a.size() - 1UL) * C * 4UL;

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));
    uint *t7 = reinterpret_cast<uint *>(std::malloc(I * sizeof(uint)));

    Math::CylinderArcF::fillCylinderInner(t1,
                                          t2,
                                          t3,
                                          t4,
                                          t5,
                                          t6,
                                          t7,
                                          _orientation,
                                          _material1.ambient.toVec3F(),
                                          _material2.ambient.toVec3F(),
                                          _material1.diffuse.toVec3F(),
                                          _material2.diffuse.toVec3F(),
                                          _material1.specular.toVec3F(),
                                          _material2.specular.toVec3F(),
                                          _material1.shine,
                                          _material2.shine,
                                          _radiusArc,
                                          _radius1,
                                          _radius2,
                                          _qualityCylinder,
                                          a);

    Data3DMaterialsNormal *result = new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, t7, _alpha);
    result->setCentralPoint(_orientation.center);

    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);
    std::free(t7);
    return result;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::path(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                                                   const float _radius,
                                                   const size_t _quality,
                                                   const uint8_t _alpha,
                                                   const bool _inverted)
{
    if (_path.size() < 2UL)
    {
        std::cerr << "Error Data3DMaterialNormal::path(" << _path.size() << ") short path, need 2 points!\n";
        return nullptr;
    }

    const std::vector<Math::Vec2F> &cp = Math::Circle2F::unitCircle(_quality).first;
    const size_t C = cp.size();
    const size_t CO = C + 1UL;
    const size_t PO = _path.size() - 1UL;
    const size_t N = CO * _path.size();
    const size_t I = C * PO * 4UL;
    std::vector<std::pair<size_t, size_t>> pool = Math::createPool(N);

    Math::Vec3F min = Math::Vec3F::maximumValue();
    Math::Vec3F max = Math::Vec3F::lowestValue();
    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    if (pool.empty())
    {
        for (size_t p = 0UL; p < _path.size(); ++p)
        {
            const Math::OrientF &o = _path[p].first;
            const Math::Vec3F ca = _path[p].second.darker().toVec3F();
            const Math::Vec3F cd = _path[p].second.toVec3F();
            for (size_t c = 0UL; c < CO; ++c)
            {
                const Math::Vec2F &p2 = (c == C) ? cp[0] : cp[c];
                const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                const Math::Vec3F pp = o.center + nn * _radius;
                const uint ji = p * CO + c;
                t1[ji] = pp;
                t2[ji] = nn;
                t3[ji] = ca;
                t4[ji] = cd;
                pp.updateRange(min, max);
            }
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Math::Vec3F, Math::Vec3F>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, C, CO, _radius](std::pair<Math::Vec3F, Math::Vec3F> &_outRange,
                                    Math::Vec3F *_t1,
                                    Math::Vec3F *_t2,
                                    Math::Vec3F *_t3,
                                    Math::Vec3F *_t4,
                                    const std::pair<Math::OrientF, Math::ColorRGB> *__path,
                                    const Math::Vec2F *_cp) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const size_t p = i / CO;
                        const size_t c = i % CO;
                        const Math::OrientF &o = __path[p].first;
                        const Math::Vec2F &p2 = (c == C) ? _cp[0] : _cp[c];
                        const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                        const Math::Vec3F pp = o.center + nn * _radius;
                        const uint ji = p * CO + c;

                        _t1[ji] = pp;
                        _t2[ji] = nn;
                        _t3[ji] = __path[p].second.darker().toVec3F();
                        _t4[ji] = __path[p].second.toVec3F();

                        pp.updateRange(_outRange.first, _outRange.second);
                    }
                },
                std::ref(tData[tt++]),
                t1,
                t2,
                t3,
                t4,
                _path.data(),
                cp.data()));

        for (std::thread &t : threads)
            t.join();

        for (std::pair<Math::Vec3F, Math::Vec3F> &t : tData)
            Math::Vec3F::updateRange(min, max, t);
    }

    const std::vector<uint> &uc = _inverted ? Math::PlaneIndices::getQuadIndexesInverted(_path.size(), CO).first
                                            : Math::PlaneIndices::getQuadIndexes(_path.size(), CO).first;

    Math::setConstantData<Math::Vec3F, size_t>(t5, Math::Vec3F(1, 1, 1), N, pool);
    Math::setConstantData<float, size_t>(t6, 32.0f, N, pool);

    Data3DMaterialsNormal *result =
        new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, uc.data(), _alpha);

    result->setCentralPoint((min + max) * 0.5f);
    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

Data3DMaterialsNormal *Data3DMaterialsNormal::path(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                                                   const Math::Vec3F &_centerPoint,
                                                   const float _radius,
                                                   const size_t _quality,
                                                   const uint8_t _alpha,
                                                   const bool _inverted)
{
    if (_path.size() < 2UL)
    {
        std::cerr << "Error Data3DMaterialNormal::path(" << _path.size() << ") short path, need 2 points!\n";
        return nullptr;
    }

    const std::vector<Math::Vec2F> &cp = Math::Circle2F::unitCircle(_quality).first;
    const size_t C = cp.size();
    const size_t CO = C + 1UL;
    const size_t PO = _path.size() - 1UL;
    const size_t N = CO * _path.size();
    const size_t I = C * PO * 4UL;
    std::vector<std::pair<size_t, size_t>> pool = Math::createPool(N);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    if (pool.empty())
    {
        for (size_t p = 0UL; p < _path.size(); ++p)
        {
            const Math::OrientF &o = _path[p].first;
            const Math::Vec3F ca = _path[p].second.darker().toVec3F();
            const Math::Vec3F cd = _path[p].second.toVec3F();
            for (size_t c = 0UL; c < CO; ++c)
            {
                const Math::Vec2F &p2 = (c == C) ? cp[0] : cp[c];
                const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                const uint ji = p * CO + c;
                t1[ji] = o.center + nn * _radius;
                t2[ji] = nn;
                t3[ji] = ca;
                t4[ji] = cd;
            }
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, C, CO, _radius](Math::Vec3F *_t1,
                                    Math::Vec3F *_t2,
                                    Math::Vec3F *_t3,
                                    Math::Vec3F *_t4,
                                    const std::pair<Math::OrientF, Math::ColorRGB> *__path,
                                    const Math::Vec2F *_cp) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const size_t p = i / CO;
                        const size_t c = i % CO;
                        const Math::OrientF &o = __path[p].first;
                        const Math::Vec2F &p2 = (c == C) ? _cp[0] : _cp[c];
                        const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                        const uint ji = p * CO + c;
                        _t1[ji] = o.center + nn * _radius;
                        _t2[ji] = nn;
                        _t3[ji] = __path[p].second.darker().toVec3F();
                        _t4[ji] = __path[p].second.toVec3F();
                    }
                },
                t1,
                t2,
                t3,
                t4,
                _path.data(),
                cp.data()));

        for (std::thread &t : threads)
            t.join();
    }

    const std::vector<uint> &uc = _inverted ? Math::PlaneIndices::getQuadIndexesInverted(_path.size(), CO).first
                                            : Math::PlaneIndices::getQuadIndexes(_path.size(), CO).first;

    Math::setConstantData<Math::Vec3F, size_t>(t5, Math::Vec3F(1, 1, 1), N, pool);
    Math::setConstantData<float, size_t>(t6, 32.0f, N, pool);

    Data3DMaterialsNormal *result =
        new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, uc.data(), _alpha);

    result->setCentralPoint(_centerPoint);
    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

Data3DMaterialsNormal *
Data3DMaterialsNormal::path(const std::vector<std::pair<Math::OrientF, Math::MaterialRGB>> &_path,
                            const float _radius,
                            const size_t _quality,
                            const uint8_t _alpha,
                            const bool _inverted)
{
    if (_path.size() < 2UL)
    {
        std::cerr << "Error Data3DMaterialNormal::path(" << _path.size() << ") short path, need 2 points!\n";
        return nullptr;
    }

    const std::vector<Math::Vec2F> &cp = Math::Circle2F::unitCircle(_quality).first;
    const size_t C = cp.size();
    const size_t CO = C + 1UL;
    const size_t PO = _path.size() - 1UL;
    const size_t N = CO * _path.size();
    const size_t I = C * PO * 4UL;
    std::vector<std::pair<size_t, size_t>> pool = Math::createPool(N);

    Math::Vec3F min = Math::Vec3F::maximumValue();
    Math::Vec3F max = Math::Vec3F::lowestValue();
    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    if (pool.empty())
    {
        for (size_t p = 0UL; p < _path.size(); ++p)
        {
            const Math::OrientF &o = _path[p].first;
            const Math::Vec3F c3 = _path[p].second.ambient.toVec3F();
            const Math::Vec3F c4 = _path[p].second.diffuse.toVec3F();
            const Math::Vec3F c5 = _path[p].second.specular.toVec3F();
            const float c6 = _path[p].second.shine;
            for (size_t c = 0UL; c < CO; ++c)
            {
                const Math::Vec2F &p2 = (c == C) ? cp[0] : cp[c];
                const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                const Math::Vec3F pp = o.center + nn * _radius;
                const uint ji = p * CO + c;
                t1[ji] = pp;
                t2[ji] = nn;
                t3[ji] = c3;
                t4[ji] = c4;
                t5[ji] = c5;
                t6[ji] = c6;
                pp.updateRange(min, max);
            }
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Math::Vec3F, Math::Vec3F>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, C, CO, _radius](std::pair<Math::Vec3F, Math::Vec3F> &_outRange,
                                    Math::Vec3F *_t1,
                                    Math::Vec3F *_t2,
                                    Math::Vec3F *_t3,
                                    Math::Vec3F *_t4,
                                    Math::Vec3F *_t5,
                                    float *_t6,
                                    const std::pair<Math::OrientF, Math::MaterialRGB> *__path,
                                    const Math::Vec2F *_cp) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const size_t p = i / CO;
                        const size_t c = i % CO;
                        const Math::OrientF &o = __path[p].first;
                        const Math::Vec2F &p2 = (c == C) ? _cp[0] : _cp[c];
                        const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                        const Math::Vec3F pp = o.center + nn * _radius;
                        const uint ji = p * CO + c;

                        _t1[ji] = pp;
                        _t2[ji] = nn;
                        _t3[ji] = __path[p].second.ambient.toVec3F();
                        _t4[ji] = __path[p].second.diffuse.toVec3F();
                        _t5[ji] = __path[p].second.specular.toVec3F();
                        _t6[ji] = __path[p].second.shine;

                        pp.updateRange(_outRange.first, _outRange.second);
                    }
                },
                std::ref(tData[tt++]),
                t1,
                t2,
                t3,
                t4,
                t5,
                t6,
                _path.data(),
                cp.data()));

        for (std::thread &t : threads)
            t.join();

        for (std::pair<Math::Vec3F, Math::Vec3F> &t : tData)
            Math::Vec3F::updateRange(min, max, t);
    }

    const std::vector<uint> &uc = _inverted ? Math::PlaneIndices::getQuadIndexesInverted(_path.size(), CO).first
                                            : Math::PlaneIndices::getQuadIndexes(_path.size(), CO).first;

    Data3DMaterialsNormal *result =
        new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, uc.data(), _alpha);

    result->setCentralPoint((min + max) * 0.5f);
    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

Data3DMaterialsNormal *
Data3DMaterialsNormal::path(const std::vector<std::pair<Math::OrientF, Math::MaterialRGB>> &_path,
                            const Math::Vec3F &_centerPoint,
                            const float _radius,
                            const size_t _quality,
                            const uint8_t _alpha,
                            const bool _inverted)
{
    if (_path.size() < 2UL)
    {
        std::cerr << "Error Data3DMaterialNormal::path(" << _path.size() << ") short path, need 2 points!\n";
        return nullptr;
    }

    const std::vector<Math::Vec2F> &cp = Math::Circle2F::unitCircle(_quality).first;
    const size_t C = cp.size();
    const size_t CO = C + 1UL;
    const size_t PO = _path.size() - 1UL;
    const size_t N = CO * _path.size();
    const size_t I = C * PO * 4UL;
    std::vector<std::pair<size_t, size_t>> pool = Math::createPool(N);

    Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    Math::Vec3F *t5 = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
    float *t6 = reinterpret_cast<float *>(std::malloc(N * sizeof(float)));

    if (pool.empty())
    {
        for (size_t p = 0UL; p < _path.size(); ++p)
        {
            const Math::OrientF &o = _path[p].first;
            const Math::Vec3F c3 = _path[p].second.ambient.toVec3F();
            const Math::Vec3F c4 = _path[p].second.diffuse.toVec3F();
            const Math::Vec3F c5 = _path[p].second.specular.toVec3F();
            const float c6 = _path[p].second.shine;
            for (size_t c = 0UL; c < CO; ++c)
            {
                const Math::Vec2F &p2 = (c == C) ? cp[0] : cp[c];
                const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                const Math::Vec3F pp = o.center + nn * _radius;
                const uint ji = p * CO + c;
                t1[ji] = pp;
                t2[ji] = nn;
                t3[ji] = c3;
                t4[ji] = c4;
                t5[ji] = c5;
                t6[ji] = c6;
            }
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, C, CO, _radius](Math::Vec3F *_t1,
                                    Math::Vec3F *_t2,
                                    Math::Vec3F *_t3,
                                    Math::Vec3F *_t4,
                                    Math::Vec3F *_t5,
                                    float *_t6,
                                    const std::pair<Math::OrientF, Math::MaterialRGB> *__path,
                                    const Math::Vec2F *_cp) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const size_t p = i / CO;
                        const size_t c = i % CO;
                        const Math::OrientF &o = __path[p].first;
                        const Math::Vec2F &p2 = (c == C) ? _cp[0] : _cp[c];
                        const Math::Vec3F nn = (o.normal2 * p2.x + o.normal3 * p2.y).normalized();
                        const uint ji = p * CO + c;
                        _t1[ji] = o.center + nn * _radius;
                        _t2[ji] = nn;
                        _t3[ji] = __path[p].second.ambient.toVec3F();
                        _t4[ji] = __path[p].second.diffuse.toVec3F();
                        _t5[ji] = __path[p].second.specular.toVec3F();
                        _t6[ji] = __path[p].second.shine;
                    }
                },
                t1,
                t2,
                t3,
                t4,
                t5,
                t6,
                _path.data(),
                cp.data()));

        for (std::thread &t : threads)
            t.join();
    }

    const std::vector<uint> &uc = _inverted ? Math::PlaneIndices::getQuadIndexesInverted(_path.size(), CO).first
                                            : Math::PlaneIndices::getQuadIndexes(_path.size(), CO).first;

    Data3DMaterialsNormal *result =
        new Data3DMaterialsNormal(GL_QUADS, N, I, t1, t2, t3, t4, t5, t6, uc.data(), _alpha);

    result->setCentralPoint(_centerPoint);
    std::free(t1);
    std::free(t2);
    std::free(t3);
    std::free(t4);
    std::free(t5);
    std::free(t6);

    return result;
}

}  // namespace OpenGL
}  // namespace U1
