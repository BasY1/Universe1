/*!
 * \file src/main.cpp
 * \brief The \b main procedure file
 */

#include <QApplication>

#include "UnitTests/test_math.cc"

/*!
 * \brief The \b main procedure
 * \param argc Argument count
 * \param argv Argument array
 * \return \c EXIT_SUCCESS or \c EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_UNUSED(app)

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    // EXIT_SUCCESS;
}
