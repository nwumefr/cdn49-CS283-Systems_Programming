#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist) {
    clist->num = 0; // Initialize command count

    if (!cmd_line || strlen(cmd_line) == 0) {
        printf(CMD_WARN_NO_CMD);
        return WARN_NO_CMDS;
    }

    char *token;
    int cmd_count = 0;

    // Split the input string by pipes
    token = strtok(cmd_line, PIPE_STRING);
    while (token != NULL) {
        if (cmd_count >= CMD_MAX) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
            return ERR_TOO_MANY_COMMANDS;
        }

        // Trim leading and trailing spaces
        while (*token == SPACE_CHAR) token++; // Trim leading spaces
        int len = strlen(token);
        while (len > 0 && token[len - 1] == SPACE_CHAR) token[--len] = '\0'; // Trim trailing spaces

        // Parse command into exe and args
        char *arg_ptr = strchr(token, SPACE_CHAR);
        if (arg_ptr) {
            *arg_ptr = '\0'; // Split into exe and args
            arg_ptr++; // Move to first argument
            while (*arg_ptr == SPACE_CHAR) arg_ptr++; // Trim any extra spaces
        }

        if (strlen(token) >= EXE_MAX) {
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
        strcpy(clist->commands[cmd_count].exe, token);

        if (arg_ptr) {
            if (strlen(arg_ptr) >= ARG_MAX) {
                return ERR_CMD_OR_ARGS_TOO_BIG;
            }
            strcpy(clist->commands[cmd_count].args, arg_ptr);
        } else {
            clist->commands[cmd_count].args[0] = '\0'; // No arguments
        }

        cmd_count++;
        token = strtok(NULL, PIPE_STRING);
    }

    clist->num = cmd_count;
    
    // Check if the number of commands exceeds the limit
    if (clist->num > CMD_MAX) {
        printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
        return ERR_TOO_MANY_COMMANDS;
    }
    printf(CMD_OK_HEADER, cmd_count);
    // Print commands and check argument length separately
    for (int i = 0; i < clist->num; i++) {
        if (clist->commands[i].args[0]) {
            printf("<%d> %s [%s]\n", i + 1, clist->commands[i].exe, clist->commands[i].args);
        } else {
            printf("<%d> %s\n", i + 1, clist->commands[i].exe);
        }
    }

    
    
    return OK;
}

int printDragon(char* dragonFile){
    FILE *file = fopen(dragonFile, "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
        
    char line[256]; // Buffer for each line
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        
    }
    fclose(file);
    return 0;
}