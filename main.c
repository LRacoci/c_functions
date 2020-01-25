#include <stdio.h>


#define stringSize(n) (((n)<<3) +1)

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned long int u8;

#define define_binary_representation(n)  \
const char *binary ## n (u ## n x){ \
    static char b[(n << 3) + 1]; \
    u1 k; \
    for(k = 0; k < n << 3; k++) { \
        b[(n << 3) - 1 - k] = (x & 1<<k) ? '1' : '0'; \
    } \
    b[n << 3] = '\0'; \
    return b; \
}

define_binary_representation(1)
define_binary_representation(2)
define_binary_representation(4)
define_binary_representation(8)

#include <string.h>
#ifdef _STRING_H
#define swap(x,y) { \
    u1 t[sizeof(x)]; \
    memcpy( t,&y,sizeof(x)); \
    memcpy(&y,&x,sizeof(x)); \
    memcpy(&x, t,sizeof(x)); \
}
#endif

u1 reverse1(u1 b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

u2 reverse2(u2 x) {
    u1* b = (u1*) &x;
    b[0] = reverse1(b[0]);
    b[1] = reverse1(b[1]);
    swap(b[0], b[1])
    return x;
}

u4 reverse4(u4 x) {
    u2* b = (u2*) &x;
    b[0] = reverse2(b[0]);
    b[1] = reverse2(b[1]);
    swap(b[0], b[1])
    return x;
}

/*
 * to implement a while loop, you will need to use recursion in the preprocessor.
 * The easiest way to do recursion is to use a deferred expression.
 * A deferred expression is an expression that requires more scans to fully expand
 */

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(id) id DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

/* Why is this important?
 * Well when a macro is scanned and expanding, it creates a disabling context.
 * This disabling context will cause a token, that refers to the currently expanding macro, to be painted blue.
 * Thus, once its painted blue, the macro will no longer expand.
 * This is why macros don't expand recursively.
 * However, a disabling context only exists during one scan,
 * so by deferring an expansion we can prevent our macros from becoming painted blue.
 * We will just need to apply more scans to the expression.
 * We can do that using this EVAL macro:

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__
 * Next, we define some operators for doing some logic(such as if, etc)
 **/

#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 ~, 1,

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BOOL(x) COMPL(NOT(x))

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define IF(c) IIF(BOOL(c))

/* Now with all these macros we can write a recursive WHILE macro.
 * We use a WHILE_INDIRECT macro to refer back to itself recursively.
 * This prevents the macro from being painted blue,
 * since it will expand on a different scan(and using a different disabling context).
 * The WHILE macro takes a predicate macro, an operator macro,
 * and a state(which is the variadic arguments).
 * It keeps applying this operator macro to the state until the predicate macro returns false(which is 0).
 **/

#define WHILE(pred, op, ...) \
    IF(pred(__VA_ARGS__)) \
    ( \
        OBSTRUCT(WHILE_INDIRECT) () \
        ( \
            pred, op, op(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
    )
#define WHILE_INDIRECT() WHILE
/* For demonstration purposes, we are just going to create a predicate that checks when number of arguments are 1:
 * */
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)

#define IS_1(x) CHECK(PRIMITIVE_CAT(IS_1_, x))
#define IS_1_1 ~, 1,

#define PRED(x, ...) COMPL(IS_1(NARGS(__VA_ARGS__)))

/*
 * Next we create an operator, which we will just concat two tokens.
 * We also create a final operator(called M) that will process the final output:
 */
#define OP(x, y, ...) CAT(x, y), __VA_ARGS__
#define M(...) CAT(__VA_ARGS__)

//M(EVAL(WHILE(PRED, OP, x, y, z))) //Expands to xyz


typedef float f1;
typedef double f2;
typedef long double f4;

typedef union _F1 {
    f1 f;
    struct {
        u4 m:23, e:8, s:1;
    }p;
} F1;

typedef union _F2 {
    f2 f;
    struct {
        u8 m:52, e:11, s:1;
    }p;
} F2;



int main(){
    F1 test1;
    test1.f = 0.5 + .25;

    u4 frac = (reverse4(test1.p.m) >> 8) | 1;
    printf("test is union {\n"
        "\tf: 0b%s,\n"
        "\tp: struct {\n"
        "\t\ts: 0b%c,\n"
        "\t\te: %d,\n"
        "\t\tm: %u,\n"
        "\t}\n"
        "}\n",
        binary4(*(u4*)&test1.f),
        test1.p.s ? '1' : '0',
        (u1)test1.p.e-128
    );
    printf("Test byte swap: 0b%s\n", binary1(reverse1(0b10)));
    printf("Test byte swap: 0b%s\n", binary2(reverse2(0b10)));
    printf("Test byte swap: 0b%s\n", binary4(reverse4(0b10)));
    return 0;
}