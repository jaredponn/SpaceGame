# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c')

inc = include_directories('Resources')
inc = include_directories('lib')

src = ['src/Main.c', 'lib/Lists/UIntNodes.c', 'lib/Lists/IDFreeList.c']

executable('spacegame',src, link_args : '-lSDL2')
