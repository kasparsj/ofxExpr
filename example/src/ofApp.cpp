#include "ofApp.h"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    float x = 123.0;
    float y = 678.0;
    float z = 57.0;
    
    ofxExpr expr;
    expr.set("x * y + 3", false);
    expr.addVar("x", x, false);
    expr.addVar("y", y);
    expr.addVar("z", z);
    cout << expr.get() << endl;
    cout << expr.hasExprSymbol("y") << endl;
    cout << expr.hasExprSymbol("z") << endl;
    
    x = 2;
    y = 3;
    cout << expr.get() << endl;
    
    expr.set("x + y");
    cout << expr.get() << endl;
    
    float i = -1.0;
    ofxExpr expr2;
    expr2.set("sin(x)");
    expr2.addVar("x", x);
    expr2.addVar("i", i);
    expr2.compile();
    cout << expr2.get() << endl;
    cout << expr2.hasExprSymbol("i") << endl;
    
    float a = 1.f;
    ofxVecExpr<glm::vec3> vecExpr;
    vecExpr.set("sin(a)");
    vecExpr.addVar("a", a);
    vecExpr.compile();
    cout << vecExpr.get() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
