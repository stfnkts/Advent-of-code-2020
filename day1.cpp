#define VALUEAMOUNT 200 //the amount of values in the input data
#define TARGETVALUE 2020    //the value which the addition is targeted at
int values[VALUEAMOUNT];

void readToArrayday1();


void day1a() {
    openInputFile("day1.txt");          //open inputfile with data
    uint8_t found = 0;
    uint16_t numA;
    uint16_t numB;

    readToArrayday1();                  //put all input data into an array
    for(int A = 0; A<VALUEAMOUNT; A++) {        //every for loop to go along all possible combinations.
        numA = values[A];
        for(int B = 0; B<VALUEAMOUNT; B++) {
            numB = values[B];
            if(numA + numB == TARGETVALUE) {    //if true, the numbers are found. No need to move on in the loops, so break.
                found++;
                break;
            }
        }
        if(found) {
            break;
        }
    }
    printf("%d", numA * numB); //result had to be multiplied.
    closeFile(input);
}

void day1b() {
    openInputFile("day1.txt");
    uint8_t found = 0;
    uint16_t numA;
    uint16_t numB;
    uint16_t numC;

    readToArrayday1();
    for(int A = 0; A<VALUEAMOUNT; A++) {        //every for loop to go along all possible combinations.
        numA = values[A];
        for(int B = 0; B<VALUEAMOUNT; B++) {
            numB = values[B];
            for(int C = 0; C<VALUEAMOUNT; C++) {
                numC = values[C];
                if(numA + numB + numC == TARGETVALUE) { //if true, the numbers are found. No need to move on in the loops, so break.
                    found++;
                    break;
                }
            }
            if(found) {
                break;
            }
        }
        if(found) {
            break;
        }
    }
    printf("%d", numA * numB * numC); //for result, multiply the numbers
    closeFile(input);
}

void readToArrayday1() {
    uint16_t i = 0;
    while((fscanf(input,"%d",&values[i]))!=EOF) { //read file, put number values into array
        i++;
    }
}

