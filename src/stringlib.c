#include "stringlib.h"
#include <stdlib.h>
#include <stdio.h>

void* safe_copy(void *from_addr, const void *to_addr, size_t length)
{
    // convert void to byte addr representation
    const unsigned char *from_addr_cuc = (unsigned char *) from_addr;
    unsigned char * to_addr_uc = (unsigned char *) to_addr;
    //convert to address to constant void representation

    if (from_addr == to_addr || length == 0)
    {
        return (void*) to_addr;
    }

    // if to_addr is above from_addr + length, forward copy as there is no overlap
    if (to_addr_uc >= from_addr_cuc + length)
    {
        for (size_t i = 0; i < length; i++)
        {
            to_addr_uc[i] = from_addr_cuc[i];
        }
        
    }
    // Otherwise copy in reverse to avoid data overwrite
    else
    {
        for (size_t i = length; i > 0; i--)
        {
            to_addr_uc[i - 1] = from_addr_cuc[i - 1];
        }        
    }

    return (void*) to_addr;
}

string* string_with_capacity(size_t capacity)
{
    string *str = malloc( sizeof(string) );
    if (str == NULL)
    {
        //@TODO: Handle malloc failure;
        return NULL;
    }

    str->buffer = (capacity > 0) ? malloc(sizeof(char) * capacity) : NULL;

    if (str->buffer == NULL)
    {
        // @TODO Handle malloc failure;
        return NULL;
    }

    str->length = 0;
    str->capacity = capacity;
    str->is_owner = 1;
    str->reference_count = 0;
    return str;
}

string* string_empty()
{
    return string_with_capacity(0);
}

string *string_reference(string *parent)
{
    string *new_reference = malloc(sizeof(string));

    new_reference->buffer = parent->buffer;
    new_reference->length = parent->length;
    new_reference->capacity = parent->capacity;

    new_reference->is_owner = 0;
    new_reference->reference_count = 0;

    return new_reference;
}

void string_promote_reference(string *reference)
{
    //@TODO: Make sure owning strings are not being promoted (Warn/assert??)
    if (!reference->is_owner)
    {
        char *new_buffer = malloc(sizeof(char) *reference->capacity);
        safe_copy(reference->buffer, new_buffer, reference->length);
        reference->buffer = new_buffer;
        reference->is_owner = 1;
    }
}

void std_realloc_check(string *str, size_t addition_size)
{
    if (str->capacity <= 0)
    {
        str->buffer = realloc(str->buffer, 100);
        str->capacity = 100;
    }
    else if (str->length + addition_size > str->capacity)
    {
        size_t new_additional_capacity =(sizeof(char) * (str->capacity / 3));
        new_additional_capacity = (new_additional_capacity > addition_size) ? new_additional_capacity : addition_size;

        str->buffer = realloc(str->buffer, str->capacity + new_additional_capacity);
        str->capacity = str->capacity + new_additional_capacity;
    }
}

void string_append_char(string *str, char c)
{
    string_promote_reference(str);
    std_realloc_check(str, 1);

    str->buffer[str->length] = c;
    str->length += 1;
}

void string_append_string(string *to_str, string *from_str)
{
    for (size_t i = 0; i < from_str->length; i++)
    {    
        string_append_char(to_str, from_str->buffer[i]);
    }
}

void string_prepend_char(string *str, char from_char)
{
    string_promote_reference(str);
    std_realloc_check(str, 1);

    safe_copy(str->buffer, str->buffer + 1, str->length);
    str->buffer[0] = from_char;
    str->length += 1;
}

void string_prepend_string(string *to_str, string *from_str)
{
    string_promote_reference(to_str);
    std_realloc_check(to_str, from_str->length);
    
    if (to_str->length <= 0)
    {
        safe_copy(from_str->buffer, to_str->buffer, from_str->length);
    }
    else
    {
        safe_copy(to_str->buffer, to_str->buffer + from_str->length, to_str->length);
        safe_copy(from_str->buffer, to_str->buffer, from_str->length);
    }

    to_str->length += from_str->length;
}

void string_print(string *str)
{
    for (size_t i = 0; i < str->length; i++)
    {
        putc(str->buffer[i], stdout);
    }
}

void string_free(string *str)
{
    if (str->is_owner && str->reference_count > 0)
    {
        //@TODO: Nuke the shit out of the warnings
    }
    free(str->buffer);
    free(str);
    str = NULL;
}

int string_compare(string *str1, string *str2)
{
    if (str1->length != str2->length)
        return 0;
    
    for (size_t i = 0; i < str1->length; i++)
    {
        if (str1->buffer[i] != str2->buffer[i])
            return 0;
    }

    return 1;
}

string* UNSAFE_string_cstring(char* cstring)
{
    size_t string_size = 0;

    while (cstring[string_size] != '\0')
        string_size++;

    string *str = string_with_capacity(string_size);
    str->length = string_size;
    safe_copy(cstring, str->buffer, string_size);
    return str;
}

void UNSAFE_string_append_cstring(char *cstring);

void UNSAFE_string_prepend_cstring(char *cstring);