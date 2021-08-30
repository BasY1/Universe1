/*!
 * \file qt/widgets/simulationeditor/widgetsimulationeditorview.h
 * \author Michal Steller
 * \brief Simulation editor Open GL view class declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITORVIEW_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITORVIEW_H

#include "../../opengl/glwidget.h"
#include "../../opengl/models/modelarrow.h"
#include "../../opengl/models/modeldots.h"
#include "../../opengl/models/modelpath.h"
#include "../../opengl/models/modelpointlight.h"
#include "../../opengl/models/modelsingularity.h"
#include "../../opengl/models/modelsphere.h"
#include "../../opengl/models/modelspinarrow.h"
#include "../../opengl/models/modelspotlight.h"

#include "../../project/qsimulation.h"
#include <set>

namespace Universe1 {
namespace Widgets {
namespace SimulationEditor {

/*!
 * \brief Simulation QT Open GL widget
 */
class WidgetSimulationEditorView : public OpenGL::GLWidget
{
    Q_OBJECT
 public:
    WidgetSimulationEditorView(
        const Project::QSimulation *_simulation,
        const std::pair<QVector3D, QVector3D> *_sceneRange,
        const std::vector<std::vector<std::pair<double, QVector3D>>> *_pathData,
        const std::vector<QVector3D> *_currentTimePositionsData,
        const std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>>
            *_currentTimePropertyData,
        const std::map<Project::QSimulation::ElementProperty, float> *_currentTimePropertyMaxLength,
        QWidget *_parent = nullptr);
    ~WidgetSimulationEditorView();

    inline bool isObserver1() const;
    inline bool isObserver2() const;
    inline bool showAxis() const;
    inline bool showDots() const;
    inline bool showPathAll() const;
    inline bool showPathSelected() const;
    inline double currentTime() const;
    inline Project::QSimulation::ElementProperties propertyAll() const;
    inline Project::QSimulation::ElementProperties propertySelected() const;
    inline const std::set<size_t> &selected() const;

    size_t memoryUsage() const override;

 public slots:
    void setPointLight(int _idx, const OpenGL::PointLight &_pointLight) override;
    void setSpotLight(int _idx, const OpenGL::SpotLight &_spotLight) override;

    void setShowAxis(bool _value);
    void setShowDots(bool _value);
    void setShowPathAll(bool _value);
    void setShowPathSelected(bool _value);

    void setPropertyAll(const Project::QSimulation::ElementProperties _value);
    void setPropertySelected(const Project::QSimulation::ElementProperties _value);

    void setCurrentTime(double _value);

    void rebuildSimulation();

 public:
    void setObserver1(const QVector3D &_position, const std::vector<std::pair<double, QVector3D>> &_objectData);
    void setObserver2(const QVector3D &_position, const std::vector<std::pair<double, QVector3D>> &_objectData);

    void hideObserver1();
    void hideObserver2();

    void setSelected(const std::set<size_t> &_value);

 protected:
    void initializeGLImpl() override;
    void paintGLImpl() override;

    void mouseDoubleClickEvent(QMouseEvent *_event) override;

    void clearSimulDataGL();

    void build();

    template <typename ARROW>
    void addVectors(std::vector<OpenGL::Models::GLModel *> &_outAll,
                    std::vector<OpenGL::Models::GLModel *> &_outSel,
                    const std::vector<std::pair<double, QVector3D>> &_propData,
                    const float propRange,
                    const OpenGL::Material &_materialLine,
                    const OpenGL::Material &_materialBottom,
                    const float _ratioRadiusLineAll,
                    const float _ratioRadiusHeaderAll,
                    const float _ratioLengthHeaderAll,
                    const float _ratioRadiusLineSelected,
                    const float _ratioRadiusHeaderSelected);
 signals:

    /*!
     * \brief Selection change request - item double-clicked
     * \param _objectIndex New selected object index
     */
    void selectionChangeRequest(uint _objectIndex);

    /*!
     * \brief Selection insert request - item double-clicked with CTRL down
     * \param _objectIndex New selected object index
     */
    void selectionInsertRequest(uint _objectIndex);

