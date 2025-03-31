project('bw-ui', 'c')


cc = meson.get_compiler('c')
message(cc.get_id())

dependencies = []
if build_machine.system() == 'windows'
  #winmm
  winmm = cc.find_library('winmm')
  dependencies += winmm

  #dgi
  gdi32 = cc.find_library('gdi32')
  dependencies += gdi32

  #OpenGL
  opengl = cc.find_library('opengl32')
  dependencies += opengl
endif
if build_machine.system() == 'linux'
  #GL
  gl = cc.find_library('GL')
  dependencies += gl

  #m
  m = cc.find_library('m')
  dependencies += m

  #pthread
  pthread = cc.find_library('pthread')
  dependencies += pthread

  #dl
  dl = cc.find_library('dl')
  dependencies += dl

  #rt
  rt = cc.find_library('rt')
  dependencies += rt

  #X11
  X11 = cc.find_library('X11')
  dependencies += X11
endif



cwd = meson.current_source_dir()
lib_dir = join_paths(cwd, 'lib')
raylib = cc.find_library('raylib', dirs: lib_dir)
dependencies += raylib


executable('bw-ui', 'main.c', dependencies: dependencies)
