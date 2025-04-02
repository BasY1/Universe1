/*!
 * \file src/Data3D/data3dpointscoloralpha.h
 * \brief Open GL point-cloud object with per vertex color and alpha
 */

#ifndef OPENGL_DATA3DPOINTSCOLORALPHA_H
#define OPENGL_DATA3DPOINTSCOLORALPHA_H

#include "data3d.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex color and alpha
 * \details Uses uniform values for vertex point size
 */
class Data3DPointsColorAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    float m_pointSize;  //!< Point size used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    Math::Vec3F *m_colorData = nullptr;  //!< Per vertex point color data array pointer
    float *m_alphaData = nullptr;        //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_colorBuffer = nullptr;  //!< Open GL buffer for point color
    QOpenGLBuffer *m_alphaBuffer = nullptr;  //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _pointSize Point size used for all vertices
     */
    Data3DPointsColorAlpha(const size_t _vertexCount, const size_t _indexCount, const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Per vertex color data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsColorAlpha(const size_t _vertexCount,
                           const size_t _indexCount,
                           const Math::Vec3F *_vertexData,
                           const Math::Vec3F *_colorData,
                           const float *_alphaData,
                           const uint *_indexData,
                           const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Per vertex color data pointer
     * \param _alphaData Per vertex alpha data pointer
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DPointsColorAlpha(const size_t _vertexCount,
                                  const Math::Vec3F *_vertexData,
                                  const Math::Vec3F *_colorData,
                                  const float *_alphaData,
                                  const float _pointSize)
        : Data3DPointsColorAlpha(_vertexCount, 0UL, _vertexData, _colorData, _alphaData, nullptr, _pointSize)
    {
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
     * \brief Create color and alpha Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy color and alpha Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind color and alpha Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release color and alpha Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSCOLORALPHA_H
