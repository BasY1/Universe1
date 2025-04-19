#include "../Video/project.h"

#include "../Items/Line/itemline.h"
#include "../Items/Line/itemarc.h"
#include "../Items/Line/itemspin.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Line item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool exampleLine(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Line example");

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
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A line example.");

    ItemLine *obj1 = footage1->add3D(new ItemLine());
    obj1->arrowStart.initOff_On(1000);
    obj1->arrowEnd.initOff_On(2000);
    obj1->pattern.setValue(3000, PATTERN_DOTS_1);
    obj1->radius.initValue(0.03);
    obj1->arrowLength.initValue(0.2);
    obj1->arrowRadius.initValue(0.1);
    obj1->length.addFromLinearValue(4000, 5000, 2.0f);
    obj1->text.setValue(4000, "$$$LENGTH$$$");
    obj1->textPosition.initValue(Line::LineTextEnd);
    obj1->textFollowCamera.initOn_Off(6000);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Line</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-5, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

/*!
 * \brief Line arc item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool exampleArc(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Line arc example");

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
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A line arc example.");

    ItemArc *obj1 = footage1->add3D(new ItemArc());
    obj1->arrowStart.initOff_On(1000);
    obj1->arrowEnd.initOff_On(2000);
    obj1->pattern.setValue(3000, PATTERN_DOTS_1);
    obj1->radiusLine.initValue(0.03);
    obj1->arrowLength.initValue(0.2);
    obj1->arrowRadius.initValue(0.1);
    obj1->angle.initValue(0);
    obj1->angle.addLinearValue(dur, 3.0 * M_PI_2);
    obj1->text.setValue(4000, "$$$ANGLE_DEG$$$°");
    obj1->textPosition.initValue(Line::LineTextHidden);
    obj1->textPosition.setValue(4000, Line::LineTextCenter);
    obj1->textPosition.setValue(5000, Line::LineTextCenter);
    obj1->textPosition.setValue(6000, Line::LineTextEnd);
    obj1->textFollowCamera.initOn_Off(7000);

    ItemLine *obj2 = footage1->add3D(new ItemLine());
    obj2->arrowStart.initOff_On(1000);
    obj2->arrowEnd.initOff_On(2000);
    obj2->pattern.setValue(3000, PATTERN_DOTS_1);
    obj2->radius.initValue(0.03);
    obj2->arrowLength.initValue(0.2);
    obj2->arrowRadius.initValue(0.1);
    obj2->length.initValue(0);
    obj2->length.addLinearValue(dur, 1.5);
    obj2->text.setValue(4000, "$$$LENGTH$$$°");
    obj2->textPosition.initValue(Line::LineTextHidden);
    obj2->textPosition.setValue(4000, Line::LineTextCenter);
    obj2->textPosition.setValue(5000, Line::LineTextCenter);
    obj2->textPosition.setValue(6000, Line::LineTextEnd);
    obj2->textFollowCamera.initOn_Off(7000);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Line ARC</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

/*!
 * \brief Line spin item example
 * \param _workDir Working directory
 * \return Success flag
 */
bool exampleSpin(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Line spin example");

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
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A spin line example.");

    ItemSpin *obj1 = footage1->add3D(new ItemSpin());
    obj1->pattern.setValue(3000, PATTERN_DOTS_1);
    obj1->radius.initValue(0.03);
    obj1->arrowLength.initValue(0.2);
    obj1->arrowRadius.initValue(0.1);
    obj1->arrowOffsetAxis.initValue(0.2);
    obj1->length.addLinearValue(dur, 2.0);
    obj1->phase.addLinearValue(dur, float(dur / 1000) * 2.0 * M_PI);
    obj1->text.setValue(4000, "$$$ANGLE_DEG$$$°");
    obj1->textPosition.initValue(Line::LineTextHidden);
    obj1->textPosition.setValue(4000, Line::LineTextCenter);
    obj1->textPosition.setValue(5000, Line::LineTextCenter);
    obj1->textPosition.setValue(6000, Line::LineTextEnd);
    obj1->textFollowCamera.initOn_Off(7000);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Line SPIN</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
