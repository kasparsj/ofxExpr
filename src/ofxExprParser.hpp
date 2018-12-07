#pragma once

#include "muParser.h"
#include "ofEvents.h"
#include "ofEventUtils.h"

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
    
private:
    static float rand(const float* v, int numArgs);
    
};
