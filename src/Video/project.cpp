/*!
 * \file src/Video/project.cpp
 * \brief Video footage
 */

#include "project.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

namespace U1 {
namespace Video {

bool Project::createVideo(const QString &_workDir, const QString &_fileName) const
{
    if (m_footages.empty())
    {
        std::cout << "Project[" << name << "]: Empty project!\n";
        return false;
    }

    if (!settingsSubtitles.isValid())
    {
        std::cout << "Project[" << name << "]: Invalid subtitles settings!\n";
        return false;
    }

    if (!settingsOpenGL.isValid())
    {
        std::cout << "Project[" << name << "]: Invalid Open GL settings!\n";
        return false;
    }

    if (!settingsVideo.isValid())
    {
        std::cout << "Project[" << name << "]: Invalid video settings!\n";
        return false;
    }

    if (!settingsAudio.isValid())
    {
        std::cout << "Project[" << name << "]: Invalid audio settings!\n";
        return false;
    }

    if (QFile::exists(_fileName))
    {
        if (!QFile::remove(_fileName))
        {
            std::cerr << "Project[" << name << "]: Can't overwrite/remove file:" << qPrintable(_fileName) << "!\n";
            return false;
        }
    }

    const QString wd = _workDir.endsWith(QDir::separator()) ? _workDir : (_workDir + QDir::separator());
    QDir(wd).removeRecursively();
    if (!QDir(wd).exists())
    {
        if (!QDir().mkpath(wd))
        {
            std::cerr << "Project[" << name << "]: Can't create working directory:" << qPrintable(wd) << "!\n";
            return false;
        }
    }

    const QString wdLaTeX = wd + "LaTeX" + QDir::separator();
    if (!QDir(wdLaTeX).exists())
    {
        if (!QDir().mkpath(wdLaTeX))
        {
            std::cerr << "Project[" << name << "]: Can't create LaTeX directory:" << qPrintable(wdLaTeX) << "!\n";
            return false;
        }
    }

    Items::ItemDefaultValues::latexWorkDir = wdLaTeX;

    if (m_footages.size() == 1UL)
        return m_footages[0UL]->createVideo(
            wd, _fileName, settingsSubtitles, settingsOpenGL, settingsVideo, settingsAudio);

    const QString suffix = QFileInfo(_fileName).suffix();

    QStringList footageVideos;
    for (size_t fID = 1UL; fID <= m_footages.size(); ++fID)
    {
        const QString wdd = wd + "Footage_" + QString::number(fID) + "_" + QDir::separator();
        const QString wdf = wd + "Footage_" + QString::number(fID) + "_." + suffix;
        if (!m_footages[fID - 1UL]->createVideo(
                wdd, wdf, settingsSubtitles, settingsOpenGL, settingsVideo, settingsAudio))
            return false;
        footageVideos.push_back(wdf);
    }

    return settingsVideo.joinVideos(_fileName, settingsAudio, footageVideos);
}

}  // namespace Video
}  // namespace U1
