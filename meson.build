# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c')

inc = include_directories('Resources')
inc = include_directories('Lib')

srcs = ['Src/Main.c'
       , 'Lib/Util.c' ]
executable('spacegame',srcs, link_args : '-lSDL2')

testsrcs = ['Lib/Util.c'  
        ,'Tests/Lib_Tests.c']
unittests = executable('unittests', testsrcs, link_args :'-lcheck')
test('unittests', unittests )
