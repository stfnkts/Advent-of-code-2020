FILE *input;

void openInputFile(const char* inputfile) {
    input = fopen(inputfile, "r");
    if(input == NULL) { //Check if file opened properly
        perror("Failed to open input file");
    }
}

void closeFile(FILE* file) {
    if(fclose(file)) {              //Check if file closed properly
        printf("Failed to close file\n");
        perror("Failed to open input file");
    }
}
