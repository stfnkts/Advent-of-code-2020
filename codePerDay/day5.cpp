#define INPUTLOCATION5 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day5.txt"       //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!

uint16_t getSeatID(char data[]);

void day5a() {
    uint16_t curID;
    uint16_t result = 0;
    char data[10];

    openInputFile(INPUTLOCATION5);
    while(!feof(input)) {
        fscanf(input, "%s", data);          //the data always has the format of 1 string
        curID = (getSeatID(data));
        if(curID > result) {    //if the current ID is higher than the result, the result should be updated.
            result = curID;
        }
    }
    printf("%d", result);
    closeFile(input);
}

void day5b() {
    uint16_t result;
    char data[10];
    uint8_t avail[128*8+8];             //all seatIDs

    for(int id = 0; id < 128*8+8; id++) {   //all are available, so all are set to available
        avail[id] = 1;
    }
    openInputFile(INPUTLOCATION5);
    while(!feof(input)) {
        fscanf(input, "%s", data);
        avail[getSeatID(data)]= 0;          //every seat in the input is used, so these should be set to unavailable
    }
    for(int r = 0; r < 128*8+8; r++) {
        if(avail[r] && !avail[r+1] && !avail[r-1]) {//if an ID is available but the ones next to it not, this is the seat you're looking for
            result = r;
            break;
        }
    }
    printf("%d", result);
    closeFile(input);
}

uint16_t getSeatID(char data[]) {
    uint16_t seatID;
    uint8_t minRow = 0;
    uint8_t maxRow = 127;
    uint8_t row;
    uint8_t minCol = 0;
    uint8_t maxCol = 7;
    uint8_t col;

    for(int r = 0; r < 6; r++) {         //the first 6 characters give which row at lowest and which row at highest
        if(data[r] == 'B') {
            minRow = minRow + (ceil((maxRow+1 - minRow) / 2));
        } else if(data[r] == 'F') {
            maxRow = maxRow - (floor((maxRow+1 - minRow) / 2));
        }
    }
    if(data[6] == 'F') {                //the 7th determine if it's the low or the high part
        row = minRow;
    } else if(data[6] == 'B') {
        row = maxRow;
    }
    for(int c = 7; c < 9; c++) {        //same is done with the columns
        if(data[c] == 'R') {
            minCol = minCol + (ceil((maxCol+1 - minCol) / 2));
        } else if(data[c] == 'L') {
            maxCol = maxCol - (floor((maxCol+1 - minCol) / 2));
        }
    }
    if(data[9] == 'L') {
        col = minCol;
    } else if(data[9] == 'R') {
        col = maxCol;
    }
    seatID = row * 8 + col;     //the ID is the row multiplied by 8, column then added
    return seatID;
}
