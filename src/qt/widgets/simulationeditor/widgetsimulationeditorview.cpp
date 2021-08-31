/*!
 * \file qt/widgets/simulationeditor/widgetsimulationeditorview.cpp
 * \author Michal Steller
 * \brief Simulation editor Open GL view class implementation
 */

#include "widgetsimulationeditorview.h"

#include <QRect>

#define AXIS_LINE_R 0.02F  //!< Default line radius for scene axis arrow
#define AXIS_HEAD_R 0.05F  //!< Default header radius for scene axis arrow
#define AXIS_HEAD_L 0.1F   //!< Default header length for scene axis arrow

#define FORCE_LINE_R_ALL 0.1F   //!< Default line radius for force arrow
#define FORCE_HEAD_R_ALL 0.2F   //!< Default header radius for force arrow
#define FORCE_HEAD_L_ALL 0.5F   //!< Default header length for force arrow
#define FORCE_LINE_R_SEL 0.15F  //!< Default line radius for selected force arrow
#define FORCE_HEAD_R_SEL 0.3F   //!< Default header radius for selected force arrow

#define SPIN_LINE_R_ALL 0.02F  //!< Default line radius for spin arrow
#define SPIN_HEAD_R_ALL 0.02F  //!< Default header radius for spin arrow
#define SPIN_HEAD_L_ALL 0.2F   //!< Default header length for spin arrow
#define SPIN_LINE_R_SEL 0.04F  //!< Default line radius for selected spin arrow
#define SPIN_HEAD_R_SEL 0.05F  //!< Default header radius for selected spin arrow

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _sceneRange Simulation scene range from all objects paths
 * \param _pathData Object's path data
 * \param _currentTimePositionsData Object's positions at current time
 * \param _currentTimePropertyData Object's Properties at current time
 * \param _currentTimePropertyMaxLength Maximum length of current vector property
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::WidgetSimulationEditorView(
    const Project::QSimulation *_simulation,
    const std::pair<QVector3D, QVector3D> *_sceneRange,
    const std::vector<std::vector<std::pair<double, QVector3D>>> *_pathData,
    const std::vector<QVector3D> *_currentTimePositionsData,
    const std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>>
        *_currentTimePropertyData,
    const std::map<Project::QSimulation::ElementProperty, float> *_currentTimePropertyMaxLength,
    QWidget *_parent)
    : OpenGL::GLWidget(new OpenGL::ShaderProgram(4, 4, 3),
                       "SimulationEditor/View/" + _simulation->simulationTypeName() + '/',
                       true,  // false, //  save camera
                       _parent)
    , m_simulation(_simulation)
    , m_sceneRange(_sceneRange)
    , m_pathData(_pathData)
    , m_currentTimePositionsData(_currentTimePositionsData)
    , m_currentTimePropertyData(_currentTimePropertyData)
    , m_currentTimePropertyMaxLength(_currentTimePropertyMaxLength)
    , m_isObserver1(false)
    , m_isObserver2(false)
    , m_showAxis(true)
    , m_showDots(true)
    , m_showPathAll(false)
    , m_showPathSelected(true)
    , m_currentTime(0.0)
    , m_axisX(new OpenGL::Models::ModelArrow(OpenGL::Material::materialRed,
                                             OpenGL::Material::materialRedLight,
                                             OpenGL::Material::materialRedDark,
                                             QVector3D(),
                                             QVector3D(1.0F, 0.0F, 0.0F),
                                             AXIS_LINE_R,
                                             AXIS_HEAD_R,
                                             AXIS_HEAD_L))
    , m_axisY(new OpenGL::Models::ModelArrow(OpenGL::Material::materialGreen,
                                             OpenGL::Material::materialGreenLight,
                                             OpenGL::Material::materialGreenDark,
                                             QVector3D(),
                                             QVector3D(0.0F, 1.0F, 0.0F),
                                             AXIS_LINE_R,
                                             AXIS_HEAD_R,
                                             AXIS_HEAD_L))
    , m_axisZ(new OpenGL::Models::ModelArrow(OpenGL::Material::materialBlue,
                                             OpenGL::Material::materialBlueLight,
                                             OpenGL::Material::materialBlueDark,
                                             QVector3D(),
                                             QVector3D(0.0F, 0.0F, 1.0F),
                                             AXIS_LINE_R,
                                             AXIS_HEAD_R,
                                             AXIS_HEAD_L))
    , m_dotsXY(new OpenGL::Models::ModelDots(OpenGL::Material::materialCyan))
    , m_observer1(new OpenGL::Models::ModelSingularity(OpenGL::Material::materialMagentaDark, QVector3D()))
    , m_observer2(new OpenGL::Models::ModelSingularity(OpenGL::Material::materialYellowDark, QVector3D()))
{
    m_dotsXY->setMaterialMode(OpenGL::Material::MaterialAmbient);

    m_pointLightModels.reserve(m_program->pointLightsCount());
    for (int i = 0; i < m_program->pointLightsCount(); ++i)
        m_pointLightModels.push_back(new OpenGL::Models::ModelPointLight(m_pointLights[i], 0.1F));

    m_spotLightModels.reserve(m_program->spotLightsCount());
    for (int i = 0; i < m_program->spotLightsCount(); ++i)
        m_spotLightModels.push_back(new OpenGL::Models::ModelSpotLight(m_spotLights[i], 0.2F));

    const QSettings settings;
    m_showAxis = settings.value(m_settingsKey + "showAxis", m_showAxis).toBool();
    m_showDots = settings.value(m_settingsKey + "showDots", m_showDots).toBool();
    m_showPathAll = settings.value(m_settingsKey + "showPathAll", m_showPathAll).toBool();
    m_showPathSelected = settings.value(m_settingsKey + "showPathSelected", m_showPathSelected).toBool();

    if (settings.contains(m_settingsKey + "propertyAll"))
    {
        m_propertyAll =
            static_cast<Project::QSimulation::ElementProperties>(settings.value(m_settingsKey + "propertyAll").toInt());
        m_propertySelected = static_cast<Project::QSimulation::ElementProperties>(
            settings.value(m_settingsKey + "propertySelected").toInt());
    }
    else
    {
        const Project::QSimulation::ElementProperties props = m_simulation->supportedElementProperties();

        if (props.testFlag(Project::QSimulation::PropertyMass))
        {
            m_propertyAll |= Project::QSimulation::PropertyMass;
            m_propertySelected |= Project::QSimulation::PropertyMass;
        }

        if (props.testFlag(Project::QSimulation::PropertyVelocity))
            m_propertySelected |= Project::QSimulation::PropertyVelocity;

        if (props.testFlag(Project::QSimulation::PropertyForce))
        {
            m_propertySelected |= Project::QSimulation::PropertyForce;

            if (props.testFlag(Project::QSimulation::PropertyForceRed))
                m_propertySelected |= Project::QSimulation::PropertyForceRed;
            if (props.testFlag(Project::QSimulation::PropertyForceGreen))
                m_propertySelected |= Project::QSimulation::PropertyForceGreen;
            if (props.testFlag(Project::QSimulation::PropertyForceBlue))
                m_propertySelected |= Project::QSimulation::PropertyForceBlue;
        }
        else if (props.testFlag(Project::QSimulation::PropertyAcceleration))
        {
            m_propertySelected |= Project::QSimulation::PropertyAcceleration;
        }

        if (props.testFlag(Project::QSimulation::PropertySpin))
        {
            m_propertySelected |= Project::QSimulation::PropertySpin;
            if (props.testFlag(Project::QSimulation::PropertySpinRed))
                m_propertySelected |= Project::QSimulation::PropertySpinRed;
            if (props.testFlag(Project::QSimulation::PropertySpinGreen))
                m_propertySelected |= Project::QSimulation::PropertySpinGreen;
            if (props.testFlag(Project::QSimulation::PropertySpinBlue))
                m_propertySelected |= Project::QSimulation::PropertySpinBlue;
        }
    }
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::~WidgetSimulationEditorView()
{
    QSettings settings;
    settings.setValue(m_settingsKey + "showAxis", m_showAxis);
    settings.setValue(m_settingsKey + "showDots", m_showDots);
    settings.setValue(m_settingsKey + "showPathAll", m_showPathAll);
    settings.setValue(m_settingsKey + "showPathSelected", m_showPathSelected);
    settings.setValue(m_settingsKey + "propertyAll", static_cast<int>(m_propertyAll));
    settings.setValue(m_settingsKey + "propertySelected", static_cast<int>(m_propertySelected));

    makeCurrent();

    delete m_axisX;
    delete m_axisY;
    delete m_axisZ;
    delete m_dotsXY;
    delete m_observer1;
    delete m_observer2;

    for (OpenGL::Models::ModelSingularity *tmp : m_observer1Sources)
        delete tmp;

    for (OpenGL::Models::ModelSingularity *tmp : m_observer2Sources)
        delete tmp;

    clearSimulDataGL();

    for (OpenGL::Models::ModelPointLight *tmp : m_pointLightModels)
        delete tmp;

    for (OpenGL::Models::ModelSpotLight *tmp : m_spotLightModels)
        delete tmp;

    doneCurrent();
}

/*!
 * \brief Returns size of allocated memory within OpenGL context
 * \returns Size of allocated memory within OpenGL context
 */
size_t Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::memoryUsage() const
{
    size_t result = 0U;
    result += m_axisX->memoryUsage();
    result += m_axisY->memoryUsage();
    result += m_axisZ->memoryUsage();
    result += m_dotsXY->memoryUsage();
    result += m_observer1->memoryUsage();
    result += m_observer2->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_observer1Sources)
        result += tmp->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_observer2Sources)
        result += tmp->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_objectPath)
        result += tmp->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_currentTimeAll)
        result += tmp->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_currentTimeSelected)
        result += tmp->memoryUsage();

    for (const std::pair<const Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>> &tmp :
         m_modelsAll)
    {
        for (const OpenGL::Models::GLModel *tmp2 : tmp.second)
            result += tmp2->memoryUsage();
    }

    for (const std::pair<const Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>> &tmp :
         m_modelsSelected)
    {
        for (const OpenGL::Models::GLModel *tmp2 : tmp.second)
            result += tmp2->memoryUsage();
    }

    for (const OpenGL::Models::GLModel *tmp : m_pointLightModels)
        result += tmp->memoryUsage();

    for (const OpenGL::Models::GLModel *tmp : m_spotLightModels)
        result += tmp->memoryUsage();

    return result;
}

