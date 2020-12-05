#define INPUTLOCATION4 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day4.txt"       //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!

uint8_t validityCheck(uint8_t checking);
uint8_t valueCheck(uint8_t key, char value[]);

void day4a() {
    uint16_t result = 0;
    char curChar;               //variable to put the current character in
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t present = 0;
    uint8_t ident = 1;          //the first 3 letters are the key, this variable is to check if the line is in an key position or elsewhere
    char key[4];         //place to save the key
    uint8_t loc = 0;

    key[3] = '\0';       //the final character of a string is an \0. That's sorted here

    openInputFile(INPUTLOCATION4);
    while(!feof(input)) {
        curChar = fgetc(input);             //the file will be go through character by character
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            ident = 1;                      //following will be an key
            if(dubbleEnter == 2) {
                if(validityCheck(present)) {//if this is true, the needed value is all available.
                    result++;
                }
                present = 0;
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar == ' ') {                //after a space, key follows
            ident = 1;
        }
        if(curChar == ':') {                    //key finished, checking which key it actually is.
            ident = 0;
            if(!strcmp("byr", key)) {    //strcmp returns 0 when strings are equal to each other
                present = present | 0b00000001;
            } else if(!strcmp("iyr", key)) {
                present = present | 0b00000010;
            } else if(!strcmp("eyr", key)) {
                present = present | 0b00000100;
            } else if(!strcmp("hgt", key)) {
                present = present | 0b00001000;
            } else if(!strcmp("hcl", key)) {
                present = present | 0b00010000;
            } else if(!strcmp("ecl", key)) {
                present = present | 0b00100000;
            } else if(!strcmp("pid", key)) {
                present = present | 0b01000000;
            } else if(!strcmp("cid", key)) {
                present = present | 0b10000000;
            } else {
                printf("UNKNOWN key\n");
            }
            loc = 0;
            //every key got it's own bit in the present variable
        }
        if(curChar != ' ' && curChar != ':' && curChar != '\n' && ident) {//if this is true, the character is a letter, and it's definitly an key, so it will be saved in the key buffer.
            key[loc] = curChar;
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
    char value[255];
    uint8_t ident = 1;          //the first 3 letters are key, this variable is to check if the line is in an key position or elsewhere
    char key[4];         //place to save the key
    uint8_t loc = 0;
    uint8_t valid = 0;

    key[3] = '\0';       //the final character of a string is an \0. That's sorted here

    openInputFile(INPUTLOCATION4);
    while(!feof(input)) {
        curChar = fgetc(input);             //the file will be go through character by character
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            ident = 1;                      //following will be an key
            if(dubbleEnter == 2) {
                if(validityCheck(valid)) {//if this is true, the needed value is all available.
                    result++;
                }
                valid = 0;                  //reset
                curID = 0;

            } else {
                value[loc] = '\0';
                loc = 0;
                if(valueCheck(curID, value)) {    //check if the value is valid, if so, set the right bit.
                    valid = valid | curID;
                }
                curID = 0;
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar == ' ') {                //after a space, key follows
            ident = 1;
            value[loc] = '\0';
            loc = 0;
                if(valueCheck(curID, value)) {    //check if the value is valid
                    valid = valid | curID;
                }
                curID = 0;
        }
        if(curChar == ':') {                    //key finished, checking which key it actually is.
            ident = 0;
            if(!strcmp("byr", key)) {    //strcmp returns 0 when strings are equal to each other
                curID = curID | 0b00000001;
            } else if(!strcmp("iyr", key)) {
                curID = curID | 0b00000010;
            } else if(!strcmp("eyr", key)) {
                curID = curID | 0b00000100;
            } else if(!strcmp("hgt", key)) {
                curID = curID | 0b00001000;
            } else if(!strcmp("hcl", key)) {
                curID = curID | 0b00010000;
            } else if(!strcmp("ecl", key)) {
                curID = curID | 0b00100000;
            } else if(!strcmp("pid", key)) {
                curID = curID | 0b01000000;
            } else if(!strcmp("cid", key)) {
                curID = curID | 0b10000000;
            } else {
                printf("UNKNOWN key\n");
            }
            loc = 0;
            //every key got it's own bit in the curID variable
        }
        if(curChar != ' ' && curChar != ':' && curChar != '\n' && ident) {//if this is true, the character is a letter, and it's definitly an key, so it will be saved in the key buffer.
            key[loc] = curChar;
            loc++;
        } else if(curChar != ' ' && curChar != ':' && curChar != '\n' && !ident) {
            value[loc] = curChar;
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
    if(checking == 0b11111111 || checking == 0b01111111) {//if true: all value is available or all value except the CID value
        return 1;

    } else {
        return 0;
    }
}

uint8_t valueCheck(uint8_t key, char value[]) {
    if(key == 0b00000001) {                      //byr, check if value is between the given timespan
        if(atoi(value) >= 1920 && atoi(value) <= 2002 ) {
            return 1;
        }
    } else if(key == 0b00000010) {               //iyr, check if value is between the given timespan
        if(atoi(value) >= 2010 && atoi(value) <= 2020) {
            return 1;
        }
    } else if(key == 0b00000100) {               //eyr, check if value is between the given timespan
        if(atoi(value) >= 2020 && atoi(value) <= 2030) {
            return 1;
        }
    } else if(key == 0b00001000) {
        if(strlen(value) == 4) {                         //if value has 4 characters, inches are used
            if(value[2] == 'i' && value[3] == 'n') {
                if(atoi(value) >= 59 && atoi(value) <= 76) {
                    return 1;
                }
            }
        } else if(strlen(value) == 5) {                  //if value has 5 characters, centimeters are used
            if(value[3] == 'c' && value[4] == 'm') {
                if(atoi(value) >= 150 && atoi(value) <= 193) {
                    return 1;
                }
            }
        }
    } else if(key == 0b00010000) {
        if(value[0] == '#') {                            //starts with #
            if(value[7] == '\0') {                       //enough characters
                uint8_t pass = 0;
                for(int i = 1; i<=6; i++) {
                    if((value[i] >= '0' && value[i] <= '9') || (value[i] >= 'a' && value[i] <= 'f')) { //between 0 to 9 OR between a and f
                        pass++;
                    }
                }
                if(pass == 6) {//all passed (if not -> invalid)
                    return 1;
                }
            }
        }
    } else if(key == 0b00100000) {                  //ecl, if one of these values it's good, otherwise fail
        if(!strcmp(value, "amb") || !strcmp(value, "blu") || !strcmp(value, "brn") || !strcmp(value, "gry") || !strcmp(value, "grn") || !strcmp(value, "hzl") || !strcmp(value, "oth")) {
            return 1;
        }
    } else if(key == 0b01000000) {               //pid 9 numbers
        if(strlen(value) == 9) {
            uint8_t pass = 0;
            for(uint8_t i = 0; i < strlen(value); i++) {
                if(value[i] >= '0' && value[i] <= '9') {
                    pass++;
                }
            }
            if(pass == 9) {
                return 1;
            }
        }
    } else if(key == 0b10000000) {               //just ignore, passed.
        return 1;
    }
    return 0;               //if the function reaches this, all have failed, so value is not valid
}
