#include <stdio.h>
#include <dynget.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "plugin.h"
#include <dlfcn.h>

void do_math(PluginOp fun, int x, int y){
    int ret = fun.operation(x, y);
    printf("%s Returned %d\n", fun.name, ret);
}

#define MAX_OPS 128
PluginOp all_ops[MAX_OPS];
int total_ops = 0;
#define opcount total_ops

void load_plug(const char* path){

    void* handle = dlopen(path, RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Plugin load error: %s\n", dlerror());
        return;
    }

    Plugin* (*init_plug)() = dlsym(handle, "init_plug");
    if (!init_plug) {
        fprintf(stderr, "Plugin missing init function\n");
        return;
    }

    Plugin* plugin = init_plug();
    printf("Loaded plugin: %s (%d ops)\n", plugin->plugname, plugin->op_count);

    for (int i = 0; i < plugin->op_count; i++) {
        all_ops[total_ops++] = plugin->operations[i];
    }
}


int main() {
    load_plug("./stdmath.dylib");
    while (1){
    char* cmd = getstr("MTH> ");

    // Strip newline
    cmd[strcspn(cmd, "\n")] = 0;

    char *token = strtok(cmd, " ");
    if (!token) {
        free(cmd);
        continue;
    }


    char *op_name = token;
    char *arg1_str = strtok(NULL, " ");
    char *arg2_str = strtok(NULL, " ");

    if (strcmp(op_name, "help") == 0) {
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

    if (strcmp(op_name, "exit") == 0) {
        free(cmd);
        exit(0);
        continue; // Shouldn't reach here, but here for safety
    }

    if (strcmp(op_name, "ldplug") == 0) {
        if (arg1_str){
            load_plug(arg1_str);
        } else {
            fprintf(stderr, "Please specify plugin path");
        }
        free(cmd);
        continue;
    }

    if (!arg1_str || !arg2_str) {
        fprintf(stderr, "Need two integer arguments!\n");
        free(cmd);
        continue;
    }

    int arg1 = atoi(arg1_str);
    int arg2 = atoi(arg2_str);
    int found = 0;
    for (int i = 0; i < opcount; i++) {
        if (strcmp(all_ops[i].name, op_name) == 0) {
            do_math(all_ops[i], arg1, arg2);
            found = 1;
            break;
        }
    }
    free(cmd);
    if (!found) {
        fprintf(stderr, "Unknown operation: %s\n", op_name);
    }
    continue;
}
}