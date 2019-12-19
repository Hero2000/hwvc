/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "AlQuadDrawer.h"

AlQuadDrawer::AlQuadDrawer() : HwNormalFilter() {

}

AlQuadDrawer::~AlQuadDrawer() {

}

bool AlQuadDrawer::prepare(TextureAllocator *texAllocator) {
    if (cover) {
        texAllocator->recycle(&cover);
    }
    int size = 2;
    uint8_t data[size * size * 4];
    memset(data, 255, size * size * 4);
    data[3] = 128;
    data[7] = 128;
    data[11] = 128;
    data[15] = 128;
    cover = texAllocator->alloc(data, size, size, GL_RGBA);
    return HwNormalFilter::prepare();
}

void AlQuadDrawer::setQuad(AlQuad &quad) {
    this->vertex[0] = quad.leftBottom().x * 2.0f - 1.0f;
    this->vertex[1] = quad.leftBottom().y * 2.0f - 1.0f;
    this->vertex[2] = quad.rightBottom().x * 2.0f - 1.0f;
    this->vertex[3] = quad.rightBottom().y * 2.0f - 1.0f;
    this->vertex[4] = quad.leftTop().x * 2.0f - 1.0f;
    this->vertex[5] = quad.leftTop().y * 2.0f - 1.0f;
    this->vertex[6] = quad.rightTop().x * 2.0f - 1.0f;
    this->vertex[7] = quad.rightTop().y * 2.0f - 1.0f;
}

void AlQuadDrawer::drawStart(HwProgram *program, HwAbsTexture *src, HwAbsTexture *dest) {
    HwAbsFilter::drawStart(program, src, dest);
    program->updateLocation(nullptr, vertex);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
}

void AlQuadDrawer::drawEnd(HwProgram *program, HwAbsTexture *src, HwAbsTexture *dest) {
    HwAbsFilter::drawEnd(program, src, dest);
    glDisable(GL_BLEND);
}

void AlQuadDrawer::draw(HwAbsTexture *dest) {
    HwNormalFilter::draw(cover, dest);
}