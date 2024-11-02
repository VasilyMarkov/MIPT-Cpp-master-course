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

Pursuant to paragraph <strong>6.5.4</strong>. Parentheses prevent argument-dependent lookup