/*
A Modular Cross-Platform Calculator
Copyright (C) 2025  Wdboyes13

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "crossdlfcn.h"
#include "plugin.h" // For plugin typedefs
#include <math.h> // For `pow()`
#include <stdlib.h> // For `rand()` and `srand()`
#include <time.h> // for time() to initialize RNG

// Math operations
int addf(int x, int y) { return x + y; }
int mulf(int x, int y) { return x * y; }
int divf(int x, int y) { return x / y; }
int subf(int x, int y) { return x - y; }
int powfu(int x, int y) { return pow((double)x, (double)y); }
int mod(int x, int y) { return x % y; }
int randf(int min, int max) { return rand() % (max - min + 1) + min; }

// Array with pointers to math operations, op names, and info for help
PluginOp ops[] = {
    { .operation=addf, .name="add", .info="Add 2 numbers" },
    { .operation=subf, .name="subtract", .info="Subtract 2 numbers" },
    { .operation=mulf, .name="multiply", .info="Multiply 2 numbers" },
    { .operation=divf, .name="divide", .info="Divide 2 numbers" },
    { .operation=powfu, .name="power", .info="Get Num1 to the power of Num2" },
    { .operation=mod, .name="modulo", .info="Get modulo of 2 numbers" },
    { .operation=randf, .name="random", .info="Get a random number between Num1 - Num2" }
};

// Plugin metadata
Plugin stdmath = {
    .plugname = "Standard Math Plugin",
    .op_count = sizeof(ops) / sizeof(PluginOp),
    .operations = ops,
};

// Initialize plugin (Do setup and return plugin) (Function required)
EXPORT  Plugin* init_plug(){
    srand(time(NULL));
    return &stdmath;
}