project(
    'reNFSU2',
    'cpp',
    'c',
    version: '0.1.0',
    default_options: ['cpp_std=c++17'],
)

cmake = import('cmake')
minhook_proj = cmake.subproject('minhook')
minhook_dep = minhook_proj.dependency('minhook')

sources = ['src/main.cpp']

shared_library(
    'renfsu2',
    sources,
    dependencies: minhook_dep,
    name_prefix: '',
    install: true,
)
