#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct task {
    char name[50];
    time_t date; // Utilisation de time_t pour stocker la date
    char status[10]; // En_attente, En_cours, Terminee
    int days;
    struct task *next;
} Task;

void get_task(Task *task) {
    printf("Enter task name: ");
    fgets(task->name, 50, stdin);
    task->name[strcspn(task->name, "\n")] = 0; // remove newline character

    task->date = time(NULL); // set current date

    printf("Enter task status: ");
    fgets(task->status, 10, stdin);
    task->status[strcspn(task->status, "\n")] = 0; // remove newline character

    printf("Enter task days: ");
    scanf("%d", &(task->days));
    getchar(); // consume newline character
}

void write_task(const char *filename, Task *task) {
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

void modify_task_status(const char *filename, const char *task_name, const char *new_status) {
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

void delete_task(const char *filename, const char *task_name) {
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

void print_menu() {
    printf("1. Add task\n");
    printf("2. Modify task status\n");
    printf("3. Delete task\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    do {
        print_menu();
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1: {
                Task task;
                get_task(&task);
                write_task("fichier.txt", &task);
                break;
            }
            case 2: {
                char task_name[50];
                char new_status[10];

                printf("Enter task name: ");
                fgets(task_name, 50, stdin);
                task_name[strcspn(task_name, "\n")] = 0; // remove newline character

                printf("Enter new status: ");
                fgets(new_status, 10, stdin);
                new_status[strcspn(new_status, "\n")] = 0; // remove newline character

                modify_task_status("fichier.txt", task_name, new_status);
                break;
            }
            case 3: {
                char task_name[50];

                printf("Enter task name to delete: ");
                fgets(task_name, 50, stdin);
                task_name[strcspn(task_name, "\n")] = 0; // remove newline character

                delete_task("fichier.txt", task_name);
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}