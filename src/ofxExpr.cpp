#include "ofxExpr.hpp"

const std::string ofxExpr::NAME_EXPR = "expression";
const std::string ofxExpr::NAME_VALUE = "value";
const std::string ofxExpr::NAME_EXPLICIT = "explicit";

ofxExpr::ofxExpr() : ofParameterGroup() {
    pExpr = std::make_shared<ofParameter<std::string>>(NAME_EXPR, "");
    add(*pExpr);
    pValue = std::make_shared<ofParameter<float>>(NAME_VALUE, 0.f);
    add(*pValue);
    pExplicit = std::make_shared<ofParameter<bool>>(NAME_EXPLICIT, false);
    add(*pExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const std::string &expression, const float &value, bool isExplicit) : ofxExpr() {
    set(expression);
    set(name, value, isExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const std::string &expr) : ofxExpr() {
    setName(name);
    set(expr);
}

ofxExpr::ofxExpr(const std::string &name, const float &value, bool isExplicit) : ofxExpr() {
    set(value, isExplicit);
}

ofxExpr::ofxExpr(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit) : ofxExpr(name, "", value, min, max, isExplicit) {}

ofxExpr::ofxExpr(const ofxExpr& other) : ofParameterGroup() {
    setName(other.getName());
    pExpr = other.getExpressionParameter();
    pValue = other.getValueParameter();
    pExplicit = other.getExplicitParameter();
    parser = other.getParser();
}

ofxExpr& ofxExpr::operator= (const ofxExpr& other) {
    if (this != &other) {
        setName(other.getName());
        set(other.getExpression());
        set(other.getName(), other.getValue(), other.getMin(), other.getMax(), other.isExplicit());
    }
    return *this;
}

float ofxExpr::get() const  {
    if (isExplicit()) {
        return getValue();
    }
    return getExprValue();
}

ofxExpr & ofxExpr::set(const std::string &expression, bool recompile) {
    pExpr->set(expression);
    pExplicit->set(false);
    compiled = false;
    if (recompile) {
        compile();
    }
    return *this;
}

ofxExpr & ofxExpr::set(const float &value, bool isExplicit) {
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const float &value, const float &min, const float &max, bool isExplicit) {
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const float &value, bool isExplicit) {
    setName(name);
    pValue->set(value);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const float &value, const float &min, const float &max, bool isExplicit) {
    setName(name);
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::set(const std::string &name, const std::string &expression, const float &value, const float &min, const float &max, bool isExplicit) {
    setName(name);
    pExpr->set(expression);
    pValue->set(NAME_VALUE, value, min, max);
    parser.setMin(min);
    parser.setMax(max);
    pExplicit->set(isExplicit);
    return *this;
}

ofxExpr & ofxExpr::setExplicit(bool isExplicit) {
    pExplicit->set(isExplicit);
    return *this;
}

const float ofxExpr::getExprValue() const {
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

bool ofxExpr::hasVar(const std::string &name) const {
    try {
        const mu::varmap_type &variables = parser.GetVar();
        return variables.find(name) != variables.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

bool ofxExpr::addVar(const std::string &name, float &value, bool recompile) {
    parser.DefineVar(name, &value);
    compiled = false;
    if (recompile) {
        return compile();
    }
    return true;
}

bool ofxExpr::addDummyVar(const std::string &name, bool recompile) {
    parser.DefineVar(name, &dummyVal);
    compiled = false;
    if (recompile) {
        return compile();
    }
    return true;
}

bool ofxExpr::hasConst(const std::string &name) const {
    try {
        const mu::valmap_type &cmap = parser.GetConst();
        return cmap.find(name) != cmap.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

bool ofxExpr::addConst(const std::string &name, const float &value, bool recompile) {
    parser.DefineConst(name, value);
    compiled = false;
    if (recompile) {
        return compile();
    }
    return true;
}

bool ofxExpr::hasExprSymbol(const std::string &name) const {
    try {
        const mu::varmap_type &uv = parser.GetUsedVar();
        return uv.find(name) != uv.end();
    }
    catch (mu::Parser::exception_type &e) {
        return false;
    }
}

bool ofxExpr::compile() {
    if (!compiled) {
        try {
            parser.SetExpr(pExpr->get());
            compiled = true;
        }
        catch (mu::Parser::exception_type &e) {
            compiled = false;
            ofLog() << "ofxExpr compile error: " << e.GetMsg();
        }
    }
    return compiled;
}

bool ofxExpr::operator== (const ofxExpr &e2) const {
    std::string v1 = isExplicit() ? ofToString(getValue()) : pExpr->get();
    std::string v2 = e2.isExplicit() ? ofToString(e2.getValue()) : e2.getExpression();
    return v1 == v2;
}

bool ofxExpr::operator!= (const ofxExpr &e2) const {
    return !(*this == e2);
}

std::shared_ptr<ofAbstractParameter> ofxExpr::newReference() const{
    return std::make_shared<ofxExpr>(*this);
}

void ofxExpr::makeReferenceTo(ofxExpr & mom) {
    setName(mom.getName());
    pExpr = mom.getExpressionParameter();
    pValue = mom.getValueParameter();
    pExplicit = mom.getExplicitParameter();
    parser = mom.getParser();
}
