#define INPUTLOCATION8 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day8.txt"      //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!
int hadInstruction[1000];
int curIns;
bool infinite = false;
int accumulator;
int chIns = 0;


void nop();
void acc(char op, int value);
void jmp(char op, int value);

void day8a() {
    for(int i = 0; i < 1000; i++) {
        hadInstruction[i] = 0;
    }
    accumulator = 0;
    curIns = 0;
    char instruction[255];
    openInputFile(INPUTLOCATION8);
    while(!infinite) {
        fscanf(input, "%s ", instruction);
        if(!strcmp(instruction, "nop")) {
            nop();
        } else if(!strcmp(instruction, "acc")) {
            char operation = fgetc(input);
            int value;
            fscanf(input, "%d", &value);
            acc(operation, value);
        } else if(!strcmp(instruction, "jmp")) {
            char operation = fgetc(input);
            int value;
            fscanf(input, "%d", &value);
            jmp(operation, value);
        }
    }
    printf("%d", accumulator);
    closeFile(input);
}

void day8b() {
    infinite = false;
    for(int i = 0; i < 1000; i++) {
        hadInstruction[i] = 0;
    }
    accumulator = 0;
    curIns = 0;
    char instruction[255];
    openInputFile(INPUTLOCATION8);
    while(!infinite && !feof(input)) {

        fscanf(input, "%s ", instruction);
        if(!strcmp(instruction, "nop")) {
            if(curIns == chIns) {
                char operation = fgetc(input);
                int value;
                fscanf(input, "%d", &value);
                jmp(operation, value);
            } else {
                nop();
            }

        } else if(!strcmp(instruction, "acc")) {
            char operation = fgetc(input);
            int value;
            fscanf(input, "%d", &value);
            acc(operation, value);
        } else if(!strcmp(instruction, "jmp")) {
            if(curIns == chIns){
                nop();
            } else {
                char operation = fgetc(input);
                int value;
                fscanf(input, "%d", &value);
                jmp(operation, value);
            }

        }
    } if(feof(input)) {
        printf("%d", accumulator);
        closeFile(input);
    } else{
        closeFile(input);
        chIns++;
        day8b();
    }

}

void nop() {
    hadInstruction[curIns]++;
    if(hadInstruction[curIns] > 1) {
        infinite = true;
        return;
    }
    while(fgetc(input) != '\n');
    curIns++;
}

void acc(char  op, int value) {
    hadInstruction[curIns]++;
    if(hadInstruction[curIns] > 1) {
        infinite = true;
        return;
    }
    if(op == '+') {
        accumulator = accumulator + value;
    } else if(op == '-') {
        accumulator = accumulator - value;
    }
    curIns++;
}

void jmp(char op, int value) {
    hadInstruction[curIns]++;
    if(hadInstruction[curIns] > 1) {
        infinite = true;
        return;
    }
    int goLine;
    if(op == '+') {
        goLine = curIns + value;
        rewind(input);
        for(int i = 0; i < goLine; i++) {
            fscanf(input, "%*s %*s");
        }
    } else if(op == '-') {
        goLine = curIns - value;
        rewind(input);
        for(int i = 0; i < goLine; i++) {
            fscanf(input, "%*s %*s");
        }
    } else {
        goLine = curIns++;
    }
    curIns = goLine;
}
