#pragma once

#include "ofxGuiGroup.h"
#include "ofxExpr.hpp"

template<class VecType>
class ofxVecExprInputField : public ofxGuiGroup {
public:
    ofxVecExprInputField() {};
    ofxVecExprInputField(ofxExpr<VecType> value, float width = defaultWidth, float height = defaultHeight);
    
    ofxVecExprInputField<VecType> * setup(ofxExpr<VecType> &value, float width = defaultWidth, float height = defaultHeight);
    ofxVecExprInputField<VecType> * setup(const std::string& controlName, const VecType & value, const VecType & min, const VecType & max, float width = defaultWidth, float height = defaultHeight);
    
    ofAbstractParameter & getParameter();
    
    ofxExpr<VecType> operator=(const ofxExpr<VecType> & v);
    operator const ofxExpr<VecType> & ();
protected:
    void changeSlider(const void * parameter, float & value);
    void changeInputField(const void * parameter, std::string & value);
    ofxExpr<VecType> value;
};
