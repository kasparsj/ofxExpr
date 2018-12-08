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
    static float ease(const float* v, int numArgs, Function easing, ofxExprParser *parser);
    template<typename Function>
    static float ease(float time, float curTime, float minOut, float maxOut, Function easing);

    static float elasticIn(const float* v, int numArgs, const mu::UserData &userData);
    static float elasticOut(const float* v, int numArgs, const mu::UserData &userData);
    static float elasticInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float expIn(const float* v, int numArgs, const mu::UserData &userData);
    static float expOut(const float* v, int numArgs, const mu::UserData &userData);
    static float expInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float bounceIn(const float* v, int numArgs, const mu::UserData &userData);
    static float bounceOut(const float* v, int numArgs, const mu::UserData &userData);
    static float bounceInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float cubicIn(const float* v, int numArgs, const mu::UserData &userData);
    static float cubicOut(const float* v, int numArgs, const mu::UserData &userData);
    static float cubicInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float sineIn(const float* v, int numArgs, const mu::UserData &userData);
    static float sineOut(const float* v, int numArgs, const mu::UserData &userData);
    static float sineInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float backIn(const float* v, int numArgs, const mu::UserData &userData);
    static float backOut(const float* v, int numArgs, const mu::UserData &userData);
    static float backInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float circIn(const float* v, int numArgs, const mu::UserData &userData);
    static float circOut(const float* v, int numArgs, const mu::UserData &userData);
    static float circInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quintIn(const float* v, int numArgs, const mu::UserData &userData);
    static float quintOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quintInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quartIn(const float* v, int numArgs, const mu::UserData &userData);
    static float quartOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quartInOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quadIn(const float* v, int numArgs, const mu::UserData &userData);
    static float quadOut(const float* v, int numArgs, const mu::UserData &userData);
    static float quadInOut(const float* v, int numArgs, const mu::UserData &userData);
    
    float min, max;
    
};
