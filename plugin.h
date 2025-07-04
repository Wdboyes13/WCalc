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

#pragma once

typedef int (*opfunc)(int, int); // Typedef for operation function pointers

// Plugin Operation Typedef
typedef struct {
    const char* name; // Operation Name
    const char* info; // Short Description of the Operation
    opfunc operation; // Function Pointer to Operation
} PluginOp;

// Plugin Typedef
typedef struct {
    const char* plugname; // Plugin Name
    int op_count;         // Number of Operations in Plugin
    PluginOp* operations; // Pointer to array of all operations
} Plugin;