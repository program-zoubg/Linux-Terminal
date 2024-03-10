#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define MAX_COMMAND_LEN 1024
#define MAX_OUTPUT_LEN 4096

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

void wget(char *url) {
    char command[MAX_COMMAND_LEN];
    sprintf(command, "powershell -command \"(New-Object System.Net.WebClient).DownloadFile('%s', 'downloaded_file')\"", url);
    system(command);
}

void curl(char *url) {
    char command[MAX_COMMAND_LEN];
    sprintf(command, "curl -o downloaded_file %s", url);
    system(command);
}

void shutdown(char *args) {
    char command[MAX_COMMAND_LEN];
    sprintf(command, "shutdown %s", args);
    system(command);
}

void ipconfig() {
    char command[] = "ipconfig";
    char output[MAX_OUTPUT_LEN];

    FILE* fp = _popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }

    _pclose(fp);
}

void mv(char *source, char *destination) {
    if (!MoveFile(source, destination)) {
        printf("Failed to move file\n");
    }
}

void cp(char *source, char *destination) {
    if (PathIsDirectory(source)) {
        char command[MAX_COMMAND_LEN];
        sprintf(command, "xcopy /s /e \"%s\" \"%s\"", source, destination);
        system(command);
    } else {
        if (!CopyFile(source, destination, FALSE)) {
            printf("Failed to copy file\n");
        }
    }
}

void touch(char *file_name) {
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Failed to create file\n");
    } else {
        fclose(fp);
    }
}

void cat(char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
    } else {
        char buffer[MAX_OUTPUT_LEN];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
}

void more(char *file_name) {
    char command[MAX_COMMAND_LEN];
    sprintf(command, "more %s", file_name);
    system(command);
}

void kill(int pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        printf("Failed to open process\n");
    } else {
        if (!TerminateProcess(hProcess, 0)) {
            printf("Failed to terminate process\n");
        } else {
            printf("Process terminated successfully\n");
        }
        CloseHandle(hProcess);
    }
}

int run() {
    char input[MAX_COMMAND_LEN];
    char command[MAX_COMMAND_LEN];
    char arg1[MAX_COMMAND_LEN];
    char arg2[MAX_COMMAND_LEN];
    int show_hidden = 0;
    int recursive = 0;

    while (1) {
    	// Clear input & command
    	memset(input, 0, sizeof(input));
    	memset(arg1, 0, sizeof(arg1));
    	memset(command, 0, sizeof(command));
    	memset(arg2, 0, sizeof(arg2));
    	
        printf("\n[%s@localhost ", get_username());
        pwd();
        printf("]$ ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        sscanf(input, "%s %s %s", command, arg1, arg2);

        if (strstr(input, "-a") != NULL) {
            show_hidden = 1;
        }
        if (strstr(input, "-r") != NULL) {
            recursive = 1;
        }

        if (strcmp(command, "ls") == 0) {
            ls(show_hidden);
        } else if (strcmp(command, "cd") == 0) {
            cd(arg1);
        } else if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "mkdir") == 0) {
            mkdir_cmd(arg1);
        } else if (strcmp(command, "rm") == 0) {
            rm(arg1, recursive);
        } else if (strcmp(command, "wget") == 0) {
            wget(arg1);
        } else if (strcmp(command, "curl") == 0) {
            curl(arg1);
        } else if (strcmp(command, "shutdown") == 0) {
            shutdown(arg1);
        } else if (strcmp(command, "ifconfig") == 0) {
            ipconfig();
        } else if (strcmp(command, "mv") == 0) {
            mv(arg1, arg2);
        } else if (strcmp(command, "cp") == 0) {
            cp(arg1, arg2);
        } else if (strcmp(command, "touch") == 0) {
            touch(arg1);
        } else if (strcmp(command, "cat") == 0) {
            cat(arg1);
        } else if (strcmp(command, "more") == 0) {
            more(arg1);
        } else if (strcmp(command, "kill") == 0) {
            int pid = atoi(arg1);
            kill(pid);
        } else if (strcmp(command, "clear") == 0) {
        	system("cls");
		} else {
            printf("Command not found\n");
        }

        show_hidden = 0;
        recursive = 0;
    }

    return 0;
}

