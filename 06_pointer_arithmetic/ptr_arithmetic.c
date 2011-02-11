#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Pointers are a kind of ITERATOR. That means they can be used to move over
   a collection of objects, specifically, an array.

   The syntax for moving a pointer among the elements of an array is called
   pointer arithmetic. It is so called because we use the arithmetical operators
   on a pointer to move over it:

   ptr + num;
   ptr - num;
   ++ptr;
   --ptr;
   ptr++;
   ptr--;
   ptr1 - ptr2;
 */

/* a quick helper function to write a single char on its own line */
void put_char(char ch) {
    printf("%c\n", ch);
}

void basic_ptr_arithmetic() {
    puts(__func__);
    /* string is a pointer to the first char in an array */
    const char* char_ptr = "A string";

    /* Right now char_ptr points at the character A. */
    put_char(*char_ptr);

    /* We can move to the next char by incrementing the pointer like we
       would increment an integer.

       Here we increment twice, so that char_ptr points to 's'
    */
    ++char_ptr;
    ++char_ptr;
    put_char(*char_ptr);

    /* We can use the + operator as well if we don't want to modify the original
       pointer.

       This prints out 'g'.
    */
    put_char(*(char_ptr + 5));

    /* We can also move the pointer backwards over the string to its original
       position */

    char_ptr = char_ptr - 2;
    put_char(*char_ptr);


    /* If you move outside the bounds of your array, C will not stop you!
       However, this will cause undefined behavior. Usually, you will get
       garbage values. Sometimes you may cause a crash if you do this.*/

    --char_ptr; /* move to position *before* beginning of array */

    put_char(*char_ptr); /* undefined behavior! */
}

/* Pointer arithmetic is done in terms of elements not bytes. For instance,
   integers usually take 4 or 8 bytes of space. However, when moving among
   an array of pointers with pionter arithmetic, you don't have to think about
   what size they are. */

void put_int(int num) {
    printf("%d\n", num);
}

void int_ptr_arithmetic() {
    puts(__func__);
    int int_array[] = {0, 1, 2, 3, 4, 5};
    int* int_ptr = int_array; /* arrays automatically convert to pointers */

    /* We move forward two elements, and print the number 2 */
    int_ptr = int_ptr + 2;
    put_int(*int_ptr);

    /* Since int_ptr + 2 moves int_ptr by two elements, this works */
}

/* Pointers can be used to define a slice of an array.

   There are two ways to slice an array:

   C style: Use a pointer and an integer. The integer counts the number of elements in
            the slice.

   C++ style: Use two pointers. The first pointer points to the beginning of the
              slice, and the second points just past the end.

   Since I'm going to segue into C++ in the next lesson, I'll show you c++ style
   slicing to get a head start.

   Lets say I have a string "foo bar"

   A slice of that string pointing to just "foo" looks like this

   ------------------
   |f|o|o| |b|a|r|\0|
   ------------------
    ^     ^
    p1    p2

    p1 points the the beginning of the slice, which you might expect.
    p2 points to the element just after the end of the slice. This might seem nonintuitive
    at first, but will make sense with practice.

    An empty slice is any slice for which both pointers point to the same location.

    ------------------
    |f|o|o| |b|a|r|\0|
    ------------------
       ^
       p1
       ^
       p2

    Both pointers of the slice point to the same position, so the slice is emtpy.
*/

/* lets define some functions that work with slices! */

void capitalize_chars(char* begin, char* end) {
    for(; begin != end; ++begin) {
        *begin = toupper(*begin);
    }
}

/* find_char returns a pointer to the first character that matches ch.
   If none match ch, it returns end.
*/
char* find_char(char* begin, char* end, char ch) {
    for(; begin != end && *begin != ch; ++begin);
    return begin;
}

void demonstrate_slicing() {
    puts(__func__);
    char string[] = "foo bar spam eggs";

    /* lets define a slice that contains the entire string. */
    char* begin = string;
    char* end = string + strlen(string);

    /* lets verify this string does not contain the character 'z' */
    if (find_char(begin, end, 'z') == end)
        puts("z not found");
    else
        puts("z found!");

    /* lets capitalize bar */
    char* bar_begin = find_char(begin, end, 'b');
    capitalize_chars(bar_begin, find_char(bar_begin, end, ' '));

    puts(string);

    /* note that even if either 'b' and ' ' aren't present, this wont' explode.
       If 'b' was missing, the slice we capitalized would have been of zero size.
       If 'b' existed, but ' ' wasn't found after it, we would just have capitalized
       until the end of the list.

       This is why find_char returns end instead of NULL if the char isn't found.
       We don't need to have any if statements to check error conditions.
    */
}

int main(int argc, char* argv[]) {
    basic_ptr_arithmetic();
    int_ptr_arithmetic();
    demonstrate_slicing();
}
