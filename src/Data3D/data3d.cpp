/*!
 * \file src/Data3D/data3d.cpp
 * \brief Base Open GL vertex data object implementation
 */

#include "data3d.h"

namespace U1 {
namespace OpenGL {

const size_t Data3D::MaxClipPlanes = 8UL;

const std::string Data3D::ClipPlanesUniforms = "uniform vec4 plane[8];\n"
                                               "uniform int clipPlanes;\n";

const std::string Data3D::ClipPlanesDetection =  //
    " for (int i = 0 ; i < clipPlanes ; i++){\n"
    "   gl_ClipDistance[i] = dot(vec4(pos,1.0f), plane[i]);\n"
    " }\n";

const std::string Data3D::GLSL_Version = "#version 430\n";
const std::string Data3D::VS_Header = Data3D::GLSL_Version + "layout (location = 0) in vec3 pos;\n";

const std::string Data3D::VS_Uniforms = Data3D::ClipPlanesUniforms + "uniform mat4 view;\n";

const std::string Data3D::VS_InMain = " gl_Position = view * vec4(pos, 1.0);\n" + Data3D::ClipPlanesDetection;

const std::string Data3D::FS_CamLightUniform = "uniform vec3 camera;\n"          //
                                               "uniform vec3 lightDir;\n"        //
                                               "uniform vec3 lightColor;\n"      //
                                               "uniform float lightAmbient;\n";  //

const std::string Data3D::FS_Header = Data3D::GLSL_Version + Data3D::FS_CamLightUniform;

Data3D::Data3D(const GLDataType _glDataType,
               const GLuint _glPrimitive,
               const size_t _vertexCount,
               const size_t _indexCount)
    : glDataType(_glDataType)
    , glPrimitive(_glPrimitive)
    , vertexCount(_vertexCount)
    , indexCount(_indexCount)
{
    if (vertexCount > 0UL)
        m_vertexData = reinterpret_cast<Math::Vec3F *>(std::malloc(vertexCount * sizeof(Math::Vec3F)));

    if (indexCount > 0UL)
        m_indexData = reinterpret_cast<uint *>(std::malloc(indexCount * sizeof(uint)));
}

Data3D::Data3D(const GLDataType _glDataType,
               const GLuint _glPrimitive,
               const size_t _vertexCount,
               const size_t _indexCount,
               const Math::Vec3F *_vertexData,
               const uint *_indexData)
    : glDataType(_glDataType)
    , glPrimitive(_glPrimitive)
    , vertexCount(_vertexCount)
    , indexCount(_indexCount)
{
    if (vertexCount > 0UL)
    {
        m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_vertexBuffer->create())
        {
            m_vertexBuffer->bind();
            m_vertexBuffer->allocate(_vertexData, vertexCount * sizeof(Math::Vec3F));
            m_vertexBuffer->release();
        }
        else
        {
            std::cerr << "[Data3D::constructor] Can't create m_vertexBuffer !\n";
        }
    }

    if (indexCount > 0UL)
    {
        m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (m_indexBuffer->create())
        {
            m_indexBuffer->bind();
            m_indexBuffer->allocate(_indexData, indexCount * sizeof(uint));
            m_indexBuffer->release();
        }
        else
        {
            std::cerr << "[Data3D::constructor] Can't create m_indexBuffer !\n";
        }
    }
}

Data3D::~Data3D()
{
    if (m_vertexData != nullptr)
        std::free(m_vertexData);

    if (m_indexData != nullptr)
        std::free(m_indexData);

    if (m_vertexBuffer != nullptr)
    {
        if (m_vertexBuffer->isCreated())
            m_vertexBuffer->destroy();
        delete m_vertexBuffer;
    }

    if (m_indexBuffer != nullptr)
    {
        if (m_indexBuffer->isCreated())
            m_indexBuffer->destroy();
        delete m_indexBuffer;
    }
}

bool Data3D::draw(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    _program->bind();

    if (!drawSetup(_functions, _program))
        return false;

    if (!hasBuffers())
    {
        if (!createBuffers())
            return false;
    }

    if (!bindBuffers(_program))
        return false;

    if (indexCount == 0UL)
    {
        bindClipPlanes(_program);
        _functions->glDrawArrays(glPrimitive, 0, vertexCount);
        releaseClipPlanes(_program);
    }
    else
    {
        if (!bindIndexBuffers())
            return false;

        bindClipPlanes(_program);
        _functions->glDrawElements(glPrimitive, indexCount, GL_UNSIGNED_INT, nullptr);
        releaseClipPlanes(_program);

        if (!releaseIndexBuffers())
        {
            releaseBuffers(_program);
            return false;
        }
    }

    const bool result = releaseBuffers(_program);

    _program->release();

    return result;
}

bool Data3D::drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program)
{
    Q_UNUSED(_functions)
    Q_UNUSED(_program)
    return true;
}

