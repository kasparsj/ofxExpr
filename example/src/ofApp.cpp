#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    float x = 123.0;
    float y = 678.0;
    float z = 57.0;
    
    expr1.set("x * y + 3");
    expr1.addVar("x", x, false);
    expr1.addVar("y", y);
    expr1.addVar("z", z);
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << expr1.getExpression() << " = " << expr1.get() << endl;
    cout << "expr1.hasExprSymbol(\"y\"): " << expr1.hasExprSymbol("y") << endl;
    cout << "expr1.hasExprSymbol(\"z\"): " << expr1.hasExprSymbol("z") << endl;
    
    x = 2;
    y = 3;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << expr1.getExpression() << " = " << expr1.get() << endl;
    
    expr1.set("x + y");
    cout << expr1.getExpression() << " = " << expr1.get() << endl;
    
    float i = -1.0;
    expr2.set("sin(x)");
    expr2.addVar("x", x);
    expr2.addVar("i", i);
    cout << expr2.getExpression() << " = " << expr2.get() << endl;
    cout << "expr2.hasExprSymbol(\"i\"): " << expr2.hasExprSymbol("i") << endl;
    
    expr3.set("t");
    cout << expr3.getExpression() << " = " << expr3.get() << endl;
    
    expr4.set("rand(x)");
    expr4.addVar("x", x);
    cout << expr4.getExpression() << " = " << expr4.get() << endl;
    cout << expr4.getExpression() << " = " << expr4.get() << endl;
    
    expr4.set("noise(x)");
    expr4.addVar("x", x);
    cout << expr4.getExpression() << " = " << expr4.get() << endl;
    
    float a = 1.f;
    cout << "a = " << a << endl;
    vecExpr[0]->set("sin(a)");
    vecExpr[1]->set("cos(a)");
    vecExpr[2]->set("tan(a)");
    vecExpr.addVar("a", a);
    cout << vecExpr.get() << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    static int i = 0;
    if (i < 2) {
        cout << expr3.getExpression() << " = " << expr3.get() << endl;
    }
    i++;
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
