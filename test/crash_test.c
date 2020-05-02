//!g++ {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_BEFORE_EACH(test_instance, test_name, index,
    if (test_name == "test_one") {
        test_instance->arg = (char*) "Hello World";
    }
)

CESTER_TEST(test_one, test_instance,
    cester_assert_equal(test_instance->arg, "Hello World");
)

CESTER_TEST(test_two, test_instance,
    cester_assert_equal(test_instance->arg, "Yahoo");
)

CESTER_AFTER_EACH(test_instance, test_name, index,
    test_instance->arg = (char*) "Yahoo";
)