#include "movie_system.h"

Movie movies[MAX_MOVIES];
Booking *bookings = NULL;
int bookingCount = 0;
int maxBookings = 0;

void initializeMovies() {
    strcpy(movies[0].name, "Avengers: Endgame");
    strcpy(movies[0].showTimes[0], "10:00 AM");
    strcpy(movies[0].showTimes[1], "2:00 PM");
    strcpy(movies[0].showTimes[2], "6:00 PM");

    for(int k=0;k<3;k++){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                movies[0].seats[k][i][j]='F';
            }
        }
    }

    strcpy(movies[1].name,"Inception");
    strcpy(movies[1].showTimes[0],"11:00 AM");
    strcpy(movies[1].showTimes[1],"3:00 PM");
    strcpy(movies[1].showTimes[2],"7:00 PM");

    for(int k=0;k<3;k++){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                movies[1].seats[k][i][j]='F';
            }
        }
    }

    strcpy(movies[2].name,"The Dark Knight");
    strcpy(movies[2].showTimes[0],"12:00 PM");
    strcpy(movies[2].showTimes[1],"4:00 PM");
    strcpy(movies[2].showTimes[2],"8:00 PM");

    for(int k=0;k<3;k++){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                movies[2].seats[k][i][j]='F';
            }
        }
    }

    strcpy(movies[3].name,"Interstellar");
    strcpy(movies[3].showTimes[0],"1:00 PM");
    strcpy(movies[3].showTimes[1],"5:00 PM");
    strcpy(movies[3].showTimes[2],"9:00 PM");

    for(int k=0;k<3;k++){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                movies[3].seats[k][i][j]='F';
            }
        }
    }

    strcpy(movies[4].name,"The Matrix");
    strcpy(movies[4].showTimes[0],"10:30 AM");
    strcpy(movies[4].showTimes[1],"2:30 PM");
    strcpy(movies[4].showTimes[2],"6:30 PM");

    for(int k=0;k<3;k++){
        for(int i=0;i<ROWS;i++){
            for(int j=0;j<COLS;j++){
                movies[4].seats[k][i][j]='F';
            }
        }
    }
}

void displayMovies() {
    printf("Available Movies:\n");
    for(int i=0;i<MAX_MOVIES;i++){
        if(strlen(movies[i].name)>0){
            printf("%d. %s\n",i+1,movies[i].name);
            printf("   Show Times: %s, %s, %s\n",
                   movies[i].showTimes[0],movies[i].showTimes[1],movies[i].showTimes[2]);
        }
    }
}

int findMovieIndex(char *name) {
    for(int i=0;i<MAX_MOVIES;i++){
        if(strcmp(movies[i].name,name)==0) return i;
    }
    return -1;
}

void displaySeats(int movieIndex, int showIndex) {
    printf("Seat Layout for %s at %s:\n", movies[movieIndex].name, movies[movieIndex].showTimes[showIndex]);
    printf("  ");
    for(int j=0;j<COLS;j++){
        printf("%2d ", j+1);
    }
    printf("\n");

    for(int i=0;i<ROWS;i++){
        printf("%2d ", i+1);
        for(int j=0;j<COLS;j++){
            char c = movies[movieIndex].seats[showIndex][i][j]=='F'?'#':'*';
            printf("%2c ", c);
        }
        printf("\n");
    }
}

float calculateCost(int seatCount){
    float sub=seatCount*BASE_PRICE;
    float tax=sub*TAX_RATE;
    return sub+tax;
}

