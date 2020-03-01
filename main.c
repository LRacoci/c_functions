#include <stdio.h>


typedef unsigned char       u0; //  8 bits = 1 byte  = 1<<0 bytes
typedef unsigned short      u1; // 16 bits = 2 bytes = 1<<1 bytes
typedef unsigned int        u2; // 32 bits = 4 bytes = 1<<2 bytes
typedef unsigned long int   u3; // 64 bits = 8 bytes = 1<<3 bytes

#define define_binary_representation(n) \
const char * binary ## n (u ## n x){ \
    static char b[((1 << n) << 3) + 1]; \
    u0 k; \
    for(k = 0; k < (1 << n) << 3; k++) { \
        b[((1 << n) << 3) - 1 - k] = (x & 1<<k) ? '1' : '0'; \
    } \
    b[(1 << n) << 3] = '\0'; \
    return b; \
}

define_binary_representation(0)
define_binary_representation(1)
define_binary_representation(2)
define_binary_representation(3)

#include <string.h>
#ifdef _STRING_H
#define swap(x,y) { \
    u0 t[sizeof(x)]; \
    memcpy( t,&y,sizeof(x)); \
    memcpy(&y,&x,sizeof(x)); \
    memcpy(&x, t,sizeof(x)); \
}
#endif

u0 reverse0(u0 b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

u1 reverse1(u1 x) {
    u0* b = (u0*) &x;
    b[0] = reverse0(b[0]);
    b[1] = reverse0(b[1]);
    swap(b[0], b[1])
    return x;
}

u2 reverse2(u2 x) {
    u1* b = (u1*) &x;
    b[0] = reverse1(b[0]);
    b[1] = reverse1(b[1]);
    swap(b[0], b[1])
    return x;
}

u3 reverse3(u3 x) {
    u2* b = (u2*) &x;
    b[0] = reverse2(b[0]);
    b[1] = reverse2(b[1]);
    swap(b[0], b[1])
    return x;
}

typedef float       f2; //  32 bits =  4 bytes = 1<<2 bytes
typedef double      f3; //  64 bits =  8 bytes = 1<<3 bytes
typedef long double f4; // 128 bits = 16 bytes = 1<<4 bytes

typedef union _F2 {
    f2 f;
    struct {
        u2 m:23, e:8, s:1;
    }p;
} F2;

typedef union _F3 {
    f3 f;
    struct {
        u3 m:52, e:11, s:1;
    }p;
} F3;

int main(){
    printf("Test binary0(%d) = 0b%s\n", 0b10, binary0(0b10));
    printf("--------------------------------\n");
    printf("Test 1 byte swap: 0b%s\n", binary0(reverse0(0b10)));
    printf("Test 2 bytes swap: 0b%s\n", binary1(reverse1(0b10)));
    printf("Test 4 bytes swap: 0b%s\n", binary2(reverse2(0b10)));

    F2 test1;
    test1.f = -0.25 - 0.125;
    printf("test1 is union {\n"
        "\tf: 0b%s,\n"
        "\tp: struct {\n"
        "\t\ts: 0b%c,\n"
        "\t\te: %d,\n"
        "\t\tm: %u,\n"
        "\t}\n"
        "}\n",
        binary2(*(u2*)&test1.f),
        test1.p.s ? '1' : '0',
           (u0)test1.p.e - 127,
        (u1) reverse1(test1.p.m)
    );
    F3 test2;
    test2.f = -0.25 - 0.125;
    printf("test2 is union {\n"
           "\tf: 0b%s,\n"
           "\tp: struct {\n"
           "\t\ts: 0b%c,\n"
           "\t\te: %d,\n"
           "\t\tm: %lu,\n"
           "\t}\n"
           "}\n",
           binary3(*(u3*)&test2.f),
           test2.p.s ? '1' : '0',
           (u1)test2.p.e - 1023,
           (u3) reverse3(test2.p.m)
    );
    printf("%d %d %d %d", sizeof(u0), sizeof(u1), sizeof(u2), sizeof(u3));
    printf("%d %d %d %d", sizeof(u0), sizeof(u1), sizeof(u2), sizeof(u3));
    return 0;
}