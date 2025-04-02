/*!
 * \file src/Data3D/data3dpointssizecolor.h
 * \brief Open GL point-cloud object with per vertex point size and color
 */

#ifndef OPENGL_DATA3DPOINTSSIZECOLOR_H
#define OPENGL_DATA3DPOINTSSIZECOLOR_H

#include "data3d.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex point size and color
 * \details Uses uniform value for vertex alpha
 */
class Data3DPointsSizeColor : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    uint8_t m_alpha;         //!< Alpha used for all vertices

    Math::Vec3F *m_colorData = nullptr;  //!< Per vertex point color data array pointer
    float *m_pointSizeData = nullptr;  //!< Per vertex point size data array pointer

    QOpenGLBuffer *m_colorBuffer = nullptr;      //!< Open GL buffer for point color
    QOpenGLBuffer *m_pointSizeBuffer = nullptr;  //!< Open GL buffer for point sizes

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _alpha Alpha used for all vertices
     */
    Data3DPointsSizeColor(const size_t _vertexCount, const size_t _indexCount, const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Vertex color data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _indexData Index data pointer
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsSizeColor(const size_t _vertexCount,
                          const size_t _indexCount,
                          const Math::Vec3F *_vertexData,
                          const Math::Vec3F *_colorData,
                          const float *_pointSizeData,
                          const uint *_indexData,
                          const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Vertex color data pointer
     * \param _pointSizeData Vertex point sizes array pointer
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffers. Indices are not used
     */
    inline Data3DPointsSizeColor(const size_t _vertexCount,
                                 const Math::Vec3F *_vertexData,
                                 const Math::Vec3F *_colorData,
                                 const float *_pointSizeData,
                                 const uint8_t _alpha)
        : Data3DPointsSizeColor(_vertexCount, 0UL, _vertexData, _colorData, _pointSizeData, nullptr, _alpha)
    {
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
     * \brief Create point size and color Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy point size and color Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind point size and color Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release point size and color Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSSIZECOLOR_H
