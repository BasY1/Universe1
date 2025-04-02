/*!
 * \file src/Data3D/data3dpointssizecoloralpha.h
 * \brief Open GL point-cloud object with per vertex point size, color and alpha
 */

#ifndef OPENGL_DATA3DPOINTSSIZECOLORALPHA_H
#define OPENGL_DATA3DPOINTSSIZECOLORALPHA_H

#include "data3d.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL point-cloud object with per vertex point size, color and alpha */
class Data3DPointsSizeColorAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    bool m_isTransparent = false;  //!< Transparency flag

    float *m_pointSizeData = nullptr;    //!< Per vertex point size data array pointer
    Math::Vec3F *m_colorData = nullptr;  //!< Per vertex point color data array pointer
    float *m_alphaData = nullptr;        //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_pointSizeBuffer = nullptr;  //!< Open GL buffer for point sizes
    QOpenGLBuffer *m_colorBuffer = nullptr;      //!< Open GL buffer for point color
    QOpenGLBuffer *m_alphaBuffer = nullptr;      //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     */
    Data3DPointsSizeColorAlpha(const size_t _vertexCount, const size_t _indexCount);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Vertex color data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _indexData Index data pointer
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsSizeColorAlpha(const size_t _vertexCount,
                               const size_t _indexCount,
                               const Math::Vec3F *_vertexData,
                               const Math::Vec3F *_colorData,
                               const float *_alphaData,
                               const float *_pointSizeData,
                               const uint *_indexData);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Vertex color data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffers. Indices are not used
     */
    inline Data3DPointsSizeColorAlpha(const size_t _vertexCount,
                                      const Math::Vec3F *_vertexData,
                                      const Math::Vec3F *_colorData,
                                      const float *_alphaData,
                                      const float *_pointSizeData)
        : Data3DPointsSizeColorAlpha(_vertexCount, 0UL, _vertexData, _colorData, _alphaData, _pointSizeData, nullptr)
    {
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
     * \brief Create additional Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy additional Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind additional Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release additional Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSSIZECOLORALPHA_H
