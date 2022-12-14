#pragma once

#include "ofMain.h"
#include "ofxExpr.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxFloatExpr expr1;
    ofxFloatExpr expr2;
    ofxFloatExpr expr3;
    ofxFloatExpr expr4;
    ofxExpr<glm::vec3> vecExpr;
    ofxExpr<glm::mat4> matExpr;
    ofxExpr<ofFloatColor> colorExpr;
    ofxFloatExpr lineExpr;
    ofxFloatExpr linearExpr;
    ofxFloatExpr expExpr;
		
};
