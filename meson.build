# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c',
 default_options : ['c_std=c11', '-Wall'] )

inc = include_directories('Extras')
inc = include_directories('Lib')

srcs = ['Src/Main.c'
       , 'Src/Engine/RunEngine.c'
       , 'Src/Engine/Resources/ResourceRegistry.c'
       , 'Src/Engine/Resources/LoadResources.c'
       , 'Src/Engine/Components/Position.c'
       , 'Src/Engine/Components/Appearance.c'
       , 'Src/Engine/Components/Entity.c'
       , 'Lib/Util.c' ]

executable('spacegame'
        , srcs
        , link_args : ['-lSDL2', '-lSDL2_image'] )

testsrcs = [ 'Lib/Util.c'  
           , 'Tests/Lib_Tests.c'
           , 'Tests/Data_Structures.c'
           ]
unittests = executable('unittests', testsrcs, link_args :'-lcheck')
test('unittests', unittests )
