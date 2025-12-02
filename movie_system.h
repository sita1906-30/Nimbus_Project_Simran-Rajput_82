#ifndef MOVIE_SYSTEM_H
#define MOVIE_SYSTEM_H

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
    char showTimes[3][20];
    char seats[3][ROWS][COLS];
} Movie;

typedef struct {
    char customerName[50];
    char movieName[50];
    char showTime[20];
    int seatCount;
    int seats[MAX_SEATS][2];
    float totalCost;
} Booking;

extern Movie movies[MAX_MOVIES];
extern Booking *bookings;
extern int bookingCount;
extern int maxBookings;

void initializeMovies();
void displayMovies();
int findMovieIndex(char *name);
void displaySeats(int movieIndex, int showIndex);
float calculateCost(int seatCount);
void bookSeats();
void cancelBooking();
void saveBookings();
void loadBookings();

#endif
