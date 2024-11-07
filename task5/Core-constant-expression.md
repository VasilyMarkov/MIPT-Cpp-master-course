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

## Conclusion


