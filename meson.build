# set the compiler to clang first
# export CC=/usr/bin/clang

project('SpaceGame', 'c',
 default_options : ['c_std=c11'] )

inc = include_directories('Extras')
inc = include_directories('Lib')
inc = include_directories('Extern/glad/include')
inc = include_directories('Src')

srcs = ['Src/Main.c'
       , 'Src/Engine/Engine.c'

       # resource loading
       , 'Src/Engine/Resources/ResourceRegistry.c'
       , 'Src/Engine/Resources/LoadResources.c'

       # Components
       , 'Src/Engine/Components/Components.c'
       , 'Src/Engine/Components/Movement.c'
       , 'Src/Engine/Components/Appearance.c'
       , 'Src/Engine/Components/Entity.c'
       , 'Src/Engine/Components/Aabb.c'
       , 'Src/Engine/Components/Attribute.c'

       , 'Src/Engine/Components/PathFindingNode.c'

       #/ Systems
       , 'Src/Engine/Systems/Render.c'
       , 'Src/Engine/Systems/UpdatePositions.c'
       , 'Src/Engine/Systems/ApplyMovementTransforms.c'
       , 'Src/Engine/Systems/AabbHitTest.c'

       #/ Low level systems
       , 'Src/Engine/LLSystems/LLSystemManager.c'
       , 'Src/Engine/LLSystems/Time.c'
       , 'Src/Engine/LLSystems/LLSInput.c'
       , 'Src/Engine/LLSystems/Input.c'
       , 'Src/Engine/LLSystems/Window.c'
       , 'Src/Engine/LLSystems/Render.c'
       , 'Src/Engine/LLSystems/LLSRender.c'

       # extras
       ,'Src/Engine/ExtraState/EngineExtraState.c'

        # inputs
       , 'Src/Engine/Input/Mouse.c'
       , 'Src/Engine/Input/Window.c'
       , 'Src/Engine/Input/InputHandler.c'
       , 'Src/Engine/Input/GameInputMaps.c'
       , 'Src/Engine/Input/InputMap.c'

        # Evenet manager
       , 'Src/Engine/Events/GameEvents.c'
       , 'Src/Engine/Events/SystemEvents.c'

        # Lib
       , 'Lib/GUI.c'
       , 'Lib/Util.c' 
       , 'Lib/MarkedFreeList.c' 
       , 'Lib/sizet_Vector.c' 
       , 'Lib/V2.c' 
       , 'Lib/Time.c'
       , 'Lib/Logger.c'

       # Extern
       , 'Extern/glad/src/glad.c'
       ]

executable('spacegame'
        , srcs
        , c_args : ['-Wall', '-Wextra', '-O2', '-g']
        # , c_args : ['-Wall', '-Wextra', '-O2', '-g', '-v', '-da', '-Q']
        , link_args : ['-lSDL2', '-lSDL2_image', '-lm', '-lglfw', '-lGL', '-ldl'] )

testsrcs = [ 'Lib/Util.c'  
           , 'UnitTesting/Run_Tests.c'
           , 'Lib/tests/Data_Structures.c'
           , 'Lib/sizet_Vector.c'
           , 'Lib/E_FreeList.c'
           , 'Lib/MarkedFreeList.c' 

           , 'Src/Engine/Components/Components.c'
           , 'Src/Engine/Components/Movement.c'
           , 'Src/Engine/Components/Appearance.c'
           , 'Src/Engine/Components/Entity.c'
           , 'Src/Engine/Components/Aabb.c'
           , 'Src/Engine/Components/Attribute.c'

           , 'Src/Engine/Components/Appearance.c'
           , 'Lib/Time.c'
           ]
unittests = executable('unittests', testsrcs, c_args : ['-Wall', '-Wextra', '-O2'],link_args :'-lcheck')
test('unittests', unittests )


# mlib
mlibtestsrcs = [ 'mlib/tests/mruntests.c' ]
mlibtests = executable('mlibtests', mlibtestsrcs, c_args : ['-Wall', '-Wextra', '-O2'], link_args :'-lcheck')
test('mlibtests', mlibtests )
