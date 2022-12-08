#pragma once

#include "ofMain.h"
#include "ofxExpr.hpp"
#include "ofxVecExpr.hpp"

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
    
    ofxExpr expr1;
    ofxExpr expr2;
    ofxExpr expr3;
    ofxVecExpr<glm::vec3> vecExpr;
		
};
