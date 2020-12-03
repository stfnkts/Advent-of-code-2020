#define PASSWORDMAXLENGTH 255       //the maximum length of a password in the input

void readandSolveday2a();
void readandSolveday2b();

void day2a() {
    openInputFile("day2.txt");
    readandSolveday2a();
    closeFile(input);
}

void day2b() {
    openInputFile("day2.txt");
    readandSolveday2b();
    closeFile(input);
}

void readandSolveday2a() {
    int result = 0;

    while(!feof(input)) {
        int counter = 0;
        int minRange;
        int maxRange;
        char character;
        char password[PASSWORDMAXLENGTH];

        fscanf(input, "%d-%d %c: %s", &minRange, &maxRange, &character, password);
        for(uint8_t loc = 0; loc <= strlen(password); loc++) {
            if(password[loc] == character) {
                counter++;
            }
        }
        if(counter >= minRange && counter <= maxRange) {
            result++;
        }
    }
    printf("%d", result);
}

void readandSolveday2b() {
    int result = 0;

    while(!feof(input)) {
        int placeA;
        int placeB;
        int check = 0;
        char character;
        char password[PASSWORDMAXLENGTH];

        fscanf(input, "%d-%d %c: %s\n", &placeA, &placeB, &character, password);
        if(password[placeA-1] == character) {
            check++;
        }
        if(password[placeB-1] == character) {
            check++;
        }
        if(check == 1) {
            result++;
        }
    }
    printf("%d", result);
}
