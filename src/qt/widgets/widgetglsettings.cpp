/*!
 * \file qt/widgets/widgetglsettings.cpp
 * \author Michal Steller
 * \brief The Open GL settings widget class implementations
 */

#include "widgetglsettings.h"

#include "horizontallinespacer.h"

#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _glWidget Bounded Open GL widget
 * \param _settings Widget settings to use
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::WidgetGLSettings::WidgetGLSettings(OpenGL::GLWidget *_glWidget,
                                                       const Settings _settings,
                                                       QWidget *_parent)
    : QWidget(_parent)
    , m_settings(_settings)
    , m_glWidget(_glWidget)
    , m_bgColor(nullptr)
    , m_antialiasing(nullptr)
    , m_blending(nullptr)
    , m_blendFunc(nullptr)
    , m_cullFaceMode(nullptr)
    , m_cullFaceCcw(nullptr)
    , m_pointSize(nullptr)
    , m_lineWidth(nullptr)
    , m_cameraVerticalAngleDeg(nullptr)
    , m_cameraNearPlane(nullptr)
    , m_cameraFarPlane(nullptr)
    , m_cameraMouseSensitivity(nullptr)
    , m_cameraMoveSpeed(nullptr)
    , m_cameraSpinSpeed(nullptr)
    , m_cameraModifierAccel(nullptr)
    , m_updateOnPaint(nullptr)
    , m_info(nullptr)
{
    bool isFirst = false;
    int row = 0;
    QGridLayout *lay = new QGridLayout();
#ifndef DOXYGEN_SKIP
#define MAYBE_LINE                                                                                                     \
    if (isFirst)                                                                                                       \
        lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);                                                    \
    else                                                                                                               \
        isFirst = true
