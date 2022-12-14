#pragma once

#include "muParser.h"
#include "ofEvents.h"
#include "ofEventUtils.h"
#include "ofxEasing.h"

class ofxExprParser : public mu::Parser {
    
public:
    class Time {
    public:
        void init() {
            if (!intialized) {
                ofAddListener(ofEvents().update, this, &Time::update, OF_EVENT_ORDER_BEFORE_APP);
                elapsedTimef = ofGetElapsedTimef();
                frameNum = ofGetFrameNum();
                intialized = true;
            }
        }
        float &getTime() {
            init();
            return elapsedTimef;
        }
        float &getFrame() {
            init();
            return frameNum;
        }
        void update(ofEventArgs &e) {
            elapsedTimef = ofGetElapsedTimef();
            frameNum = ofGetFrameNum();
        }
    private:
        bool intialized = false;
        float elapsedTimef;
        float frameNum;
    };
    static Time time;
    
    ofxExprParser();
    using ParserBase::operator=;
    void set(const std::string& expr) {
        SetExpr(expr);
        setTimef = time.getTime();
    }
    void setMin(const float &m) {
        min = m;
    }
    void setMax(const float &m) {
        max = m;
    }
    const float& getMin() const {
        return min;
    }
    const float& getMax() const {
        return max;
    }
    const float& getSetTime() const {
        return setTimef;
    }
    
private:
    static float rand(const float* v, int numArgs);
    static float noise(const float* v, int numArgs);
    static float fmod(float v1, float v2);
    static float line(void* userData, const float* v, int numArgs);
    static float toAndBack(const float* v, int numArgs);
    
    template<typename Function>
    static float ease(const float* v, int numArgs, Function easing, ofxExprParser *parser);
    template<typename Function>
    static float ease(float time, float curTime, float minOut, float maxOut, Function easing);

    static float linear(void* userData, const float* v, int numArgs);
    static float elasticIn(void* userData, const float* v, int numArgs);
    static float elasticOut(void* userData, const float* v, int numArgs);
    static float elasticInOut(void* userData, const float* v, int numArgs);
    static float expIn(void* userData, const float* v, int numArgs);
    static float expOut(void* userData, const float* v, int numArgs);
    static float expInOut(void* userData, const float* v, int numArgs);
    static float bounceIn(void* userData, const float* v, int numArgs);
    static float bounceOut(void* userData, const float* v, int numArgs);
    static float bounceInOut(void* userData, const float* v, int numArgs);
    static float cubicIn(void* userData, const float* v, int numArgs);
    static float cubicOut(void* userData, const float* v, int numArgs);
    static float cubicInOut(void* userData, const float* v, int numArgs);
    static float sineIn(void* userData, const float* v, int numArgs);
    static float sineOut(void* userData, const float* v, int numArgs);
    static float sineInOut(void* userData, const float* v, int numArgs);
    static float backIn(void* userData, const float* v, int numArgs);
    static float backOut(void* userData, const float* v, int numArgs);
    static float backInOut(void* userData, const float* v, int numArgs);
    static float circIn(void* userData, const float* v, int numArgs);
    static float circOut(void* userData, const float* v, int numArgs);
    static float circInOut(void* userData, const float* v, int numArgs);
    static float quintIn(void* userData, const float* v, int numArgs);
    static float quintOut(void* userData, const float* v, int numArgs);
    static float quintInOut(void* userData, const float* v, int numArgs);
    static float quartIn(void* userData, const float* v, int numArgs);
    static float quartOut(void* userData, const float* v, int numArgs);
    static float quartInOut(void* userData, const float* v, int numArgs);
    static float quadIn(void* userData, const float* v, int numArgs);
    static float quadOut(void* userData, const float* v, int numArgs);
    static float quadInOut(void* userData, const float* v, int numArgs);
    
    float min, max;
    float setTimef;
    
};
