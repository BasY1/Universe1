#include "../Video/project.h"

#include "../Items/Hand/itemhand.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Hand item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool exampleHand(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Hand example");

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

    static const size_t dur = 2000UL;
    static const float rot2 = 3.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A hand example. ", 1000);

    ItemHand *obj1 = footage1->add3D(new ItemHand());
    ItemHand *obj2 = footage1->add3D(new ItemHand());

    obj1->quality.initValue(3);
    obj2->quality.initValue(3);

    obj2->rightHand.initOff();

    obj1->materialBody.initValue(Qt::cyan);
    obj2->materialBody.initValue(Qt::yellow);

    obj1->center.initValue({0, 1, 0});
    obj2->center.initValue({0, -1, 0});

    obj1->normal.initValue({1, 0, 0});
    obj2->normal.initValue({-1, 0, 0});

    obj1->arm.initValue({0, 1, 0});
    obj2->arm.initValue({0, -1, 0});

    obj1->openThumb.addLinearValue(dur, 0);
    obj1->openIndex.addLinearValue(dur, 0);
    obj1->open345.addLinearValue(dur, 0);

    obj2->openThumb.addLinearValue(dur, 0);
    obj2->openIndex.addLinearValue(dur, 0);
    obj2->open345.addLinearValue(dur, 0);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Hand</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
