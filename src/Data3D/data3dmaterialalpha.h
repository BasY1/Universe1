/*!
 * \file src/Data3D/data3dmaterialalpha.h
 * \brief Open GL object with per vertex alpha, and uniform material and normal
 */

#ifndef OPENGL_DATA3DMATERIALALPHA_H
#define OPENGL_DATA3DMATERIALALPHA_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"
#include "../Math/circle.h"
#include "../Math/ellipse.h"
#include "../Math/irregellipse.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex alpha, and uniform material and normal */
class Data3DMaterialAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::Vec3F m_normal;          //!< Normal used for all vertices
    Math::MaterialRGB m_material;  //!< Material used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    float *m_alphaData = nullptr;            //!< Per vertex point alpha data array pointer
    QOpenGLBuffer *m_alphaBuffer = nullptr;  //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     */
    Data3DMaterialAlpha(const GLuint _glPrimitive,
                        const size_t _vertexCount,
                        const size_t _indexCount,
                        const Math::Vec3F &_normal,
                        const Math::MaterialRGB &_material);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialAlpha(const GLuint _glPrimitive,
                        const size_t _vertexCount,
                        const size_t _indexCount,
                        const Math::Vec3F *_vertexData,
                        const float *_alphaData,
                        const uint *_indexData,
                        const Math::Vec3F &_normal,
                        const Math::MaterialRGB &_material);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _normal Normal used for all vertices
     * \param _material Material used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialAlpha(const GLuint _glPrimitive,
                               const size_t _vertexCount,
                               const Math::Vec3F *_vertexData,
                               const float *_alphaData,
                               const Math::Vec3F &_normal,
                               const Math::MaterialRGB &_material)
        : Data3DMaterialAlpha(_glPrimitive, _vertexCount, 0UL, _vertexData, _alphaData, nullptr, _normal, _material)
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

 public:
    /*!
     * \brief Create a triangle 3D object
     * \param _p1 Vertex 1
     * \param _p2 Vertex 2
     * \param _p3 Vertex 3
     * \param _material Material
     * \param _alpha1 Alpha vertex 1
     * \param _alpha2 Alpha vertex 2
     * \param _alpha3 Alpha vertex 3
     * \return 3D triangle object
     */
    inline static Data3DMaterialAlpha *triangle(const Math::Vec3F &_p1,
                                                const Math::Vec3F &_p2,
                                                const Math::Vec3F &_p3,
                                                const Math::MaterialRGB &_material,
                                                const uint8_t _alpha1,
                                                const uint8_t _alpha2,
                                                const uint8_t _alpha3)
    {
        const std::vector<Math::Vec3F> tmp1 = {_p1, _p2, _p3};
        const std::vector<float> tmp2 = {float(_alpha1) / 255.0f, float(_alpha2) / 255.0f, float(_alpha3) / 255.0f};
        const Math::Vec3F N = Math::Vec3F::cross((_p2 - _p1), (_p3 - _p1)).normalized();
        return new Data3DMaterialAlpha(GL_TRIANGLES, 3UL, tmp1.data(), tmp2.data(), N, _material);
    }

    /*!
     * \brief Create a rectangle 3D object
     * \param _orientation Orientation of rectangle in space
     * \param _radius1 Radius 1 (within the \c normal2 in \a _orientation)
     * \param _radius2 Radius 2 (within the \c normal3 in \a _orientation)
     * \param _material Material
     * \param _alpha1 Alpha vertex 1
     * \param _alpha2 Alpha vertex 2
     * \param _alpha3 Alpha vertex 3
     * \param _alpha4 Alpha vertex 4
     * \return 3D rectangle object
     */
    inline static Data3DMaterialAlpha *rectangle(const Math::OrientF &_orientation,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const Math::MaterialRGB &_material,
                                                 const uint8_t _alpha1,
                                                 const uint8_t _alpha2,
                                                 const uint8_t _alpha3,
                                                 const uint8_t _alpha4)
    {
        const std::vector<Math::Vec3F> tmp1 = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2};
        const std::vector<float> tmp2 = {
            float(_alpha1) / 255.0f, float(_alpha2) / 255.0f, float(_alpha3) / 255.0f, float(_alpha4) / 255.0f};
        return new Data3DMaterialAlpha(GL_QUADS, 4UL, tmp1.data(), tmp2.data(), _orientation.normal1, _material);
    }

    /*!
     * \brief Create a circle 3D object
     * \param _orientation Orientation of circle in space
     * \param _radius Circle radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alphaCenter Alpha at center
     * \param _alphaBorder Alpha at border
     * \return 3D circle object
     */
    inline static Data3DMaterialAlpha *circle(const Math::OrientF &_orientation,
                                              const float _radius,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alphaCenter,
                                              const uint8_t _alphaBorder)
    {
        const size_t N = Math::Circle3F::circleCenterVertexCount(_quality);
        Math::Vec3F *tmp1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *tmp2 = reinterpret_cast<float *>(N * sizeof(float));

        Math::Circle3F::fillCircle(
            tmp1, tmp2, _orientation, float(_alphaCenter) / 255.0f, float(_alphaBorder) / 255.0f, _radius, _quality);
        Data3DMaterialAlpha *result =
            new Data3DMaterialAlpha(GL_TRIANGLE_FAN, N, tmp1, tmp2, _orientation.normal1, _material);
        std::free(tmp1);
        std::free(tmp2);
        return result;
    }

    /*!
     * \brief Create a ellipse 3D object
     * \param _orientation Orientation of ellipse in space
     * \param _radius1 Ellipse radius (within the \c normal2 in \a _orientation)
     * \param _radius2 Ellipse radius (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alphaCenter Alpha at center
     * \param _alphaBorder Alpha at border
     * \return 3D ellipse object
     */
    inline static Data3DMaterialAlpha *ellipse(const Math::OrientF &_orientation,
                                               const float _radius1,
                                               const float _radius2,
                                               const size_t _quality,
                                               const Math::MaterialRGB &_material,
                                               const uint8_t _alphaCenter,
                                               const uint8_t _alphaBorder)
    {
        const size_t N = Math::EllipseF::ellipseCenterVertexCount(_quality);
        Math::Vec3F *tmp1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *tmp2 = reinterpret_cast<float *>(N * sizeof(float));
        Math::EllipseF::fillEllipse(tmp1,
                                    tmp2,
                                    _orientation,
                                    float(_alphaCenter) / 255.0f,
                                    float(_alphaBorder) / 255.0f,
                                    _radius1,
                                    _radius2,
                                    _quality);
        Data3DMaterialAlpha *result =
            new Data3DMaterialAlpha(GL_TRIANGLE_FAN, N, tmp1, tmp2, _orientation.normal1, _material);
        std::free(tmp1);
        std::free(tmp2);
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
     * \param _alphaCenter Alpha at center
     * \param _alphaBorder Alpha at border
     * \return 3D irregular ellipse object
     */
    inline static Data3DMaterialAlpha *irregEllipse(const Math::OrientF &_orientation,
                                                    const float _radius1P,
                                                    const float _radius1M,
                                                    const float _radius2P,
                                                    const float _radius2M,
                                                    const size_t _quality,
                                                    const Math::MaterialRGB &_material,
                                                    const uint8_t _alphaCenter,
                                                    const uint8_t _alphaBorder)
    {
        const size_t N = Math::IrregEllipseF::ellipseCenterVertexCount(_quality);
        Math::Vec3F *tmp1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *tmp2 = reinterpret_cast<float *>(N * sizeof(float));
        Math::IrregEllipseF::fillEllipse(tmp1,
                                         tmp2,
                                         _orientation,
                                         float(_alphaCenter) / 255.0f,
                                         float(_alphaBorder) / 255.0f,
                                         _radius1P,
                                         _radius1M,
                                         _radius2P,
                                         _radius2M,
                                         _quality);
        Data3DMaterialAlpha *result =
            new Data3DMaterialAlpha(GL_TRIANGLE_FAN, N, tmp1, tmp2, _orientation.normal1, _material);
        std::free(tmp1);
        std::free(tmp2);
        return result;
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALALPHA_H
