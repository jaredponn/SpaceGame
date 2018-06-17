# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c')

inc = include_directories('Resources')
inc = include_directories('Lib')

srcs = ['Src/Main.c'
     # ,'lib/Lists/IDFreeList.c'
       , 'Lib/Stack/IntStack.c'
       , 'Lib/Util.c' ]
executable('spacegame',srcs, link_args : '-lSDL2')

testsrcs = ['Lib/Vector/GenericVector.c','Lib/FreeList/GenericFreeList.c', 'Lib/Stack/IntStack.c','Lib/Util.c'  , 'Tests/Stack_Test.c']
unittests = executable('unittests', testsrcs, link_args :'-lcheck')
test('unittests', unittests )
