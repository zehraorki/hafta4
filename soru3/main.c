#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    if (newJob == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strncpy(newJob->fileName, fileName, sizeof(newJob->fileName) - 1);
    newJob->fileName[sizeof(newJob->fileName) - 1] = '\0';
    newJob->next = NULL;

    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }

    printf("'%s' kuyruga eklendi.\n", fileName);
}

void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Kuyruk bos\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Yazdiriliyor: %s\n", temp->fileName);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Kuyruk bos!\n");
        return;
    }

    printf("\n*** Yazdirma Kuyrugu ***\n");
    PrintJob* temp = q.front;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->fileName);
        temp = temp->next;
    }
    printf("-------------------------------\n");
}

int main() {
    Queue printQueue;
    printQueue.front = NULL;
    printQueue.rear = NULL;

    int choice;
    char fileName[50];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1) Yeni dosya ekle\n");
        printf("2) Yazdir\n");
        printf("3) Kuyrugu goster\n");
        printf("4) Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &choice) != 1) {
            break;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Dosya adi: ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = '\0';
                enqueuePrintJob(&printQueue, fileName);
                break;

            case 2:
                processNextJob(&printQueue);
                break;

            case 3:
                showQueue(printQueue);
                break;

            case 4:
                while (printQueue.front != NULL) {
                    processNextJob(&printQueue);
                }
                printf("Programdan cikildi.\n");
                return 0;

            default:
                printf("Lutfen 1-4 arasi secim yapin.\n");
        }
    }

    return 0;
}