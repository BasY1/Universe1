/*!
 * \file src/Data3D/data3dtexture.h
 * \brief Open GL object with texture
 */

#ifndef OPENGL_DATA3DTEXTURE_H
#define OPENGL_DATA3DTEXTURE_H

#include "data3d.h"

#include "../Math/orientation.h"

#include <QOpenGLTexture>

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL object with texture
 * \details Uses uniform values for vertex alpha
 */
class Data3DTexture : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    uint8_t m_alpha;  //!< Alpha used for all vertices

    QOpenGLTexture *m_texture = nullptr;  //!< Open GL texture

    Math::Vec2F *m_coordData = nullptr;      //!< Per vertex texture coordinates array pointer
    QOpenGLBuffer *m_coordBuffer = nullptr;  //!< Open GL buffer for texture coordinates

 public:
    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _alpha Alpha used for all vertices
     */
    Data3DTexture(QOpenGLTexture *_texture,
                  const GLuint _glPrimitive,
                  const size_t _vertexCount,
                  const size_t _indexCount,
                  const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _coordData Per vertex texture coordinates data pointer
     * \param _indexData Index data pointer
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DTexture(QOpenGLTexture *_texture,
                  const GLuint _glPrimitive,
                  const size_t _vertexCount,
                  const size_t _indexCount,
                  const Math::Vec3F *_vertexData,
                  const Math::Vec2F *_coordData,
                  const uint *_indexData,
                  const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _texture Open GL texture
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _coordData Per vertex texture coordinates data pointer
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DTexture(QOpenGLTexture *_texture,
                         const GLuint _glPrimitive,
                         const size_t _vertexCount,
                         const Math::Vec3F *_vertexData,
                         const Math::Vec2F *_coordData,
                         const uint8_t _alpha)
        : Data3DTexture(_texture, _glPrimitive, _vertexCount, 0UL, _vertexData, _coordData, nullptr, _alpha)
    {
    }

    ~Data3DTexture();  //!< Destructor

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
     * \brief Vertex alpha getter
     * \return Vertex alpha
     */
    inline uint8_t alpha() const
    {
        return m_alpha;
    }

    /*!
     * \brief Setup vertex alpha
     * \param _alpha New vertex alpha
     */
    inline void setAlpha(const uint8_t _alpha)
    {
        m_alpha = _alpha;
    }

    /*!
     * \brief Test if \a m_alpha is lower than 255
     * \return \c true if \a m_alpha is lower than 255
     */
    bool isTransparent() const override;

    /*!
     * \brief Setup uniform attributes for Open GL shader programs
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program) override;


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
     * \param _alpha Alpha
     * \return 3D texture rectangle object
     */
    inline static Data3DTexture *rectangle(QOpenGLTexture *_texture,
                                           const Math::OrientF &_orientation,
                                           const float _radius1,
                                           const float _radius2,
                                           const uint8_t _alpha)
    {
        static const std::vector<Math::Vec2F> t2 = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
        const std::vector<Math::Vec3F> t1 = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2};

        Data3DTexture *result = new Data3DTexture(_texture, GL_QUADS, 4UL, t1.data(), t2.data(), _alpha);
        result->setCentralPoint(_orientation.center);
        return result;
    }

    /*!
     * \brief Create a texture rectangle 3D object that is visible from back
     * \param _texture Open GL texture
     * \param _orientation Orientation of rectangle in space
     * \param _radius1 Radius 1 (within the \c normal2 in \a _orientation)
     * \param _radius2 Radius 2 (within the \c normal3 in \a _orientation)
     * \param _alpha Alpha
     * \return 3D texture rectangle object
     */
    inline static Data3DTexture *rectangleInverted(QOpenGLTexture *_texture,
                                                   const Math::OrientF &_orientation,
                                                   const float _radius1,
                                                   const float _radius2,
                                                   const uint8_t _alpha)
    {
        static const std::vector<Math::Vec2F> t2 = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
        const std::vector<Math::Vec3F> t1 = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2};

        Data3DTexture *result = new Data3DTexture(_texture, GL_QUADS, 4UL, t1.data(), t2.data(), _alpha);
        result->setCentralPoint(_orientation.center);
        return result;
    }

    /*!
     * \brief Create a texture sphere 3D object - visible from outside
     * \param _texture Open GL texture
     * \param _orientation Orientation of sphere in space
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture sphere object
     */
    static Data3DTexture *sphere(QOpenGLTexture *_texture,
                                 const Math::OrientF &_orientation,
                                 const float _radius,
                                 const size_t _quality,
                                 const uint8_t _alpha);

    /*!
     * \brief Create a texture sphere 3D object - visible from inside
     * \param _texture Open GL texture
     * \param _orientation Orientation of sphere in space
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture sphere object
     */
    static Data3DTexture *sphereInn(QOpenGLTexture *_texture,
                                    const Math::OrientF &_orientation,
                                    const float _radius,
                                    const size_t _quality,
                                    const uint8_t _alpha);

    /*!
     * \brief Create a texture ellipsoid 3D object - visible from outside
     * \param _texture Open GL texture
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1 Ellipsoid radius 1
     * \param _radius2 Ellipsoid radius 2
     * \param _radius3 Ellipsoid radius 3
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture ellipsoid object
     */
    static Data3DTexture *ellipsoid(QOpenGLTexture *_texture,
                                    const Math::OrientF &_orientation,
                                    const float _radius1,
                                    const float _radius2,
                                    const float _radius3,
                                    const size_t _quality,
                                    const uint8_t _alpha);

    /*!
     * \brief Create a texture ellipsoid 3D object - visible from inside
     * \param _texture Open GL texture
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1 Ellipsoid radius 1
     * \param _radius2 Ellipsoid radius 2
     * \param _radius3 Ellipsoid radius 3
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture ellipsoid object
     */
    static Data3DTexture *ellipsoidInn(QOpenGLTexture *_texture,
                                       const Math::OrientF &_orientation,
                                       const float _radius1,
                                       const float _radius2,
                                       const float _radius3,
                                       const size_t _quality,
                                       const uint8_t _alpha);

    /*!
     * \brief Create a texture irregular ellipsoid 3D object - visible from outside
     * \param _texture Open GL texture
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1P Ellipsoid radius 1 positive
     * \param _radius1M Ellipsoid radius 1 negative
     * \param _radius2P Ellipsoid radius 2 positive
     * \param _radius2M Ellipsoid radius 2 negative
     * \param _radius3P Ellipsoid radius 3 positive
     * \param _radius3M Ellipsoid radius 3 negative
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture ellipsoid object
     */
    static Data3DTexture *irregEllipsoid(QOpenGLTexture *_texture,
                                         const Math::OrientF &_orientation,
                                         const float _radius1P,
                                         const float _radius1M,
                                         const float _radius2P,
                                         const float _radius2M,
                                         const float _radius3P,
                                         const float _radius3M,
                                         const size_t _quality,
                                         const uint8_t _alpha);

    /*!
     * \brief Create a texture irregular ellipsoid 3D object - visible from inside
     * \param _texture Open GL texture
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1P Ellipsoid radius 1 positive
     * \param _radius1M Ellipsoid radius 1 negative
     * \param _radius2P Ellipsoid radius 2 positive
     * \param _radius2M Ellipsoid radius 2 negative
     * \param _radius3P Ellipsoid radius 3 positive
     * \param _radius3M Ellipsoid radius 3 negative
     * \param _quality Circle quality
     * \param _alpha Alpha
     * \return 3D texture ellipsoid object
     */
    static Data3DTexture *irregEllipsoidInn(QOpenGLTexture *_texture,
                                            const Math::OrientF &_orientation,
                                            const float _radius1P,
                                            const float _radius1M,
                                            const float _radius2P,
                                            const float _radius2M,
                                            const float _radius3P,
                                            const float _radius3M,
                                            const size_t _quality,
                                            const uint8_t _alpha);
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DTEXTURE_H
