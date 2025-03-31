project('bw-ui', 'c')


cc = meson.get_compiler('c')
message(cc.get_id())

winmm = cc.find_library('winmm')
opengl = cc.find_library('opengl32')
gdi32 = cc.find_library('gdi32')

cwd = meson.current_source_dir()
lib_dir = join_paths(cwd, 'lib')
raylib = cc.find_library('raylib', dirs: lib_dir)

dependencies = [winmm, opengl, gdi32, raylib]
src = ['bw-components.c']

executable('bw-ui', 'main.c', dependencies: dependencies, sources: src)
