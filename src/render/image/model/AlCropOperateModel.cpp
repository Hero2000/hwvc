/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "AlCropOperateModel.h"
#include "AlMath.h"
#include "AlVec4.h"
#include "AlOrthMatrix.h"

AlCropOperateModel::AlCropOperateModel() : AlAbsOperateModel() {

}

AlCropOperateModel::AlCropOperateModel(const AlCropOperateModel &o)
        : AlAbsOperateModel(o), rectF(o.rectF) {

}

AlCropOperateModel::~AlCropOperateModel() {

}

void AlCropOperateModel::setRect(float left, float top, float right, float bottom) {
    this->rectF.set(left, top, right, bottom);
}

void AlCropOperateModel::setRotation(AlRational &r) {
    this->rotation.num = r.num;
    this->rotation.den = r.den;
}

HwResult AlCropOperateModel::measure(AlAbsOperateModel::AlLayerDesc desc,
                                     AlImageLayerDrawModel *description) {
    AlSize layerSize = description->getLayerSize();
    AlSize src(layerSize.width * rectF.getWidth() / 2.0f,
               layerSize.height * rectF.getHeight() / 2.0f);
    AlSize dest = layerSize;
    AlRectF srcRectF, destRectF;
    _calculateRect(src, dest, srcRectF, destRectF);

    AlOrthMatrix oMat;
    oMat.update(destRectF.left, destRectF.right, destRectF.bottom, destRectF.top, -1.0f, 1.0f);
    AlMatrix tMat;
//    t1Mat.setTranslate(-0.5f, -0.5f);
    tMat.setRotation(AlMath::PI * rotation.toFloat());
    tMat.setScale(rectF.getHeight() / 2.0f, rectF.getHeight() / 2.0f);
//    t2Mat.setTranslate(0.5f, 0.5f);
    AlMatrix mat = oMat * tMat;
    AlVec4 lt(srcRectF.left, srcRectF.top);
    AlVec4 lb(srcRectF.left, srcRectF.bottom);
    AlVec4 rb(srcRectF.right, srcRectF.bottom);
    AlVec4 rt(srcRectF.right, srcRectF.top);
    description->cropQuad.setLeftTop((lt.multiply(mat).xy() + 1.0f) / 2.0f);
    description->cropQuad.setLeftBottom((lb.multiply(mat).xy() + 1.0f) / 2.0f);
    description->cropQuad.setRightBottom((rb.multiply(mat).xy() + 1.0f) / 2.0f);
    description->cropQuad.setRightTop((rt.multiply(mat).xy() + 1.0f) / 2.0f);
    description->setLayerSize(static_cast<int32_t>(layerSize.width * rectF.getWidth() / 2.0f),
                              static_cast<int32_t>(layerSize.height * rectF.getHeight() / 2.0f));
    return Hw::SUCCESS;
}

void AlCropOperateModel::_calculateRect(AlSize &src, AlSize &dest,
                                        AlRectF &srcRectF, AlRectF &destRectF) {
    float aspectRatio = dest.width > dest.height ?
                        (float) dest.width / (float) dest.height :
                        (float) dest.height / (float) dest.width;

    //计算正交矩阵
    if (dest.width > dest.height) {
        destRectF.left = -aspectRatio;
        destRectF.right = -destRectF.left;
        destRectF.bottom = -1.0f;
        destRectF.top = -destRectF.bottom;
    } else {
        destRectF.left = -1.0f;
        destRectF.right = -destRectF.left;
        destRectF.bottom = -aspectRatio;
        destRectF.top = -destRectF.bottom;
    }
    /// 根据Canvas大小计算纹理顶点
    /// 保证图片总是完整填充到Canvas
    /// 并保证至Layer和Canvas至少有一边相等
    /// 此时layer model的scale=1为默认状态
    if (src.width / (float) src.height > dest.width / (float) dest.height) {
        srcRectF.left = destRectF.left;
        srcRectF.right = -srcRectF.left;
        srcRectF.bottom = srcRectF.left * src.height / (float) src.width;
        srcRectF.top = -srcRectF.bottom;
    } else {
        srcRectF.bottom = destRectF.bottom;
        srcRectF.top = -srcRectF.bottom;
        srcRectF.left = srcRectF.bottom * src.width / (float) src.height;
        srcRectF.right = -srcRectF.left;
    }
}