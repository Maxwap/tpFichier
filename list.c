#include "list.h"

void askTask(Task *task) {
    printf("Entrer le nom de la tache: ");
    scanf("%s", task->name);

    task->date = time(NULL); // set current date
    strcpy(task->status, "En_attente"); // set status to "En_attente

    printf("Entrer le nombre de jours pour la realiser: ");
    scanf("%d", &task->days);
    getchar(); // consume newline character

    while (task->days < 1) {
        printf("Le nombre de jours doit etre superieur a 1. Recommencez: ");
        scanf("%d", &task->days);
    }
}

void writeTask(const char *filename, Task *task) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // write new task to temporary file
    fprintf(temp, "%s,%ld,%s,%d\n", task->name, task->date, task->status, task->days);

    // copy contents of original file to temporary file
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    // delete original file and rename temporary file
    remove(filename);
    rename("temp.txt", filename);
}

void modifyTaskStatus(const char *filename, const char *task_name, const char *new_status) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Task task;
        sscanf(line, "%[^,],%ld,%[^,],%d", task.name, &(task.date), task.status, &(task.days));

        if (strcmp(task.name, task_name) == 0) {
            strcpy(task.status, new_status);
        }

        fprintf(temp, "%s,%ld,%s,%d\n", task.name, task.date, task.status, task.days);
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}

void deleteTask(const char *filename, const char *task_name) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Task task;
        sscanf(line, "%[^,],%ld,%[^,],%d", task.name, &(task.date), task.status, &(task.days));

        if (strcmp(task.name, task_name) != 0) {
            fprintf(temp, "%s,%ld,%s,%d\n", task.name, task.date, task.status, task.days);
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}

void printMenu() {
    printf("1. Add task\n");
    printf("2. Modify task status\n");
    printf("3. Delete task\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}