## Simple Game Engine

### Description

This is a game engine design for NTUEE game console.

### Architecture

```
└──engine/
   ├──include/
   │  ├──Engine.h
   │  └──ResourceManager.h
   ├──src/
   │  └──ResourceManager.c
   ├──CMakeLists.txt
   └──README.md
```

### How to use?

(Running on ESP32 has not been tested yet)

### Develop

If you perfer developing without using ESP32, you can use following Structure

```
├──components/engine/
│  ├──include/
│  │  ├──Engine.h
│  │  └──ResourceManager.h
│  ├──src/
│  │  └──ResourceManager.c
│  ├──CMakeLists.txt
│  └──README.md
└──main/
   └──main.c
```
include this header file in `main.c`
```C
#include "../components/engine/include/Engine.h"
```
when compiling, run following command
```
gcc -Wall -Wextra -g3 [file_location]/main/main.c [file_location]/components/engine/src/ResourceManager.c [file_location]/components/engine/src/RenderManager.c  -I[file_location]/components/engine/include -o [file_location]/main/output/main
```
then run
```
./main
```
