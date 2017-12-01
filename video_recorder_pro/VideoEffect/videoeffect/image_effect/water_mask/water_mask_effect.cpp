#include "water_mask_effect.h"

#define LOG_TAG "ImageWaterMaskEffect"

ImageWaterMaskEffect::ImageWaterMaskEffect() {
    mVertexShader = WATER_MASK_VERTEX_SHADER;
    mFragmentShader = WATER_MASK_FRAG_SHADER;
}

ImageWaterMaskEffect::~ImageWaterMaskEffect() {
}

bool ImageWaterMaskEffect::init(){
    BaseVideoEffect::init();
    cpyTextureProgId = loadProgram(VERTEX_SHADER_FILTER, FRAG_SHADER_FILTER);
    if (!cpyTextureProgId) {
        LOGE("Could not create program cpyTextureProgId.");
        return false;
    }
    cpyTexturePosition = glGetAttribLocation(cpyTextureProgId, "position");
    checkGlError("glGetAttribLocation cpyTexturePosition");
    cpyTextureCoords = glGetAttribLocation(cpyTextureProgId, "texcoord");
    checkGlError("glGetAttribLocation cpyTextureCoords");
    cpyTextureUniformSampler = glGetUniformLocation(cpyTextureProgId, "yuvTexSampler");
    checkGlError("glGetUniformLocation cpyTextureUniformSampler");
    
    mUniformTransforms = glGetUniformLocation(mGLProgId, "trans");
    checkGlError("glGetUniformLocation mUniformTransforms");
    
    return true;
}

