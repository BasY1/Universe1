/*!
 * \file src/Data3D/data3dtexturealpha.h
 * \brief Open GL object with texture and per vertex alpha
 */

#ifndef OPENGL_DATA3DTEXTUREALPHA_H
#define OPENGL_DATA3DTEXTUREALPHA_H

#include "data3d.h"

#include "../Math/orientation.h"

#include <QOpenGLTexture>

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL object with texture and per vertex alpha
 */
class Data3DTextureAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    bool m_isTransparent = false;  //!< Transparency flag

    QOpenGLTexture *m_texture = nullptr;  //!< Open GL texture

    Math::Vec2F *m_coordData = nullptr;  //!< Per vertex texture coordinates array pointer
    float *m_alphaData = nullptr;        //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_coordBuffer = nullptr;  //!< Open GL buffer for texture coordinates
    QOpenGLBuffer *m_alphaBuffer = nullptr;  //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     */
    Data3DTextureAlpha(QOpenGLTexture *_texture,
                       const GLuint _glPrimitive,
                       const size_t _vertexCount,
                       const size_t _indexCount);

    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _coordData Per vertex texture coordinates data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \param _indexData Index data pointer
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DTextureAlpha(QOpenGLTexture *_texture,
                       const GLuint _glPrimitive,
                       const size_t _vertexCount,
                       const size_t _indexCount,
                       const Math::Vec3F *_vertexData,
                       const Math::Vec2F *_coordData,
                       const float *_alphaData,
                       const uint *_indexData);

    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _coordData Per vertex texture coordinates data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DTextureAlpha(QOpenGLTexture *_texture,
                              const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const Math::Vec3F *_vertexData,
                              const Math::Vec2F *_coordData,
                              const float *_alphaData)
        : Data3DTextureAlpha(_texture, _glPrimitive, _vertexCount, 0UL, _vertexData, _coordData, _alphaData, nullptr)
    {
    }

    ~Data3DTextureAlpha();  //!< Destructor

    /*!
     * \brief Getter for texture coordinates data pointer (constant version)
     * \return Vertex texture coordinates data pointer
     */
    inline const Math::Vec2F *coordData() const
    {
        return m_coordData;
    }

    /*!
     * \brief Getter for texture coordinates data pointer
     * \return Vertex texture coordinates data pointer
     */
    inline Math::Vec2F *coordData()
    {
        return m_coordData;
    }

    /*!
     * \brief Getter for alpha data pointer (constant version)
     * \return Vertex alpha data pointer
     */
    inline const float *alphaData() const
    {
        return m_alphaData;
    }

    /*!
     * \brief Getter for alpha data pointer
     * \return Vertex alpha data pointer
     */
    inline float *alphaData()
    {
        return m_alphaData;
    }

    /*!
     * \brief Setup transparency flag
     * \param _isTransparent New transparency flag
     */
    inline void setTransparent(const bool _isTransparent)
    {
        m_isTransparent = _isTransparent;
    }

    /*!
     * \brief Transparency flag getter
     * \return Transparency flag
     */
    bool isTransparent() const override;

 protected:
    /*!
     * \brief Create color Open GL buffer
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy color Open GL buffer
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind color Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release color Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;

 public:
    /*!
     * \brief Create a texture rectangle 3D object
     * \param _texture Open GL texture
     * \param _orientation Orientation of rectangle in space
     * \param _radius1 Radius 1 (within the \c normal2 in \a _orientation)
     * \param _radius2 Radius 2 (within the \c normal3 in \a _orientation)
     * \param _alpha1 Alpha for vertex 1
     * \param _alpha2 Alpha for vertex 2
     * \param _alpha3 Alpha for vertex 3
     * \param _alpha4 Alpha for vertex 4
     * \return 3D texture rectangle object
     */
    inline static Data3DTextureAlpha *rectangle(QOpenGLTexture *_texture,
                                                const Math::OrientF &_orientation,
                                                const float _radius1,
                                                const float _radius2,
                                                const uint8_t _alpha1,
                                                const uint8_t _alpha2,
                                                const uint8_t _alpha3,
                                                const uint8_t _alpha4)
    {
        static const std::vector<Math::Vec2F> t2 = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
        const std::vector<Math::Vec3F> t1 = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2};
        const std::vector<float> t3 = {
            float(_alpha1) / 255.0f, float(_alpha2) / 255.0f, float(_alpha3) / 255.0f, float(_alpha4) / 255.0f};
        Data3DTextureAlpha *result = new Data3DTextureAlpha(_texture, GL_QUADS, 4UL, t1.data(), t2.data(), t3.data());
        result->setCentralPoint(_orientation.center);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U || _alpha3 != 255U || _alpha4 != 255U);
        return result;
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DTEXTUREALPHA_H
