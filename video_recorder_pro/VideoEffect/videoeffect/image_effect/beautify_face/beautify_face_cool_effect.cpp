#include "beautify_face_cool_effect.h"
#include "../beautify/beautify_effect.hpp"

#define LOG_TAG "BeautifyFaceCoolEffect"

BeautifyFaceCoolEffect::BeautifyFaceCoolEffect(){
    this->addFilter(new ImageBeautifyEffect());
    this->addFilter(new SharpenEffect());
    this->addFilter(new ToneCurveEffect());
}

BeautifyFaceCoolEffect::~BeautifyFaceCoolEffect() {
}
