#include "../Video/project.h"

#include "../Items/Simulation/itemnewtonsimulation.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Simulation-Newton item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool exampleSimulationNewton(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Simulation-Newton example");

    // ItemDefaultValues::sphereQuality = 15UL;
    // ItemDefaultValues::lineQuality = 3UL;
    // ItemDefaultValues::pixelSize = 0.001F;
    // ItemDefaultValues::textPixelSize = 0.01F;
    // ItemDefaultValues::lineRadius = 0.005F;
    // ItemDefaultValues::arrowLength = 0.075F;
    // ItemDefaultValues::arrowRadius = 0.025F;
    // ItemDefaultValues::lineColor = QColor(255, 255, 255);
    // ItemDefaultValues::textColor = QColor(255, 255, 255);
    // ItemDefaultValues::textFont = "Sans Serif";
    // ItemDefaultValues::fontHeight = 24;

    // project.settingsOpenGL.useGlBlend = true;
    // project.settingsOpenGL.useGlSamples = 4U;

    // project.settingsSubtitles.useSubtitles = true;
    // project.settingsSubtitles.upperCase = false;
    // project.settingsSubtitles.fontColor = Qt::white;
    // project.settingsSubtitles.fontFamily = "Sans Serif";
    // project.settingsSubtitles.fontHeight = 24;
    // project.settingsSubtitles.bottomOffset = 24;

    // project.settingsVideo.imgSuffix = "png";
    // project.settingsVideo.videoCodec = "libx264";
    // project.settingsVideo.videoPixelFormat = "yuv420p";
    // project.settingsVideo.resolution = {1920, 1080};
    // project.settingsVideo.frameDuration = (1000.0f / 30.0f);

    // project.settingsAudio.channels = 1;
    // project.settingsAudio.sampleRate = 44100;
    // project.settingsAudio.sampleFormat = QAudioFormat::Int16;
    // project.settingsAudio.fileSuffix = "wav";

    // project.setupMinimum();
    // project.setupSmall();
    // project.setupFullHD();
    // project.setup4K();
    // project.setup8K();

    static const size_t dur = 8000UL;
    // static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A Newtonian simulation example. ", 1000);

    ItemNewtonSimulation *obj1 = footage1->add3D(new ItemNewtonSimulation(
        {NewtonSimD::simulationGalaxyNewton(_workDir.toStdString() + "simulation.data",
                                            1,
                                            1001,
                                            2UL + size_t(float(dur) / project.settingsVideo.frameDuration),
                                            true,
                                            0.001,
                                            0.01,
                                            1.0,
                                            0.1,
                                            100.0,
                                            0.9,
                                            1.1),
         true}));
    obj1->time.addLinearValue(dur, obj1->latestSimulationTimestep());
    obj1->colorMode.initValue(NewtonSimulation::SimulationColorConstant);
    // obj1->colorMode.setValue(1000, NewtonSimulation::SimulationColorVelocityRainbow);
    // obj1->colorMode.setValue(2000, NewtonSimulation::SimulationColorAccelRainbow);
    obj1->colorMode.setValue(1000, NewtonSimulation::SimulationColorMassGrayscale);
    obj1->colorMode.setValue(3000, NewtonSimulation::SimulationColorMassRainbow);
    obj1->maxPointSize.initValue(6U);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(
        new Item2DText("Info", "<font color=\"#FF0000\">Newtonian</font> simulation example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    // footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
