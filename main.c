#include "movie_system.h"

int main() {
    initializeMovies();
    loadBookings();
    int choice;

    while(1){
        printf("\n1. Display Movies\n2. Book Seats\n3. Cancel Booking\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();

        switch(choice){
            case 1:
                displayMovies();
                break;
            case 2:
                bookSeats();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                saveBookings();
                free(bookings);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
