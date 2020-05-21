#include "GamePCH.h"
#include "Game/TweenObject.h"
#include "Game/TweenFunction.h"

TweenObject::TweenObject()
{
    m_pFunction = TweenFunction_Linear;
    m_modifierValue = nullptr;
    m_startValue = 0.0f;
    m_endValue = 0.0f;
    m_TweenTotalTime = 0.0;
    m_TweenTimePassed = 0.0;
    bStart = true;
    bIsFinished = false;
}

TweenObject::~TweenObject()
{

}

void TweenObject::SetUp(TweenFunction pFunction, float* pFloat, float startValue, float endValue, double tweenTime, bool start)
{
    m_pFunction = pFunction;
    m_modifierValue = pFloat;
    m_startValue = startValue;
    m_endValue = endValue;
    m_TweenTotalTime = tweenTime;
    bStart = start;
    //add time pass and total time
}

void TweenObject::Update(float deltaTime)
{
    //float startvalue, float valuerange, double timepassed, double totaltime
    m_TweenTimePassed += deltaTime;
    float valuerange = m_endValue - m_startValue;
    float value = m_pFunction(m_startValue, valuerange, m_TweenTimePassed, m_TweenTotalTime);
    *m_modifierValue = value;
    if (m_TweenTimePassed > m_TweenTotalTime)
    {
        bIsFinished = true;
    }
}