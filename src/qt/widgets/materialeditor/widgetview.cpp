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
    , m_sceneAmbientFactor(0.1F)
    , m_modelSphere(new OpenGL::Models::ModelSphere(_material))
    , m_modelTriangle(new OpenGL::Models::ModelTriangle(_material))
    , m_modelPlane(new OpenGL::Models::ModelPlane(
          _material, QVector3D(), QVector3D(0.5F, 0.0F, 0.0F), QVector3D(0.0F, 0.0F, 0.5F)))
    , m_models({m_modelSphere, m_modelTriangle, m_modelPlane})
    , m_currentModel(0)
{
    const QSettings settings;
    m_modelSphere->setDrawWireFrame(
        settings.value(m_settingsKey + "Sphere/drawWireFrame", m_modelSphere->drawWireFrame()).toBool());
    m_modelSphere->setEquatorPointCount(
        settings.value(m_settingsKey + "Sphere/equatorPointCount", m_modelSphere->equatorPointCount()).toInt());

    m_modelTriangle->setDrawWireFrame(
        settings.value(m_settingsKey + "Triangle/drawWireFrame", m_modelTriangle->drawWireFrame()).toBool());
    m_modelTriangle->setCcw(settings.value(m_settingsKey + "Triangle/ccw", m_modelTriangle->ccw()).toBool());
    m_modelTriangle->setNormal1(
        settings.value(m_settingsKey + "Triangle/normal1", m_modelTriangle->normal1()).value<QVector3D>());
    m_modelTriangle->setNormal2(
        settings.value(m_settingsKey + "Triangle/normal2", m_modelTriangle->normal2()).value<QVector3D>());
    m_modelTriangle->setNormal3(
        settings.value(m_settingsKey + "Triangle/normal3", m_modelTriangle->normal3()).value<QVector3D>());

    m_modelPlane->setDrawWireFrame(
        settings.value(m_settingsKey + "Plane/drawWireFrame", m_modelPlane->drawWireFrame()).toBool());
    m_modelPlane->setNormal1(
        settings.value(m_settingsKey + "Plane/normal1", m_modelPlane->normal1()).value<QVector3D>());
    m_modelPlane->setNormal2(
        settings.value(m_settingsKey + "Plane/normal2", m_modelPlane->normal2()).value<QVector3D>());
    m_modelPlane->setDots1(settings.value(m_settingsKey + "Plane/dots1", m_modelPlane->dots1()).toInt());
    m_modelPlane->setDots2(settings.value(m_settingsKey + "Plane/dots2", m_modelPlane->dots2()).toInt());

    m_pointLights.reserve(OpenGL::ShaderProgram::pointLightsCount);
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, +1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, +1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, +1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, +1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, -1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(+1.0F, -1.0F, -1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, -1.0F, +1.0F)));
    m_pointLights.push_back(OpenGL::PointLight(QVector3D(-1.0F, -1.0F, -1.0F)));

    m_pointLights[0].mode = OpenGL::PointLight::LightQuadratic;
    m_pointLights[0].constant = 1.0F;
    m_pointLights[0].linear = 0.1F;
    m_pointLights[0].quadratic = 0.01F;

    for (int i = 1; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLights[i].mode = OpenGL::PointLight::LightOff;

    m_sceneAmbientFactor = settings.value(m_settingsKey + "sceneAmbientFactor", m_sceneAmbientFactor).toFloat();
    m_currentModel = settings.value(m_settingsKey + "currentModel", m_currentModel).toInt();

    m_directionLight.loadSettings(settings, m_settingsKey + "DirectionLight/");
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLights[i].loadSettings(settings, m_settingsKey + "PointLight_" + QString::number(i) + "_/");

    m_pointLightModels.reserve(OpenGL::ShaderProgram::pointLightsCount);
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLightModels.push_back(new OpenGL::Models::ModelPointLight(m_pointLights[i], 0.1F));
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetView::~WidgetView()
{
    QSettings settings;
    settings.setValue(m_settingsKey + "Sphere/drawWireFrame", m_modelSphere->drawWireFrame());
    settings.setValue(m_settingsKey + "Sphere/equatorPointCount", m_modelSphere->equatorPointCount());
    settings.setValue(m_settingsKey + "Triangle/drawWireFrame", m_modelTriangle->drawWireFrame());
    settings.setValue(m_settingsKey + "Triangle/ccw", m_modelTriangle->ccw());
    settings.setValue(m_settingsKey + "Triangle/normal1", m_modelTriangle->normal1());
    settings.setValue(m_settingsKey + "Triangle/normal2", m_modelTriangle->normal2());
    settings.setValue(m_settingsKey + "Triangle/normal3", m_modelTriangle->normal3());
    settings.setValue(m_settingsKey + "Plane/drawWireFrame", m_modelPlane->drawWireFrame());
    settings.setValue(m_settingsKey + "Plane/normal1", m_modelPlane->normal1());
    settings.setValue(m_settingsKey + "Plane/normal2", m_modelPlane->normal2());
    settings.setValue(m_settingsKey + "Plane/dots1", m_modelPlane->dots1());
    settings.setValue(m_settingsKey + "Plane/dots2", m_modelPlane->dots2());

    settings.setValue(m_settingsKey + "sceneAmbientFactor", m_sceneAmbientFactor);
    settings.setValue(m_settingsKey + "currentModel", m_currentModel);

    m_directionLight.saveSettings(settings, m_settingsKey + "DirectionLight/");
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLights[i].saveSettings(settings, m_settingsKey + "PointLight_" + QString::number(i) + "_/");

    disconnect(m_models.at(m_currentModel),
               &OpenGL::Models::GLModel::changed,
               this,
               static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
    m_models.clear();

    makeCurrent();
    delete m_modelSphere;
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
 * \brief Setter for scene ambient factor
 * \param _value New Scene ambient factor value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setSceneAmbientFactor(float _value)
{
    m_sceneAmbientFactor = _value;
    update();
}

/*!
 * \brief Setter for material, update all models
 * \param _material New material
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setMaterial(const OpenGL::Material &_material)
{
    m_modelSphere->setMaterial(_material);
    m_modelTriangle->setMaterial(_material);
    m_modelPlane->setMaterial(_material);
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
 * \brief Setter for point light
 * \param _idx Point light index
 * \param _pointLight New point light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setPointLight(int _idx, const OpenGL::PointLight &_pointLight)
{
    if (_idx >= 0 && _idx < OpenGL::ShaderProgram::pointLightsCount)
    {
        m_pointLights.at(_idx) = _pointLight;
        makeCurrent();
        m_pointLightModels.at(_idx)->setPointLight(_pointLight);
        doneCurrent();
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
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLightModels[i]->initGL();

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

    m_program->setupSceneAmbientFactor(m_sceneAmbientFactor);

    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLightModels[i]->paintGL(m_program);

    m_models.at(m_currentModel)->paintGL(m_program);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Triangle widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::triangleWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelTriangle->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Triangle widget changed CCW flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::triangleCcwChanged(bool _value)
{
    makeCurrent();
    m_modelTriangle->setCcw(_value);
    doneCurrent();
}

/*!
 * \brief Triangle widget changed normal 1
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::triangleNormal1Changed(const QVector3D &_value)
{
    makeCurrent();
    m_modelTriangle->setNormal1(_value);
    doneCurrent();
}

/*!
 * \brief Triangle widget changed normal 3
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::triangleNormal2Changed(const QVector3D &_value)
{
    makeCurrent();
    m_modelTriangle->setNormal2(_value);
    doneCurrent();
}

/*!
 * \brief Triangle widget changed normal 3
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::triangleNormal3Changed(const QVector3D &_value)
{
    makeCurrent();
    m_modelTriangle->setNormal3(_value);
    doneCurrent();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sphere widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::sphereWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelSphere->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Sphere widget changed point count
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::sphereEquatorPointCountChanged(int _value)
{
    makeCurrent();
    m_modelSphere->setEquatorPointCount(_value);
    doneCurrent();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Plane widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::planeWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelPlane->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Plane widget changed normal 1
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::planeNormal1Changed(const QVector3D &_value)
{
    makeCurrent();
    m_modelPlane->setNormal1(_value);
    doneCurrent();
}

/*!
 * \brief Plane widget changed normal 2
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::planeNormal2Changed(const QVector3D &_value)
{
    makeCurrent();
    m_modelPlane->setNormal2(_value);
    doneCurrent();
}

/*!
 * \brief Plane widget changed dot 1 count
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::planeDots1Changed(int _value)
{
    makeCurrent();
    m_modelPlane->setDots1(_value);
    doneCurrent();
}

/*!
 * \brief Plane widget changed dot 2 count
 * \param _value New value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::planeDots2Changed(int _value)
{
    makeCurrent();
    m_modelPlane->setDots2(_value);
    doneCurrent();
}
