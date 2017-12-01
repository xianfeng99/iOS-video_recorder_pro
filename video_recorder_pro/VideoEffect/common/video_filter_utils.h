#ifndef VIDEO_FILTER_UTILS_H
#define VIDEO_FILTER_UTILS_H
#include "./../videoeffect/image_effect/contrast_effect.h"
#include "./../videoeffect/image_effect/player_contrast_effect.h"
#include "./../videoeffect/image_effect/grayscale_effect.h"
#include "./../videoeffect/image_effect/mix_effect.h"
#include "./../videoeffect/image_effect/sepia_effect.h"
#include "./../videoeffect/image_effect/tone_curve_effect.h"
#include "./../videoeffect/image_effect/vignette_effect.h"
#include "./../videoeffect/image_effect/beautify/beautify_effect.hpp"
#include "./../videoeffect/multi_effect/muti_effect.h"
#include "./../videoeffect/image_effect/whitening/whitening_effect.h"
#include "./../videoeffect/image_effect/whitening/whitening_cool_effect.h"
#include "./../videoeffect/image_effect/beautify_face/beautify_face_effect.h"
#include "./../videoeffect/image_effect/beautify_face/thin_beautify_face_effect.h"
#include "./../videoeffect/image_effect/beautify_face/beautify_face_cool_effect.h"
#include "./../videoeffect/image_effect/thin/thin_whitening_effect.h"
#include "./../videoeffect/saturation_scene/saturation_effect.h"
#include "./../videoeffect/png_sequence/png_sequence_effect.h"
#include "./../videoeffect/blur_scene/blur_scene_effect.h"
#include "./../videoeffect/blur_scene/selective_blur_scene_effect.h"
#include "./../videoeffect/base_video_effect.h"
#include "./../editmodel/text_scene/text_scene_filter.h"
#include "./../editmodel/blur_scene/blur_scene_filter.h"
#include "./../editmodel/selective_blur_scene/selective_blur_scene_filter.h"

BaseVideoEffect * createVideoEffect(const char * filterName);

ModelFilter * createModelFilter(int filterIndex, int64_t sequenceIn, int64_t sequenceOut, char* filterName);


#endif // VIDEO_FILTER_UTILS_H
