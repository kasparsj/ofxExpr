# ofxExpr openFrameworks addon

mathematical expression parser for strings and ofxGui, based on muParser

currently OS X only (Intel and Apple Silicon)

tested with of_v0.11.1

Supported return value types:

- float `ofxFloatExpr`
- glm::vec2 `ofxExpr<glm::vec2>`
- glm::vec3 `ofxExpr<glm::vec3>`
- glm::vec4 `ofxExpr<glm::vec4>`
- glm::mat2 `ofxExpr<glm::mat2>`
- glm::mat3 `ofxExpr<glm::mat3>`
- glm::mat4 `ofxExpr<glm::mat4>`

## examples

1. arithmetic

```cpp
float x = 123.0;
float y = 678.0;
float z = 57.0;

ofxFloatExpr expr1;
expr1.set("x * y + 3");
expr1.addVar("x", x, false);
expr1.addVar("y", y);
expr1.addVar("z", z);

cout << "x = " << x << endl; // x = 123
cout << "y = " << y << endl; // y = 678
cout << "z = " << z << endl; // z = 57
cout << expr1.getExpression() << " = " << expr1.get() << endl; // x * y + 3 = 83397
```

2. trigonometry

```cpp
float x = 2;
ofxFloatExpr expr2;
expr2.set("sin(x)");
expr2.addVar("x", x);
cout << expr2.getExpression() << " = " << expr2.get() << endl; // sin(x) = 0.909297
```

3. built-in variables

`t = ofGetElapsedTimef();`

```cpp
ofxFloatExpr expr3;
expr3.set("t");
cout << expr3.getExpression() << " = " << expr3.get() << endl; // t = 1.2177
```

4. built-in functions

```cpp
float x = 2;
ofxFloatExpr expr4;
expr4.set("rand(x)");
expr4.addVar("x", x);
cout << expr4.getExpression() << " = " << expr4.get() << endl; // rand(x) = 0.37822
cout << expr4.getExpression() << " = " << expr4.get() << endl; // rand(x) = 0.736426

expr4.set("noise(x)");
expr4.addVar("x", x);
cout << expr4.getExpression() << " = " << expr4.get() << endl; // noise(x) = 0.5
```
