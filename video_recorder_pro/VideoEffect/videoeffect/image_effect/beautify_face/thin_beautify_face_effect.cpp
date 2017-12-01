#include "thin_beautify_face_effect.h"
#include "../beautify/beautify_effect.hpp"

#define LOG_TAG "ThinBeautifyFaceEffect"

ThinBeautifyFaceEffect::ThinBeautifyFaceEffect(){
    this->addFilter(new ThinEffect());
    this->addFilter(new ImageBeautifyEffect());
    this->addFilter(new SharpenEffect());
}

ThinBeautifyFaceEffect::~ThinBeautifyFaceEffect() {
}
