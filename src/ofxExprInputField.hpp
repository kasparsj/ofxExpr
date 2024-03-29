#pragma once

#include "ofxGuiGroup.h"
#include "ofxInputField.h"
#include "ofxExpr.hpp"

class ofxExprInputField : public ofxGuiGroup {
    
public:
    ofxExprInputField() {}
    ofxExprInputField(const ofxFloatExpr& val, float width = defaultWidth, float height = defaultHeight);
    
    ofxExprInputField * setup(const ofxFloatExpr& value, float width = defaultWidth, float height = defaultHeight);
    ofxExprInputField * setup(const std::string& controlName, const float & value, const float & min, const float & max, float width = defaultWidth, float height = defaultHeight);
    
    ofAbstractParameter & getParameter();
    
    void clear();
    void minimize() {}
    void maximize() {}
    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args);
    void generateDraw();
    void render();
    void sizeChangedCB();
    
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, std::string & value);
    
    ofxFloatExpr value;
    ofxTextField * textField = NULL;
    ofxSlider<float> * slider = NULL;
    
    ofVboMesh textMesh;
    
};
