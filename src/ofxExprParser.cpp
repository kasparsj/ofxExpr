#include "ofxExprParser.hpp"
#include "ofMath.h"

ofxExprParser::Time ofxExprParser::time;

ofxExprParser::ofxExprParser() : Parser() {
    const mu::UserData userData(this);
    DefineFun("rand", ofxExprParser::rand, false);
    DefineFun("noise", ofxExprParser::noise, true);
    DefineFun("fmod", ofxExprParser::fmod, true);
    DefineFun("toAndBack", ofxExprParser::toAndBack, true);
    DefineFun("elasticIn", ofxExprParser::elasticIn, userData, true);
    DefineFun("elasticOut", ofxExprParser::elasticOut, userData, true);
    DefineFun("elasticInOut", ofxExprParser::elasticInOut, userData, true);
    DefineFun("expIn", ofxExprParser::expIn, userData, true);
    DefineFun("expOut", ofxExprParser::expOut, userData, true);
    DefineFun("expInOut", ofxExprParser::expInOut, userData, true);
    DefineFun("bounceIn", ofxExprParser::bounceIn, userData, true);
    DefineFun("bounceOut", ofxExprParser::bounceOut, userData, true);
    DefineFun("bounceInOut", ofxExprParser::bounceInOut, userData, true);
    DefineFun("cubicIn", ofxExprParser::cubicIn, userData, true);
    DefineFun("cubicOut", ofxExprParser::cubicOut, userData, true);
    DefineFun("cubicInOut", ofxExprParser::cubicInOut, userData, true);
    DefineFun("sineIn", ofxExprParser::sineIn, userData, true);
    DefineFun("sineOut", ofxExprParser::sineOut, userData, true);
    DefineFun("sineInOut", ofxExprParser::sineInOut, userData, true);
    DefineFun("backIn", ofxExprParser::backIn, userData, true);
    DefineFun("backOut", ofxExprParser::backOut, userData, true);
    DefineFun("backInOut", ofxExprParser::backInOut, userData, true);
    DefineFun("circIn", ofxExprParser::circIn, userData, true);
    DefineFun("circOut", ofxExprParser::circOut, userData, true);
    DefineFun("circInOut", ofxExprParser::circInOut, userData, true);
    DefineFun("quintIn", ofxExprParser::quintIn, userData, true);
    DefineFun("quintOut", ofxExprParser::quintOut, userData, true);
    DefineFun("quintInOut", ofxExprParser::quintInOut, userData, true);
    DefineFun("quartIn", ofxExprParser::quartIn, userData, true);
    DefineFun("quartOut", ofxExprParser::quartOut, userData, true);
    DefineFun("quartInOut", ofxExprParser::quartInOut, userData, true);
    DefineFun("quadIn", ofxExprParser::quadIn, userData, true);
    DefineFun("quadOut", ofxExprParser::quadOut, userData, true);
    DefineFun("quadInOut", ofxExprParser::quadInOut, userData, true);
    
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

float ofxExprParser::elasticIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::elastic::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::elasticOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::elastic::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::elasticInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::elastic::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::exp::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::exp::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::exp::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::bounce::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::bounce::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::bounce::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::cubic::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::cubic::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::cubic::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::sine::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::sine::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::sine::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::backIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::back::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::backOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::back::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::backInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::back::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::circIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::circ::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::circOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::circ::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::circInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::circ::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quintIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quint::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quintOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quint::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quintInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quint::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quartIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quart::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quartOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quart::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quartInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quart::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quadIn(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quad::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quadOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quad::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::quadInOut(const float* v, int numArgs, const mu::UserData &userData) {
    return ease(v, numArgs, ofxeasing::quad::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
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
