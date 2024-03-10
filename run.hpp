#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_COMMAND_LEN 100

char* get_username() {
    return getenv("USERNAME");
}

void ls(int show_hidden) {
    if (show_hidden) {
        system("dir /a");
    } else {
        system("dir");
    }
}

void cd(char *path) {
    if (SetCurrentDirectory(path) == 0) {
        printf("Failed to change directory\n");
    }
}

void pwd() {
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);
    printf("%s", path);
}

void mkdir_cmd(char *dir_name) {
    if (!CreateDirectory(dir_name, NULL)) {
        printf("Failed to create directory\n");
    }
}

void rm(char *file_name, int recursive) {
    if (recursive) {
        char command[MAX_COMMAND_LEN];
        sprintf(command, "rmdir /s /q %s", file_name);
        system(command);
    } else {
        if (!DeleteFile(file_name)) {
            printf("Failed to delete file\n");
        }
    }
}

int run() {
    char input[MAX_COMMAND_LEN];
    char command[MAX_COMMAND_LEN];
    char arg[MAX_COMMAND_LEN];
    int show_hidden = 0;
    int recursive = 0;

    while (1) {
        printf("\n[%s@localhost ", get_username());
        pwd();
        printf("]$ ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        sscanf(input, "%s %s", command, arg);

        if (strstr(input, "-a") != NULL) {
            show_hidden = 1;
        }
        if (strstr(input, "-r") != NULL) {
            recursive = 1;
        }

        if (strcmp(command, "ls") == 0) {
            ls(show_hidden);
        } else if (strcmp(command, "cd") == 0) {
            cd(arg);
        } else if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "mkdir") == 0) {
            mkdir_cmd(arg);
        } else if (strcmp(command, "rm") == 0) {
            rm(arg, recursive);
        } else {
            printf("Command not found\n");
        }

        show_hidden = 0;
        recursive = 0;
    }

    return 0;
}

