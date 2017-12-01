//
// Created by tianchi on 17-9-11.
//

#ifndef SONGSTUDIO_MUTI_EFFECT_H
#define SONGSTUDIO_MUTI_EFFECT_H


#include "base_video_effect.h"

//#define _STR(s) #s
//#define STR(s) _STR(s)
//#define SHARPEN 0
//#define TONE_CURVE 1
//#define HUE 2
//#define SEPIA 4
//#define GRAY 5
//#define VIGNETTE 6
//#define MIX 7
//
//const char * vs = STR(
//attribute vec4 position;
//attribute vec2 texcoord;
//varying vec2 tx;
//varying vec2 tx_origin;
//
//
//// 缩放值
//uniform float zoom;
//// 是否启用瘦脸
//uniform int thin;
//
//void main(){
//    tx_origin = texcoord;
//    float x;
//    float y;
//    y = texcoord.y - position.y * (1.0 - zoom) / 2.0;
//    if(thin == 1){
//        x = texcoord.x - position.x * (1.0 - zoom) / 2.0 * (position.y + 1.0) / 2.0;
//    }else{
//        x = texcoord.x - position.x * (1.0 - zoom) / 2.0;
//    }
//    tx = vec2(x, y);
//    gl_Position = position;
//}
//);
//
//
//const char * fs = STR(
//precision mediump float;
//varying vec2 tx;
//varying vec2 tx_origin;
//uniform sampler2D yuvTexSampler;
//// 滤镜选择开关
//uniform int filter_switch[8];
//
//// filter data ---------------------------------------------------
//// 锐化 sharp
//uniform float sharpness;
//uniform float pix_step_x;
//uniform float pix_step_y;
//
//// 颜色曲线 tone_curve
//uniform sampler2D acv_tex;
//
//// 色相调整
//uniform float hue_adjust;
//const vec4  kRGBToYPrime = vec4 (0.299, 0.587, 0.114, 0.0);
//const vec4  kRGBToI     = vec4 (0.595716, -0.274453, -0.321263, 0.0);
//const vec4  kRGBToQ     = vec4 (0.211456, -0.522591, 0.31135, 0.0);
//const vec4  kYIQToR   = vec4 (1.0, 0.9563, 0.6210, 0.0);
//const vec4  kYIQToG   = vec4 (1.0, -0.2721, -0.6474, 0.0);
//const vec4  kYIQToB   = vec4 (1.0, -1.1070, 1.7046, 0.0);
//
//// 怀旧 sepia
//uniform mat4 sepia_matrix;
//uniform float sepia_intensity;
//
//// 灰度
//const vec4 gray_w = vec4(0.2125, 0.7154, 0.0721, 0.0);
//
//// 晕影 vignette
//uniform vec2 vignetteCenter;
//uniform vec3 vignetteColor;
//const float vignetteStart = 0.3;
//const float vignetteEnd = 0.75;
//
//// 混合
//uniform sampler2D mix_tex;
//uniform float mix_progress;
//
//// filter func ---------------------------------------------------
//vec4 shapen(vec2 pos){
//    vec4 c = texture2D(yuvTexSampler, pos);
//    if(filter_switch[SHARPEN] == 1){
//        vec4 c_up = texture2D(yuvTexSampler, vec2(pos.x, pos.y - pix_step_y));
//        vec4 c_down = texture2D(yuvTexSampler, vec2(pos.x, pos.y + pix_step_y));
//        vec4 c_left = texture2D(yuvTexSampler, vec2(pos.x - pix_step_x, pos.y));
//        vec4 c_right = texture2D(yuvTexSampler, vec2(pos.x + pix_step_x, pos.y));
//        c += (c * 4.0 - c_up - c_down - c_left - c_right) * sharpness;
//        c.a = 1.0;
//    }
//    return c;
//}
//// 颜色曲线 tone_curve
//vec4 tone_curve(vec2 pos){
//    vec4 c = shapen(pos);
//    if(filter_switch[TONE_CURVE] == 1){
//        float r = texture2D(acv_tex, vec2(c.r, 0)).r;
//        float g = texture2D(acv_tex, vec2(c.g, 0)).g;
//        float b = texture2D(acv_tex, vec2(c.b, 0)).b;
//        c = vec4(r, g, b, 1.0);
//    }
//    return c;
//}
//
//// 色相调整 hue
//vec4 hue(vec2 pos){
//    vec4 color = tone_curve(pos);
//    if(filter_switch[HUE] == 1){
//        // Convert to YIQ
//        float   YPrime  = dot (color, kRGBToYPrime);
//        float   I      = dot (color, kRGBToI);
//        float   Q      = dot (color, kRGBToQ);
//        // Calculate the hue and chroma
//        float   hue     = atan (Q, I);
//        float   chroma  = sqrt (I * I + Q * Q);
//        // Make the user's adjustments
//        float hue1 = hue;
//        float weight = 1.0;
//        if ((hue1 < 0.2617993833) && (hue1 > -1.8325956833)){
//            hue1 += (-hue_adjust);
//            weight = hue;
//            weight += 0.78539815;
//            weight = abs(weight);
//            weight /= 1.0471975333;
//            weight *= 4.0;
//            weight -= 3.0;
//            if (weight < 0.0){
//                weight = 0.0;
//            }
//            hue = hue1;
//            Q = chroma * sin (hue);
//            I = chroma * cos (hue);
//            // Convert back to RGB
//            vec4 yIQ = vec4 (YPrime, I, Q, 0.0);
//            color.r = color.r * weight + (1.0 - weight) * dot (yIQ, kYIQToR);
//            color.g = color.g * weight + (1.0 - weight) * dot (yIQ, kYIQToG);
//            color.b = color.b * weight + (1.0 - weight) * dot (yIQ, kYIQToB);
//        }
//    }
//    return color;
//}
//
//// 怀旧 sepia
//vec4 sepia(vec2 pos){
//    vec4 c = hue(pos);
//    if(filter_switch[SEPIA] == 1){
//        vec4 cc = c * sepia_matrix;
//        c = mix(c , cc, sepia_intensity);
//    }
//    return c;
//}
//
//// 灰度图
//vec4 gary(vec2 pos){
//    vec4 c = sepia(pos);
//    if(filter_switch[GRAY] == 1){
//        vec3 g = vec3(dot(c, gray_w));
//        c.rgb = g;
//    }
//    return c;
//}
//
//// 晕影 vignette
//vec4 vignette(vec2 pos){
//    vec4 c = gary(pos);
//    if(filter_switch[VIGNETTE] == 1){
//        vec3 rgb = c.rgb;
//        float d = distance(pos, vignetteCenter);
//        float percent = smoothstep(vignetteStart, vignetteEnd, d);
//        c = vec4(mix(rgb, vignetteColor, percent), 1.0);
//    }
//    return c;
//}
//
//// 纹理混合 mix 目前看到android 在暂停的时候会调用 贴了一个半透明的图
//vec4 texture_mix(vec2 pos){
//    vec4 c = vignette(pos);
//    if(filter_switch[MIX] == 1){
//        vec4 m = texture2D(mix_tex, tx_origin);
//        c = mix(c, m, mix_progress);
//    }
//    return c;
//}
//void main(void){
//    gl_FragColor = texture_mix(tx);
//}
//);

class muti_effect : public BaseVideoEffect{
public:
    muti_effect();
    virtual ~muti_effect();
    virtual bool init();
    void onDrawArraysPre(EffectCallback * filterCallback);
    virtual void buildParamDefaultValue();
protected:
    GLuint vbos[3];
    size_t elementsCount;
    virtual void renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback);
private:
    GLint loc_sharpness;
    GLint loc_pix_step_x;
    GLint loc_pix_step_y;
    GLint loc_zoom;
    GLint loc_thin;
    GLint loc_filter_switch;
    GLint loc_acv_tex;
    GLint loc_hue_adjust;
    GLint loc_vignette_center;
    GLint loc_vignette_color;
    GLint loc_sepia_matrix;
    GLint loc_sepia_intensity;
    GLint loc_mix_tex;
    GLint loc_mix_progress;

    GLuint acv_tex;
};
#endif //SONGSTUDIO_MUTI_EFFECT_H
