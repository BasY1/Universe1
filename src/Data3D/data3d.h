/*!
 * \file src/Data3D/data3d.h
 * \brief Base Open GL vertex data object
 */

#ifndef OPENGL_DATA3D_H
#define OPENGL_DATA3D_H

#include "../Math/vec3.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

namespace U1 {
namespace OpenGL {

/*! \brief Base Open GL vertex data object */
class Data3D
{
 public:
    /*! \brief Supported types for Open GL vertex data object */
    enum GLDataType : int
    {
        GL_POINTS_Base = 0,        //!< Standard point-cloud object (Vertices has the same size, color and alpha)
        GL_POINTS_Size,            //!< Point-cloud object with per vertex size (Vertices has the same color and alpha)
        GL_POINTS_Color,           //!< Point-cloud object with per vertex color (Vertices has the same color and size)
        GL_POINTS_Alpha,           //!< Point-cloud object with per vertex alpha (Vertices has the same size and alpha)
        GL_POINTS_SizeAlpha,       //!< Point-cloud object with per vertex size and alpha (Vertices has the same color)
        GL_POINTS_ColorAlpha,      //!< Point-cloud object with per vertex color and alpha (Vertices has the same size)
        GL_POINTS_ColorSize,       //!< Point-cloud object with per vertex color and size (Vertices has the same alpha)
        GL_POINTS_ColorAlphaSize,  //!< Point-cloud object with per vertex color, alpha and size

        GL_TEXTURE_Base,   //!< Polygon like objects with textures and texture coordinates
        GL_TEXTURE_Alpha,  //!< Polygon like objects with textures and texture coordinates and per vertex alpha

        GL_MATERIAL_SINGLE_Base,         //!< Polygon like objects
        GL_MATERIAL_SINGLE_Normal,       //!< Polygon like objects with per vertex normal
        GL_MATERIAL_SINGLE_Alpha,        //!< Polygon like objects with per vertex alpha
        GL_MATERIAL_SINGLE_NormalAlpha,  //!< Polygon like objects with per vertex normal and alpha
        GL_MATERIAL_VERTEX_Base,         //!< Polygon like objects with per vertex material
        GL_MATERIAL_VERTEX_Normal,       //!< Polygon like objects with per vertex material and normal
        GL_MATERIAL_VERTEX_Alpha,        //!< Polygon like objects with per vertex material and alpha
        GL_MATERIAL_VERTEX_NormalAlpha,  //!< Polygon like objects with per vertex material, normal and alpha
    };

    static const size_t MaxClipPlanes;             //!< Maximal count of clipping planes
    static const std::string ClipPlanesUniforms;   //!< Uniform clip-plane variable declarations for vertex shader
    static const std::string ClipPlanesDetection;  //!< Clip-plane calculation algorithm for vertex shader

    static const std::string GLSL_Version;  //!< General vertex shared program version
    static const std::string VS_Header;     //!< General vertex shared program header - version + position buffer
    static const std::string VS_Uniforms;   //!< General vertex shared program uniforms - clip-planes + view matrix
    static const std::string VS_InMain;     //!< General vertex shared program calculation - clip-planes + gl_Position

    const GLDataType glDataType;  //!< Open GL data type
    const GLuint glPrimitive;     //!< Open GL primitive to draw (\c GL_POINTS, \c GL_TRIANGLES, \c GL_QUADS, ...)

    const size_t vertexCount;  //!< Count of vertices
    const size_t indexCount;   //!< Count of indices

 protected:
    Math::Vec3F *m_vertexData = nullptr;  //!< Vertex data pointer
    uint *m_indexData = nullptr;          //!< Index data pointer

    QOpenGLBuffer *m_vertexBuffer = nullptr;  //!< Open GL buffer for vertices
    QOpenGLBuffer *m_indexBuffer = nullptr;   //!< Open GL buffer for indices

    std::vector<QVector4D> m_clipPlanes = {};  //!< Clipping planes

    Math::Vec3F m_centralPoint = {};  //!< Average vertex position

    /*!
     * \brief Protected constructor
     * \param _glDataType Open GL data type
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \details Allocate memory for vertices and indices if needed
     */
    explicit Data3D(const GLDataType _glDataType,
                    const GLuint _glPrimitive,
                    const size_t _vertexCount,
                    const size_t _indexCount);

