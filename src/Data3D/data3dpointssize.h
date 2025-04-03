/*!
 * \file src/Data3D/data3dpointssize.h
 * \brief Open GL point-cloud object with per vertex point size
 */

#ifndef OPENGL_DATA3DPOINTSSIZE_H
#define OPENGL_DATA3DPOINTSSIZE_H

#include "data3d.h"

#include "../Math/colorrgb.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex point size
 * \details Uses uniform values for vertex color and alpha
 */
class Data3DPointsSize : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::ColorRGB m_color;  //!< Color used for all vertices
    uint8_t m_alpha;         //!< Alpha used for all vertices

    float *m_pointSizeData = nullptr;  //!< Per vertex point size data array pointer

    QOpenGLBuffer *m_pointSizeBuffer = nullptr;  //!< Open GL buffer for point sizes

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     */
    Data3DPointsSize(const size_t _vertexCount,
                     const size_t _indexCount,
                     const Math::ColorRGB &_color,
                     const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _indexData Index data pointer
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsSize(const size_t _vertexCount,
                     const size_t _indexCount,
                     const Math::Vec3F *_vertexData,
                     const float *_pointSizeData,
                     const uint *_indexData,
                     const Math::ColorRGB &_color,
                     const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffers. Indices are not used
     */
    inline Data3DPointsSize(const size_t _vertexCount,
                            const Math::Vec3F *_vertexData,
                            const float *_pointSizeData,
                            const Math::ColorRGB &_color,
                            const uint8_t _alpha)
        : Data3DPointsSize(_vertexCount, 0UL, _vertexData, _pointSizeData, nullptr, _color, _alpha)
    {
    }

    ~Data3DPointsSize();  //!< Destructor

    /*!
     * \brief Getter for point size data pointer (constant version)
     * \return Vertex point size data pointer
     */
    inline const float *pointSizeData() const
    {
        return m_pointSizeData;
    }

    /*!
     * \brief Getter for point size data pointer
     * \return Vertex point size data pointer
     */
    inline float *pointSizeData()
    {
        return m_pointSizeData;
    }

    /*!
     * \brief Vertex color getter
     * \return Vertex color
     */
    inline const Math::ColorRGB &color() const
    {
        return m_color;
    }

    /*!
     * \brief Setup vertex color
     * \param _color New vertex color
     */
    inline void setColor(const Math::ColorRGB &_color)
    {
        m_color = _color;
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
     * \brief Setup uniform attributes for Open GL shader programs
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Test if \a m_alpha is lower than 255
     * \return \c true if \a m_alpha is lower than 255
     */
    bool isTransparent() const override;

 protected:
    /*!
     * \brief Create point size Open GL buffer
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy point size Open GL buffer
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind point size Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release point size Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSSIZE_H
