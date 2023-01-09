/*
 *	Made by Noah Van Miert
 *	12/12/2022
*/

#include "string.h"


/*
    strlen() - Returns the length of
    a null-terminated string.
*/
size_t strlen(const char *str)
{
    size_t size;
    for (size = 0; str[size] != '\0'; size++);
    return size;
}
