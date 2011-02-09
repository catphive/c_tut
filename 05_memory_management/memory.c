#include <stdio.h>

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
	  fixed size.
*/

int variable_size_array(int size) {
	/* not particularly portable, probably should't do this. */
	int array[size];
}




int main(int argc, char* argv[]) {
	undefined_behavior();
}
