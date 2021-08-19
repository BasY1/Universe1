/*!
 * \file qt/widgets/materialeditor/widgetmodels.cpp
 * \author Michal Steller
 * \brief Material editor - Models widget classes implementation
 */

#include "widgetmodels.h"

#include <QGridLayout>
#include <QLabel>
#include <QSettings>

/*!
 * \brief Tool function - prepare triangle normal vectors
 * \param _angle Angle with "direction to center"
 * \param _nameExt Name extension
 * \returns Triangle normal vectors
 */
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::NormalSetup
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::NormalSetup::fromAngle(const float _angle,
                                                                                const QString &_nameExt)
{
    Universe1::Widgets::MaterialEditor::WidgetModelTriangle::NormalSetup result;

    result.name = QObject::tr("Center rotated: %1°").arg(_angle);
    if (!_nameExt.isEmpty())
        result.name += (" (" + _nameExt + ')');

    result.normal1 =
        ((OpenGL::Models::ModelTriangle::defaultVertex2 - OpenGL::Models::ModelTriangle::defaultVertex1).normalized() -
         (OpenGL::Models::ModelTriangle::defaultVertex3 - OpenGL::Models::ModelTriangle::defaultVertex1).normalized())
            .normalized();

    result.normal2 =
        ((OpenGL::Models::ModelTriangle::defaultVertex1 - OpenGL::Models::ModelTriangle::defaultVertex2).normalized() -
         (OpenGL::Models::ModelTriangle::defaultVertex3 - OpenGL::Models::ModelTriangle::defaultVertex2).normalized())
            .normalized();

    result.normal3 =
        ((OpenGL::Models::ModelTriangle::defaultVertex1 - OpenGL::Models::ModelTriangle::defaultVertex3).normalized() -
         (OpenGL::Models::ModelTriangle::defaultVertex2 - OpenGL::Models::ModelTriangle::defaultVertex3).normalized())
            .normalized();

    const QVector3D nTr =
        QVector3D::crossProduct(
            (OpenGL::Models::ModelTriangle::defaultVertex2 - OpenGL::Models::ModelTriangle::defaultVertex1),
            (OpenGL::Models::ModelTriangle::defaultVertex3 - OpenGL::Models::ModelTriangle::defaultVertex1))
            .normalized();

    result.normal1 = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(nTr, result.normal1).normalized(), _angle)
                         .rotatedVector(result.normal1);
    result.normal2 = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(nTr, result.normal2).normalized(), _angle)
                         .rotatedVector(result.normal2);
    result.normal3 = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(nTr, result.normal3).normalized(), _angle)
                         .rotatedVector(result.normal3);

    return result;
}

