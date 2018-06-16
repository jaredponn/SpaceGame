# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c')

inc = include_directories('Resources')
inc = include_directories('lib')

srcs = ['src/Main.c'
     # ,'lib/Lists/IDFreeList.c'
       , 'lib/Stack/IntStack.c'
       , 'lib/Util.c' ]

executable('spacegame',srcs, link_args : '-lSDL2')
