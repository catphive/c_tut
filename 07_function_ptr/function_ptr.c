/* 
   Almost all language provide some means of putting a function in a variable,
   and passing it as an argument to other functions. This is possible even in
   assembly. In fact, the only language that cannot do this that I know of
   are pure OO languages like Java.

   Functions that take functions as arguments are called higher order functions.
   As we shall see, they are rediculously useful.

   C's support for higher order functions is very minimalistic, but serviceable.
   C has function pointers. Function pointers are like other pointers, except
   that instead of pointing to a variable they point to the first instruction of
   a function.
*/

#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

void some_function() {
    puts("some_function() called");
}

void put_a_function_in_a_variable() {
    puts(__func__);

    /* The syntax for declaring a function pointer is a little gnarly
       This is a pointer to a function that returns void and has zero
       arguments*/
    
    void (*func_ptr)() = NULL;

    /* We can assign some_function to this variable like so */
    func_ptr = &some_function;

    /* The & operator is optional when taking the address of a function.
     This does the same thing. as above
    */
    func_ptr = some_function;

    /* Now we can derefence the function pointer and call it like like a normal
       function */
    (*func_ptr)();
    
    /* Again, dereferencing the function pointer is optional. */
    func_ptr();

    /* Usually I do not bother with the & and * operators when dealing with
       function pointers.
    */
}

/* Lets show an example of how you can use function pointers to store an
   equation in a struct.
*/

int mult(int x, int y) {
    return x * y;
}

int div(int x, int y) {
    return x / y;
}

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}


/* wasn't the syntax for declaring function pointer variables a little
   awkward? The way to make weird looking types more readable in c and c++
   is the typedef.
   
   We can give "pointer to function that takes two ints and returns an int"
   another name.
*/

typedef int (*operation_ptr)(int, int);

/* Now we can define a struct that has all the information we need about a
   simple arithmetical expression.

   This struct is fairly small, so we will just pass it around by value.
*/

typedef struct {
    int left_operand;
    int right_operand;
    operation_ptr operator;
} expression_t;

/* and a function that given an expression, can evaluate it.
   Note it is const, because we don't modify exp.*/
int eval_expression(expression_t exp) {
    return exp.operator(exp.left_operand, exp.right_operand);
}

/* a function to map mathematical symbols * / + - to functions */
operation_ptr math_symbol_to_func(char op_code) {
    switch(op_code) {
        case '*':
            return mult;
        case '/':
            return div;
        case '+':
            return add;
        case '-':
            return  sub;
        default:
            return add;
    }
}


/* and a function that reads an expression from the user.
*/

expression_t read_expression() {
    /* Set defaults in case scanf fails */
    expression_t exp = {0, 0, add};
    char op_code = '*';
    while(scanf("%d %c %d",
                &exp.left_operand, &op_code, &exp.right_operand) != 3) {
        /* This is really limited error checking. Just checks that 3 items
           matched */
        puts("Bad input. Must be of format NUMBER OPERATOR NUMBER");
    }

    exp.operator = math_symbol_to_func(op_code);
    
    return exp;
}


void use_expressions() {
    puts(__func__);
    /*OK! Now we have functions to read expressions from the user, and to
      evaluate them.
    */

    puts("An expression of the form NUMBER OPERATOR NUMBER");

    printf("Result %d\n", eval_expression(read_expression()));
}


/*
  HIGHER ORDER FUNCTIONS:

  Functions that take other functions as arguments are called higher order
  functions.

  If you have an algorithm that you want to customize for a given situation,
  you can make it take functions as arguments to change its behavior.
  
  In the last lesson we had a function called char_find that I will duplicate
  here.
 */

char* find_char(char* begin, char* end, char ch) {
    for(; begin != end && *begin != ch; ++begin);
    return begin;
}

/* find_char can find the first char ch. But what if you want to find a certain
   KIND of char? What if you want to find the first upper case char? Or the
   first number? Or the first whitespac char (including tabs and spaces)?
   
   We need a version of this function we can customize with our own matching
   function.
   
   For this we will use a PREDICATE. A predicate is a kind of function that has
   these properties:
   1. It returns true or false.
   2. It is REFERENTIALLY TRANSPARENT.
   
      Referential transparency is just a fancy term that means a function always
      returns the same result for the same argument passed in.
      
      For instance, lets say we have a predicate function p, and some value x.

      Then p(x) should always have the same result no matter when, or how many
      times you call it.
      
      A predicate p(x) that takes one argument is called unary. A predicate
      p(x, y) that takes two arguments is called binary.

      NOTE: in C we use integers for TRUE and FALSE. In C++ there is a special
      bool type.

      Also, c prevides a bunch of predicates for chars that we will reuse.
      However, for historical reasons, they take int as arguments.
*/

