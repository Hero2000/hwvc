/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HARDWAREVIDEOCODEC_HWAUDIOINPUT_H
#define HARDWAREVIDEOCODEC_HWAUDIOINPUT_H

#include "HwStreamMedia.h"
#include "AsynAudioDecoder.h"
#include "HwAudioFrame.h"

class HwAudioInput : public HwStreamMedia {
public:
    HwAudioInput(string alias);

    virtual ~HwAudioInput();

    bool onDestroy(AlMessage *msg) override;

    bool onCreate(AlMessage *msg) override;

    bool eventSetSource(AlMessage *msg) override;

    bool eventStart(AlMessage *msg) override;

    bool eventPause(AlMessage *msg) override;

    bool eventStop(AlMessage *msg) override;

    bool eventSeek(AlMessage *msg) override;

    bool eventLoop(AlMessage *msg);

    void setPlayListener(function<void(int64_t, int64_t)> listener);

private:
    void loop();

    HwResult grab();

    void playFrame(HwAudioFrame *frame);

    void processPlayListener(int64_t us);

    string getPath();

private:
    const int INTERVAL_PROGRESS = 500000;
    AbsAudioDecoder *decoder = nullptr;
    PlayState playState = STOP;
    SimpleLock simpleLock;
    SimpleLock playTimeLock;
    HwAudioFrame *frame = nullptr;
    int64_t lastPlayPts = INT64_MIN;

    /** Listeners */
    function<void(int64_t, int64_t)> playListener = nullptr;

    /** setting */
    bool enableLoop = true;
};


#endif //HARDWAREVIDEOCODEC_HWAUDIOINPUT_H
