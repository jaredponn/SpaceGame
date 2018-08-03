#include "AabbHitTest.h"

// TODO find a way to make this stuff more generic so we don't literally copy
// and paste the same thing....

// TODO evreything is broken about this

void SYS_rectAabbHitTest(const struct RectAabbManager *arectmanager,
			 const struct RectAabbManager *brectmanager,
			 struct EVT_SystemEventManager *eventmanager)
{
	const struct RectAabbVector *arectvec =
		RectAabbManager_get_packed_data(arectmanager);
	size_t arectvecSize = RectAabbVector_size(arectvec);

	const struct RectAabbVector *brectvec =
		RectAabbManager_get_packed_data(brectmanager);
	size_t brectvecSize = RectAabbVector_size(brectvec);

	for (size_t i = 0; i < arectvecSize; ++i) {
		for (size_t j = 0; j < brectvecSize; ++j) {
			if (CPT_hitTestRectAabb(
				    RectAabbVector_get_p(arectvec, i),
				    RectAabbVector_get_p(brectvec, j)))

			{
				/** EventManager_push_back( */
				/**         eventmanager, */
				/**         (Event){.type = EVT_Collision, */
				/**                 .collision =
				 * (EVT_CollisionSignal){ */
				/**                         .a =
				 * RectAabbManager_get_index_from( */
				/** arectmanager, */
				/**                                 i), */
				/**                         .b =
				 * RectAabbManager_get_index_from( */
				/** brectmanager, */
				/**                                 j)}}); */
			}
		}
	}
}

void SYS_circAabbHitTest(const struct CircAabbManager *aCircManager,
			 const struct CircAabbManager *bCircManager,
			 struct EVT_SystemEventManager *eventManager)
{
	const struct CircAabbVector *arectvec =
		CircAabbManager_get_packed_data(aCircManager);
	size_t arectvecSize = CircAabbVector_size(arectvec);

	const struct CircAabbVector *brectvec =
		CircAabbManager_get_packed_data(bCircManager);
	size_t brectvecSize = CircAabbVector_size(brectvec);

	for (size_t i = 0; i < arectvecSize; ++i) {
		for (size_t j = 0; j < brectvecSize; ++j) {
			if (CPT_hitTestCircAabb(
				    CircAabbVector_get_p(arectvec, i),
				    CircAabbVector_get_p(brectvec, j)))

			{
				/** EventManager_push_back( */
				/**         eventManager, */
				/**         (Event){.type = EVT_Collision, */
				/**                 .collision =
				 * (EVT_CollisionSignal){ */
				/**                         .a =
				 * CircAabbManager_get_index_from( */
				/** aCircManager, */
				/**                                 i), */
				/**                         .b =
				 * CircAabbManager_get_index_from( */
				/** bCircManager, */
				/**                                 j)}}); */
			}
		}
	}
}

void SYS_circRectAabbHitTest(const struct CircAabbManager *circAabbManager,
			     const struct RectAabbManager *rectAabbManager,
			     struct EVT_SystemEventManager *eventManager)
{

	const struct CircAabbVector *circVec =
		CircAabbManager_get_packed_data(circAabbManager);
	size_t circVecSize = CircAabbVector_size(circVec);

	const struct RectAabbVector *rectVec =
		RectAabbManager_get_packed_data(rectAabbManager);
	size_t rectVecSize = RectAabbVector_size(rectVec);

	for (size_t i = 0; i < circVecSize; ++i) {
		for (size_t j = 0; j < rectVecSize; ++j) {
			if (CPT_hitTestCircRectAabb(
				    CircAabbVector_get_p(circVec, i),
				    RectAabbVector_get_p(rectVec, j)))

			{
				/** EventManager_push_back( */
				/**         eventManager, */
				/**         (Event){.type = EVT_Collision, */
				/**                 .collision =
				 * (EVT_CollisionSignal){ */
				/**                         .a =
				 * CircAabbManager_get_index_from( */
				/** circAabbManager, */
				/**                                 i), */
				/**                         .b =
				 * RectAabbManager_get_index_from( */
				/** rectAabbManager, */
				/**                                 j)}}); */
			}
		}
	}
}
