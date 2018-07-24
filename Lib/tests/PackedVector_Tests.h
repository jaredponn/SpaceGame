#include <check.h>
#include <stdint.h>
#include "Data_Structures.h"

// testing the add function
START_TEST(packedvector_test) {
        struct intPackedVector pkdvec;
        /* initilizes an empty int packedvector with 10 reserved spots*/
        intPackedVector_init(&pkdvec, 10);

        /* check to see if there was a proper initiliaziatoin */
        // sparse_vector should have a size and capacity of 10 and should be
        // filled with SIZE_MAX
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 10);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 10);
        for (size_t i = 0; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // global_indicies, and data should have a size of 0, and capacity of 10
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 0);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 0);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // the next_packed_index should be 0
        ck_assert_int_eq(pkdvec.next_packed_index, 0);

        /* Adding an int of value 0 at index 0.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, .. SIZE_MAX ]
         * packed_indices: [0]
         * data: [0]
         */
        // at index 0, add value 0 to the array
        intPackedVector_add_at(&pkdvec, 0, &(int){0});

        // checking the size / capacity of sparse_vector. SHould still be 10
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 10);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 10);

        // checking the size / capacity of global_indicies and data. Size should
        // be 1, and capacity should still be 10
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 1);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 1);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the indices of the sparse_array. index 0 should be 0, and the
        // rest should be SIZE_MAX
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), 0);
        for (size_t i = 1; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check value of index 0 of packed_indices and data. Both should be 0
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 0);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 0);

        ck_assert_int_eq(pkdvec.next_packed_index, 1);
        /* Adding an int of value 7 at index 3.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX ]
         * packed_indices: [0,3]
         * data: [0,7]
         */
        // at index 3, add value 7 to the array
        int tmp1 = 7;
        intPackedVector_add_at(&pkdvec, 3, &tmp1);

        // checking the size / capacity of sparse_vector. should still be 10
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 10);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 10);

        // checking the size / capacity of global_indicies and data. Size should
        // be 1, and capacity should still be 10
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 2);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 2);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 3), 1);
        for (size_t i = 4; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check indices packed_indices and data.
        // packed_indices: [0,3]
        // data: [0,7]
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 1), 3);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 0);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 1), 7);

        ck_assert_int_eq(pkdvec.next_packed_index, 2);
        // clang-format off
        /* Adding an int of value 4 at index 10.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 4, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        // at index 10, add value 4 to the array
        int tmp2 = 4;
        intPackedVector_add_at(&pkdvec, 10, &tmp2);

        // checking the size / capacity of sparse_vector. Should change to 15,
        // because 10 is too small
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 3);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 3);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 3), 1);
        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 10), 2);
        for (size_t i = 11; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1,2 for packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 1), 3);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 2), 10);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 0);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 1), 7);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 2), 4);

        ck_assert_int_eq(pkdvec.next_packed_index, 3);
        // clang-format off
        /* Adding an int of value 4 at index 0 Nothing should occur.
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 4, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        // at index 0, add value 4 to the array
        int tmp3 = 4;
        intPackedVector_add_at(&pkdvec, 0, &tmp3);

        // checking the size / capacity of sparse_vector. Should change to 15,
        // because 10 is too small
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 3);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 3);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the indices of the sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1,
        // SIZE_MAX .. SIZE_MAX ]
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 2), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 3), 1);
        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 10), 2);
        for (size_t i = 11; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1,2 for packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 1), 3);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 2), 10);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 0);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 1), 7);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 2), 4);

        ck_assert_int_eq(pkdvec.next_packed_index, 3);

        intPackedVector_free(&pkdvec);
}
END_TEST

// testing the delete function
START_TEST(packedvector_test2) {
        struct intPackedVector pkdvec;
        intPackedVector_init(&pkdvec, 10);

        // clang-format off
        /* Recreating the same manager from the add test
         * The arrays should be as follows:
         * sparse_vector: [0, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 2, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [0,3,10] 
         * data: [0,7,4]
         */
        // clang-format on
        int tmp0 = 0;
        int tmp1 = 7;
        int tmp2 = 4;
        int tmp3 = 4;
        intPackedVector_add_at(&pkdvec, 0, &tmp0);
        intPackedVector_add_at(&pkdvec, 3, &tmp1);
        intPackedVector_add_at(&pkdvec, 10, &tmp2);
        intPackedVector_add_at(&pkdvec, 0, &tmp3);

        // clang-format off
        /* Deleting index 0
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, 1, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [10, 3] 
         * data: [4, 7]
         */
        // clang-format on
        // at index 0, delete the value
        intPackedVector_remove_at(&pkdvec, 0);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 2);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 2);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the values of the sparse_vector
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 1), SIZE_MAX);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 2), SIZE_MAX);

        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 3), 1);

        for (size_t i = 4; i < 10; ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 10), 0);
        for (size_t i = 11; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 10);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 1), 3);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 4);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 1), 7);

        ck_assert_int_eq(pkdvec.next_packed_index, 2);

        // clang-format off
        /* Deleting index 3
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value
        intPackedVector_remove_at(&pkdvec, 3);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 1);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 1);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < 10; ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 10), 0);
        for (size_t i = 11; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 10);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 4);

        ck_assert_int_eq(pkdvec.next_packed_index, 1);

        // clang-format off
        /* Deleting an already deleted index like 0
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value
        intPackedVector_remove_at(&pkdvec, 0);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 1);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 1);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < 10; ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 10), 0);
        for (size_t i = 11; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        // check the values of indices 0,1 for packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 10);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 4);

        ck_assert_int_eq(pkdvec.next_packed_index, 1);

        // clang-format off
        /* Deleting the last element at index 10
         * The arrays should change to be be as follows:
         * sparse_vector: [SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX .. SIZE_MAX, 0, SIZE_MAX .. SIZE_MAX ] 
         * packed_indices: [10] 
         * data: [4]
         */
        // clang-format on
        // at index 0, delete the value

        intPackedVector_remove_at(&pkdvec, 10);

        // checking the size / capacity of sparse_vector. Should remain as 15
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 15);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 15);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 0);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 10);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 0);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 10);

        // check the values of the sparse_vector
        for (size_t i = 0; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, i),
                                 SIZE_MAX);
        }

        ck_assert_int_eq(pkdvec.next_packed_index, 0);

        // freeing the vectors
        intPackedVector_free(&pkdvec);
}
END_TEST

