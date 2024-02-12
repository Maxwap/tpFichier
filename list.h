#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef UNTITLED4_LIST_H
#define UNTITLED4_LIST_H

typedef struct task {
    char name[50];
    time_t date; // Utilisation de time_t pour stocker la date
    char status[10]; // En_attente, En_cours, Terminee
    int days;
    struct task *next;
} Task;

void askTask(Task *task);

void writeTask(const char *filename, Task *task);

void modifyTaskStatus(const char *filename, const char *task_name, const char *new_status);

void deleteTask(const char *filename, const char *task_name);

void printMenu();

#endif //UNTITLED4_LIST_H