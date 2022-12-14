#pragma once

#include "ofMain.h"
#include "muParser.h"
#include "ofxExprParser.hpp"

template<typename Type>
class ofxExpr_ : public ofParameterGroup {
    
public:
    static const std::string NAME_EXPR;
    static const std::string NAME_VALUE;
    static const std::string NAME_EXPLICIT;
    
    ofxExpr_();
    ~ofxExpr_();
    ofxExpr_(const std::string &name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit = false);
    ofxExpr_(const std::string &name, const std::string &expression, const Type &value, bool isExplicit = false);
    ofxExpr_(const std::string &name, const std::string &expr);
    ofxExpr_(const std::string &name, const Type &value, bool isExplicit = true);
    ofxExpr_(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr_(const ofxExpr_& other);
    ofxExpr_& operator= (const ofxExpr_& other);
    
    Type get() const;
    const std::string & getExpression() const {
        return pExpr->get();
    }
    const Type & getValue() const {
        return pValue->get();
    }
    Type getMin() const {
        return pValue->getMin();
    }
    Type getMax() const {
        return pValue->getMax();
    }
    const bool isExplicit() const {
        return pExplicit->get();
    }
    const bool hasError() const {
        return !compiled;
    }
    
    ofxExpr_ & set(const std::string &expression);
    ofxExpr_ & set(const Type &value, bool isExplicit = true);
    ofxExpr_ & set(const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr_ & set(const std::string &name, const Type &value, bool isExplicit = true);
    ofxExpr_ & set(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit = true);
    ofxExpr_ & set(const std::string & name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit = false);
    ofxExpr_ & setExplicit(bool isExplicit);
    void setMin(const Type &min) {
        pValue->setMin(min);
        parser.setMin(min);
    }
    void setMax(const Type &max) {
        pValue->setMax(max);
        parser.setMax(max);
    }
    ofxExpr_ & setSliderMinMax(const Type &min, const Type &max) {
        pValue->setMin(min);
        pValue->setMax(max);
        return *this;
    }
    void setRandom() {
        set(ofRandom(getMin(), getMax()));
    }
    
    const Type getExprValue() const;
    bool hasVar(const std::string &name) const;
    bool addVar(const std::string &name, Type &value, bool recompile = true);
    bool addDummyVar(const std::string &name, bool recompile = true);
    bool hasConst(const std::string &name) const;
    bool addConst(const std::string &name, const Type &value, bool recompile = true);
    bool hasExprSymbol(const std::string &name) const;
    bool isTimeDependent() const;
    bool compile();
    
    const mu::Parser &getParser() const {
        return parser;
    }
    
    const std::shared_ptr<ofParameter<std::string>> & getExpressionParameter() const {
        return pExpr;
    }
    const std::shared_ptr<ofParameter<Type>> & getValueParameter() const {
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
    
    bool operator== (const ofxExpr_ &e2) const;
    bool operator!= (const ofxExpr_ &e2) const;
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxExpr_ & mom);
    
private:
    
    void setExprParameter(const std::shared_ptr<ofParameter<std::string>> & pExpr);
    void onChangeExpr(std::string &expr);
    void notCompiled(bool recompile);
    
    ofxExprParser parser;
    float dummyVal;
    bool compiled = false;
    
    std::shared_ptr<ofParameter<std::string>> pExpr;
    std::shared_ptr<ofParameter<Type>> pValue;
    std::shared_ptr<ofParameter<bool>> pExplicit;
};

typedef ofxExpr_<float> ofxFloatExpr;

template<class VecType>
class ofxExpr : public ofParameterGroup {
    
public:
    ofxExpr();
    ofxExpr(VecType value);
    ofxExpr(const ofxExpr<VecType> &other);
    ofxExpr<VecType>& operator= (const ofxExpr<VecType>& other);
    
    VecType get() const;
    VecType getExplicit() const;
    VecType getNonExplicit() const;
    VecType getMin() const;
    VecType getMax() const;

    ofxExpr<VecType> & set(const std::string &value);
    ofxExpr<VecType> & set(const VecType & v, bool isExplicit = true);
    ofxExpr<VecType> & set(const std::string& name, const VecType & v);
    ofxExpr<VecType> & set(const std::string& name, const VecType & v, const VecType & min, const VecType & max);
    void setMin(const VecType & min);
    void setMax(const VecType & max);
    ofxExpr<VecType> & setSliderMinMax(const VecType & min, const VecType & max);
    bool hasVar(const std::string &name) const;
    bool hasExprSymbol(const std::string &name) const;
    bool isTimeDependent() const;
    bool addVar(const std::string &name, float &value, bool recompile = true);
    bool addDummyVar(const std::string &name, bool recompile = false);
    bool hasConst(const std::string &name) const;
    bool addConst(const std::string &name, const float &value, bool recompile = true);
    bool compile();
    bool isExplicit() const;
    
    using ofParameterGroup::get;
    const std::shared_ptr<ofxFloatExpr> & operator [] (const int i) const {
        return expr[i];
    }
    
    friend bool operator== (const ofxExpr<VecType> &c1, const ofxExpr<VecType> &c2) {
        bool result = true;
        for (int i=0; i<ofxExpr<VecType>::dim(); i++) {
            result = result && (*c1[i] == *c2[i]);
        }
        return result;
    }
    friend bool operator!= (const ofxExpr<VecType> &c1, const ofxExpr<VecType> &c2) {
        return !(c1 == c2);
    }
    
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxExpr<VecType> & mom);
    size_t size() const {
        return expr.size();
    }
    static size_t dim();
    static float* value_ptr(VecType& v);
    static const float* value_ptr(const VecType& v);
    
private:
    std::vector<std::shared_ptr<ofxFloatExpr>> expr;
    
};
