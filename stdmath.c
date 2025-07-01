#include "plugin.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int addf(int x, int y) { return x + y; }
int mulf(int x, int y) { return x * y; }
int divf(int x, int y) { return x / y; }
int subf(int x, int y) { return x - y; }
int powfu(int x, int y) { return pow((double)x, (double)y); }
int mod(int x, int y) { return x % y; }
int randf(int min, int max) { return rand() % (max - min + 1) + min; }

PluginOp ops[] = {
    { .operation=addf, .name="add", .info="Add 2 numbers" },
    { .operation=subf, .name="subtract", .info="Subtract 2 numbers" },
    { .operation=mulf, .name="multiply", .info="Multiply 2 numbers" },
    { .operation=divf, .name="divide", .info="Divide 2 numbers" },
    { .operation=powfu, .name="power", .info="Get Num1 to the power of Num2" },
    { .operation=mod, .name="modulo", .info="Get modulo of 2 numbers" },
    { .operation=randf, .name="random", .info="Get a random number between Num1 - Num2" }
};

Plugin stdmath = {
    .plugname = "Standard Math Plugin",
    .op_count = sizeof(ops) / sizeof(PluginOp),
    .operations = ops,
};

Plugin* init_plug(){
    srand(time(NULL));
    return &stdmath;
}