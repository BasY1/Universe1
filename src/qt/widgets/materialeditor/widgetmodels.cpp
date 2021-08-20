/*!
 * \file qt/widgets/materialeditor/widgetmodels.cpp
 * \author Michal Steller
 * \brief Material editor - Models widget classes implementation
 */

#include "widgetmodels.h"

#include "../horizontallinespacer.h"

#include <QGridLayout>
#include <QLabel>

/*!
 * \brief Constructor
 * \param _model Triangle Open GL model
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::WidgetModelTriangle(OpenGL::Models::ModelTriangle *_model,
                                                                             QWidget *_parent)
    : QWidget(_parent)
    , m_model(_model)
    , m_wireFrame(new QCheckBox())
    , m_boxCWW(new QCheckBox())
    , m_guiNormal1(new GUI::GuiVector3D(m_model->normal1()))
    , m_guiNormal2(new GUI::GuiVector3D(m_model->normal2()))
    , m_guiNormal3(new GUI::GuiVector3D(m_model->normal3()))
{
    m_wireFrame->setChecked(m_model->drawWireFrame());
    m_boxCWW->setChecked(m_model->ccw());
    m_boxCWW->setToolTip(tr("Counter-clockwise point order"));

    connect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelTriangle::wireFrameChanged);
    connect(m_boxCWW, &QCheckBox::toggled, this, &WidgetModelTriangle::ccwChanged);
    connect(m_guiNormal1, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal1Changed);
    connect(m_guiNormal2, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal2Changed);
    connect(m_guiNormal3, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal3Changed);

    int row = 0;
    QGridLayout *lay = new QGridLayout();

    lay->addWidget(new QLabel(tr("Wire-frame")), row, 0, 1, 2);
    lay->addWidget(m_wireFrame, row++, 2, 1, 2);

    lay->addWidget(new QLabel(tr("Point order")), row, 0, 1, 2);
    lay->addWidget(m_boxCWW, row++, 2, 1, 2);

    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

    m_guiNormal1->layoutRow(tr("Normal 1"), lay, row);
    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);
    m_guiNormal2->layoutRow(tr("Normal 2"), lay, row);
    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);
    m_guiNormal3->layoutRow(tr("Normal 3"), lay, row);

    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 2);
    setLayout(lay);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::~WidgetModelTriangle()
{
    disconnect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelTriangle::wireFrameChanged);
    disconnect(m_boxCWW, &QCheckBox::toggled, this, &WidgetModelTriangle::ccwChanged);
    disconnect(m_guiNormal1, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal1Changed);
    disconnect(m_guiNormal2, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal2Changed);
    disconnect(m_guiNormal3, &GUI::GuiVector3D::changed, this, &WidgetModelTriangle::normal3Changed);

    delete m_guiNormal1;
    delete m_guiNormal2;
    delete m_guiNormal3;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _model Sphere Open GL model
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::WidgetModelSphere::WidgetModelSphere(OpenGL::Models::ModelSphere *_model,
                                                                         QWidget *_parent)
    : QWidget(_parent)
    , m_model(_model)
    , m_wireFrame(new QCheckBox())
    , m_equatorPointCount(new GUI::GuiInt(m_model->equatorPointCount(), 4, 1024, Qt::Horizontal))
{
    m_wireFrame->setChecked(m_model->drawWireFrame());

    connect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelSphere::wireFrameChanged);
    connect(m_equatorPointCount, &GUI::GuiInt::changed, this, &WidgetModelSphere::equatorPointCountChanged);

    QGridLayout *lay = new QGridLayout();
    int row = 0;
    lay->addWidget(new QLabel(tr("Wire-frame")), row, 0, 1, 2);
    lay->addWidget(m_wireFrame, row++, 2, 1, 2);

    m_equatorPointCount->layoutRow(tr("Equator point count"), lay, row);

    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);

    setLayout(lay);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetModelSphere::~WidgetModelSphere()
{
    disconnect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelSphere::wireFrameChanged);
    disconnect(m_equatorPointCount, &GUI::GuiInt::changed, this, &WidgetModelSphere::equatorPointCountChanged);

    delete m_equatorPointCount;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _model Plane Open GL model
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::WidgetModelPlane::WidgetModelPlane(OpenGL::Models::ModelPlane *_model,
                                                                       QWidget *_parent)
    : QWidget(_parent)
    , m_model(_model)
    , m_normal1(m_model->normal1())
    , m_normal2(m_model->normal2())
    , m_wireFrame(new QCheckBox())
    , m_normal1X(new GUI::GuiFloat(m_model->normal1().x(), -2, 2, 3, Qt::Horizontal))
    , m_normal2Z(new GUI::GuiFloat(m_model->normal2().z(), -2, 2, 3, Qt::Horizontal))
    , m_dots1Count(new GUI::GuiInt(m_model->dots1(), 0, 32, Qt::Horizontal))
    , m_dots2Count(new GUI::GuiInt(m_model->dots2(), 0, 32, Qt::Horizontal))
{
    m_wireFrame->setChecked(m_model->drawWireFrame());

    connect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelPlane::wireFrameChanged);
    connect(m_normal1X, &GUI::GuiFloat::changed, this, &WidgetModelPlane::normal1XChaged);
    connect(m_normal2Z, &GUI::GuiFloat::changed, this, &WidgetModelPlane::normal2ZChaged);
    connect(m_dots1Count, &GUI::GuiInt::changed, this, &WidgetModelPlane::dots1Changed);
    connect(m_dots2Count, &GUI::GuiInt::changed, this, &WidgetModelPlane::dots2Changed);

    QGridLayout *lay = new QGridLayout();
    int row = 0;
    lay->addWidget(new QLabel(tr("Wire-frame")), row, 0, 1, 2);
    lay->addWidget(m_wireFrame, row++, 2, 1, 2);

    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

    m_normal1X->layoutRow(tr("Normal 1 (X)"), lay, row);
    m_dots1Count->layoutRow(tr("Dots 1"), lay, row);

    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

    m_normal2Z->layoutRow(tr("Normal 2 (Z)"), lay, row);
    m_dots2Count->layoutRow(tr("Dots 2"), lay, row);

    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);

    setLayout(lay);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetModelPlane::~WidgetModelPlane()
{
    disconnect(m_wireFrame, &QCheckBox::toggled, this, &WidgetModelPlane::wireFrameChanged);
    disconnect(m_normal1X, &GUI::GuiFloat::changed, this, &WidgetModelPlane::normal1XChaged);
    disconnect(m_normal2Z, &GUI::GuiFloat::changed, this, &WidgetModelPlane::normal2ZChaged);
    disconnect(m_dots1Count, &GUI::GuiInt::changed, this, &WidgetModelPlane::dots1Changed);
    disconnect(m_dots2Count, &GUI::GuiInt::changed, this, &WidgetModelPlane::dots2Changed);

    delete m_normal1X;
    delete m_normal2Z;
    delete m_dots1Count;
    delete m_dots2Count;
}

/*!
 * \brief Update normal 1 (X)
 * \param _value New normal 1 (X)
 */
void Universe1::Widgets::MaterialEditor::WidgetModelPlane::normal1XChaged(float _value)
{
    m_normal1.setX(_value);
    emit normal1Changed(m_normal1);
}

/*!
 * \brief Update normal 2 (Z)
 * \param _value New normal 2 (Z)
 */
void Universe1::Widgets::MaterialEditor::WidgetModelPlane::normal2ZChaged(float _value)
{
    m_normal2.setZ(_value);
    emit normal2Changed(m_normal2);
}
