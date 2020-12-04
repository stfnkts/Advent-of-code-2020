#define INPUTLOCATION4 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day4.txt"       //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!

uint8_t validityCheck(uint8_t checking);
uint8_t dataCheck(uint8_t identifier, char data[]);

void day4a() {
    uint16_t result = 0;
    char curChar;               //variable to put the current character in
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t present = 0;
    uint8_t ident = 1;          //the first 3 letters are identifier, this variable is to check if the line is in an identifier position or elsewhere
    char identifier[4];         //place to save the identifier
    uint8_t loc = 0;

    identifier[3] = '\0';       //the final character of a string is an \0. That's sorted here

    openInputFile(INPUTLOCATION4);
    while(!feof(input)) {
        curChar = fgetc(input);             //the file will be go through character by character
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            ident = 1;                      //following will be an identifier
            if(dubbleEnter == 2) {
                if(validityCheck(present)) {//if this is true, the needed data is all available.
                    result++;
                }
                present = 0;
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar == ' ') {                //after a space, identifier follows
            ident = 1;
        }
        if(curChar == ':') {                    //identifier finished, checking which identifier it actually is.
            ident = 0;
            if(!strcmp("byr", identifier)) {    //strcmp returns 0 when strings are equal to each other
                present = present | 0b00000001;
            } else if(!strcmp("iyr", identifier)) {
                present = present | 0b00000010;
            } else if(!strcmp("eyr", identifier)) {
                present = present | 0b00000100;
            } else if(!strcmp("hgt", identifier)) {
                present = present | 0b00001000;
            } else if(!strcmp("hcl", identifier)) {
                present = present | 0b00010000;
            } else if(!strcmp("ecl", identifier)) {
                present = present | 0b00100000;
            } else if(!strcmp("pid", identifier)) {
                present = present | 0b01000000;
            } else if(!strcmp("cid", identifier)) {
                present = present | 0b10000000;
            } else {
                printf("UNKNOWN IDENTIFIER\n");
            }
            loc = 0;
            //every identifier got it's own bit in the present variable
        }
        if(curChar != ' ' && curChar != ':' && curChar != '\n' && ident) {//if this is true, the character is a letter, and it's definitly an identifier, so it will be saved in the identifier buffer.
            identifier[loc] = curChar;
            loc++;
        }
    }
    if(validityCheck(present)) { //just to check the last one :D
        result++;
    }
    printf("%d", result);
    closeFile(input);
}

void day4b() {
    uint16_t result = 0;
    char curChar;               //variable to put the current character in
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t curID = 0;
    char data[255];
    uint8_t ident = 1;          //the first 3 letters are identifier, this variable is to check if the line is in an identifier position or elsewhere
    char identifier[4];         //place to save the identifier
    uint8_t loc = 0;
    uint8_t valid = 0;

    identifier[3] = '\0';       //the final character of a string is an \0. That's sorted here

    openInputFile(INPUTLOCATION4);
    while(!feof(input)) {
        curChar = fgetc(input);             //the file will be go through character by character
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            ident = 1;                      //following will be an identifier
            if(dubbleEnter == 2) {
                if(validityCheck(valid)) {//if this is true, the needed data is all available.
                    result++;
                }
                valid = 0;                  //reset
                curID = 0;

            } else {
                data[loc] = '\0';
                loc = 0;
                if(dataCheck(curID, data)) {    //check if the data is valid, if so, set the right bit.
                    valid = valid | curID;
                }
                curID = 0;
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar == ' ') {                //after a space, identifier follows
            ident = 1;
            data[loc] = '\0';
            loc = 0;
                if(dataCheck(curID, data)) {    //check if the data is valid
                    valid = valid | curID;
                }
                curID = 0;
        }
        if(curChar == ':') {                    //identifier finished, checking which identifier it actually is.
            ident = 0;
            if(!strcmp("byr", identifier)) {    //strcmp returns 0 when strings are equal to each other
                curID = curID | 0b00000001;
            } else if(!strcmp("iyr", identifier)) {
                curID = curID | 0b00000010;
            } else if(!strcmp("eyr", identifier)) {
                curID = curID | 0b00000100;
            } else if(!strcmp("hgt", identifier)) {
                curID = curID | 0b00001000;
            } else if(!strcmp("hcl", identifier)) {
                curID = curID | 0b00010000;
            } else if(!strcmp("ecl", identifier)) {
                curID = curID | 0b00100000;
            } else if(!strcmp("pid", identifier)) {
                curID = curID | 0b01000000;
            } else if(!strcmp("cid", identifier)) {
                curID = curID | 0b10000000;
            } else {
                printf("UNKNOWN IDENTIFIER\n");
            }
            loc = 0;
            //every identifier got it's own bit in the curID variable
        }
        if(curChar != ' ' && curChar != ':' && curChar != '\n' && ident) {//if this is true, the character is a letter, and it's definitly an identifier, so it will be saved in the identifier buffer.
            identifier[loc] = curChar;
            loc++;
        } else if(curChar != ' ' && curChar != ':' && curChar != '\n' && !ident) {
            data[loc] = curChar;
            loc++;
        }
    }
    if(validityCheck(valid)) { //just to check the last one :D
        result++;
    }
    printf("%d", result);
    closeFile(input);
}


