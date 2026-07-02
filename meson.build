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

sources = run_command(
    'find',
    'src',
    '-name',
    '*.cpp',
    check: true
).stdout().strip().split()

inc = include_directories('src')

shared_library(
    'renfsu2',
    sources,
    include_directories: inc,
    dependencies: minhook_dep,
    link_args: ['-static-libgcc', '-static-libstdc++', '-static'],
    name_prefix: '',
    install: true,
)
