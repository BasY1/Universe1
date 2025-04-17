#include "../Video/project.h"

#include "../Items/Rectangle/itemrectangle.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Rectangle item example
 * \param _workDir Working directory
 * \param _img Texture image file
 * \return Success flag
 */
bool exampleRectangle(const QString &_workDir, const QString &_img = "")
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Rectangle example");

    // ItemDefaultValues::sphereQuality = 15UL;
    // ItemDefaultValues::lineQuality = 3UL;
    // ItemDefaultValues::pixelSize = 0.001F;
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
    static const float rot1 = 16.0 * M_PI;
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A rectangle example. ", 1000);

    ItemRectangle *rect1 = footage1->add3D(new ItemRectangle());
    ItemRectangleCamera *rect2 = footage1->add3D(new ItemRectangleCamera());

    if (QFile::exists(_img))
    {
        rect1->show.initValue(Rectangle::RectangleTextureFrontBack);
        rect2->show.initValue(Rectangle::RectangleCameraTexture);
        rect1->textureImage.initValue(_img);
        rect2->textureImage.initValue(_img);
    }
    else
    {
        rect1->show.initValue(Rectangle::RectangleVertexFrontBack);
        rect2->show.initValue(Rectangle::RectangleCameraVertex);
    }

    rect1->stepWire.initValue(0.2f);
    rect2->stepWire.initValue(0.2f);

    rect1->showWire.initValue(Rectangle::RectangleWireFull);
    rect2->showWire.initValue(Rectangle::RectangleWireFull);

    rect1->arm.addRotated(dur, {}, {1, 0, 0}, rot1);

    rect2->spin.addLinearValue(dur, rot1);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Rectangle</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-5, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
