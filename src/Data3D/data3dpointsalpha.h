/*!
 * \file src/Data3D/data3dpointsalpha.h
 * \brief Open GL point-cloud object with per vertex alpha
 */

#ifndef OPENGL_DATA3DPOINTSALPHA_H
#define OPENGL_DATA3DPOINTSALPHA_H

#include "data3d.h"

#include "../Math/colorrgb.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex alpha
 * \details Uses uniform values for vertex color and point size
 */
class Data3DPointsAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::ColorRGB m_color;  //!< Color used for all vertices
    float m_pointSize;       //!< Point size used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    float *m_alphaData = nullptr;            //!< Per vertex point alpha data array pointer
    QOpenGLBuffer *m_alphaBuffer = nullptr;  //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _color Color used for all vertices
     * \param _pointSize Point size used for all vertices
     */
    Data3DPointsAlpha(const size_t _vertexCount,
                      const size_t _indexCount,
                      const Math::ColorRGB &_color,
                      const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _color Color used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsAlpha(const size_t _vertexCount,
                      const size_t _indexCount,
                      const Math::Vec3F *_vertexData,
                      const float *_alphaData,
                      const uint *_indexData,
                      const Math::ColorRGB &_color,
                      const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \param _color Color used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DPointsAlpha(const size_t _vertexCount,
                             const Math::Vec3F *_vertexData,
                             const float *_alphaData,
                             const Math::ColorRGB &_color,
                             const float _pointSize)
        : Data3DPointsAlpha(_vertexCount, 0UL, _vertexData, _alphaData, nullptr, _color, _pointSize)
    {
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
     * \brief Vertex point size getter
     * \return Vertex point size
     */
    inline float pointSize() const
    {
        return m_pointSize;
    }

    /*!
     * \brief Setup vertex point size
     * \param _pointSize New vertex point size
     */
    inline void setPointSize(const float _pointSize)
    {
        m_pointSize = _pointSize;
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
     * \brief Create alpha Open GL buffer
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy alpha Open GL buffer
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind alpha Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release alpha Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSALPHA_H