    /*!
     * \brief Clear selection request - item double-clicked (right mouse button)
     */
    void selectionClearRequest();

 protected:
    const Project::QSimulation *m_simulation;  //!< Processing simulation

    const std::pair<QVector3D, QVector3D> *m_sceneRange;  //!< Simulation scene range from all objects paths

    const std::vector<std::vector<std::pair<double, QVector3D>>> *m_pathData;  //!< Object's path data

    const std::vector<QVector3D> *m_currentTimePositionsData;  //!< Object's positions at current time

    const std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>>
        *m_currentTimePropertyData;  //!< Object's Properties at current time

    const std::map<Project::QSimulation::ElementProperty, float>
        *m_currentTimePropertyMaxLength;  //!< Maximum length of current vector property

    bool m_isObserver1;  //!< Observer 1 enabled flag
    bool m_isObserver2;  //!< Observer 2 enabled flag

    bool m_showAxis;  //!< Show axis flag
    bool m_showDots;  //!< Show dots flag (in X-Y plane)

    bool m_showPathAll;       //!< Show objects path flag
    bool m_showPathSelected;  //!< Show selected objects path flag

    double m_currentTime;  //!< Current timestamp in simulation

    Project::QSimulation::ElementProperties m_propertyAll;       //!< Visible objects properties
    Project::QSimulation::ElementProperties m_propertySelected;  //!< Visible selected objects properties

    std::set<size_t> m_selected;  //!< Selected objects

    OpenGL::Models::ModelArrow *m_axisX;  //!< Axis X model
    OpenGL::Models::ModelArrow *m_axisY;  //!< Axis Y model
    OpenGL::Models::ModelArrow *m_axisZ;  //!< Axis Z model
    OpenGL::Models::ModelDots *m_dotsXY;  //!< Plane XY dots model

    OpenGL::Models::ModelSingularity *m_observer1;  //!< Model for observer 1 position
    OpenGL::Models::ModelSingularity *m_observer2;  //!< Model for observer 2 position

    std::vector<OpenGL::Models::ModelSingularity *> m_observer1Sources;  //!< Models for sources for observer 1
    std::vector<OpenGL::Models::ModelSingularity *> m_observer2Sources;  //!< Models for sources for observer 2

    std::vector<OpenGL::Models::ModelPath *> m_objectPath;         //!< Object's path
    std::vector<OpenGL::Models::GLModel *> m_currentTimeAll;       //!< Object's current time model
    std::vector<OpenGL::Models::GLModel *> m_currentTimeSelected;  //!< Selected object's current time model

    std::unordered_map<Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>>
        m_modelsAll;  //!< Models for object properties at current time
    std::unordered_map<Project::QSimulation::ElementProperty, std::vector<OpenGL::Models::GLModel *>>
        m_modelsSelected;  //!< Models for selected object properties at current time

    std::vector<OpenGL::Models::ModelPointLight *> m_pointLightModels;  //!< Scene point light models
    std::vector<OpenGL::Models::ModelSpotLight *> m_spotLightModels;    //!< Scene spot light models
};

/*!
 * \brief Getter for observer 1 enabled flag
 * \returns Observer 1 enabled flag
 */
inline bool WidgetSimulationEditorView::isObserver1() const
{
    return m_isObserver1;
}

/*!
 * \brief Getter for observer 2 enabled flag
 * \returns Observer 2 enabled flag
 */
inline bool WidgetSimulationEditorView::isObserver2() const
{
    return m_isObserver2;
}

/*!
 * \brief Getter for show axis flag
 * \returns Show axis flag
 */
inline bool WidgetSimulationEditorView::showAxis() const
{
    return m_showAxis;
}

/*!
 * \brief Getter for show dots flag
 * \returns Show dots flag
 */
inline bool WidgetSimulationEditorView::showDots() const
{
    return m_showDots;
}

/*!
 * \brief Getter for show objects path flag
 * \returns Show objects path flag
 */
inline bool WidgetSimulationEditorView::showPathAll() const
{
    return m_showPathAll;
}

/*!
 * \brief Getter for show selected objects path flag
 * \returns Show selected objects path flag
 */
