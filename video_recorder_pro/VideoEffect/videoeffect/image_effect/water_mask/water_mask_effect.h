//
//  image_water_mask.hpp
//  liveDemo
//
//  Created by apple on 16/11/6.
//  Copyright © 2016年 changba. All rights reserved.
//

#ifndef image_water_mask_hpp
#define image_water_mask_hpp

#include "../../base_video_effect.h"

//Shader.vert文件内容
static char* WATER_MASK_VERTEX_SHADER =
    "attribute vec4 position;    \n"
    "attribute vec2 texcoord;   \n"
    "varying vec2 v_texcoord;     \n"
    "uniform mat4 trans; \n"
    "void main(void)               \n"
    "{                            \n"
    "   gl_Position = trans * position;  \n"
    "   v_texcoord = texcoord;  \n"
    "}                            \n";

//Shader.frag文件内容
static char* WATER_MASK_FRAG_SHADER =
    "precision highp float;\n"
    "varying highp vec2 v_texcoord;\n"
    "uniform sampler2D yuvTexSampler;\n"
    "void main() {\n"
    "vec4 fragColor = texture2D(yuvTexSampler, v_texcoord); \n"
    "gl_FragColor = fragColor;\n"
    "}\n";

class ImageWaterMaskEffect: public BaseVideoEffect {
private:
    GLuint cpyTextureProgId;
    GLuint cpyTexturePosition;
    GLuint cpyTextureCoords;
    GLint cpyTextureUniformSampler;
    
    GLint mUniformTransforms;
    
public:
    ImageWaterMaskEffect();
    virtual ~ImageWaterMaskEffect();
    
    virtual bool init();
    virtual void renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback);
    virtual void destroy();

};


#endif /* image_water_mask_hpp */
