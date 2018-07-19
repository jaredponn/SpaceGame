#include "ApplyAcceleration.h"
#include "Lib/V2.h"

// -----------------------------------------
//    Private function declarations
// -----------------------------------------

// adds the acceleration * time to the position
static void SYS_addAccelerationToVelocity(const Acceleration* const,
                                          Velocity* const, Time);

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
        struct V2 changeInDistance =
            V2_smul(acceleration_p, UTI_castTimeToSecs(dt));

        // applying the velocity changes to the position
        *velocity_p = V2_add(velocity_p, &changeInDistance);
}
