#include "../Video/project.h"

#include "../Items/Path/itempath.h"
#include "../Items/Path/itempathspiral.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Path item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool examplePath(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Path example");

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

    static const size_t dur = 4000UL;
    // static const float rot1 = 16.0 * M_PI;
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    as->addSpeechSUBS(500, "A path example. ", 1000);

    const std::vector<OrientF> p1 = {
        OrientF({0, 0.5, 0.0}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}),
        OrientF({0, 0.5, 0.2}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}),
        OrientF({0, 0.5, 0.4}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}),
        OrientF({0, 0.5, 0.6}, {0, 0, 1}, {1, 0, 0}, {0, 1, 0}),
    };

    const std::vector<std::pair<OrientF, ColorRGB>> p2 = {
        {OrientF({0, -0.5, 0.0}, {0, 0, 1}, {1, 0, 0}), {Qt::red}},
        {OrientF({0, -0.5, 0.2}, {0, 0, 1}, {1, 0, 0}), {Qt::magenta}},
        {OrientF({0, -0.5, 0.4}, {0, 0, 1}, {1, 0, 0}), {Qt::blue}},
        {OrientF({0, -0.5, 0.6}, {0, 0, 1}, {1, 0, 0}), {Qt::cyan}},
    };

    ItemPath *obj1 = footage1->add3D(new ItemPath(p1));
    ItemPathColor *obj2 = footage1->add3D(new ItemPathColor(p2));

    obj1->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);
    obj2->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);
    obj1->radius.initValue(0.05);
    obj2->radius.initValue(0.05);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Path</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-2, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

/*!
 * \brief Spiral path item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool examplePathSpiral(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Spiral path example");

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

    static const size_t dur = 4000UL;
    // static const float rot1 = 16.0 * M_PI;
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    as->addSpeechSUBS(500, "A spiral path example. ", 1000);

    ItemPathSpiral *obj1 = footage1->add3D(new ItemPathSpiral());
    ItemPathSpiralRainbow *obj2 = footage1->add3D(new ItemPathSpiralRainbow());

    obj1->center.initValue({0, 1, 0});
    obj2->center.initValue({0, -1, 0});

    obj1->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);
    obj2->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);

    obj1->radiusLine.initValue(0.05);
    obj2->radiusLine.initValue(0.05);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(
        new Item2DText("Info", "<font color=\"#FF0000\">SPIRAL path</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
