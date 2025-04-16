/*!
 * \file src/Data3D/data3dmaterialbase.h
 * \brief Open GL object with uniform material, alpha and normal
 */

#ifndef OPENGL_DATA3DMATERIALBASE_H
#define OPENGL_DATA3DMATERIALBASE_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"
#include "../Math/circle.h"
#include "../Math/ellipse.h"
#include "../Math/irregellipse.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with uniform material, alpha and normal */
class Data3DMaterialBase : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::Vec3F m_normal;          //!< Normal used for all vertices
    Math::MaterialRGB m_material;  //!< Material used for all vertices
    uint8_t m_alpha;               //!< Alpha used for all vertices

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     */
    inline Data3DMaterialBase(const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const size_t _indexCount,
                              const Math::Vec3F &_normal,
                              const Math::MaterialRGB &_material,
                              const uint8_t _alpha)
        : Data3D(GL_MATERIAL_SINGLE_Base, _glPrimitive, _vertexCount, _indexCount)
        , m_normal(_normal)
        , m_material(_material)
        , m_alpha(_alpha)
    {
    }

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _indexData Index data pointer
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    inline Data3DMaterialBase(const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const size_t _indexCount,
                              const Math::Vec3F *_vertexData,
                              const uint *_indexData,
                              const Math::Vec3F &_normal,
                              const Math::MaterialRGB &_material,
                              const uint8_t _alpha)
        : Data3D(GL_MATERIAL_SINGLE_Base, _glPrimitive, _vertexCount, _indexCount, _vertexData, _indexData)
        , m_normal(_normal)
        , m_material(_material)
        , m_alpha(_alpha)
    {
    }

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialBase(const GLuint _glPrimitive,
                              const size_t _vertexCount,
                              const Math::Vec3F *_vertexData,
                              const Math::Vec3F &_normal,
                              const Math::MaterialRGB &_material,
                              const uint8_t _alpha)
        : Data3DMaterialBase(_glPrimitive, _vertexCount, 0UL, _vertexData, nullptr, _normal, _material, _alpha)
    {
    }

    /*!
     * \brief Vertex material getter
     * \return Vertex material
     */
    inline const Math::MaterialRGB &material() const
    {
        return m_material;
    }

    /*!
     * \brief Setup vertex material
     * \param _material New vertex material
     */
    inline void setMaterial(const Math::MaterialRGB &_material)
    {
        m_material = _material;
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
     * \brief Vertex normal getter
     * \return Uniform normal
     */
    inline const Math::Vec3F &normal() const
    {
        return m_normal;
    }

    /*!
     * \brief Setup uniform normal
     * \param _normal New uniform normal
     */
    inline void setNormal(const Math::Vec3F &_normal)
    {
        m_normal = _normal;
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

 public:
    /*!
     * \brief Create a triangle 3D object
     * \param _p1 Vertex 1
     * \param _p2 Vertex 2
     * \param _p3 Vertex 3
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D triangle object
     */
    inline static Data3DMaterialBase *triangle(const Math::Vec3F &_p1,
                                               const Math::Vec3F &_p2,
                                               const Math::Vec3F &_p3,
                                               const Math::MaterialRGB &_material,
                                               const uint8_t _alpha)
    {
        const std::vector<Math::Vec3F> tmp = {_p1, _p2, _p3};
        const Math::Vec3F N = Math::Vec3F::cross((_p2 - _p1), (_p3 - _p1)).normalized();
        Data3DMaterialBase *result = new Data3DMaterialBase(GL_TRIANGLES, 3UL, tmp.data(), N, _material, _alpha);
        result->setCentralPoint((_p1 + _p2 + _p3) / 3.0f);
        return result;
    }

    /*!
     * \brief Create a rectangle 3D object
     * \param _orientation Orientation of rectangle in space
     * \param _radius1 Radius 1 (within the \c normal2 in \a _orientation)
     * \param _radius2 Radius 2 (within the \c normal3 in \a _orientation)
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D rectangle object
     */
    inline static Data3DMaterialBase *rectangle(const Math::OrientF &_orientation,
                                                const float _radius1,
                                                const float _radius2,
                                                const Math::MaterialRGB &_material,
                                                const uint8_t _alpha)
    {
        const std::vector<Math::Vec3F> tmp = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2};
        Data3DMaterialBase *result =
            new Data3DMaterialBase(GL_QUADS, 4UL, tmp.data(), _orientation.normal1, _material, _alpha);
        result->setCentralPoint(_orientation.center);
        return result;
    }

    /*!
     * \brief Create a circle 3D object
     * \param _orientation Orientation of circle in space
     * \param _radius Circle radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D circle object
     */
    inline static Data3DMaterialBase *circle(const Math::OrientF &_orientation,
                                             const float _radius,
                                             const size_t _quality,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha)
    {
        const size_t N = Math::Circle3F::circleVertexCount(_quality);
        Math::Vec3F *tmp = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
        Math::Circle3F::fillCircle(tmp, _orientation, _radius, _quality);
        Data3DMaterialBase *result =
            new Data3DMaterialBase(GL_TRIANGLE_FAN, N, tmp, _orientation.normal1, _material, _alpha);
        result->setCentralPoint(_orientation.center);
        std::free(tmp);
        return result;
    }

    /*!
     * \brief Create a ellipse 3D object
     * \param _orientation Orientation of ellipse in space
     * \param _radius1 Ellipse radius (within the \c normal2 in \a _orientation)
     * \param _radius2 Ellipse radius (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D ellipse object
     */
    inline static Data3DMaterialBase *ellipse(const Math::OrientF &_orientation,
                                              const float _radius1,
                                              const float _radius2,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alpha)
    {
        const size_t N = Math::EllipseF::ellipseVertexCount(_quality);
        Math::Vec3F *tmp = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
        Math::EllipseF::fillEllipse(tmp, _orientation, _radius1, _radius2, _quality);
        Data3DMaterialBase *result =
            new Data3DMaterialBase(GL_TRIANGLE_FAN, N, tmp, _orientation.normal1, _material, _alpha);
        result->setCentralPoint(_orientation.center);
        std::free(tmp);
        return result;
    }

    /*!
     * \brief Create a irregular ellipse 3D object
     * \param _orientation Orientation of irregular ellipse in space
     * \param _radius1P Ellipse radius (within the \b positive \c normal2 in \a _orientation)
     * \param _radius1M Ellipse radius (within the \b negative \c normal2 in \a _orientation)
     * \param _radius2P Ellipse radius (within the \b positive \c normal3 in \a _orientation)
     * \param _radius2M Ellipse radius (within the \b negative \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D irregular ellipse object
     */
    inline static Data3DMaterialBase *irregEllipse(const Math::OrientF &_orientation,
                                                   const float _radius1P,
                                                   const float _radius1M,
                                                   const float _radius2P,
                                                   const float _radius2M,
                                                   const size_t _quality,
                                                   const Math::MaterialRGB &_material,
                                                   const uint8_t _alpha)
    {
        const size_t N = Math::IrregEllipseF::ellipseVertexCount(_quality);
        Math::Vec3F *tmp = reinterpret_cast<Math::Vec3F *>(std::malloc(N * sizeof(Math::Vec3F)));
        Math::IrregEllipseF::fillEllipse(tmp, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _quality);
        Data3DMaterialBase *result =
            new Data3DMaterialBase(GL_TRIANGLE_FAN, N, tmp, _orientation.normal1, _material, _alpha);
        result->setCentralPoint(_orientation.center);
        std::free(tmp);
        return result;
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALBASE_H
