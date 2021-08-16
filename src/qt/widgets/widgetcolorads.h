/*!
 * \file qt/widgets/widgetcolorads.h
 * \author Michal Steller
 * \brief The QT color ambient - diffuse - specular widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETCOLORADS_H
#define UNIVERSE1_WIDGETS_WIDGETCOLORADS_H

#include "../opengl/adscolors.h"
#include "widgetcolor.h"

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Ambient - diffuse - specular color widget
 */
class WidgetColorADS : public QWidget
{
    Q_OBJECT
 public:
    WidgetColorADS(const OpenGL::ADSColors &_colors, const Qt::Orientation _orientation, QWidget *_parent = nullptr);

    inline WidgetColorADS(const OpenGL::ADSColors &_colors, QWidget *_parent = nullptr);

    inline WidgetColorADS(const QColor _colorAmbient,
                          const QColor _colorDiffuse,
                          const QColor _colorSpecular,
                          const Qt::Orientation _orientation,
                          QWidget *_parent = nullptr);

    inline WidgetColorADS(const QColor _colorAmbient,
                          const QColor _colorDiffuse,
                          const QColor _colorSpecular,
                          QWidget *_parent = nullptr);

    ~WidgetColorADS();

    inline const OpenGL::ADSColors &colors() const;
    inline QColor colorAmbient() const;
    inline QColor colorDiffuse() const;
    inline QColor colorSpecular() const;

 public slots:
    void setColorAmbient(QColor _color);
    void setColorDiffuse(QColor _color);
    void setColorSpecular(QColor _color);

    void setColorsADS(const OpenGL::ADSColors &_colors);
    void setColors(const QColor _colorAmbient, const QColor _colorDiffuse, const QColor _colorSpecular);

 protected slots:
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
    WidgetColor *m_ambient;      //!< Ambient color widget
    WidgetColor *m_diffuse;      //!< Diffuse color widget
    WidgetColor *m_specular;     //!< Specular color widget
};

/*!
 * \brief Constructor
 * \param _colors Initialization colors
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetColorADS::WidgetColorADS(const OpenGL::ADSColors &_colors, QWidget *_parent)
    : WidgetColorADS(_colors, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _colorAmbient Initialization ambient color
 * \param _colorDiffuse Initialization diffuse color
 * \param _colorSpecular Initialization specular color
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QWidget
 */
inline WidgetColorADS::WidgetColorADS(const QColor _colorAmbient,
                                      const QColor _colorDiffuse,
                                      const QColor _colorSpecular,
                                      const Qt::Orientation _orientation,
                                      QWidget *_parent)
    : WidgetColorADS(OpenGL::ADSColors(_colorAmbient, _colorDiffuse, _colorSpecular), _orientation, _parent)
{
}

/*!
 * \brief Constructor
 * \param _colorAmbient Initialization ambient color
 * \param _colorDiffuse Initialization diffuse color
 * \param _colorSpecular Initialization specular color
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetColorADS::WidgetColorADS(const QColor _colorAmbient,
                                      const QColor _colorDiffuse,
                                      const QColor _colorSpecular,
                                      QWidget *_parent)
    : WidgetColorADS(OpenGL::ADSColors(_colorAmbient, _colorDiffuse, _colorSpecular), Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current colors
 * \return Current colors
 */
inline const OpenGL::ADSColors &WidgetColorADS::colors() const
{
    return m_colors;
}

/*!
 * \brief Getter for current ambient color
 * \return Current ambient color
 */
inline QColor WidgetColorADS::colorAmbient() const
{
    return m_colors.ambient;
}

/*!
 * \brief Getter for current diffuse color
 * \return Current diffuse color
 */
inline QColor WidgetColorADS::colorDiffuse() const
{
    return m_colors.diffuse;
}

/*!
 * \brief Getter for current specular color
 * \return Current specular color
 */
inline QColor WidgetColorADS::colorSpecular() const
{
    return m_colors.specular;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETCOLORADS_H
