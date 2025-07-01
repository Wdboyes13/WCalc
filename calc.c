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

#include <stdio.h>
#include <dynget.h> // From libdyn (https://github.com/Wdboyes13/libdyn)
#include <string.h> // For `strtok` and `strcspn`
#include <stdlib.h> // For `atoi`, `free`, and `exit`
#include "plugin.h" // For Plugin typedefs
#include "crossdlfcn.h" // For Cross-Platform Dynamic Libraru Loading

void do_math(PluginOp fun, int x, int y){
    int ret = fun.operation(x, y); // Call the `operation` member of struct PluginOp
    printf("%s Returned %d\n", fun.name, ret); // Print Value
}

#define MAX_OPS 128
PluginOp all_ops[MAX_OPS]; // Master array of ALL ops
int total_ops = 0; // Counter of loaded ops
#define opcount total_ops

void load_plug(const char* path){

    void* handle = DLOPEN(path); // Load inputted `.dylib`
    if (!handle) {
        printf("Plugin load error: %s\n", DLERROR());
        return;
    }

    Plugin* (*init_plug)() = DLSYM(handle, "init_plug"); // Grab `init_plug` method from loaded `.dylib`
    if (!init_plug) {
        printf("Plugin missing init function\n");
        return;
    }

    Plugin* plugin = init_plug(); // Call `init_plug` method from `.dylib` which returns the plugin
    if (total_ops + plugin->op_count < MAX_OPS){
        for (int i = 0; i < plugin->op_count; i++) {
            all_ops[total_ops++] = plugin->operations[i]; // Add operations to the master array
        }
        printf("Loaded plugin: %s (%d ops)\n", plugin->plugname, plugin->op_count); // Notify the user that the plugin loaded
    } else {
        printf("Failed to load plugin: Max Ops Reached (Max = %d, Current = %d, Plugin Wants = %d)\n",
                                                                MAX_OPS, total_ops, plugin->op_count);
    }
    
}


int main() {
    load_plug("./stdmath.dylib"); // Auto-Load `stdmath` Plugin (Standard Math)
    while (1){
    char* cmd = getstr("MATH> "); // Prompt + Input

    // Strip newline
    cmd[strcspn(cmd, "\n")] = 0;

    char *token = strtok(cmd, " "); // Get op name
    if (!token) { // If `strtok` failed, free input and go back to start of loop
        free(cmd);
        continue;
    }


    char *op_name = token;
    char *arg1_str = strtok(NULL, " "); // Extract 1st arg
    char *arg2_str = strtok(NULL, " "); // Extract 2nd arg

    if (strcmp(op_name, "help") == 0) { // Do help stuff
        printf("Available operations:\n");
        for (int i = 0; i < opcount; i++) {
            printf(" - %s - %s\n", all_ops[i].name, all_ops[i].info);
        }
        puts("Built-in commands:");
        puts(" - ldplug [path]");
        puts(" - help");
        puts(" - exit");
        free(cmd);
        continue;
    }

    if (strcmp(op_name, "exit") == 0) { // Safely exit
        free(cmd);
        exit(0);
        continue; // Shouldn't reach here, but here for safety
    }

    if (strcmp(op_name, "ldplug") == 0) { // Call Plugin loader if user provided a path
        if (arg1_str){
            load_plug(arg1_str);
        } else {
            fprintf(stderr, "Please specify plugin path");
        }
        free(cmd);
        continue;
    }

    if (!arg1_str || !arg2_str) { // Check 2 args we're passed
        fprintf(stderr, "Need two integer arguments!\n");
        free(cmd);
        continue;
    }

    int arg1 = atoi(arg1_str); // Convert args to int
    int arg2 = atoi(arg2_str);
    int found = 0; // Flag for if found
    for (int i = 0; i < opcount; i++) {
        if (strcmp(all_ops[i].name, op_name) == 0) { // Search through master ops list
            do_math(all_ops[i], arg1, arg2); // If found do the operation
            found = 1; // Set as found
            break; // Stop looking for more ops
        }
    }
    free(cmd); // Free input since we're done with it
    if (!found) {
        fprintf(stderr, "Unknown operation: %s\n", op_name); // Error if op not found
    }
    continue;
}
}