typedef int (*unary_pred)(int);

/* Now lets make our customizeable find function.

   Instead of stopping when we match the char ch, we stop on the char for which
   is_found returns true.
 */

char* find_char_if(char* begin, char* end, unary_pred is_found) {
    for(; begin != end && !is_found(*begin); ++begin);
    return begin;
}

/* Now we can reuse the character predicates found in ctype.h.

   For details:
   man isalnum
*/

void using_find_char_if() {
    puts(__func__);

    char string[] = "A string full of words and 1 number.";

    puts(string);

    /* form a slice */
    char* begin = string;
    char* end = string + strlen(string);

    /* now we can find characters based on a variety of criterial */
    printf("Found first digit: %c\n", *find_char_if(begin, end, isdigit));
    printf("Found first upper case: %c\n", *find_char_if(begin, end, isupper));
    printf("Found first punctuation: %c\n", *find_char_if(begin, end, ispunct));
}

/* Not all higher order functions need to take predicates as arguments.
   
   unary_func is *not* a predicate because it does not return true or false.
   It may also not be referentially transparent.
 */

typedef void (*unary_func)(char* char_ptr);

void for_each_char(char* begin, char* end, unary_func func) {
    for(; begin != end; ++begin)
        func(begin);
}

/* To use for_each_char we must have a function ready to pass to it. Lets write
   a function that capitalizes a char.
*/

void cap_char(char* char_ptr) {
    *char_ptr = toupper(*char_ptr);
}

/* Now we can rewrite the capitalize_chars function from the last lesson using
   for_each_char
*/

void capitalize_chars(char* begin, char* end) {
    for_each_char(begin, end, cap_char);
}

/* Now we can rewrite our example from last time that demonstrated slicing
   using higher order functions */

void capitalize_word_in_string() {
    puts(__func__);

    /* This string actually has a tab between bar and spam */
    char string[] = "foo bar\tspam eggs";

    char* begin = string;
    char* end = string + strlen(string);

    /* find the start of bar with the old version of find_char */
    char* bar_begin = find_char(begin, end, 'b');
    
    /* using find_char_if we find the end of bar by searching for any kind
       of whitespace. Then we capitalize it.
    */
    capitalize_chars(bar_begin, find_char_if(bar_begin, end, isspace));

    puts(string);
}

/* Higher order functions make algorithms much more flexible!

   However... in C there are some limitations!
   
   1. When I write for_each_char, it's annoying to have to define a seperate
      function elsewhere in the file. It would be nice to be able to define
      the function right where it's called with something like this:

         for_each_char(begin, end, function(char* ptr){ *ptr = toupper(*ptr); })

      Also, what if I want to use for_each_char to count the number of chars?
      If would be nice if I could use the above made up syntax to increment a
      local variable.

         int count = 0;
         for_each_char(begin, end, function(char* ptr){ ++count; })

      This is called a LAMBDA. C++0x has these, but with different syntax.
      
      Standard C doesn't let you do this, although some compilers support
      it as an extension. GNU C has nested functions, which are similar.

      Most modern languages, such as python, javascript, and C# have lambas.

   2. for_each_char and find_char_if only work with chars, even though if you
      look at their definition you wouldn't really need to change much to make
      it work with another type like int.

      Wouldn't it be nice if you could define a whole family of functions at
      once, that work with every type? Say you could define a generic pattern
      for all for_each_*** function, and let the compiler make the specific
      one you need for a given cicumstance?

      Something like:
      
          (for every type T)
          char* find_T_if(T* begin, T* end, unary_pred is_found) {
              for(; begin != end && !is_found(*begin); ++begin);
              return begin;
          }
      
      You can do this in C++, and it is called a FUNCTION TEMPLATE.
      
      In C, you can you can kindasorta hack this together with either
      void pointers, or macros, but it is very ugly. Also, hacky solutions
      in C using void pointers are not as fast as c++ templates.

      C comes with a generic quicksort algorithm called qsort. It uses void
      pointers, and is not that easy to use.
      
      By comparison, c++ has a sort function that uses templates and is both
      eaiser to use and more efficient.

   Hopefully you've learned something new about C, and are also motivated to
   lean more about C++ and C++0x.
*/

int main(int argc, char* argv[]) {
    put_a_function_in_a_variable();
    use_expressions();
    using_find_char_if();
    capitalize_word_in_string();
    return 0;
}
