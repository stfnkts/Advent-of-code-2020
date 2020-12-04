uint8_t validityCheck(uint8_t checking);

void day4a() {
    uint16_t result = 0;
    char curChar;               //variable to put the current character in
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t present = 0;
    uint8_t ident = 1;          //the first 3 letters are identifier, this variable is to check if the line is in an identifier position or elsewhere
    char identifier[4];         //place to save the identifier
    uint8_t loc = 0;

    identifier[3] = '\0';       //the final character of a string is an \0. That's sorted here

    openInputFile("day4.txt");
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
            }
            if(!strcmp("iyr", identifier)) {
                present = present | 0b00000010;
            }
            if(!strcmp("eyr", identifier)) {
                present = present | 0b00000100;
            }
            if(!strcmp("hgt", identifier)) {
                present = present | 0b00001000;
            }
            if(!strcmp("hcl", identifier)) {
                present = present | 0b00010000;
            }
            if(!strcmp("ecl", identifier)) {
                present = present | 0b00100000;
            }
            if(!strcmp("pid", identifier)) {
                present = present | 0b01000000;
            }
            if(!strcmp("cid", identifier)) {
                present = present | 0b10000000;
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
}

void day4b() {

}

uint8_t validityCheck(uint8_t checking) {
    if(checking == 0b11111111 || checking == 0b01111111) {//if true: all data is available or all data except the CID data
        return 1;

    } else {
        return 0;
    }
}
