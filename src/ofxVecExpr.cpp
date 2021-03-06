#include "ofxVecExpr.hpp"

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr() : ofParameterGroup() {
    const std::string names[4] = {"x", "y", "z", "w"};
    for (int i=0; i<ofxVecExpr<VecType>::dim(); i++) {
        std::shared_ptr<ofxExpr> e = std::make_shared<ofxExpr>();
        e->setName(names[i]);
        add(*e);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(float value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(value);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(VecType value) : ofxVecExpr() {
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(value[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType>::ofxVecExpr(const ofxVecExpr<VecType>& other) : ofParameterGroup() {
    setName(other.getName());
    for (int i=0; i<other.size(); i++) {
        std::shared_ptr<ofxExpr> e = other[i];
        add(*e);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxVecExpr<VecType>& ofxVecExpr<VecType>::operator= (const ofxVecExpr<VecType>& other) {
    if (this != &other) {
        setName(other.getName());
        for (int i=0; i<other.size(); i++) {
            *expr[i] = *other[i];
        }
    }
    return *this;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::get() const {
    VecType val;
    for (int i=0; i<expr.size(); i++) {
        val[i] = expr[i]->get();
    }
    return val;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getExplicit() const {
    VecType val;
    for (int i=0; i<expr.size(); i++) {
        if (expr[i]->isExplicit()) {
            val[i] = expr[i]->getValue();
        }
    }
    return val;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getNonExplicit() const {
    VecType val;
    for (int i=0; i<expr.size(); i++) {
        if (expr[i]->isExplicit()) {
            continue;
        }
        val[i] = expr[i]->getExprValue();
    }
    return val;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getMin() const {
    VecType min;
    for (int i=0; i<size(); i++) {
        min[i] = expr[i]->getMin();
    }
    return min;
}

template<typename VecType>
VecType ofxVecExpr<VecType>::getMax() const {
    VecType max;
    for (int i=0; i<size(); i++) {
        max[i] = expr[i]->getMax();
    }
    return max;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string &value) {
    for (int i=0; i<size(); i++) {
        expr[i]->set(value);
    }
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const VecType & v, bool isExplicit) {
    for (int i=0; i<size(); i++) {
        expr[i]->set(v[i], isExplicit);
    }
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string& name, const VecType & v) {
    setName(name);
    for (int i=0; i<size(); i++) {
        expr[i]->set(v[i]);
    }
    return *this;
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::set(const std::string& name, const VecType & v, const VecType & min, const VecType & max) {
    setName(name);
    for (int i=0; i<size(); i++) {
        expr[i]->set(v[i], min[i], max[i]);
    }
    return *this;
}

template<typename VecType>
void ofxVecExpr<VecType>::setMin(const VecType & min) {
    for (int i=0; i<size(); i++) {
        expr[i]->setMin(min[i]);
    }
}

template<typename VecType>
void ofxVecExpr<VecType>::setMax(const VecType & max) {
    for (int i=0; i<size(); i++) {
        expr[i]->setMax(max[i]);
    }
}

template<typename VecType>
ofxVecExpr<VecType> & ofxVecExpr<VecType>::setSliderMinMax(const VecType &min, const VecType &max) {
    for (int i=0; i<size(); i++) {
        expr[i]->setSliderMinMax(min[i], max[i]);
    }
    return *this;
}

template<typename VecType>
void ofxVecExpr<VecType>::setRandom() {
    set(ofRandom(getMin(), getMax()));
}

template<typename VecType>
bool ofxVecExpr<VecType>::hasVar(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasVar(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxVecExpr<VecType>::hasExprSymbol(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasExprSymbol(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxVecExpr<VecType>::isTimeDependent() const {
    return hasExprSymbol("t") || hasExprSymbol("f");
}

template<typename VecType>
bool ofxVecExpr<VecType>::addVar(const std::string &name, float &value, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addVar(name, value, recompile);
    }
}

template<typename VecType>
bool ofxVecExpr<VecType>::addDummyVar(const std::string &name, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addDummyVar(name, recompile);
    }
}

template<typename VecType>
bool ofxVecExpr<VecType>::hasConst(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasConst(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxVecExpr<VecType>::addConst(const std::string &name, const float &value, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addConst(name, value, recompile);
    }
}

template<typename VecType>
bool ofxVecExpr<VecType>::compile() {
    for (int i=0; i<size(); i++) {
        expr[i]->compile();
    }
}

template<typename VecType>
bool ofxVecExpr<VecType>::isExplicit() const {
    bool result = false;
    for (int i=0; i<size(); i++) {
        result = result || expr[i]->isExplicit();
    }
    return result;
}

template<typename VecType>
std::shared_ptr<ofAbstractParameter> ofxVecExpr<VecType>::newReference() const{
    return std::make_shared<ofxVecExpr<VecType>>(*this);
}

template<typename VecType>
void ofxVecExpr<VecType>::makeReferenceTo(ofxVecExpr<VecType> & mom) {
    setName(mom.getName());
    for (int i=0; i<size(); i++) {
        expr[i] = mom[i];
    }
}

template<>
size_t ofxVecExpr<glm::vec2>::dim(){
    return 2;
}

template<>
size_t ofxVecExpr<glm::vec3>::dim(){
    return 3;
}

template<>
size_t ofxVecExpr<glm::vec4>::dim(){
    return 4;
}

template class ofxVecExpr<glm::vec2>;
template class ofxVecExpr<glm::vec3>;
template class ofxVecExpr<glm::vec4>;
