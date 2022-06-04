project(
  'bs2',
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'],
  meson_version: '>= 0.56.2')

bs2_source = [
  'codegen.cc',
  'codegen/x64/x64.cc',
  'codegen/xml/xml.cc',
  'lex.cc',
  'main.cc',
  'op.cc',
  'parser.cc',
  'type.cc',
  'util.cc',
]

if ['address', 'memory', 'undefined'].contains(get_option('b_sanitize'))
  if meson.get_compiler('cpp').get_id() != 'clang'
    error('msan only suported on clang')
  else
    # Msan requires libc++
    add_global_arguments('-stdlib=libc++', language: 'cpp')
    add_global_link_arguments('-stdlib=libc++', language: 'cpp')
  endif
endif


bs2_deps = [
  dependency('fmt')
]

executable(
  'bs2',
  sources: bs2_source,
  dependencies: bs2_deps,         
  install : true)
