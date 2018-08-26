#include <QApplication>
#include <f1x/openauto/autoapp/Projection/pulseaudiooutput.hpp>
#include <f1x/openauto/Common/Log.hpp>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace projection
{

PulseAudioOutput::PulseAudioOutput(f1x::openauto::autoapp::configuration::Configuration conf, uint32_t channelCount, uint32_t sampleSize, uint32_t sampleRate) :
    mConf(conf),
    playbackStarted_(false)
{
    pSoundio = soundio_create();
    pDevice = nullptr;

    switch (sampleSize) {
        case 16:
            mFormat = SoundIoFormatS16LE;
            break;
        case 24:
            mFormat = SoundIoFormatS24LE;
            break;
        case 32:
            mFormat = SoundIoFormatS32LE;
            break;
    }

    this->moveToThread(QApplication::instance()->thread());
    connect(this, &PulseAudioOutput::startPlayback, this, &PulseAudioOutput::onStartPlayback);
    connect(this, &PulseAudioOutput::suspendPlayback, this, &PulseAudioOutput::onSuspendPlayback);
    connect(this, &PulseAudioOutput::stopPlayback, this, &PulseAudioOutput::onStopPlayback);

    QMetaObject::invokeMethod(this, "createAudioOutput", Qt::BlockingQueuedConnection);
}

void PulseAudioOutput::createAudioOutput() {
    OPENAUTO_LOG(debug) << "[PulseAudioOutput] create.";
    soundio_connect_backend(pSoundio, SoundIoBackendPulseAudio);
    soundio_flush_events(pSoundio);

    int c = soundio_output_device_count(pSoundio);

    for (int i = 0; i < c; ++i) {
        auto dev = soundio_get_output_device(pSoundio, i);
        QString id = dev->id;

        if (id.compare(mConf.getAudioOutputDevice().toString()) == 0) {
            pDevice = dev;
        }
    }

    if (pDevice != nullptr) {
        pOutStream = soundio_outstream_create(pDevice);
    }
}

bool PulseAudioOutput::open() {
    return mAudioBuffer.open(QIODevice::ReadWrite);
}

void PulseAudioOutput::write(aasdk::messenger::Timestamp::ValueType, const aasdk::common::DataConstBuffer& buffer)
{
    mAudioBuffer.write(reinterpret_cast<const char*>(buffer.cdata), buffer.size);
}

void PulseAudioOutput::start()
{
    emit startPlayback();
}

void PulseAudioOutput::stop()
{
    emit stopPlayback();
}

void PulseAudioOutput::suspend()
{
    emit suspendPlayback();
}

uint32_t PulseAudioOutput::getSampleSize() const
{
    uint32_t sz = 0;

    switch (mFormat) {
        case SoundIoFormatS16LE:
            sz = 16;
            break;
        case SoundIoFormatS24LE:
            sz = 24;
            break;
        case SoundIoFormatS32LE:
            sz = 32;
            break;
    }

    return sz;
}

uint32_t PulseAudioOutput::getChannelCount() const
{
    if (pDevice != nullptr)
        return pOutStream->layout.channel_count;

    return 0;
}

uint32_t PulseAudioOutput::getSampleRate() const
{
    if (pDevice != nullptr)
        return pOutStream->sample_rate;

    return 0;
}

void PulseAudioOutput::onStartPlayback()
{
    if(!playbackStarted_)
    {

        playbackStarted_ = true;
    }
    else
    {

    }
}

void PulseAudioOutput::onSuspendPlayback()
{

}

void PulseAudioOutput::onStopPlayback()
{
    if(playbackStarted_)
    {

        playbackStarted_ = false;
    }
}

}
}
}
}
