/*!
 * \file unit_test/main.cpp
 * \author Michal Steller
 * \brief The main application that run all registered test cases
 */

#include <QCoreApplication>

#include "unit_test/test_vec3.h"

//#include "unit_test/test_metaclassinfo.h"
//#include "unit_test/test_metaproperty.h"
//#include "unit_test/test_qtmeta.h"

// #include "unit_test/test_neutrinoobject.h"
// #include "unit_test/test_neutrinotimestamp.h"
// #include "unit_test/test_newton.h"
// #include "unit_test/test_spherecrosssection.h"
// #include "unit_test/test_spiral.h"

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
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("BasY");
    QCoreApplication::setApplicationName("Universe1_tests");

    using namespace Universe1::UnitTest;
    // qRegisterMetaType<Universe1::UnitTest::Test_MetaClassInfoObject1 *>();
    // qRegisterMetaType<Test_MetaPropertyObject1 *>("Test_MetaPropertyObject1*");
    // qRegisterMetaType<Test_MetaPropertyObject2 *>("Test_MetaPropertyObject2*");
    // qRegisterMetaType<Test_MetaPropertyObject1 *>();
    // qRegisterMetaType<Universe1::UnitTest::Test_MetaPropertyObject2 *>();

    // QRegExp re("(\\w+)(\\()(\\d+)(\\))");
    // QStringList texts = {"aaa_Aaa(0)",  //
    //                     "aaaAaa(1)",
    //                     "aaaAaa(-1)",
    //                     "aaaAaa()",
    //                     "aaaAaa(0]",
    //                     "lolo"};
    //
    // for (const auto &t : texts)
    //{
    //    qDebug() << (re.indexIn(t) >= 0 && re.captureCount() == 4);
    //}

    // qDebug() << QMetaType(1025).name();
    // qDebug() << QMetaType(1025).flags();

    static const std::vector<QObject *> tests = {
        new Universe1::UnitTest::Test_Vec3(),  //
        // new Universe1::UnitTest::Test_MetaClassInfo(),  //
        // new Universe1::UnitTest::Test_MetaProperty(),
        // new Universe1::UnitTest::Test_QtMeta(),  //
        // new Test_Newton(),
        // new Test_SphereCrossSection(),
        // new Test_NeutrinoTimeStamp(),
        // new Test_NeutrinoObject(),
    };

    bool result = true;

    for (QObject *test : tests)
        if (QTest::qExec(test) != 0)
            result = false;
    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