#endif  // DOXYGEN_SKIP

    if (m_settings.testFlag(SettingsBGColor))
    {
        MAYBE_LINE;

        m_bgColor = new GUI::GuiColor(m_glWidget->bgColor(), Qt::Horizontal, this);
        connect(m_bgColor, &GUI::GuiColor::changed, m_glWidget, &OpenGL::GLWidget::setBGColor);

        m_bgColor->layoutRow(tr("Background"), lay, row);
    }

    if (m_settings.testFlag(SettingsAntialiasing))
    {
        MAYBE_LINE;

        m_antialiasing = new QCheckBox();
        m_antialiasing->setChecked(m_glWidget->antialiasing());
        connect(m_antialiasing, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setAntialiasing);

        lay->addWidget(new QLabel(tr("Antialiasing")), row, 0, 1, 2);
        lay->addWidget(m_antialiasing, row, 2, 1, 2);
        row++;
    }

    if (m_settings.testFlag(SettingsBlending))
    {
        MAYBE_LINE;

        m_blending = new QCheckBox();
        m_blending->setChecked(m_glWidget->blending());

        m_blendFunc = new QCheckBox();
        m_blendFunc->setChecked(m_glWidget->blendFunc());
        m_blendFunc->setEnabled(m_glWidget->blending());
        setBlendFuncToolTip(m_glWidget->blendFunc());

        connect(m_blending, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setBlending);
        connect(m_blending, &QCheckBox::toggled, m_blendFunc, &QCheckBox::setEnabled);

        connect(m_blendFunc, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setBlendFunc);
        connect(m_blendFunc, &QCheckBox::toggled, this, &WidgetGLSettings::setBlendFuncToolTip);

        lay->addWidget(new QLabel(tr("Blending")), row, 0, 1, 2);
        lay->addWidget(m_blending, row, 2);
        lay->addWidget(m_blendFunc, row, 3);
        row++;
    }

    if (m_settings.testFlag(SettingsCullFace))
    {
        MAYBE_LINE;

        m_cullFaceMode = new QComboBox();
        m_cullFaceMode->addItem(tr("Disabled"), static_cast<int>(OpenGL::GLWidget::CullDisabled));
        m_cullFaceMode->addItem(tr("Front"), static_cast<int>(OpenGL::GLWidget::CullFront));
        m_cullFaceMode->addItem(tr("Back"), static_cast<int>(OpenGL::GLWidget::CullBack));
        m_cullFaceMode->addItem(tr("Front and back"), static_cast<int>(OpenGL::GLWidget::CullFrontAndBack));

        m_cullFaceMode->setCurrentIndex(m_cullFaceMode->findData(static_cast<int>(m_glWidget->cullFaceMode())));

        m_cullFaceCcw = new QCheckBox();
        m_cullFaceCcw->setChecked(m_glWidget->cullFaceCcw());
        m_cullFaceCcw->setEnabled(m_glWidget->cullFaceMode() != OpenGL::GLWidget::CullDisabled);

        connect(m_cullFaceMode,
                static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this,
                &WidgetGLSettings::cullFaceModeChanged);
        connect(m_cullFaceCcw, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setCullFaceCcw);

        lay->addWidget(new QLabel(tr("Cull face")), row, 0, 1, 2);
        lay->addWidget(m_cullFaceMode, row, 2, 1, 2);
        row++;

        lay->addWidget(new QLabel(tr("Face counter-clockwise")), row, 0, 1, 2);
        lay->addWidget(m_cullFaceCcw, row, 2, 1, 2);
        row++;
    }

    if (m_settings.testFlag(SettingsPointSize))
    {
        MAYBE_LINE;

        m_pointSize = new GUI::GuiFloat(m_glWidget->pointSize(), 1, 8, 0, Qt::Horizontal, this);
        connect(m_pointSize, &GUI::GuiFloat::changed, m_glWidget, &OpenGL::GLWidget::setPointSize);

        lay->addWidget(new QLabel(tr("Point size")), row, 0, 1, 2);
        lay->addWidget(m_pointSize->box(), row, 2);
        lay->addWidget(m_pointSize->slider(), row, 3);
        row++;
    }

    if (m_settings.testFlag(SettingsLineWidth))
    {
        MAYBE_LINE;

        m_lineWidth = new GUI::GuiFloat(m_glWidget->lineWidth(), 1, 8, 0, Qt::Horizontal, this);
        connect(m_lineWidth, &GUI::GuiFloat::changed, m_glWidget, &OpenGL::GLWidget::setLineWidth);

        lay->addWidget(new QLabel(tr("Line width")), row, 0, 1, 2);
        lay->addWidget(m_lineWidth->box(), row, 2);
        lay->addWidget(m_lineWidth->slider(), row, 3);
        row++;
    }

    if (m_settings.testFlag(SettingsCameraView))
    {
        MAYBE_LINE;

        m_cameraVerticalAngleDeg =
            new GUI::GuiFloat(m_glWidget->camera()->verticalAngleDeg(), 30, 150, 0, Qt::Horizontal, this);

        m_cameraNearPlane = new GUI::GuiFloat(m_glWidget->camera()->nearPlane(), 0, 100, 3, Qt::Horizontal, this);
        m_cameraFarPlane = new GUI::GuiFloat(m_glWidget->camera()->farPlane(), 0, 1000, 1, Qt::Horizontal, this);

        connect(m_cameraVerticalAngleDeg,
                &GUI::GuiFloat::changed,
                m_glWidget->camera(),
                &OpenGL::Camera::setVerticalAngleDeg);
        connect(m_cameraNearPlane, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setNearPlane);
        connect(m_cameraFarPlane, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setFarPlane);

        m_cameraVerticalAngleDeg->layoutRow(tr("Camera view angle"), lay, row);
        m_cameraNearPlane->layoutRow(tr("Camera near plane"), lay, row);
        m_cameraFarPlane->layoutRow(tr("Camera far plane"), lay, row);
    }

    if (m_settings.testFlag(SettingsCameraMove))
    {
        MAYBE_LINE;

        m_cameraMouseSensitivity =
            new GUI::GuiFloat(m_glWidget->camera()->mouseSensitivity(), 1, 20, 0, Qt::Horizontal, this);

        m_cameraMoveSpeed = new GUI::GuiFloat(m_glWidget->camera()->moveSpeed(), 0, 20, 2, Qt::Horizontal, this);
        m_cameraSpinSpeed = new GUI::GuiFloat(m_glWidget->camera()->spinSpeed(), 0, 20, 1, Qt::Horizontal, this);
        m_cameraModifierAccel =
            new GUI::GuiFloat(m_glWidget->camera()->modifierAccel(), 2, 20, 1, Qt::Horizontal, this);

        connect(m_cameraMouseSensitivity,
                &GUI::GuiFloat::changed,
                m_glWidget->camera(),
                &OpenGL::Camera::setMouseSensitivity);

        connect(m_cameraMoveSpeed, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setMoveSpeed);
        connect(m_cameraSpinSpeed, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setSpinSpeed);
        connect(
            m_cameraModifierAccel, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setModifierAccel);

        m_cameraMouseSensitivity->layoutRow(tr("Mouse sensitivity"), lay, row);
        m_cameraMoveSpeed->layoutRow(tr("Camera move speed"), lay, row);
        m_cameraSpinSpeed->layoutRow(tr("Camera spin speed"), lay, row);
        m_cameraModifierAccel->layoutRow(tr("Move acceleration"), lay, row);
    }

    if (m_settings.testFlag(SettingsCameraInfo) || m_settings.testFlag(SettingsOpenGLInfo))
    {
        MAYBE_LINE;

        m_info = new QTextBrowser();
        m_info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_info->setReadOnly(true);

        if (m_settings.testFlag(SettingsCameraInfo))
        {
            connect(m_glWidget->camera(), &OpenGL::Camera::changed, this, &WidgetGLSettings::cameraChanged);
            connect(m_glWidget->camera(), &OpenGL::Camera::changedHandling, this, &WidgetGLSettings::cameraChanged);
            connect(m_glWidget->camera(), &OpenGL::Camera::changedLockView, this, &WidgetGLSettings::cameraChanged);
        }

        if (m_settings.testFlag(SettingsOpenGLInfo))
        {
            m_updateOnPaint = new QCheckBox();
            m_updateOnPaint->setChecked(m_glWidget->emitContextPainted());
            connect(m_updateOnPaint, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setEmitContextPainted);

            lay->addWidget(new QLabel(tr("Update Open GL context")), row, 0, 1, 2);
            lay->addWidget(m_updateOnPaint, row, 2, 1, 2);
            row++;

            connect(m_glWidget, &OpenGL::GLWidget::contextPainted, this, &WidgetGLSettings::contextChanged);
        }
        lay->addWidget(m_info, row, 0, 1, 4);
    }
    else
    {
        lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);
    }
    setLayout(lay);
}

