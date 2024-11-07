# Constant Expressions
## Example:

```C++
struct S {
    int a: *new int{1};
};

enum E {
    V = *new int{1}
};
```
## Explanation

In this example we see an attempt to assign the bit field and the enumeration member from the result of a dynamic allocation.

First, we need to determine what type of expressions we can assign.

For bit-fields <strong>11.4.10</strong>:
```
identifieropt attribute-specifier-seqopt : 
    constant-expression brace-or-equal-initializeropt
```

For enumerations <strong>9.7.1</strong>:
```
enumerator-definition :
    enumerator
    enumerator = constant-expression
```

In general `new` can be an expression with fulfillment of some conditions. \
<strong>7.7.5.18</strong>:
>a new-expression (7.6.2.8), unless the selected allocation function is a replaceable global allocation
function (17.6.3.2, 17.6.3.3) and the allocated storage is <strong>deallocated </strong>within the evaluation of E;

But in our case there is no deallocation, which means that `new` cannot be considered a constant expression and accordingly assignment to the bit-fields and enumerators should not be compiled.


That's what gcc says:

>'*(operator new(4), ((true, (((*(int*)<anonymous>) = 1), (<anonymous> = false))), ((int*)<anonymous>)))' is not a constant expression because allocated storage has not been deallocated


## Conclusion
GCC is right, Clang is wrong.