const std::vector<Universe1::Widgets::MaterialEditor::WidgetModelTriangle::NormalSetup>
    Universe1::Widgets::MaterialEditor::WidgetModelTriangle::m_normals = {

        NormalSetup::fromAngle(0.0F),
        NormalSetup::fromAngle(30.0F),
        NormalSetup::fromAngle(45.0F),
        NormalSetup::fromAngle(60.0F),
        NormalSetup::fromAngle(90.0F, tr("+Y: All")),
        NormalSetup::fromAngle(120.0F),
        NormalSetup::fromAngle(135.0F),
        NormalSetup::fromAngle(150.0F),
        NormalSetup::fromAngle(180.0F),
        NormalSetup::fromAngle(210.0F),
        NormalSetup::fromAngle(225.0F),
        NormalSetup::fromAngle(240.0F),
        NormalSetup::fromAngle(270.0F, tr("-Y: All")),
        NormalSetup::fromAngle(300.0F),
        NormalSetup::fromAngle(315.0F),
        NormalSetup::fromAngle(330.0F),

        {QObject::tr("+X: All"),  //
         QVector3D(1.0F, 0.0F, 0.0F),
         QVector3D(1.0F, 0.0F, 0.0F),
         QVector3D(1.0F, 0.0F, 0.0F)},

        {QObject::tr("-X: All"),  //
         QVector3D(-1.0F, 0.0F, 0.0F),
         QVector3D(-1.0F, 0.0F, 0.0F),
         QVector3D(-1.0F, 0.0F, 0.0F)},

        {QObject::tr("+Y: All (Center rotated: 90°)"),  //
         QVector3D(0.0F, 1.0F, 0.0F),
         QVector3D(0.0F, 1.0F, 0.0F),
         QVector3D(0.0F, 1.0F, 0.0F)},

        {QObject::tr("-Y: All (Center rotated: 270°)"),  //
         QVector3D(0.0F, -1.0F, 0.0F),
         QVector3D(0.0F, -1.0F, 0.0F),
         QVector3D(0.0F, -1.0F, 0.0F)},

        {QObject::tr("+Z: All"),  //
         QVector3D(0.0F, 0.0F, 1.0F),
         QVector3D(0.0F, 0.0F, 1.0F),
         QVector3D(0.0F, 0.0F, 1.0F)},

        {QObject::tr("-Z: All"),  //
         QVector3D(0.0F, 0.0F, -1.0F),
         QVector3D(0.0F, 0.0F, -1.0F),
         QVector3D(0.0F, 0.0F, -1.0F)},

        {QObject::tr("+X +Y +Z: All"),  //
         QVector3D(1.0F, 1.0F, 1.0F),
         QVector3D(1.0F, 1.0F, 1.0F),
         QVector3D(1.0F, 1.0F, 1.0F)},

        {QObject::tr("-X -Y -Z: All"),  //
         QVector3D(-1.0F, -1.0F, -1.0F),
         QVector3D(-1.0F, -1.0F, -1.0F),
         QVector3D(-1.0F, -1.0F, -1.0F)},
};

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
    , m_boxNormal(new QComboBox())
{
    for (const NormalSetup &ns : m_normals)
        m_boxNormal->addItem(ns.name);

    const QSettings settings;
    m_wireFrame->setChecked(settings.value("MaterialEditor/Triangle/wireFrame", m_model->drawWireFrame()).toBool());
    m_boxCWW->setChecked(settings.value("MaterialEditor/Triangle/cww", m_model->ccw()).toBool());
    m_boxNormal->setCurrentIndex(settings.value("MaterialEditor/Triangle/normalIdx", 4).toInt());

    m_model->setDrawWireFrame(m_wireFrame->isChecked());
    m_model->setCcw(m_boxCWW->isChecked());
    normalChanged(m_boxNormal->currentIndex());

    connect(m_wireFrame, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelTriangle::setDrawWireFrame);
    connect(m_boxCWW, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelTriangle::setCcw);
    connect(m_boxNormal,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &WidgetModelTriangle::normalChanged);

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(new QLabel(tr("Draw wire-frame")), 0, 0);
    lay->addWidget(m_wireFrame, 0, 1);
    lay->addWidget(new QLabel(tr("Counter-clockwise point order")), 1, 0);
    lay->addWidget(m_boxCWW, 1, 1);
    lay->addWidget(new QLabel(tr("Normal directions")), 2, 0);
    lay->addWidget(m_boxNormal, 2, 1);
    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 2);
    setLayout(lay);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::~WidgetModelTriangle()
{
    QSettings settings;
    settings.setValue("MaterialEditor/Triangle/wireFrame", m_model->drawWireFrame());
    settings.setValue("MaterialEditor/Triangle/cww", m_model->ccw());
    settings.setValue("MaterialEditor/Triangle/normalIdx", m_boxNormal->currentIndex());

    disconnect(m_wireFrame, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelTriangle::setDrawWireFrame);
    disconnect(m_boxCWW, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelTriangle::setCcw);
    disconnect(m_boxNormal,
               static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this,
               &WidgetModelTriangle::normalChanged);
}

/*!
 * \brief Normal combo-box changed handler
 * \param _currentIndex New selected current index
 */
void Universe1::Widgets::MaterialEditor::WidgetModelTriangle::normalChanged(int _currentIndex)
{
    const NormalSetup &ns = m_normals.at(_currentIndex);
    m_boxNormal->setToolTip(tr("Normal 1: [ %1 x %2 x %3 ]\n"
                               "Normal 2: [ %4 x %5 x %6 ]\n"
                               "Normal 3: [ %7 x %8 x %9 ]")
                                .arg(ns.normal1.x())
                                .arg(ns.normal1.y())
                                .arg(ns.normal1.z())
                                .arg(ns.normal2.x())
                                .arg(ns.normal2.y())
                                .arg(ns.normal2.z())
                                .arg(ns.normal3.x())
                                .arg(ns.normal3.y())
                                .arg(ns.normal3.z()));

    m_model->setNormals(ns.normal1, ns.normal2, ns.normal3);
}

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
    const QSettings settings;
    m_wireFrame->setChecked(settings.value("MaterialEditor/Sphere/wireFrame", m_model->drawWireFrame()).toBool());
    m_model->setDrawWireFrame(m_wireFrame->isChecked());

    m_equatorPointCount->setValue(
        settings.value("MaterialEditor/Sphere/equatorPointCount", m_model->equatorPointCount()).toInt());

    m_model->setEquatorPointCount(m_equatorPointCount->value());

    connect(m_wireFrame, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelSphere::setDrawWireFrame);
    connect(m_equatorPointCount, &GUI::GuiInt::changed, m_model, &OpenGL::Models::ModelSphere::setEquatorPointCount);

    QGridLayout *lay = new QGridLayout();
    int row = 0;
    lay->addWidget(new QLabel(tr("Draw wire-frame")), row, 0, 1, 2);
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
    disconnect(m_wireFrame, &QCheckBox::toggled, m_model, &OpenGL::Models::ModelSphere::setDrawWireFrame);
    disconnect(m_equatorPointCount, &GUI::GuiInt::changed, m_model, &OpenGL::Models::ModelSphere::setEquatorPointCount);

    QSettings settings;
    settings.setValue("MaterialEditor/Sphere/wireFrame", m_model->drawWireFrame());
    settings.setValue("MaterialEditor/Sphere/equatorPointCount", m_model->equatorPointCount());
}
