#include "ofxExprParser.hpp"
#include "ofMath.h"

ofxExprParser::Time ofxExprParser::time;

ofxExprParser::ofxExprParser() : Parser() {
    using namespace std::placeholders;
    
    DefineFun("rand", ofxExprParser::rand, false);
    DefineFun("noise", ofxExprParser::noise, true);
    DefineFun("fmod", ofxExprParser::fmod, true);
    
    const mu::UserData userData(this);
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
    
    DefineOprt("%", ofxExprParser::fmod, mu::prMUL_DIV);
    DefineVar("t", &time.get());
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

float ofxExprParser::elasticIn(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::elastic::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::elasticOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::elastic::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::elasticInOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::elastic::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expIn(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::exp::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::exp::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::expInOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::exp::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceIn(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::bounce::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::bounce::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::bounceInOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::bounce::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicIn(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::cubic::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::cubic::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::cubicInOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::cubic::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineIn(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::sine::easeIn, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::sine::easeOut, static_cast<ofxExprParser*>(userData.ptr));
}

float ofxExprParser::sineInOut(float time, float maxTime, const mu::UserData &userData) {
    return ease(time, maxTime, ofxeasing::sine::easeInOut, static_cast<ofxExprParser*>(userData.ptr));
}

template<typename Function>
float ofxExprParser::ease(float time, float maxTime, Function easing, ofxExprParser *parser) {
    return ofxeasing::map(fmod(time, maxTime), 0, maxTime, parser->getMin(), parser->getMax(), easing);
}

template<typename Function>
float ofxExprParser::ease(float time, float maxTime, float minOut, float maxOut, Function easing) {
    return ofxeasing::map(fmod(time, maxTime), 0, maxTime, minOut, maxOut, easing);
}
