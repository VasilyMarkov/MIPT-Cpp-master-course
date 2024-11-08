# Core Constant Expressions
## Example

```C++
struct Type {
    int a;
    const int& b;
    constexpr Type(): a(1), b(a) {}
};

constexpr auto get() {return Type();}

constexpr Type t2 = get();

constexpr int c2 = t2.a;
```
## Explanation

In this example gcc says:
```
<source>:11:25: error: 'Type{1, ((const int&)(&<anonymous>.Type::a))}' is not a constant expression
```
but clang compiles this one. 

But if replaced `constexpr auto get() {return Type();}` to \
`consteval auto get() {return Type();}`, clang will generate also a compilation error:
```
error: call to consteval function 'get' is not a constant expression
   11 | constexpr Type t2 = get();
```

Looks like clang executes `constexpr get` in runtime. That's why there are no problems, unlike gcc. \

It remains to understand whether this expression is a type of constant expression to make sure that compilers generate the error correctly.
## Conclusion


