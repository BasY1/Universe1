/*!
 * \file main.cpp
 * \author Michal Steller
 * \brief The main application method
 */

#include <QApplication>

/*!
 * \brief Run unit tests
 * \return \c true if all unit tests success
 */
bool runTests();

/*!
 * \brief The main application method
 * \param argc Argument count
 * \param argv Arguments array
 * \return Application execution result ( \c EXIT_SUCCESS or \c EXIT_FAILURE )
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!runTests())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
    // return app.exec();
}

#include "unit_tests/test_vec3.h"

bool runTests()
{
    static const std::vector<QObject *> tests = {new Test_Vec3()};

    bool result = true;

    for (QObject *test : tests)
        if (QTest::qExec(test) != 0)
            result = false;

    return result;
}
