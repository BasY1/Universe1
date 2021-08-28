/*!
 * \file qt/project/project.cpp
 * \author Michal Steller
 * \brief The QT Simulation abstract class implementation
 */

#include "project.h"

/*!
 * \brief Constructor
 * \param _directory Project working directory
 * \param _parent Parent \c QObject
 */
Universe1::Project::Project::Project::Project(const QString &_directory, QObject *_parent)
    : QObject(_parent)
    , m_directory(_directory.endsWith('/') ? _directory : (_directory + '/'))
    , m_settings(_directory + "Project.ini", QSettings::IniFormat)
    , m_name(m_settings.value("name").toString())
    , m_description(m_settings.value("description").toString())
    , m_speech(new SpeechDB(_directory + "speech/"))
{
}

/*!
 * \brief Destructor
 */
Universe1::Project::Project::Project::~Project()
{
    delete m_speech;
}
