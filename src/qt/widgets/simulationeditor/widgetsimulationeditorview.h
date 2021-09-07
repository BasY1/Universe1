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
        const std::vector<std::vector<std::pair<double, QVector3D>>> *_path1Data,
        const std::vector<std::vector<std::vector<std::pair<double, QVector3D>>>> *_path2Data,
        const std::vector<std::vector<std::vector<std::pair<double, QVector3D>>>> *_path3Data,
        const std::vector<std::pair<bool, QVector3D>> *_currentTimePositions1Data,
        const std::vector<std::pair<bool, QVector3D>> *_currentTimePositions2Data,
        const std::vector<std::pair<bool, QVector3D>> *_currentTimePositions3Data,
        const std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<bool, QVector3D>>>
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
                    const std::vector<std::pair<bool, QVector3D>> &_propData,
                    const float propRange,
                    const OpenGL::Material &_materialLine,
                    const OpenGL::Material &_materialBottom,
                    const float _ratioRadiusLineAll,
                    const float _ratioRadiusHeaderAll,
                    const float _ratioLengthHeaderAll,
                    const float _ratioRadiusLineSelected,
                    const float _ratioRadiusHeaderSelected);

    template <typename ARROW>
    void addVectors2(std::vector<OpenGL::Models::GLModel *> &_outAll,
                     std::vector<OpenGL::Models::GLModel *> &_outSel,
                     const std::vector<std::pair<bool, QVector3D>> &_propData,
                     const float propRange,
                     const OpenGL::Material &_materialLine,
                     const OpenGL::Material &_materialBottom,
                     const float _ratioRadiusLineAll,
                     const float _ratioRadiusHeaderAll,
                     const float _ratioLengthHeaderAll,
                     const float _ratioRadiusLineSelected,
                     const float _ratioRadiusHeaderSelected);

    template <typename ARROW>
    void addVectors3(std::vector<OpenGL::Models::GLModel *> &_outAll,
                     std::vector<OpenGL::Models::GLModel *> &_outSel,
                     const std::vector<std::pair<bool, QVector3D>> &_propData,
                     const float propRange,
                     const OpenGL::Material &_materialLine,
                     const OpenGL::Material &_materialBottom,
                     const float _ratioRadiusLineAll,
                     const float _ratioRadiusHeaderAll,
                     const float _ratioLengthHeaderAll,
                     const float _ratioRadiusLineSelected,
                     const float _ratioRadiusHeaderSelected);

    template <typename ARROW>
    void addFixedVectors(std::vector<OpenGL::Models::GLModel *> &_outAll,
                         std::vector<OpenGL::Models::GLModel *> &_outSel,
                         const std::vector<std::pair<bool, QVector3D>> &_propData,
                         const float propRange,
                         const OpenGL::Material &_materialLine,
                         const OpenGL::Material &_materialBottom,
                         const float _fixedLengthAll,
                         const float _ratioRadiusLineAll,
                         const float _ratioRadiusHeaderAll,
                         const float _ratioLengthHeaderAll,
                         const float _ratioRadiusLineSelected,
                         const float _ratioRadiusHeaderSelected);

    template <typename ARROW>
    void addFixedVectors2(std::vector<OpenGL::Models::GLModel *> &_outAll,
                          std::vector<OpenGL::Models::GLModel *> &_outSel,
                          const std::vector<std::pair<bool, QVector3D>> &_propData,
                          const float propRange,
                          const OpenGL::Material &_materialLine,
                          const OpenGL::Material &_materialBottom,
                          const float _fixedLengthAll,
                          const float _ratioRadiusLineAll,
                          const float _ratioRadiusHeaderAll,
                          const float _ratioLengthHeaderAll,
                          const float _ratioRadiusLineSelected,
                          const float _ratioRadiusHeaderSelected);

    template <typename ARROW>
    void addFixedVectors3(std::vector<OpenGL::Models::GLModel *> &_outAll,
                          std::vector<OpenGL::Models::GLModel *> &_outSel,
                          const std::vector<std::pair<bool, QVector3D>> &_propData,
                          const float propRange,
                          const OpenGL::Material &_materialLine,
                          const OpenGL::Material &_materialBottom,
                          const float _fixedLengthAll,
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

    const std::vector<std::vector<std::pair<double, QVector3D>>> *m_path1Data;               //!< Object's path data
    const std::vector<std::vector<std::vector<std::pair<double, QVector3D>>>> *m_path2Data;  //!< Generation 2 path data
    const std::vector<std::vector<std::vector<std::pair<double, QVector3D>>>> *m_path3Data;  //!< Generation 3 path data

    const std::vector<std::pair<bool, QVector3D>> *m_currentTimePositions1Data;  //!< Object's positions at current time
    const std::vector<std::pair<bool, QVector3D>>
        *m_currentTimePositions2Data;  //!< Generation 2 positions at current time
    const std::vector<std::pair<bool, QVector3D>>
        *m_currentTimePositions3Data;  //!< Generation 3 positions at current time

    const std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<bool, QVector3D>>>
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
 * \brief Tool function push arrows into collection
 * \param _outAll Output all models collection for pushing
 * \param _outSel Output selected models collection for pushing
 * \param _arrowAll Arrow for all models
 * \param _arrowSel Arrow for selected models
 */
inline void pushModel(std::vector<OpenGL::Models::GLModel *> &_outAll,
                      std::vector<OpenGL::Models::GLModel *> &_outSel,
                      OpenGL::Models::GLModel *_arrowAll,
                      OpenGL::Models::GLModel *_arrowSel)
{
    _arrowAll->initGL();
    _arrowSel->initGL();
    _outAll.push_back(_arrowAll);
    _outSel.push_back(_arrowSel);
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
                                            const std::vector<std::pair<bool, QVector3D>> &_propData,
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

    static const float offset = 0.05F;
    const float elRadius = m_simulation->usesRadius() ? m_simulation->getConstantElementRadius() : 0.0F;

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            const std::pair<bool, QVector3D> &pos = m_currentTimePositions1Data->at(i);
            if (pos.first && _propData[i].first)
            {
                const QVector3D fromPos = pos.second + (elRadius + offset) * _propData[i].second.normalized();
                const QVector3D toPos = fromPos + _propData[i].second;
                pushModel(_outAll,
                          _outSel,
                          new ARROW(materialLineDark,
                                    OpenGL::Material::materialGreen,
                                    materialBottomDark,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineAll,
                                    _ratioRadiusHeaderAll,
                                    _ratioLengthHeaderAll),

                          new ARROW(_materialLine,
                                    OpenGL::Material::materialGreenLight,
                                    _materialBottom,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineSelected,
                                    _ratioRadiusHeaderSelected,
                                    _ratioLengthHeaderAll));
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            const std::pair<bool, QVector3D> &pos = m_currentTimePositions1Data->at(i);
            if (pos.first && _propData[i].first)
            {
                const QVector3D fromPos = pos.second + (elRadius + offset) * _propData[i].second.normalized();
                const QVector3D toPos = fromPos + _propData[i].second;
                const float valueRatio = _propData[i].second.length() / _propRange;
                const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                pushModel(_outAll,
                          _outSel,
                          new ARROW(materialLineDark,
                                    material.darker(),
                                    materialBottomDark,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineAll,
                                    _ratioRadiusHeaderAll,
                                    _ratioLengthHeaderAll),
                          new ARROW(_materialLine,
                                    material,
                                    _materialBottom,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineSelected,
                                    _ratioRadiusHeaderSelected,
                                    _ratioLengthHeaderAll));
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
}

/*!
 * \brief Prepare object property arrow - generation 2
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
void WidgetSimulationEditorView::addVectors2(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                             std::vector<OpenGL::Models::GLModel *> &_outSel,
                                             const std::vector<std::pair<bool, QVector3D>> &_propData,
                                             const float _propRange,
                                             const OpenGL::Material &_materialLine,
                                             const OpenGL::Material &_materialBottom,
                                             const float _ratioRadiusLineAll,
                                             const float _ratioRadiusHeaderAll,
                                             const float _ratioLengthHeaderAll,
                                             const float _ratioRadiusLineSelected,
                                             const float _ratioRadiusHeaderSelected)
{
    static const float offset = 0.05F;
    const float elRadius = m_simulation->getConstantElementRadius();
    const OpenGL::Material materialLineDark = _materialLine.darker();
    const OpenGL::Material materialBottomDark = _materialBottom.darker();

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                if (pos1.first && pos2.first)
                {
                    const float g2Radius = elRadius - (pos1.second.distanceToPoint(pos2.second));
                    const QVector3D fromPos = pos2.second + (g2Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second;
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        OpenGL::Material::materialGreen,
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        OpenGL::Material::materialGreenLight,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                if (pos1.first && pos2.first)
                {
                    const float g2Radius = elRadius - (pos1.second.distanceToPoint(pos2.second));
                    const QVector3D fromPos = pos2.second + (g2Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second;
                    const float valueRatio = _propData[i].second.length() / _propRange;
                    const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        material.darker(),
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        material,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
}

/*!
 * \brief Prepare object property arrow - generation 3
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
void WidgetSimulationEditorView::addVectors3(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                             std::vector<OpenGL::Models::GLModel *> &_outSel,
                                             const std::vector<std::pair<bool, QVector3D>> &_propData,
                                             const float _propRange,
                                             const OpenGL::Material &_materialLine,
                                             const OpenGL::Material &_materialBottom,
                                             const float _ratioRadiusLineAll,
                                             const float _ratioRadiusHeaderAll,
                                             const float _ratioLengthHeaderAll,
                                             const float _ratioRadiusLineSelected,
                                             const float _ratioRadiusHeaderSelected)
{
    static const float offset = 0.05F;
    const float elRadius = m_simulation->getConstantElementRadius();
    const OpenGL::Material materialLineDark = _materialLine.darker();
    const OpenGL::Material materialBottomDark = _materialBottom.darker();

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                const std::pair<bool, QVector3D> &pos3 = m_currentTimePositions3Data->at(i);
                if (pos1.first && pos2.first && pos3.first)
                {
                    const float g3Radius = elRadius - (pos1.second.distanceToPoint(pos2.second)) -
                        pos2.second.distanceToPoint(pos3.second);
                    const QVector3D fromPos = pos3.second + (g3Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second;
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        OpenGL::Material::materialGreen,
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        OpenGL::Material::materialGreenLight,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                const std::pair<bool, QVector3D> &pos3 = m_currentTimePositions3Data->at(i);
                if (pos1.first && pos2.first && pos3.first)
                {
                    const float g3Radius = elRadius - (pos1.second.distanceToPoint(pos2.second)) -
                        pos2.second.distanceToPoint(pos3.second);
                    const QVector3D fromPos = pos3.second + (g3Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second;
                    const float valueRatio = _propData[i].second.length() / _propRange;
                    const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        material.darker(),
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        material,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
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
 * \param _fixedLengthAll Length of all arrows
 * \param _ratioRadiusLineAll Arrow line radius
 * \param _ratioRadiusHeaderAll Arrow header radius
 * \param _ratioLengthHeaderAll Arrow header length
 * \param _ratioRadiusLineSelected Selected object arrow line radius
 * \param _ratioRadiusHeaderSelected Selected object arrow header radius
 */
template <typename ARROW>
void WidgetSimulationEditorView::addFixedVectors(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                                 std::vector<OpenGL::Models::GLModel *> &_outSel,
                                                 const std::vector<std::pair<bool, QVector3D>> &_propData,
                                                 const float _propRange,
                                                 const OpenGL::Material &_materialLine,
                                                 const OpenGL::Material &_materialBottom,
                                                 const float _fixedLengthAll,
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
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            const std::pair<bool, QVector3D> &pos = m_currentTimePositions1Data->at(i);
            if (pos.first && _propData[i].first)
            {
                const QVector3D &value = _propData[i].second;
                const QVector3D fromPos = pos.second + value * (m_simulation->usesRadius() ? 1.05F : 0.05F);
                const QVector3D toPos = fromPos + value.normalized() * _fixedLengthAll;
                pushModel(_outAll,
                          _outSel,
                          new ARROW(materialLineDark,
                                    OpenGL::Material::materialGreen,
                                    materialBottomDark,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineAll,
                                    _ratioRadiusHeaderAll,
                                    _ratioLengthHeaderAll),
                          new ARROW(_materialLine,
                                    OpenGL::Material::materialGreenLight,
                                    _materialBottom,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineSelected,
                                    _ratioRadiusHeaderSelected,
                                    _ratioLengthHeaderAll));
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            const std::pair<bool, QVector3D> &pos = m_currentTimePositions1Data->at(i);
            if (pos.first && _propData[i].first)
            {
                const QVector3D &value = _propData[i].second;
                const QVector3D fromPos = pos.second + value * (m_simulation->usesRadius() ? 1.05F : 0.05F);
                const QVector3D toPos = fromPos + value.normalized() * _fixedLengthAll;
                const float valueRatio = value.length() / _propRange;
                const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                pushModel(_outAll,
                          _outSel,
                          new ARROW(materialLineDark,
                                    material.darker(),
                                    materialBottomDark,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineAll,
                                    _ratioRadiusHeaderAll,
                                    _ratioLengthHeaderAll),
                          new ARROW(_materialLine,
                                    material,
                                    _materialBottom,
                                    fromPos,
                                    toPos,
                                    _ratioRadiusLineSelected,
                                    _ratioRadiusHeaderSelected,
                                    _ratioLengthHeaderAll));
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
}

/*!
 * \brief Prepare object property arrow - generation 2
 * \tparam ARROW Arrow model class
 * \param _outAll Output all models collection for pushing
 * \param _outSel Output selected models collection for pushing
 * \param _propData Data property values
 * \param _propRange Maximum property length
 * \param _materialLine Material for arrow line
 * \param _materialBottom Material for arrow bottom
 * \param _fixedLengthAll Length of all arrows
 * \param _ratioRadiusLineAll Arrow line radius
 * \param _ratioRadiusHeaderAll Arrow header radius
 * \param _ratioLengthHeaderAll Arrow header length
 * \param _ratioRadiusLineSelected Selected object arrow line radius
 * \param _ratioRadiusHeaderSelected Selected object arrow header radius
 */
template <typename ARROW>
void WidgetSimulationEditorView::addFixedVectors2(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                                  std::vector<OpenGL::Models::GLModel *> &_outSel,
                                                  const std::vector<std::pair<bool, QVector3D>> &_propData,
                                                  const float _propRange,
                                                  const OpenGL::Material &_materialLine,
                                                  const OpenGL::Material &_materialBottom,
                                                  const float _fixedLengthAll,
                                                  const float _ratioRadiusLineAll,
                                                  const float _ratioRadiusHeaderAll,
                                                  const float _ratioLengthHeaderAll,
                                                  const float _ratioRadiusLineSelected,
                                                  const float _ratioRadiusHeaderSelected)
{
    static const float offset = 0.05F;
    const float elRadius = m_simulation->getConstantElementRadius();
    const OpenGL::Material materialLineDark = _materialLine.darker();
    const OpenGL::Material materialBottomDark = _materialBottom.darker();

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                if (pos1.first && pos2.first)
                {
                    const float g2Radius = elRadius - (pos1.second.distanceToPoint(pos2.second));
                    const QVector3D fromPos = pos2.second + (g2Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second.normalized() * _fixedLengthAll;
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        OpenGL::Material::materialGreen,
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        OpenGL::Material::materialGreenLight,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                if (pos1.first && pos2.first)
                {
                    const float g2Radius = elRadius - (pos1.second.distanceToPoint(pos2.second));
                    const QVector3D fromPos = pos2.second + (g2Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second.normalized() * _fixedLengthAll;
                    const float valueRatio = _propData[i].second.length() / _propRange;
                    const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        material.darker(),
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        material,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
}

/*!
 * \brief Prepare object property arrow - generation 3
 * \tparam ARROW Arrow model class
 * \param _outAll Output all models collection for pushing
 * \param _outSel Output selected models collection for pushing
 * \param _propData Data property values
 * \param _propRange Maximum property length
 * \param _materialLine Material for arrow line
 * \param _materialBottom Material for arrow bottom
 * \param _fixedLengthAll Length of all arrows
 * \param _ratioRadiusLineAll Arrow line radius
 * \param _ratioRadiusHeaderAll Arrow header radius
 * \param _ratioLengthHeaderAll Arrow header length
 * \param _ratioRadiusLineSelected Selected object arrow line radius
 * \param _ratioRadiusHeaderSelected Selected object arrow header radius
 */
template <typename ARROW>
void WidgetSimulationEditorView::addFixedVectors3(std::vector<OpenGL::Models::GLModel *> &_outAll,
                                                  std::vector<OpenGL::Models::GLModel *> &_outSel,
                                                  const std::vector<std::pair<bool, QVector3D>> &_propData,
                                                  const float _propRange,
                                                  const OpenGL::Material &_materialLine,
                                                  const OpenGL::Material &_materialBottom,
                                                  const float _fixedLengthAll,
                                                  const float _ratioRadiusLineAll,
                                                  const float _ratioRadiusHeaderAll,
                                                  const float _ratioLengthHeaderAll,
                                                  const float _ratioRadiusLineSelected,
                                                  const float _ratioRadiusHeaderSelected)
{
    static const float offset = 0.05F;
    const float elRadius = m_simulation->getConstantElementRadius();
    const OpenGL::Material materialLineDark = _materialLine.darker();
    const OpenGL::Material materialBottomDark = _materialBottom.darker();

    if (qFuzzyIsNull(_propRange))
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                const std::pair<bool, QVector3D> &pos3 = m_currentTimePositions3Data->at(i);
                if (pos1.first && pos2.first && pos3.first)
                {
                    const float g3Radius = elRadius - (pos1.second.distanceToPoint(pos2.second)) -
                        pos2.second.distanceToPoint(pos3.second);
                    const QVector3D fromPos = pos3.second + (g3Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second.normalized() * _fixedLengthAll;
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        OpenGL::Material::materialGreen,
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        OpenGL::Material::materialGreenLight,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
    else
    {
        for (size_t i = 0U; i < m_path1Data->size(); ++i)
        {
            if (_propData[i].first)
            {
                const std::pair<bool, QVector3D> &pos1 = m_currentTimePositions1Data->at(i);
                const std::pair<bool, QVector3D> &pos2 = m_currentTimePositions2Data->at(i);
                const std::pair<bool, QVector3D> &pos3 = m_currentTimePositions3Data->at(i);
                if (pos1.first && pos2.first && pos3.first)
                {
                    const float g3Radius = elRadius - (pos1.second.distanceToPoint(pos2.second)) -
                        pos2.second.distanceToPoint(pos3.second);
                    const QVector3D fromPos = pos3.second + (g3Radius + offset) * _propData[i].second.normalized();
                    const QVector3D toPos = fromPos + _propData[i].second.normalized() * _fixedLengthAll;
                    const float valueRatio = _propData[i].second.length() / _propRange;
                    const OpenGL::Material material = OpenGL::Material::ratioGreenRed(valueRatio);
                    pushModel(_outAll,
                              _outSel,
                              new ARROW(materialLineDark,
                                        material.darker(),
                                        materialBottomDark,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineAll,
                                        _ratioRadiusHeaderAll,
                                        _ratioLengthHeaderAll),
                              new ARROW(_materialLine,
                                        material,
                                        _materialBottom,
                                        fromPos,
                                        toPos,
                                        _ratioRadiusLineSelected,
                                        _ratioRadiusHeaderSelected,
                                        _ratioLengthHeaderAll));
                }
                else
                {
                    _outAll.push_back(nullptr);
                    _outSel.push_back(nullptr);
                }
            }
            else
            {
                _outAll.push_back(nullptr);
                _outSel.push_back(nullptr);
            }
        }
    }
}

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITORVIEW_H
