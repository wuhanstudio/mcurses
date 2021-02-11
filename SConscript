from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('src/*.c')

if GetDepend('MCURSES_USING_SIMPLE'):
	src    += Glob('examples/simple_test.c')

if GetDepend('MCURSES_USING_BOX'):
	src    += Glob('examples/box_demo.c')

if GetDepend('MCURSES_USING_MATRIX_RAIN'):
	src    += Glob('examples/matrix_rain.c')

if GetDepend('MCURSES_USING_SCREEN'):
	src    += Glob('examples/screen_demo.c')

if GetDepend('MCURSES_USING_TEMPERATURE'):
	src    += Glob('examples/temperature_graph.c')

if GetDepend('MCURSES_USING_TOWER'):
	src    += Glob('examples/towers_of_hanoi.c')

if GetDepend('MCURSES_USING_KEY_TEST'):
	src    += Glob('examples/key_test.c')

if GetDepend('MCURSES_USING_NUMBER_EDITOR'):
	src    += Glob('examples/number_edit_demo.c')

if GetDepend('MCURSES_USING_HEX_EDITOR'):
	src    += Glob('examples/hexeditor_demo.c')

path   =  [cwd + '/src']
path   += [cwd + '/examples']

LOCAL_CCFLAGS = ''

group = DefineGroup('mcurses', src, depend = ['PKG_USING_MCURSES'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
