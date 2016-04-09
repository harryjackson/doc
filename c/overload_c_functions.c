/*
 * http://stackoverflow.com/questions/36506988/function-overloading-in-c-compiler-warnings
 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define print(x)                                                                      \
  (__builtin_choose_expr(__builtin_types_compatible_p(typeof(x), int   ), print_int   , \
                         __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), char[]), print_string, \
                           (void)0))(x))

#define print1(x)                                                                          \
  __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), int   ), print_int1(1,x)   , \
      __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), char[]), print_string1(1,x), \
        (void)0))

#define print2(x)                                                                    \
  __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), int   ), printer(1,x), \
      __builtin_choose_expr(__builtin_types_compatible_p(typeof(x), char[]), printer(2,x), \
        (void)0))

#define TYPE_ID(x) __builtin_types_compatible_p(typeof(x), int   ) * 1 \
                +  __builtin_types_compatible_p(typeof(x), char[]) * 2  

#define print3(x) printer(TYPE_ID(x), x)

#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]

#define print4(x) \
    STATIC_ASSERT(TYPE_ID(x), __LINE__); \
    printer(TYPE_ID(x), x)

void printer(int i, ...) {
  va_list v;
  va_start(v, i);
  switch(i) {
    case 1:{
             int arg = va_arg(v, int);
             printf("int: %d\n", arg);
             va_end(v);
             break;
           }   
    case 2:{
             char * arg = va_arg(v, char*);
             printf("char*: %s\n", arg);
             va_end(v);
             break;
           }   
    default: {
               fprintf(stderr, "Unknown type, abort\n");
               abort();
             }
  }
}

void print_int(int i) {
    printf("int: %d\n", i);
}

void print_string(char* s) {
    printf("char*: %s\n", s);
}

void print_int1(int i, ...) {
  va_list v;
  va_start(v, i);
  int arg = va_arg(v, int);
  printf("int: %d\n", arg);
  va_end(v);
}

void print_string1(int i, ...) {
  va_list v;
  va_start(v, i);
  char * arg = va_arg(v, char*);
  printf("char*: %s\n", arg);
  va_end(v);
}

int main(int argc, char* argv[]) {
  int  var    = 1729;
  double var1 = 1729;
  //Type safe
  //print(var1);//Comple time error
  print(var);
  print("print");

  /* Following are not Type Safe */ 
  print1(var1);// BAD... Does nothing.
  print1(var);
  print1("print1");

  print2(var1);// BAD... Does nothing.
  print2(var);
  print2("print2");

  //print3(var1);//Evil... Runtime error
  print3(var);
  print3("print3");

  //Type Safe
  //print4(var1);//Comple time error
  print4(var);
  print4("print4");
  return 0;
}
