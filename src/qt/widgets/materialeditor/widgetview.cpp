/*!
 * \file qt/widgets/materialeditor/widgetview.cpp
 * \author Michal Steller
 * \brief Material editor Open GL view class implementation
 */

#include "widgetview.h"

/*!
 * \brief Constructor
 * \param _material Material
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::WidgetView::WidgetView(const OpenGL::Material &_material, QWidget *_parent)
    : OpenGL::GLWidget(_parent)
    , m_modelTriangle(new OpenGL::Models::TriangleModel(_material))
    , m_models({m_modelTriangle})
    , m_currentModel(0)
{
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetView::~WidgetView()
{
    disconnect(m_models.at(m_currentModel),
               &OpenGL::Models::GLModel::changed,
               this,
               static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
    m_models.clear();

    makeCurrent();
    delete m_modelTriangle;
    doneCurrent();
}

/*!
 * \brief Returns size of allocated memory within OpenGL context
 * \returns Size of allocated memory within OpenGL context
 */
size_t Universe1::Widgets::MaterialEditor::WidgetView::memoryUsage() const
{
    size_t result = 0U;
    for (const OpenGL::Models::GLModel *m : m_models)
        result += m->memoryUsage();
    return result;
}

/*!
 * \brief Setter for new current model
 * \param _modelIndex Model index
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setModel(int _modelIndex)
{
    if (m_currentModel != _modelIndex && _modelIndex >= 0 && _modelIndex < static_cast<int>(m_models.size()))
    {
        disconnect(m_models.at(m_currentModel),
                   &OpenGL::Models::GLModel::changed,
                   this,
                   static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));

        m_currentModel = _modelIndex;

        connect(m_models.at(m_currentModel),
                &OpenGL::Models::GLModel::changed,
                this,
                static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));

        update();
    }
}

/*!
 * \brief Setter for directional light
 * \param _directionLight New directional light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setDirectionLight(const OpenGL::DirectionLight &_directionLight)
{
    m_directionLight = _directionLight;
    update();
}

/*!
 * \brief Setter for directional light
 * \param _idx Point light index
 * \param _pointLight New point light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setPointLight(int _idx, const OpenGL::PointLight &_pointLight)
{
    if (_idx > 0 && _idx < OpenGL::ShaderProgram::pointLightsCount)
    {
        m_pointLights.at(_idx) = _pointLight;
        update();
    }
}

/*!
 * \brief Mouse double click event handler - switch camera locked center of view flag
 * \param _event Event data
 */
void Universe1::Widgets::MaterialEditor::WidgetView::mouseDoubleClickEvent(QMouseEvent *_event)
{
    if (_event->buttons().testFlag(Qt::RightButton))
    {
        if (m_camera->isLockedCenterOfView())
            m_camera->setLockedCenterOfView(false);
        else
            m_camera->setLockedCenterOfView(QVector3D(), true);
    }
}

/*!
 * \brief Initialize Open GL models
 */
void Universe1::Widgets::MaterialEditor::WidgetView::initializeGLImpl()
{
    for (OpenGL::Models::GLModel *m : m_models)
        m->initGL();

    connect(m_models.at(m_currentModel),
            &OpenGL::Models::GLModel::changed,
            this,
            static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
}

/*!
 * \brief Paint current Open GL model
 */
void Universe1::Widgets::MaterialEditor::WidgetView::paintGLImpl()
{
    m_program->setupDirectionLight(m_directionLight);
    m_program->setupPointLights(m_pointLights);

    m_models.at(m_currentModel)->paintGL(m_program);
}
