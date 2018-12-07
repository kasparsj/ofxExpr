#pragma once

#include "ofxExpr.hpp"

template<class VecType>
class ofxVecExpr : public ofParameterGroup {
    
public:
    ofxVecExpr();
    ofxVecExpr(float value);
    ofxVecExpr(VecType value);
    ofxVecExpr(const ofxVecExpr<VecType> &other);
    ofxVecExpr<VecType>& operator= (const ofxVecExpr<VecType>& other);
    
    VecType get() const;
    VecType getExplicit() const;
    VecType getNonExplicit() const;
    VecType getMin() const;
    VecType getMax() const;

    ofxVecExpr<VecType> & set(const std::string &value);
    ofxVecExpr<VecType> & set(const VecType & v);
    ofxVecExpr<VecType> & set(const std::string& name, const VecType & v);
    ofxVecExpr<VecType> & set(const std::string& name, const VecType & v, const VecType & min, const VecType & max);
    void setMin(const VecType & min);
    void setMax(const VecType & max);
    ofxVecExpr<VecType> & setSliderMinMax(const VecType & min, const VecType & max);
    void setRandom();
    bool hasVar(const std::string &name) const;
    bool hasExprSymbol(const std::string &name) const;
    bool addVar(const std::string &name, float &value, bool recompile = true);
    bool addDummyVar(const std::string &name, bool recompile = false);
    bool compile();
    bool isExplicit() const;
    
#ifdef ofxexpr_use_exprtk
    
    bool hasConst(const std::string &name) const {
        for (int i=0; i<size(); i++) {
            if (expr[i]->hasConst(name)) {
                return true;
            }
        }
        return false;
    }
    bool hasStringvar(const std::string &name) const {
        for (int i=0; i<size(); i++) {
            if (expr[i]->hasStringvar(name)) {
                return true;
            }
        }
        return false;
    }
    bool hasVector(const std::string &name) const {
        for (int i=0; i<size(); i++) {
            if (expr[i]->hasVector(name)) {
                return true;
            }
        }
        return false;
    }
    bool addConst(const std::string &name, const float &value, bool recompile = true) {
        for (int i=0; i<size(); i++) {
            expr[i]->addConst(name, value, recompile);
        }
    }
    bool addStringvar(const std::string &name, std::string &value, bool recompile = true) {
        for (int i=0; i<size(); i++) {
            expr[i]->addStringvar(name, value, recompile);
        }
    }
    template<typename VecType1>
    bool addVector(const std::string &name, std::vector<VecType1> &value, bool recompile = true) {
        for (int i=0; i<size(); i++) {
            expr[i]->addVector(name, value, recompile);
        }
    }
    
#endif
    
    using ofParameterGroup::get;
    const std::shared_ptr<ofxExpr> & operator [] (const int i) const {
        return expr[i];
    }
    
    friend bool operator== (const ofxVecExpr<VecType> &c1, const ofxVecExpr<VecType> &c2) {
        bool result = true;
        for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
            result = result && (*c1[i] == *c2[i]);
        }
        return result;
    }
    friend bool operator!= (const ofxVecExpr<VecType> &c1, const ofxVecExpr<VecType> &c2) {
        return !(c1 == c2);
    }
    
    std::shared_ptr<ofAbstractParameter> newReference() const;
    void makeReferenceTo(ofxVecExpr<VecType> & mom);
    size_t size() const {
        return expr.size();
    }
    static size_t dim();
    
private:
    std::vector<std::shared_ptr<ofxExpr>> expr;
    
};
