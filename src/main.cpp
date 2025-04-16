/*!
 * \file src/main.cpp
 * \brief The \b main procedure file
 */

#include <QApplication>
#include <QStandardPaths>

#ifdef U1_UNIT_TESTS
#include "UnitTests/test_math.cc"
#else
#include "Examples/example_triangle.cc"
#include "Examples/example_rectangle.cc"
#endif

/*!
 * \brief The \b main procedure
 * \param argc Argument count
 * \param argv Argument array
 * \return \c EXIT_SUCCESS or \c EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Universe1");
    Q_UNUSED(app)

#ifdef U1_UNIT_TESTS
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else

    static const QString workDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
        QDir::separator() + "U1" + QDir::separator();

    if (U1::Examples::exampleRectangle(workDir))
    {
        U1::Audio::SettingsAudio::runProcess("/usr/bin/vlc", {"--loop", workDir + "video.avi"});
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;

#endif
}
