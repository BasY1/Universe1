#include "../Video/project.h"

#include "../Items/Sphere/itemsphere.h"
#include "../Items/Items2D/item2dtext.h"

namespace U1 {
namespace Examples {

/*!
 * \brief Sphere item example
 * \param _workDir Working directory
 * \param _img Texture image file
 * \return Success flag
 */
bool exampleSphere(const QString &_workDir, const QString &_img = "")
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    Project project("Sphere example");

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
    static const float rot1 = 16.0 * M_PI;
    static const float rot2 = 2.0 * M_PI;

    Footage *footage1 = project.addFootage("Footage 1");

    ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());

    as->addSpeechSUBS(500, "A sphere example. ", 1000);

    ItemSphere *obj1 = footage1->add3D(new ItemSphere());

    obj1->arm.addRotated(dur, {}, {0, 0, 1}, rot1);

    if (QFile::exists(_img))
    {
        obj1->textureImage.initValue(_img);
        obj1->show.initValue(Sphere::SphereTextureOuter);
        obj1->show.setValue(dur / 2UL, Sphere::SphereTextureInner);
    }
    else
    {
        obj1->show.initValue(Sphere::SphereOuter);
        obj1->show.setValue(1000, Sphere::SphereInner);
        obj1->show.setValue(2000, Sphere::SphereTextureSoccerBall);
        obj1->show.setValue(3000, Sphere::SphereTextureSoccerEarth);
        obj1->show.setValue(4000, Sphere::SphereHidden);

        ItemSphereCut *obj2 = footage1->add3D(new ItemSphereCut());
        obj2->arm.addRotated(dur, {}, {0, 0, 1}, rot1);
        obj2->visible.initOff_On(4000);
        obj2->angleLonEnd.addFromLinearValue(4000, dur, 2.0 * M_PI);
        obj2->angleLatEnd.addFromLinearValue(4000, dur, M_PI);
    }

    obj1->stepWire.initValue(0.2f);
    obj1->radiusWire.initValue(0.02f);

    obj1->showWire.initValue(Sphere::SphereWireHidden);
    obj1->showWire.setValue(2000, Sphere::SphereWireLatLongStep);
    obj1->showWire.setValue(4000, Sphere::SphereWireLatLongFixed);
    obj1->showWire.setValue(6000, Sphere::SphereWireXYZ);

    footage1->addCamera("Camera 1", {+2, 0, 0});
    footage1->addCamera("Camera 2", {-2, 0, 0});

    footage1->add2D(new Item2DText("Info", "<font color=\"#FF0000\">Sphere</font> example", Math::_AlignTopCenter));

    footage1->cameraPosition.initValue({-3, -1, 1});
    footage1->cameraPosition.addFromRotatedAccelerated(dur / 8UL, (7UL * dur) / 8UL, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    footage1->minimalFootageDuration = dur;

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
