#include "./video_effect_processor.h"

#define LOG_TAG "VideoEffectProcessor"

VideoEffectProcessor::VideoEffectProcessor() {
	inputVideoFrame = NULL;
	outputVideoFrame = NULL;
	directPassEffect = NULL;
	effectCache = NULL;
	timeLine = new ModelTimeline();
	timeLine->init();
	mNeedChangeTimeline = false;
	pthread_rwlock_init(&mRwlock, NULL);
}

VideoEffectProcessor::~VideoEffectProcessor() {
	mNeedChangeTimeline = false;
	pthread_rwlock_destroy(&mRwlock);
}

bool VideoEffectProcessor::init() {
	inputVideoFrame = new OpenglVideoFrame();
	outputVideoFrame = new OpenglVideoFrame();

	directPassEffect = new DirectPassEffect();
	directPassEffect->init();
	effectCache = new VideoEffectCache();

	return true;
}

int VideoEffectProcessor::addFilter(int trackIndex, int64_t sequenceIn, int64_t sequenceOut, string filterName) {
	int filterId = -1;
	if (timeLine) {
		char *data;
		int len = filterName.length();
		data = new char[len+1];
		filterName.copy(data, len, 0);
		data[len] = '\0';

		filterId = timeLine->addFilter(trackIndex, sequenceIn, sequenceOut, data);

		delete [] data;
	}
    else
    {
        LOGE("error : timeLine is not init ! ! !");
    }
	return filterId;
}

void VideoEffectProcessor::removeFilter(int trackIndex, int filterId){
	timeLine->removeFilter(trackIndex, filterId);
}

void VideoEffectProcessor::removeAllFilters(){
	timeLine->init();
}

bool VideoEffectProcessor::invokeFilterOnReady(int trackIndex, int filterId){
	return timeLine->invokeFilterOnInit(trackIndex, filterId);
}

void VideoEffectProcessor::setFilterParamValue(int trackIndex, int filterId, string paramName, ParamVal value) {
	if (timeLine) {
		char *data;
		int len = paramName.length();
		data = new char[len + 1];
		paramName.copy(data, len, 0);
		data[len] = '\0';

		timeLine->setFilterParamValue(trackIndex, filterId, data, value);

		delete []data;
	}
}

void VideoEffectProcessor::process(OpenglVideoFrame* sourceVideoFrame, float position, OpenglVideoFrame* targetVideoFrame) {
	// traverse the filter list to render the filters need rendered
	ImagePosition imagePosition;
	targetVideoFrame->GetImagePosition(&imagePosition);
	GLuint sourceTexId = sourceVideoFrame->getTextureId();
	GLuint outputTexId = targetVideoFrame->getTextureId();

	pthread_rwlock_wrlock(&mRwlock);	// lock here, maybe block UI, but safe is more important
	if (mNeedChangeTimeline) {
		mNeedChangeTimeline = false;
		timeLine->clearFilters();
	}
	pthread_rwlock_unlock(&mRwlock);

	if (timeLine) {
		list<ModelFilter *> filters = timeLine->getAllTranAndFilters(0);
		list<ModelFilter *>::iterator itor = filters.begin();
		int filterCount = 0;
		for (; itor != filters.end(); itor++) {
			ModelFilter* filter = *itor;
			if (filter->isAvailable(position, detectGPUSurpportedEffectByPlatforms, mContext))
				filterCount++;
		}
		if(filterCount == 0){
			inputVideoFrame->init(sourceTexId, imagePosition);
			outputVideoFrame->init(outputTexId, imagePosition);
			directPassEffect->renderEffect(inputVideoFrame, outputVideoFrame, NULL);
		} else{
			itor = filters.begin();
			int sub = 0;
			GLuint previousTexId = sourceTexId;
			GPUTexture* previousTextureFromCache = NULL;
			for (; itor != filters.end(); itor++) {
				ModelFilter* filter = *itor;
				if (filter->isAvailable(position, detectGPUSurpportedEffectByPlatforms, mContext)) {
					BaseVideoEffect* effect = effectCache->getVideoEffectFromCache(string((*itor)->name));
					if (effect) {
						filter->onRenderPre(position);

						inputVideoFrame->init(previousTexId, imagePosition, position);

						GLuint currentTexId = outputTexId;
						GPUTexture* textureFromCache = NULL;
						if(sub < (filterCount - 1)){
							textureFromCache = GPUTextureCache::GetInstance()->fetchTexture(imagePosition.width, imagePosition.height);
							textureFromCache->lock();
							currentTexId = textureFromCache->getTexId();
						}
						outputVideoFrame->init(currentTexId, imagePosition);

						effect->renderEffect(inputVideoFrame, outputVideoFrame, filter->getFilterCallback());

						previousTexId = currentTexId;
						if(NULL != previousTextureFromCache){
							previousTextureFromCache->unLock();
						}
						previousTextureFromCache = textureFromCache;
					} else {
						LOGE("getVideoEffectFromCache failed");
					}
					sub++;
				}
			}
		}
	}
}

void VideoEffectProcessor::dealloc() {

	// release videoFrame
	if(inputVideoFrame){
		delete inputVideoFrame;
		inputVideoFrame = NULL;
	}
	if(outputVideoFrame){
		delete outputVideoFrame;
		outputVideoFrame = NULL;
	}
	if (timeLine) {
		delete timeLine;
		timeLine = NULL;
	}
	if(NULL != directPassEffect){
		delete directPassEffect;
		directPassEffect = NULL;
	}
	if(NULL != effectCache){
		delete effectCache;
		effectCache = NULL;
	}
	GPUTextureCache::GetInstance()->destroy();
}

