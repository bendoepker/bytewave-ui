# ByteWave UI

This repo serves as the testing ground for development of the ByteWave UI before it is
ported into the main project, this is mainly for testing out UI layout, optimization, etc

## Compiling

### Dependencies:

#### OpenGL
> Included in most system libraries

#### gdi32
> Included with Windows / Wine

#### WinMM
> Included with Windows / Wine

#### Raylib v5.5
> Download the source from [github](https://github.com/raysan5/raylib/tree/5.5)
> Compile as a static library using MinGW-w64 and copy to lib folder
>```console
    cd /path/to/raylib/src
    make
    cp /path/to/raylib/src/libraylib.a /path/to/bytewave-ui/lib
    cp /path/to/raylib/src/raylib.h /path/to/bytewave-ui/lib
    cp /path/to/raylib/src/raymath.h /path/to/bytewave-ui/lib
>```

#### Clay UI Layout Library v.13
> Currently contained within the bytewave-ui repo

#### Meson Build system
> Download and install from the [Meson Website](https://mesonbuild.com/Getting-meson.html)

### Building

The following commands will build the project;
>```console
    cd /path/to/bytewave-ui
    meson setup build
    cd build
    meson compile
>```

### Running

The following command will run the built project:
>```console
    cd /path/to/bytewave-ui/build
    ./bw-ui.exe
>```
