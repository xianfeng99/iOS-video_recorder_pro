//
//  beautify_effect.cpp
//  video_recorder_pro
//
//  Created by XiaokaiZhan on 2017/9/23.
//  Copyright © 2017年 xiaokai.zhan. All rights reserved.
//

#include "beautify_effect.hpp"

#define LOG_TAG "ImageBeautifyEffect"

ImageBeautifyEffect::ImageBeautifyEffect() {
    mVertexShader = BEAUTIFY_VERTEX_SHADER;
    mFragmentShader = BEAUTIFY_FRAGMENT_SHADER;
}

ImageBeautifyEffect::~ImageBeautifyEffect() {
}

bool ImageBeautifyEffect::init()
{
    if(BaseVideoEffect::init()){
        glUseProgram(mGLProgId);
        beautyFactorsUniform = glGetUniformLocation(mGLProgId, "beautyFactors");
        checkGlError("glGetUniformLocation beautyFactors checkGlError");
        textureWidthUniform = glGetUniformLocation(mGLProgId, "textureWidth");
        checkGlError("glGetUniformLocation textureWidth checkGlError");
        textureHeightUniform = glGetUniformLocation(mGLProgId, "textureHeight");
        checkGlError("glGetUniformLocation textureHeight checkGlError");
        return true;
    }
    return false;
}

void ImageBeautifyEffect::renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback, GLfloat* vertexCoords, GLfloat* textureCoords) {
    if (inputFrame == NULL || outputFrame == NULL) {
        LOGE("ImageBeautifyEffect::renderEffect input or output frame pointer is NULL!");
        return;
    }
    if (!mIsInitialized) {
        LOGE("ImageBeautifyEffect::renderEffect effect not initialized!");
        return;
    }
    this->switchFBOAttachmentTexture(outputFrame->getTextureId());
    ImagePosition imgPos;
    outputFrame->GetImagePosition(&imgPos);
    glViewport(imgPos.x, imgPos.y, imgPos.width, imgPos.height);
    glUseProgram(mGLProgId);
    glVertexAttribPointer(mGLVertexCoords, 2, GL_FLOAT, 0, 0, vertexCoords);
    glEnableVertexAttribArray(mGLVertexCoords);
    glVertexAttribPointer(mGLTextureCoords, 2, GL_FLOAT, 0, 0, textureCoords);
    glEnableVertexAttribArray(mGLTextureCoords);
    glActiveTexture(GL_TEXTURE0);
    this->bindTexture(inputFrame->getTextureId());
    glUniform1i(mGLUniformTexture, 0);
    glUniform1f(textureWidthUniform, imgPos.width);
    glUniform1f(textureHeightUniform, imgPos.height);
    ParamVal val;
    bool suc = filterCallback->getParamValue(string(SMOOTH_SKIN_EFFECT_PARAM_CHANGED), val);
    if (suc) {
        bool isChanged = val.u.boolVal;
        if (isChanged) {
            val.u.boolVal = false;
            filterCallback->setParamValue(string(SMOOTH_SKIN_EFFECT_PARAM_CHANGED), val);
            
            float softLightProgress = 0.25;
            suc = filterCallback->getParamValue(string(SOFT_LIGHT_PROGRESS), val);
            if (suc) {
                softLightProgress = val.u.fltVal;
                LOGI("get success, softLightProgress:%.3f", softLightProgress);
            } else {
                LOGI("get softLightProgress failed, use default value softLightProgress");
            }
            
            float sCurveProgress = 0.8;
            suc = filterCallback->getParamValue(string(MASK_CURVE_PROGRESS), val);
            if (suc) {
                sCurveProgress = val.u.fltVal;
                LOGI("get success, sCurveProgress:%.3f", sCurveProgress);
            } else {
                LOGI("get sCurveProgress failed, use default value sCurveProgress");
            }
            
            float satuRatio = 0.25f;
            suc = filterCallback->getParamValue(string(SATU_RATIO), val);
            if (suc) {
                satuRatio = val.u.fltVal;
                LOGI("get success, satuRatio:%.3f", satuRatio);
            } else {
                LOGI("get satuRatio failed, use default value satuRatio");
            }
            
            float hue = 0.6;
            suc = filterCallback->getParamValue(string(HUE_EFFECT_HUE_ANGLE), val);
            if (suc) {
                hue = val.u.fltVal;
                LOGI("get success, hueAngle:%.3f", hue);
            } else {
                LOGI("get hueAngle failed, use default value hueAngle");
            }
            glUniform4f(beautyFactorsUniform, hue, sCurveProgress, softLightProgress, satuRatio);
            checkGlError("glUniform1f sCurveProgressUniform");
        }
    }
    this->draw();
    glDisableVertexAttribArray(mGLVertexCoords);
    glDisableVertexAttribArray(mGLTextureCoords);
    glBindTexture(GL_TEXTURE_2D, 0);
    this->switchFBODefaultAttachment();
}
