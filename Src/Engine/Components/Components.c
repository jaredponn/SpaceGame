#include "Components.h"
#include <stdint.h>

void CPT_initComponents(struct CPT_Components *engineComponents,
			size_t capacity)
{
	MarkedFreeList_init(&engineComponents->free_elements);
	MarkedFreeList_reserve(&engineComponents->free_elements, capacity);

	// initilizes all the components with capacity
#define X_CPT(type, prefix, name)                                              \
	prefix##Manager_init(&engineComponents->MANAGER_NAME(name), capacity);
	LIST_OF_COMPONENTS
#undef X_CPT
}

// TODO broken
void CPT_updateCurFreeIndex(struct CPT_Components *components)
{
	struct MarkedFreeList *freeElements = &components->free_elements;
	if (MarkedFreeList_is_index_used(freeElements,
					 CPT_getCurFreeIndex(components))) {
		/** (void)MarkedFreeList_add(&components->free_elements, */
		/**                          (MarkedIndex){true, SIZE_MAX}); */
		MarkedFreeList_update_index(freeElements);
	}
}

size_t CPT_getCurFreeIndex(struct CPT_Components *components)
{

	return MarkedFreeList_get_curr_free_index(&components->free_elements);
}

void CPT_deleteEntityAt(struct CPT_Components *engineComponents, size_t index)
{
	// updates the next free index so the free list updates properly
	CPT_updateCurFreeIndex(engineComponents);

	// marking the index free for the next get_next_free_index function
	struct MarkedFreeList *freeElements = &engineComponents->free_elements;
	if (MarkedIndexVector_size(&freeElements->data) > index
	    && MarkedFreeList_is_index_used(
		       freeElements,
		       index)) // checks to see if there is something first
	{
		MarkedFreeList_remove_at(freeElements, index);
		MarkedFreeList_mark_index_as_free(freeElements, index);

		// deleting the components each of the managers
#define X_CPT(type, prefix, name)                                              \
	prefix##Manager_remove_at(&engineComponents->MANAGER_NAME(name), index);
		LIST_OF_COMPONENTS
#undef X_CPT
	}
}


// defining the component manager getters
#define X_CPT(type, prefix, name)                                              \
	struct prefix##Manager *MANAGER_GETTER_NAME(name)(                     \
		struct CPT_Components * engineComponents)                      \
	{                                                                      \
		return &engineComponents->MANAGER_NAME(name);                  \
	}
LIST_OF_COMPONENTS
#undef X_CPT

// CPT_add<name>At(components, index, val )
#define X_CPT(type, prefix, name)                                              \
	void MANAGER_ADD_AT_NAME(name)(struct CPT_Components                   \
					       * engineComponents,             \
				       size_t index, type * val)               \
	{                                                                      \
		MarkedFreeList_mark_index_as_used(                             \
			&engineComponents->free_elements, index);              \
		prefix##Manager_add_at(                                        \
			MANAGER_GETTER_NAME(name)(engineComponents), index,    \
			val);                                                  \
	}
LIST_OF_COMPONENTS
#undef X_CPT

// CPT_add<name>(components, index, val )
#define X_CPT(type, prefix, name)                                              \
	void MANAGER_ADD_NAME(name)(struct CPT_Components * components,        \
				    type * val)                                \
	{                                                                      \
		MANAGER_ADD_AT_NAME(name)                                      \
		(components, CPT_getCurFreeIndex(components), val);            \
	}
LIST_OF_COMPONENTS
#undef X_CPT

// free components
void CPT_freeComponents(struct CPT_Components *engineComponents)
{
	MarkedFreeList_free(&engineComponents->free_elements);

	// initilizes all the components with capacity
#define X_CPT(type, prefix, name)                                              \
	prefix##Manager_free(&engineComponents->MANAGER_NAME(name));
	LIST_OF_COMPONENTS
#undef X_CPT
}
