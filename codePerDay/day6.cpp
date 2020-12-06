#define INPUTLOCATION6 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day6.txt"      //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!

uint8_t amountYes(uint8_t quesYes[]);
uint8_t amountYes(uint8_t quesYes[], uint8_t amPeople);

void day6a() {
    uint16_t result = 0;
    char curChar;
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t quesYes[26];

    openInputFile(INPUTLOCATION6);

    for (int i = 0; i < 26; i++) {
        quesYes[i] = 0;
    }
    while(!feof(input)) {
        curChar = fgetc(input);
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            if(dubbleEnter == 2) {
                result = result + amountYes(quesYes);
                for (int i = 0; i < 26; i++) {  //resetting every question as not answered "yes"
                    quesYes[i] = 0;
                }
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar >= 'a' && curChar <= 'z') {
            quesYes[curChar - 'a']++;           //highing up the right value
        }
    }
    result = result + amountYes(quesYes);
    printf("%d", result);
    closeFile(input);
}

void day6b() {
    uint16_t result = 0;
    char curChar;                   //to put the current character in
    uint8_t dubbleEnter = 0;        //when 2 enters are placed, a whiteline is created, a variable is needed to check this.
    uint8_t quesYes[26];            //every location in the array is a question.
    uint8_t amPeople = 0;

    openInputFile(INPUTLOCATION6);

    for (int i = 0; i < 26; i++) {
        quesYes[i] = 0;
    }
    while(!feof(input)) {
        curChar = fgetc(input);
        if(curChar == '\n') {               // /n stands for an enter
            dubbleEnter++;
            if(dubbleEnter == 2) {
                result = result + amountYes(quesYes, amPeople);
                for (int i = 0; i < 26; i++) {
                    quesYes[i] = 0;         //resetting every question as not answered "yes"
                }
                amPeople = 0;               //resetting amount of people in a group
            } else {
                amPeople++;                 //more people in the group
            }
        } else {
            dubbleEnter = 0;
        }
        if(curChar >= 'a' && curChar <= 'z') {
            quesYes[curChar - 'a']++;
        }
    }
    result = result + amountYes(quesYes, amPeople+1);       //at the end there isn't an '\n', which means the amount of people is 1 too low.
    printf("%d", result);
    closeFile(input);
}

uint8_t amountYes(uint8_t quesYes[]) {
    uint8_t result = 0;
    for(uint8_t i = 0; i < 26; i++) {
        if(quesYes[i]) {                    //if the question is answered "yes" at least once, it's valid and counts
            result++;
        }
    }
    return result;
}

uint8_t amountYes(uint8_t quesYes[], uint8_t amPeople) {
    uint8_t result = 0;
    for(uint8_t i = 0; i < 26; i++) {
        if(quesYes[i] == amPeople) {        //here, the amount of answers "yes" has to be the same as the amount of people. only then it counts.
            result++;
        }
    }
    return result;
}
