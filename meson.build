project('Academia - Dreams of Madness', license: 'GPL-2.0-only',
		license_files: 'LICENSE.txt', meson_version: '>=1.1.0',
		version: 'v2023.06.27-NEXT')
proj_copyright = '(c) 2023 Academia Team'

sources = [
	'src/acaddom.c',
	'src/arg_list.c',
	'src/bitmaps.c',
	'src/effects.c',
	'src/events.c',
	'src/font16.c',
	'src/in_vbl.c',
	'src/input.c',
	'src/model.c',
	'src/move.c',
	'src/mus_vbl.c',
	'src/music.c',
	'src/num_util.c',
	'src/psg.c',
	'src/raster.c',
	'src/renderer.c',
	'src/vbl.c',
	'src/vector.c'
]

if host_machine.cpu() == 'm68k'
	sources += 'src/in_asm.s'
	sources += 'src/ints_asm.s'
	sources += 'src/psg_asm.s'
	sources += 'src/rast_asm.s'
	sources += 'src/su_asm.s'
	sources += 'src/vbl_asm.s'
endif

if meson.is_cross_build()
	compiler = find_program('vc', required: true)
	compilerArgs = ['+tos16']
	run_command(compiler, compilerArgs, check: true)

	custom_target('acaddom', build_by_default: true,
				  command: [compiler, compilerArgs, '@INPUT@', '-o',
				  			'@OUTPUT@'],
				  input: sources, output: 'acaddom.tos')
else
	error('Only cross compilation is supported.')
endif