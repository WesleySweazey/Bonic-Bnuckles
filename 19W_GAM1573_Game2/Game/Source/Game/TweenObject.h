#ifndef __TweenObject_H__
#define __TweenObject_H__

#include "Game/TweenFunction.h"

class TweenObject
{
public:
    TweenFunction m_pFunction;
    float* m_modifierValue;
    float m_startValue;
    float m_endValue;
    double m_TweenTotalTime;
    double m_TweenTimePassed;
    bool bStart;
    bool bIsFinished;

    TweenObject();
    ~TweenObject();
    void SetUp(TweenFunction pFunction, float* pFloat, float startValue, float endValue, double tweenTime, bool start);
    void Update(float deltaTime);
    bool GetIsFinished() { return bIsFinished; }
};
#endif