#include "Appearance.h"
#include "Entity.h"
#include "Position.h"

struct ECS_Components;
struct ECS_Components {
        struct Entity_Manager entity_manager;
        struct Position_Manager position_manager;
        struct Appearance_Manager appearance_manager;
};
