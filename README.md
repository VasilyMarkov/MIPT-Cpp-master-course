# CoW String
This project is my implementation of `Copy-on-Write String`.

## Features
Project contains big-5. Also substr and tokenizing support.

## Dependencies and requirements
> 'cowString' requires at least C++20. \
> Also 'cowString' requires boost-tokenizer library.
>
## Installation and building
### Install
```bash
git clone https://github.com/VasilyMarkov/my_impl_cpp.git
cd my_impl_cpp
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