    /*!
     * \brief Protected constructor
     * \param _glDataType Open GL data type
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex data pointer
     * \param _indexData Index data pointer
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    explicit Data3D(const GLDataType _glDataType,
                    const GLuint _glPrimitive,
                    const size_t _vertexCount,
                    const size_t _indexCount,
                    const Math::Vec3F *_vertexData,
                    const uint *_indexData);

    /*!
     * \brief Protected constructor
     * \param _glDataType Open GL data type
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex data pointer
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline explicit Data3D(const GLDataType _glDataType,
                           const GLuint _glPrimitive,
                           const size_t _vertexCount,
                           const Math::Vec3F *_vertexData)
        : Data3D(_glDataType, _glPrimitive, _vertexCount, 0UL, _vertexData, nullptr)
    {
    }

 public:
    /*!
     * \brief Destructor
     * \details Free vertex and index data. Destroys Open GL buffers if still exist
     */
    virtual ~Data3D();

    /*!
     * \brief Getter for vertex data pointer (constant version)
     * \return Vertex data pointer
     */
    inline const Math::Vec3F *getVertexData() const
    {
        return m_vertexData;
    }

    /*!
     * \brief Getter for vertex data pointer
     * \return Vertex data pointer
     */
    inline Math::Vec3F *getVertexData()
    {
        return m_vertexData;
    }

    /*!
     * \brief Getter for index data pointer (constant version)
     * \return Index data pointer
     */
    inline const uint *getIndexData() const
    {
        return m_indexData;
    }

    /*!
     * \brief Getter for index data pointer
     * \return Index data pointer
     */
    inline uint *getIndexData()
    {
        return m_indexData;
    }

    /*!
     * \brief Getter for clipping planes array
     * \return Clipping planes
     */
    inline const std::vector<QVector4D> &clipPlanes() const
    {
        return m_clipPlanes;
    };

    /*!
     * \brief Setup new clipping planes
     * \param _planes New clipping planes, collection of pairs: plane-normal (\c first) and plane-point (\c second)
     */
    void setClipPlanes(const std::vector<std::pair<Math::Vec3F, Math::Vec3F>> &_planes);

    /*!
     * \brief Setup single clipping plane
     * \param _planeNormal Clipping plane normal
     * \param _planePoint Clipping plane point
     */
    inline void setClipPlane(const Math::Vec3F &_planeNormal, const Math::Vec3F &_planePoint = {})
    {
        setClipPlanes({{_planeNormal.normalized(), _planePoint}});
    }

    /*!
     * \brief Append new clipping plane
     * \param _planeNormal Clipping plane normal
     * \param _planePoint Clipping plane point
     */
    void addClipPlane(const Math::Vec3F &_planeNormal, const Math::Vec3F &_planePoint = {});

    /*!
     * \brief Object central point getter
     * \return Average vertex position
     */
    inline const Math::Vec3F &centralPoint() const
    {
        return m_centralPoint;
    }

    /*!
     * \brief Setup average vertex position
     * \param _centralPoint New average vertex position
     */
    inline void setCentralPoint(const Math::Vec3F &_centralPoint)
    {
        m_centralPoint = _centralPoint;
    }

    /*!
     * \brief Draw object within the current Open GL context
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool draw(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program);

    /*!
     * \brief Setup shader uniform attributes
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program);

    /*!
     * \brief Bind clipping planes
     * \param _program Open GL program
     * \return
     */
    virtual void bindClipPlanes(QOpenGLShaderProgram *_program);

    /*!
     * \brief Release clipping planes
     * \param _program Open GL program
     * \return
     */
    virtual void releaseClipPlanes(QOpenGLShaderProgram *_program);

    /*!
     * \brief Create Open GL buffers
     * \return Success flag
     */
    virtual bool createBuffers() final;

    /*!
     * \brief Destroy Open GL buffers
     * \return Success flag
     */
    virtual bool destroyBuffers() final;

    /*!
     * \brief Test if Open GL buffers exist
     * \return \c true when Open GL buffers are ready to use
     */
    virtual bool hasBuffers() const final;

    /*!
     * \brief Bind Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool bindBuffers(QOpenGLShaderProgram *_program) final;

    /*!
     * \brief Release Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool releaseBuffers(QOpenGLShaderProgram *_program) final;

    /*!
     * \brief Bind index buffer
     * \return Success flag
     */
    virtual bool bindIndexBuffers() final;

    /*!
     * \brief Release index buffer
     * \return Success flag
     */
    virtual bool releaseIndexBuffers() final;

    /*!
     * \brief Getter for transparency flag
     * \return \c true if any vertex is transparent
     */
    virtual bool isTransparent() const = 0;

 protected:
    /*!
     * \brief Create additional Open GL buffers
     * \return Success flag
     */
    virtual bool createBuffersImpl() = 0;

    /*!
     * \brief Destroy additional Open GL buffers
     * \return Success flag
     */
    virtual bool destroyBuffersImpl() = 0;

    /*!
     * \brief Bind additional Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool bindBuffersImpl(QOpenGLShaderProgram *_program) = 0;

    /*!
     * \brief Release additional Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    virtual bool releaseBuffersImpl(QOpenGLShaderProgram *_program) = 0;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3D_H
