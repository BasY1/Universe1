/*!
 * \file qt/widgets/gui/guicolorads.h
 * \author Michal Steller
 * \brief The QT color ambient - diffuse - specular GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUICOLORADS_H
#define UNIVERSE1_WIDGETS_GUI_GUICOLORADS_H

#include "../../opengl/adscolors.h"
#include "guicolor.h"

#include <QCheckBox>

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Ambient - diffuse - specular color GUI
 */
class GuiColorADS : public QObject
{
    Q_OBJECT
 public:
    GuiColorADS(const OpenGL::ADSColors &_colors, const Qt::Orientation _orientation, QObject *_parent = nullptr);

    inline GuiColorADS(const OpenGL::ADSColors &_colors, QObject *_parent = nullptr);

    inline GuiColorADS(const QColor _colorAmbient,
                       const QColor _colorDiffuse,
                       const QColor _colorSpecular,
                       const Qt::Orientation _orientation,
                       QObject *_parent = nullptr);

    inline GuiColorADS(const QColor _colorAmbient,
                       const QColor _colorDiffuse,
                       const QColor _colorSpecular,
                       QObject *_parent = nullptr);

    ~GuiColorADS();

    inline const OpenGL::ADSColors &colors() const;
    inline QCheckBox *singleColor();
    inline GuiColor *ambientWidgets();
    inline GuiColor *diffuseWidgets();
    inline GuiColor *specularWidgets();

    inline QColor colorAmbient() const;
    inline QColor colorDiffuse() const;
    inline QColor colorSpecular() const;

 public slots:
    void setColorAmbient(QColor _color);
    void setColorDiffuse(QColor _color);
    void setColorSpecular(QColor _color);

    void setColorsADS(const OpenGL::ADSColors &_colors);
    void setColors(const QColor _colorAmbient, const QColor _colorDiffuse, const QColor _colorSpecular);

    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);

 protected slots:
    void singleColorChanged(bool _value);
    void ambientChanged(QColor _value);
    void diffuseChanged(QColor _value);
    void specularChanged(QColor _value);

 signals:
    /*!
     * \brief Emits when any color was changed
     * \param _colors New ADS values
     */
    void changed(const OpenGL::ADSColors &_colors);

 protected:
    OpenGL::ADSColors m_colors;  //!< Current colors
    QCheckBox *m_singleColor;    //!< Use single color for all nested colors flag widget
    GuiColor *m_ambient;         //!< Ambient color widget
    GuiColor *m_diffuse;         //!< Diffuse color widget
    GuiColor *m_specular;        //!< Specular color widget
};

/*!
 * \brief Constructor
 * \param _colors Initialization colors
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiColorADS::GuiColorADS(const OpenGL::ADSColors &_colors, QObject *_parent)
    : GuiColorADS(_colors, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _colorAmbient Initialization ambient color
 * \param _colorDiffuse Initialization diffuse color
 * \param _colorSpecular Initialization specular color
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 */
inline GuiColorADS::GuiColorADS(const QColor _colorAmbient,
                                const QColor _colorDiffuse,
                                const QColor _colorSpecular,
                                const Qt::Orientation _orientation,
                                QObject *_parent)
    : GuiColorADS(OpenGL::ADSColors(_colorAmbient, _colorDiffuse, _colorSpecular), _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _colorAmbient Initialization ambient color
 * \param _colorDiffuse Initialization diffuse color
 * \param _colorSpecular Initialization specular color
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiColorADS::GuiColorADS(const QColor _colorAmbient,
                                const QColor _colorDiffuse,
                                const QColor _colorSpecular,
                                QObject *_parent)
    : GuiColorADS(OpenGL::ADSColors(_colorAmbient, _colorDiffuse, _colorSpecular), Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current colors
 * \returns Current colors
 */
inline const OpenGL::ADSColors &GuiColorADS::colors() const
{
    return m_colors;
}

/*!
 * \brief Getter for Use single color widget
 * \returns Use single color widget
 */
inline QCheckBox *GuiColorADS::singleColor()
{
    return m_singleColor;
}

/*!
 * \brief Getter for current ambient color widget
 * \returns Ambient color widget
 */
inline GuiColor *GuiColorADS::ambientWidgets()
{
    return m_ambient;
}

/*!
 * \brief Getter for current diffuse color widget
 * \returns Diffuse color widget
 */
inline GuiColor *GuiColorADS::diffuseWidgets()
{
    return m_diffuse;
}

/*!
 * \brief Getter for current specular color widget
 * \returns Specular color widget
 */
inline GuiColor *GuiColorADS::specularWidgets()
{
    return m_specular;
}

/*!
 * \brief Getter for current ambient color
 * \returns Current ambient color
 */
inline QColor GuiColorADS::colorAmbient() const
{
    return m_colors.ambient;
}

/*!
 * \brief Getter for current diffuse color
 * \returns Current diffuse color
 */
inline QColor GuiColorADS::colorDiffuse() const
{
    return m_colors.diffuse;
}

/*!
 * \brief Getter for current specular color
 * \returns Current specular color
 */
inline QColor GuiColorADS::colorSpecular() const
{
    return m_colors.specular;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUICOLORADS_H
