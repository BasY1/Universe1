/*!
 * \file qt/opengl/models/glmodel.cpp
 * \author Michal Steller
 * \brief Base Open GL model class implementation
 */

#include "glmodel.h"

/*!
 * \brief Constructor
 * \param _material Initial material object with values
 * \param _parent Parent \c QObject
 */
Universe1::OpenGL::Models::GLModel::GLModel(const Material &_material, QObject *_parent)
    : QObject(_parent)
    , m_enabled(true)
    , m_material(_material)
{
}

/*!
 * \brief Initialize Open GL
 * \returns Void
 */
void Universe1::OpenGL::Models::GLModel::initGL()
{
    initializeOpenGLFunctions();
    initGLImlp();
}

/*!
 * \brief Paint model within Open GL
 * \param _program Shader program
 * \returns Void
 */
void Universe1::OpenGL::Models::GLModel::paintGL(ShaderProgram *_program)
{
    if (m_enabled && isInit())
    {
        _program->setupMaterial(m_material);

        paintGLImlp(_program);
    }
}

/*!
 * \brief Setter for enabled flag
 * \param _value New enabled flag value
 */
void Universe1::OpenGL::Models::GLModel::setEnabled(bool _value)
{
    m_enabled = _value;
    emit changed();
}

/*!
 * \brief Setter for material
 * \param _value New material object with values
 */
void Universe1::OpenGL::Models::GLModel::setMaterial(const Material &_value)
{
    m_material = _value;
    emit changed();
}

/*!
 * \brief Tool function prepare perpendicular vector
 * \param _vec Base vector
 * \returns Normalized vector perpendicular to base vector
 */
QVector3D Universe1::OpenGL::Models::GLModel::perpendicularVector(const QVector3D &_vec)
{
    static const QVector3D n(1.0F, 0.0F, 0.0F);
    if (qFuzzyCompare(_vec, n))
        return QVector3D::crossProduct(QVector3D(0.0F, 1.0F, 0.0F), _vec).normalized();
    return QVector3D::crossProduct(n, _vec).normalized();
}

/*!
 * \brief Tool function, make sure given normal are perpendicular
 * \param _pole Main normal
 * \param _equator Secondary normal
 * \returns
 */
void Universe1::OpenGL::Models::GLModel::initNormals(QVector3D &_pole, QVector3D &_equator)
{
    if (!qFuzzyCompare(1.0F, _pole.lengthSquared()))
    {
        if (_pole.isNull())
        {
            _pole = QVector3D(0.0F, 0.0F, 1.0F);
            _equator = QVector3D(1.0F, 0.0F, 0.0F);
            return;
        }
        _pole.normalize();
    }

    if (!qFuzzyCompare(1.0F, _equator.lengthSquared()))
    {
        if (_equator.isNull())
        {
            _equator = perpendicularVector(_pole);
            return;
        }

        _equator.normalize();
    }

    if (!qFuzzyIsNull(QVector3D::dotProduct(_pole, _equator)))
        _equator = QVector3D::crossProduct(QVector3D::crossProduct(_equator, _pole), _equator).normalized();
}
