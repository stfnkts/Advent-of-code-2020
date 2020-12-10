#define INPUTLOCATION7 "D:/ICT/CodeBlocks/projects/AoC2020/inputData/day7.txt"      //CHANGE THIS TO YOUR OWN LOCATION IF YOU USE IT!
#define MAXVER 1441
struct Rules *makeData(int n);
void makeColorID(uint16_t placeID);
void amBags(struct Rules *rule, int bagID);
int checkID(char Color[]);
void makeEdges();
void amountBags(struct Rules *rule, int bagID, int depth);

char colorID[594][255];
int containList[1441][3];
int posCon = 0;
int result;
int passed[594];

struct Rules {
    struct Bag* root[MAXVER];
};

struct Bag {
    int dest, amount;
    struct Bag* next;
};

struct Contain {
    int src, dest, amount;
};

void day7a() {
    result = 0;
    uint16_t placeID = 0;
    for (int i = 0; i < 594; i++) {
        passed[i] = 0;
    }
    char colorToSearch[] = "shiny gold";
    openInputFile(INPUTLOCATION7);
    while(!feof(input)) {
        makeColorID(placeID);
        placeID++;
    }
    rewind(input);
    while(!feof(input)) {
        makeEdges();
    }
    int n = sizeof(containList)/sizeof(containList[0]);
    struct Rules *rule = makeData(n);
    int searchColor = checkID(colorToSearch);
    amBags(rule, searchColor);
    printf("%d", result);
    closeFile(input);

}

void day7b() {
    result = 0;
    uint16_t placeID = 0;
    for (int i = 0; i < 594; i++) {
        passed[i] = 0;
    }
    char colorToSearch[] = "shiny gold";
    openInputFile(INPUTLOCATION7);
    while(!feof(input)) {
        makeColorID(placeID);
        placeID++;
    }
    rewind(input);
    while(!feof(input)) {
        makeEdges();
    }
    int n = sizeof(containList)/sizeof(containList[0]);
    struct Rules *rule = makeData(n);
    int searchColor = checkID(colorToSearch);
    amountBags(rule, searchColor, 1);
    printf("%d", result);
    closeFile(input);

}

struct Rules *makeData(int n) {
    struct Rules *rule = (struct Rules*)malloc(sizeof(struct Rules));
    for(unsigned i = 0; i < MAXVER; i++) {
        rule->root[i] = NULL;
    }
    for(int i = 0; i < n; i++) {
        int src = containList[i][0];
        int dest = containList[i][1];
        int amount = containList[i][2];
        struct Bag *newBag = (struct Bag*)malloc(sizeof(struct Bag));
        newBag->dest = dest;
        newBag->amount = amount;
        newBag->next = rule->root[src];
        rule->root[src] = newBag;
    }
    return rule;
}

void makeColorID(uint16_t placeID) {

    char curcolorpA[255];
    char curcolorpB[255];
    fscanf(input, "%s %s %*s %*s ", curcolorpA, curcolorpB);
    for(uint8_t i = 0; i < strlen(curcolorpA); i++) {
        colorID[placeID][i] = curcolorpA[i];
    }
    int len = strlen(curcolorpA);
    int pos = 0;
    colorID[placeID][len] = ' ';
    for (uint8_t i = len+1; i <= len+strlen(curcolorpB); i++){
        colorID[placeID][i] = curcolorpB[pos];
        pos++;
    }
    colorID[placeID][len+pos+1] = '\0';
    while(fgetc(input) != '.');
    if(fgetc(input) == EOF) {
        return;
    }
}

void makeEdges() {
    int curColorID;
    char curColor[255];
    char curcolorpA[255];
    char curcolorpB[255];
    fscanf(input, "%s %s %*s %*s ", curcolorpA, curcolorpB);
    for(uint8_t i = 0; i < strlen(curcolorpA); i++) {
        curColor[i] = curcolorpA[i];
    }
    int len = strlen(curcolorpA);
    int pos = 0;
    curColor[len] = ' ';
    for (uint8_t i = len+1; i <= len+strlen(curcolorpB); i++){
        curColor[i] = curcolorpB[pos];
        pos++;
    }
    curColor[len+pos+1] = '\0';
    curColorID = checkID(curColor);
    char temp;
    temp = fgetc(input);
    if(temp == 'n') {
        while(fgetc(input) != '\n');
    } else {
        int conColorID;
        char conColor[255];
        char concolorpA[255];
        char concolorpB[255];
        char tempb[255];
        fscanf(input, "%s %s %s", concolorpA, concolorpB, tempb);
        for(uint8_t i = 0; i < strlen(concolorpA); i++) {
            conColor[i] = concolorpA[i];
        }
        int len = strlen(concolorpA);
        int pos = 0;
        conColor[len] = ' ';
        for (uint8_t i = len+1; i <= len+strlen(concolorpB); i++){
            conColor[i] = concolorpB[pos];
            pos++;
        }
        conColor[len+pos+1] = '\0';
        conColorID = checkID(conColor);
        containList[posCon][0] = curColorID;
        containList[posCon][1] = conColorID;
        containList[posCon][2] = temp - '0';
        posCon++;
        while(tempb[3] == ',' || tempb[4] == ',') {
            int amount;
            fscanf(input, "%d %s %s %s", &amount, concolorpA, concolorpB, tempb);
            for(uint8_t i = 0; i < strlen(concolorpA); i++) {
                conColor[i] = concolorpA[i];
            }
            int len = strlen(concolorpA);
            int pos = 0;
            conColor[len] = ' ';
            for (uint8_t i = len+1; i <= len+strlen(concolorpB); i++){
                conColor[i] = concolorpB[pos];
                pos++;
            }
            conColor[len+pos+1] = '\0';
            conColorID = checkID(conColor);
            containList[posCon][0] = curColorID;
            containList[posCon][1] = conColorID;
            containList[posCon][2] = amount;
            posCon++;
        }
    }
}

int checkID(char Color[]) {
    for(int i = 0; i < 594; i++) {
        if(!strcmp(Color, colorID[i])){
            return i;
        }
    }
    return(-1);
}

void amBags(struct Rules *rule, int bagID) {
    for (int i = 0; i<MAXVER; i++){
        struct Bag *bag = rule->root[i];
        while(bag != NULL){
            int temp = bag->dest;
            if(temp == bagID) {
                if(!passed[i]) {
                    passed[i]++;
                    result++;
                    amBags(rule, i);
                }
            }
            bag = bag->next;
        }
    }
}

void amountBags(struct Rules *rule, int bagID, int depth) {

    for (int i = 0; i<MAXVER; i++){
        struct Bag *bag = rule->root[i];
        while(bag != NULL){
            int temp = bag->dest;
            if(temp == bagID) {
                if(!passed[i]) {
                    passed[i]++;
                    for(int j = 0; j < depth; j++) {
                        result = result; //...;
                    }
                    printf("%d: %d, %d (%d)\n", depth, i, temp, bag->amount);
                    amountBags(rule, i, depth++);
                }
            }
            bag = bag->next;
        }
    }
}
