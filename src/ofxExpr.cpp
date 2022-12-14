#include "ofxExpr.hpp"

template<typename Type>
const std::string ofxExpr_<Type>::NAME_EXPR = "expression";

template<typename Type>
const std::string ofxExpr_<Type>::NAME_VALUE = "value";

template<typename Type>
const std::string ofxExpr_<Type>::NAME_EXPLICIT = "explicit";

template<typename Type>
ofxExpr_<Type>::ofxExpr_() : ofParameterGroup() {
    setExprParameter(std::make_shared<ofParameter<std::string>>(NAME_EXPR, ""));
    add(*pExpr);
    pValue = std::make_shared<ofParameter<float>>(NAME_VALUE, 0.f);
    add(*pValue);
    pExplicit = std::make_shared<ofParameter<bool>>(NAME_EXPLICIT, false);
    add(*pExplicit);
}

template<typename Type>
ofxExpr_<Type>::ofxExpr_(const std::string &name, const std::string &expression, const Type &value, bool isExplicit) : ofxExpr_() {
    set(expression);
    set(name, value, isExplicit);
}

template<typename Type>
ofxExpr_<Type>::ofxExpr_(const std::string &name, const std::string &expr) : ofxExpr_() {
    setName(name);
    set(expr);
}

template<typename Type>
ofxExpr_<Type>::ofxExpr_(const std::string &name, const Type &value, bool isExplicit) : ofxExpr_() {
    set(value, isExplicit);
}

template<typename Type>
ofxExpr_<Type>::ofxExpr_(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit) : ofxExpr_(name, "", value, min, max, isExplicit) {}

template<typename Type>
ofxExpr_<Type>::ofxExpr_(const ofxExpr_& other) : ofParameterGroup() {
    setName(other.getName());
    setExprParameter(other.getExpressionParameter());
    pValue = other.getValueParameter();
    pExplicit = other.getExplicitParameter();
    parser = other.getParser();
}

template<typename Type>
ofxExpr_<Type>::~ofxExpr_() {
    if (pExpr != NULL) {
        pExpr->removeListener(this, &ofxExpr_::onChangeExpr);
    }
}

template<typename Type>
ofxExpr_<Type>& ofxExpr_<Type>::operator= (const ofxExpr_& other) {
    if (this != &other) {
        setName(other.getName());
        set(other.getExpression());
        set(other.getName(), other.getValue(), other.getMin(), other.getMax(), other.isExplicit());
    }
    return *this;
}

