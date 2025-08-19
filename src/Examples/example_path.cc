#include "../Video/project.h"

#include "../Items/Line/itemline.h"
#include "../Items/Path/itempath.h"
#include "../Items/Path/itempathspiral.h"
#include "../Items/Path/itempathspiralarc.h"
#include "../Items/Path/itempathbezier.h"
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

    ItemPathSpiral *obj1 = footage1->add3D(new ItemPathSpiral("S1", {0, 1, 0}));
    ItemPathSpiralRainbow *obj2 = footage1->add3D(new ItemPathSpiralRainbow("S2", {0, -1, 0}));

    obj1->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);
    obj2->pattern.setValue(dur / 2UL, PATTERN_DOTS_1);

    obj1->radiusLine.initValue(0.05);
    obj2->radiusLine.initValue(0.05);

    // footage1->addCamera("Camera 1", {+2, 0, 0});
    // footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(
        new Item2DText("Info", "<font color=\"#FF0000\">SPIRAL path</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

/*!
 * \brief Spiral path item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool examplePathSpiralArc(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Spiral-arc path example");

    static const size_t dur = 1000UL;
    static const float rot = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    // ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    // as->addSpeechSUBS(500, "A spiral arc path example. ", 1000);

    static const float arm = 5;
    static const float a1 = 0;
    static const float a2 = 6.0f * M_PI;
    static const Vec3F C = {0, -5, 0};
    static const Vec3F N1 = {1, 0, 0};
    static const Vec3F N2 = {0, 1, 0};
    ItemPathSpiralArc *o1 =
        footage1->add3D(new ItemPathSpiralArc("S1", C, N1, N2, true, a1, a2, (arm - 2.0) * 0.25, (arm - 2.0)));
    ItemPathSpiralArc2Color *o2 =
        footage1->add3D(new ItemPathSpiralArc2Color("S2", C, N1, N2, true, a1, a2, arm * 0.25, arm));
    ItemPathSpiralArcRainbow *o3 =
        footage1->add3D(new ItemPathSpiralArcRainbow("S3", C, N1, N2, true, a1, a2, (arm + 2.0) * 0.25, (arm + 2.0)));

    o1->radiusLine.initValue(0.05);
    o2->radiusLine.initValue(0.05);
    o3->radiusLine.initValue(0.05);

    o1->pattern.setValue(dur / 4UL, PATTERN_DASH_L);
    o2->pattern.setValue(dur / 4UL, PATTERN_DASH_S);
    o3->pattern.setValue(dur / 4UL, PATTERN_DASH_1);

    o1->pattern.setValue(dur / 2UL, PATTERN_DASH_DOT_DOT_1);
    o2->pattern.setValue(dur / 2UL, PATTERN_DASH_DOT_DOT_2);
    o3->pattern.setValue(dur / 2UL, PATTERN_DASH_DOT_DOT_3);

    o1->pattern.setValue(3UL * dur / 4UL, PATTERN_DASH_DOT_1);
    o2->pattern.setValue(3UL * dur / 4UL, PATTERN_DASH_DOT_2);
    o3->pattern.setValue(3UL * dur / 4UL, PATTERN_DASH_DOT_3);

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">SPIRAL-ARC path</font> example", _AlignTopRight));

    footage1->add3D(new ItemCoordAxis());

    footage1->cameraPosition.initValue({-5, -1, 1});
    footage1->cameraPosition.addRotatedAccelerated(dur, {}, {0, 0, 1}, rot, 0.1, 0.1);
    // footage1->cameraPosition.addFromRotatedAccelerated(dur / 2UL, dur, {}, {0, 0, 1}, rot, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

/*!
 * \brief Spiral path item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool examplePathBezier(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Bezier path example");

    static const size_t dur = 1000UL;
    static const float rot = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ItemPathBezier *o1 = footage1->add3D(new ItemPathBezier("B1"));
    ItemPathBezier2Color *o2 = footage1->add3D(new ItemPathBezier2Color("B2", {0, -1, 0}, {0, -1, 1}));
    ItemPathBezierRainbow *o3 = footage1->add3D(new ItemPathBezierRainbow("B3", {0, 1, 0}, {0, 1, 1}));

    o1->weight1.addLinearValue(dur, 0.5);
    o1->weight2.addLinearValue(dur, 2.0);

    o2->weight1.addLinearValue(dur, 0.5);
    o3->weight2.addLinearValue(dur, 2.0);

    footage1->cameraPosition.initValue({2, -1, 1.5});
    footage1->cameraPosition.addRotatedAccelerated(dur / 2, {}, {0, 0, 1}, rot, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
