project('Plutus','cpp')

args = ['-std=c++17',
  '-Wall',
  '-Werror',
  '-Wextra',
  '-Wpedantic'
]

src = files(
  'src/main.cpp'
)

incl = include_directories('include')

sqlitecpp = dependency('sqlitecpp',version: '3.3.2')

executable('plutus',src,include_directories: incl, cpp_args: args, dependencies: sqlitecpp)
