#include "stdio.h"

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

int main(int argc, char* argv[]) {
	use_pointers_to_pass_by_reference();

	return 0;
}
