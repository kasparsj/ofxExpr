#include "ofxExprParser.hpp"
#include "ofMath.h"

ofxExprParser::Time ofxExprParser::time;

ofxExprParser::ofxExprParser() : Parser() {
    DefineFun("rand", ofxExprParser::rand, false);
    DefineVar("t", &time.get());
}

float ofxExprParser::rand(const float* v, int numArgs) {
    switch (numArgs) {
        case 2:
            return ofRandom(v[0], v[1]);
        case 1:
            return ofRandom(v[0]);
        case 0:
        default:
            return ofRandom(1.f);
    }
}
