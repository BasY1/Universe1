/*!
 * \file qt/widgets/widgetglsettings.h
 * \author Michal Steller
 * \brief The Open GL settings widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETGLSETTINGS_H
#define UNIVERSE1_WIDGETS_WIDGETGLSETTINGS_H

#include "../opengl/glwidget.h"

#include "gui/guicolor.h"
#include "gui/guifloat.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QTextBrowser>

namespace Universe1 {
namespace Widgets {

/*!
 * \brief The Open GL settings widget
 */
class WidgetGLSettings : public QWidget
{
	Q_OBJECT

 public:
    /*!
     * \brief Possible setting enumeration
     */
    enum Setting
    {
        SettingsBGColor = 0x0001,       //!< Show background color widgets
        SettingsAntialiasing = 0x0002,  //!< Show antialiasing check box
        SettingsBlending = 0x0004,      //!< Show blending widgets
        SettingsCullFace = 0x0008,      //!< Show cull face widgets
        SettingsPointSize = 0x0010,     //!< Show point size widgets
        SettingsLineWidth = 0x0020,     //!< Show line width widgets
        SettingsCameraView = 0x0040,    //!< Show camera view widgets
        SettingsCameraMove = 0x0080,    //!< Show camera move widgets
        SettingsCameraInfo = 0x0100,    //!< Show camera info widgets
        SettingsOpenGLInfo = 0x0200,    //!< Show Open GL information widgets
    };
    Q_DECLARE_FLAGS(Settings, Setting)
    Q_FLAG(Settings)

    WidgetGLSettings(OpenGL::GLWidget *_glWidget, const Settings _settings, QWidget *_parent = nullptr);
    inline WidgetGLSettings(OpenGL::GLWidget *_glWidget, QWidget *_parent = nullptr);

    ~WidgetGLSettings();

 protected slots:
    void setBlendFuncToolTip(bool _value);
    void cullFaceModeChanged(int _value);
    void cameraChanged();
    void contextChanged(QOpenGLContext *_context);

 protected:
    const Settings m_settings;  //!< Widget settings flag

    OpenGL::GLWidget *m_glWidget;  //!< Bounded Open GL widget

    GUI::GuiColor *m_bgColor;  //!< Background color GUI

    QCheckBox *m_antialiasing;  //!< Antialiasing enable  widget

    QCheckBox *m_blending;   //!< Blending enable widget
    QCheckBox *m_blendFunc;  //!< Blending function switch widget

    QComboBox *m_cullFaceMode;  //!< Cull face mode widget
    QCheckBox *m_cullFaceCcw;   //!< Cull face counter-clockwise switch widget

    GUI::GuiFloat *m_pointSize;  //!< Point size widget
    GUI::GuiFloat *m_lineWidth;  //!< Line width widget

    GUI::GuiFloat *m_cameraVerticalAngleDeg;  //!< Camera vertical angle widget
    GUI::GuiFloat *m_cameraNearPlane;         //!< Camera near plane widget
    GUI::GuiFloat *m_cameraFarPlane;          //!< Camera far plane widget

    GUI::GuiFloat *m_cameraMouseSensitivity;  //!< Camera mouse sensitivity widget
    GUI::GuiFloat *m_cameraMoveSpeed;         //!< Camera move speed widget
    GUI::GuiFloat *m_cameraSpinSpeed;         //!< Camera spin speed widget
    GUI::GuiFloat *m_cameraModifierAccel;     //!< Camera modifier acceleration widget

    QCheckBox *m_updateOnPaint;  //!< Antialiasing enable  widget
    QTextBrowser *m_info;        //!< Information text browser
    QString m_cameraHtml;        //!< Current camera information text
    QString m_openGLHtml;        //!< Current Open GL information text
};

Q_DECLARE_OPERATORS_FOR_FLAGS(WidgetGLSettings::Settings)

/*!
 * \brief Constructor prepare widget with all setting
 * \param _glWidget Bounded Open GL widget
 * \param _parent Parent \c QWidget
 */
inline WidgetGLSettings::WidgetGLSettings(OpenGL::GLWidget *_glWidget, QWidget *_parent)
    : WidgetGLSettings(_glWidget,
                       (SettingsBGColor | SettingsAntialiasing | SettingsBlending | SettingsCullFace |
                        SettingsPointSize | SettingsLineWidth | SettingsCameraView | SettingsCameraMove |
                        SettingsCameraInfo | SettingsOpenGLInfo),
                       _parent)
{
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETGLSETTINGS_H
