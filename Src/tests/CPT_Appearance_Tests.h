#include <SDL2/SDL.h>
#include <check.h>
#include <stdbool.h>
#include "Src/Engine/Components/Appearance.h"

// tests if the rects are equal
bool SDL_rectEquals(const SDL_Rect rect1, const SDL_Rect rect2);
bool SDL_rectEquals(const SDL_Rect rect1, const SDL_Rect rect2) {
        return (rect1.x == rect2.x) && (rect1.y == rect2.y) &&
               (rect1.w == rect2.w) && (rect1.h == rect2.h);
}

// TODO WRITE THESE UNIT TESTS

START_TEST(modifySdlRectPosition_test) {
        SDL_Rect rect = (SDL_Rect){.x = 0, .y = 0, .w = 1, .h = 1};
        ck_assert_msg(
            SDL_rectEquals(rect, (SDL_Rect){.x = 0, .y = 0, .w = 1, .h = 1}),
            "error in rectEquals function");

        // moving the position
        ck_assert_msg(
            SDL_rectEquals(rect, (SDL_Rect){.x = 0, .y = 0, .w = 1, .h = 1}),
            "error in rectEquals function");
}
END_TEST

static Suite *appearances_test_suite(void) {
        Suite *s;
        TCase *tc_core;

        s = suite_create("Appearances test suite");

        // core test case
        tc_core = tcase_create("Core");

        // ADD MORE CASES TO TC_CORE HERE
        tcase_add_test(tc_core, modifySdlRectPosition_test);

        suite_add_tcase(s, tc_core);

        return s;
}
