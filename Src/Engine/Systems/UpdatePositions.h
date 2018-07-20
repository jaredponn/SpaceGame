#include "Src/Engine/Components/Appearance.h"
#include "Src/Engine/Components/EngineComponents.h"
#include "Src/Engine/Components/Entity.h"
#include "Src/Engine/Components/Movement.h"

// copies all Positions to things with an appearance
void SYS_updatePositions(const struct Position_Manager*,
                         struct Appearance_Manager*);
