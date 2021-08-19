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
    : OpenGL::GLWidget("MaterialEditor/View/", true, _parent)
    , m_modelSphere(new OpenGL::Models::ModelSphere(_material))
    , m_modelTriangle(new OpenGL::Models::ModelTriangle(_material))
    , m_models({m_modelSphere, m_modelTriangle})
    , m_currentModel(0)
{
    m_pointLights.reserve(OpenGL::ShaderProgram::pointLightsCount);
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, -1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, -1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, -1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, -1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, +1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, +1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, +1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, +1.0F, +1.0F)));

    const QSettings settings;
    m_currentModel = settings.value(m_settingsKey + "currentModel", m_currentModel).toInt();

    m_directionLight.loadSettings(settings, m_settingsKey + "/DirectionLight/");
    for (size_t i = 0; i < m_pointLights.size(); ++i)
        m_pointLights[i].loadSettings(settings, m_settingsKey + "/PointLight_" + QString::number(i) + "_/");
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetView::~WidgetView()
{
    QSettings settings;
    settings.setValue(m_settingsKey + "currentModel", m_currentModel);

    m_directionLight.saveSettings(settings, m_settingsKey + "/DirectionLight/");
    for (size_t i = 0; i < m_pointLights.size(); ++i)
        m_pointLights[i].saveSettings(settings, m_settingsKey + "/PointLight_" + QString::number(i) + "_/");

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
void Universe1::Widgets::MaterialEditor::WidgetView::setCurrentModel(int _modelIndex)
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
 * \brief Setter for material, update all models
 * \param _material New material
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setMaterial(const OpenGL::Material &_material)
{
    m_modelTriangle->setMaterial(_material);
    m_modelSphere->setMaterial(_material);
    update();
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