void Data3D::setClipPlanes(const std::vector<std::pair<Math::Vec3F, Math::Vec3F>> &_planes)
{
    if (_planes.size() > MaxClipPlanes)
        std::cerr << "Warning: setClipPlanes(" << _planes.size() << ") Can use only " << MaxClipPlanes
                  << " clipping planes!\n";

    const size_t N = std::min(MaxClipPlanes, _planes.size());

    m_clipPlanes.clear();
    m_clipPlanes.reserve(N);
    for (size_t i = 0UL; i < N; ++i)
    {
        const Math::Vec3F n = _planes.at(i).first.normalized();
        m_clipPlanes.push_back(QVector4D(n.x, n.y, n.z, Math::Vec3F().distanceToPlane(_planes.at(i).second, n)));
    }
}

void Data3D::addClipPlane(const Math::Vec3F &_planeNormal, const Math::Vec3F &_planePoint)
{
    if (m_clipPlanes.size() >= MaxClipPlanes)
    {
        std::cerr << "Error: addClipPlane(" << _planeNormal << "," << _planePoint
                  << ") Can't add clipping plane, maximum is " << MaxClipPlanes << " clip planes!\n";
        return;
    }

    const Math::Vec3F n = _planeNormal.normalized();
    m_clipPlanes.push_back(QVector4D(n.x, n.y, n.z, Math::Vec3F().distanceToPlane(_planePoint, n)));
}

void Data3D::bindClipPlanes(QOpenGLShaderProgram *_program)
{
    _program->setUniformValue("clipPlanes", GLint(m_clipPlanes.size()));
    int i = 0;
    for (const QVector4D &p : std::as_const(m_clipPlanes))
        _program->setUniformValue(QString("plane[%1]").arg(i++).toLatin1().constData(), p);

    switch (m_clipPlanes.size())
    {
    case 0UL: break;
    case 1UL: glEnable(GL_CLIP_DISTANCE0); break;
    case 2UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        break;
    case 3UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        break;
    case 4UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        glEnable(GL_CLIP_DISTANCE3);
        break;
    case 5UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        glEnable(GL_CLIP_DISTANCE3);
        glEnable(GL_CLIP_DISTANCE4);
        break;
    case 6UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        glEnable(GL_CLIP_DISTANCE3);
        glEnable(GL_CLIP_DISTANCE4);
        glEnable(GL_CLIP_DISTANCE5);
        break;
    case 7UL:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        glEnable(GL_CLIP_DISTANCE3);
        glEnable(GL_CLIP_DISTANCE4);
        glEnable(GL_CLIP_DISTANCE5);
        glEnable(GL_CLIP_DISTANCE6);
        break;
    default:
        glEnable(GL_CLIP_DISTANCE0);
        glEnable(GL_CLIP_DISTANCE1);
        glEnable(GL_CLIP_DISTANCE2);
        glEnable(GL_CLIP_DISTANCE3);
        glEnable(GL_CLIP_DISTANCE4);
        glEnable(GL_CLIP_DISTANCE5);
        glEnable(GL_CLIP_DISTANCE6);
        glEnable(GL_CLIP_DISTANCE7);
        break;
    }
}

void Data3D::releaseClipPlanes(QOpenGLShaderProgram *_program)
{
    _program->setUniformValue("clipPlanes", GLint(0));
    switch (m_clipPlanes.size())
    {
    case 0UL: break;
    case 1UL: glDisable(GL_CLIP_DISTANCE0); break;
    case 2UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        break;
    case 3UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        break;
    case 4UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        glDisable(GL_CLIP_DISTANCE3);
        break;
    case 5UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        glDisable(GL_CLIP_DISTANCE3);
        glDisable(GL_CLIP_DISTANCE4);
        break;
    case 6UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        glDisable(GL_CLIP_DISTANCE3);
        glDisable(GL_CLIP_DISTANCE4);
        glDisable(GL_CLIP_DISTANCE5);
        break;
    case 7UL:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        glDisable(GL_CLIP_DISTANCE3);
        glDisable(GL_CLIP_DISTANCE4);
        glDisable(GL_CLIP_DISTANCE5);
        glDisable(GL_CLIP_DISTANCE6);
        break;
    default:
        glDisable(GL_CLIP_DISTANCE0);
        glDisable(GL_CLIP_DISTANCE1);
        glDisable(GL_CLIP_DISTANCE2);
        glDisable(GL_CLIP_DISTANCE3);
        glDisable(GL_CLIP_DISTANCE4);
        glDisable(GL_CLIP_DISTANCE5);
        glDisable(GL_CLIP_DISTANCE6);
        glDisable(GL_CLIP_DISTANCE7);
        break;
    }
}

