project('Plutus','cpp')

args = ['-std=c++17',
  '-Wall',
  '-Werror',
  '-Wextra',
  '-Wpedantic'
]

# TODO: rewrite
src = files(
  'src/main.cpp',
  'src/sql.cpp',
  'src/utils.cpp',
  'src/category.cpp',
  'src/transaction.cpp',
  'src/mbudget.cpp',
  'src/controllers/category.cpp'
)

incl = include_directories('include')

sqlitecpp = dependency('sqlitecpp',version: '>=3.3.2')

executable('plutus',src,include_directories: incl, cpp_args: args, dependencies: sqlitecpp)
