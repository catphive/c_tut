#include <stddef.h>

/* Variables in C can be marked constant.
   Constant variables cannot be modified. */

void constant_values() {
    int const x = 0;
    /* Cannot modify x.
       x = 1; would fail to compile */
}

/* Constant values are not often used in C. However, pointers to constant values
   are used often. */

void pointer_to_const() {
    char const * const_string = "You cannot change this string";
    
    /* Note that const applies to the type to the LEFT.
       const_string is a non-const pointer to constant chars.
       We CAN modify the pointer itself.*/
    const_string = "Now pointing to a different constant string";

    /* This will not compile! It is the chars that are const.
        *const_string = 'A';
     */

    /* This is a const pointer to a const char */
    char const * const const_ptr_to_const_string = "Double const!";

    /* You usually want to make what you are pointing at constant.
       Making pointers themselves const is fairly pointless. */
}

/* You can go from pointer to non-const to pointer to const,
   but not backwards. */
void nonconst_to_const() {
    int x = 0;
    int* ptr_to_x = &x;
    int const * const_ptr_to_x = ptr_to_x;

    /* This would fail to compile
       ptr_to_x = const_ptr_to_x;
    */
}

/* Functions that are passed a pointer to something they read but do not
   write to, should take pointers to const. */

int string_length(char const * string) {
    int count = 0;
    for (; *string; ++string, ++count);
    return count;
}

void using_string_length() {
    char string[] = "testing.";
    /* string is modifiable. */
    string[7] = '!';

    /* Since string_length takes a pointer to const,
       we know it does not modify it. */
    string_length(string);
}

/* These types are the same:
   char const * string;
   const char * string;

   The second form is used more in practice.
*/

void alternative_syntax(const char* buffer) {
}

/* TAKEAWAY:

   0. Read pointer and const expresions right to left.

      char const *

      Reads: pointer to const char.

   1. Do not confuse pointers to const with const pointers.

      Pointers to const (both mean the same thing):
          const char*
          char const *

      const pointer (rarely used in practice):
          char * const

      const pointer to const (also rare):
          char const * const
          const char * const

      Confusingly, pointers to const are often refered to as const pointers in
      casual conversation. Real const pointers are so rare that sometimes
      C programmers do not remember the distinction.

      This distinction comes up again when dealing with C++ smart pointers.

   2. If a function does not modify the target of a pointer, it should accept a
      pointer to const.
     
      e.g. string_length(string) does not modify the string, so it should take a
      pointer to const.
*/

/* Complicated Example:

   C allows pointers to pointers.
   Also, pointers to pointers to pointers.
   Also, pointers to pointers to pointers to pointers.
   ...

   Each level may be const.
*/

void pointers_to_pointers_to_etc() {
    int x = 0;
    int* ptr_to_x = &x;
    int** ptr_to_ptr_to_x = &ptr_to_x;
    int*** ptr_to_ptr_to_ptr_to_x = &ptr_to_ptr_to_x;

    /* Each level may be const!
     */

    int const * const * const * const lotsa_const = NULL;

    /* Read that type RIGHT TO LEFT:
       
       const pointer to const pointer to const pointer to const int.
     */
}

/* In C sometimes you really do need double and triple pointers.
   However, almost never in C++!
   One more reason to use C++ instead of C.
*/

int main(int argc, char* argv[]) {
    constant_values();
    pointer_to_const();
    nonconst_to_const();
}