inline bool WidgetSimulationEditorView::showPathSelected() const
{
    return m_showPathSelected;
}

/*!
 * \brief Getter for current time
 * \returns Current time
 */
inline double WidgetSimulationEditorView::currentTime() const
{
    return m_currentTime;
}

/*!
 * \brief Getter for visible object properties
 * \returns Visible object properties
 */
inline Project::QSimulation::ElementProperties WidgetSimulationEditorView::propertyAll() const
{
    return m_propertyAll;
}

/*!
 * \brief Getter for visible selected object properties
 * \returns Visible selected object properties
 */
inline Project::QSimulation::ElementProperties WidgetSimulationEditorView::propertySelected() const
{
    return m_propertySelected;
}

/*!
 * \brief Getter for selected object IDs
 * \returns Selected object IDs
 */
inline const std::set<size_t> &WidgetSimulationEditorView::selected() const
{
    return m_selected;
}

/*!
 * \brief Prepare object property arrow
 * \tparam ARROW Arrow model class
 * \param _outAll Output all models collection for pushing
 * \param _outSel Output selected models collection for pushing
 * \param _propData Data property values
 * \param _propRange Maximum property length
 * \param _materialLine Material for arrow line
 * \param _materialBottom Material for arrow bottom
 * \param _ratioRadiusLineAll Arrow line radius
 * \param _ratioRadiusHeaderAll Arrow header radius
 * \param _ratioLengthHeaderAll Arrow header length
 * \param _ratioRadiusLineSelected Selected object arrow line radius
 * \param _ratioRadiusHeaderSelected Selected object arrow header radius
 */
template <typename ARROW>
void WidgetSimulationEditorView::addVectors(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                            std::vector<OpenGL::Models::GLModel *> &_outSel,
                                            const std::vector<std::pair<double, QVector3D>> &_propData,
                                            const float _propRange,
                                            const OpenGL::Material &_materialLine,
                                            const OpenGL::Material &_materialBottom,
                                            const float _ratioRadiusLineAll,
                                            const float _ratioRadiusHeaderAll,
                                            const float _ratioLengthHeaderAll,
                                            const float _ratioRadiusLineSelected,
                                            const float _ratioRadiusHeaderSelected)
{
    const OpenGL::Material materialLineDark = _materialLine.darker();
    const OpenGL::Material materialBottomDark = _materialBottom.darker();

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_pathData->size(); ++i)
        {
            const QVector3D fromPos =
                m_currentTimePositionsData->at(i) + (m_simulation->usesRadius() ? 1.05F : 0.05F) * _propData[i].second;
            const QVector3D toPos =
                m_currentTimePositionsData->at(i) + (m_simulation->usesRadius() ? 2.05F : 1.05F) * _propData[i].second;

            ARROW *arrowAll = new ARROW(materialLineDark,
                                        OpenGL::Material::materialGreen,
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll);

            ARROW *arrowSel = new ARROW(_materialLine,
                                        OpenGL::Material::materialGreenLight,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll);
            arrowAll->initGL();
            arrowSel->initGL();
            _outAll.push_back(arrowAll);
            _outSel.push_back(arrowSel);
        }
    }
    else
    {
        for (size_t i = 0U; i < m_pathData->size(); ++i)
        {
            const QVector3D fromPos =
                m_currentTimePositionsData->at(i) + (m_simulation->usesRadius() ? 1.05F : 0.05F) * _propData[i].second;
            const QVector3D toPos =
                m_currentTimePositionsData->at(i) + (m_simulation->usesRadius() ? 2.05F : 1.05F) * _propData[i].second;

            const float valueRatio = _propData[i].second.length() / _propRange;
            const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);

            ARROW *arrowAll = new ARROW(materialLineDark,
                                        material.darker(),
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll);
            ARROW *arrowSel = new ARROW(_materialLine,
                                        material,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll);
            arrowAll->initGL();
            arrowSel->initGL();
            _outAll.push_back(arrowAll);
            _outSel.push_back(arrowSel);
        }
    }
}

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITORVIEW_H