START_TEST(packedvector_test3) {
        struct intPackedVector pkdvec;
        /* initilizes an empty int packedvector with 5 reserved spots*/
        intPackedVector_init(&pkdvec, 5);

        // clang-format off
        /* Fill the index as follows:
         * sparse_vector: [0, 1, 2, 3, 4] 
         * packed_indices: [0, 1, 2, 3, 4]
         * data: [3,9,2,12,9]
         */
        int tmp0 = 3;
        int tmp1 = 9;
        int tmp2 = 2;
        int tmp3 = 12;
        int tmp4 = 9;
        // clang-format on
        intPackedVector_add_at(&pkdvec, 0, &tmp0);
        intPackedVector_add_at(&pkdvec, 1, &tmp1);
        intPackedVector_add_at(&pkdvec, 2, &tmp2);
        intPackedVector_add_at(&pkdvec, 3, &tmp3);
        intPackedVector_add_at(&pkdvec, 4, &tmp4);

        // checking the get_p_at function when in bounds
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 0), 3);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 1), 9);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 2), 2);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 3), 12);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 4), 9);

        // checking the get_p_at function when out of bounds
        ck_assert_msg(intPackedVector_get_p_at(&pkdvec, 5) == NULL,
                      "failed to recognize out of bounds error");
        ck_assert_msg(intPackedVector_get_p_at(&pkdvec, 100) == NULL,
                      "failed to recognize out of bounds error");

        // deleting an index
        // clang-format off
        /* Fill the index as follows:
         * sparse_vector: [0, 1, SIZE_MAX, 3, 2] 
         * packed_indices: [0, 1, 4, 3]
         * data: [3,9,9,12]
         */
        // clang-format on
        intPackedVector_remove_at(&pkdvec, 2);

        // testing if everything is good still
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 0), 3);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 1), 9);
        ck_assert_msg(intPackedVector_get_p_at(&pkdvec, 2) == NULL,
                      "failed to recognize deleted element");
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 3), 12);
        ck_assert_int_eq(*intPackedVector_get_p_at(&pkdvec, 4), 9);

        intPackedVector_free(&pkdvec);
}
END_TEST
// testing adding and deletion
START_TEST(packedvector_test4) {
        struct intPackedVector pkdvec;
        /* initilizes an empty int packedvector with 5 reserved spots*/
        intPackedVector_init(&pkdvec, 5);

        // clang-format off
        /* Fill the index as follows:
         * sparse_vector: [0, 1, 2, 3, 4] 
         * packed_indices: [0, 1, 2, 3, 4]
         * data: [0,1,2,3,4]
         */
        // clang-format on
        int tmp;
        for (size_t i = 0; i < SizetVector_size(&pkdvec.sparse_vector); ++i) {
                tmp = (int)i;
                intPackedVector_add_at(&pkdvec, i, &tmp);
        }
        // checking the size / capacity of sparse_vector.
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 5);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 5);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 5);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 5);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 5);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 5);

        // clang-format off
        /* deleting index 2, and at index 2 add value 7
         * sparse_vector: [0, 1, 4, 3, 2] 
         * packed_indices: [0, 1, 4, 3, 2]
         * data: [0,1,4,3,7]
         */
        // clang-format on
        int tmp1 = 7;
        intPackedVector_remove_at(&pkdvec, 2);
        intPackedVector_add_at(&pkdvec, 2, &tmp1);

        // checking the size / capacity of sparse_vector.
        ck_assert_int_eq(SizetVector_size(&pkdvec.sparse_vector), 5);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.sparse_vector), 5);

        // checking the size / capacity of global_indicies and data.
        ck_assert_int_eq(SizetVector_size(&pkdvec.packed_indices), 5);
        ck_assert_int_eq(SizetVector_capacity(&pkdvec.packed_indices), 5);
        ck_assert_int_eq(intVector_size(&pkdvec.packed_data), 5);
        ck_assert_int_eq(intVector_capacity(&pkdvec.packed_data), 5);

        // checking the values of the sparse_vector
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 1), 1);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 2), 4);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 3), 3);
        ck_assert_int_eq(SizetVector_get(&pkdvec.sparse_vector, 4), 2);

        // checking the values of the packed_indices and data
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 0), 0);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 0), 0);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 1), 1);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 1), 1);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 2), 4);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 2), 4);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 3), 3);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 3), 3);
        ck_assert_int_eq(SizetVector_get(&pkdvec.packed_indices, 4), 2);
        ck_assert_int_eq(intVector_get(&pkdvec.packed_data, 4), 7);

        intPackedVector_free(&pkdvec);
}
END_TEST

// TODO ADD A FREE FUNCTINO FOR THE COMPONENT MAANGER AS WELL

static Suite *packedvector_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Packed Vector");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, packedvector_test);
        tcase_add_test(tc_core, packedvector_test2);
        tcase_add_test(tc_core, packedvector_test3);
        tcase_add_test(tc_core, packedvector_test4);
        // tcase_add_test(tc_core, stack_test);

        suite_add_tcase(s, tc_core);

        return s;
}
