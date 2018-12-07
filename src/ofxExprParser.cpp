#include "ofxExprParser.hpp"
#include "ofMath.h"

ofxExprParser::Time ofxExprParser::time;

ofxExprParser::ofxExprParser() : Parser() {
    DefineFun("rand", ofxExprParser::rand, false);
    DefineFun("noise", ofxExprParser::noise, true);
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
