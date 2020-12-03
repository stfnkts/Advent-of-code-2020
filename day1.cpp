#define VALUEAMOUNT 200 //the amount of values in the input data
#define TARGETVALUE 2020    //the value which the addition is targeted at
int values[VALUEAMOUNT];

void readToArrayday1();


void day1a() {
    openInputFile("day1.txt");          //open inputfile with data
    int found = 0;
    int numA;
    int numB;

    readToArrayday1();                  //put all input data into an array
    for(int A = 0; A<VALUEAMOUNT; A++) {
        numA = values[A];
        for(int B = 0; B<VALUEAMOUNT; B++) {
            numB = values[B];
            if(numA + numB == TARGETVALUE) {
                found++;
                break;
            }
        }
        if(found) {
            break;
        }
    }
    printf("%d", numA * numB);
    closeFile(input);
}

void day1b() {
    openInputFile("day1.txt");
    int found = 0;
    int numA;
    int numB;
    int numC;

    readToArrayday1();
    for(int A = 0; A<VALUEAMOUNT; A++) {
        numA = values[A];
        for(int B = 0; B<VALUEAMOUNT; B++) {
            numB = values[B];
            for(int C = 0; C<VALUEAMOUNT; C++) {
                numC = values[C];
                if(numA + numB + numC == TARGETVALUE) {
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
    printf("%d", numA * numB * numC);
    closeFile(input);
}

void readToArrayday1() {
    int i = 0;
    while((fscanf(input,"%d",&values[i]))!=EOF) { //read file, put number values into array
        i++;
    }
}

