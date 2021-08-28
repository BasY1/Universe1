/*!
 * \file qt/project/project.h
 * \author Michal Steller
 * \brief The QT Simulation abstract class declaration
 */

#ifndef UNIVERSE1_PROJECT_PROJECT_H
#define UNIVERSE1_PROJECT_PROJECT_H

#include "qsimulation.h"

#include "scenesetup.h"

#include "speechdb.h"

#include <QLocale>
#include <QObject>

namespace Universe1 {
namespace Project {

// struct SceneItem
// {
//     uint ID;
//     virtual uint duration() const = 0;
// };
//
// struct SpeechSentense
// {
//     QString speechText;
//     QString titlesHtml;
//
//     QString audioFile;
//
//     uint audioDurationMS;
//     uint holdAfterAudioMS;
//     uint holdTitlesAfterAudioMS;
//
//     uint duration() const
//     {
//         return audioDurationMS + holdAfterAudioMS + holdTitlesAfterAudioMS;
//     }
// };
//
// struct SpeechParagraph : public SceneItem
// {
//     std::list<SpeechSentense> speech;
//     uint holdBeforeMS;
//     uint holdAfterMS;
//
//     uint duration() const
//     {
//         return holdBeforeMS + holdAfterMS;  // + speech[N]->duration();
//     }
// };
//
// struct SceneScenar
// {
//     SceneSetup setup;
//
//     std::list<SpeechParagraph> speech;
// };

/*!
 * \brief Root class for Universe 1 project structure
 */
class Project : public QObject
{
    Q_OBJECT
 public:
    Project(const QString &_directory, QObject *_parent = nullptr);
    ~Project();

    inline SpeechDB *speech();

 protected:
    const QString m_directory;  //!< Project working directory
    QSettings m_settings;       //!< QT-Settings with ini file format for serialization

    QString m_name;         //!< Project name
    QString m_description;  //!< Project description

    SpeechDB *m_speech;  //!< Speech database

    // SceneSetup m_sceneSetupView;
    // std::vector<QSimulation *> m_simulations;
};

/*!
 * \brief Getter for  Speech database
 * \returns Speech database
 */
inline SpeechDB *Project::speech()
{
    return m_speech;
}

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_PROJECT_H
