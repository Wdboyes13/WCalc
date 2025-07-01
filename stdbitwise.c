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

#include "plugin.h"
#include <stdio.h> // For info prints

// Bitwise Math Operations
int opxor(int x, int y) { return x ^ y; }
int opor(int x, int y) { return x | y; }
int opand(int x, int y) { return x & y; }
int opbsl(int x, int y) { return x << y; }
int opbsr(int x, int y) { return x >> y; }
int opboc(int x, int _ ) {
    (void)_; printf("Ignoring Num2\n"); 
    return ~x;
}

// Operation Table
PluginOp ops[] = {
    { .operation=opxor, .name="bxor", .info="Bitwise XOR" },
    { .operation=opor, .name="bor", .info="Bitwise OR" },
    { .operation=opand, .name="band", .info="Bitwise AND" },
    { .operation=opbsl, .name="bsl", .info="Bitshift Left" },
    { .operation=opbsr, .name="bsr", .info="Bitshift Right" },
    { .operation=opboc, .name="boc", .info="Bitwise Ones Complement" }

};

// Plugin Metadata
Plugin stdbitwise = {
    .plugname = "Standard Bitwise Operations Plugin",
    .op_count = sizeof(ops) / sizeof(PluginOp),
    .operations = ops
};

// Plugin initializer
Plugin* init_plug(){
    printf("Bitwise ops are distinguished with b-\n");
    return &stdbitwise;
}