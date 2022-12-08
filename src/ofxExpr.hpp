#pragma once

#include "ofMain.h"
#include "muParser.h"
#include "ofxExprParser.hpp"

class ofxExpr : public ofParameterGroup {
    
public:
    static const std::string NAME_EXPR;
    static const std::string NAME_VALUE;
    static const std::string NAME_EXPLICIT;
    
    ofxExpr();
    ~ofxExpr();
    ofxExpr(const std::string &name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expression, const float &value, bool isExplicit = false);
    ofxExpr(const std::string &name, const std::string &expr);
    ofxExpr(const std::string &name, const float &value, bool isExplicit = true);
    ofxExpr(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr(const ofxExpr& other);
    ofxExpr& operator= (const ofxExpr& other);
    
    float get() const;
    const std::string & getExpression() const {
        return pExpr->get();
    }
    const float & getValue() const {
        return pValue->get();
    }
    float getMin() const {
        return pValue->getMin();
    }
    float getMax() const {
        return pValue->getMax();
    }
    const bool isExplicit() const {
        return pExplicit->get();
    }
    const bool hasError() const {
        return !compiled;
    }
    
    ofxExpr & set(const std::string &expression);
    ofxExpr & set(const float &value, bool isExplicit = true);
    ofxExpr & set(const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr & set(const std::string &name, const float &value, bool isExplicit = true);
    ofxExpr & set(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit = true);
    ofxExpr & set(const std::string & name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit = false);
    ofxExpr & setExplicit(bool isExplicit);
    void setMin(const float &min) {
        pValue->setMin(min);
        parser.setMin(min);
    }
    void setMax(const float &max) {
        pValue->setMax(max);
        parser.setMax(max);
    }
    ofxExpr & setSliderMinMax(const float &min, const float &max) {
        pValue->setMin(min);
        pValue->setMax(max);
        return *this;
    }
    void setRandom() {
        set(ofRandom(getMin(), getMax()));
    }
    
    const float getExprValue() const;
    bool hasVar(const std::string &name) const;
    bool addVar(const std::string &name, float &value, bool recompile = true);
    bool addDummyVar(const std::string &name, bool recompile = true);
    bool hasConst(const std::string &name) const;
    bool addConst(const std::string &name, const float &value, bool recompile = true);
    bool hasExprSymbol(const std::string &name) const;
    bool isTimeDependent() const;
    bool compile();
    
    const mu::Parser &getParser() const {
        return parser;
    }
    
    const std::shared_ptr<ofParameter<std::string>> & getExpressionParameter() const {
        return pExpr;
    }
    const std::shared_ptr<ofParameter<float>> & getValueParameter() const {
        return pValue;
    }
    const std::shared_ptr<ofParameter<bool>> & getExplicitParameter() const {
        return pExplicit;
    }

    template<typename ParameterType>
    const ofParameter<ParameterType> & get(const std::string& name) const {
        return ofParameterGroup::get<ParameterType>(name);
    }
    template<typename ParameterType>
    ofParameter<ParameterType> & get(const std::string& name) {
        return ofParameterGroup::get<ParameterType>(name);
    }
    
    bool operator== (const ofxExpr &e2) const;
    bool operator!= (const ofxExpr &e2) const;
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxExpr & mom);
    
private:
    
    void setExprParameter(const std::shared_ptr<ofParameter<std::string>> & pExpr);
    void onChangeExpr(std::string &expr);
    void notCompiled(bool recompile);
    
    ofxExprParser parser;
    float dummyVal;
    bool compiled = false;
    
    std::shared_ptr<ofParameter<std::string>> pExpr;
    std::shared_ptr<ofParameter<float>> pValue;
    std::shared_ptr<ofParameter<bool>> pExplicit;
};
