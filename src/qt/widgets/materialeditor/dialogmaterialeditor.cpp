/*!
 * \file qt/widgets/materialeditor/dialogmaterialeditor.cpp
 * \author Michal Steller
 * \brief Material editor - Main dialog class implementation
 */

#include "dialogmaterialeditor.h"

#include <QDialogButtonBox>
#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _materialDB Processing material database
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::MaterialEditor::DialogMaterialEditor::DialogMaterialEditor(OpenGL::MaterialDB *_materialDB,
                                                                               QWidget *_parent)
    : QDialog(_parent)
    , m_rootWidget(new WidgetMaterialEditor(_materialDB))
{
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(m_rootWidget, 0, 0);
    lay->addWidget(buttons, 1, 0);
    setLayout(lay);

    const QSettings settings;
    move(settings.value("MaterialEditor/Dialog/pos", pos()).toPoint());
    resize(settings.value("MaterialEditor/Dialog/size", size()).toSize());
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::MaterialEditor::DialogMaterialEditor::~DialogMaterialEditor()
{
    QSettings settings;
    settings.setValue("MaterialEditor/Dialog/pos", pos());
    settings.setValue("MaterialEditor/Dialog/size", size());
}