uint8_t validityCheck(uint8_t checking) {
    if(checking == 0b11111111 || checking == 0b01111111) {//if true: all data is available or all data except the CID data
        return 1;

    } else {
        return 0;
    }
}

uint8_t dataCheck(uint8_t identifier, char data[]) {
    if(identifier == 0b00000001) {                      //byr, check if value is between the given timespan
        if(atoi(data) >= 1920 && atoi(data) <= 2002 ) {
            return 1;
        }
    } else if(identifier == 0b00000010) {               //iyr, check if value is between the given timespan
        if(atoi(data) >= 2010 && atoi(data) <= 2020) {
            return 1;
        }
    } else if(identifier == 0b00000100) {               //eyr, check if value is between the given timespan
        if(atoi(data) >= 2020 && atoi(data) <= 2030) {
            return 1;
        }
    } else if(identifier == 0b00001000) {
        if(strlen(data) == 4) {                         //if data has 4 characters, inches are used
            if(data[2] == 'i' && data[3] == 'n') {
                if(atoi(data) >= 59 && atoi(data) <= 76) {
                    return 1;
                }
            }
        } else if(strlen(data) == 5) {                  //if data has 5 characters, centimeters are used
            if(data[3] == 'c' && data[4] == 'm') {
                if(atoi(data) >= 150 && atoi(data) <= 193) {
                    return 1;
                }
            }
        }
    } else if(identifier == 0b00010000) {
        if(data[0] == '#') {                            //starts with #
            if(data[7] == '\0') {                       //enough characters
                uint8_t pass = 0;
                for(int i = 1; i<=6; i++) {
                    if((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'a' && data[i] <= 'f')) { //between 0 to 9 OR between a and f
                        pass++;
                    }
                }
                if(pass == 6) {//all passed (if not -> invalid)
                    return 1;
                }
            }
        }
    } else if(identifier == 0b00100000) {                  //ecl, if one of these values it's good, otherwise fail
        if(!strcmp(data, "amb") || !strcmp(data, "blu") || !strcmp(data, "brn") || !strcmp(data, "gry") || !strcmp(data, "grn") || !strcmp(data, "hzl") || !strcmp(data, "oth")) {
            return 1;
        }
    } else if(identifier == 0b01000000) {               //pid 9 numbers
        if(strlen(data) == 9) {
            uint8_t pass = 0;
            for(uint8_t i = 0; i < strlen(data); i++) {
                if(data[i] >= '0' && data[i] <= '9') {
                    pass++;
                }
            }
            if(pass == 9) {
                return 1;
            }
        }
    } else if(identifier == 0b10000000) {               //just ignore, passed.
        return 1;
    }
    return 0;               //if the function reaches this, all have failed, so data is not valid
}
