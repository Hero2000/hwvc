/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef HWVC_ANDROID_ALMESSAGE_H
#define HWVC_ANDROID_ALMESSAGE_H

#include "Object.h"

class AlLooper;

class AlHandler;

al_class(AlMessage) {
public:
    int32_t what = 0;
    int32_t arg1 = 0;
    int64_t arg2 = 0;
    string desc;
    Object *obj = nullptr;
    int16_t queueMode = QUEUE_MODE_NORMAL;
private:
    friend AlLooper;
    friend AlHandler;
    AlHandler *target = nullptr;

public:
    static AlMessage *obtain();

    static AlMessage *obtain(int32_t what);

    static AlMessage *obtain(int32_t what, Object *obj);

    static AlMessage *obtain(int32_t what, Object *obj, int16_t queueMode);

    AlMessage();

    AlMessage(int32_t what);

    AlMessage(int32_t what, Object *obj);

    AlMessage(int32_t what, Object *obj, int16_t queueMode);

    virtual ~AlMessage();

    void *tyrUnBox();

public:
    static const int16_t QUEUE_MODE_NORMAL;
    static const int16_t QUEUE_MODE_UNIQUE;
    static const int16_t QUEUE_MODE_FIRST_ALWAYS;
    static const int16_t QUEUE_MODE_CLEAR;
};


#endif //HWVC_ANDROID_ALMESSAGE_H