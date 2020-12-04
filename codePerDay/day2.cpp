#define PASSWORDMAXLENGTH 255       //the maximum length of a password in the input
#define INPUTLOCATION2 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day2.txt"       //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!
void readandSolveday2a();
void readandSolveday2b();

void day2a() {
    openInputFile(INPUTLOCATION2);
    readandSolveday2a();
    closeFile(input);
}

void day2b() {
    openInputFile(INPUTLOCATION2);
    readandSolveday2b();
    closeFile(input);
}

void readandSolveday2a() {
    uint16_t result = 0;

    while(!feof(input)) {
        uint16_t counter = 0;
        int minRange;
        int maxRange;
        char character;
        char password[PASSWORDMAXLENGTH];

        fscanf(input, "%d-%d %c: %s", &minRange, &maxRange, &character, password);      //every line has this specific layout.
        for(uint8_t loc = 0; loc <= strlen(password); loc++) {
            if(password[loc] == character) {                //if a character in the password matches with the character searched for, add the counter
                counter++;
            }
        }
        if(counter >= minRange && counter <= maxRange) { //if in the range, valid.
            result++;
        }
    }
    printf("%d", result);
}

void readandSolveday2b() {
    uint16_t result = 0;

    while(!feof(input)) {
        int placeA;
        int placeB;
        uint8_t check = 0;
        char character;
        char password[PASSWORDMAXLENGTH];

        fscanf(input, "%d-%d %c: %s\n", &placeA, &placeB, &character, password); //every line has this specific layout.
        if(password[placeA-1] == character) {   //an array starts with counting from 0, the input starts at 1, so inputvalue-1 to get the right letter.
            check++;
        }
        if(password[placeB-1] == character) {
            check++;
        }
        if(check == 1) {    //if 1, on place A or place B the right character is found. if 0 or 2, both or none, so invalid
            result++;
        }
    }
    printf("%d", result);
}