#undef MAYBE_LINE
/*!
 * \brief Destructor
 */
Universe1::Widgets::WidgetGLSettings::~WidgetGLSettings()
{
    if (m_settings.testFlag(SettingsBGColor))
        disconnect(m_bgColor, &GUI::GuiColor::changed, m_glWidget, &OpenGL::GLWidget::setBGColor);

    if (m_settings.testFlag(SettingsAntialiasing))
        disconnect(m_antialiasing, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setAntialiasing);

    if (m_settings.testFlag(SettingsBlending))
    {
        disconnect(m_blending, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setBlending);
        disconnect(m_blending, &QCheckBox::toggled, m_blendFunc, &QCheckBox::setEnabled);

        disconnect(m_blendFunc, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setBlendFunc);
        disconnect(m_blendFunc, &QCheckBox::toggled, this, &WidgetGLSettings::setBlendFuncToolTip);
    }

    if (m_settings.testFlag(SettingsCullFace))
    {
        disconnect(m_cullFaceMode,
                   static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this,
                   &WidgetGLSettings::cullFaceModeChanged);
        disconnect(m_cullFaceCcw, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setCullFaceCcw);
    }

    if (m_settings.testFlag(SettingsPointSize))
        disconnect(m_pointSize, &GUI::GuiFloat::changed, m_glWidget, &OpenGL::GLWidget::setPointSize);

    if (m_settings.testFlag(SettingsLineWidth))
        disconnect(m_lineWidth, &GUI::GuiFloat::changed, m_glWidget, &OpenGL::GLWidget::setLineWidth);

    if (m_settings.testFlag(SettingsCameraView))
    {
        disconnect(m_cameraVerticalAngleDeg,
                   &GUI::GuiFloat::changed,
                   m_glWidget->camera(),
                   &OpenGL::Camera::setVerticalAngleDeg);
        disconnect(m_cameraNearPlane, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setNearPlane);
        disconnect(m_cameraFarPlane, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setFarPlane);
    }

    if (m_settings.testFlag(SettingsCameraMove))
    {
        disconnect(m_cameraMouseSensitivity,
                   &GUI::GuiFloat::changed,
                   m_glWidget->camera(),
                   &OpenGL::Camera::setMouseSensitivity);

        disconnect(m_cameraMoveSpeed, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setMoveSpeed);
        disconnect(m_cameraSpinSpeed, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setSpinSpeed);
        disconnect(
            m_cameraModifierAccel, &GUI::GuiFloat::changed, m_glWidget->camera(), &OpenGL::Camera::setModifierAccel);
    }

    if (m_settings.testFlag(SettingsCameraInfo))
    {
        disconnect(m_glWidget->camera(), &OpenGL::Camera::changed, this, &WidgetGLSettings::cameraChanged);
        disconnect(m_glWidget->camera(), &OpenGL::Camera::changedHandling, this, &WidgetGLSettings::cameraChanged);
        disconnect(m_glWidget->camera(), &OpenGL::Camera::changedLockView, this, &WidgetGLSettings::cameraChanged);
    }

    if (m_settings.testFlag(SettingsOpenGLInfo))
    {
        disconnect(m_updateOnPaint, &QCheckBox::toggled, m_glWidget, &OpenGL::GLWidget::setEmitContextPainted);
        disconnect(m_glWidget, &OpenGL::GLWidget::contextPainted, this, &WidgetGLSettings::contextChanged);
    }
}

