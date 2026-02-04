#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Song structure
struct Song {
    int musicno;
    char musicname[100];
    char musictype[30];
    char filepath[200]; // Path to the actual song file
    struct Song *prev, *next;
};

struct Song *head = NULL;
struct Song *current = NULL;

// Create a new Song node
struct Song* createSong(int musicno, char musicname[], char musictype[], char filepath[]) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));
    newSong->musicno = musicno;
    strcpy(newSong->musicname, musicname);
    strcpy(newSong->musictype, musictype);
    strcpy(newSong->filepath, filepath);
    newSong->prev = newSong->next = NULL;
    return newSong;
}

// Add song to playlist
void addSong() {
    int musicno;
    char musicname[100], musictype[30], filepath[200];

    printf("\nEnter Song Number: ");
    scanf("%d", &musicno);
    getchar(); // clear newline
    printf("Enter Telugu Song Name: ");
    fgets(musicname, sizeof(musicname), stdin);
    musicname[strcspn(musicname, "\n")] = 0; // remove newline

    printf("Enter Song Type): ");
    scanf("%s", musictype);
    getchar();

    printf("Enter full path of the music file: ");
    fgets(filepath, sizeof(filepath), stdin);
    filepath[strcspn(filepath, "\n")] = 0;

    struct Song *newSong = createSong(musicno, musicname, musictype, filepath);

    if (head == NULL) {
        head = newSong;
        current = head;
        printf("First song added to the playlist!\n");
    } else {
        struct Song *temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newSong;
        newSong->prev = temp;
        printf("song added to playlist!\n");
    }
}

// Display all songs
void displayPlaylist() {
    if (head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    struct Song *temp = head;
    printf("\nSongs Playlist:\n");
    while (temp != NULL) {
        printf("[%d] %s (%s) - %s\n", temp->musicno, temp->musicname, temp->musictype, temp->filepath);
        temp = temp->next;
    }
}

// Function to play a song file
void playSongFile(char filepath[]) {
#ifdef _WIN32
    char command[300];
    sprintf(command, "start \"\" \"%s\"", filepath);
    system(command);
#elif __APPLE__
    char command[300];
    sprintf(command, "open \"%s\"", filepath);
    system(command);
#else
    char command[300];
    sprintf(command, "xdg-open \"%s\"", filepath);
    system(command);
#endif
}

// Play the current song
void playCurrent() {
    if (current == NULL) {
        printf("\nNo song is currently selected.\n");
        return;
    }
    printf("\nNow Playing: %s (%s)\n", current->musicname, current->musictype);
    playSongFile(current->filepath);
}

// Play next song
void playNext() {
    if (current == NULL) {
        printf("\nPlaylist is empty!\n");
        return;
    }
    if (current->next != NULL) {
        current = current->next;
        printf("\nNow Playing Next: %s (%s)\n", current->musicname, current->musictype);
        playSongFile(current->filepath);
    } else {
        printf("\nYou are at the last song.\n");
    }
}

// Play previous song
void playPrevious() {
    if (current == NULL) {
        printf("\nPlaylist is empty!\n");
        return;
    }
    if (current->prev != NULL) {
        current = current->prev;
        printf("\nNow Playing Previous: %s (%s)\n", current->musicname, current->musictype);
        playSongFile(current->filepath);
    } else {
        printf("\nYou are at the first song.\n");
    }
}

// Play first song
void playFirst() {
    if (head == NULL) {
        printf("\nPlaylist is empty!\n");
        return;
    }
    current = head;
    printf("\nPlaying first Telugu song: %s (%s)\n", current->musicname, current->musictype);
    playSongFile(current->filepath);
}

// Delete song by number
void deleteSong() {
    if (head == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    int musicno;
    printf("\nEnter Song Number to Delete: ");
    scanf("%d", &musicno);

    struct Song *temp = head;

    while (temp != NULL && temp->musicno != musicno)
        temp = temp->next;

    if (temp == NULL) {
        printf("Song not found!\n");
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    if (current == temp)
        current = head;

    printf("Deleted song: %s\n", temp->musicname);
    free(temp);
}

// Show currently playing song
void nowPlaying() {
    if (current == NULL)
        printf("\nNo  song is currently selected.\n");
    else
        printf("\nNow Playing: %s (%s)\n", current->musicname, current->musictype);
}

// Main menu
int main() {
    int choice;

    printf("\n Music Playlist using Doubly Linked List \n");

    while (1) {
        printf("\n---------------- MENU ----------------\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Play First Song\n");
        printf("4. Play Current Song\n");
        printf("5. Play Next Song\n");
        printf("6. Play Previous Song\n");
        printf("7. Show Current Song\n");
        printf("8. Delete Song\n");
        printf("9. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addSong(); break;
            case 2: displayPlaylist(); break;
            case 3: playFirst(); break;
            case 4: playCurrent(); break;
            case 5: playNext(); break;
            case 6: playPrevious(); break;
            case 7: nowPlaying(); break;
            case 8: deleteSong(); break;
            case 9:
                printf("\nExiting Music Playlist.\n");
               exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
return 0;
}
