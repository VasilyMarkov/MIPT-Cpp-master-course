# Perfect Forward
### Example:

```C++
int g(int &&t) { return 1; }
int g(int &t) { return 2; }

template <typename T>
void/*int?*/ h(T &&t) { g(std::forward<T> (t)); }

const int x = 1; int z = h(x); // ???
```
### Explanation
```C++
template <typename T>
void h(T&& t) {
    //t -> const T&
    //T -> const&
}
```
In this case, `T` is a universal reference and the correct convolution 
will be applied to the type inference.

When passing a non-reference type, an lvalue reference will be appended to it 
and then by the convolution rule & + && = &. Thus type "t" will be `const int&`.
`T` will be `const int&` also.

`std::forward` provides a perfect forward so that type "t" is thrown unchanged inside, so: 
```C++
 g(std::forward<T>(t)) -> g(const int&)
```
Since there is no such overloading, and in `int&` and `int&&` 
it is forbidden to pass const int&, there will be a compilation error.


`std::forward`:
```C++
template <class T>
T&& forward(typename std::remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}
```
Transformation chain:

`std::remove_reference<const int>::type& -> const int& -> static_cast<&&>(const int&) -> const int& -> (const int&)&& -> const int&`