#include <stdio.h>

struct record {
    char* name;
    int age;
};

void print_record(struct record rec) {
    printf("%s: %d\n", rec.name, rec.age);
}

void initialize_and_print_record() {
    puts(__func__);
    struct record rec;
    /* rec is undefined!
       print_record(rec); would spit out garbage. */

    rec.name = "Robert Redford";
    rec.age = 42;

    /* now rec's value is defined, and it is safe to use. */
    print_record(rec);
}

/* Typedefs create type aliases. They are just another name for the original
   type, not a new type.

   A typedef of a struct makes it so we don't need to type "struct"
   keyword before creating record_t variables.

   TYPENAME_t means typedef of TYPENAME.
*/

typedef struct record record_t;

/* NOTE: could have just written
    typedef struct {
        char* name;
        int age;
     } record_t;
*/

/* Assigning one struct to another copies elements memberwise.

   Somewhat unusual to copy structs by value in C. In C++ there's mechanisms to
   make this more efficient.
 */

void struct_assignment() {
    puts(__func__);
    record_t rec1;
    rec1.name = "Herbert Hoover";
    rec1.age = 86;
    
    /* copies each element from rec1 */
    record_t rec2 = rec1;

    /* make rec1 and rec2 have different values */
    rec2.age = 26;
}

/* Structs can also be passed to a function by value and returned by value.

   Again, copying is done member by member.
 */

record_t make_record(char* name, int age) {
    record_t rec;
    rec.name = name;
    rec.age = age;
}

void return_struct_by_value() {
    puts(__func__);
    record_t rec = make_record("Franklin D. Roosevelt", 55);
    print_record(rec);
}

/* Sometimes copying member by member is not what you want... especially if the
   struct contains pointers to dynamically allocated memory.

   In C++, you can change the behavior of struct copying to do the right thing.
   However, in C you cannot. Instead, you should make structs you don't want
   copyable opaque to prevent copying.
*/

/* Can initialize a struct with an initializer list.
   Elements in list initialize structure member by member based on order.
 */
void initialize_record_with_initializer_list() {
    puts(__func__);
    record_t rec = {"Warren G. Harding", 34};
    print_record(rec);
}

/* For pointers to structures, there is a special short hand
   syntax to get members.
*/
void print_record_ptr(record_t* rec) {
    /* rec->name is shorthand for (*rec).name */
    printf("%s: %d\n", rec->name, rec->age);
}

void pointer_to_structure() {
    puts(__func__);
    record_t rec = {"Calvin Coolidge", 84};
    print_record_ptr(&rec);
}

int main(int argc, char* argv[]) {
    initialize_and_print_record();
    struct_assignment();
    return_struct_by_value();
    initialize_record_with_initializer_list();
    pointer_to_structure();
}
