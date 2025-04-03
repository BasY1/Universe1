/*!
 * \file src/Data3D/data3dpointscolor.h
 * \brief Open GL point-cloud object with per vertex color
 */

#ifndef OPENGL_DATA3DPOINTSCOLOR_H
#define OPENGL_DATA3DPOINTSCOLOR_H

#include "data3d.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Open GL point-cloud object with per vertex color
 * \details Uses uniform values for vertex alpha and point size
 */
class Data3DPointsColor : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    uint8_t m_alpha;         //!< Alpha used for all vertices
    float m_pointSize;       //!< Point size used for all vertices

    Math::Vec3F *m_colorData = nullptr;      //!< Per vertex point color data array pointer
    QOpenGLBuffer *m_colorBuffer = nullptr;  //!< Open GL buffer for point color

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     */
    Data3DPointsColor(const size_t _vertexCount,
                      const size_t _indexCount,
                      const uint8_t _alpha,
                      const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Per vertex color data pointer
     * \param _indexData Index data pointer
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DPointsColor(const size_t _vertexCount,
                      const size_t _indexCount,
                      const Math::Vec3F *_vertexData,
                      const Math::Vec3F *_colorData,
                      const uint *_indexData,
                      const uint8_t _alpha,
                      const float _pointSize);

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _colorData Per vertex color data pointer
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DPointsColor(const size_t _vertexCount,
                             const Math::Vec3F *_vertexData,
                             const Math::Vec3F *_colorData,
                             const uint8_t _alpha,
                             const float _pointSize)
        : Data3DPointsColor(_vertexCount, 0UL, _vertexData, _colorData, nullptr, _alpha, _pointSize)
    {
    }

    ~Data3DPointsColor();  //!< Destructor

    /*!
     * \brief Getter for color data pointer (constant version)
     * \return Vertex color data pointer
     */
    inline const Math::Vec3F *colorData() const
    {
        return m_colorData;
    }

    /*!
     * \brief Getter for color data pointer
     * \return Vertex color data pointer
     */
    inline Math::Vec3F *colorData()
    {
        return m_colorData;
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
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSCOLOR_H
