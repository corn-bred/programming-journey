# CornJam
A small game engine mostly made to make quick games, with the tradeoff being less control. 

## Supports:
- Textures
- Grid-based animation (I'll add .json support later)
- Compute shader-based particles! :\)
- `.wav` only Audio (I didn't add `dr_ogg` and `dr_flac` yet)
- Grid-based bitmap text rendering (I'll add freetype later)
- Custom game states
- Key input management
- AABB collision
- Virtual entity class (ugly) 

This was just made as a template for me to make a game in a game jam, hence the name CornJam.

## How To Build
CMake is required. Run these commands in the parent folder

### Dynamically-Linked Libraries

`cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++`
`cmake --build build`

### Statically-Linked Libraries

`cmake -S . -B build -G Ninja -DSTATIC_BUILD=ON -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++`
`cmake --build build`
(you still need to keep the `openal32.dll` file though)