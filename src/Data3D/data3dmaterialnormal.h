/*!
 * \file src/Data3D/data3dmaterialnormal.h
 * \brief Open GL object with per vertex normals and uniform material and alpha
 */

#ifndef OPENGL_DATA3DMATERIALNORMAL_H
#define OPENGL_DATA3DMATERIALNORMAL_H

#include "data3d.h"

#include "../Math/material.h"
#include "../Math/orientation.h"

namespace U1 {
namespace OpenGL {

/*! \brief Open GL object with per vertex normals and uniform material and alpha */
class Data3DMaterialNormal : public Data3D
{
 public:
    static const std::string vs;  //!< Vertex shader source code
    static const std::string fs;  //!< Fragment shader source code

 protected:
    Math::MaterialRGB m_material;  //!< Material used for all vertices
    uint8_t m_alpha;               //!< Alpha used for all vertices

    Math::Vec3F *m_normalData = nullptr;      //!< Per vertex normal data array pointer
    QOpenGLBuffer *m_normalBuffer = nullptr;  //!< Open GL buffer for vertex normals

 public:
    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     */
    Data3DMaterialNormal(const GLuint _glPrimitive,
                         const size_t _vertexCount,
                         const size_t _indexCount,
                         const Math::MaterialRGB &_material,
                         const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _indexCount Count of indices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _indexData Index data pointer
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices and indices, but creates and fills Open GL buffers
     */
    Data3DMaterialNormal(const GLuint _glPrimitive,
                         const size_t _vertexCount,
                         const size_t _indexCount,
                         const Math::Vec3F *_vertexData,
                         const Math::Vec3F *_normalData,
                         const uint *_indexData,
                         const Math::MaterialRGB &_material,
                         const uint8_t _alpha);

    /*!
     * \brief Constructor
     * \param _glPrimitive Open GL primitive
     * \param _vertexCount Count of vertices
     * \param _vertexData Vertex position data pointer
     * \param _normalData Vertex normal data pointer
     * \param _material Material used for all vertices
     * \param _alpha Alpha used for all vertices
     * \details DO NOT allocate memory for vertices, but creates and fills Open GL buffer. Indices are not used
     */
    inline Data3DMaterialNormal(const GLuint _glPrimitive,
                                const size_t _vertexCount,
                                const Math::Vec3F *_vertexData,
                                const Math::Vec3F *_normalData,
                                const Math::MaterialRGB &_material,
                                const uint8_t _alpha)
        : Data3DMaterialNormal(_glPrimitive, _vertexCount, 0UL, _vertexData, _normalData, nullptr, _material, _alpha)
    {
    }

    ~Data3DMaterialNormal();  //!< Destructor

    /*!
     * \brief Getter for normal data pointer (constant version)
     * \return Vertex normal data pointer
     */
    inline const Math::Vec3F *normalData() const
    {
        return m_normalData;
    }

    /*!
     * \brief Getter for normal data pointer
     * \return Vertex normal data pointer
     */
    inline Math::Vec3F *normalData()
    {
        return m_normalData;
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
     * \brief Create normal Open GL buffer
     * \return Success flag
     */
    bool createBuffersImpl() override;

    /*!
     * \brief Destroy normal Open GL buffer
     * \return Success flag
     */
    bool destroyBuffersImpl() override;

    /*!
     * \brief Bind normal Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool bindBuffersImpl(QOpenGLShaderProgram *_program) override;

    /*!
     * \brief Release normal Open GL buffer
     * \param _program Open GL program
     * \return Success flag
     */
    bool releaseBuffersImpl(QOpenGLShaderProgram *_program) override;

 public:
    /*!
     * \brief Create a sphere 3D object - visible from outside
     * \param _orientation Orientation of sphere in space
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D sphere object
     */
    static Data3DMaterialNormal *sphere(const Math::OrientF &_orientation,
                                        const float _radius,
                                        const size_t _quality,
                                        const Math::MaterialRGB &_material,
                                        const uint8_t _alpha);

    /*!
     * \brief Create a sphere 3D object - visible from inside
     * \param _orientation Orientation of sphere in space
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D sphere object
     */
    static Data3DMaterialNormal *sphereInn(const Math::OrientF &_orientation,
                                           const float _radius,
                                           const size_t _quality,
                                           const Math::MaterialRGB &_material,
                                           const uint8_t _alpha);

    /*!
     * \brief Create a sphere 3D object - visible from outside
     * \param _orientation Orientation of sphere in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D sphere object
     */
    static Data3DMaterialNormal *sphereArc(const Math::OrientF &_orientation,
                                           const float _angleLonStart,
                                           const float _angleLonEnd,
                                           const float _angleLatStart,
                                           const float _angleLatEnd,
                                           const float _radius,
                                           const size_t _quality,
                                           const Math::MaterialRGB &_material,
                                           const uint8_t _alpha);

    /*!
     * \brief Create a sphere 3D object - visible from inside
     * \param _orientation Orientation of sphere in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius Sphere radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D sphere object
     */
    static Data3DMaterialNormal *sphereArcInn(const Math::OrientF &_orientation,
                                              const float _angleLonStart,
                                              const float _angleLonEnd,
                                              const float _angleLatStart,
                                              const float _angleLatEnd,
                                              const float _radius,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alpha);

    /*!
     * \brief Create a ellipsoid 3D object - visible from outside
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1 Ellipsoid radius 1 (within the \c normal1 in \a _orientation)
     * \param _radius2 Ellipsoid radius 2 (within the \c normal2 in \a _orientation)
     * \param _radius3 Ellipsoid radius 3 (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D ellipsoid object
     */
    static Data3DMaterialNormal *ellipsoid(const Math::OrientF &_orientation,
                                           const float _radius1,
                                           const float _radius2,
                                           const float _radius3,
                                           const size_t _quality,
                                           const Math::MaterialRGB &_material,
                                           const uint8_t _alpha);

    /*!
     * \brief Create a ellipsoid 3D object - visible from inside
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1 Ellipsoid radius 1 (within the \c normal1 in \a _orientation)
     * \param _radius2 Ellipsoid radius 2 (within the \c normal2 in \a _orientation)
     * \param _radius3 Ellipsoid radius 3 (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D ellipsoid object
     */
    static Data3DMaterialNormal *ellipsoidInn(const Math::OrientF &_orientation,
                                              const float _radius1,
                                              const float _radius2,
                                              const float _radius3,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alpha);

    /*!
     * \brief Create a ellipsoid 3D object - visible from outside
     * \param _orientation Orientation of ellipsoid in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius1 Ellipsoid radius 1 (within the \c normal1 in \a _orientation)
     * \param _radius2 Ellipsoid radius 2 (within the \c normal2 in \a _orientation)
     * \param _radius3 Ellipsoid radius 3 (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D ellipsoid object
     */
    static Data3DMaterialNormal *ellipsoidArc(const Math::OrientF &_orientation,
                                              const float _angleLonStart,
                                              const float _angleLonEnd,
                                              const float _angleLatStart,
                                              const float _angleLatEnd,
                                              const float _radius1,
                                              const float _radius2,
                                              const float _radius3,
                                              const size_t _quality,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alpha);

    /*!
     * \brief Create a ellipsoid 3D object - visible from inside
     * \param _orientation Orientation of ellipsoid in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius1 Ellipsoid radius 1 (within the \c normal1 in \a _orientation)
     * \param _radius2 Ellipsoid radius 2 (within the \c normal2 in \a _orientation)
     * \param _radius3 Ellipsoid radius 3 (within the \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D ellipsoid object
     */
    static Data3DMaterialNormal *ellipsoidArcInn(const Math::OrientF &_orientation,
                                                 const float _angleLonStart,
                                                 const float _angleLonEnd,
                                                 const float _angleLatStart,
                                                 const float _angleLatEnd,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const float _radius3,
                                                 const size_t _quality,
                                                 const Math::MaterialRGB &_material,
                                                 const uint8_t _alpha);

    /*!
     * \brief Create an irregular ellipsoid 3D object - visible from outside
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1P Ellipsoid radius 1 (within the \b positive direction of \c normal1 in \a _orientation)
     * \param _radius1M Ellipsoid radius 1 (within the \b negative direction of \c normal1 in \a _orientation)
     * \param _radius2P Ellipsoid radius 2 (within the \b positive direction of \c normal2 in \a _orientation)
     * \param _radius2M Ellipsoid radius 2 (within the \b negative direction of \c normal2 in \a _orientation)
     * \param _radius3P Ellipsoid radius 3 (within the \b positive direction of \c normal3 in \a _orientation)
     * \param _radius3M Ellipsoid radius 3 (within the \b negative direction of \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D irregular ellipsoid object
     */
    static Data3DMaterialNormal *irregEllipsoid(const Math::OrientF &_orientation,
                                                const float _radius1P,
                                                const float _radius1M,
                                                const float _radius2P,
                                                const float _radius2M,
                                                const float _radius3P,
                                                const float _radius3M,
                                                const size_t _quality,
                                                const Math::MaterialRGB &_material,
                                                const uint8_t _alpha);

    /*!
     * \brief Create an irregular ellipsoid 3D object - visible from inside
     * \param _orientation Orientation of ellipsoid in space
     * \param _radius1P Ellipsoid radius 1 (within the \b positive direction of \c normal1 in \a _orientation)
     * \param _radius1M Ellipsoid radius 1 (within the \b negative direction of \c normal1 in \a _orientation)
     * \param _radius2P Ellipsoid radius 2 (within the \b positive direction of \c normal2 in \a _orientation)
     * \param _radius2M Ellipsoid radius 2 (within the \b negative direction of \c normal2 in \a _orientation)
     * \param _radius3P Ellipsoid radius 3 (within the \b positive direction of \c normal3 in \a _orientation)
     * \param _radius3M Ellipsoid radius 3 (within the \b negative direction of \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D irregular ellipsoid object
     */
    static Data3DMaterialNormal *irregEllipsoidInn(const Math::OrientF &_orientation,
                                                   const float _radius1P,
                                                   const float _radius1M,
                                                   const float _radius2P,
                                                   const float _radius2M,
                                                   const float _radius3P,
                                                   const float _radius3M,
                                                   const size_t _quality,
                                                   const Math::MaterialRGB &_material,
                                                   const uint8_t _alpha);

    /*!
     * \brief Create an irregular ellipsoid 3D object - visible from outside
     * \param _orientation Orientation of ellipsoid in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius1P Ellipsoid radius 1 (within the \b positive direction of \c normal1 in \a _orientation)
     * \param _radius1M Ellipsoid radius 1 (within the \b negative direction of \c normal1 in \a _orientation)
     * \param _radius2P Ellipsoid radius 2 (within the \b positive direction of \c normal2 in \a _orientation)
     * \param _radius2M Ellipsoid radius 2 (within the \b negative direction of \c normal2 in \a _orientation)
     * \param _radius3P Ellipsoid radius 3 (within the \b positive direction of \c normal3 in \a _orientation)
     * \param _radius3M Ellipsoid radius 3 (within the \b negative direction of \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D irregular ellipsoid object
     */
    static Data3DMaterialNormal *irregEllipsoidArc(const Math::OrientF &_orientation,
                                                   const float _angleLonStart,
                                                   const float _angleLonEnd,
                                                   const float _angleLatStart,
                                                   const float _angleLatEnd,
                                                   const float _radius1P,
                                                   const float _radius1M,
                                                   const float _radius2P,
                                                   const float _radius2M,
                                                   const float _radius3P,
                                                   const float _radius3M,
                                                   const size_t _quality,
                                                   const Math::MaterialRGB &_material,
                                                   const uint8_t _alpha);

    /*!
     * \brief Create an irregular ellipsoid 3D object - visible from inside
     * \param _orientation Orientation of ellipsoid in space
     * \param _angleLonStart Start longitude angle in radians
     * \param _angleLonEnd End longitude angle in radians
     * \param _angleLatStart Start latitude angle in radians
     * \param _angleLatEnd End latitude angle in radians
     * \param _radius1P Ellipsoid radius 1 (within the \b positive direction of \c normal1 in \a _orientation)
     * \param _radius1M Ellipsoid radius 1 (within the \b negative direction of \c normal1 in \a _orientation)
     * \param _radius2P Ellipsoid radius 2 (within the \b positive direction of \c normal2 in \a _orientation)
     * \param _radius2M Ellipsoid radius 2 (within the \b negative direction of \c normal2 in \a _orientation)
     * \param _radius3P Ellipsoid radius 3 (within the \b positive direction of \c normal3 in \a _orientation)
     * \param _radius3M Ellipsoid radius 3 (within the \b negative direction of \c normal3 in \a _orientation)
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D irregular ellipsoid object
     */
    static Data3DMaterialNormal *irregEllipsoidArcInn(const Math::OrientF &_orientation,
                                                      const float _angleLonStart,
                                                      const float _angleLonEnd,
                                                      const float _angleLatStart,
                                                      const float _angleLatEnd,
                                                      const float _radius1P,
                                                      const float _radius1M,
                                                      const float _radius2P,
                                                      const float _radius2M,
                                                      const float _radius3P,
                                                      const float _radius3M,
                                                      const size_t _quality,
                                                      const Math::MaterialRGB &_material,
                                                      const uint8_t _alpha);

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D cylinder object
     */
    static Data3DMaterialNormal *cylinder(const Math::OrientF &_orientation,
                                          const float _length,
                                          const float _radius1,
                                          const float _radius2,
                                          const size_t _quality,
                                          const Math::MaterialRGB &_material,
                                          const uint8_t _alpha);

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material with alpha
     * \return 3D cylinder object
     */
    inline static Data3DMaterialNormal *cylinder(const Math::OrientF &_orientation,
                                                 const float _length,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const size_t _quality,
                                                 const Math::MaterialRGBA &_material)
    {
        return cylinder(_orientation, _length, _radius1, _radius2, _quality, _material.toRGB(), _material.alpha);
    }

    /*!
     * \brief Create a line cylinder 3D object - visible from outside
     * \param _point1 Orientation of cylinder in space
     * \param _point2 Orientation of cylinder in space
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D cylinder object
     */
    inline static Data3DMaterialNormal *line(const Math::Vec3F &_point1,
                                             const Math::Vec3F &_point2,
                                             const float _radius1,
                                             const float _radius2,
                                             const size_t _quality,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha)
    {
        return cylinder({_point1, (_point2 - _point1).normalized()},
                        _point1.distanceToPoint(_point2),
                        _radius1,
                        _radius2,
                        _quality,
                        _material,
                        _alpha);
    }

    /*!
     * \brief Create a line cylinder 3D object - visible from outside
     * \param _point1 Orientation of cylinder in space
     * \param _point2 Orientation of cylinder in space
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material with alpha
     * \return 3D cylinder object
     */
    inline static Data3DMaterialNormal *line(const Math::Vec3F &_point1,
                                             const Math::Vec3F &_point2,
                                             const float _radius1,
                                             const float _radius2,
                                             const size_t _quality,
                                             const Math::MaterialRGBA &_material)
    {
        return cylinder({_point1, (_point2 - _point1).normalized()},
                        _point1.distanceToPoint(_point2),
                        _radius1,
                        _radius2,
                        _quality,
                        _material.toRGB(),
                        _material.alpha);
    }

    /*!
     * \brief Create a cylinder 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _quality Circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D cylinder object
     */
    static Data3DMaterialNormal *cylinderInn(const Math::OrientF &_orientation,
                                             const float _length,
                                             const float _radius1,
                                             const float _radius2,
                                             const size_t _quality,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha);

    /*!
     * \brief Create a cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialNormal *cylinderArc(const Math::OrientF &_orientation,
                                             const float _length,
                                             const float _radiusArc,
                                             const float _radius1,
                                             const float _radius2,
                                             const size_t _qualityArc,
                                             const size_t _qualityCylinder,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha,
                                             const float _offsetAngle = 0.0f);

    /*!
     * \brief Create a cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material Material with alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    inline static Data3DMaterialNormal *cylinderArc(const Math::OrientF &_orientation,
                                                    const float _length,
                                                    const float _radiusArc,
                                                    const float _radius1,
                                                    const float _radius2,
                                                    const size_t _qualityArc,
                                                    const size_t _qualityCylinder,
                                                    const Math::MaterialRGBA &_material,
                                                    const float _offsetAngle = 0.0f)
    {
        return cylinderArc(_orientation,
                           _length,
                           _radiusArc,
                           _radius1,
                           _radius2,
                           _qualityArc,
                           _qualityCylinder,
                           _material.toRGB(),
                           _material.alpha,
                           _offsetAngle);
    }

    /*!
     * \brief Create a torus from cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _radiusTorus Cylinder radius at start
     * \param _radiusRing Cylinder radius at end
     * \param _qualityTorus Cylinder arc quality
     * \param _qualityRing Cylinder body circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    inline static Data3DMaterialNormal *torus(const Math::OrientF &_orientation,
                                              const float _radiusTorus,
                                              const float _radiusRing,
                                              const size_t _qualityTorus,
                                              const size_t _qualityRing,
                                              const Math::MaterialRGB &_material,
                                              const uint8_t _alpha,
                                              const float _offsetAngle = 0.0f)
    {
        return cylinderArc(_orientation,
                           2.0f * M_PI * _radiusTorus,
                           _radiusTorus,
                           _radiusRing,
                           _radiusRing,
                           _qualityTorus,
                           _qualityRing,
                           _material,
                           _alpha,
                           _offsetAngle);
    }

    /*!
     * \brief Create a torus from cylinder arc 3D object - visible from outside
     * \param _orientation Orientation of cylinder in space
     * \param _radiusTorus Cylinder radius at start
     * \param _radiusRing Cylinder radius at end
     * \param _qualityTorus Cylinder arc quality
     * \param _qualityRing Cylinder body circle quality
     * \param _material Material with alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    inline static Data3DMaterialNormal *torus(const Math::OrientF &_orientation,
                                              const float _radiusTorus,
                                              const float _radiusRing,
                                              const size_t _qualityTorus,
                                              const size_t _qualityRing,
                                              const Math::MaterialRGBA &_material,
                                              const float _offsetAngle = 0.0f)
    {
        return torus(_orientation,
                     _radiusTorus,
                     _radiusRing,
                     _qualityTorus,
                     _qualityRing,
                     _material.toRGB(),
                     _material.alpha,
                     _offsetAngle);
    }

    /*!
     * \brief Create a cylinder arc 3D object - visible from inside
     * \param _orientation Orientation of cylinder in space
     * \param _length Cylinder length
     * \param _radiusArc Cylinder arc radius
     * \param _radius1 Cylinder radius at start
     * \param _radius2 Cylinder radius at end
     * \param _qualityArc Cylinder arc quality
     * \param _qualityCylinder Cylinder body circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \param _offsetAngle Start angle in radians
     * \return 3D cylinder arc object
     */
    static Data3DMaterialNormal *cylinderArcInn(const Math::OrientF &_orientation,
                                                const float _length,
                                                const float _radiusArc,
                                                const float _radius1,
                                                const float _radius2,
                                                const size_t _qualityArc,
                                                const size_t _qualityCylinder,
                                                const Math::MaterialRGB &_material,
                                                const uint8_t _alpha,
                                                const float _offsetAngle = 0.0f);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _material Material with alpha
     * \return 3D path object
     */
    static Data3DMaterialNormal *path(const std::vector<Math::OrientF> &_path,
                                      const float _radius,
                                      const size_t _quality,
                                      const Math::MaterialRGBA &_material);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D path object
     */
    inline static Data3DMaterialNormal *path(const std::vector<Math::OrientF> &_path,
                                             const float _radius,
                                             const size_t _quality,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha)
    {
        return path(_path, _radius, _quality, {_material, _alpha});
    }

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _centerPoint Calculated central point
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _material Material with alpha
     * \return 3D path object
     */
    static Data3DMaterialNormal *path(const std::vector<Math::OrientF> &_path,
                                      const Math::Vec3F &_centerPoint,
                                      const float _radius,
                                      const size_t _quality,
                                      const Math::MaterialRGBA &_material);

    /*!
     * \brief Create path 3D data
     * \param _path Path points
     * \param _centerPoint Calculated central point
     * \param _radius Path radius
     * \param _quality Path quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D path object
     */
    inline static Data3DMaterialNormal *path(const std::vector<Math::OrientF> &_path,
                                             const Math::Vec3F &_centerPoint,
                                             const float _radius,
                                             const size_t _quality,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha)
    {
        return path(_path, _centerPoint, _radius, _quality, {_material, _alpha});
    }

    /*!
     * \brief Create 3D data for elliptical path
     * \param _orientation Ellipse orientation
     * \param _radius1 Ellipse radius 1
     * \param _radius2 Ellipse radius 2
     * \param _radiusPath Path cylinder radius
     * \param _quality Ellipse quality
     * \param _qualityPath Path circle quality
     * \param _material Material with alpha
     * \return 3D path object
     */
    static Data3DMaterialNormal *pathEllipse(const Math::OrientF &_orientation,
                                             const float _radius1,
                                             const float _radius2,
                                             const float _radiusPath,
                                             const size_t _quality,
                                             const size_t _qualityPath,
                                             const Math::MaterialRGBA &_material);

    /*!
     * \brief Create 3D data for elliptical path
     * \param _orientation Ellipse orientation
     * \param _radius1 Ellipse radius 1
     * \param _radius2 Ellipse radius 2
     * \param _radiusPath Path cylinder radius
     * \param _quality Ellipse quality
     * \param _qualityPath Path circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \return 3D path object
     */
    static Data3DMaterialNormal *pathEllipse(const Math::OrientF &_orientation,
                                             const float _radius1,
                                             const float _radius2,
                                             const float _radiusPath,
                                             const size_t _quality,
                                             const size_t _qualityPath,
                                             const Math::MaterialRGB &_material,
                                             const uint8_t _alpha)
    {
        return pathEllipse(_orientation, _radius1, _radius2, _radiusPath, _quality, _qualityPath, {_material, _alpha});
    }
};

}  // namespace OpenGL
}  // namespace U1

#endif  // OPENGL_DATA3DMATERIALNORMAL_H
