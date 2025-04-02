/*!
 * \file src/Data3D/data3dpointsbase.h
 * \brief Base Open GL point-cloud object
 */

#ifndef OPENGL_DATA3DPOINTSBASE_H
#define OPENGL_DATA3DPOINTSBASE_H

#include "data3d.h"

#include "../Math/colorrgb.h"

namespace U1 {
namespace OpenGL {

/*!
 * \brief Base Open GL point-cloud object
 * \details Uses uniform values for vertex color, alpha and point size
 */
class Data3DPointsBase : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::ColorRGB m_color;  //!< Color used for all vertices
    uint8_t m_alpha;         //!< Alpha used for all vertices
    float m_pointSize;       //!< Point size used for all vertices

 public:
    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     */
    inline Data3DPointsBase(const size_t _vertexCount,
                            const size_t _indexCount,
                            const Math::ColorRGB &_color,
                            const uint8_t _alpha,
                            const float _pointSize)
        : Data3D(GL_POINTS_Base, GL_POINTS, _vertexCount, _indexCount)
        , m_color(_color)
        , m_alpha(_alpha)
        , m_pointSize(_pointSize)
    {
    }

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex data pointer
     * \param _indexData Index data pointer
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    inline Data3DPointsBase(const size_t _vertexCount,
                            const size_t _indexCount,
                            const Math::Vec3F *_vertexData,
                            const uint *_indexData,
                            const Math::ColorRGB &_color,
                            const uint8_t _alpha,
                            const float _pointSize)
        : Data3D(GL_POINTS_Base, GL_POINTS, _vertexCount, _indexCount, _vertexData, _indexData)
        , m_color(_color)
        , m_alpha(_alpha)
        , m_pointSize(_pointSize)
    {
    }

    /*!
     * \brief Constructor
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex data pointer
     * \param _color Color used for all vertices
     * \param _alpha Alpha used for all vertices
     * \param _pointSize Point size used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DPointsBase(const size_t _vertexCount,
                            const Math::Vec3F *_vertexData,
                            const Math::ColorRGB &_color,
                            const uint8_t _alpha,
                            const float _pointSize)
        : Data3DPointsBase(_vertexCount, 0UL, _vertexData, nullptr, _color, _alpha, _pointSize)
    {
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
     * \brief No additional Open GL buffers
     * \return \c true
     */
    bool createBuffersImpl() override;
    /*!
     * \brief No additional Open GL buffers
     * \return \c true
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief No additional Open GL buffers
     * \param _program Open GL program
     * \return \c true
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief No additional Open GL buffers
     * \param _program Open GL program
     * \return \c true
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DPOINTSBASE_H
