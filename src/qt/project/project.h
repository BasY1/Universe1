/*!
 * \file qt/project/project.h
 * \author Michal Steller
 * \brief The QT Simulation abstract class declaration
 */

#ifndef UNIVERSE1_PROJECT_PROJECT_H
#define UNIVERSE1_PROJECT_PROJECT_H

#include "../../simulation/simulation.h"

#include "materialdb.h"

#include <QObject>

namespace Universe1 {
namespace Project {

/*!
 * \brief Root class for Universe 1 project structure
 */
class Project : public QObject
{
    Q_OBJECT
 public:
 protected:
    MaterialDB *m_materials;  //!< Material database

    QString m_name;         //!< Project name
    QString m_description;  //!< Project description
};

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_PROJECT_H
