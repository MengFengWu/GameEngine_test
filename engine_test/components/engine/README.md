## Simple Game Engine

### Description

This is a game engine designed for NTUEE game console.

### Architecture

```
└──engine/
   ├──include/
   │  ├──Engine.h
   │  ├──ResourceManager.h
   │  └──RenderManager.h
   ├──src/
   │  ├──ResourceManager.c
   │  └──RenderManager.c
   ├──CMakeLists.txt
   └──README.md
```

### How to use?

Include following file in `main.c`
```C
#include "Engine.h"
```
For more usage of the engine, you can visit the [tutorial](https://hackmd.io/@uzF57KwOT5SnkVGD3Ppheg/Bkq8tLnLC) here.
