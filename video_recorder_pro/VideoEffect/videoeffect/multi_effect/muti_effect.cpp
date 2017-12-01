//
// Created by tianchi on 17-9-11.
//

#include "muti_effect.h"
#include "acv_util.h"
#include "video_effect_def.h"


muti_effect::muti_effect(){
//    mVertexShader = (char *)vs;
//    mFragmentShader = (char *)fs;
    acv_tex = 0;
}

muti_effect::~muti_effect() {
    if(vbos[0] != 0){
        glDeleteBuffers(3, vbos);
    }
    if(acv_tex != 0){
        glDeleteTextures(1, &acv_tex);
    }
}

bool muti_effect::init(){
//    if(BaseVideoEffect::init()){
//        static const GLfloat points[8] = {-1, 1, 1, 1, 1, -1, -1, -1};
//        static const GLfloat vertexCoords[8] = {0, 0, 1, 0, 1, 1, 0, 1};
//        static const GLuint indexes[6] = {0, 1, 2, 0, 2, 3};
//        glGenBuffers(3, vbos);
//        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, points, GL_STATIC_DRAW);
//        glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, vertexCoords, GL_STATIC_DRAW);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indexes, GL_STATIC_DRAW);
//        elementsCount = 6;
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//        loc_zoom = glGetUniformLocation(mGLProgId, "zoom");
//        loc_thin = glGetUniformLocation(mGLProgId, "thin");
//        loc_filter_switch = glGetUniformLocation(mGLProgId, "filter_switch");
//        loc_acv_tex = glGetUniformLocation(mGLProgId, "acv_tex");
//        loc_hue_adjust = glGetUniformLocation(mGLProgId, "hue_adjust");
//        loc_vignette_center = glGetUniformLocation(mGLProgId, "vignetteCenter");
//        loc_vignette_color = glGetUniformLocation(mGLProgId, "vignetteColor");
//        loc_sepia_matrix = glGetUniformLocation(mGLProgId, "sepia_matrix");
//        loc_sepia_intensity = glGetUniformLocation(mGLProgId, "sepia_intensity");
//        loc_mix_tex = glGetUniformLocation(mGLProgId, "mix_tex");
//        loc_mix_progress = glGetUniformLocation(mGLProgId, "mix_progress");
//        loc_sharpness = glGetUniformLocation(mGLProgId, "sharpness");
//        loc_pix_step_x = glGetUniformLocation(mGLProgId, "pix_step_x");
//        loc_pix_step_y = glGetUniformLocation(mGLProgId, "pix_step_y");
//        return true;
//    }
    return false;
}
//
void muti_effect::onDrawArraysPre(EffectCallback * filterCallback){
//    GLint filter_switch[8] = {0};
//    if(filterCallback){
//        ParamVal val, val1;
//        bool suc, suc1;
//        suc = filterCallback->getParamValue(string(MUTI_ZOOM), val);
//        if(suc){
//            glUniform1f(loc_zoom, (float)val.u.fltVal);
//        }else{
//            glUniform1f(loc_zoom, 1.0f);
//        }
//        suc = filterCallback->getParamValue(string(MUTI_THIN_ENABLE), val);
//        if(suc && val.u.boolVal){
//            glUniform1i(loc_thin, 1);
//        }else{
//            glUniform1i(loc_thin, 0);
//        }
//
//        suc = filterCallback->getParamValue(string(MUTI_SHARPEN_ENABLE), val);
//        if(suc && val.u.boolVal){
//            suc = filterCallback->getParamValue(string(MUTI_SHARPEN_SHARPNESS), val);
//            if(suc){
//                filter_switch[SHARPEN] = 1;
//                glUniform1f(loc_sharpness, (float)val.u.fltVal);
//                filterCallback->getParamValue(string(IMAGE_EFFECT_GROUP_TEXTURE_WIDTH), val);
//                glUniform1f(loc_pix_step_x, 1.0f / (float)val.u.fltVal);
//                filterCallback->getParamValue(string(IMAGE_EFFECT_GROUP_TEXTURE_HEIGHT), val);
//                glUniform1f(loc_pix_step_y, 1.0f / (float)val.u.fltVal);
//            }
//        }
//
//        suc = filterCallback->getParamValue(string(MUTI_TONE_CURVE_ENABLE), val);
//        if(suc && val.u.boolVal){
//            filter_switch[TONE_CURVE] = 1;
//            suc = filterCallback->getParamValue(string(MUTI_TONE_CURVE_ACV_BUFFER_CHANGED), val);
//            if(suc && val.u.boolVal){
//                if(acv_tex != 0){
//                    glDeleteTextures(1, &acv_tex);
//                }
//                val.u.boolVal = false;
//                filterCallback->setParamValue(string(MUTI_TONE_CURVE_ACV_BUFFER_CHANGED), val);
//
//                ParamVal acv_buffer_size_val, acv_buffer_val;
//                suc = filterCallback->getParamValue(string(MUTI_TONE_CURVE_ACV_BUFFER_SIZE), acv_buffer_size_val);
//                suc1 = filterCallback->getParamValue(string(MUTI_TONE_CURVE_ACV_BUFFER), acv_buffer_val);
//                if(suc && suc1){
//                    acv_util * acv = new acv_util();
//                    unsigned char * res;
//                    acv->parse((unsigned char *)acv_buffer_val.u.arbData, acv_buffer_size_val.u.intVal, &res);
//                    delete acv;
//                    glGenTextures(1, &acv_tex);
//                    glBindTexture(GL_TEXTURE_2D, acv_tex);
//                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, res);
//                    free(res);
//                }
//            }
//            glActiveTexture(GL_TEXTURE1);
//            glBindTexture(GL_TEXTURE_2D, acv_tex);
//            glUniform1i(loc_acv_tex, 1);
//        }
//
////        suc = filterCallback->getParamValue(string(MUTI_HUE_ENABLE), val);
////        if(suc && val.u.boolVal){
////            suc = filterCallback->getParamValue(string(MUTI_HUE_ADJUST), val);
////            if(suc){
////                filter_switch[HUE] = 1;
////                glUniform1f(loc_hue_adjust, (float)val.u.fltVal * 3.1415926f /180.0f);
////            }
////        }
//
//        suc = filterCallback->getParamValue(string(MUTI_SEPIA_ENABLE), val);
//        if(suc && val.u.boolVal){
//            GLfloat mColorMatrix[16] = {
//                    0.3588f, 0.7044f, 0.1368f, 0.0f,
//                    0.2990f, 0.5870f, 0.1140f, 0.0f,
//                    0.2392f, 0.4696f, 0.0912f, 0.0f,
//                    0.0f, 0.0f, 0.0f, 1.0f
//            };
//            suc = filterCallback->getParamValue(string(MUTI_SEPIA_INTENSITY), val);
//            if(suc){
//                filter_switch[SEPIA] = 1;
//                glUniform1f(loc_sepia_intensity, (float)val.u.fltVal);
//                glUniformMatrix4fv(loc_sepia_matrix, 1, GL_FALSE, mColorMatrix);
//            }
//        }
//
//        suc = filterCallback->getParamValue(string(MUTI_GRAY_ENABLE), val);
//        if(suc && val.u.boolVal){
//            filter_switch[GRAY] = 1;
//        }
//
//        suc = filterCallback->getParamValue(string(MUTI_VIGNETTE_ENABLE), val);
//        if(suc && val.u.boolVal){
//            suc = filterCallback->getParamValue(string(MUTI_VIGNETTE_CENTER), val);
//            suc1 = filterCallback->getParamValue(string(MUTI_VIGNETTE_COLOR), val1);
//            if(suc && suc1){
//                filter_switch[VIGNETTE] = 1;
//                glUniform2f(loc_vignette_center, val.u.pos2dVal.x, val.u.pos2dVal.y);
//                glUniform3f(loc_vignette_color, val1.u.pos3dVal.x, val1.u.pos3dVal.y, val1.u.pos3dVal.z);
//            }
//        }
//
//        suc = filterCallback->getParamValue(string(MUTI_MIX_ENABLE), val);
//        if(suc && val.u.boolVal){
//            suc = filterCallback->getParamValue(string(MUTI_MIX_TEXTURE), val);
//            suc1 = filterCallback->getParamValue(string(MUTI_MIX_PROGRESS), val1);
//            if(suc && suc1){
//                filter_switch[MIX] = 1;
//                glActiveTexture(GL_TEXTURE2);
//                glBindTexture(GL_TEXTURE_2D, (GLuint)val.u.intVal);
//                glUniform1i(loc_mix_tex, 2);
//                glUniform1f(loc_mix_progress, (float)val1.u.fltVal);
//            }
//        }
//    }
//    glUniform1iv(loc_filter_switch, 8, filter_switch);
}
//
void muti_effect::buildParamDefaultValue(){
//    mMapParamDef.clear();
//    ParamVal p_zoom;
//    p_zoom.type = EffectParamTypeFloat;
//    p_zoom.u.fltVal = 1.0;
//    mMapParamDef[string(MUTI_ZOOM)] = p_zoom;
//
//    ParamVal p_thin_enable;
//    p_thin_enable.type = EffectParamTypeBoolean;
//    p_thin_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_THIN_ENABLE)] = p_thin_enable;
//
//    ParamVal p_tone_curve_enable;
//    p_tone_curve_enable.type = EffectParamTypeBoolean;
//    p_tone_curve_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_TONE_CURVE_ENABLE)] = p_tone_curve_enable;
//
//    ParamVal p_tone_curve_buffer_changed;
//    p_tone_curve_buffer_changed.type = EffectParamTypeBoolean;
//    p_tone_curve_buffer_changed.u.boolVal = false;
//    mMapParamDef[string(MUTI_TONE_CURVE_ACV_BUFFER_CHANGED)] = p_tone_curve_buffer_changed;
//
//    ParamVal p_hue_enable;
//    p_hue_enable.type = EffectParamTypeBoolean;
//    p_hue_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_HUE_ENABLE)] = p_hue_enable;
//
//    ParamVal p_sepia_enable;
//    p_sepia_enable.type = EffectParamTypeBoolean;
//    p_sepia_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_SEPIA_ENABLE)] = p_sepia_enable;
//
//    ParamVal p_gray_enable;
//    p_gray_enable.type = EffectParamTypeBoolean;
//    p_gray_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_GRAY_ENABLE)] = p_gray_enable;
//
//    ParamVal p_vignette_enable;
//    p_vignette_enable.type = EffectParamTypeBoolean;
//    p_vignette_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_VIGNETTE_ENABLE)] = p_vignette_enable;
//
//    ParamVal p_mix_enable;
//    p_mix_enable.type = EffectParamTypeBoolean;
//    p_mix_enable.u.boolVal = false;
//    mMapParamDef[string(MUTI_MIX_ENABLE)] = p_mix_enable;
}
void muti_effect::renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback){
//
//    if (inputFrame == NULL || outputFrame == NULL) {
//        return;
//    }
//
//    if (!mIsInitialized) {
//        return;
//    }
//
//    //
//    glUseProgram(mGLProgId);
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
//    glVertexAttribPointer(mGLVertexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(mGLVertexCoords);
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glEnableVertexAttribArray");
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
//    glVertexAttribPointer(mGLTextureCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(mGLTextureCoords);
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glEnableVertexAttribArray");
//
//    //
//    glBindTexture(GL_TEXTURE_2D, outputFrame->getTextureId());
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glBindTexture");
//
//    this->switchFBOAttachmentTexture(outputFrame->getTextureId());
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glFramebufferTexture2D");
//
//    ImagePosition imgPos;
//    outputFrame->GetImagePosition(&imgPos);
//    glViewport(imgPos.x, imgPos.y, imgPos.width, imgPos.height);
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glViewport");
//
//    this->onDrawArraysPre(filterCallback);
//
//    glActiveTexture (GL_TEXTURE0);
//    this->bindTexture(inputFrame->getTextureId());
//    glUniform1i(mGLUniformTexture, 0);
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glUniform1i");
//
////    this->draw();
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
//    glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect draw");
//    //
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    glDisableVertexAttribArray(mGLVertexCoords);
//    glDisableVertexAttribArray(mGLTextureCoords);
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//    this->switchFBODefaultAttachment();
//    GL_CHECK_ERROR("BaseVideoEffect::renderEffect glFramebufferTexture2D");
//
}

