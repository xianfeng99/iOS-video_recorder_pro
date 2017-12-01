#include "beautify_face_effect.h"
#include "../beautify/beautify_effect.hpp"
#define LOG_TAG "BeautifyFaceEffect"

BeautifyFaceEffect::BeautifyFaceEffect(){
    this->addFilter(new DirectPassEffect());
    this->addFilter(new ImageBeautifyEffect());
    this->addFilter(new SharpenEffect());
}

BeautifyFaceEffect::~BeautifyFaceEffect() {
}
