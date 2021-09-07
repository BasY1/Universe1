/*!
 * \file main.cpp
 * \author Michal Steller
 * \brief The main application method
 */

#include <QApplication>

#include "qt/project/project.h"
#include "qt/widgets/materialeditor/dialogmaterialeditor.h"
#include "qt/widgets/simulationeditor/dialogsimulationeditor.h"

/*!
 * \brief Run unit tests
 * \returns \c true if all unit tests success
 */
bool runTests();

/*!
 * \brief The main application method
 * \param argc Argument count
 * \param argv Arguments array
 * \returns Application execution result ( \c EXIT_SUCCESS or \c EXIT_FAILURE )
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("BasY");
    QCoreApplication::setApplicationName("Universe1");

    // QSettings().clear();

    // if (!runTests())
    //     return EXIT_FAILURE;
    // return EXIT_SUCCESS;

    // Universe1::Project::Project *p = new
    // Universe1::Project::Project("/home/basy/Universe1/projectWorkingDirectory/");
    // p->speech()->setSpeechTool("/home/basy/.local/bin/google_speech", {"-l", "en-us", "-o"});
    //// qDebug() << p->speech()->isToolValid();
    //// qDebug() << p->speech()->getAudioFileName("Car is blue !");
    // delete p;

    // Universe1::Project::MaterialDB db(Universe1::OpenGL::Material(Qt::red, Qt::green, Qt::blue, 32.0F, 1.0F));
    // Universe1::Widgets::MaterialEditor::DialogMaterialEditor dialog(&db);
    // return dialog.exec();

    // Universe1::Project::QSimulationNewtonCurrent *sim = new Universe1::Project::QSimulationNewtonCurrent("0");
    Universe1::Project::QSimulationNewtonByWave *sim = new Universe1::Project::QSimulationNewtonByWave("0");

    sim->setPrecision(Universe1::Project::QSimulation::PrecisionLongDouble);
    sim->setMaximumStepTime(0.1);
    sim->setCalculationStepCount(200);

    Universe1::Widgets::SimulationEditor::DialogSimulationEditor dialog(sim);
    return dialog.exec();

    // return EXIT_SUCCESS;
    // return app.exec();
}

#include "unit_tests/test_neutrinoobject.h"
#include "unit_tests/test_neutrinotimestamp.h"
#include "unit_tests/test_newton.h"
#include "unit_tests/test_spherecrosssection.h"
#include "unit_tests/test_vec3.h"

bool runTests()
{
    static const std::vector<QObject *> tests =  //
        {
            // new Test_Vec3(),
            new Test_Newton(),
            // new Test_SphereCrossSection(),
            // new Test_NeutrinoTimeStamp(),
            // new Test_NeutrinoObject(),
        };

    bool result = true;

    for (QObject *test : tests)
        if (QTest::qExec(test) != 0)
            result = false;

    return result;
}
