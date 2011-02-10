/*
  C has a pipeline that starts with the .c and .h files, and ends with an
  executable program. What follows is a fairly in depth explanation of the C
  compilation pipeline, with maybe more info than you really need.

  1. The C preprocessor (called cpp on unix) takes in main.c and helper.h and
     generates the translation unit main.i.
  
     main.i is the actual C language document. Preprocessor directives such as
     #include are part of the preprocessor language, not the C language proper.

  2. main.i is passed to the C compiler (gcc). The C compiler generates assembly
     for your particular processor, usually X86 or x86_64. The output assembly
     file is called main.s

  3. main.s is passed to the assembler (gas) which generates machine language.
     This machine language code is what the processor actually reads. It is
     stored in the file main.o

  4. All other files ending in .c, such as helper.c, go through the same
     pipeline.

  5. All .o files, in this case main.o and helper.o, are combined by the linker.
     The linker basically packs them into an indexed archive. This is the actual
     program file that you run, called a binary or executable. In this case
     the name of the output file is "test"

     NOTE: executables do not end in .exe on Linux. That is only for windows.

     Normally the GCC program does many of these steps automatically for you,
     and deletes the intemediary files like main.i and main.s. Behind the scenes
     GCC is always running cpp, gas, and ld.
     
     For educational purposes I pass the -save-temps flag
     to GCC, which tells it to not delete .i and .s files. Take a look at them.
     Unless you know assembly, you may not understand the .s files, but you
     should be able to understand at least main.i.

     The format of the .o files and the executable itself is an even more
     advanced topic. Usually you do not need to worry about it, but rather
     think in terms of the source (.c) files and translation units.
     See: Executable and Linking Format (ELF)
 */


#include "helper.h"
/* The above #include directive tells the preprocessor cpp to process
   helper.h, and add its contents to main.i.

   This is necessary because helper.h has the declaration of a function we want
   to call. Before you can call a function, it must be either declared or
   defined.

   Technically, declarations could just be repeated in each .c file like this:

   void helper();

   However, it is usually easier to organize declarations common between files
   in .h HEADER FILES. Then, every file that needs the same declations can
   simply #include the header.
*/

int main(int argc, char* argv[]) {

    /* We can call helper here, even though it is not defined, only declared,
       in this translation unit.
       
       When main.o and helper.o are combined by the linker, the linker will look
       up the defintion of helper() in helper.o, and point this function call at
       it.
    */
    helper();

    /* In C, the main function should end with a return statement.
       Return 0 indicates the program succeeded. Returning any other
       integer indicates failure.

       In C++, this is not necessary. Return 0 is implied in C++.
    */
    return 0;
}