/*!
 * \brief Update tool-tip for blending function switch \a m_blendFunc
 * \param _value Checked flag
 */
void Universe1::Widgets::WidgetGLSettings::setBlendFuncToolTip(bool _value)
{
    m_blendFunc->setToolTip(_value ? tr("Current:  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)\n"
                                        "Disabled: glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA)")
                                   : tr("Current: glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA)\n"
                                        "Enabled: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)"));
}

/*!
 * \brief Cull face mode widget change handler
 * \param _value New cull face mode index
 */
void Universe1::Widgets::WidgetGLSettings::cullFaceModeChanged(int _value)
{
    m_glWidget->setCullFaceMode(static_cast<OpenGL::GLWidget::CullFaceMode>(m_cullFaceMode->itemData(_value).toInt()));
    m_cullFaceCcw->setEnabled(m_glWidget->cullFaceMode() != OpenGL::GLWidget::CullDisabled);
}

//#define TABLE_BEGIN "<table border=\"1\" cellspacing=\"2\" cellpadding=\"1\">\n";  //!< Default HTML table header

#define TABLE_BEGIN "<table border=\"0\" cellspacing=\"0\" cellpadding=\"1\">\n";  //!< Default HTML table header

/*!
 * \brief Cull face mode widget change handler
 * \param _value New cull face mode index
 */
