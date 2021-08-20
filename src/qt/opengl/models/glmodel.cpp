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
