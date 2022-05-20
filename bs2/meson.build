project(
  'bs2',
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'],
  meson_version: '>= 0.56.2')

bs2_source = [
  #'codegen.cc',
  #'codegen/xml/xml.cc',
  'lex.cc',
  'main.cc',
  #'parser.cc',
  'util.cc',
]

bs2_deps = [
  dependency('fmt')
]

executable(
  'bs2',
  sources: bs2_source,
  dependencies: bs2_deps,         
  install : true)
