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
Clang compiles this one. 

But if replaced `constexpr auto get() {return Type();}` to \
`consteval auto get() {return Type();}`, clang will generate also a compilation error:
```
error: call to consteval function 'get' is not a constant expression
   11 | constexpr Type t2 = get();
```

Looks like clang executes `constexpr get()` in runtime. That's why there are no problems, unlike gcc. 

It remains to understand whether this expression is a type of constant expression to make sure that compilers generate the error correctly.

`const int& b` in the `Type` struct is being initialized with a temporary object, which is not allowed in a constant expression context.  
<strong>7.7.12</strong>:

>A constant expression is either a glvalue core constant expression that refers to an entity that is a permitted result of a constant expression (as defined below), or a prvalue core constant expression whose value satisfies the following constraints: ...


The dangling reference doesn't satisfies these requirements.
## Conclusion

Different compiler behavior is observed because clang decided to execute the function in run time and gcc in compile time. If you force both compilers to execute the function in compile time, they will both generate an error that the reference to the temporary object is not a constant expression.