template<typename Type>
Type ofxExpr_<Type>::get() const  {
    if (isExplicit()) {
        return getValue();
    }
    return getExprValue();
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::set(const std::string &expression) {
    pExpr->set(expression);
    pExplicit->set(false);
    return *this;
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::set(const Type &value, bool isExplicit) {
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::set(const Type &value, const Type &min, const Type &max, bool isExplicit) {
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::set(const std::string &name, const Type &value, bool isExplicit) {
    setName(name);
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr_<Type>& ofxExpr_<Type>::set(const std::string &name, const Type &value, const Type &min, const Type &max, bool isExplicit) {
    setName(name);
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::set(const std::string &name, const std::string &expression, const Type &value, const Type &min, const Type &max, bool isExplicit) {
    setName(name);
    pExpr->set(expression);
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
ofxExpr_<Type> & ofxExpr_<Type>::setExplicit(bool isExplicit) {
    pExplicit->set(isExplicit);
    return *this;
}

template<typename Type>
const Type ofxExpr_<Type>::getExprValue() const {
    if (compiled) {
        try {
            return parser.Eval();
        }
        catch (mu::Parser::exception_type &e) {
            return getValue();
        }
    }
    return getValue();
}

template<typename Type>
bool ofxExpr_<Type>::hasVar(const std::string &name) const {
    try {
        const mu::varmap_type &variables = parser.GetVar();
        return variables.find(name) != variables.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

template<typename Type>
bool ofxExpr_<Type>::addVar(const std::string &name, Type &value, bool recompile) {
    parser.DefineVar(name, &value);
    notCompiled(recompile);
    return true;
}

template<typename Type>
bool ofxExpr_<Type>::addDummyVar(const std::string &name, bool recompile) {
    parser.DefineVar(name, &dummyVal);
    notCompiled(recompile);
    return true;
}

template<typename Type>
bool ofxExpr_<Type>::hasConst(const std::string &name) const {
    try {
        const mu::valmap_type &cmap = parser.GetConst();
        return cmap.find(name) != cmap.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

template<typename Type>
bool ofxExpr_<Type>::addConst(const std::string &name, const Type &value, bool recompile) {
    parser.DefineConst(name, value);
    notCompiled(recompile);
    return true;
}

template<typename Type>
bool ofxExpr_<Type>::hasExprSymbol(const std::string &name) const {
    try {
        const mu::varmap_type &uv = parser.GetUsedVar();
        return uv.find(name) != uv.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

template<typename Type>
bool ofxExpr_<Type>::isTimeDependent() const {
    return hasExprSymbol("t") || hasExprSymbol("f");
}

template<typename Type>
bool ofxExpr_<Type>::compile() {
    try {
        parser.set(pExpr->get());
        compiled = true;
    }
    catch (mu::Parser::exception_type &e) {
        compiled = false;
        ofLog() << "ofxExpr compile error: " << e.GetMsg();
    }
    return compiled;
}

template<typename Type>
bool ofxExpr_<Type>::operator== (const ofxExpr_ &e2) const {
    std::string v1 = isExplicit() ? ofToString(getValue()) : pExpr->get();
    std::string v2 = e2.isExplicit() ? ofToString(e2.getValue()) : e2.getExpression();
    return v1 == v2;
}

template<typename Type>
bool ofxExpr_<Type>::operator!= (const ofxExpr_ &e2) const {
    return !(*this == e2);
}

template<typename Type>
std::shared_ptr<ofAbstractParameter> ofxExpr_<Type>::newReference() const{
    return std::make_shared<ofxExpr_>(*this);
}

template<typename Type>
void ofxExpr_<Type>::makeReferenceTo(ofxExpr_ & mom) {
    setName(mom.getName());
    setExprParameter(mom.getExpressionParameter());
    pValue = mom.getValueParameter();
    pExplicit = mom.getExplicitParameter();
    parser = mom.getParser();
}

template<typename Type>
void ofxExpr_<Type>::setExprParameter(const std::shared_ptr<ofParameter<std::string>> & _pExpr)  {
    if (pExpr != NULL) {
        pExpr->removeListener(this, &ofxExpr_::onChangeExpr);
    }
    pExpr = _pExpr;
    if (pExpr != NULL) {
        pExpr->addListener(this, &ofxExpr_::onChangeExpr);
    }
}

template<typename Type>
void ofxExpr_<Type>::onChangeExpr(std::string &expr) {
    notCompiled(true);
}

template<typename Type>
void ofxExpr_<Type>::notCompiled(bool recompile) {
    compiled = false;
    if (recompile) {
        compile();
    }
}

template<typename VecType>
ofxExpr<VecType>::ofxExpr() : ofParameterGroup() {
    const std::string names[16] = {"x", "y", "z", "w", "x2", "y2", "z2", "w2", "x3", "y3", "z3", "w3", "x4", "y4", "z4", "w4"};
    for (int i=0; i<ofxExpr<VecType>::dim(); i++) {
        std::shared_ptr<ofxFloatExpr> e = std::make_shared<ofxFloatExpr>();
        e->setName(names[i]);
        add(*e);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxExpr<VecType>::ofxExpr(VecType value) : ofxExpr<VecType>() {
    const float* pSource = (const float*) value_ptr(value);
    for (int i=0; i<expr.size(); i++) {
        expr[i]->set(pSource[i]);
    }
}

template<typename VecType>
ofxExpr<VecType>::ofxExpr(const ofxExpr<VecType>& other) : ofParameterGroup() {
    setName(other.getName());
    for (int i=0; i<other.size(); i++) {
        std::shared_ptr<ofxFloatExpr> e = other[i];
        add(*e);
        expr.push_back(e);
    }
}

template<typename VecType>
ofxExpr<VecType>& ofxExpr<VecType>::operator= (const ofxExpr<VecType>& other) {
    if (this != &other) {
        setName(other.getName());
        for (int i=0; i<other.size(); i++) {
            *expr[i] = *other[i];
        }
    }
    return *this;
}

template<typename VecType>
VecType ofxExpr<VecType>::get() const {
    VecType val;
    float *pVal = value_ptr(val);
    for (int i=0; i<expr.size(); i++) {
        pVal[i] = expr[i]->get();
    }
    return val;
}

template<typename VecType>
VecType ofxExpr<VecType>::getExplicit() const {
    VecType val;
    float *pVal = (float*) value_ptr(val);
    for (int i=0; i<expr.size(); i++) {
        if (expr[i]->isExplicit()) {
            pVal[i] = expr[i]->getValue();
        }
    }
    return val;
}

template<typename VecType>
VecType ofxExpr<VecType>::getNonExplicit() const {
    VecType val;
    float *pVal = (float*) value_ptr(val);
    for (int i=0; i<expr.size(); i++) {
        if (expr[i]->isExplicit()) {
            continue;
        }
        pVal[i] = expr[i]->getExprValue();
    }
    return val;
}

template<typename VecType>
VecType ofxExpr<VecType>::getMin() const {
    VecType min;
    float *pMin = (float*) value_ptr(min);
    for (int i=0; i<size(); i++) {
        pMin[i] = expr[i]->getMin();
    }
    return min;
}

template<typename VecType>
VecType ofxExpr<VecType>::getMax() const {
    VecType max;
    float *pMax = (float*) value_ptr(max);
    for (int i=0; i<size(); i++) {
        pMax[i] = expr[i]->getMax();
    }
    return max;
}

template<typename VecType>
ofxExpr<VecType>& ofxExpr<VecType>::set(const std::string& value) {
    for (int i=0; i<size(); i++) {
        expr[i]->set(value);
    }
    return *this;
}

template<typename VecType>
ofxExpr<VecType>& ofxExpr<VecType>::set(const VecType& v, bool isExplicit) {
    const float *pV = value_ptr(v);
    for (int i=0; i<size(); i++) {
        expr[i]->set(pV[i], isExplicit);
    }
    return *this;
}

template<typename VecType>
ofxExpr<VecType> & ofxExpr<VecType>::set(const std::string& name, const VecType& v) {
    setName(name);
    const float *pV = value_ptr(v);
    for (int i=0; i<size(); i++) {
        expr[i]->set(pV[i]);
    }
    return *this;
}

template<typename VecType>
ofxExpr<VecType> & ofxExpr<VecType>::set(const std::string& name, const VecType & v, const VecType & min, const VecType & max) {
    setName(name);
    const float *pV = value_ptr(v);
    const float *pMin = value_ptr(min);
    const float *pMax = value_ptr(max);
    for (int i=0; i<size(); i++) {
        expr[i]->set(pV[i], pMin[i], pMax[i]);
    }
    return *this;
}

template<typename VecType>
void ofxExpr<VecType>::setMin(const VecType & min) {
    const float *pMin = value_ptr(min);
    for (int i=0; i<size(); i++) {
        expr[i]->setMin(pMin[i]);
    }
}

template<typename VecType>
void ofxExpr<VecType>::setMax(const VecType & max) {
    const float *pMax = value_ptr(max);
    for (int i=0; i<size(); i++) {
        expr[i]->setMax(pMax[i]);
    }
}

template<typename VecType>
ofxExpr<VecType> & ofxExpr<VecType>::setSliderMinMax(const VecType& min, const VecType& max) {
    const float *pMin = value_ptr(min);
    const float *pMax = value_ptr(max);
    for (int i=0; i<size(); i++) {
        expr[i]->setSliderMinMax(pMin[i], pMax[i]);
    }
    return *this;
}

template<typename VecType>
bool ofxExpr<VecType>::hasVar(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasVar(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxExpr<VecType>::hasExprSymbol(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasExprSymbol(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxExpr<VecType>::isTimeDependent() const {
    return hasExprSymbol("t") || hasExprSymbol("f");
}

template<typename VecType>
bool ofxExpr<VecType>::addVar(const std::string &name, float &value, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addVar(name, value, recompile);
    }
}

template<typename VecType>
bool ofxExpr<VecType>::addDummyVar(const std::string &name, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addDummyVar(name, recompile);
    }
}

template<typename VecType>
bool ofxExpr<VecType>::hasConst(const std::string &name) const {
    for (int i=0; i<size(); i++) {
        if (expr[i]->hasConst(name)) {
            return true;
        }
    }
    return false;
}

template<typename VecType>
bool ofxExpr<VecType>::addConst(const std::string &name, const float &value, bool recompile) {
    for (int i=0; i<size(); i++) {
        expr[i]->addConst(name, value, recompile);
    }
}

template<typename VecType>
bool ofxExpr<VecType>::compile() {
    for (int i=0; i<size(); i++) {
        expr[i]->compile();
    }
}

template<typename VecType>
bool ofxExpr<VecType>::isExplicit() const {
    bool result = false;
    for (int i=0; i<size(); i++) {
        result = result || expr[i]->isExplicit();
    }
    return result;
}

template<typename VecType>
std::shared_ptr<ofAbstractParameter> ofxExpr<VecType>::newReference() const{
    return std::make_shared<ofxExpr<VecType>>(*this);
}

template<typename VecType>
void ofxExpr<VecType>::makeReferenceTo(ofxExpr<VecType> & mom) {
    setName(mom.getName());
    for (int i=0; i<size(); i++) {
        expr[i] = mom[i];
    }
}

template<>
size_t ofxExpr<float>::dim(){
    return 1;
}

template<>
size_t ofxExpr<glm::vec2>::dim(){
    return 2;
}

template<>
size_t ofxExpr<glm::vec3>::dim(){
    return 3;
}

template<>
size_t ofxExpr<glm::vec4>::dim(){
    return 4;
}

template<>
size_t ofxExpr<glm::mat2>::dim(){
    return 4;
}

template<>
size_t ofxExpr<glm::mat3>::dim(){
    return 9;
}

template<>
size_t ofxExpr<glm::mat4>::dim(){
    return 16;
}

template<>
size_t ofxExpr<ofFloatColor>::dim(){
    return 4;
}

template<>
float* ofxExpr<float>::value_ptr(float& v) {
    return &v;
}

template<>
float* ofxExpr<glm::vec2>::value_ptr(glm::vec2& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<glm::vec3>::value_ptr(glm::vec3& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<glm::vec4>::value_ptr(glm::vec4& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<glm::mat2>::value_ptr(glm::mat2& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<glm::mat3>::value_ptr(glm::mat3& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<glm::mat4>::value_ptr(glm::mat4& v) {
    return glm::value_ptr(v);
}

template<>
float* ofxExpr<ofFloatColor>::value_ptr(ofFloatColor& v) {
    return &v[0];
}

template class ofxExpr<float>; // allowed for compatability but not recommended - use ofxFloatExpr
template class ofxExpr<glm::vec2>;
template class ofxExpr<glm::vec3>;
template class ofxExpr<glm::vec4>;
template class ofxExpr<glm::mat2>;
template class ofxExpr<glm::mat3>;
template class ofxExpr<glm::mat4>;
template class ofxExpr<ofFloatColor>;
