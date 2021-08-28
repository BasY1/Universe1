/*!
 * \file qt/project/speechdb.h
 * \author Michal Steller
 * \brief Text to speech database declaration
 */

#ifndef UNIVERSE1_PROJECT_SPEECHDB_H
#define UNIVERSE1_PROJECT_SPEECHDB_H

#include <QLocale>
#include <QObject>
#include <QSettings>
#include <QString>

#include <unordered_map>

namespace Universe1 {
namespace Project {

/*!
 * \brief Speech database class
 */
class SpeechDB : public QObject
{
    Q_OBJECT
 public:
    SpeechDB(const QString &_directory,
             const QString &_toolExec,
             const QStringList &_toolOptions,
             QObject *_parent = nullptr);

    inline SpeechDB(const QString &_directory, QObject *_parent = nullptr);

    ~SpeechDB();

    QString getAudioFileName(const QString &_speechText);

    inline bool isToolValid() const;
    inline const QString &speechToolExec() const;
    inline const QStringList &speechToolOptions() const;

 public slots:
    void setSpeechTool(const QString &_toolExec, const QStringList &_toolOptions);

 protected:
    bool prepareWav(const QString &_audioFileName, const QString &_speechText);

    /*!
     * \brief Tool structure - Speech database item
     */
    struct SpeachItem
    {
        QString speechText;     //!< Speech text
        QString audioFileName;  //!< Audio file name
    };

    const QString m_directory;  //!< Audio file cache directory (/tmp/ will be used)
    bool m_toolValid;           //!< Validation flag for external text to speech tool
    QString m_toolExec;         //!< External text to speech tool - executable
    QStringList m_toolOptions;  //!< External text to speech tool - command line options
    QSettings m_settings;       //!< QT-Settings with ini file format for serialization

    std::unordered_map<size_t, SpeachItem> m_db;  //!< Speech database

    static size_t hashID(const QString &_speechText);
    static QString hashFileName(const size_t _hashValue, const QString &_speechText);
};

/*!
 * \brief Constructor
 * \param _directory Audio file cache directory
 * \param _parent Parent \c QObject
 */
inline SpeechDB::SpeechDB(const QString &_directory, QObject *_parent)
    : SpeechDB(_directory, QString(), QStringList(), _parent)
{
}

/*!
 * \brief Getter for tool validation flag
 * \returns Validation flag for external text to speech tool
 */
inline bool SpeechDB::isToolValid() const
{
    return m_toolValid;
}

/*!
 * \brief Getter for external text to speech tool - executable
 * \returns External text to speech tool - executable
 */
inline const QString &SpeechDB::speechToolExec() const
{
    return m_toolExec;
}

/*!
 * \brief Getter for external text to speech tool - command line options
 * \returns External text to speech tool - command line options
 */
inline const QStringList &SpeechDB::speechToolOptions() const
{
    return m_toolOptions;
}

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_SPEECHDB_H
