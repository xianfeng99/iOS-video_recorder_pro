//
// Created by tianchi on 17-9-6.
//

#include "acv_util.h"

//acv_util::acv_util(){
//}
//
//acv_util::~acv_util() {
//}
//
//bool compare(PointF* src, PointF* target) {
//    return (src->x < target->x);
//}
//
//bool compareFloat(float src, float target) {
//    return (src < target);
//}
//void acv_util::parse(unsigned char * data, int len, unsigned char ** out) {
//    this->mACVBuffer = data;
//    this->mACVBufferSize = len;
//    fillControlPointsFromACVBuffer();
//    mRgbCompositeCurve = createSplineCurve(mRgbCompositeControlPoints);
//    mRedCurve = createSplineCurve(mRedControlPoints);
//    mGreenCurve = createSplineCurve(mGreenControlPoints);
//    mBlueCurve = createSplineCurve(mBlueControlPoints);
//    delete mRgbCompositeControlPoints;
//    delete mRedControlPoints;
//    delete mGreenControlPoints;
//    delete mBlueControlPoints;
//
//    byte * res = (byte *)malloc(sizeof(unsigned char) * 256 * 4);
//    if ((mRedCurve->size() >= 256) && (mGreenCurve->size() >= 256) && (mBlueCurve->size() >= 256) && (mRgbCompositeCurve->size() >= 256)) {
//        for (int currentCurveIndex = 0; currentCurveIndex < 256; currentCurveIndex++) {
//            // BGRA for upload to texture
//            res[currentCurveIndex * 4] = (byte) ((int) std::min(std::max(currentCurveIndex + mRedCurve->at(currentCurveIndex) + mRgbCompositeCurve->at(currentCurveIndex), 0.0f, compareFloat), 255.0f, compareFloat) & 0xff);
//            res[currentCurveIndex * 4 + 1] = (byte) ((int) std::min(std::max(currentCurveIndex + mGreenCurve->at(currentCurveIndex) + mRgbCompositeCurve->at(currentCurveIndex), 0.0f, compareFloat), 255.0f, compareFloat) & 0xff);
//            res[currentCurveIndex * 4 + 2] = (byte) ((int) std::min(std::max(currentCurveIndex + mBlueCurve->at(currentCurveIndex) + mRgbCompositeCurve->at(currentCurveIndex), 0.0f, compareFloat), 255.0f, compareFloat) & 0xff);
//            res[currentCurveIndex * 4 + 3] = (byte) (0xff);
//        }
////        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256 /*width*/, 1 /*height*/, 0, GL_RGBA, GL_UNSIGNED_BYTE, toneCurveByteArray);
//    }
//    delete mRgbCompositeCurve;
//    delete mRedCurve;
//    delete mGreenCurve;
//    delete mBlueCurve;
//    this->mACVBuffer = NULL;
//    *out = res;
//}
//
//void acv_util::fillControlPointsFromACVBuffer() {
//    int version = readShortFromACVBuffer();
//    int totalCurves = readShortFromACVBuffer();
//
//    float pointRate = 1.0f / 255;
//    for (int i = 0; i < totalCurves; i++) {
//        if(i > 3){
//            return;
//        }
//        // 2 bytes, Count of points in the curve (short integer from 2...19)
//        short pointCount = readShortFromACVBuffer();
//        std::vector<PointF*>* points = new std::vector<PointF*>();
//        // point count * 4
//        // Curve points. Each curve point is a pair of short integers where
//        // the first number is the output value (vertical coordinate on the
//        // Curves dialog graph) and the second is the input value. All coordinates have range 0 to 255.
//        for (int j = 0; j < pointCount; j++) {
//            short y = readShortFromACVBuffer();
//            short x = readShortFromACVBuffer();
//            points->push_back(new PointF(x * pointRate, y * pointRate));
//        }
//        if (i == 0) {
//            mRgbCompositeControlPoints = points;
//        } else if (i == 1) {
//            mRedControlPoints = points;
//        } else if (i == 2) {
//            mGreenControlPoints = points;
//        } else if (i == 3) {
//            mBlueControlPoints = points;
//        }
//    }
//}
//
//short acv_util::readShortFromACVBuffer() {
//    short highBit = *mACVBuffer << 8;
//    mACVBuffer++;
//    short lowBit = *mACVBuffer;
//    mACVBuffer++;
//    return (short) (highBit | lowBit);
//}
//
//std::vector<double>* acv_util::createSecondDerivative(std::vector<PointF*>* points) {
//    int n = points->size();
//    if (n <= 1) {
//        return NULL;
//    }
//
//    double matrix[n][3];
//    double result[n];
//
//    matrix[0][1] = 1;
//    // What about matrix[0][1] and matrix[0][0]? Assuming 0 for now (Brad L.)
//    matrix[0][0] = 0;
//    matrix[0][2] = 0;
//
//    for (int i = 1; i < n - 1; i++) {
//        PointF* P1 = points->at(i - 1);
//        PointF* P2 = points->at(i);
//        PointF* P3 = points->at(i + 1);
//
//        matrix[i][0] = (double) (P2->x - P1->x) / 6;
//        matrix[i][1] = (double) (P3->x - P1->x) / 3;
//        matrix[i][2] = (double) (P3->x - P2->x) / 6;
//        result[i] = (double) (P3->y - P2->y) / (P3->x - P2->x) - (double) (P2->y - P1->y) / (P2->x - P1->x);
//    }
//
//    // What about result[0] and result[n-1]? Assuming 0 for now (Brad L.)
//    result[0] = 0;
//    result[n - 1] = 0;
//
//    matrix[n - 1][1] = 1;
//    // What about matrix[n-1][0] and matrix[n-1][2]? For now, assuming they are 0 (Brad L.)
//    matrix[n - 1][0] = 0;
//    matrix[n - 1][2] = 0;
//
//    // solving pass1 (up->down)
//    for (int i = 1; i < n; i++) {
//        double k = matrix[i][0] / matrix[i - 1][1];
//        matrix[i][1] -= k * matrix[i - 1][2];
//        matrix[i][0] = 0;
//        result[i] -= k * result[i - 1];
//    }
//    // solving pass2 (down->up)
//    for (int i = n - 2; i >= 0; i--) {
//        double k = matrix[i][2] / matrix[i + 1][1];
//        matrix[i][1] -= k * matrix[i + 1][0];
//        matrix[i][2] = 0;
//        result[i] -= k * result[i + 1];
//    }
//
//    std::vector<double>* output = new std::vector<double>();
//    for (int i = 0; i < n; i++) {
//        output->push_back(result[i] / matrix[i][1]);
//    }
//    return output;
//}
//
//std::vector<PointF*>* acv_util::createSplineCurve2(std::vector<PointF*>* points) {
//    std::vector<double>* sdA = createSecondDerivative(points);
//    // Is [points count] equal to [sdA count]?
////    int n = [points count];
//    int n = sdA->size();
//    if (n < 1) {
//        return NULL;
//    }
//
//    double sd[n];
//    for (int i = 0; i < n; i++) {
//        sd[i] = sdA->at(i);
//    }
//    //FIX Memory Leak
//    delete sdA;
//    std::vector<PointF*>* output = new std::vector<PointF*>();
//
//    for (int i = 0; i < n - 1; i++) {
//        PointF *cur = points->at(i);
//        PointF *next = points->at(i + 1);
//        for (int x = cur->x; x < next->x; x++) {
//            double t = (double) (x - cur->x) / (next->x - cur->x);
//            double a = 1 - t;
//            double b = t;
//            double h = next->x - cur->x;
//            double y = a * cur->y + b * next->y + (h * h / 6) * ((a * a * a - a) * sd[i] + (b * b * b - b) * sd[i + 1]);
//            if (y > 255.0) {
//                y = 255.0;
//            } else if (y < 0.0) {
//                y = 0.0;
//            }
//            output->push_back(new PointF(x, (int) round(y)));
//        }
//    }
//
//    // If the last point is (255, 255) it doesn't get added.
//    if (output->size() == 255) {
//        PointF* pointF = points->at(points->size() - 1);
//        output->push_back(new PointF(pointF->x, pointF->y));
//    }
//    return output;
//
//}
//
//std::vector<float>* acv_util::createSplineCurve(std::vector<PointF*>* points) {
//    if (NULL == points || points->empty()) {
//        return NULL;
//    }
//
//    // Sort the array
////    points->sort();
//    sort(points->begin(), points->end(), compare);
//
//    // Convert from (0, 1) to (0, 255).
//    std::vector<PointF*>* convertedPoints = new std::vector<PointF*>();
//    std::vector<PointF*>::iterator i;
//    for (i = points->begin(); i != points->end(); ++i) {
//        PointF* point = *i;
//        convertedPoints->push_back(new PointF((int) (point->x * 255), (int) (point->y * 255)));
//        //FIX Memory Leak
//        delete point;
//    }
//    std::vector<PointF*>* splinePoints = createSplineCurve2(convertedPoints);
//
//    for (i = convertedPoints->begin(); i != convertedPoints->end(); ++i) {
//        PointF* point = *i;
//        //FIX Memory Leak
//        delete point;
//    }
//    delete convertedPoints;
//    // If we have a first point like (0.3, 0) we'll be missing some points at the beginning
//    // that should be 0. = splinePoints->begin();
//    PointF* firstSplinePoint = splinePoints->front();
//    if (firstSplinePoint->x > 0) {
//        for (int i = firstSplinePoint->x; i >= 0; i--) {
//            splinePoints->insert(splinePoints->begin(), new PointF(i, 0));
//        }
//    }
//
//    // Insert points similarly at the end, if necessary.
//    PointF* lastSplinePoint = splinePoints->back();
//    if (lastSplinePoint->x < 255) {
//        for (int i = lastSplinePoint->x + 1; i <= 255; i++) {
//            splinePoints->push_back(new PointF(i, 255));
//        }
//    }
//
//    // Prepare the spline points.
//    std::vector<PointF*>::iterator splinePointsIte;
//    std::vector<float>* preparedSplinePoints = new std::vector<float>();
//    for (splinePointsIte = splinePoints->begin(); splinePointsIte != splinePoints->end(); ++splinePointsIte) {
//        PointF* newPoint = *splinePointsIte;
//        PointF* origPoint = new PointF(newPoint->x, newPoint->x);
//        float distance = (float) sqrt(pow((origPoint->x - newPoint->x), 2.0) + pow((origPoint->y - newPoint->y), 2.0));
//        if (origPoint->y > newPoint->y) {
//            distance = -distance;
//        }
//        //FIX Memory Leak
//        delete origPoint;
//        delete newPoint;
//        preparedSplinePoints->push_back(distance);
//    }
//    //FIX Memory Leak
//    delete splinePoints;
//    return preparedSplinePoints;
//}

