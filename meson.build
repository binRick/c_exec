#//***********************************************************/
project(
    'c_exec',          ['c'],         version : '0.0.1',         
    default_options : ['warning_level=2','c_std=gnu99'],
)
#//***********************************************************/
host_system = host_machine.system()

cc = meson.get_compiler('c')
sh = find_program('sh', required : true)
passh = find_program('passh', required : true)

#//***********************************************************/
test_deps = []
#//***********************************************************/
incdir = include_directories(
  './include', 
  './deps', 
  '../',
  '../metalang99/include',
  '../ok',
)
#//***********************************************************/
test_exec1 = executable('test_exec1', [ 
    'src/exec.c', 
    'tests/test_exec1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
tests = [
  ['test_exec1 -h', test_exec1, '-h',  ],
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
test(i[0], passh, args: [ i[1], i[2] ], env: test_env)
endforeach
#//***********************************************************/
#//***********************************************************/


