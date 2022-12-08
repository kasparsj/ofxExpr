# ofxExpr

mathematical expression parser for strings and ofxGui, based on muParser

currently OS X only

## examples
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
