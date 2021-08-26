/*!
 * \file qt/widgets/materialeditor/widgetview.h
 * \author Michal Steller
 * \brief Material editor Open GL view class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H

#include "../../opengl/glwidget.h"
#include "../../opengl/lights.h"
#include "../../opengl/models/modelarrow.h"
#include "../../opengl/models/modelbox.h"
#include "../../opengl/models/modelcylinder.h"
#include "../../opengl/models/modelplane.h"
#include "../../opengl/models/modelpointlight.h"
#include "../../opengl/models/modelsphere.h"
#include "../../opengl/models/modelspotlight.h"
#include "../../opengl/models/modeltorus.h"
#include "../../opengl/models/modeltriangle.h"

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

    inline OpenGL::Models::ModelSphere *modelSphere();
    inline OpenGL::Models::ModelCylinder *modelCylinder();
    inline OpenGL::Models::ModelTorus *modelTorus();
    inline OpenGL::Models::ModelBox *modelBox();
    inline OpenGL::Models::ModelArrow *modelArrow();
    inline OpenGL::Models::ModelTriangle *modelTriangle();
    inline OpenGL::Models::ModelPlane *modelPlane();
    inline int currentModel() const;

    size_t memoryUsage() const override;

 public slots:
    void setPointLight(int _idx, const OpenGL::PointLight &_pointLight) override;
    void setSpotLight(int _idx, const OpenGL::SpotLight &_spotLight) override;

    void setCurrentModel(int _modelIndex);
    void setMaterial(const OpenGL::Material &_material);

    void sphereWireFrameChanged(bool _value);
    void sphereEquatorPointCountChanged(int _value);

    void cylinderWireFrameChanged(bool _value);
    void cylinderEquatorPointCountChanged(int _value);

    void torusWireFrameChanged(bool _value);
    void torusCirclePointCountChanged(int _value);

    void boxWireFrameChanged(bool _value);
    void boxNormalSetupChanged(OpenGL::Models::ModelBox::NormalSetup _value);
    void boxBoxSize1Changed(float _value);
    void boxBoxSize2Changed(float _value);
    void boxBoxSize3Changed(float _value);

    void arrowWireFrameChanged(bool _value);
    void arrowCirclePointCountChanged(int _value);
    void arrowMaterialLineChanged(const OpenGL::Material &_value);
    void arrowMaterialBottomChanged(const OpenGL::Material &_value);

    void triangleWireFrameChanged(bool _value);
    void triangleCcwChanged(bool _value);
    void triangleNormal1Changed(const QVector3D &_value);
    void triangleNormal2Changed(const QVector3D &_value);
    void triangleNormal3Changed(const QVector3D &_value);

    void planeWireFrameChanged(bool _value);
    void planeNormal1Changed(const QVector3D &_value);
    void planeNormal2Changed(const QVector3D &_value);
    void planeDots1Changed(int _value);
    void planeDots2Changed(int _value);

 protected:
    void mouseDoubleClickEvent(QMouseEvent *_event) override;

    void initializeGLImpl() override;
    void paintGLImpl() override;

 protected:
    OpenGL::Models::ModelSphere *m_modelSphere;      //!< Sphere Open GL model
    OpenGL::Models::ModelCylinder *m_modelCylinder;  //!< Cylinder Open GL model
    OpenGL::Models::ModelTorus *m_modelTorus;        //!< Torus Open GL model
    OpenGL::Models::ModelBox *m_modelBox;            //!< Box Open GL model
    OpenGL::Models::ModelArrow *m_modelArrow;        //!< Arrow Open GL model
    OpenGL::Models::ModelTriangle *m_modelTriangle;  //!< Triangle Open GL model
    OpenGL::Models::ModelPlane *m_modelPlane;        //!< Plane Open GL model

    std::vector<OpenGL::Models::GLModel *> m_models;  //!< Open GL Model collection
    int m_currentModel;                               //!< Current Open GL model index

    std::vector<OpenGL::Models::ModelPointLight *> m_pointLightModels;  //!< Scene point light models
    std::vector<OpenGL::Models::ModelSpotLight *> m_spotLightModels;  //!< Scene spot light models
};

/*!
 * \brief Getter for triangle Open GL model
 * \returns Triangle Open GL model
 */
inline OpenGL::Models::ModelTriangle *WidgetView::modelTriangle()
{
    return m_modelTriangle;
}

/*!
 * \brief Getter for plane Open GL model
 * \returns Plane Open GL model
 */
inline OpenGL::Models::ModelPlane *WidgetView::modelPlane()
{
    return m_modelPlane;
}

/*!
 * \brief Getter for sphere Open GL model
 * \returns Sphere Open GL model
 */
inline OpenGL::Models::ModelSphere *WidgetView::modelSphere()
{
    return m_modelSphere;
}

/*!
 * \brief Getter for sphere Open GL model
 * \returns Cylinder Open GL model
 */
inline OpenGL::Models::ModelCylinder *WidgetView::modelCylinder()
{
    return m_modelCylinder;
}

/*!
 * \brief Getter for sphere Open GL model
 * \returns Torus Open GL model
 */
inline OpenGL::Models::ModelTorus *WidgetView::modelTorus()
{
    return m_modelTorus;
}

/*!
 * \brief Getter for box Open GL model
 * \returns Box Open GL model
 */
inline OpenGL::Models::ModelBox *WidgetView::modelBox()
{
    return m_modelBox;
}

/*!
 * \brief Getter for arrow Open GL model
 * \returns Arrow Open GL model
 */
inline OpenGL::Models::ModelArrow *WidgetView::modelArrow()
{
    return m_modelArrow;
}

/*!
 * \brief Getter for current Open GL model index
 * \returns Current Open GL model index
 */
inline int WidgetView::currentModel() const
{
    return m_currentModel;
}

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETVIEW_H
