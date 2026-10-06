#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (newSong == NULL) {
        printf("Bellek yetersiz\n");
        return;
    }

    strncpy(newSong->name, name, sizeof(newSong->name) - 1);
    newSong->name[sizeof(newSong->name) - 1] = '\0';
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        printf("Listeye eklendi: %s\n", name);
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
    printf("Listeye eklendi: %s\n", name);
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* current = *head;

    while (current != NULL && strcmp(current->name, name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("'%s' isimli sarki listede bulunamadi.\n", name);
        return;
    }

    if (current == *head) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    free(current);
    printf("Listeden silindi: %s\n", name);
}

void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste bos\n");
        return;
    }

    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Simdi caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin sonundasiniz.\n");
    }
}

void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste bos\n");
        return;
    }

    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Simdi caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin basindasiniz.\n");
    }
}

void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos\n");
        return;
    }

    printf("\n**Calma Listesi**\n");
    Song* temp = head;
    int index = 1;
    while (temp != NULL) {
        printf("%d. %s\n", index++, temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main() {
    Song* playlist = NULL;
    Song* currentPlaying = NULL;
    int choice;
    char songName[50];

    while (1) {
        printf("\n*** MENU ***\n");
        if (currentPlaying != NULL) {
            printf("Su an calan: [%s]\n", currentPlaying->name);
        } else {
            printf("Su an calan: [Yok]\n");
        }
        printf("1-Sarki Ekle\n");
        printf("2-Sarki Sil\n");
        printf("3-Sonraki Sarkiya Gec\n");
        printf("4-Onceki Sarkiya Gec\n");
        printf("5-Calma Listesini Goruntule\n");
        printf("6-Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &choice) != 1) {
            break;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Eklenecek sarki adi: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = '\0';
                addSongToEnd(&playlist, songName);
                if (currentPlaying == NULL) {
                    currentPlaying = playlist;
                }
                break;

            case 2:
                printf("Silinecek sarki adi: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = '\0';

                if (currentPlaying != NULL && strcmp(currentPlaying->name, songName) == 0) {
                    if (currentPlaying->next != NULL) {
                        currentPlaying = currentPlaying->next;
                    } else if (currentPlaying->prev != NULL) {
                        currentPlaying = currentPlaying->prev;
                    } else {
                        currentPlaying = NULL;
                    }
                }
                removeSong(&playlist, songName);
                break;

            case 3:
                playNext(&currentPlaying);
                break;

            case 4:
                playPrevious(&currentPlaying);
                break;

            case 5:
                displayPlaylist(playlist);
                break;

            case 6:
                while (playlist != NULL) {
                    Song* temp = playlist;
                    playlist = playlist->next;
                    free(temp);
                }
                printf("Programdan cikildi\n");
                return 0;

            default:
                printf("Lutfen 1-6 arasi seçim yap.\n");
        }
    }

    return 0;
}