void ImageWaterMaskEffect::renderEffect(OpenglVideoFrame * inputFrame, OpenglVideoFrame * outputFrame, EffectCallback * filterCallback) {
//    if (inputFrame == NULL || outputFrame == NULL) {
//        LOGE("BaseVideoEffect::renderEffect input or output frame pointer is NULL!");
//        return;
//    }
//    
//    if (!mIsInitialized) {
//        LOGE("BaseVideoEffect::renderEffect effect not initialized!");
//        return;
//    }
//    
//    // texture id bind with FBO
//    ImagePosition imgPos;
//    outputFrame->GetImagePosition(&imgPos);
//    
//    this->switchFBOAttachmentTexture(outputFrame->getTextureId());
//    GL_CHECK_ERROR("ImageWaterMaskEffect::renderEffect glFramebufferTexture2D");
//    
////    glEnable(GL_BLEND);
////    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//    //拷贝原始纹理
//    glUseProgram(cpyTextureProgId);
//    static const GLfloat cpyTexVertices[] = { -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f };
//    glVertexAttribPointer(cpyTexturePosition, 2, GL_FLOAT, 0, 0, cpyTexVertices);
//    glEnableVertexAttribArray(cpyTexturePosition);
//    static const GLfloat cpyTexCoords[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
//    glVertexAttribPointer(cpyTextureCoords, 2, GL_FLOAT, 0, 0, cpyTexCoords);
//    glEnableVertexAttribArray(cpyTextureCoords);
//    
//    glViewport(imgPos.x, imgPos.y, imgPos.width, imgPos.height);
//    glActiveTexture(GL_TEXTURE0);
//    this->bindTexture(inputFrame->getTextureId());
//    glUniform1i(cpyTextureUniformSampler, 0);
//    this->draw();
//    glDisableVertexAttribArray(cpyTexturePosition);
//    glDisableVertexAttribArray(cpyTextureCoords);
//    GL_CHECK_ERROR("ImageWaterMaskEffect::renderEffect glDisableVertexAttribArray");
//    
//    ParamVal paramValTexId = getParamValHelper(string(WATER_MASK_PARAM_ID_TEXTURE_ID), filterCallback);
//    int maskTexId = paramValTexId.u.intVal;
//    if(0 != maskTexId){
//        glUseProgram(mGLProgId);
//        
//        glViewport(imgPos.x, imgPos.y, imgPos.width, imgPos.height);
//        static const GLfloat _vertices[] = { -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
//            1.0f, 1.0f, 1.0f };
//        glVertexAttribPointer(mGLVertexCoords, 2, GL_FLOAT, 0, 0, _vertices);
//        glEnableVertexAttribArray(mGLVertexCoords);
//        static const GLfloat texCoords[] = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
//        glVertexAttribPointer(mGLTextureCoords, 2, GL_FLOAT, 0, 0, texCoords);
//        glEnableVertexAttribArray(mGLTextureCoords);
//        /** 开启混合 **/
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        ParamVal paramValTextureWidth = getParamValHelper(string(WATER_MASK_PARAM_ID_IMAGE_WIDTH), filterCallback);
//        ParamVal paramValTextureHeight = getParamValHelper(string(WATER_MASK_PARAM_ID_IMAGE_HEIGHT), filterCallback);
//        ParamVal paramValTopPadding = getParamValHelper(string(WATER_MASK_TOP_PADDING), filterCallback);
//        ParamVal paramValLeftPadding = getParamValHelper(string(WATER_MASK_LEFT_PADDING), filterCallback);
//        ParamVal paramValWidth = getParamValHelper(string(WATER_MASK_SCALE_WIDTH), filterCallback);
//        ParamVal paramValAngle = getParamValHelper(string(WATER_MASK_ROTATE_ANGLE), filterCallback);
//        //构造缩放矩阵
//        float scaleMatrix[4 * 4];
//        matrixSetIdentityM(scaleMatrix);
//        float widthRatio = (float)paramValWidth.u.intVal/(float)paramValTextureWidth.u.intVal;
//        float verticleWidth = (float)imgPos.width;
//        float verticleHeight = (float)imgPos.height;
//        if(90 == paramValAngle.u.fltVal || 270 == paramValAngle.u.fltVal){
//            verticleWidth = (float)imgPos.height;
//            verticleHeight = (float)imgPos.width;
//        }
//        float widthScale = (float)paramValTextureWidth.u.intVal / verticleWidth * widthRatio;
//        float heightScale = (float)paramValTextureHeight.u.intVal / verticleHeight * widthRatio;
//        matrixScaleM(scaleMatrix, widthScale, heightScale, 1.0f);
//        //构造旋转矩阵
//        float rotateMatrix[4 * 4];
//        matrixSetIdentityM(rotateMatrix);
//        matrixRotateM(rotateMatrix, paramValAngle.u.fltVal, 0, 0, 1);
//        //构造位移矩阵
//        float translateMatrix[4 * 4];
//        matrixSetIdentityM(translateMatrix);
//        float xOffset = 2 * (((float)(paramValLeftPadding.u.intVal + paramValTextureWidth.u.intVal * widthRatio / 2) / (float)imgPos.width) - 0.5);
//        float yOffset = 2 * (((float)(paramValTopPadding.u.intVal + paramValTextureHeight.u.intVal * widthRatio / 2) / (float)imgPos.height) - 0.5);
//        matrixTranslateM(translateMatrix, xOffset, -1 * yOffset, 0.0f);
//        //组合位移与旋转矩阵
//        float transformMatrix[4 * 4];
//        matrixMultiplyMM(transformMatrix, translateMatrix, rotateMatrix);
//        //将上一步的结果组合缩放矩阵, 注意这里的顺序其实S->R->T 由于矩阵相乘 所以倒着写
//        float transformMatrix1[4 * 4];
//        matrixMultiplyMM(transformMatrix1, transformMatrix, scaleMatrix);
//        //最后将结果矩阵传递给OpenGL
//        glUniformMatrix4fv(mUniformTransforms, 1, GL_FALSE, (GLfloat *) transformMatrix1);
//        glActiveTexture(GL_TEXTURE0);
//        this->bindTexture(maskTexId);
//        glUniform1i(mGLUniformTexture, 0);
//        this->draw();
//        glDisableVertexAttribArray(mGLVertexCoords);
//        glDisableVertexAttribArray(mGLTextureCoords);
//        glDisable(GL_BLEND);
//    }
//    
//    glBindTexture(GL_TEXTURE_2D, 0);
//    this->switchFBODefaultAttachment();
//    GL_CHECK_ERROR("ImageWaterMaskEffect::renderEffect glBindFramebuffer 0 ");
}

void ImageWaterMaskEffect::destroy() {
    BaseVideoEffect::destroy();
    glDeleteProgram(cpyTextureProgId);
}
