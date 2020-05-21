#ifndef __TweenFunction_H__
#define __TweenFunction_H__

float TweenFunction_Linear(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_SineEaseIn(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_SineEaseOut(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_SineEaseInOut(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_BounceEaseIn(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_BounceEaseOut(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_BounceEaseInOut(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_ElasticEaseIn(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_ElasticEaseOut(float startvalue, float valuerange, double timepassed, double totaltime);
float TweenFunction_ElasticEaseInOut(float startvalue, float valuerange, double timepassed, double totaltime);

typedef float(*TweenFunction)(float startvalue, float valuerange, double timepassed, double totaltime);

#endif //__TweenTweenFunction_H__
