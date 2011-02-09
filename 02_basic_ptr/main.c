#include "stdio.h"
#include "stddef.h"

/* Pointers store the address of another variable.*/

void basic_pointer_use() {
    /* Always initialize variables, or they have undefined "garbage" values. */
    int x = 0;

    /* Given a variable x, we can obtain a pointer to x using the "address of"
       operator: &

       For any variable of type T, the type of the pointer to T is T*
    */

    int* ptr = &x;

    /* Given a pointer ptr, we can obtain the variable it points to
       to with the "dereference" operator: *
       
       NOTE: *var means dereference, but var1 * var2 mean multiplication.
    */

    int y = *ptr; /* copies x to y */
}

/* In C, pointers are the only way to modify a variable not in the current
   scope.
*/

void print_val(int val) {
    printf("val: %d\n", val);
}

void incr(int* int_ptr) {
    ++*int_ptr;
}

void bad_incr(int val) {
    ++val;
}

void use_pointers_to_pass_by_reference() {
    int val = 0;
    
    print_val(val);
    incr(&val);
    print_val(val);

    /* bad_incr does nothing to our val because passed by value. */
    bad_incr(val);
    print_val(val);
}

/* Pointers can have a special NULL state.
   NULL is just a macro that expands to 0.
   No object can be located at address 0 on most hardware, so 0 indicates that
   a pointer points to nothing.

   The NULL macro is included with:
   #include <stddef.h>

   Be very careful that you do not dereference a null pointer with *
   If you try to access the contents of address zero, the operating system
   will usually kill your program.
*/

void dereference_null_ptr() {
    int* null_ptr = NULL;

    /* This will crash your program with a segfault */
    *null_ptr = 10;
}

/* NULL is used if a parameter to a function is optional.

   In the example bellow, the error message is optional, and a default error
   message is printed if NULL is passed.
*/

void print_error_msg(char* msg) {
    if (msg == NULL) 
        msg = "An error has occured\n";

    fputs(msg, stderr);
}

void using_optional_parameters() {
    /* print the default error message */
    print_error_msg(NULL);

    /* print a non-default error message */
    print_error_msg("A very strange error has occured\n");
}

/* In C, the compiler will always let you assign NULL to any pointer.
   
   However, most functions that accept pointers as arguments do not intend
   for their arguments to be optional. They usually do not check for NULL,
   thus passing NULL to most functions will cause a crash.

   Only pass NULL to a function if the documentation for that function
   explicitly says that NULL may be passed.
*/
void not_all_pointer_arguments_are_optional() {
    puts(NULL);
}

/*
  Editorial On NULL:
  
   Avoid overusing NULL. Most of the time pointers do not need or want an
   extra NULL state. If you ever set a pointer to NULL, then you need to check
   for null later when you try to use it. This adds clutter to your code.
   
   In C++ there are REFERENCES. These can be used to pass arguments by
   reference, like a pointer, but are simpler. They have no NULL state,
   and so make NULL checks unnessary.
*/

int main(int argc, char* argv[]) {
    use_pointers_to_pass_by_reference();

    /* uncomment the line below to cause a segfault */
    /* dereference_null_ptr(); */

    using_optional_parameters();

    /* uncomment the line below to cause a segfault */
    /* not_all_pointer_arguments_are_optional(); */

    return 0;
}
