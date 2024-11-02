# Name Lookup
### Example:

```C++
struct S; 

template <typename T> struct Wrapper { T val; };

void foo(const Wrapper<S>&) {}

Wrapper<S>& get();

int main() {
    (foo)(get());
    // foo(get()); 
}
```
### Explanation

Pursuant to paragraph <strong>6.5.4</strong>. Parentheses prevent argument-dependent lookup.
So, `(foo)` is `( expression )`, not unqualified-id, therefore ADL doesn't apply. A parenthesized unqualified-id is no longer an unqualified-id. 

Arthur O’Dwyer gives a similar example in his article [What is ADL?](https://quuxplusone.github.io/blog/2019/04/26/what-is-adl/):

```C++
namespace A {
    struct A { operator int(); };
    void f(A);
}
namespace B {
    void f(int);
    void f(double);
    void test() {
        A::A a;
        void (*fp)(int) = f;  // OK, no ADL
        void (*gp)(A::A) = f; // ERROR, no ADL, fails to find A::f
        f(a);     // ADL, calls A::f(A)
        (&f)(a);  // no ADL, calls B::f(int)
        (f)(a);   // no ADL, calls B::f(int)
    }
}
```
He sais: 
"ADL is defined in terms of the unqualified-id grammar production, which means that ADL does not apply to a redundantly parenthesized call such as (f)(a), because (f) is a primary-expression, not an unqualified-id."
