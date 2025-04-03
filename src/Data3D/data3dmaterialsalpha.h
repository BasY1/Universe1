/*!
 * \file src/Data3D/data3dmaterialsalpha.h
 * \brief Open GL object with per vertex material and alpha, and uniform normal
 */

#ifndef OPENGL_DATA3DMATERIALSALPHA_H
#define OPENGL_DATA3DMATERIALSALPHA_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"
#include "../Math/circle.h"
#include "../Math/ellipse.h"
#include "../Math/irregellipse.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex material and alpha, and uniform normal */
class Data3DMaterialsAlpha : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::Vec3F m_normal;          //!< Normal used for all vertices

    bool m_isTransparent = false;  //!< Transparency flag

    Math::Vec3F *m_ambientData = nullptr;   //!< Per vertex ambient color data array pointer
    Math::Vec3F *m_diffuseData = nullptr;   //!< Per vertex diffuse color data array pointer
    Math::Vec3F *m_specularData = nullptr;  //!< Per vertex specular color data array pointer
    float *m_shineData = nullptr;           //!< Per vertex shine data array pointer
    float *m_alphaData = nullptr;           //!< Per vertex point alpha data array pointer

    QOpenGLBuffer *m_ambientBuffer = nullptr;   //!< Open GL buffer for vertex ambient color
    QOpenGLBuffer *m_diffuseBuffer = nullptr;   //!< Open GL buffer for vertex diffuse color
    QOpenGLBuffer *m_specularBuffer = nullptr;  //!< Open GL buffer for vertex specular color
    QOpenGLBuffer *m_shineBuffer = nullptr;     //!< Open GL buffer for vertex shine
    QOpenGLBuffer *m_alphaBuffer = nullptr;     //!< Open GL buffer for point alpha

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _normal Normal used for all vertices
     */
    Data3DMaterialsAlpha(const GLuint _glPrimitive,
                         const size_t _vertexCount,
                         const size_t _indexCount,
                         const Math::Vec3F &_normal);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _ambientData Vertex ambient color data pointer
     * \param _diffuseData Vertex diffuse color data pointer
     * \param _specularData Vertex specular color data pointer
     * \param _shineData Vertex shine data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _indexData Index data pointer
     * \param _normal Normal used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialsAlpha(const GLuint _glPrimitive,
                         const size_t _vertexCount,
                         const size_t _indexCount,
                         const Math::Vec3F *_vertexData,
                         const Math::Vec3F *_ambientData,
                         const Math::Vec3F *_diffuseData,
                         const Math::Vec3F *_specularData,
                         const float *_shineData,
                         const float *_alphaData,
                         const uint *_indexData,
                         const Math::Vec3F &_normal);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _ambientData Vertex ambient color data pointer
     * \param _diffuseData Vertex diffuse color data pointer
     * \param _specularData Vertex specular color data pointer
     * \param _shineData Vertex shine data pointer
     * \param _alphaData Vertex alpha data pointer
     * \param _normal Normal used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialsAlpha(const GLuint _glPrimitive,
                                const size_t _vertexCount,
                                const Math::Vec3F *_vertexData,
                                const Math::Vec3F *_ambientData,
                                const Math::Vec3F *_diffuseData,
                                const Math::Vec3F *_specularData,
                                const float *_shineData,
                                const float *_alphaData,
                                const Math::Vec3F &_normal)
        : Data3DMaterialsAlpha(_glPrimitive,
                               _vertexCount,
                               0UL,
                               _vertexData,
                               _ambientData,
                               _diffuseData,
                               _specularData,
                               _shineData,
                               _alphaData,
                               nullptr,
                               _normal)
    {
    }

    ~Data3DMaterialsAlpha();  //!< Destructor

    /*!
     * \brief Getter for ambient color data pointer (constant version)
     * \return Vertex ambient color data pointer
     */
    inline const Math::Vec3F *ambientData() const
    {
        return m_ambientData;
    }

    /*!
     * \brief Getter for ambient color data pointer
     * \return Vertex ambient color data pointer
     */
    inline Math::Vec3F *ambientData()
    {
        return m_ambientData;
    }

    /*!
     * \brief Getter for diffuse color data pointer (constant version)
     * \return Vertex diffuse color data pointer
     */
    inline const Math::Vec3F *diffuseData() const
    {
        return m_diffuseData;
    }

    /*!
     * \brief Getter for diffuse color data pointer
     * \return Vertex diffuse color data pointer
     */
    inline Math::Vec3F *diffuseData()
    {
        return m_diffuseData;
    }

    /*!
     * \brief Getter for specular color data pointer (constant version)
     * \return Vertex specular color data pointer
     */
    inline const Math::Vec3F *specularData() const
    {
        return m_specularData;
    }

    /*!
     * \brief Getter for specular color data pointer
     * \return Vertex specular color data pointer
     */
    inline Math::Vec3F *specularData()
    {
        return m_specularData;
    }

    /*!
     * \brief Getter for shine data pointer (constant version)
     * \return Vertex shine data pointer
     */
    inline const float *shineData() const
    {
        return m_shineData;
    }

    /*!
     * \brief Getter for shine data pointer
     * \return Vertex shine data pointer
     */
    inline float *shineData()
    {
        return m_shineData;
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
     * \brief Create material Open GL buffers
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy material Open GL buffers
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind material Open GL buffers
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release material Open GL buffers
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
     * \param _material1 Material for vertex 1
     * \param _material2 Material for vertex 2
     * \param _material3 Material for vertex 3
     * \param _alpha1 Alpha for vertex 1
     * \param _alpha2 Alpha for vertex 2
     * \param _alpha3 Alpha for vertex 3
     * \return 3D triangle object
     */
    inline static Data3DMaterialsAlpha *triangle(const Math::Vec3F &_p1,
                                                 const Math::Vec3F &_p2,
                                                 const Math::Vec3F &_p3,
                                                 const Math::MaterialRGB &_material1,
                                                 const Math::MaterialRGB &_material2,
                                                 const Math::MaterialRGB &_material3,
                                                 const uint8_t _alpha1,
                                                 const uint8_t _alpha2,
                                                 const uint8_t _alpha3)
    {
        const std::vector<Math::Vec3F> t1 = {_p1, _p2, _p3};
        const std::vector<Math::Vec3F> t2 = {
            _material1.ambient.toVec3F(), _material2.ambient.toVec3F(), _material3.ambient.toVec3F()};
        const std::vector<Math::Vec3F> t3 = {
            _material1.diffuse.toVec3F(), _material2.diffuse.toVec3F(), _material3.diffuse.toVec3F()};
        const std::vector<Math::Vec3F> t4 = {
            _material1.specular.toVec3F(), _material2.specular.toVec3F(), _material3.specular.toVec3F()};
        const std::vector<float> t5 = {_material1.shine, _material2.shine, _material3.shine};
        const std::vector<float> t6 = {float(_alpha1) / 255.0f, float(_alpha2) / 255.0f, float(_alpha3) / 255.0f};
        const Math::Vec3F N = Math::Vec3F::cross((_p2 - _p1), (_p3 - _p1)).normalized();
        Data3DMaterialsAlpha *result = new Data3DMaterialsAlpha(
            GL_TRIANGLES, 3UL, t1.data(), t2.data(), t3.data(), t4.data(), t5.data(), t6.data(), N);
        result->setCentralPoint((_p1 + _p2 + _p3) / 3.0f);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U || _alpha3 != 255U);
        return result;
    }

    /*!
     * \brief Create a rectangle 3D object
     * \param _orientation Orientation of rectangle in space
     * \param _radius1 Radius 1 (within the \c normal2 in \a _orientation)
     * \param _radius2 Radius 2 (within the \c normal3 in \a _orientation)
     * \param _material1 Material for vertex 1
     * \param _material2 Material for vertex 2
     * \param _material3 Material for vertex 3
     * \param _material4 Material for vertex 4
     * \param _alpha1 Alpha for vertex 1
     * \param _alpha2 Alpha for vertex 2
     * \param _alpha3 Alpha for vertex 3
     * \param _alpha4 Alpha for vertex 4
     * \return 3D rectangle object
     */
    inline static Data3DMaterialsAlpha *rectangle(const Math::OrientF &_orientation,
                                                  const float _radius1,
                                                  const float _radius2,
                                                  const Math::MaterialRGB &_material1,
                                                  const Math::MaterialRGB &_material2,
                                                  const Math::MaterialRGB &_material3,
                                                  const Math::MaterialRGB &_material4,
                                                  const uint8_t _alpha1,
                                                  const uint8_t _alpha2,
                                                  const uint8_t _alpha3,
                                                  const uint8_t _alpha4)
    {
        const std::vector<Math::Vec3F> t1 = {
            _orientation.center - _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2,
            _orientation.center - _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 - _orientation.normal3 * _radius2,
            _orientation.center + _orientation.normal2 * _radius1 + _orientation.normal3 * _radius2};
        const std::vector<Math::Vec3F> t2 = {_material1.ambient.toVec3F(),
                                             _material2.ambient.toVec3F(),
                                             _material3.ambient.toVec3F(),
                                             _material4.ambient.toVec3F()};
        const std::vector<Math::Vec3F> t3 = {_material1.diffuse.toVec3F(),
                                             _material2.diffuse.toVec3F(),
                                             _material3.diffuse.toVec3F(),
                                             _material4.diffuse.toVec3F()};
        const std::vector<Math::Vec3F> t4 = {_material1.specular.toVec3F(),
                                             _material2.specular.toVec3F(),
                                             _material3.specular.toVec3F(),
                                             _material4.specular.toVec3F()};
        const std::vector<float> t5 = {_material1.shine, _material2.shine, _material3.shine, _material4.shine};

        const std::vector<float> t6 = {
            float(_alpha1) / 255.0f, float(_alpha2) / 255.0f, float(_alpha3) / 255.0f, float(_alpha4) / 255.0f};

        Data3DMaterialsAlpha *result = new Data3DMaterialsAlpha(
            GL_QUADS, 4UL, t1.data(), t2.data(), t3.data(), t4.data(), t5.data(), t6.data(), _orientation.normal1);
        result->setCentralPoint(_orientation.center);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U || _alpha3 != 255U || _alpha4 != 255U);
        return result;
    }

    /*!
     * \brief Create a circle 3D object
     * \param _orientation Orientation of circle in space
     * \param _radius Circle radius
     * \param _quality Circle quality
     * \param _material1 Material at center
     * \param _material2 Material at border
     * \param _alpha1 Alpha at center
     * \param _alpha2 Alpha at border
     * \return 3D circle object
     */
    inline static Data3DMaterialsAlpha *circle(const Math::OrientF &_orientation,
                                               const float _radius,
                                               const size_t _quality,
                                               const Math::MaterialRGB &_material1,
                                               const Math::MaterialRGB &_material2,
                                               const uint8_t _alpha1,
                                               const uint8_t _alpha2)
    {
        const size_t N = Math::Circle3F::circleVertexCount(_quality);
        Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *t5 = reinterpret_cast<float *>(N * sizeof(float));
        float *t6 = reinterpret_cast<float *>(N * sizeof(float));

        Math::Circle3F::fillCircle(t1,
                                   t2,
                                   t3,
                                   t4,
                                   t5,
                                   t6,
                                   _orientation,
                                   _material1.ambient.toVec3F(),
                                   _material2.ambient.toVec3F(),
                                   _material1.diffuse.toVec3F(),
                                   _material2.diffuse.toVec3F(),
                                   _material1.specular.toVec3F(),
                                   _material2.specular.toVec3F(),
                                   _material1.shine,
                                   _material2.shine,
                                   float(_alpha1) / 255.0f,
                                   float(_alpha2) / 255.0f,
                                   _radius,
                                   _quality);

        Data3DMaterialsAlpha *result =
            new Data3DMaterialsAlpha(GL_TRIANGLE_FAN, N, t1, t2, t3, t4, t5, t6, _orientation.normal1);
        result->setCentralPoint(_orientation.center);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U);

        std::free(t1);
        std::free(t2);
        std::free(t3);
        std::free(t4);
        std::free(t5);
        std::free(t6);

        return result;
    }

    /*!
     * \brief Create a ellipse 3D object
     * \param _orientation Orientation of ellipse in space
     * \param _radius1 Ellipse radius (within the \c normal2 in \a _orientation)
     * \param _radius2 Ellipse radius (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material1 Material at center
     * \param _material2 Material at border
     * \param _alpha1 Alpha at center
     * \param _alpha2 Alpha at border
     * \return 3D ellipse object
     */
    inline static Data3DMaterialsAlpha *ellipse(const Math::OrientF &_orientation,
                                                const float _radius1,
                                                const float _radius2,
                                                const size_t _quality,
                                                const Math::MaterialRGB &_material1,
                                                const Math::MaterialRGB &_material2,
                                                const uint8_t _alpha1,
                                                const uint8_t _alpha2)
    {
        const size_t N = Math::EllipseF::ellipseVertexCount(_quality);
        Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *t5 = reinterpret_cast<float *>(N * sizeof(float));
        float *t6 = reinterpret_cast<float *>(N * sizeof(float));

        Math::EllipseF::fillEllipse(t1,
                                    t2,
                                    t3,
                                    t4,
                                    t5,
                                    t6,
                                    _orientation,
                                    _material1.ambient.toVec3F(),
                                    _material2.ambient.toVec3F(),
                                    _material1.diffuse.toVec3F(),
                                    _material2.diffuse.toVec3F(),
                                    _material1.specular.toVec3F(),
                                    _material2.specular.toVec3F(),
                                    _material1.shine,
                                    _material2.shine,
                                    float(_alpha1) / 255.0f,
                                    float(_alpha2) / 255.0f,
                                    _radius1,
                                    _radius2,
                                    _quality);

        Data3DMaterialsAlpha *result =
            new Data3DMaterialsAlpha(GL_TRIANGLE_FAN, N, t1, t2, t3, t4, t5, t6, _orientation.normal1);
        result->setCentralPoint(_orientation.center);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U);

        std::free(t1);
        std::free(t2);
        std::free(t3);
        std::free(t4);
        std::free(t5);
        std::free(t6);

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
     * \param _material1 Material at center
     * \param _material2 Material at border
     * \param _alpha1 Alpha at center
     * \param _alpha2 Alpha at border
     * \return 3D irregular ellipse object
     */
    inline static Data3DMaterialsAlpha *irregEllipse(const Math::OrientF &_orientation,
                                                     const float _radius1P,
                                                     const float _radius1M,
                                                     const float _radius2P,
                                                     const float _radius2M,
                                                     const size_t _quality,
                                                     const Math::MaterialRGB &_material1,
                                                     const Math::MaterialRGB &_material2,
                                                     const uint8_t _alpha1,
                                                     const uint8_t _alpha2)
    {
        const size_t N = Math::IrregEllipseF::ellipseVertexCount(_quality);
        Math::Vec3F *t1 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t2 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t3 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        Math::Vec3F *t4 = reinterpret_cast<Math::Vec3F *>(N * sizeof(Math::Vec3F));
        float *t5 = reinterpret_cast<float *>(N * sizeof(float));
        float *t6 = reinterpret_cast<float *>(N * sizeof(float));

        Math::IrregEllipseF::fillEllipse(t1,
                                         t2,
                                         t3,
                                         t4,
                                         t5,
                                         t6,
                                         _orientation,
                                         _material1.ambient.toVec3F(),
                                         _material2.ambient.toVec3F(),
                                         _material1.diffuse.toVec3F(),
                                         _material2.diffuse.toVec3F(),
                                         _material1.specular.toVec3F(),
                                         _material2.specular.toVec3F(),
                                         _material1.shine,
                                         _material2.shine,
                                         float(_alpha1) / 255.0f,
                                         float(_alpha2) / 255.0f,
                                         _radius1P,
                                         _radius1M,
                                         _radius2P,
                                         _radius2M,
                                         _quality);

        Data3DMaterialsAlpha *result =
            new Data3DMaterialsAlpha(GL_TRIANGLE_FAN, N, t1, t2, t3, t4, t5, t6, _orientation.normal1);
        result->setCentralPoint(_orientation.center);
        result->setTransparent(_alpha1 != 255U || _alpha2 != 255U);

        std::free(t1);
        std::free(t2);
        std::free(t3);
        std::free(t4);
        std::free(t5);
        std::free(t6);

        return result;
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALSALPHA_H
