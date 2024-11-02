# Persistent Binary search tree
This project contains a Persistent Binary search tree implementation that supports one-time operations undo and redo.
Also for the int type an optimized version flat tree.  

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
cd PersistentBST
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