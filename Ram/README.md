# String implementation
This is a [Ram project. The project represent a simple non context-free grammar.

## Dependencies and requirements
> Project requires at least C++20. \
> Libraries: googletests.
## Installation and building
### Install
```bash
git clone https://github.com/VasilyMarkov/my_impl_cpp.git
cd my_impl_cpp
```
```bash
cd Ram
```
### Build
#### Release
```bash
cmake --preset release
cmake --build --preset release
```
#### Debug
```bash
cmake --preset debug
cmake --build --preset debug
```
#### Test
```bash
cmake --preset test
cmake --build --preset test
```
#### Sanitize test
```bash
cmake --preset sanitize_test
cmake --build --preset sanitize_test
```
## Run
For run [Ram parser you need to write language constructs to a file and pass the file to [Ram as an argument
```bash
./Ram {file_path}
```