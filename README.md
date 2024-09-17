# String implementation
This project consists CoW string implementation and a string_twine class that concatenate at O(logN). 

## Features
Project contains big-5. Also substr and tokenizing support.

## Dependencies and requirements
> Project requires at least C++20. \
> Libraries: boost-tokenizer, googletests.
## Installation and building
### Install
```bash
git clone https://github.com/VasilyMarkov/my_impl_cpp.git
cd my_impl_cpp
```
```bash
cd cow_string
```
or
```bash
cd string_twine
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
```bash
./test_run
```