void Universe1::Widgets::WidgetGLSettings::cameraChanged()
{
    const OpenGL::Camera *cam = m_glWidget->camera();

    m_cameraHtml = TABLE_BEGIN;
    m_cameraHtml += "<tr><th colspan=\"7\">" + tr("Camera") + "</th></tr>\n";

    m_cameraHtml += "<tr>";
    m_cameraHtml += "<th> </th>";
    m_cameraHtml += "<th><b>" + tr("X") + "</b></th>";
    m_cameraHtml += "<th> </th>";
    m_cameraHtml += "<th><b>" + tr("Y") + "</b></th>";
    m_cameraHtml += "<th> </th>";
    m_cameraHtml += "<th><b>" + tr("Z") + "</b></th>";
    m_cameraHtml += "<th> </th>";
    m_cameraHtml += "</tr>\n";

    m_cameraHtml += "<tr>";
    m_cameraHtml += "<td><b>" + tr("Position") + "</b></td>";
    m_cameraHtml += "<td>" + QString::number(cam->position().x()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->position().y()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->position().z()) + "</td>";
    m_cameraHtml += "<td> </td>";
    m_cameraHtml += "</tr>\n";

    m_cameraHtml += "<tr>";
    m_cameraHtml += "<td><b>" + tr("Look at") + "</b></td>";
    m_cameraHtml += "<td>" + QString::number(cam->centerOfView().x()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->centerOfView().y()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->centerOfView().z()) + "</td>";
    if (cam->isLockedCenterOfView())
        m_cameraHtml += "<td><i>" + tr("Locked") + "</i></td>";
    else
        m_cameraHtml += "<td> </td>";
    m_cameraHtml += "</tr>\n";

    m_cameraHtml += "<tr>";
    m_cameraHtml += "<td><b>" + tr("Up vector") + "</b></td>";
    m_cameraHtml += "<td>" + QString::number(cam->upVector().x()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->upVector().y()) + "</td>";
    m_cameraHtml += "<td>x</td>";
    m_cameraHtml += "<td>" + QString::number(cam->upVector().z()) + "</td>";
    m_cameraHtml += "<td> </td>";
    m_cameraHtml += "</tr>\n";

    m_cameraHtml += "</table>\n\n";

    m_info->setHtml(m_cameraHtml + m_openGLHtml);
}

static QString loadStr(QOpenGLContext *context, GLenum name)
{
    return QString(reinterpret_cast<const char *>(context->functions()->glGetString(name)));
}

static QString sizeText(const size_t size)
{
    const QString tmpStr = QString::number(size);
    QString result;
    for (int s = 1, i = tmpStr.length() - 1; i >= 0; ++s, --i)
    {
        result.prepend(tmpStr[i]);
        if (s % 3 == 0 && i > 0)
            result.prepend(' ');
    }
    return result;
}

static QString memSizeText(const size_t memSize, const bool showBytes = true, const QString &_separator = " ")
{
    static const size_t memSizeK = 1024U;
    static const size_t memSizeM = 1024U * memSizeK;
    static const size_t memSizeG = 1024U * memSizeM;

    static const double memSizeKD = memSizeK;
    static const double memSizeMD = memSizeM;
    static const double memSizeGD = memSizeG;
    const double memSizeD = memSize;

    QString result;
    if (memSize >= memSizeG)
        result = QString("%1 GB").arg(memSizeD / memSizeGD, 0, 'f', 3);
    else if (memSize >= memSizeM)
        result = QString("%1 MB").arg(memSizeD / memSizeMD, 0, 'f', 3);
    else if (memSize >= memSizeK)
        result = QString("%1 kB").arg(memSizeD / memSizeKD, 0, 'f', 3);

    if (showBytes && !result.isEmpty())
        result += _separator + "(" + sizeText(memSize) + " B)";

    if (result.isEmpty())
        result = sizeText(memSize) + " B";

    return result;
}

/*!
 * \brief Open GL widget paint handler
 * \param _context Current Open GL context object
 */
