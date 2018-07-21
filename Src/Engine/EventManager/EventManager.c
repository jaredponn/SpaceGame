#include "EventManager.h"

void EVT_push_back(struct ECS_EventManager* eventManager, const Event* event) {
        Event_vector_push_back(&eventManager->events, *event);
}

const struct Event_Vector* EVT_get_events(
    const struct ECS_EventManager* eventManager) {
        return &eventManager->events;
}

void EVT_clear(struct ECS_EventManager* eventManager) {
        Event_vector_lazy_clear(&eventManager->events);
}

void ECS_initEventManager(struct ECS_EventManager* eventManager,
                          size_t capacity) {
        Event_vector_init(&eventManager->events);
        Event_vector_reserve(&eventManager->events, capacity);
}

VECTOR_DEFINE(Event, Event)
