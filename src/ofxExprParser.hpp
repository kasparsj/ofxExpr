#pragma once

#include "muParser.h"
#include "ofEvents.h"
#include "ofEventUtils.h"
#include "ofxEasing.h"

class ofxExprParser : public mu::Parser {
    
public:
    class Time {
    public:
        float &get() {
            if (!intialized) {
                ofAddListener(ofEvents().update, this, &Time::update, OF_EVENT_ORDER_BEFORE_APP);
                elapsedTimef = ofGetElapsedTimef();
                intialized = true;
            }
            return elapsedTimef;
        }
        void update(ofEventArgs &e) {
            elapsedTimef = ofGetElapsedTimef();
        }
    private:
        bool intialized = false;
        float elapsedTimef;
    };
    static Time time;
    
    ofxExprParser();
    using ParserBase::operator=;
    void setMin(const float &m) {
        min = m;
    }
    void setMax(const float &m) {
        max = m;
    }
    const float &getMin() const {
        return min;
    }
    const float &getMax() const {
        return max;
    }
    
private:
    static float rand(const float* v, int numArgs);
    static float noise(const float* v, int numArgs);
    static float fmod(float v1, float v2);
    
    template<typename Function>
    static float ease(float time, float maxTime, Function easing, ofxExprParser *parser);
    template<typename Function>
    static float ease(float time, float curTime, float minOut, float maxOut, Function easing);

    static float elasticIn(float time, float maxTime, const mu::UserData &userData);
    static float elasticOut(float time, float maxTime, const mu::UserData &userData);
    static float elasticInOut(float time, float maxTime, const mu::UserData &userData);
    static float expIn(float time, float maxTime, const mu::UserData &userData);
    static float expOut(float time, float maxTime, const mu::UserData &userData);
    static float expInOut(float time, float maxTime, const mu::UserData &userData);
    static float bounceIn(float time, float maxTime, const mu::UserData &userData);
    static float bounceOut(float time, float maxTime, const mu::UserData &userData);
    static float bounceInOut(float time, float maxTime, const mu::UserData &userData);
    static float cubicIn(float time, float maxTime, const mu::UserData &userData);
    static float cubicOut(float time, float maxTime, const mu::UserData &userData);
    static float cubicInOut(float time, float maxTime, const mu::UserData &userData);
    static float sineIn(float time, float maxTime, const mu::UserData &userData);
    static float sineOut(float time, float maxTime, const mu::UserData &userData);
    static float sineInOut(float time, float maxTime, const mu::UserData &userData);
    
    float min, max;
    
};
