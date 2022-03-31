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
test_reproc1 = executable('test_reproc1', [ 
    'src/exec.c', 
    'tests/test_reproc1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
test_exec1 = executable('test_exec1', [ 
    'src/exec.c', 
    'tests/test_exec1.c',  
  ], include_directories : [incdir], 
  dependencies : [],
)
#//***********************************************************/
reprocs = [
  ['test_reproc1', 'test_reproc1.log', test_reproc1]
]
tests = [
  # ['test_exec1 HELP', 'exec1.log', test_exec1]
]
#//***********************************************************/

#//***********************************************************/
test_env = environment()
test_env.set('__SH', sh.full_path())
test_env.set('__BD', meson.current_build_dir())
test_env.set('__SD', meson.current_source_dir())
#//***********************************************************/
foreach i : tests
#//***********************************************************/
 log = '/tmp/' + i[1]
 help_cmd  = i[2].path() + ' ' + '-h'
 sleep_cmd = i[2].path() + ' ' + 'sleep'
 echo_cmd  = i[2].path() + ' ' + 'echo OK123'
 #//***********************************************************/
 test(i[0]+'->HELP();   '+i[0], passh, args: [ '-L', log, '/bin/sh', '-c', help_cmd])
 test(i[0]+'->SLEEP(1);   '+i[0], passh, args: [ '-L', log, '/bin/sh', '-c', sleep_cmd + ' 1'])
 test(i[0]+'->SLEEP(2);   '+i[0], passh, args: [ '-L', log, '/bin/sh', '-c', sleep_cmd + ' 2'])
 test(i[0]+'->ECHO(OK123);   '+i[0], passh, args: [ '-L', log, '/bin/sh', '-c', echo_cmd])
#//***********************************************************/
endforeach
foreach i : reprocs
 log = '/tmp/' + i[1]
 cmd = i[2]
 test(i[0], passh, args: [ '-L', log, '/bin/sh', '-c', cmd])
endforeach
#//***********************************************************/
#//***********************************************************/


