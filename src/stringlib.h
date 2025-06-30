#ifndef STRINGLIB_H
#define STRINGLIB_H
#include <ctype.h>

typedef struct STRING string;

//
struct STRING
{
    unsigned char is_owner;
    int reference_count;

    size_t length;
    size_t capacity;
    char *buffer;
};


string *string_empty();

string *string_with_capacity(size_t capacity);

string *string_reference(string *parent);

void string_promote_reference(string *reference);

// #### STRING WRITE
void string_append_char(string *str, char c);

void string_append_string(string *to_str, string *from_str);

void string_prepend_char(string *to_str, char from_char);

void string_prepend_string(string *to_str, string *from_str);

// #### STRING WRITE

// #### STRING UTILS
void* safe_copy(void *from_addr, const void *to_addr, size_t length);

string* string_substring(string *from_str, size_t start, size_t end);

int string_index_of(string *target, char look_for);

int string_compare(string *str1, string *str2);

void string_print(string *str);

void string_free(string *str);
// #### STRING UTILS

// #### UNSAFE
string* UNSAFE_string_cstring(char* cstring);

void UNSAFE_string_append_cstring(char *cstring);

void UNSAFE_string_prepend_cstring(char *cstring);
// #### UNSAFE


#endif