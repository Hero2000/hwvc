/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef HARDWAREVIDEOCODEC_HWADBMEDIAFRAME_H
#define HARDWAREVIDEOCODEC_HWADBMEDIAFRAME_H

#include "HwAbsFrame.h"

class HwAbsMediaFrame : public HwAbsFrame {
public:
    enum Type {
        VIDEO,
        AUDIO,
    };

    HwAbsMediaFrame(Type type);

    virtual ~HwAbsMediaFrame();

    void setFormat(uint16_t format);

    uint16_t getFormat();

    Type getType();

    void setPts(int64_t pts);

    int64_t getPts();

    bool isVideo();

    bool isAudio();

    /**
     * us
     */
    virtual uint64_t duration()=0;

    virtual HwAbsMediaFrame *clone()=0;

    virtual void clone(HwAbsMediaFrame *src)=0;

private:
    Type type = Type::AUDIO;
    uint16_t format = 0;
    int64_t pts;
};


#endif //HARDWAREVIDEOCODEC_HWADBMEDIAFRAME_H