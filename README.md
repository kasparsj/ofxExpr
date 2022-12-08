# ofxExpr

mathematical expression parser for strings and ofxGui, based on muParser

currently OS X only

## examples

1. arithmetic

```cpp
float x = 123.0;
float y = 678.0;
float z = 57.0;

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
expr2.set("sin(x)");
expr2.addVar("x", x);
cout << expr2.getExpression() << " = " << expr2.get() << endl; // sin(x) = 0.909297
```

3. built-in variables

`t = ofGetElapsedTimef();`

```cpp
expr3.set("t");
cout << expr3.getExpression() << " = " << expr3.get() << endl; // t = 1.2177
```

4. built-in functions

```cpp
expr4.set("rand(x)");
expr4.addVar("x", x);
cout << expr4.getExpression() << " = " << expr4.get() << endl; // rand(x) = 0.37822
cout << expr4.getExpression() << " = " << expr4.get() << endl; // rand(x) = 0.736426

expr4.set("noise(x)");
expr4.addVar("x", x);
cout << expr4.getExpression() << " = " << expr4.get() << endl; // noise(x) = 0.5
```
