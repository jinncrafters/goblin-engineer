# goblin-engineer

[![Build Status](https://travis-ci.org/jinncrafters/goblin-engineer.svg?branch=master)](https://travis-ci.org/jinncrafters/goblin-engineer)
# How To Use

## For Users

Add the corresponding remote to your conan:

```bash
conan remote add cyberduckninja https://api.bintray.com/conan/cyberduckninja/conan
```

### Basic setup
```bash
conan remote add bincrafters  https://api.bintray.com/conan/bincrafters/public-conan
conan install goblin-engineer/1.0.0a3@cyberduckninja/stable
```
### Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*

    [requires]
    goblin-engineer/1.0.0a3@cyberduckninja/stable

    [generators]
    cmake

# Getting started
The library has a "service" abstraction which allows you to bind handlers which would call asynchronously on completing HTTP request
