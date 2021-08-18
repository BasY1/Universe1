/*!
 * \file qt/widgets/materialeditor/widgetmodeltriangle.cpp
 * \author Michal Steller
 * \brief Material editor - Triangle model widget class implementation
 */

#include "widgetmodeltriangle.h"

#include <QGridLayout>
#include <QSettings>

/*!
 * \brief Tool function - prepare triangle normal vectors
 * \param _angle Angle with "direction to center"
 * \param _nameExt Name extension
 * \return Triangle normal vectors
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
        ((OpenGL::Models::TriangleModel::defaultVertex2 - OpenGL::Models::TriangleModel::defaultVertex1).normalized() -
         (OpenGL::Models::TriangleModel::defaultVertex3 - OpenGL::Models::TriangleModel::defaultVertex1).normalized())
            .normalized();

    result.normal2 =
        ((OpenGL::Models::TriangleModel::defaultVertex1 - OpenGL::Models::TriangleModel::defaultVertex2).normalized() -
         (OpenGL::Models::TriangleModel::defaultVertex3 - OpenGL::Models::TriangleModel::defaultVertex2).normalized())
            .normalized();

    result.normal3 =
        ((OpenGL::Models::TriangleModel::defaultVertex1 - OpenGL::Models::TriangleModel::defaultVertex3).normalized() -
         (OpenGL::Models::TriangleModel::defaultVertex2 - OpenGL::Models::TriangleModel::defaultVertex3).normalized())
            .normalized();

    const QVector3D nTr =
        QVector3D::crossProduct(
            (OpenGL::Models::TriangleModel::defaultVertex2 - OpenGL::Models::TriangleModel::defaultVertex1),
            (OpenGL::Models::TriangleModel::defaultVertex3 - OpenGL::Models::TriangleModel::defaultVertex1))
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
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::WidgetModelTriangle(OpenGL::Models::TriangleModel *_model,
                                                                             QWidget *_parent)
    : WidgetModel(_parent)
    , m_model(_model)
    , m_boxCWW(new QCheckBox())
    , m_boxNormal(new QComboBox())
{
    for (const NormalSetup &ns : m_normals)
        m_boxNormal->addItem(ns.name);

    const QSettings settings;
    m_boxCWW->setChecked(settings.value("MaterialEditor/Triangle/cww", m_model->ccw()).toBool());
    m_boxNormal->setCurrentIndex(settings.value("MaterialEditor/Triangle/normalIdx", 4).toInt());

    m_model->setCcw(m_boxCWW->isChecked());
    normalChanged(m_boxNormal->currentIndex());

    connect(m_boxCWW, &QCheckBox::toggled, m_model, &OpenGL::Models::TriangleModel::setCcw);
    connect(m_boxNormal,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &WidgetModelTriangle::normalChanged);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetModelTriangle::~WidgetModelTriangle()
{
    QSettings settings;
    settings.setValue("MaterialEditor/Triangle/cww", m_model->ccw());
    settings.setValue("MaterialEditor/Triangle/normalIdx", m_boxNormal->currentIndex());

    disconnect(m_boxCWW, &QCheckBox::toggled, m_model, &OpenGL::Models::TriangleModel::setCcw);
    disconnect(m_boxNormal,
               static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this,
               &WidgetModelTriangle::normalChanged);
}

/*!
 * \brief Getter for Open GL model object
 * \return Open GL triangle model object
 */
Universe1::OpenGL::Models::GLModel *Universe1::Widgets::MaterialEditor::WidgetModelTriangle::model()
{
    return m_model;
}

/*!
 * \brief Getter for model name
 * \return Model name
 */
QString Universe1::Widgets::MaterialEditor::WidgetModelTriangle::name() const
{
    return tr("Triangle");
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
