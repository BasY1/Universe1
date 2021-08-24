/*!
 * \file qt/widgets/materialeditor/widgetmaterialeditor.cpp
 * \author Michal Steller
 * \brief Material editor - Main widget class implementation
 */

#include "widgetmaterialeditor.h"

#include "../horizontallinespacer.h"

#include <QDialogButtonBox>
#include <QGridLayout>

/*!
 * \brief Tool function fill row in table
 * \param _table QT Table
 * \param _row Row index
 * \param _name Material name
 * \param _material Material
 */
inline void initTableMaterial(QTableWidget *_table,
                              const int _row,
                              const QString &_name,
                              const Universe1::OpenGL::Material &_material)
{
    QTableWidgetItem *item = new QTableWidgetItem(_name);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
    _table->setItem(_row, 0, item);

    item = new QTableWidgetItem(" ");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
    item->setBackground(_material.ambient);
    _table->setItem(_row, 1, item);

    item = new QTableWidgetItem(" ");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
    item->setBackground(_material.diffuse);
    _table->setItem(_row, 2, item);

    item = new QTableWidgetItem(" ");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
    item->setBackground(_material.specular);
    _table->setItem(_row, 3, item);

    item = new QTableWidgetItem(QString::number(_material.shininess));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable);
    _table->setItem(_row, 4, item);
}

