#define FIELDLENGTH 323     //length (up-down)
#define FIELDWIDTH 31       //width (left - right)
#define INPUTLOCATION3 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day3.txt"       //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!
char field[FIELDLENGTH][FIELDWIDTH];
void createField();
uint16_t slope(uint8_t placementRow, uint8_t placementCol);

void day3a() {
    openInputFile(INPUTLOCATION3);
    createField();              //creates the field from the input file
    printf("%d", slope(1, 3));  //prints result
    closeFile(input);
}

void day3b() {
    openInputFile(INPUTLOCATION3);
    createField();
    printf("%d", slope(1, 1) * slope(1, 3) * slope(1, 5) * slope(1, 7) * slope(2, 1)); //result was multiply multiple numbers
    closeFile(input);
}

void createField() {
    char buffer[FIELDWIDTH];
    uint16_t row = 0;

    while(!feof(input)) {
        fscanf(input, "%s", buffer);
        for(uint8_t cur = 0; cur <= strlen(buffer); cur++) {
            field[row][cur] = buffer[cur];
        }
        row++;
    }
}

uint16_t slope(uint8_t placementRow, uint8_t placementCol) {
    uint16_t result = 0;
    int currow = 0;
    int curcol = 0;
    while(currow < FIELDLENGTH){    //if currow exceeds the fieldlength, the bottom has reached.
        if(field[currow][curcol] == '#') {  //if this location has an #, you'll hit a tree.
            result++;
        }
        currow = currow + placementRow; //go down the specific amount of rows
        curcol = curcol + placementCol; //go right the specific amount of columns
        if(curcol >= FIELDWIDTH) {
            curcol = curcol - FIELDWIDTH; //the field has the same pattern farther to the right, this put it at the right place in the field again.
        }
    }
    return (result);
}
