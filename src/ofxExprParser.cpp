#include "ofxExprParser.hpp"
#include "ofMath.h"

ofxExprParser::Time ofxExprParser::time;

ofxExprParser::ofxExprParser() : Parser() {
    void* userData(this);
    DefineFun("rand", ofxExprParser::rand, false);
    DefineFun("noise", ofxExprParser::noise, true);
    DefineFun("fmod", ofxExprParser::fmod, true);
    DefineFunUserData("line", ofxExprParser::line, userData, true);
    DefineFun("toAndBack", ofxExprParser::toAndBack, true);
    DefineFunUserData("linear", ofxExprParser::linear, userData, true);
    DefineFunUserData("elasticIn", ofxExprParser::elasticIn, userData, true);
    DefineFunUserData("elasticOut", ofxExprParser::elasticOut, userData, true);
    DefineFunUserData("elasticInOut", ofxExprParser::elasticInOut, userData, true);
    DefineFunUserData("expIn", ofxExprParser::expIn, userData, true);
    DefineFunUserData("expOut", ofxExprParser::expOut, userData, true);
    DefineFunUserData("expInOut", ofxExprParser::expInOut, userData, true);
    DefineFunUserData("bounceIn", ofxExprParser::bounceIn, userData, true);
    DefineFunUserData("bounceOut", ofxExprParser::bounceOut, userData, true);
    DefineFunUserData("bounceInOut", ofxExprParser::bounceInOut, userData, true);
    DefineFunUserData("cubicIn", ofxExprParser::cubicIn, userData, true);
    DefineFunUserData("cubicOut", ofxExprParser::cubicOut, userData, true);
    DefineFunUserData("cubicInOut", ofxExprParser::cubicInOut, userData, true);
    DefineFunUserData("sineIn", ofxExprParser::sineIn, userData, true);
    DefineFunUserData("sineOut", ofxExprParser::sineOut, userData, true);
    DefineFunUserData("sineInOut", ofxExprParser::sineInOut, userData, true);
    DefineFunUserData("backIn", ofxExprParser::backIn, userData, true);
    DefineFunUserData("backOut", ofxExprParser::backOut, userData, true);
    DefineFunUserData("backInOut", ofxExprParser::backInOut, userData, true);
    DefineFunUserData("circIn", ofxExprParser::circIn, userData, true);
    DefineFunUserData("circOut", ofxExprParser::circOut, userData, true);
    DefineFunUserData("circInOut", ofxExprParser::circInOut, userData, true);
    DefineFunUserData("quintIn", ofxExprParser::quintIn, userData, true);
    DefineFunUserData("quintOut", ofxExprParser::quintOut, userData, true);
    DefineFunUserData("quintInOut", ofxExprParser::quintInOut, userData, true);
    DefineFunUserData("quartIn", ofxExprParser::quartIn, userData, true);
    DefineFunUserData("quartOut", ofxExprParser::quartOut, userData, true);
    DefineFunUserData("quartInOut", ofxExprParser::quartInOut, userData, true);
    DefineFunUserData("quadIn", ofxExprParser::quadIn, userData, true);
    DefineFunUserData("quadOut", ofxExprParser::quadOut, userData, true);
    DefineFunUserData("quadInOut", ofxExprParser::quadInOut, userData, true);
    
    DefineOprt("%", ofxExprParser::fmod, mu::prMUL_DIV);
    DefineVar("t", &time.getTime());
    DefineVar("f", &time.getFrame());
    DefineVar("min", &min);
    DefineVar("max", &max);
}

float ofxExprParser::rand(const float* v, int numArgs) {
    switch (numArgs) {
        case 1:
            return ofRandom(v[0]);
        case 2:
        default:
            return ofRandom(v[0], v[1]);
    }
}

float ofxExprParser::noise(const float* v, int numArgs) {
    switch (numArgs) {
        case 1:
            return ofNoise(v[0]);
        case 2:
            return ofNoise(v[0], v[1]);
        case 3:
            return ofNoise(v[0], v[1], v[2]);
        case 4:
        default:
            return ofNoise(v[0], v[1], v[2], v[3]);
    }
}

float ofxExprParser::fmod(float v1, float v2) {
    return std::fmod(v1, v2);
}

float ofxExprParser::line(void* userData, const float* v, int numArgs) {
    float setTimef = static_cast<ofxExprParser*>(userData)->getSetTime();
    switch (numArgs) {
        case 3:
            return ofMap(time.getTime(), setTimef, setTimef + v[2], v[0], v[1], true);
        case 2:
        default:
            return ofMap(time.getTime(), setTimef, setTimef + v[1], 0, v[0], true);
    }
}

float ofxExprParser::toAndBack(const float* v, int numArgs) {
    float from = 0;
    float to;
    switch (numArgs) {
        case 2:
            to = v[1];
            break;
        case 3:
        default:
            from = v[1];
            to = v[2];
            break;
    }
    // todo: fix for 30, 0
    float twoV;
    float range = (to - from);
    twoV = std::fmod(v[0], range * 2.f);
    return twoV > to ? to - std::fmod(twoV, range) : twoV;
}

float ofxExprParser::linear(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::linear::easeNone, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::elasticIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::elastic::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::elasticOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::elastic::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::elasticInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::elastic::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::expIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::exp::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::expOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::exp::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::expInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::exp::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::bounceIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::bounce::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::bounceOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::bounce::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::bounceInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::bounce::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::cubicIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::cubic::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::cubicOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::cubic::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::cubicInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::cubic::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::sineIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::sine::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::sineOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::sine::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::sineInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::sine::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::backIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::back::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::backOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::back::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::backInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::back::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::circIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::circ::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::circOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::circ::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::circInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::circ::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quintIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quint::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quintOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quint::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quintInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quint::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quartIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quart::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quartOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quart::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quartInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quart::easeInOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quadIn(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quad::easeIn, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quadOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quad::easeOut, static_cast<ofxExprParser*>(userData));
}

float ofxExprParser::quadInOut(void* userData, const float* v, int numArgs) {
    return ease(v, numArgs, ofxeasing::quad::easeInOut, static_cast<ofxExprParser*>(userData));
}

template<typename Function>
float ofxExprParser::ease(const float* v, int numArgs, Function easing, ofxExprParser *parser) {
    switch (numArgs) {
        case 4:
            return ofxeasing::map(std::fmod(v[0], v[1]), 0, v[1], v[2], v[3], easing);
        case 3:
            return ofxeasing::map(std::fmod(v[0], v[1]), 0, v[1], parser->getMin(), v[2], easing);
        case 2:
        default:
            return ofxeasing::map(std::fmod(v[0], v[1]), 0, v[1], parser->getMin(), parser->getMax(), easing);
    }
}

template<typename Function>
float ofxExprParser::ease(float time, float maxTime, float minOut, float maxOut, Function easing) {
    return ofxeasing::map(fmod(time, maxTime), 0, maxTime, minOut, maxOut, easing);
}
