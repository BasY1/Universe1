/*!
 * \file main.cpp
 * \author Michal Steller
 * \brief The main application method
 */

#include <QApplication>

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

    if (!runTests())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
    // return app.exec();
}

//#include "unit_tests/test_singularity.h"
#include "unit_tests/test_vec3.h"

#include "math/timestepdata.h"
template <typename T>
struct TimeStamp2 : public Universe1::Simulation::TimeStamp<T>
{
};

bool runTests()
{
    Universe1::Simulation::ObjectHistoryVector<float, TimeStamp2<float>> hist;
    Universe1::Simulation::ObjectHistoryVector<double, TimeStamp2<double>> hist2;

    hist.eventSource(1, 1, Universe1::Math::Vec3<float>(1, 1, 1));
    hist2.eventSource(1, 1, Universe1::Math::Vec3<double>(1, 1, 1));

    static const std::vector<QObject *> tests = {new Test_Vec3()};  //{new Test_Vec3(), new Test_Singularity()};

    bool result = true;

    for (QObject *test : tests)
        if (QTest::qExec(test) != 0)
            result = false;

    return result;
}
