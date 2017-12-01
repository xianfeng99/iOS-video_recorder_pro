//
//  beautify_effect.hpp
//  video_recorder_pro
//
//  Created by XiaokaiZhan on 2017/9/23.
//  Copyright © 2017年 xiaokai.zhan. All rights reserved.
//

#ifndef beautify_effect_hpp
#define beautify_effect_hpp

#include "../image_base_effect.h"
#include "beautify.vert"
#include "beautify.frag"

class ImageBeautifyEffect: public ImageBaseEffect {
private:
    /** Program extra uniform **/
    GLint beautyFactorsUniform;
    GLint textureWidthUniform;
    GLint textureHeightUniform;
    
public:
    ImageBeautifyEffect();
    virtual ~ImageBeautifyEffect();
    
    virtual bool init();
    virtual void renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback, GLfloat* vertexCoords, GLfloat* textureCoords);
};

#endif /* beautify_effect_hpp */
