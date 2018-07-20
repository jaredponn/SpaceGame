#include "ApplyMovementTransforms.h"
#include "Src/Engine/Components/Movement.h"
#include "Src/Engine/Components/MovementGenerics.h"

// -----------------------------------------
//    Private function declarations
// -----------------------------------------

// adds the velocity * time to the position
static void SYS_addVelocityToPosition(const Velocity* const, Position* const,
                                      Time);

// adds the acceleration * time to the position
static void SYS_addAccelerationToVelocity(const Acceleration* const,
                                          Velocity* const, Time);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_applyVelocity(const struct Velocity_Manager* const velocityManager_p,
                       struct Position_Manager* const positionManager_p,
                       const Time dt) {
        //  getting the Velocity_Vector and its length
        const struct Velocity_Vector* velocityData_p =
            Velocity_manager_get_data(velocityManager_p);
        size_t velocityDataLength = Velocity_vector_size(velocityData_p);

        // temp value of the global index of the current
        size_t globalIndex;

        // more temp variables
        Velocity* tmpVelocity_p;
        Position* tmpPosition_p;

        for (size_t i = 0; i < velocityDataLength; ++i) {
                // gets the i'th velocity pointer
                tmpVelocity_p = Velocity_vector_get_p(velocityData_p, i);

                // gets the corrosponding position pointer
                globalIndex =
                    Velocity_manager_get_index_from(velocityManager_p, i);
                tmpPosition_p = Position_manager_get_data_p_at(
                    positionManager_p, globalIndex);

                // modifying the position
                SYS_addVelocityToPosition(tmpVelocity_p, tmpPosition_p, dt);
        }
}

// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_applyAcceleration(
    const struct Acceleration_Manager* const velocityManager_p,
    struct Velocity_Manager* const positionManager_p, const Time dt) {
        //  getting the Acceleration_Vector and its length
        const struct Acceleration_Vector* velocityData_p =
            Acceleration_manager_get_data(velocityManager_p);
        size_t velocityDataLength = Acceleration_vector_size(velocityData_p);

        // temp value of the global index of the current
        size_t globalIndex;

        // more temp variables
        Acceleration* tmpAcceleration_p;
        Velocity* tmpVelocity_p;

        for (size_t i = 0; i < velocityDataLength; ++i) {
                // gets the i'th velocity pointer
                tmpAcceleration_p =
                    Acceleration_vector_get_p(velocityData_p, i);

                // gets the corrosponding position pointer
                globalIndex =
                    Acceleration_manager_get_index_from(velocityManager_p, i);
                tmpVelocity_p = Velocity_manager_get_data_p_at(
                    positionManager_p, globalIndex);

                // modifying the position
                SYS_addAccelerationToVelocity(tmpAcceleration_p, tmpVelocity_p,
                                              dt);
        }
}

// -----------------------------------------
//    Private function implementations
// -----------------------------------------
static void SYS_addAccelerationToVelocity(
    const Acceleration* const acceleration_p, Velocity* const velocity_p,
    Time dt) {
        // calculating the change in distance
        Velocity changeInVelocity =
            MVT_smul((const Velocity*)acceleration_p, UTI_castTimeToSecs(dt));

        // applying the velocity changes to the position
        *velocity_p = MVT_add((const Velocity*)velocity_p, &changeInVelocity);
}

static void SYS_addVelocityToPosition(const Velocity* const velocity_p,
                                      Position* const position_p, Time dt) {
        // old les sshitty way
        /** // calculating the change in distance */
        /** struct V2 changeInDistance = */
        /**     V2_smul(velocity_p, UTI_castTimeToSecs(dt)); */
        /**  */
        /** // applying the velocity changes to the position */
        /** *position_p = V2_add(position_p, &changeInDistance); */

        // calculating the change in distance
        Position changeInDistance =
            MVT_smul((const Position*)velocity_p, UTI_castTimeToSecs(dt));

        // applying the velocity changes to the position

        *position_p = MVT_add((const Position*)position_p, &changeInDistance);
}
