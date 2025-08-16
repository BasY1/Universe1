#include "../Video/project.h"

#include "../Items/Sphere/itemsphere.h"
#include "../Items/Items2D/item2dtext.h"

// #include "../Items/Line/itemline.h"
#include "../Items/BodyParts/Eye/itemeye.h"
#include "../Items/BodyParts/Head/itemhead.h"

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

bool exampleBodyEyeBall(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    static const size_t dur = 1000UL;
    // static const float rot1 = 16.0 * M_PI;
    static const float rot2 = 0.9 * M_PI_2;  // 2.0 * M_PI;

    Project project("Eye example");

    Footage *footage1 = project.addFootage("Footage 1");
    // ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    // as->addSpeechSUBS(500, "An eye ball example. ", 1000);

    // footage1->add3D(new ItemCoordAxis());

    ItemEye *obj1 = footage1->add3D(new ItemEye());

    obj1->eyeBall.quality.initValue(31);
    obj1->eyeBall.radius.initValue(0.4f);

    obj1->eyeBall.materialPupil.initValue(Qt::magenta);

    obj1->eyeBall.offsetPupil.addFromLinearValue(600, 900, 0.75f);

    obj1->eyeBall.angleLidUp.addLinearValue(dur, M_PI);
    obj1->eyeBall.angleLidBottom.addLinearValue(dur, M_PI);

    footage1->cameraPosition.initValue({1, -0.3, 0.5});
    footage1->cameraPosition.addFromRotatedAccelerated(300, 600, {}, {0, 0, 1}, rot2, 0.1, 0.1);

    footage1->minimalFootageDuration = dur;

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

bool exampleBodyHead(const QString &_workDir)
{
    using namespace U1::Audio;
    using namespace U1::Video;
    using namespace U1::Items;
    using namespace U1::Math;

    static const size_t dur = 1000UL;
    static const float rot1 = 2.0 * M_PI;
    // static const float rot2 = 0.25 * M_PI_2;

    Project project("Eye example");

    Footage *footage1 = project.addFootage("Footage 1");
    footage1->minimalFootageDuration = dur;

    // ScenarioAudioTTS *as = footage1->addAudio_espeak("TTS", _workDir + "espeak" + QDir::separator());
    // as->addSpeechSUBS(500, "An eye ball example. ", 1000);

    // footage1->add3D(new ItemCoordAxis());
    ItemHead *i1 = footage1->add3D(new ItemHead());
    // i1->eyeRight.materialIris.initValue(Qt::red);
    // i1->nose.material.initValue(Qt::magenta);
    // i1->chin.material.initValue(Qt::blue);
    // i1->forehead.material.initValue(Qt::darkMagenta);
    // i1->eyeRight.materialEyeliner.initValue(Qt::yellow);
    // i1->eyeLeft.materialEyeliner.initValue(Qt::yellow);
    // i1->eyeRight.materialLid.initValue(Qt::red);
    // i1->eyeLeft.materialLid.initValue(Qt::cyan);
    // i1->nose.anglePosUp.addLinearValue(dur / 2, Math::toRad(30.0f));
    // i1->nose.anglePosUp.addLinearValue(dur, Math::toRad(-30.0f));
    // i1->nose.angleRotSide.addLinearValue(dur / 2, Math::toRad(30));
    // i1->nose.angleRotSide.addLinearValue(dur, Math::toRad(-30));

    // i1->eyeRight.angleSide.addLinearValue(dur, Math::toRad(20.0f));
    // i1->eyeLeft.angleSide.addLinearValue(dur, Math::toRad(20.0f));

    // i1->eyeRight.angleUp.addLinearValue(dur, Math::toRad(10.0f));
    // i1->eyeLeft.angleUp.addLinearValue(dur, Math::toRad(10.0f));

    i1->eyeRight.angleLid.addLinearValue(dur / 10UL, 0.0f);
    i1->eyeLeft.angleLid.addLinearValue(dur / 10UL, 0.0f);

    i1->eyeRight.angleLid.addLinearValue(dur / 5UL, i1->eyeRight.angleLid.getInitValue());
    i1->eyeLeft.angleLid.addLinearValue(dur / 5UL, i1->eyeLeft.angleLid.getInitValue());

    i1->mouth.pointRight.angleUp.addFromLinearValue((3UL * dur) / 10UL, (4UL * dur) / 10UL, Math::toRad(-5.0f));
    i1->mouth.pointLeft.angleUp.addFromLinearValue((3UL * dur) / 10UL, (4UL * dur) / 10UL, Math::toRad(-5.0f));

    i1->mouth.pointRight.angleUp.addLinearValue((5UL * dur) / 10UL, Math::toRad(3.0f));
    i1->mouth.pointLeft.angleUp.addLinearValue((5UL * dur) / 10UL, Math::toRad(3.0f));

    i1->mouth.pointRight.angleUp.addFromLinearValue((7UL * dur) / 10UL, (8UL * dur) / 10UL, Math::toRad(-3.0f));
    i1->mouth.pointLeft.angleUp.addFromLinearValue((7UL * dur) / 10UL, (8UL * dur) / 10UL, Math::toRad(-3.0f));

    i1->mouth.pointRight.angleUp.addFromLinearValue((9UL * dur) / 10UL, dur, Math::toRad(3.0f));
    i1->mouth.pointLeft.angleUp.addFromLinearValue((9UL * dur) / 10UL, dur, Math::toRad(3.0f));

    i1->mouth.pointDownCenter.angleUp.addFromLinearValue(
        (7UL * dur) / 10UL, (8UL * dur) / 10UL, i1->mouth.pointDownCenter.angleUp.getInitValue() - Math::toRad(10.0f));
    i1->mouth.pointDownCenter.angleUp.addFromLinearValue(
        (9UL * dur) / 10UL, dur, i1->mouth.pointDownCenter.angleUp.getInitValue());

    footage1->cameraPosition.initValue({2, -1, 0.5});
    // footage1->cameraPosition.addLinearValue(dur, {3, -1, 0});
    footage1->cameraPosition.addRotatedAccelerated(dur, {}, {0, 0, 1}, rot1, 0.1, 0.1);
    // footage1->cameraPosition.addRotatedMovedAccelerated(dur, {}, {0, 0, 1}, rot1, -1, 0.1, 0.1);

    return project.createVideo(_workDir + "Video" + QDir::separator(), _workDir + "video.avi");
}

}  // namespace Examples
}  // namespace U1
