#include "./video_filter_utils.h"

BaseVideoEffect * createVideoEffect(const char * filterName) {
	if (0 == strcmp(filterName, SATURATION_SCENE_FILTER_NAME)) {
		SaturationEffect * obj = new SaturationEffect();
		return static_cast<BaseVideoEffect *>(obj);
    } else if (0 == strcmp(filterName, SELECTIVE_BLUR_SCENE_FILTER_NAME)) {
		SelectiveBlurSceneEffect * obj = new SelectiveBlurSceneEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, BLUR_SCENE_FILTER_NAME)) {
		BlurSceneEffect * obj = new BlurSceneEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, PNG_SEQUENCE_FILTER_NAME)) {
		PngSequenceEffect * obj = new PngSequenceEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, CONTRAST_FILTER_NAME)) {
		ContrastEffect * obj = new ContrastEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, PLAYER_CONTRAST_FILTER_NAME)) {
		PlayerContrastEffect * obj = new PlayerContrastEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, GRAY_SCALE_FILTER_NAME)) {
		GrayScaleEffect * obj = new GrayScaleEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, VIGNETTE_FILTER_NAME)) {
		VignetteEffect * obj = new VignetteEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, TONE_CURVE_FILTER_NAME)) {
		ToneCurveEffect * obj = new ToneCurveEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, THIN_WHITENING_FILTER_NAME)) {
		ThinWhiteningEffect * obj = new ThinWhiteningEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, WHITENING_FILTER_NAME)) {
		WhiteningEffect * obj = new WhiteningEffect();
		return static_cast<BaseVideoEffect *>(obj);
    }  else if (0 == strcmp(filterName, WHITENING_COOL_FILTER_NAME)) {
        WhiteningCoolEffect * obj = new WhiteningCoolEffect();
        return static_cast<BaseVideoEffect *>(obj);
    } else if (0 == strcmp(filterName, BEAUTIFY_FACE_FILTER_NAME)) {
        BeautifyFaceEffect * obj = new BeautifyFaceEffect();
        return static_cast<BaseVideoEffect *>(obj);
    } else if (0 == strcmp(filterName, BEAUTIFY_FACE_COOL_FILTER_NAME)) {
        BeautifyFaceCoolEffect * obj = new BeautifyFaceCoolEffect();
        return static_cast<BaseVideoEffect *>(obj);
    } else if (0 == strcmp(filterName, THIN_BEAUTIFY_FACE_FILTER_NAME)) {
        muti_effect * obj = new muti_effect();
        return static_cast<BaseVideoEffect *>(obj);
    } else if (0 == strcmp(filterName, IMAGE_BASE_EFFECT_NAME)) {
		ImageBaseEffect * obj = new ImageBaseEffect();
		return static_cast<BaseVideoEffect *>(obj);
	} else if (0 == strcmp(filterName, MIX_FILTER_NAME)) {
		MixEffect * obj = new MixEffect();
		return static_cast<BaseVideoEffect *>(obj);
    } else if(0 == strcmp(filterName, BEAUTY_FILTER_NAME)) {
        ImageBeautifyEffect * obj = new ImageBeautifyEffect();
        return static_cast<BaseVideoEffect *>(obj);
    } else {
		return new BaseVideoEffect();
	}
}

ModelFilter * createModelFilter(int filterIndex, int64_t sequenceIn, int64_t sequenceOut, char* filterName) {
	if (0 == strcmp(filterName, CONTRAST_FILTER_NAME)) {
		ModelFilter* obj = new ModelFilter(filterIndex, sequenceIn, sequenceOut, filterName);
		return static_cast<ModelFilter *>(obj);
	} else if (0 == strcmp(filterName, SELECTIVE_BLUR_SCENE_FILTER_NAME)) {
		SelectiveBlurSceneFilter* obj = new SelectiveBlurSceneFilter(filterIndex, sequenceIn, sequenceOut, filterName);
		return static_cast<ModelFilter *>(obj);
	} else if (0 == strcmp(filterName, BLUR_SCENE_FILTER_NAME)) {
		BlurSceneFilter* obj = new BlurSceneFilter(filterIndex, sequenceIn, sequenceOut, filterName);
		return static_cast<ModelFilter *>(obj);
	} else if (0 == strcmp(filterName, TEXT_SCENE_FILTER_NAME)) {
		TextSceneFilter* obj = new TextSceneFilter(filterIndex, sequenceIn, sequenceOut, filterName);
		return static_cast<ModelFilter *>(obj);
	} else {
		ModelFilter* obj = new ModelFilter(filterIndex, sequenceIn, sequenceOut, filterName);
		return static_cast<ModelFilter *>(obj);
	}
}
