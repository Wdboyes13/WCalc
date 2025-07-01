#include "plugin.h"
#include <stdio.h>

int opxor(int x, int y) { return x ^ y; }
int opor(int x, int y) { return x | y; }
int opand(int x, int y) { return x & y; }
int opbsl(int x, int y) { return x << y; }
int opbsr(int x, int y) { return x >> y; }
int opboc(int x, int _ ) {
    (void)_; printf("Ignoring Num2\n"); 
    return ~x;
}

PluginOp ops[] = {
    { .operation=opxor, .name="bxor", .info="Bitwise XOR" },
    { .operation=opor, .name="bor", .info="Bitwise OR" },
    { .operation=opand, .name="band", .info="Bitwise AND" },
    { .operation=opbsl, .name="bsl", .info="Bitshift Left" },
    { .operation=opbsr, .name="bsr", .info="Bitshift Right" },
    { .operation=opboc, .name="boc", .info="Bitwise Ones Complement" }

};

Plugin stdbitwise = {
    .plugname = "Standard Bitwise Operations Plugin",
    .op_count = sizeof(ops) / sizeof(PluginOp),
    .operations = ops
};

Plugin* init_plug(){
    printf("Bitwise ops are distinguished with b-\n");
    return &stdbitwise;
}