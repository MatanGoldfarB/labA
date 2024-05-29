#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
  if(argc >= 2){
    int pos = 2;
    int len = strlen(argv[1])-2;
    int enc, factor=0;
    FILE *inFile = stdin;
    FILE *outFile = stdout;
    bool debug = true;
    for(int i=1; i < argc; i++){
      if(debug){
        if(strncmp(argv[i], "-D", 2) == 0){
          debug = false;
        }
        else{
          fprintf(stderr, "'%s'\n", argv[i]);
        }
      }
      if(strncmp(argv[i], "+e", 2) == 0){
        factor = 1;
      }
      else if(strncmp(argv[i], "-e", 2) == 0){
        factor = -1;
      }
      else if(strncmp(argv[i], "+D", 2) == 0){
        debug = true;
      }
      else if(strncmp(argv[i], "-I", 2) == 0){
        inFile = fopen(argv[i]+2,"r");
        if(inFile==NULL){
          fprintf(stderr, "Error: Failed to open input file '%s' for reading.\n", argv[i] + 2);
          exit(1);
        }
      }
      else if(strncmp(argv[i], "-O", 2) == 0){
        outFile = fopen(argv[i]+2,"w");
        if(outFile==NULL){
          fprintf(stderr, "Error: Failed to open output file '%s' for writing.\n", argv[i] + 2);
          exit(1);
        }
      }
    }
    int ch;
    while ((ch = fgetc(inFile)) != EOF) {
      if (ch != '\n') { // Check if the character is not a newline
        if (ch >= 'a' && ch <= 'z'){
          char str[2];
          str[0] = argv[1][pos];
          str[1] = '\0';
          enc = (ch - 'a' + factor*atoi(str)) % 26 + 'a';
        }
        else if(ch >= '0' && ch <= '9'){
          char str[2];
          str[0] = argv[1][pos];
          str[1] = '\0';
          enc = (ch - '0' + factor*atoi(str)) % 10 + '0';
        }
        else{
          enc = ch;
        }
        fputc(enc, outFile); // Output character to stdout
      } else {
        fputc('\n', outFile); // Output newline character as is
      }
      pos = ((pos-1)%len) + 2;
    }
    fflush(outFile); // Flush stdout to ensure immediate printing
    if(inFile!=stdin){
      fclose(inFile);
    }
    if(outFile!=stdout){
      fclose(outFile);
    }
  }
  return 0;
}