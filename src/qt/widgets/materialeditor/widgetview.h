/*!
 * \file qt/widgets/materialeditor/widgetview.h
 * \author Michal Steller
 * \brief Material editor Open GL view class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H

#include "../../opengl/glwidget.h"
#include "../../opengl/lights.h"
#include "../../opengl/models/trianglemodel.h"

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Base QT Open GL widget
 */
class WidgetView : public OpenGL::GLWidget
{
    Q_OBJECT
 public:
    WidgetView(const OpenGL::Material &_material, QWidget *parent = nullptr);
    ~WidgetView();

    inline OpenGL::Models::TriangleModel *modelTriangle();

    inline const OpenGL::DirectionLight &directionLight() const;
    inline const std::vector<OpenGL::PointLight> &pointLights() const;

    size_t memoryUsage() const override;

 public slots:
    void setModel(int _modelIndex);
    void setDirectionLight(const OpenGL::DirectionLight &_directionLight);
    void setPointLight(int _idx, const OpenGL::PointLight &_pointLight);

 protected:
    void mouseDoubleClickEvent(QMouseEvent *_event) override;

    void initializeGLImpl() override;
    void paintGLImpl() override;

 protected:
    OpenGL::Models::TriangleModel *m_modelTriangle;  //!< Triangle Open GL model

    std::vector<OpenGL::Models::GLModel *> m_models;  //!< Open GL Model collection
    int m_currentModel;                               //!< Current Open GL model index

    OpenGL::DirectionLight m_directionLight;        //!< Scene directional light
    std::vector<OpenGL::PointLight> m_pointLights;  //!< Scene point lights
};

/*!
 * \brief Getter for triangle Open GL model
 * \return Triangle Open GL model
 */
inline OpenGL::Models::TriangleModel *WidgetView::modelTriangle()
{
    return m_modelTriangle;
}

/*!
 * \brief Getter for scene directional light
 * \return Scene directional light
 */
inline const OpenGL::DirectionLight &WidgetView::directionLight() const
{
    return m_directionLight;
}

/*!
 * \brief Getter for scene point lights collection
 * \return Scene point lights
 */
inline const std::vector<OpenGL::PointLight> &WidgetView::pointLights() const
{
    return m_pointLights;
}

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H
