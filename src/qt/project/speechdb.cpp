/*!
 * \file qt/project/speechdb.cpp
 * \author Michal Steller
 * \brief Text to speech database implementation
 */

#include "speechdb.h"

#include <QDir>
#include <QFileInfo>
#include <QProcess>

/*!
 * \brief Tool function initialize speech database path
 * \param _directory Directory
 * \returns Empty string or existing (maybe created) path to directory
 */
inline QString initDirectory(const QString &_directory)
{
    if (_directory.isEmpty())
        return _directory;

    if (QDir().exists(_directory))
        return (_directory.endsWith('/') ? _directory : (_directory + '/'));

    if (QDir().mkpath(_directory))
        return (_directory.endsWith('/') ? _directory : (_directory + '/'));
    return QString();
}

/*!
 * \brief Constructor
 * \param _directory Audio file cache directory
 * \param _toolExec External text to speech tool - executable
 * \param _toolOptions External text to speech tool - command line options
 * \param _parent Parent \c QObject
 */
Universe1::Project::SpeechDB::SpeechDB(const QString &_directory,
                                       const QString &_toolExec,
                                       const QStringList &_toolOptions,
                                       QObject *_parent)
    : QObject(_parent)
    , m_directory(initDirectory(_directory))
    , m_toolValid(QFileInfo(_toolExec).isExecutable())
    , m_toolExec(_toolExec)
    , m_toolOptions(_toolOptions)
    , m_settings(_directory + "SpeechDB.ini", QSettings::IniFormat)
{
    if (!m_toolValid && m_settings.contains("externalToolExec"))
    {
        m_toolExec = m_settings.value("externalToolExec").toString();
        m_toolOptions = m_settings.value("externalToolOptions").toStringList();
        m_toolValid = QFileInfo(m_toolExec).isExecutable();
    }

    const int count = m_settings.value("count", 0).toInt();

    m_settings.beginGroup("DB");
    for (int i = 0; i < count; ++i)
    {
        const QString key = QString("_%1_").arg(i);
        const size_t hash = m_settings.value(key + "hash").toULongLong();
        const QString text = m_settings.value(key + "text").toString();
        const QString file = m_settings.value(key + "file").toString();
        m_db.insert({hash, {text, file}});
    }
    m_settings.endGroup();
}

/*!
 * \brief Destructor
 */
Universe1::Project::SpeechDB::~SpeechDB()
{
    std::unordered_map<size_t, SpeachItem>::const_iterator it = m_db.cbegin();
    const int count = static_cast<int>(m_db.size());

    m_settings.setValue("externalToolExec", m_toolExec);
    m_settings.setValue("externalToolOptions", m_toolOptions);
    m_settings.setValue("count", count);

    m_settings.beginGroup("DB");
    for (int i = 0; i < count; ++i, ++it)
    {
        const QString key = QString("_%1_").arg(i);
        m_settings.setValue(key + "hash", static_cast<qulonglong>(it->first));
        m_settings.setValue(key + "text", it->second.speechText);
        m_settings.setValue(key + "file", it->second.audioFileName);
    }
    m_settings.endGroup();
}

/*!
 * \brief External text to speech tool
 * \param _toolExec Text to speech tool executable
 * \param _toolOptions Text to speech tool options
 */
void Universe1::Project::SpeechDB::setSpeechTool(const QString &_toolExec, const QStringList &_toolOptions)
{
    if (QFileInfo(_toolExec).isExecutable())
    {
        m_toolValid = true;
        m_toolExec = _toolExec;
        m_toolOptions = _toolOptions;
    }
}

/*!
 * \brief Get audio file
 * \param _speechText Text for audio
 * \returns Path to cached or prepared audio file
 */
QString Universe1::Project::SpeechDB::getAudioFileName(const QString &_speechText)
{
    if (!m_toolValid)
        return QString();

    const size_t h = hashID(_speechText);
    if (m_directory.isEmpty())
    {
        const QString fileName = "/tmp/" + QString("speech_%1_%2.wav").arg(h, 16, 16, QLatin1Char('0'));
        if (prepareWav(fileName, _speechText))
            return fileName;
        return QString();
    }

    std::unordered_map<size_t, SpeachItem>::const_iterator it = m_db.find(h);
    if (it != m_db.cend())
        return it->second.audioFileName;

    const QString fileName = m_directory + hashFileName(h, _speechText);
    if (!prepareWav(fileName, _speechText))
        return QString();

    m_db.insert({h, {_speechText, fileName}});
    return fileName;
}

/*!
 * \brief Prepare wav file using external tool
 * \param _audioFileName Output audio file
 * \param _speechText Text to speech witch audio
 * \returns Success flag
 */
bool Universe1::Project::SpeechDB::prepareWav(const QString &_audioFileName, const QString &_speechText)
{
    QProcess process;

    QStringList opts = m_toolOptions;
    opts.push_back(_audioFileName);
    opts.push_back(_speechText);

    process.start(m_toolExec, opts);

    return process.waitForFinished();
}

/*!
 * \brief Tool function - hashes text
 * \param _speechText Text to hash
 * \returns Text hash value
 */
size_t Universe1::Project::SpeechDB::hashID(const QString &_speechText)
{
    return std::hash<std::string>{}(_speechText.toStdString());
}

/*!
 * \brief Tool function - prepare file name from hash
 * \param _hashValue value of hash
 * \param _speechText Text to speech witch audio
 * \returns File name from hash
 */
QString Universe1::Project::SpeechDB::hashFileName(const size_t _hashValue, const QString &_speechText)
{
    QString fn = _speechText;
    fn.replace(QRegExp("[\\s,.:!?/*%\\\\\\\"]"), "_");
    return QString("speech_%1__").arg(_hashValue, 16, 16, QLatin1Char('0')) + fn + ".wav";
}
