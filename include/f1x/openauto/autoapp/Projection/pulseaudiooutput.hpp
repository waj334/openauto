#ifndef PULSEAUDIOOUTPUT_HPP
#define PULSEAUDIOOUTPUT_HPP

#include <f1x/openauto/autoapp/Projection/IAudioOutput.hpp>
#include <f1x/openauto/autoapp/Projection/SequentialBuffer.hpp>
#include <f1x/openauto/autoapp/Configuration/Configuration.hpp>

#include <soundio/soundio.h>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace projection
{

class PulseAudioOutput: public QObject, public IAudioOutput
{
Q_OBJECT
public:
    PulseAudioOutput(f1x::openauto::autoapp::configuration::Configuration conf, uint32_t channelCount, uint32_t sampleSize, uint32_t sampleRate);
    bool open() override;
    void write(aasdk::messenger::Timestamp::ValueType, const aasdk::common::DataConstBuffer &buffer);
    void start() override;
    void stop() override;
    void suspend() override;
    uint32_t getSampleSize() const override;
    uint32_t getChannelCount() const override;
    uint32_t getSampleRate() const override;

signals:
    void startPlayback();
    void suspendPlayback();
    void stopPlayback();

protected slots:
    void createAudioOutput();
    void onStartPlayback();
    void onSuspendPlayback();
    void onStopPlayback();

private:
    struct SoundIo *pSoundio;
    struct SoundIoDevice *pDevice;
    struct SoundIoOutStream *pOutStream;

    f1x::openauto::autoapp::configuration::Configuration mConf;

    SoundIoFormat mFormat;
    SequentialBuffer mAudioBuffer;
    bool playbackStarted_;
};

}
}
}
}

#endif // PULSEAUDIOOUTPUT_HPP
