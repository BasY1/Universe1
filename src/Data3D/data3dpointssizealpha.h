/*!
 * \file src/Data3D/data3dpointssizealpha.h
 * \brief Open GL point-cloud object with per vertex point size and alpha
 */

#ifndef OPENGL_DATA3DPOINTSSIZEALPHA_H
#define OPENGL_DATA3DPOINTSSIZEALPHA_H

#include "data3d.h"

#include "../Math/colorrgb.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex point size and alpha
 * \details Uses uniform value for vertex color
 */
class Data3DPointsSizeAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::ColorRGB m_color;  //!< Color used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    float *m_pointSizeData = nullptr;  //!< Per vertex point size data array pointer
    float *m_alphaData = nullptr;      //!< Per vertex alpha data array pointer

    QOpenGLBuffer *m_pointSizeBuffer = nullptr;  //!< Open GL buffer for point sizes
    QOpenGLBuffer *m_alphaBuffer = nullptr;      //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _color Color used for all vertices
     */
    Data3DPointsSizeAlpha(const size_t _vertexCount, const size_t _indexCount, const Math::ColorRGB &_color);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _color Color used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsSizeAlpha(const size_t _vertexCount,
                          const size_t _indexCount,
                          const Math::Vec3F *_vertexData,
                          const float *_pointSizeData,
                          const float *_alphaData,
                          const uint *_indexData,
                          const Math::ColorRGB &_color);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _color Color used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffers. Indices are not used
     */
    inline Data3DPointsSizeAlpha(const size_t _vertexCount,
                                 const Math::Vec3F *_vertexData,
                                 const float *_pointSizeData,
                                 const float *_alphaData,
                                 const Math::ColorRGB &_color)
        : Data3DPointsSizeAlpha(_vertexCount, 0UL, _vertexData, _pointSizeData, _alphaData, nullptr, _color)
    {
    }

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

    /*!
     * \brief Setup uniform attributes for Open GL shader programs
     * \param _functions Open GL functions
     * \param _program Open GL program
     * \return Success flag
     */
    bool drawSetup(QOpenGLFunctions *_functions, QOpenGLShaderProgram *_program) override;

 protected:
    /*!
     * \brief Create point size and alpha Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy point size and alpha Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind point size and alpha Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release point size and alpha Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSSIZEALPHA_H
