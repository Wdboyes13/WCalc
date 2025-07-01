#pragma once

typedef int (*opfunc)(int, int);

typedef struct {
    const char* name;
    const char* info;
    opfunc operation;
} PluginOp;

typedef struct {
    const char* plugname;
    int op_count;
    PluginOp* operations;
} Plugin;