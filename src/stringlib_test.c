#include <stdio.h>
#include "stringlib.h"


void append_char_test()
{
    string *append_char_test = string_empty();
    string_append_char(append_char_test, '1');
    string_append_char(append_char_test, '2');
    string_append_char(append_char_test, '3');
    string_append_char(append_char_test, '4');
    string_append_char(append_char_test, '5');
    string_append_char(append_char_test, '6');

    string *append_char_test_case = UNSAFE_string_cstring("123456");
    printf("APPEND RESULT: %d\n", string_compare(append_char_test, append_char_test));

    string_free(append_char_test);
    string_free(append_char_test_case);
}

void append_string_test()
{
    string *string_one = UNSAFE_string_cstring("HELLO");
    string *string_two = UNSAFE_string_cstring("WORLD");
    string_append_string(string_one, string_two);
    printf("APPEND_TEST_RESULT: %d\n", string_compare(string_one, UNSAFE_string_cstring("HELLOWORLD")));
}

void prepend_char_test()
{
    string *test = string_empty();
    string_prepend_char(test, 'd');
    string_prepend_char(test, 'o');
    string_prepend_char(test, 'g');
    printf("%d\n", test->length);
    printf("%d\n", test->capacity);
    fwrite(test->buffer, 1, test->length, stdout);
    printf("PREPEND_CHAR_RESULT: %d\n", string_compare(test, UNSAFE_string_cstring("god")));

}

void prepend_string_test()
{
    string *test = string_empty();
    
    string *prepend_string_a = UNSAFE_string_cstring("Hello Bob");
    string *prepend_string_b = UNSAFE_string_cstring("Goodbye Bob");
    
    string *compare = UNSAFE_string_cstring("Goodbye BobHello Bob");

    string_prepend_string(test, prepend_string_a);
    string_prepend_string(test, prepend_string_b);
    
    int result = string_compare(test, compare);
    printf("PREPEND_STRING_RESULT: %d\n", result);

    if (!result)
    {
        string_print(test);
    }
}

int main(int argc, char const *argv[])
{
    append_char_test();
    append_string_test();
    prepend_char_test();
    prepend_string_test();

    return 0;
}


