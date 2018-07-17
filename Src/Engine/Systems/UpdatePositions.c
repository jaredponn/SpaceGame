#include "UpdatePositions.h"
// -----------------------------------------
//    Private function declarations
// -----------------------------------------

// moves an appearance on the screen to a given position
static void SYS_moveAppearanceTo(Appearance*, const Position* const);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_updatePositions(const struct Position_Manager* positionManager_p,
                         struct Appearance_Manager* appearanceManager_p) {
        // getting the Position_Vector and its length
        const struct Position_Vector* positionData =
            Position_manager_get_data(positionManager_p);
        size_t postionDataLength = Position_vector_size(positionData);

        // global index of the position that it is known by all other components
        size_t globalIndex;

        // temporary variabels
        Position* tmpPosition_p;
        Appearance* tmpAppearance_p;

        for (size_t i = 0; i < postionDataLength; ++i) {
                // gets the position pointer
                tmpPosition_p = Position_vector_get_p(positionData, i);

                // gets the corrosponding appearance pointer for th eposition
                globalIndex =
                    Position_manager_get_index_from(positionManager_p, i);
                tmpAppearance_p = Appearance_manager_get_data_p_at(
                    appearanceManager_p, globalIndex);

                // updates
                SYS_moveAppearanceTo(tmpAppearance_p, tmpPosition_p);
        }
}

// -----------------------------------------
//    Private function implementations
// -----------------------------------------
static void SYS_moveAppearanceTo(Appearance* appearance,
                                 const Position* const position) {
        CPT_setSdlRectPosition(&appearance->dstrect, position);
}
