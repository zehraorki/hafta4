#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strncpy(newWord->text, text, sizeof(newWord->text) - 1);
    newWord->text[sizeof(newWord->text) - 1] = '\0';

    newWord->next = *top;
    *top = newWord;
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("Stack bos\n");
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}



void showWords(Word* top) {
    if (top == NULL) {
        printf("Metin bos.\n");
        return;
    }
    Word* words[100];
    int count = 0;

    Word* temp = top;
    while (temp != NULL && count < 100) {
        words[count++] = temp;
        temp = temp->next;
    }
    for (int i = count - 1; i >= 0; i--) {
        printf("%s ", words[i]->text);
    }
    printf("\n");
}

int main() {
    Word* stackTop = NULL;
    char command[100];
    char action[20];
    char text[50];

    printf("Komutlar: 'add', 'undo', 'show', 'exit'\n");

    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        int readCount = sscanf(command, "%s", action);
        if (readCount < 1) continue;

        if (strcmp(action, "add") == 0) {
            if (sscanf(command, "%*s %[^\n]", text) == 1) {
                pushWord(&stackTop, text);
            } else {
                printf("Kullanim: add\n");
            }
        } else if (strcmp(action, "undo") == 0) {
            popWord(&stackTop);
        } else if (strcmp(action, "show") == 0) {
            showWords(stackTop);
        } else if (strcmp(action, "exit") == 0) {
            while (stackTop != NULL) {
                popWord(&stackTop);
            }
            break;
        } else {
            printf("Gecersiz komut!\n");
        }
    }

    return 0;
}