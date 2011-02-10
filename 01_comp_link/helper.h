/* This file contains the declaration of the function in helper.c */

#ifndef HELPER_H
#define HELPER_H


/* This declaration tells the compiler HOW to call helper(). It says what
   arguments and return type helper() has.
*/
void helper();

#endif /* HELPER_H */


/* In the above file you probably noticed the lines:

   #ifndef HELPER_H
   #define HELPER_H

   #endif

   All headers files have code like this. It prevents the contents
   of the header from being included twice. So if your .c file contains.

   #include "helper.h"
   #include "helper.h"

   Only the first #include does anything.

   The preprossor directive
   #define FOO
   
   makes FOO into a macro that replaces itself with nothing.

   #ifndef means "if macro is not defined."

   #ifndef FOO
   ...
   #endif
   checks to see if the FOO macro has already been defined.
   If FOO is NOT defined, then the code between #ifndef and #endif is emitted
   into the translation unit (the .i file).

   If FOO is defined, then the code between #ifndef and #endif is skipped.
*/