void Universe1::Widgets::WidgetGLSettings::contextChanged(QOpenGLContext *_context)
{
    const QSurfaceFormat format = _context->format();
    const QSet<QByteArray> set = _context->extensions();
    QList<QByteArray> exts(set.cbegin(), set.cend());
    std::sort(exts.begin(), exts.end());

    m_openGLHtml = TABLE_BEGIN;
    m_openGLHtml += "<tr><th colspan=\"2\">" + tr("Open GL - Device") + "</th></tr>\n";

    m_openGLHtml += "<tr>";
    m_openGLHtml += "<td><b>" + tr("Vendor") + "</b></td>";
    m_openGLHtml += "<td>" + loadStr(_context, GL_VENDOR) + "</td>";
    m_openGLHtml += "</tr>\n";

    m_openGLHtml += "<tr>";
    m_openGLHtml += "<td><b>" + tr("Renderer") + "</b></td>";
    m_openGLHtml += "<td>" + loadStr(_context, GL_RENDERER) + "</td>";
    m_openGLHtml += "</tr>\n";

    m_openGLHtml += "<tr>";
    m_openGLHtml += "<td><b>" + tr("Version") + "</b></td>";
    m_openGLHtml += "<td>" + loadStr(_context, GL_VERSION) + "</td>";
    m_openGLHtml += "</tr>\n";

    if (set.contains("GL_NVX_gpu_memory_info"))
    {
        GLint total_mem_kb = 0, cur_avail_mem_kb = 0;
        _context->functions()->glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_mem_kb);
        _context->functions()->glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &cur_avail_mem_kb);

        if (total_mem_kb > 0)
        {
            m_openGLHtml += "<tr>";
            m_openGLHtml += "<td><b>" + tr("NV Total memory") + "</b></td>";
            m_openGLHtml += "<td>" + memSizeText(size_t(total_mem_kb) * 1024U) + "</td>";
            m_openGLHtml += "</tr>\n";
        }

        if (cur_avail_mem_kb > 0)
        {
            m_openGLHtml += "<tr>";
            m_openGLHtml += "<td><b>" + tr("NV Available memory") + "</b></td>";
            m_openGLHtml += "<td>" + memSizeText(size_t(cur_avail_mem_kb) * 1024U) + "</td>";
            m_openGLHtml += "</tr>\n";
        }
    }

    if (set.contains("GL_ATI_meminfo"))
    {
        GLint freeVbo = 0, freeTex = 0, freeRen = 0;
        _context->functions()->glGetIntegerv(GL_VBO_FREE_MEMORY_ATI, &freeVbo);
        _context->functions()->glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI, &freeTex);
        _context->functions()->glGetIntegerv(GL_RENDERBUFFER_FREE_MEMORY_ATI, &freeRen);

        if (freeVbo > 0)
        {
            m_openGLHtml += "<tr>";
            m_openGLHtml += "<td><b>" + tr("ATI Free VBO memory") + "</b></td>";
            m_openGLHtml += "<td>" + memSizeText(size_t(freeVbo)) + "</td>";
            m_openGLHtml += "</tr>\n";
        }

        if (freeTex > 0)
        {
            m_openGLHtml += "<tr>";
            m_openGLHtml += "<td><b>" + tr("ATI Free texture memory") + "</b></td>";
            m_openGLHtml += "<td>" + memSizeText(size_t(freeTex)) + "</td>";
            m_openGLHtml += "</tr>\n";
        }

        if (freeRen > 0)
        {
            m_openGLHtml += "<tr>";
            m_openGLHtml += "<td><b>" + tr("ATI Free render memory") + "</b></td>";
            m_openGLHtml += "<td>" + memSizeText(size_t(freeRen)) + "</td>";
            m_openGLHtml += "</tr>\n";
        }
    }

    m_openGLHtml += "<tr>";
    m_openGLHtml += "<td><b>" + tr("Memory usage") + "</b></td>";
    m_openGLHtml += "<td>" + memSizeText(m_glWidget->memoryUsage()) + "</td>";
    m_openGLHtml += "</tr>\n";

    m_openGLHtml += "</table>\n\n";

    m_info->setHtml(m_cameraHtml + m_openGLHtml);
}
