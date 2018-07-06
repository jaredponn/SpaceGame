#include <check.h>
#include <stdint.h>
#include "Data_Structures.h"

// testing the add function
START_TEST(componentmanager_test) {
        struct Int_Manager intmgr;
        /* initilizes an empty int manager with 10 reserved spots*/
        Int_manager_init(&intmgr, 10);

        /* check to see if there was a proper initiliaziatoin */
        // sparse_vector should have a size and capacity of 10 and should be
        // filled with SIZE_MAX
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 10);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 10);
        for (size_t i = 0; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // global_indicies, and data should have a size of 0, and capacity of 10
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 0);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 0);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // the next_packed_index should be 0
        ck_assert_int_eq(intmgr.next_packed_index, 0);

        /* Adding an int of value 0 at index 0.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, .. SIZE_MAX ]
         * global_indices: [0]
         * data: [0]
         */
        // at index 0, add value 0 to the array
        Int_manager_add(&intmgr, 0, 0);

        // checking the size / capacity of sparse_vector. SHould still be 10
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 10);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 10);

        // checking the size / capacity of global_indicies and data. Size should
        // be 1, and capacity should still be 10
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 1);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 1);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the indices of the sparse_array. index 0 should be 0, and the
        // rest should be SIZE_MAX
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 0), 0);
        for (size_t i = 1; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check value of index 0 of global_indices and data. Both should be 0
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 0);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 0);

        ck_assert_int_eq(intmgr.next_packed_index, 1);
        /* Adding an int of value 7 at index 3.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX ]
         * global_indices: [0,3]
         * data: [0,7]
         */
        // at index 3, add value 7 to the array
        Int_manager_add(&intmgr, 3, 7);

        // checking the size / capacity of sparse_vector. should still be 10
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 10);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 10);

        // checking the size / capacity of global_indicies and data. Size should
        // be 1, and capacity should still be 10
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 2);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 2);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 3), 1);
        for (size_t i = 4; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check indices global_indices and data.
        // global_indices: [0,3]
        // data: [0,7]
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 1), 3);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 0);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 1), 7);

        ck_assert_int_eq(intmgr.next_packed_index, 2);
        // clang-format off
        /* Adding an int of value 4 at index 10.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 4, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        // at index 10, add value 4 to the array
        Int_manager_add(&intmgr, 10, 4);

        // checking the size / capacity of sparse_vector. Should change to 15,
        // because 10 is too small
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 3);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 3);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 3), 1);
        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 10), 2);
        for (size_t i = 11; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1,2 for global_indices and data
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 1), 3);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 2), 10);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 0);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 1), 7);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 2), 4);

        ck_assert_int_eq(intmgr.next_packed_index, 3);
        // clang-format off
        /* Adding an int of value 4 at index 0 Nothing should occur.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 4, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        // at index 0, add value 4 to the array
        Int_manager_add(&intmgr, 0, 4);

        // checking the size / capacity of sparse_vector. Should change to 15,
        // because 10 is too small
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 3);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 3);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 3), 1);
        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 10), 2);
        for (size_t i = 11; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1,2 for global_indices and data
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 0);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 1), 3);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 2), 10);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 0);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 1), 7);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 2), 4);

        ck_assert_int_eq(intmgr.next_packed_index, 3);

        Int_manager_free(&intmgr);
}
END_TEST

// testing the delete function
START_TEST(componentmanager_test2) {
        struct Int_Manager intmgr;
        Int_manager_init(&intmgr, 10);

        // clang-format off
        /* Recreating the same manager from the add test
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 2, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        Int_manager_add(&intmgr, 0, 0);
        Int_manager_add(&intmgr, 3, 7);
        Int_manager_add(&intmgr, 10, 4);
        Int_manager_add(&intmgr, 0, 4);

        // clang-format off
        /* Deleting index 0
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [10, 3] 
         * data: [4, 7]
         */
        // clang-format on
        // at index 0, delete the value
        Int_manager_remove(&intmgr, 0);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 2);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 2);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the values of the sparse_vector
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 0), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 2), SIZE_MAX);

        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 3), 1);

        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 10), 0);
        for (size_t i = 11; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for global_indices and data
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 10);
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 1), 3);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 4);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 1), 7);

        ck_assert_int_eq(intmgr.next_packed_index, 2);

        // clang-format off
        /* Deleting index 3
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value
        Int_manager_remove(&intmgr, 3);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 1);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 1);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < 10; ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 10), 0);
        for (size_t i = 11; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for global_indices and data
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 10);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 4);

        ck_assert_int_eq(intmgr.next_packed_index, 1);

        // clang-format off
        /* Deleting an already deleted index like 0
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value
        Int_manager_remove(&intmgr, 0);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 1);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 1);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < 10; ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, 10), 0);
        for (size_t i = 11; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for global_indices and data
        ck_assert_int_eq(sizet_vector_get(&intmgr.global_indices, 0), 10);
        ck_assert_int_eq(Int_vector_get(&intmgr.data, 0), 4);

        ck_assert_int_eq(intmgr.next_packed_index, 1);

        // clang-format off
        /* Deleting the last element at index 10
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * global_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value

        Int_manager_remove(&intmgr, 10);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(sizet_vector_size(&intmgr.sparse_vector), 15);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(sizet_vector_size(&intmgr.global_indices), 0);
        ck_assert_int_eq(sizet_vector_capacity(&intmgr.global_indices), 10);
        ck_assert_int_eq(Int_vector_size(&intmgr.data), 0);
        ck_assert_int_eq(Int_vector_capacity(&intmgr.data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < sizet_vector_size(&intmgr.sparse_vector); ++i) {
                ck_assert_int_eq(sizet_vector_get(&intmgr.sparse_vector, i),
                                 SIZE_MAX);
        }

        ck_assert_int_eq(intmgr.next_packed_index, 0);

        // freeing the vectors
        Int_manager_free(&intmgr);
}
END_TEST

// testing adding and deletion
START_TEST(componentmanager_test3) {
        struct Int_Manager intmgr;
        /* initilizes an empty int manager with 5 reserved spots*/
        Int_manager_init(&intmgr, 5);

        Int_manager_free(&intmgr);
}
END_TEST

// TODO ADD A FREE FUNCTINO FOR THE COMPONENT MAANGER AS WELL

static Suite *componentmanager_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Component manager");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, componentmanager_test);
        tcase_add_test(tc_core, componentmanager_test2);
        tcase_add_test(tc_core, componentmanager_test3);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
