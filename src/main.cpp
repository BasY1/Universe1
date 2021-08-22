/*!
 * \file main.cpp
 * \author Michal Steller
 * \brief The main application method
 */

#include <QApplication>

#include "qt/widgets/materialeditor/dialogmaterialeditor.h"

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

    // QSettings().clear();

    // if (!runTests())
    //    return EXIT_FAILURE;

    Universe1::OpenGL::MaterialDB db(Universe1::OpenGL::Material(Qt::red, Qt::green, Qt::blue, 32.0F, 1.0F));
    Universe1::Widgets::MaterialEditor::DialogMaterialEditor dialog(&db);
    return dialog.exec();

    // return EXIT_SUCCESS;
    // return app.exec();
}

#include "unit_tests/test_newton.h"
#include "unit_tests/test_vec3.h"

bool runTests()
{
    static const std::vector<QObject *> tests = {new Test_Vec3(), new Test_Newton()};

    bool result = true;

    for (QObject *test : tests)
        if (QTest::qExec(test) != 0)
            result = false;

    return result;
}
