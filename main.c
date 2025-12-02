#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 5
#define ROWS 20
#define COLS 20
#define MAX_SEATS 400
#define TAX_RATE 0.1
#define BASE_PRICE 80.0

typedef struct {
    char name[50];
    char showTimes[3][20]; // Assume 3 show times per movie
    char seats[3][ROWS][COLS]; // 'O' for occupied, 'F' for free, per show time
} Movie;

typedef struct {
    char customerName[50];
    char movieName[50];
    char showTime[20];
    int seatCount;
    int seats[MAX_SEATS][2]; // row, col
    float totalCost;
} Booking;

Movie movies[MAX_MOVIES];
Booking *bookings = NULL;
int bookingCount = 0;
int maxBookings = 0;

void initializeMovies() {
    strcpy(movies[0].name, "Avengers: Endgame");
    strcpy(movies[0].showTimes[0], "10:00 AM");
    strcpy(movies[0].showTimes[1], "2:00 PM");
    strcpy(movies[0].showTimes[2], "6:00 PM");
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                movies[0].seats[k][i][j] = 'F';
            }
        }
    }

    strcpy(movies[1].name, "Inception");
    strcpy(movies[1].showTimes[0], "11:00 AM");
    strcpy(movies[1].showTimes[1], "3:00 PM");
    strcpy(movies[1].showTimes[2], "7:00 PM");
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                movies[1].seats[k][i][j] = 'F';
            }
        }
    }

    strcpy(movies[2].name, "The Dark Knight");
    strcpy(movies[2].showTimes[0], "12:00 PM");
    strcpy(movies[2].showTimes[1], "4:00 PM");
    strcpy(movies[2].showTimes[2], "8:00 PM");
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                movies[2].seats[k][i][j] = 'F';
            }
        }
    }

    strcpy(movies[3].name, "Interstellar");
    strcpy(movies[3].showTimes[0], "1:00 PM");
    strcpy(movies[3].showTimes[1], "5:00 PM");
    strcpy(movies[3].showTimes[2], "9:00 PM");
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                movies[3].seats[k][i][j] = 'F';
            }
        }
    }

    strcpy(movies[4].name, "The Matrix");
    strcpy(movies[4].showTimes[0], "10:30 AM");
    strcpy(movies[4].showTimes[1], "2:30 PM");
    strcpy(movies[4].showTimes[2], "6:30 PM");
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                movies[4].seats[k][i][j] = 'F';
            }
        }
    }

}

void displayMovies() {
    printf("Available Movies:\n");
    for (int i = 0; i < MAX_MOVIES; i++) {
        if (strlen(movies[i].name) > 0) {
            printf("%d. %s\n", i + 1, movies[i].name);
            printf("   Show Times: %s, %s, %s\n", movies[i].showTimes[0], movies[i].showTimes[1], movies[i].showTimes[2]);
        }
    }
}

int findMovieIndex(char *name) {
    for (int i = 0; i < MAX_MOVIES; i++) {
        if (strcmp(movies[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}