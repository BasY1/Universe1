/*!
 * \file src/Items/item.cpp
 * \brief Basic video item
 */

#include "item.h"

#include "../Audio/settingsaudio.h"

#include <QTextOption>
#include <QDir>
#include <QFile>
#include <QFileInfo>

namespace U1 {
namespace Items {

QString ItemDefaultValues::latexWorkDir = QString(".") + QDir::separator();

size_t ItemDefaultValues::sphereQuality = 15UL;
size_t ItemDefaultValues::lineQuality = 3UL;

float ItemDefaultValues::pixelSize = 0.001F;
float ItemDefaultValues::textPixelSize = 0.01f;
float ItemDefaultValues::lineRadius = 0.005F;
float ItemDefaultValues::arrowLength = 0.075F;
float ItemDefaultValues::arrowRadius = 0.025F;

QColor ItemDefaultValues::lineColor = QColor(255, 255, 255);
QColor ItemDefaultValues::textColor = QColor(255, 255, 255);

QString ItemDefaultValues::textFont = "Sans Serif";
uint ItemDefaultValues::fontHeight = 24;

Item::Item(const std::string &_name, const uint8_t _alpha, const bool _visible)
    : Props::ItemPropertyGroup(_name)
    , alpha("alpha", _alpha)
    , visible("visible", _visible)
{
    setupProperties({&alpha, &visible});
}

/*!
 * \brief Create latex math image
 * \param _latexMath LaTeX text
 * \param _imageFile Output image file name
 * \return Success flag
 * \note Usage: <code>"$$$LatexMath#\\fg{FFFFFF} \\huge C = \\frac{A}{B}###"</code>
 */
bool createLatexMath(const QString &_latexMath, const QString &_imageFile)
{
    const QStringList args = {
        "-q", QString("https://latex.codecogs.com/png.download?%1").arg(_latexMath), "-O", _imageFile};
    Audio::SettingsAudio::runProcess("/usr/bin/wget", args);

    if (!QFile::exists(_imageFile))
    {
        std::cerr << "Error: Invalid LaTeX:[" << qPrintable(_latexMath) << "]\n";
        return false;
    }

    if (QFileInfo(_imageFile).size() == 0)
    {
        QFile::remove(_imageFile);
        std::cerr << "Error: Invalid LaTeX:[" << qPrintable(_latexMath) << "]\n";
        return false;
    }
    return true;
}

/*!
 * \brief Create latex math image
 * \param _latexMath LaTeX text
 * \param _ok Success flag pointer
 * \return Image file name
 * \note Uses ItemDefaultValues::latexWorkDir
 * \sa ItemDefaultValues::latexWorkDir
 */
QString createLatexMathImg(const QString &_latexMath, bool *_ok)
{
    const size_t h = std::hash<std::string>{}(_latexMath.toStdString());
    const QString result = ItemDefaultValues::latexWorkDir + "latex_" + QString::number(h) + ".png";
    if (QFile::exists(result))
        return result;
    const bool ok = createLatexMath(_latexMath, result);
    if (!ok)
    {
        if (_ok != nullptr)
            *_ok = false;
        return "";
    }
    if (_ok != nullptr)
        *_ok = true;
    return result;
}

QTextDocument *Item::createTextDocument(const QString &_text,
                                        const QString &_fontFamily,
                                        const uint32_t _fontHeight,
                                        const QColor &_usedColor)
{
    QTextDocument *result = new QTextDocument();
    QTextOption opts;
    opts.setAlignment(Qt::AlignCenter);
    opts.setWrapMode(QTextOption::NoWrap);
    result->setDefaultTextOption(opts);
    result->setUndoRedoEnabled(false);
    QString tmp = "<span style=\"";
    if (!_fontFamily.isEmpty())
        tmp += "font-family:" + _fontFamily + "; ";
    tmp += "font-size:" + QString::number(_fontHeight) + "pt; ";
    if (_usedColor.isValid())
        tmp += "color:" + _usedColor.name() + "; ";
    tmp += "\">";
    tmp += "<table><tr><td align=\"center\">";

    qsizetype i = _text.indexOf("$$$LatexMath#");
    if (i < 0)
    {
        tmp += _text;
    }
    else
    {
        bool ok = true;
        QString text2 = _text;
        while (i >= 0)
        {
            const qsizetype i2 = text2.indexOf("###", i + 13);
            if (i2 < 0)
            {
                ok = false;
                break;
            }

            const QString latexTextFull = text2.mid(i, i2 - i + 3);
            const QString latexText = latexTextFull.mid(13, i2 - (i + 13));
            const QString imgFileName = createLatexMathImg(latexText, &ok);
            if (!ok)
                break;

            text2.replace(latexTextFull, QString("<img src=\"%1\" />").arg(imgFileName));
            i = text2.indexOf("$$$LatexMath#");
        }

        if (ok)
            tmp += text2;
        else
            tmp += _text;
    }
    tmp += "</td></tr></table></span>";

    result->setHtml(tmp);
    return result;
}

}  // namespace Items
}  // namespace U1