/*!
 * \brief Setter for point light
 * \param _idx Point light index
 * \param _pointLight New point light object with values
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setPointLight(
    int _idx, const OpenGL::PointLight &_pointLight)
{
    if (_idx >= 0 && _idx < m_program->pointLightsCount())
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
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setSpotLight(int _idx,
                                                                                    const OpenGL::SpotLight &_spotLight)
{
    if (_idx >= 0 && _idx < m_program->spotLightsCount())
    {
        m_spotLights.at(_idx) = _spotLight;
        makeCurrent();
        m_spotLightModels.at(_idx)->setSpotLight(_spotLight);
        doneCurrent();
        update();
    }
}

/*!
 * \brief Setter for show axis flag
 * \param _value New show axis flag
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setShowAxis(bool _value)
{
    m_showAxis = _value;
    update();
}

/*!
 * \brief Setter for show dots flag
 * \param _value New show dots flag
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setShowDots(bool _value)
{
    m_showDots = _value;
    update();
}

/*!
 * \brief Setter for show objects path flag
 * \param _value New show objects path flag
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setShowPathAll(bool _value)
{
    m_showPathAll = _value;
    update();
}

/*!
 * \brief Setter for show selected objects path flag
 * \param _value New show selected objects path flag
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setShowPathSelected(bool _value)
{
    m_showPathSelected = _value;
    update();
}

/*!
 * \brief Setter for visible objects properties
 * \param _value New visible objects properties
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setPropertyAll(
    const Project::QSimulation::ElementProperties _value)
{
    m_propertyAll = _value;
    update();
}

/*!
 * \brief Setter for visible selected objects properties
 * \param _value New visible selected objects properties
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setPropertySelected(
    const Project::QSimulation::ElementProperties _value)
{
    m_propertySelected = _value;
    update();
}

/*!
 * \brief Setter for current timestamp in simulation
 * \param _value New current timestamp in simulation
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setCurrentTime(double _value)
{
    m_currentTime = _value;
    makeCurrent();
    clearSimulDataGL();
    build();
    doneCurrent();
    update();
}

/*!
 * \brief Rebuild simulation data
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::rebuildSimulation()
{
    m_isObserver1 = false;
    m_isObserver2 = false;
    m_currentTime = 0.0F;
    m_selected.clear();

    makeCurrent();

    for (OpenGL::Models::ModelSingularity *tmp : m_observer1Sources)
        delete tmp;
    m_observer1Sources.clear();

    for (OpenGL::Models::ModelSingularity *tmp : m_observer2Sources)
        delete tmp;
    m_observer2Sources.clear();

    clearSimulDataGL();

    build();

    doneCurrent();

    update();
}

/*!
 * \brief Setter for observer 1
 * \param _position Observer position
 * \param _objectData Object's sources position
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setObserver1(
    const QVector3D &_position, const std::vector<std::pair<double, QVector3D>> &_objectData)
{
    makeCurrent();

    for (OpenGL::Models::ModelSingularity *s : m_observer1Sources)
        delete s;
    m_observer1Sources.clear();

    m_observer1->setPosition(_position);

    m_observer1Sources.reserve(_objectData.size());
    for (const std::pair<double, QVector3D> &p : _objectData)
    {
        OpenGL::Models::ModelSingularity *ms =
            new OpenGL::Models::ModelSingularity(OpenGL::Material::materialMagenta, p.second);
        ms->initGL();
        m_observer1Sources.push_back(ms);
    }

    m_isObserver1 = true;

    doneCurrent();
    update();
}

/*!
 * \brief Setter for observer 2
 * \param _position Observer position
 * \param _objectData Object's sources position
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setObserver2(
    const QVector3D &_position, const std::vector<std::pair<double, QVector3D>> &_objectData)
{
    makeCurrent();

    for (OpenGL::Models::ModelSingularity *s : m_observer2Sources)
        delete s;
    m_observer2Sources.clear();

    m_observer2->setPosition(_position);

    m_observer2Sources.reserve(_objectData.size());
    for (const std::pair<double, QVector3D> &p : _objectData)
    {
        OpenGL::Models::ModelSingularity *ms =
            new OpenGL::Models::ModelSingularity(OpenGL::Material::materialYellow, p.second);
        ms->initGL();
        m_observer2Sources.push_back(ms);
    }

    m_isObserver2 = true;

    doneCurrent();
    update();
}

/*!
 * \brief Disables observer 1 visualization
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::hideObserver1()
{
    m_isObserver1 = false;
    update();
}

/*!
 * \brief Disables observer 2 visualization
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::hideObserver2()
{
    m_isObserver2 = false;
    update();
}

/*!
 * \brief Setter for selected objects
 * \param _value New selected objects
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::setSelected(const std::set<size_t> &_value)
{
    if (m_selected.empty() && _value.empty())
        return;

    m_selected = _value;

    // if (m_selected.size() != 1U)
    //    m_camera->setLockedCenterOfView(false);
    // else
    //    m_camera->setLockedCenterOfView(m_currentTimePositionsData->at(*m_selected.cbegin()), true);

    update();
}

/*!
 * \brief Initialize Open GL models
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::initializeGLImpl()
{
    m_axisX->initGL();
    m_axisY->initGL();
    m_axisZ->initGL();
    m_dotsXY->initGL();
    m_observer1->initGL();
    m_observer2->initGL();

    for (int i = 0; i < m_program->pointLightsCount(); ++i)
        m_pointLightModels[i]->initGL();

    for (int i = 0; i < m_program->spotLightsCount(); ++i)
        m_spotLightModels[i]->initGL();

    build();
}

/*!
 * \brief Paint current Open GL model
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::paintGLImpl()
{
    for (int i = 0; i < m_program->pointLightsCount(); ++i)
        m_pointLightModels[i]->paintGL(m_program);

    for (int i = 0; i < m_program->spotLightsCount(); ++i)
        m_spotLightModels[i]->paintGL(m_program);

    if (m_showAxis)
    {
        m_axisX->paintGL(m_program);
        m_axisY->paintGL(m_program);
        m_axisZ->paintGL(m_program);
    }

    if (m_showDots)
        m_dotsXY->paintGL(m_program);

    if (m_isObserver1)
    {
        m_observer1->paintGL(m_program);
        for (OpenGL::Models::ModelSingularity *s : m_observer1Sources)
            s->paintGL(m_program);
    }

    if (m_isObserver2)
    {
        m_observer2->paintGL(m_program);
        for (OpenGL::Models::ModelSingularity *s : m_observer2Sources)
            s->paintGL(m_program);
    }

    const std::list<Project::QSimulation::ElementProperty> flagsAll =
        Project::QSimulation::parseElementProperties(m_propertyAll);

    if (m_selected.empty())
    {
        if (m_showPathAll)
        {
            for (OpenGL::Models::ModelPath *s : m_objectPath)
                s->paintGL(m_program);
        }

        for (const Project::QSimulation::ElementProperty f : flagsAll)
        {
            std::unordered_map<Project::QSimulation::ElementProperty,
                               std::vector<OpenGL::Models::GLModel *>>::const_iterator it = m_modelsAll.find(f);

            if (it != m_modelsAll.cend())
            {
                for (OpenGL::Models::GLModel *m : it->second)
                    m->paintGL(m_program);
            }
        }

        for (OpenGL::Models::GLModel *m : m_currentTimeAll)
            m->paintGL(m_program);
    }
    else
    {
        const std::list<Project::QSimulation::ElementProperty> flagsSelected =
            Project::QSimulation::parseElementProperties(m_propertySelected);

        for (size_t i = 0U; i < m_objectPath.size(); ++i)
        {
            if (m_selected.find(i) != m_selected.cend())
            {
                glLineWidth(m_lineWidth * 2.0F);

                if (m_showPathSelected)
                    m_objectPath[i]->paintGL(m_program);

                glLineWidth(m_lineWidth);

                for (const Project::QSimulation::ElementProperty f : flagsSelected)
                {
                    std::unordered_map<Project::QSimulation::ElementProperty,
                                       std::vector<OpenGL::Models::GLModel *>>::const_iterator it =
                        m_modelsSelected.find(f);
                    if (it != m_modelsSelected.cend())
                        it->second[i]->paintGL(m_program);
                }

                m_currentTimeSelected[i]->paintGL(m_program);
            }
            else
            {
                if (m_showPathAll)
                    m_objectPath[i]->paintGL(m_program);

                for (const Project::QSimulation::ElementProperty f : flagsAll)
                {
                    std::unordered_map<Project::QSimulation::ElementProperty,
                                       std::vector<OpenGL::Models::GLModel *>>::const_iterator it = m_modelsAll.find(f);
                    if (it != m_modelsAll.cend())
                        it->second[i]->paintGL(m_program);
                }

                m_currentTimeAll[i]->paintGL(m_program);
            }
        }
    }
}

/*!
 * \brief Mouse double-click handler
 * \param _event Event data
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::mouseDoubleClickEvent(QMouseEvent *_event)
{
    if (m_currentTimePositionsData->empty())
        return;

    if (_event->buttons() == Qt::RightButton)
    {
        emit selectionClearRequest();
    }
    else if (_event->buttons() == Qt::LeftButton)
    {
        const QVector2D screenPos(_event->pos().x(), _event->pos().y());
        const QRect viewPort(0, 0, width(), height());
        const float hh = height();
        // const QMatrix4x4 view = m_camera->viewMatrix();
        const QMatrix4x4 view = m_camera->lookAtMatrix();
        const QMatrix4x4 proj = m_camera->perspectiveMatrix();

        std::vector<QVector3D>::const_iterator it = m_currentTimePositionsData->cbegin();

        QVector3D posProj = (*it).project(view, proj, viewPort);
        float distance = QVector2D(posProj.x(), hh - posProj.y()).distanceToPoint(screenPos);
        uint closeIdx = 0U;
        uint tmpIdx = 1U;

        ++it;
        while (it != m_currentTimePositionsData->cend())
        {
            posProj = (*it).project(view, proj, viewPort);
            const float distance2 = QVector2D(posProj.x(), hh - posProj.y()).distanceToPoint(screenPos);
            if (distance2 < distance)
            {
                distance = distance2;
                closeIdx = tmpIdx;
            }
            ++it;
            ++tmpIdx;
        }

        if (distance < 5.0F)
        {
            if (_event->modifiers() == Qt::ControlModifier)
                emit selectionInsertRequest(closeIdx);
            else
                emit selectionChangeRequest(closeIdx);
        }
        else if (_event->modifiers() != Qt::ControlModifier)
        {
            emit selectionClearRequest();
        }
    }
}

/*!
 * \brief Clear simulation Open GL data
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::clearSimulDataGL()
{
    for (OpenGL::Models::ModelPath *tmp : m_objectPath)
        delete tmp;
    m_objectPath.clear();

    for (OpenGL::Models::GLModel *tmp : m_currentTimeAll)
        delete tmp;
    m_currentTimeAll.clear();

    for (OpenGL::Models::GLModel *tmp : m_currentTimeSelected)
        delete tmp;
    m_currentTimeSelected.clear();

    for (std::pair<const Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>> &tmp :
         m_modelsAll)
    {
        for (OpenGL::Models::GLModel *tmp2 : tmp.second)
            delete tmp2;
    }
    m_modelsAll.clear();

    for (std::pair<const Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>> &tmp :
         m_modelsSelected)
    {
        for (OpenGL::Models::GLModel *tmp2 : tmp.second)
            delete tmp2;
    }
    m_modelsSelected.clear();
}

/*!
 * \brief Rebuild visualization data
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditorView::build()
{
    const size_t objCount = m_pathData->size();
    if (objCount == 0U || objCount != m_currentTimePositionsData->size())
        return;

    for (const std::pair<const Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>> &prop :
         *m_currentTimePropertyData)
        if (objCount != prop.second.size())
            return;

    m_dotsXY->setPlaneXY(std::min(-10, static_cast<int>(m_sceneRange->first.x()) - 1),
                         std::min(-10, static_cast<int>(m_sceneRange->first.y()) - 1),
                         std::max(10, static_cast<int>(m_sceneRange->second.x()) + 1),
                         std::max(10, static_cast<int>(m_sceneRange->second.y()) + 1));

    for (const std::vector<std::pair<double, QVector3D>> &path : *m_pathData)
    {
        OpenGL::Models::ModelPath *mp = new OpenGL::Models::ModelPath(
            {OpenGL::Material::materialCyanDark, OpenGL::Material::materialYellow, OpenGL::Material::materialMagenta});
        mp->initGL();
        mp->setMaterialMode(OpenGL::Material::MaterialDiffuse);

        std::vector<QVector3D> vertexData;
        std::vector<uint8_t> colorData;
        vertexData.reserve(path.size());
        colorData.reserve(path.size());
        for (const std::pair<double, QVector3D> &p : path)
        {
            vertexData.push_back(p.second);

            if (p.first < m_currentTime)
            {
                if (p.first < 0.0)
                    colorData.push_back(1U);
                else
                    colorData.push_back(2U);
            }
            else
            {
                colorData.push_back(0U);
            }
        }

        mp->setPath(vertexData, colorData);
        m_objectPath.push_back(mp);
    }

    m_currentTimeAll.reserve(objCount);
    m_currentTimeSelected.reserve(objCount);

    if (m_simulation->usesRadius())
    {
        for (const QVector3D &pos : *m_currentTimePositionsData)
        {
            OpenGL::Models::GLModel *m1 = new OpenGL::Models::ModelSphere(OpenGL::Material::materialWhite, pos, 1.0F);
            OpenGL::Models::GLModel *m2 =
                new OpenGL::Models::ModelSphere(OpenGL::Material::materialWhiteLight, pos, 1.0F);
            m1->initGL();
            m2->initGL();
            m_currentTimeAll.push_back(m1);
            m_currentTimeSelected.push_back(m2);
        }
    }
    else
    {
        static const OpenGL::Material whiteMoreDarker = OpenGL::Material::materialWhiteDark.darker();
        for (const QVector3D &pos : *m_currentTimePositionsData)
        {
            OpenGL::Models::GLModel *m1 = new OpenGL::Models::ModelSingularity(whiteMoreDarker,
                                                                               OpenGL::Material::materialWhiteDark,
                                                                               OpenGL::Material::materialWhite,
                                                                               pos,
                                                                               0.01F,
                                                                               0.9F);

            OpenGL::Models::GLModel *m2 = new OpenGL::Models::ModelSingularity(OpenGL::Material::materialWhiteDark,
                                                                               OpenGL::Material::materialWhite,
                                                                               OpenGL::Material::materialWhiteLight,
                                                                               pos,
                                                                               0.05F,
                                                                               0.95F);
            m1->setMaterialMode(OpenGL::Material::MaterialDiffuse);
            m2->setMaterialMode(OpenGL::Material::MaterialDiffuse);
            m1->initGL();
            m2->initGL();
            m_currentTimeAll.push_back(m1);
            m_currentTimeSelected.push_back(m2);
        }
    }

    for (const std::pair<const Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>> &prop :
         *m_currentTimePropertyData)
    {
        std::map<Project::QSimulation::ElementProperty, float>::const_iterator itRange =
            m_currentTimePropertyMaxLength->find(prop.first);

        if (itRange == m_currentTimePropertyMaxLength->cend())
            continue;

        const float &propRange = itRange->second;
        const std::vector<std::pair<double, QVector3D>> &propData = prop.second;

        std::vector<OpenGL::Models::GLModel *> &tmpAll = m_modelsAll.insert({prop.first, {}}).first->second;
        std::vector<OpenGL::Models::GLModel *> &tmpSel = m_modelsSelected.insert({prop.first, {}}).first->second;
        tmpAll.reserve(objCount);
        tmpSel.reserve(objCount);

        switch (prop.first)
        {
        case Project::QSimulation::PropertyNone: break;

        case Project::QSimulation::PropertyMass:
            if (qFuzzyIsNull(propRange))
            {
                for (size_t i = 0U; i < objCount; ++i)
                {
                    OpenGL::Models::GLModel *mAll = new OpenGL::Models::ModelSphere(
                        OpenGL::Material::materialGreen, m_currentTimePositionsData->at(i), 1.0F);
                    OpenGL::Models::GLModel *mSel = new OpenGL::Models::ModelSphere(
                        OpenGL::Material::materialGreenLight, m_currentTimePositionsData->at(i), 1.0F);
                    mAll->initGL();
                    mSel->initGL();
                    tmpAll.push_back(mAll);
                    tmpSel.push_back(mSel);
                }
            }
            else
            {
                for (size_t i = 0U; i < objCount; ++i)
                {
                    const float massRatio = propData[i].second.x() / propRange;
                    const float massRadius = std::cbrt(massRatio * 0.1F);
                    const OpenGL::Material material = OpenGL::Material::ratioGreenRed(massRatio);

                    OpenGL::Models::GLModel *mAll = new OpenGL::Models::ModelSphere(
                        material.darker(), m_currentTimePositionsData->at(i), massRadius);
                    OpenGL::Models::GLModel *mSel =
                        new OpenGL::Models::ModelSphere(material, m_currentTimePositionsData->at(i), massRadius);
                    mAll->initGL();
                    mSel->initGL();
                    tmpAll.push_back(mAll);
                    tmpSel.push_back(mSel);
                }
            }
            break;

        case Project::QSimulation::PropertyVelocity:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialCyanDark,
                                                   OpenGL::Material::materialCyanDark.darker(),
                                                   0.01F,
                                                   0.05F,
                                                   0.1F,
                                                   0.03F,
                                                   0.15F);
            break;

        case Project::QSimulation::PropertyAcceleration:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialYellowDark,
                                                   OpenGL::Material::materialYellowDark.darker(),
                                                   0.05F,
                                                   0.15F,
                                                   0.2F,
                                                   0.10F,
                                                   0.30F);
            break;

        case Project::QSimulation::PropertyForce:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialWhite,
                                                   OpenGL::Material::materialWhiteDark,
                                                   FORCE_LINE_R_ALL,
                                                   FORCE_HEAD_R_ALL,
                                                   FORCE_HEAD_L_ALL,
                                                   FORCE_LINE_R_SEL,
                                                   FORCE_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertyForceRed:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialRed,
                                                   OpenGL::Material::materialRedDark,
                                                   FORCE_LINE_R_ALL,
                                                   FORCE_HEAD_R_ALL,
                                                   FORCE_HEAD_L_ALL,
                                                   FORCE_LINE_R_SEL,
                                                   FORCE_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertyForceGreen:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialGreen,
                                                   OpenGL::Material::materialGreenDark,
                                                   FORCE_LINE_R_ALL,
                                                   FORCE_HEAD_R_ALL,
                                                   FORCE_HEAD_L_ALL,
                                                   FORCE_LINE_R_SEL,
                                                   FORCE_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertyForceBlue:
            addVectors<OpenGL::Models::ModelArrow>(tmpAll,
                                                   tmpSel,
                                                   propData,
                                                   propRange,
                                                   OpenGL::Material::materialBlue,
                                                   OpenGL::Material::materialBlueDark,
                                                   FORCE_LINE_R_ALL,
                                                   FORCE_HEAD_R_ALL,
                                                   FORCE_HEAD_L_ALL,
                                                   FORCE_LINE_R_SEL,
                                                   FORCE_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertySpin:
            addVectors<OpenGL::Models::ModelSpinArrow>(tmpAll,
                                                       tmpSel,
                                                       propData,
                                                       propRange,
                                                       OpenGL::Material::materialWhite,
                                                       OpenGL::Material::materialWhiteDark,
                                                       SPIN_LINE_R_ALL,
                                                       SPIN_HEAD_R_ALL,
                                                       SPIN_HEAD_L_ALL,
                                                       SPIN_LINE_R_SEL,
                                                       SPIN_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertySpinRed:
            addVectors<OpenGL::Models::ModelSpinArrow>(tmpAll,
                                                       tmpSel,
                                                       propData,
                                                       propRange,
                                                       OpenGL::Material::materialRed,
                                                       OpenGL::Material::materialRedDark,
                                                       SPIN_LINE_R_ALL,
                                                       SPIN_HEAD_R_ALL,
                                                       SPIN_HEAD_L_ALL,
                                                       SPIN_LINE_R_SEL,
                                                       SPIN_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertySpinGreen:
            addVectors<OpenGL::Models::ModelSpinArrow>(tmpAll,
                                                       tmpSel,
                                                       propData,
                                                       propRange,
                                                       OpenGL::Material::materialGreen,
                                                       OpenGL::Material::materialGreenDark,
                                                       SPIN_LINE_R_ALL,
                                                       SPIN_HEAD_R_ALL,
                                                       SPIN_HEAD_L_ALL,
                                                       SPIN_LINE_R_SEL,
                                                       SPIN_HEAD_R_SEL);
            break;

        case Project::QSimulation::PropertySpinBlue:
            addVectors<OpenGL::Models::ModelSpinArrow>(tmpAll,
                                                       tmpSel,
                                                       propData,
                                                       propRange,
                                                       OpenGL::Material::materialBlue,
                                                       OpenGL::Material::materialBlueDark,
                                                       SPIN_LINE_R_ALL,
                                                       SPIN_HEAD_R_ALL,
                                                       SPIN_HEAD_L_ALL,
                                                       SPIN_LINE_R_SEL,
                                                       SPIN_HEAD_R_SEL);

            break;
        }
    }
}
