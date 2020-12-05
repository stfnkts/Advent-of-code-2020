FILE *input;

void openInputFile(const char* inputfile) {
    input = fopen(inputfile, "r");
    if(input == NULL) { //Check if file opened properly
        perror("Failed to open input file");
        exit(0x1);
    }
}

void closeFile(FILE* file) {
    if(fclose(file)) {              //Check if file closed properly
        perror("Failed to open input file");
        exit(0XA);
    }
}
