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
    , m_modelCylinder(new OpenGL::Models::ModelCylinder(_material, QVector3D(), 0.25F, 1.0F))
    , m_modelTorus(new OpenGL::Models::ModelTorus(_material, QVector3D(), 1.0F, 0.25F))
    , m_modelBox(new OpenGL::Models::ModelBox(_material))
    , m_modelArrow(new OpenGL::Models::ModelArrow(
          _material, _material, _material, QVector3D(0.0F, 0.0F, -0.5F), QVector3D(0.0F, 0.0F, 0.5F)))
    , m_modelTriangle(new OpenGL::Models::ModelTriangle(_material))
    , m_modelPlane(new OpenGL::Models::ModelPlane(
          _material, QVector3D(), QVector3D(0.5F, 0.0F, 0.0F), QVector3D(0.0F, 0.0F, 0.5F)))
    , m_models({m_modelSphere, m_modelCylinder, m_modelTorus, m_modelBox, m_modelArrow, m_modelTriangle, m_modelPlane})
    , m_currentModel(0)
{
    const QSettings settings;
    m_modelSphere->setDrawWireFrame(
        settings.value(m_settingsKey + "Sphere/drawWireFrame", m_modelSphere->drawWireFrame()).toBool());
    m_modelSphere->setEquatorPointCount(
        settings.value(m_settingsKey + "Sphere/equatorPointCount", m_modelSphere->equatorPointCount()).toInt());

    m_modelCylinder->setDrawWireFrame(
        settings.value(m_settingsKey + "Cylinder/drawWireFrame", m_modelCylinder->drawWireFrame()).toBool());
    m_modelCylinder->setEquatorPointCount(
        settings.value(m_settingsKey + "Cylinder/equatorPointCount", m_modelCylinder->equatorPointCount()).toInt());

    m_modelTorus->setDrawWireFrame(
        settings.value(m_settingsKey + "Torus/drawWireFrame", m_modelTorus->drawWireFrame()).toBool());
    m_modelTorus->setCirclePointCount(
        settings.value(m_settingsKey + "Torus/circlePointCount", m_modelTorus->circlePointCount()).toInt());

    m_modelBox->setDrawWireFrame(
        settings.value(m_settingsKey + "Box/drawWireFrame", m_modelBox->drawWireFrame()).toBool());
    m_modelBox->setNormalSetup(static_cast<OpenGL::Models::ModelBox::NormalSetup>(
        settings.value(m_settingsKey + "Box/normalSetup", static_cast<int>(m_modelBox->normalSetup())).toInt()));
    m_modelBox->setBoxSize1(settings.value(m_settingsKey + "Box/boxSize1", m_modelBox->boxSize1()).toFloat());
    m_modelBox->setBoxSize2(settings.value(m_settingsKey + "Box/boxSize2", m_modelBox->boxSize2()).toFloat());
    m_modelBox->setBoxSize3(settings.value(m_settingsKey + "Box/boxSize3", m_modelBox->boxSize3()).toFloat());

    m_modelArrow->setDrawWireFrame(
        settings.value(m_settingsKey + "Arrow/drawWireFrame", m_modelArrow->drawWireFrame()).toBool());
    m_modelArrow->setCirclePointCount(
        settings.value(m_settingsKey + "Arrow/circlePointCount", m_modelArrow->circlePointCount()).toInt());

    OpenGL::Material tmpMaterial;
    tmpMaterial.loadSettings(settings, m_settingsKey + "Arrow/MaterialLine/");
    m_modelArrow->setMaterialLine(tmpMaterial);

    tmpMaterial.loadSettings(settings, m_settingsKey + "Arrow/MaterialBottom/");
    m_modelArrow->setMaterialBottom(tmpMaterial);

    m_modelTriangle->setDrawWireFrame(
        settings.value(m_settingsKey + "Triangle/drawWireFrame", m_modelTriangle->drawWireFrame()).toBool());
    m_modelTriangle->setInvertedFaces(
        settings.value(m_settingsKey + "Triangle/invertedFaces", m_modelTriangle->invertedFaces()).toBool());
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

    m_pointLightModels.reserve(OpenGL::ShaderProgram::pointLightsCount);
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLightModels.push_back(new OpenGL::Models::ModelPointLight(m_pointLights[i], 0.1F));

    m_spotLightModels.reserve(OpenGL::ShaderProgram::spotLightsCount);
    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        m_spotLightModels.push_back(new OpenGL::Models::ModelSpotLight(m_spotLights[i], 0.2F));

    m_currentModel = settings.value(m_settingsKey + "currentModel", m_currentModel).toInt();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetView::~WidgetView()
{
    QSettings settings;
    settings.setValue(m_settingsKey + "Sphere/drawWireFrame", m_modelSphere->drawWireFrame());
    settings.setValue(m_settingsKey + "Sphere/equatorPointCount", m_modelSphere->equatorPointCount());
    settings.setValue(m_settingsKey + "Cylinder/drawWireFrame", m_modelCylinder->drawWireFrame());
    settings.setValue(m_settingsKey + "Cylinder/equatorPointCount", m_modelCylinder->equatorPointCount());
    settings.setValue(m_settingsKey + "Torus/drawWireFrame", m_modelTorus->drawWireFrame());
    settings.setValue(m_settingsKey + "Torus/circlePointCount", m_modelTorus->circlePointCount());
    settings.setValue(m_settingsKey + "Box/drawWireFrame", m_modelBox->drawWireFrame());
    settings.setValue(m_settingsKey + "Box/normalSetup", static_cast<int>(m_modelBox->normalSetup()));
    settings.setValue(m_settingsKey + "Box/boxSize1", m_modelBox->boxSize1());
    settings.setValue(m_settingsKey + "Box/boxSize2", m_modelBox->boxSize2());
    settings.setValue(m_settingsKey + "Box/boxSize3", m_modelBox->boxSize3());
    settings.setValue(m_settingsKey + "Arrow/drawWireFrame", m_modelArrow->drawWireFrame());
    settings.setValue(m_settingsKey + "Arrow/circlePointCount", m_modelArrow->circlePointCount());
    m_modelArrow->materialLine().saveSettings(settings, m_settingsKey + "Arrow/MaterialLine/");
    m_modelArrow->materialBottom().saveSettings(settings, m_settingsKey + "Arrow/MaterialBottom/");
    settings.setValue(m_settingsKey + "Triangle/drawWireFrame", m_modelTriangle->drawWireFrame());
    settings.setValue(m_settingsKey + "Triangle/invertedFaces", m_modelTriangle->invertedFaces());
    settings.setValue(m_settingsKey + "Triangle/normal1", m_modelTriangle->normal1());
    settings.setValue(m_settingsKey + "Triangle/normal2", m_modelTriangle->normal2());
    settings.setValue(m_settingsKey + "Triangle/normal3", m_modelTriangle->normal3());
    settings.setValue(m_settingsKey + "Plane/drawWireFrame", m_modelPlane->drawWireFrame());
    settings.setValue(m_settingsKey + "Plane/normal1", m_modelPlane->normal1());
    settings.setValue(m_settingsKey + "Plane/normal2", m_modelPlane->normal2());
    settings.setValue(m_settingsKey + "Plane/dots1", m_modelPlane->dots1());
    settings.setValue(m_settingsKey + "Plane/dots2", m_modelPlane->dots2());

    settings.setValue(m_settingsKey + "currentModel", m_currentModel);

    disconnect(m_models.at(m_currentModel),
               &OpenGL::Models::GLModel::changed,
               this,
               static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
    m_models.clear();

    makeCurrent();
    delete m_modelSphere;
    delete m_modelCylinder;
    delete m_modelTorus;
    delete m_modelBox;
    delete m_modelArrow;
    delete m_modelTriangle;
    delete m_modelPlane;

    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        delete m_pointLightModels[i];
    m_pointLightModels.clear();

    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        delete m_spotLightModels[i];
    m_spotLightModels.clear();

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
    m_modelSphere->setMaterial(_material);
    m_modelCylinder->setMaterial(_material);
    m_modelTorus->setMaterial(_material);
    m_modelBox->setMaterial(_material);
    m_modelArrow->setMaterialHeader(_material);
    m_modelTriangle->setMaterial(_material);
    m_modelPlane->setMaterial(_material);
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
 * \brief Setter for spot light
 * \param _idx Spot light index
 * \param _spotLight New spot light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetView::setSpotLight(int _idx, const OpenGL::SpotLight &_spotLight)
{
    if (_idx >= 0 && _idx < OpenGL::ShaderProgram::spotLightsCount)
    {
        m_spotLights.at(_idx) = _spotLight;
        makeCurrent();
        m_spotLightModels.at(_idx)->setSpotLight(_spotLight);
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

    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        m_spotLightModels[i]->initGL();

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
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        m_pointLightModels[i]->paintGL(m_program);

    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        m_spotLightModels[i]->paintGL(m_program);

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
    m_modelTriangle->setInvertedFaces(_value);
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
 * \brief Cylinder widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::cylinderWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelCylinder->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Cylinder widget changed point count
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::cylinderEquatorPointCountChanged(int _value)
{
    makeCurrent();
    m_modelCylinder->setEquatorPointCount(_value);
    doneCurrent();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Torus widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::torusWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelTorus->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Torus widget changed point count
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::torusCirclePointCountChanged(int _value)
{
    makeCurrent();
    m_modelTorus->setCirclePointCount(_value);
    doneCurrent();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Box widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::boxWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelBox->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Box widget changed normal setup
 * \param _value New normal setup value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::boxNormalSetupChanged(OpenGL::Models::ModelBox::NormalSetup _value)
{
    makeCurrent();
    m_modelBox->setNormalSetup(_value);
    doneCurrent();
}

/*!
 * \brief Box widget changed box size 1
 * \param _value New box size 1 value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::boxBoxSize1Changed(float _value)
{
    makeCurrent();
    m_modelBox->setBoxSize1(_value);
    doneCurrent();
}

/*!
 * \brief Box widget changed box size 2
 * \param _value New box size 2 value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::boxBoxSize2Changed(float _value)
{
    makeCurrent();
    m_modelBox->setBoxSize2(_value);
    doneCurrent();
}

/*!
 * \brief Box widget changed box size 3
 * \param _value New box size 3 value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::boxBoxSize3Changed(float _value)
{
    makeCurrent();
    m_modelBox->setBoxSize3(_value);
    doneCurrent();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Arrow widget changed draw wire-frame flag
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::arrowWireFrameChanged(bool _value)
{
    makeCurrent();
    m_modelArrow->setDrawWireFrame(_value);
    doneCurrent();
}

/*!
 * \brief Arrow widget changed point count
 * \param _value New flag value
 */
void Universe1::Widgets::MaterialEditor::WidgetView::arrowCirclePointCountChanged(int _value)
{
    makeCurrent();
    m_modelArrow->setCirclePointCount(_value);
    doneCurrent();
}

/*!
 * \brief Arrow widget changed line material
 * \param _value New line material
 */
void Universe1::Widgets::MaterialEditor::WidgetView::arrowMaterialLineChanged(const OpenGL::Material &_value)
{
    m_modelArrow->setMaterialLine(_value);
}

/*!
 * \brief Arrow widget changed header bottom material
 * \param _value New header bottom material
 */
void Universe1::Widgets::MaterialEditor::WidgetView::arrowMaterialBottomChanged(const OpenGL::Material &_value)
{
    m_modelArrow->setMaterialBottom(_value);
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
