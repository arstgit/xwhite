project('xwhite', 'c',
  version : '0.0.2',
  default_options : ['warning_level=3'])

dep = [dependency('x11'), dependency('xrandr')]

exe = executable('xwhite', 'xwhite.c',
  dependencies : dep,
  install : true)

test('basic', exe)
