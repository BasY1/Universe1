#include "../Video/project.h"

#include "../Items/Text/itemtext.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

using namespace U1::Audio;
using namespace U1::Video;
using namespace U1::Items;
using namespace U1::Math;

static void mkFootage1(Project &project, const QString &_workDir);

/*!
 * \brief Universe 1 presentation video
 * \param _workDir Working directory
 * \return Success flag
 */
bool videoUniverse1(const QString &_workDir)
{

    Project project("Universe 1");

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

    mkFootage1(project, _workDir);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

static void mkFootage1(Project &project, const QString &_workDir)
{
    Footage *footage = project.addFootage("Footage 1");
    ScenarioAudioTTS *as = footage->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    // as->addSpeechSUBS(500, "A text example. ", 1000);

    footage->cameraPosition.initValue({-5, -1, 1});
}

}  // namespace Examples
}  // namespace U1
