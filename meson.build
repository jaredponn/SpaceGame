# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c',
 default_options : ['c_std=c11', '-Wall','-Wextra'] )

inc = include_directories('Extras')
inc = include_directories('Lib')
inc = include_directories('Src')

srcs = ['Src/Main.c'
       , 'Src/Engine/Engine.c'

       # resource loading
       , 'Src/Engine/Resources/ResourceRegistry.c'
       , 'Src/Engine/Resources/LoadResources.c'
       # Components
       , 'Src/Engine/Components/EngineComponents.c'
       , 'Src/Engine/Components/Acceleration.c'
       , 'Src/Engine/Components/Position.c'
       , 'Src/Engine/Components/Velocity.c'
       , 'Src/Engine/Components/Appearance.c'
       , 'Src/Engine/Components/Entity.c'

       # Systems
       , 'Src/Engine/Systems/Render.c'
       , 'Src/Engine/Systems/UpdatePositions.c'
       , 'Src/Engine/Systems/ApplyVelocity.c'
       , 'Src/Engine/Systems/ApplyAcceleration.c'

       # extras
       , 'Src/Engine/ExtraState/EngineExtraState.c'

        # inputs
       , 'Src/Engine/InputManager/Input.c'

        # Lib
       , 'Lib/Util.c' 
       , 'Lib/E_FreeList.c' 
       , 'Lib/sizet_Vector.c' 
       , 'Lib/V2.c' 
       , 'Lib/Time.c'
       ]

executable('spacegame'
        , srcs
        , link_args : ['-lSDL2', '-lSDL2_image'] )

testsrcs = [ 'Lib/Util.c'  
           , 'UnitTesting/Run_Tests.c'
           , 'Lib/tests/Data_Structures.c'
           , 'Lib/sizet_Vector.c'
           , 'Src/Engine/Components/Appearance.c'
           ]
unittests = executable('unittests', testsrcs, link_args :'-lcheck')
test('unittests', unittests )