bool Data3D::createBuffers()
{
    if (m_vertexBuffer != nullptr)
    {
        std::cerr << "[Data3D::createBuffers] Buffers already created!\n";
        return false;
    }

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!m_vertexBuffer->create())
    {
        std::cerr << "[Data3D::createBuffers] Can't create m_vertexBuffer !\n";
        return false;
    }

    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(m_vertexData, vertexCount * sizeof(Math::Vec3F));
    m_vertexBuffer->release();

    if (!createBuffersImpl())
        return false;

    if (indexCount > 0UL)
    {
        m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        if (!m_indexBuffer->create())
        {
            std::cerr << "[Data3D::createBuffers] Can't create m_indexBuffer !\n";
            return false;
        }

        m_indexBuffer->bind();
        m_indexBuffer->allocate(m_indexData, indexCount * sizeof(uint));
        m_indexBuffer->release();
    }

    return true;
}

bool Data3D::destroyBuffers()
{
    if (m_vertexBuffer == nullptr)
    {
        std::cerr << "[Data3D::destroyBuffers] Buffers not created!\n";
        return false;
    }

    if (m_vertexBuffer->isCreated())
        m_vertexBuffer->destroy();

    delete m_vertexBuffer;
    m_vertexBuffer = nullptr;

    if (!destroyBuffersImpl())
        return false;

    if (indexCount > 0UL)
    {
        if (m_indexBuffer == nullptr)
        {
            std::cerr << "[Data3D::destroyBuffers] Index buffer not created!\n";
            return false;
        }
        if (m_indexBuffer->isCreated())
            m_indexBuffer->destroy();

        delete m_indexBuffer;
        m_indexBuffer = nullptr;
    }

    return true;
}

bool Data3D::hasBuffers() const
{
    return m_vertexBuffer != nullptr && m_vertexBuffer->isCreated();
}

bool Data3D::bindBuffers(QOpenGLShaderProgram *_program)
{
    if (m_vertexBuffer == nullptr)
    {
        std::cerr << "[Data3D::bindBuffers] m_vertexBuffer == nullptr!\n";
        return false;
    }

    if (!m_vertexBuffer->bind())
    {
        std::cerr << "[Data3D::bindBuffers] m_vertexBuffer->bind() failed!\n";
        return false;
    }

    _program->enableAttributeArray(0);
    _program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    return bindBuffersImpl(_program);
}

bool Data3D::releaseBuffers(QOpenGLShaderProgram *_program)
{
    if (m_vertexBuffer == nullptr)
    {
        std::cerr << "[Data3D::releaseBuffers] m_vertexBuffer == nullptr!\n";
        return false;
    }

    _program->disableAttributeArray(0);
    m_vertexBuffer->release();

    return releaseBuffersImpl(_program);
}

bool Data3D::bindIndexBuffers()
{
    if (indexCount == 0UL)
    {
        std::cerr << "[Data3D::bindIndexBuffers] Index count == 0!\n";
        return false;
    }

    if (m_indexBuffer == nullptr)
    {
        std::cerr << "[Data3D::bindIndexBuffers] m_indexBuffer == nullptr!\n";
        return false;
    }

    if (!m_indexBuffer->bind())
    {
        std::cerr << "[Data3D::bindIndexBuffers] m_indexBuffer->bind() failed!\n";
        return false;
    }
    return true;
}

bool Data3D::releaseIndexBuffers()
{
    if (indexCount == 0UL)
    {
        std::cerr << "[Data3D::releaseIndexBuffers] Index count = 0!\n";
        return false;
    }

    if (m_indexBuffer == nullptr)
    {
        std::cerr << "[Data3D::releaseIndexBuffers] m_indexBuffer == nullptr!\n";
        return false;
    }

    m_indexBuffer->release();

    return true;
}

}  // namespace OpenGL
}  // namespace U1
