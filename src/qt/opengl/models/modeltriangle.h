/*!
 * \file qt/opengl/models/modeltriangle.h
 * \author Michal Steller
 * \brief Open GL single triangle model with material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MODELS_MODELTRIANGLE_H
#define UNIVERSE1_OPENGL_MODELS_MODELTRIANGLE_H

#include "meshmodel.h"

namespace Universe1 {
namespace OpenGL {
namespace Models {

/*!
 * \brief Open GL single triangle model
 */
class ModelTriangle : public MeshModel
{
    Q_OBJECT
 public:
    ModelTriangle(const Material &_material, QObject *_parent = nullptr);

    ModelTriangle(QVector3D _vertex1,
                  QVector3D _vertex2,
                  QVector3D _vertex3,
                  QVector3D _normalAll,
                  const Material &_material,
                  QObject *_parent = nullptr);

    ModelTriangle(QVector3D _vertex1,
                  QVector3D _vertex2,
                  QVector3D _vertex3,
                  QVector3D _normal1,
                  QVector3D _normal2,
                  QVector3D _normal3,
                  const Material &_material,
                  QObject *_parent = nullptr);

    inline bool ccw() const;
    inline const QVector3D &vertex1() const;
    inline const QVector3D &vertex2() const;
    inline const QVector3D &vertex3() const;
    inline const QVector3D &normal1() const;
    inline const QVector3D &normal2() const;
    inline const QVector3D &normal3() const;

 protected:
    void rebuild() override;

 public slots:
    void setCcw(bool _value);

    void setTriangle(QVector3D _vertex1, QVector3D _vertex2, QVector3D _vertex3, QVector3D _normalAll);
    void setTriangle(QVector3D _vertex1,
                     QVector3D _vertex2,
                     QVector3D _vertex3,
                     QVector3D _normal1,
                     QVector3D _normal2,
                     QVector3D _normal3);

    void setVertex1(QVector3D _value);
    void setVertex2(QVector3D _value);
    void setVertex3(QVector3D _value);

    void setNormal1(QVector3D _value);
    void setNormal2(QVector3D _value);
    void setNormal3(QVector3D _value);

    void setNormalAll(QVector3D _value);
    void setNormals(QVector3D _normal1, QVector3D _normal2, QVector3D _normal3);

 protected:
    /*!
     * \brief Counter-clockwise flag
     * \details
     * | Flag value | Vertex order |
     * | :--------- | :----------- |
     * | \c true    | 1 - 2 - 3    |
     * | \c false   | 1 - 3 - 2    |
     */
    bool m_ccw;

    QVector3D m_vertex1;  //!< Vertex 1 position
    QVector3D m_vertex2;  //!< Vertex 2 position
    QVector3D m_vertex3;  //!< Vertex 3 position
    QVector3D m_normal1;  //!< Vertex 1 normal
    QVector3D m_normal2;  //!< Vertex 2 normal
    QVector3D m_normal3;  //!< Vertex 3 normal

 public:
    static const QVector3D defaultVertex1;  //!< Default vertex 1 position
    static const QVector3D defaultVertex2;  //!< Default vertex 2 position
    static const QVector3D defaultVertex3;  //!< Default vertex 3 position
};

/*!
 * \brief Getter for counter-clockwise flag
 * \returns Counter-clockwise flag
 */
inline bool ModelTriangle::ccw() const
{
    return m_ccw;
}

/*!
 * \brief Getter for vertex 1 position
 * \returns Vertex 1 position
 */
inline const QVector3D &ModelTriangle::vertex1() const
{
    return m_vertex1;
}

/*!
 * \brief Getter for vertex 2 position
 * \returns Vertex 2 position
 */
inline const QVector3D &ModelTriangle::vertex2() const
{
    return m_vertex2;
}

/*!
 * \brief Getter for vertex 3 position
 * \returns Vertex 3 position
 */
inline const QVector3D &ModelTriangle::vertex3() const
{
    return m_vertex3;
}

/*!
 * \brief Getter for vertex 1 normal
 * \returns Vertex 1 normal
 */
inline const QVector3D &ModelTriangle::normal1() const
{
    return m_normal1;
}

/*!
 * \brief Getter for vertex 2 normal
 * \returns Vertex 2 normal
 */
inline const QVector3D &ModelTriangle::normal2() const
{
    return m_normal2;
}

/*!
 * \brief Getter for vertex 3 normal
 * \returns Vertex 3 normal
 */
inline const QVector3D &ModelTriangle::normal3() const
{
    return m_normal3;
}

}  // namespace Models
}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_MODELS_MODELTRIANGLE_H
