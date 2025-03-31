# ByteWave UI

This repo serves as the testing ground for development of the ByteWave UI before it is
ported into the main project, this is mainly for testing out UI layout, optimization, etc

# Compiling

## Dependencies:

### Windows:

#### OpenGL

Included with Windows

#### gdi32

Included with Windows

#### WinMM

Included with Windows

### Linux

Required libraries:

> gl, m, pthread, dl, rt, X11

The required libraries can be installed using the package manager of choice for your distro
of choice, here are some bash scripts for some popular distro (Copied from Raylib Wiki)

#### Ubuntu
>```console
>   sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
>```

#### Fedora
>```console
>   sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
>```

#### Arch Linux
>```console
>   sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
>```

#### Void Linux
>```console
>   sudo xbps-install make alsa-lib-devel libglvnd-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel mesa MesaLib-devel
>```

### Cross Platform Required Libraries / Frameworks

#### Raylib v5.5
> Download the source from [github](https://github.com/raysan5/raylib/tree/5.5)
> Compile as a static library using MinGW-w64 and copy to lib folder
>```console
>   cd /path/to/raylib/src
>   make
>   cp /path/to/raylib/src/libraylib.a /path/to/bytewave-ui/lib
>   cp /path/to/raylib/src/raylib.h /path/to/bytewave-ui/lib
>   cp /path/to/raylib/src/raymath.h /path/to/bytewave-ui/lib
>```

#### Clay UI Layout Library v.13
> Currently contained within the bytewave-ui repo

#### Meson Build system
> Download and install from the [Meson Website](https://mesonbuild.com/Getting-meson.html)

## Building

The following commands will build the project;
>```console
>   cd /path/to/bytewave-ui
>   meson setup build
>   cd build
>   meson compile
>```

## Running

The following command will run the built project:
>```console
>   cd /path/to/bytewave-ui/build
>   ./bw-ui.exe
>```
