// File: sopfind/src/cli.h
#ifndef SOPFIND_SRC_CLI_H
#define SOPFIND_SRC_CLI_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void print_usage(const char *progname);


int parse_cli(int argc, char *argv[], const char **start_path);

#ifdef __cplusplus
}
#endif

#endif 

