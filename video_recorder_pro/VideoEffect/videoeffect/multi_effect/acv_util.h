//
// Created by tianchi on 17-9-6.
//

#ifndef FILTERDEMO_ACV_UTIL_H
#define FILTERDEMO_ACV_UTIL_H

#include <list>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
//
//typedef unsigned char byte;
//
//typedef struct PointF
//{
//    float x;
//    float y;
//    bool operator < (PointF *point) const
//    {
//        return x < point->x;
//    }
//    bool operator > (PointF *point) const
//    {
//        return x > point->x;
//    }
//    PointF(float x, float y):x(x),y(y){
//        //DO NOTHING HERE
//    };
//} PointF;
//class acv_util{
//public:
//    acv_util();
//    virtual ~acv_util();
//    void parse(unsigned char * data, int len, unsigned char ** out);
//private:
//    byte* mACVBuffer;
//    int mACVBufferSize;
//
//    void fillControlPointsFromACVBuffer();
//    short readShortFromACVBuffer();
//
//    std::vector<PointF*>* mRgbCompositeControlPoints;
//    std::vector<PointF*>* mRedControlPoints;
//    std::vector<PointF*>* mGreenControlPoints;
//    std::vector<PointF*>* mBlueControlPoints;
//
//    std::vector<float>* mRgbCompositeCurve;
//    std::vector<float>* mRedCurve;
//    std::vector<float>* mGreenCurve;
//    std::vector<float>* mBlueCurve;
//
//    std::vector<float>* createSplineCurve(std::vector<PointF*>* points);
//    std::vector<double>* createSecondDerivative(std::vector<PointF*>* points);
//    std::vector<PointF*>* createSplineCurve2(std::vector<PointF*>* convertedPoints);
//};


#endif //FILTERDEMO_ACV_UTIL_H
