#define FIELDLENGTH 323     //length (up-down)
#define FIELDWIDTH 31       //width (left - right)

char field[FIELDLENGTH][FIELDWIDTH];
void createField();
int slope(int placementRow, int placementCol);

void day3a() {
    openInputFile("day3.txt");
    createField();
    printf("%d", slope(1, 3));
    closeFile(input);
}

void day3b() {
    openInputFile("day3.txt");
    createField();
    printf("%d", slope(1, 1) * slope(1, 3) * slope(1, 5) * slope(1, 7) * slope(2, 1));
    closeFile(input);
}

void createField() {
    char buffer[FIELDWIDTH];
    int row = 0;

    while(!feof(input)) {
        fscanf(input, "%s", buffer);
        for(uint8_t cur = 0; cur <= strlen(buffer); cur++) {
            field[row][cur] = buffer[cur];
        }
        row++;
    }
}

int slope(int placementRow, int placementCol) {
    int result = 0;
    int currow = 0;
    int curcol = 0;
    while(currow < FIELDLENGTH){
        if(field[currow][curcol] == '#') {
            result++;
        }
        currow = currow + placementRow;
        curcol = curcol + placementCol;
        if(curcol >= FIELDWIDTH) {
            curcol = curcol - FIELDWIDTH;
        }
    }
    return (result);
}
