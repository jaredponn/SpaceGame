/**
 * Wrappers for the specialize typed functions
 */

// clang-format off

/* Vector */
#define vector_init(_vec)                       \
        ((_Generic((_vec), Entity               \
                   : Entity_vector_init, ID     \
                   : id_vector_init, Appearance \
                   : app_vector_init))(_vec))

#define vector_reserve(_vec, _capacity)            \
        ((_Generic((_vec), Entity                  \
                   : Entity_vector_reserve, ID     \
                   : id_vector_reserve, Appearance \
                   : app_vector_reserve))(_vec, _capacity))

#define vector_resize(_vec, _capacity)            \
        ((_Generic((_vec), Entity                 \
                   : Entity_vector_resize, ID     \
                   : id_vector_resize, Appearance \
                   : app_vector_resize))(_vec, _capacity))

#define vector_size(_vec)                       \
        ((_Generic((_vec), Entity               \
                   : Entity_vector_size, ID     \
                   : id_vector_size, Appearance \
                   : app_vector_size))(_vec))

#define vector_capacity(_vec)                       \
        ((_Generic((_vec), Entity                   \
                   : Entity_vector_capacity, ID     \
                   : id_vector_capacity, Appearance \
                   : app_vector_capacity))(_vec))

#define vector_pushback(_vec, _val)                 \
        ((_Generic((_vec), Entity                   \
                   : Entity_vector_pushback, ID     \
                   : id_vector_pushback, Appearance \
                   : app_vector_pushback))(_vec, _val))

#define vector_popback(_vec)                       \
        ((_Generic((_vec), Entity                  \
                   : Entity_vector_popback, ID     \
                   : id_vector_popback, Appearance \
                   : app_vector_popback))(_vec))

#define vector_popback(_vec)                       \
        ((_Generic((_vec), Entity                  \
                   : Entity_vector_popback, ID     \
                   : id_vector_popback, Appearance \
                   : app_vector_popback))(_vec))

#define vector_set(_vec, _index, _val)         \
        ((_Generic((_vec), Entity              \
                   : Entity_vector_set, ID     \
                   : id_vector_set, Appearance \
                   : app_vector_set))(_vec, _index, _val))

#define vector_get(_vec, _index)               \
        ((_Generic((_vec), Entity              \
                   : Entity_vector_get, ID     \
                   : id_vector_get, Appearance \
                   : app_vector_get))(_vec, _index))

#define vector_remove(_vec, _index)               \
        ((_Generic((_vec), Entity                 \
                   : Entity_vector_remove, ID     \
                   : id_vector_remove, Appearance \
                   : app_vector_remove))(_vec, _index))

#define vector_free(_vec)                       \
        ((_Generic((_vec), Entity               \
                   : Entity_vector_free, ID     \
                   : id_vector_free, Appearance \
                   : app_vector_free))(_vec))

/* Free list*/
#define freelist_init(_freelist) \
        ((_Generic((_freelist), Entity : Entity_freelist_init))(_freelist))

#define freelist_init(_freelist) \
        ((_Generic((_freelist), Entity : Entity_freelist_init))(_freelist))

#define freelist_reserve(_freelist, _capacity) \
        ((_Generic((_freelist), Entity         \
                   : Entity_freelist_reserve))(_freelist, _capacity))

#define freelist_add(_freelist, _val) \
        ((_Generic((_freelist), Entity : Entity_freelist_add))(_freelist, _val))

#define freelist_get(_freelist, _index) \
        ((_Generic((_freelist), Entity  \
                   : Entity_freelist_get))(_freelist, _index))

#define freelist_removeat(_freelist, _index) \
        ((_Generic((_freelist), Entity       \
                   : Entity_freelist_removeat))(_freelist, _index))
