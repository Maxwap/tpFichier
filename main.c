#include "list.h"

int main() {
    int choice;

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1: {
                Task task;
                askTask(&task);
                writeTask("fichier.txt", &task);
                break;
            }
            case 2: {
                char task_name[50];
                char new_status[10];

                printf("Entrer le nom de la tâche à modifier: ");
                scanf("%s", task_name);

                printf("Entrer le nouveau statut: ");
                scanf("%s", new_status);

                modifyTaskStatus("fichier.txt", task_name, new_status);
                break;
            }
            case 3: {
                char task_name[50];

                printf("Enter task name to delete: ");
                scanf("%s", task_name);

                deleteTask("fichier.txt", task_name);
                break;
            }
            case 4:
                printf("End\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}