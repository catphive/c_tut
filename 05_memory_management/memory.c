#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Important C++ note:
  Virtually everything I teach you how to do in this lesson is WRONG
  if you are programming in C++. C++ has a different mechanism of doing memory
  management called RAII: Resource Aquisition is Initialization.

  This lesson is for C ONLY. In C++ the same code may leak memory due to
  exceptions. However, some concepts carry over (heap and stack).
*/


/* Variables declared in functions are created on the STACK.
 */

void stack_example() {
    /* a variable on the stack */
    int x = 0;
}

/*
   Variables created on the stack have two limitation.
  
   1. They disappear when the function returns. Trying to use a stack variable
      after its function has returned is UNDEFINED BEHAVIOR. Undefined behavior
      is very bad. It usually means your program blows up.

      After a function returns, the space it uses for variables will be reused
      for future function calls. So if you have a pointer to it, you will end up
      pointing to something totally unrelated!

      NOTE: This would be a good time for me to make a diagram of the stack on
      the whiteboard.
*/

int* return_ptr_to_stack_variable() {
    int x = 2;

    /* gcc generates a warning for this... */
    return &x;
}

void unrelated_function() {
    int some_var = 1234;
}

void undefined_behavior() {
    /* ut oh */
    int* x_ptr = return_ptr_to_stack_variable();

    unrelated_function();
    
    /* noooooo! */
    printf("value of %d\n", *x_ptr);
    /* prints 1234!
       Way crazy things can happen when you do this...
     */
}

/*
      So, um, don't return pointers to locals variables. EVER.

   2. Stack variables are of fixed size that must be known at compile time.
*/

int fixed_size_array() {
    /* arrays are created on the stack */
    int array[5] = {1, 2, 3, 4};
}

/*
      Well... that's half the truth...

      You can have variable sized stuff on the stack... in C99 and GNU C and
      GNU C++. 

      But you can't in c89 and standard C++... so pretend stack arrays are
      statically size.
*/

int variable_size_array(int size) {
    /* not particularly portable, probably should't do this. */
    int array[size];
}

/* Aside from the stack memory can be also allocated on the HEAP. This is called
   dynamically allocated memory.

   In C dynamically allocated memory is primarily managed by two functions,
   malloc, and free.

   #include <stdlib.h>

   void *malloc(size_t size);
   void free(void* ptr);

   malloc a pointer to memory of size bytes. When you are done with the memory
   returned by malloc, you must call free on it so that the memory may be
   reused.
*/

void malloc_free_example() {
    /* allocate 1000 bytes */
    void* ptr = malloc(1000);

    if (ptr == NULL) {
        puts("We ran out of memory");
        exit(1);
    }

    free(ptr);
}

/* Every time you allocated memory with malloc, you must remember to free it
   when you are done with the memory. If you fail to free memory you allocated,
   it is called a MEMORY LEAK.
   
   A correct C program should not leak memory. On many systems, you can run out
   of memory if you leak enough.
*/

/* VOID POINTER:
       malloc returns a pointer to void. These are pointers to an unknown
       type. They are not useful in themselves, and must be cast to the
       particular type you want before using them.

       Any other pointer type will automatically convert to a void pointer if
       passed to a function that accepts void pointers like C.

       void pointers are another C construct that usually should not be used in
       C++. In C++ templates make them unnecessary.
*/

void malloc_string() {
    char* string = (char*)malloc(4 * sizeof(char));
    if (string == NULL) {
        puts("Out of memory");
        exit(1);
    }

    string[0] = 'a';
    string[1] = 'b';
    string[2] = 'c';
    string[3] = '\0'; // Must null terminate strings.

    free(string);
}

/* Some new constructs we used above:

   1. sizeof(char)
          sizeof(TYPE) evaluates to the size in bytes of TYPE.
          char's are usually only 1 byte in size.

          Whenever we allocate an array of some type with malloc we use the
          form:
          malloc( num_objects * sizeof(TYPE));

   2. (char*)
          This is a c style cast. Again, this is different in C++...
          (TYPE) value
          forces the compiler to convert value to TYPE.
          In this case we are converting from void* to char*.

   3. size_t
          malloc takes an argument of size_t. size_t is a typedef of whatever
          kind of unsigned integer is large enough on your system to count all
          objects in memory. If you need to keep track of the size of an array,
          you should always use size_t.
          
          size_t and also NULL is included by #include <stddef.h>
*/

/* In C we say the function or object responsible for freeing some memory OWNS
   that memory.

   In fact, ownership is an important concept not just for memory,
   but any resource you must free or close, such as files, threads, and mutices.

   In the above functions, the functions that allocated the memory were also
   responsible for freeing that memory. However, this is not always the case.
*/

typedef struct {
    int age;
    int height; /*in inches*/
} record_t;

/* make_record returns a pointer to a record.
   The caller owns the record, and is responsible for freeing it
*/
record_t* make_record(int age, int height) {
    record_t* rec = (record_t*) malloc(sizeof(record_t));
    if (rec == NULL) {
        puts("Out of memory!");
        exit(1);
    }
    rec->age = age;
    rec->height = height;
    return rec;
}

void gain_ownership_of_record() {
    record_t* bob = make_record(48, 72);
    
    /* make_record returned ownership of bob to us,
       so we are responsible for freeing him.
     */

    free(bob);
}

/* All of this no longer works in C++...
 */

void function_that_fails(record_t* rec) {
    /* pretend this throws an exception*/
}

void fake_exception_example() {
    record_t* bob = make_record(48, 72);
    
    /* pretend this function throws an exception */
    function_that_fails(bob);

    /* we never free bob because control has been transfered to an
       exception handler!
    */
    free(bob);
}

/* To reiterate, because this is really important.

   In C the pattern:

   resource_t* res = make_resource();

   do_stuff();

   free_resource(res);

   is ok and normal. In C++, it is wrong, and there is a better way to free 
   resources. When I see the above pattern in C++ it makes my eyes bulge, and
   steam come out of my ears.
*/

int main(int argc, char* argv[]) {
    undefined_behavior();
}
