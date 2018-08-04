#include "Src/Engine/Components/Appearance.h"
#include "Src/Engine/Components/Components.h"
#include "Src/Engine/Components/Entity.h"
#include "Src/Engine/Components/Movement.h"

// copies all Positions to things with an appearance
void SYS_updatePositions(const struct V2Manager *positionManager_p,
			 struct AppearanceManager *appearanceManager_p,
			 struct CircAabbManager *bCircManager);

void SYS_setElementPosition(struct V2Manager *positionManager,
			    const size_t globalIndex, const Position *position,
			    const struct V2 *offset);
