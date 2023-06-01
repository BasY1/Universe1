#ifndef UNIVERSE1_VIDEO_SHADER_H
#define UNIVERSE1_VIDEO_SHADER_H

#include "data3d.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Open GL Shader program
 */
class Shader : public QOpenGLShaderProgram
{
    Q_OBJECT
 protected:
    QOpenGLFunctions *f;  //!< Open GL functions

    const QVector3D m_camPos;                                          //!< Camera position
    const QMatrix4x4 m_camMvp;                                         //!< MVP matrix
    const QMatrix4x4 m_perspectiveMatrix;                              //!< Perspective matrix
    const QVector3D m_lightDir = QVector3D(-1, -2, -10).normalized();  //!< Light direction
    const QVector3D m_lightColor = QVector3D(1, 1, 1);                 //!< Light color
    const float m_lightAmbient = 0.75f;                                //!< Light ambient factor

 public:
    /*!
     * \brief Constructor
     * \param _f Open GL functions
     * \param _cameraStats Camera statistics
     * \param _perspectiveMatrix Perspective matrix
     * \param _parent Parent \c QObject
     */
    Shader(QOpenGLFunctions *_f,
           const std::pair<QVector3D, QMatrix4x4> &_cameraStats,
           const QMatrix4x4 &_perspectiveMatrix,
           QObject *_parent = nullptr);

    /*!
     * \brief Getter for camera position
     * \return Camera position
     */
    inline const QVector3D &cam() const
    {
        return m_camPos;
    }

    /*!
     * \brief Getter for light direction
     * \return Light direction
     */
    inline const QVector3D &lightDir() const
    {
        return m_lightDir;
    }

    /*!
     * \brief Initialize shader
     * \return Success flag
     */
    virtual bool initialize();

    /*!
     * \brief Draw 3D objects
     * \param _data 3D objects
     * \return
     */
    virtual void draw(std::list<Data3D> &_data);

 protected:
    /*!
     * \brief Draw single 3D object
     * \param _data 3D object
     * \return
     */
    virtual void drawData(const Data3D *_data);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_SHADER_H