void bookSeats(){
    char customerName[50], movieName[50], showTime[20];
    int movieIndex, showIndex, seatCount;

    printf("Enter customer name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName,"\n")] = 0;

    printf("Enter movies name: ");
    fgets(movieName, sizeof(movieName), stdin);
    movieName[strcspn(movieName,"\n")] = 0;

    movieIndex=findMovieIndex(movieName);
    if(movieIndex==-1){
        printf("Movie not found.\n");
        return;
    }

    printf("Enter show time: ");
    fgets(showTime, sizeof(showTime), stdin);
    showTime[strcspn(showTime,"\n")] = 0;

    showIndex=-1;
    for(int i=0;i<3;i++){
        if(strcmp(movies[movieIndex].showTimes[i],showTime)==0){
            showIndex=i; break;
        }
    }

    if(showIndex==-1){
        printf("Show time not found.\n");
        return;
    }

    displaySeats(movieIndex,showIndex);

    printf("Enter number of seats to book: ");
    scanf("%d",&seatCount);

    if(seatCount<=0 || seatCount>MAX_SEATS){
        printf("Invalid number.\n");
        return;
    }

    int seats[MAX_SEATS][2];

    for(int i=0;i<seatCount;i++){
        printf("Enter row and column for seat %d: ", i+1);
        scanf("%d %d",&seats[i][0],&seats[i][1]);
        seats[i][0]--; seats[i][1]--;

        if(seats[i][0]<0||seats[i][0]>=ROWS||seats[i][1]<0||seats[i][1]>=COLS
           || movies[movieIndex].seats[showIndex][seats[i][0]][seats[i][1]]=='O'){
            printf("Invalid or occupied seat.\n");
            return;
        }
    }

    for(int i=0;i<seatCount;i++){
        movies[movieIndex].seats[showIndex][seats[i][0]][seats[i][1]]='O';
    }

    if(bookingCount>=maxBookings){
        maxBookings+=10;
        bookings=realloc(bookings, maxBookings*sizeof(Booking));
    }

    strcpy(bookings[bookingCount].customerName,customerName);
    strcpy(bookings[bookingCount].movieName,movieName);
    strcpy(bookings[bookingCount].showTime,showTime);
    bookings[bookingCount].seatCount=seatCount;
    memcpy(bookings[bookingCount].seats,seats,sizeof(seats));
    bookings[bookingCount].totalCost=calculateCost(seatCount);

    bookingCount++;

    printf("Booking successful. Total cost: %.2f\n",bookings[bookingCount-1].totalCost);
}

void cancelBooking(){
    char customerName[50];
    printf("Enter customer name: ");
    fgets(customerName,sizeof(customerName),stdin);
    customerName[strcspn(customerName,"\n")]=0;

    for(int i=0;i<bookingCount;i++){
        if(strcmp(bookings[i].customerName,customerName)==0){

            int movieIndex=findMovieIndex(bookings[i].movieName);
            int showIndex=-1;

            for(int k=0;k<3;k++){
                if(strcmp(movies[movieIndex].showTimes[k],bookings[i].showTime)==0){
                    showIndex=k; break;
                }
            }

            for(int j=0;j<bookings[i].seatCount;j++){
                int r=bookings[i].seats[j][0];
                int c=bookings[i].seats[j][1];
                movies[movieIndex].seats[showIndex][r][c]='F';
            }

            for(int j=i;j<bookingCount-1;j++){
                bookings[j]=bookings[j+1];
            }

            bookingCount--;

            printf("Booking cancelled.\n");
            return;
        }
    }

    printf("Booking not found.\n");
}

void saveBookings(){
    FILE *fp=fopen("bookings.txt","w");
    if(!fp) return;

    fprintf(fp,"%d\n",bookingCount);

    for(int i=0;i<bookingCount;i++){
        fprintf(fp,"%s %s %s %d %.2f\n",
                bookings[i].customerName,
                bookings[i].movieName,
                bookings[i].showTime,
                bookings[i].seatCount,
                bookings[i].totalCost);

        for(int j=0;j<bookings[i].seatCount;j++){
            fprintf(fp,"%d %d ",bookings[i].seats[j][0],bookings[i].seats[j][1]);
        }

        fprintf(fp,"\n");
    }

    fclose(fp);
}

void loadBookings(){
    FILE *fp=fopen("bookings.txt","r");
    if(!fp) return;

    fscanf(fp,"%d",&bookingCount);

    maxBookings=bookingCount+10;
    bookings=malloc(maxBookings*sizeof(Booking));

    for(int i=0;i<bookingCount;i++){
        fscanf(fp,"%s %s %s %d %f",
               bookings[i].customerName,
               bookings[i].movieName,
               bookings[i].showTime,
               &bookings[i].seatCount,
               &bookings[i].totalCost);

        for(int j=0;j<bookings[i].seatCount;j++){
            fscanf(fp,"%d %d",
                   &bookings[i].seats[j][0],
                   &bookings[i].seats[j][1]);
        }

        int movieIndex=findMovieIndex(bookings[i].movieName);
        int showIndex=-1;

        for(int k=0;k<3;k++){
            if(strcmp(movies[movieIndex].showTimes[k],bookings[i].showTime)==0){
                showIndex=k; break;
            }
        }

        for(int j=0;j<bookings[i].seatCount;j++){
            int r=bookings[i].seats[j][0];
            int c=bookings[i].seats[j][1];
            movies[movieIndex].seats[showIndex][r][c]='O';
        }
    }

    fclose(fp);
}


