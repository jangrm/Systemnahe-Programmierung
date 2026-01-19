// File: sopfind/src/cli.h
#ifndef SOPFIND_SRC_CLI_H
#define SOPFIND_SRC_CLI_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Zeigt die Usage/Hilfe für das Programm an. */
void print_usage(const char *progname);

/*
 Parsiert globale CLI-Optionen.
 - argc, argv: Standard-Argumente.
 - start_path: Zeiger auf const char\*; wird auf den gewählten Startpfad gesetzt.
 Rückgabewerte:
   1  -> Hilfe wurde angezeigt (Programm sollte mit Exit 0 beenden)
   0  -> Erfolg, normal weitermachen
  -1  -> Fehler beim Parsen (z.\,B. fehlendes Argument)
*/
int parse_cli(int argc, char *argv[], const char **start_path);

#ifdef __cplusplus
}
#endif

#endif /* SOPFIND_SRC_CLI_H */