/*!
 * \brief Constructor
 * \param _materialDB Processing material database
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::WidgetMaterialEditor(OpenGL::MaterialDB *_materialDB,
                                                                               QWidget *_parent)
    : QSplitter(Qt::Horizontal, _parent)
    , m_materialDB(_materialDB)
    , m_view(new WidgetView(m_materialDB->defaultMaterial()))
    , m_sceneAmbient(new GUI::GuiFloat(m_view->sceneAmbientFactor(), 0, 1, 3, Qt::Horizontal))
    , m_guiMaterial(new GUI::GuiMaterial(m_materialDB->defaultMaterial(), Qt::Horizontal))
    , m_materialName(new QLineEdit())
    , m_addMaterial(new QPushButton(tr("Add")))
    , m_delMaterial(new QPushButton(tr("Delete")))
    , m_tableDB(new QTableWidget())
    , m_guiDirectionLight(new GUI::GuiDirectionLight(m_view->directionLight()))
    , m_widgetGLSettings(new WidgetGLSettings(m_view))
    , m_widgetSphere(new WidgetModelSphere(m_view->modelSphere()))
    , m_widgetBox(new WidgetModelBox(m_view->modelBox()))
    , m_widgetArrow(new WidgetModelArrow(m_view->modelArrow()))
    , m_widgetTriangle(new WidgetModelTriangle(m_view->modelTriangle()))
    , m_widgetPlane(new WidgetModelPlane(m_view->modelPlane()))
    , m_tabModels(new QTabWidget())
    , m_tabPointLights(new QTabWidget())
    , m_tabSpotLights(new QTabWidget())
    , m_tabSettings(new QTabWidget())
{
    const QSettings settings;

    int rowLay = 0;
    QGridLayout *layMaterial = new QGridLayout();

    m_guiMaterial->layoutRow(layMaterial, rowLay, true);

    layMaterial->addWidget(new HorizontalLineSpacer(), rowLay++, 0, 1, 4);

    m_sceneAmbient->layoutRow(tr("Scene ambient"), layMaterial, rowLay);
    m_sceneAmbient->setToolTip(tr("Scene ambient factor"));

    layMaterial->addWidget(new QLabel(tr("Name")), rowLay, 0, 1, 2);
    layMaterial->addWidget(m_materialName, rowLay, 2, 1, 2);
    rowLay++;

    m_addMaterial->setEnabled(false);
    m_delMaterial->setEnabled(false);

    QDialogButtonBox *buttons = new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(m_addMaterial, QDialogButtonBox::ActionRole);
    buttons->addButton(m_delMaterial, QDialogButtonBox::ActionRole);
    layMaterial->addWidget(buttons, rowLay, 0, 1, 4);
    rowLay++;

    const std::map<QString, OpenGL::Material> &map = m_materialDB->map();

    m_tableDB->setColumnCount(5);
    m_tableDB->setRowCount(map.size());
    m_tableDB->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableDB->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableDB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_tableDB->setHorizontalHeaderLabels({tr("Name"), tr("Ambient"), tr("Diffuse"), tr("Specular"), tr("Shininess")});

    int rowTable = 0;
    for (const std::pair<const QString, OpenGL::Material> &m : map)
    {
        initTableMaterial(m_tableDB, rowTable, m.first, m.second);
        rowTable++;
    }

    layMaterial->addWidget(m_tableDB, rowLay, 0, 1, 4);
    rowLay++;

    QWidget *widMaterial = new QWidget();
    widMaterial->setLayout(layMaterial);

    static const std::pair<QVector3D, QVector3D> range = {QVector3D(-2, -2, -2), QVector3D(2, 2, 2)};
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
    {
        const OpenGL::PointLight &pl = m_view->pointLights().at(i);
        m_guiPointLight[i] = new GUI::GuiPointLight(i, pl, range, 2, Qt::Horizontal);

        QGridLayout *layPointLight = new QGridLayout();
        rowLay = 0;
        m_guiPointLight[i]->layoutRow(layPointLight, rowLay, true);
        layPointLight->addItem(
            new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), rowLay++, 0, 1, 4);

        QWidget *widLight = new QWidget();
        widLight->setLayout(layPointLight);

        m_tabPointLights->addTab(
            widLight, tr("%1 %2").arg(pl.mode == OpenGL::PointLight::LightOff ? tr("Off") : tr("Light")).arg(i + 1));
    }

    m_tabPointLights->setCurrentIndex(
        settings.value("MaterialEditor/tabPointLights", m_tabPointLights->currentIndex()).toInt());

    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
    {
        const OpenGL::SpotLight &sl = m_view->spotLights().at(i);
        m_guiSpotLight[i] = new GUI::GuiSpotLight(i, sl, range, 2, Qt::Horizontal);

        QGridLayout *laySpotLight = new QGridLayout();
        rowLay = 0;
        m_guiSpotLight[i]->layoutRow(laySpotLight, rowLay, true);
        laySpotLight->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), rowLay++, 0, 1, 4);

        QWidget *widLight = new QWidget();
        widLight->setLayout(laySpotLight);

        m_tabSpotLights->addTab(
            widLight, tr("%1 %2").arg(sl.mode == OpenGL::SpotLight::LightOff ? tr("Off") : tr("Light")).arg(i + 1));
    }

    m_tabSpotLights->setCurrentIndex(
        settings.value("MaterialEditor/tabSpotLights", m_tabSpotLights->currentIndex()).toInt());

    QGridLayout *layDirLight = new QGridLayout();
    rowLay = 0;
    m_guiDirectionLight->layoutRow(layDirLight, rowLay, true);
    layDirLight->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), rowLay++, 0, 1, 4);
    QWidget *widDirLight = new QWidget();
    widDirLight->setLayout(layDirLight);

    m_tabModels->addTab(m_widgetSphere, tr("Sphere"));
    m_tabModels->addTab(m_widgetBox, tr("Box"));
    m_tabModels->addTab(m_widgetArrow, tr("Arrow"));
    m_tabModels->addTab(m_widgetTriangle, tr("Triangle"));
    m_tabModels->addTab(m_widgetPlane, tr("Plane"));
    m_tabModels->setCurrentIndex(m_view->currentModel());

    m_tabSettings->addTab(m_tabModels, tr("Models"));
    m_tabSettings->addTab(widDirLight, tr("Direction light"));
    m_tabSettings->addTab(m_tabPointLights, tr("Point lights"));
    m_tabSettings->addTab(m_tabSpotLights, tr("Spot lights"));
    m_tabSettings->addTab(m_widgetGLSettings, tr("Settings"));
    m_tabSettings->setCurrentIndex(settings.value("MaterialEditor/tabSettings").toInt());

    addWidget(widMaterial);
    addWidget(m_view);
    addWidget(m_tabSettings);
    setChildrenCollapsible(false);

    if (settings.contains("MaterialEditor/splitter"))
        restoreState(settings.value("MaterialEditor/splitter").toByteArray());

    connect(m_materialName, &QLineEdit::textChanged, this, &WidgetMaterialEditor::materialNameChanged);
    connect(m_addMaterial, &QPushButton::clicked, this, &WidgetMaterialEditor::addClicked);
    connect(m_delMaterial, &QPushButton::clicked, this, &WidgetMaterialEditor::delClicked);
    connect(m_tableDB, &QTableWidget::currentItemChanged, this, &WidgetMaterialEditor::namesCurrentChanged);
    connect(m_tableDB, &QTableWidget::itemDoubleClicked, this, &WidgetMaterialEditor::namesDoubleClicked);

    connect(m_guiMaterial, &GUI::GuiMaterial::changed, m_view, &WidgetView::setMaterial);
    connect(m_guiDirectionLight, &GUI::GuiDirectionLight::changed, m_view, &WidgetView::setDirectionLight);
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        connect(m_guiPointLight[i], &GUI::GuiPointLight::changed, this, &WidgetMaterialEditor::pointLightChanged);

    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        connect(m_guiSpotLight[i], &GUI::GuiSpotLight::changed, this, &WidgetMaterialEditor::spotLightChanged);

    connect(m_sceneAmbient, &GUI::GuiFloat::changed, m_view, &WidgetView::setSceneAmbientFactor);
    connect(m_tabModels, &QTabWidget::currentChanged, m_view, &WidgetView::setCurrentModel);

    connect(m_widgetSphere, &WidgetModelSphere::wireFrameChanged, m_view, &WidgetView::sphereWireFrameChanged);
    connect(m_widgetSphere,
            &WidgetModelSphere::equatorPointCountChanged,
            m_view,
            &WidgetView::sphereEquatorPointCountChanged);

    connect(m_widgetBox, &WidgetModelBox::wireFrameChanged, m_view, &WidgetView::boxWireFrameChanged);
    connect(m_widgetBox, &WidgetModelBox::normalSetupChanged, m_view, &WidgetView::boxNormalSetupChanged);
    connect(m_widgetBox, &WidgetModelBox::boxSize1Changed, m_view, &WidgetView::boxBoxSize1Changed);
    connect(m_widgetBox, &WidgetModelBox::boxSize2Changed, m_view, &WidgetView::boxBoxSize2Changed);
    connect(m_widgetBox, &WidgetModelBox::boxSize3Changed, m_view, &WidgetView::boxBoxSize3Changed);

    connect(m_widgetArrow, &WidgetModelArrow::wireFrameChanged, m_view, &WidgetView::arrowWireFrameChanged);
    connect(
        m_widgetArrow, &WidgetModelArrow::circlePointCountChanged, m_view, &WidgetView::arrowCirclePointCountChanged);
    connect(m_widgetArrow, &WidgetModelArrow::materialLineChanged, m_view, &WidgetView::arrowMaterialLineChanged);
    connect(m_widgetArrow, &WidgetModelArrow::materialBottomChanged, m_view, &WidgetView::arrowMaterialBottomChanged);

    connect(m_widgetTriangle, &WidgetModelTriangle::wireFrameChanged, m_view, &WidgetView::triangleWireFrameChanged);
    connect(m_widgetTriangle, &WidgetModelTriangle::ccwChanged, m_view, &WidgetView::triangleCcwChanged);
    connect(m_widgetTriangle, &WidgetModelTriangle::normal1Changed, m_view, &WidgetView::triangleNormal1Changed);
    connect(m_widgetTriangle, &WidgetModelTriangle::normal2Changed, m_view, &WidgetView::triangleNormal2Changed);
    connect(m_widgetTriangle, &WidgetModelTriangle::normal3Changed, m_view, &WidgetView::triangleNormal3Changed);

    connect(m_widgetPlane, &WidgetModelPlane::wireFrameChanged, m_view, &WidgetView::planeWireFrameChanged);
    connect(m_widgetPlane, &WidgetModelPlane::normal1Changed, m_view, &WidgetView::planeNormal1Changed);
    connect(m_widgetPlane, &WidgetModelPlane::normal2Changed, m_view, &WidgetView::planeNormal2Changed);
    connect(m_widgetPlane, &WidgetModelPlane::dots1Changed, m_view, &WidgetView::planeDots1Changed);
    connect(m_widgetPlane, &WidgetModelPlane::dots2Changed, m_view, &WidgetView::planeDots2Changed);
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::~WidgetMaterialEditor()
{
    QSettings settings;
    settings.setValue("MaterialEditor/tabPointLights", m_tabPointLights->currentIndex());
    settings.setValue("MaterialEditor/tabSettings", m_tabSettings->currentIndex());
    settings.setValue("MaterialEditor/splitter", saveState());

    disconnect(m_materialName, &QLineEdit::textChanged, this, &WidgetMaterialEditor::materialNameChanged);
    disconnect(m_addMaterial, &QPushButton::clicked, this, &WidgetMaterialEditor::addClicked);
    disconnect(m_delMaterial, &QPushButton::clicked, this, &WidgetMaterialEditor::delClicked);
    disconnect(m_tableDB, &QTableWidget::currentItemChanged, this, &WidgetMaterialEditor::namesCurrentChanged);
    disconnect(m_tableDB, &QTableWidget::itemDoubleClicked, this, &WidgetMaterialEditor::namesDoubleClicked);

    disconnect(m_guiMaterial, &GUI::GuiMaterial::changed, m_view, &WidgetView::setMaterial);
    disconnect(m_guiDirectionLight, &GUI::GuiDirectionLight::changed, m_view, &WidgetView::setDirectionLight);
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        disconnect(m_guiPointLight[i], &GUI::GuiPointLight::changed, this, &WidgetMaterialEditor::pointLightChanged);
    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        disconnect(m_guiSpotLight[i], &GUI::GuiSpotLight::changed, this, &WidgetMaterialEditor::spotLightChanged);

    disconnect(m_sceneAmbient, &GUI::GuiFloat::changed, m_view, &WidgetView::setSceneAmbientFactor);
    disconnect(m_tabModels, &QTabWidget::currentChanged, m_view, &WidgetView::setCurrentModel);

    disconnect(m_widgetSphere, &WidgetModelSphere::wireFrameChanged, m_view, &WidgetView::sphereWireFrameChanged);
    disconnect(m_widgetSphere,
               &WidgetModelSphere::equatorPointCountChanged,
               m_view,
               &WidgetView::sphereEquatorPointCountChanged);

    disconnect(m_widgetBox, &WidgetModelBox::wireFrameChanged, m_view, &WidgetView::boxWireFrameChanged);
    disconnect(m_widgetBox, &WidgetModelBox::normalSetupChanged, m_view, &WidgetView::boxNormalSetupChanged);
    disconnect(m_widgetBox, &WidgetModelBox::boxSize1Changed, m_view, &WidgetView::boxBoxSize1Changed);
    disconnect(m_widgetBox, &WidgetModelBox::boxSize2Changed, m_view, &WidgetView::boxBoxSize2Changed);
    disconnect(m_widgetBox, &WidgetModelBox::boxSize3Changed, m_view, &WidgetView::boxBoxSize3Changed);

    disconnect(m_widgetArrow, &WidgetModelArrow::wireFrameChanged, m_view, &WidgetView::arrowWireFrameChanged);
    disconnect(
        m_widgetArrow, &WidgetModelArrow::circlePointCountChanged, m_view, &WidgetView::arrowCirclePointCountChanged);
    disconnect(m_widgetArrow, &WidgetModelArrow::materialLineChanged, m_view, &WidgetView::arrowMaterialLineChanged);
    disconnect(
        m_widgetArrow, &WidgetModelArrow::materialBottomChanged, m_view, &WidgetView::arrowMaterialBottomChanged);

    disconnect(m_widgetTriangle, &WidgetModelTriangle::wireFrameChanged, m_view, &WidgetView::triangleWireFrameChanged);
    disconnect(m_widgetTriangle, &WidgetModelTriangle::ccwChanged, m_view, &WidgetView::triangleCcwChanged);
    disconnect(m_widgetTriangle, &WidgetModelTriangle::normal1Changed, m_view, &WidgetView::triangleNormal1Changed);
    disconnect(m_widgetTriangle, &WidgetModelTriangle::normal2Changed, m_view, &WidgetView::triangleNormal2Changed);
    disconnect(m_widgetTriangle, &WidgetModelTriangle::normal3Changed, m_view, &WidgetView::triangleNormal3Changed);

    disconnect(m_widgetPlane, &WidgetModelPlane::wireFrameChanged, m_view, &WidgetView::planeWireFrameChanged);
    disconnect(m_widgetPlane, &WidgetModelPlane::normal1Changed, m_view, &WidgetView::planeNormal1Changed);
    disconnect(m_widgetPlane, &WidgetModelPlane::normal2Changed, m_view, &WidgetView::planeNormal2Changed);
    disconnect(m_widgetPlane, &WidgetModelPlane::dots1Changed, m_view, &WidgetView::planeDots1Changed);
    disconnect(m_widgetPlane, &WidgetModelPlane::dots2Changed, m_view, &WidgetView::planeDots2Changed);

    delete m_sceneAmbient;
    delete m_guiMaterial;
    delete m_guiDirectionLight;
    for (int i = 0; i < OpenGL::ShaderProgram::pointLightsCount; ++i)
        delete m_guiPointLight[i];
    for (int i = 0; i < OpenGL::ShaderProgram::spotLightsCount; ++i)
        delete m_guiSpotLight[i];
}

/*!
 * \brief Material name edited handler
 * \param _materialName New material name
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::materialNameChanged(QString _materialName)
{
    m_addMaterial->setEnabled(!_materialName.isEmpty() && !m_materialDB->contains(_materialName));
}

/*!
 * \brief Material table current changed handler
 * \param _current New current item
 * \param _previous Previous selected item
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::namesCurrentChanged(QTableWidgetItem *_current,
                                                                                   QTableWidgetItem *_previous)
{
    Q_UNUSED(_previous)
    m_delMaterial->setEnabled(_current != nullptr);
}

/*!
 * \brief Material table double click changed handler
 * \param _item Double clicked item
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::namesDoubleClicked(QTableWidgetItem *_item)
{
    m_guiMaterial->setMaterial(m_materialDB->get(m_tableDB->item(_item->row(), 0)->text()));
}

/*!
 * \brief Add material to database
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::addClicked()
{
    const QString newName = m_materialName->text();
    if (newName.isEmpty() || m_materialDB->contains(newName))
    {
        m_addMaterial->setEnabled(false);
        return;
    }

    if (m_materialDB->add(newName, m_guiMaterial->material()))
    {
        const int row = m_tableDB->rowCount();
        m_tableDB->setRowCount(row + 1);
        initTableMaterial(m_tableDB, row, newName, m_guiMaterial->material());

        m_materialName->clear();
    }
}

/*!
 * \brief Delete selected material from database
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::delClicked()
{
    QTableWidgetItem *item = m_tableDB->currentItem();
    if (item != nullptr && m_materialDB->remove(m_tableDB->item(item->row(), 0)->text()))
        m_tableDB->removeRow(item->row());
}

/*!
 * \brief Point light changed handler
 * \param _idx Point light index
 * \param _pointLight New point light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::pointLightChanged(int _idx,
                                                                                 const OpenGL::PointLight &_pointLight)
{
    m_view->setPointLight(_idx, _pointLight);
    m_tabPointLights->setTabText(
        _idx,
        tr("%1 %2").arg(_pointLight.mode == OpenGL::PointLight::LightOff ? tr("Off") : tr("Light")).arg(_idx + 1));
}

/*!
 * \brief Spot light changed handler
 * \param _idx Spot light index
 * \param _spotLight New spot light object with values
 */
void Universe1::Widgets::MaterialEditor::WidgetMaterialEditor::spotLightChanged(int _idx,
                                                                                const OpenGL::SpotLight &_spotLight)
{
    m_view->setSpotLight(_idx, _spotLight);
    m_tabSpotLights->setTabText(
        _idx, tr("%1 %2").arg(_spotLight.mode == OpenGL::SpotLight::LightOff ? tr("Off") : tr("Light")).arg(_idx + 1));
}
