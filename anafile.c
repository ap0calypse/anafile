#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>

/*******************************************************************************

    project:    anafile
    author:     Manuel Fill (ap0calypse@agitatio.org)
    purpose:    reads in a file and prints out information about every
                character in the file. supports UTF-8.

*******************************************************************************/

char *get_binary(wint_t number) {
    int numbits = sizeof(wint_t) * 8;
    int i;
    char *binstuff;
    binstuff = (char *) malloc(numbits+1);

    for (i = numbits - 1; i >= 0; --i) {
        if (((double) number - (pow(2,i))) < 0) {
            binstuff[i] = '0';
        }
        else if (((double) number - (pow(2,i))) == 0) {
            binstuff[i] = '1';
            number = 0;
        }
        else {
            binstuff[i] = '1';
            number = (double) number - (pow(2,i));
        }
    }

    binstuff[numbits] = '\0';
    return binstuff;
}

int main(int argc, char *argv[]) {
    char *filename;
    wchar_t character;
    FILE *infd;
    
    setlocale(LC_ALL, "");

    argc == 2 ? filename = argv[1] : exit(1);
    infd = fopen(filename, "rb, ccs=UNICODE");

    wprintf(L"\n# analysis of file: %s\n\n", filename);
    wprintf(L"%32s %10s %8s %s\n", "BINARY              ", "DECIMAL", "HEX   ", "CHARACTER");
    
    while ((character = fgetwc(infd)) != WEOF) {
        switch(character) {
            case 10:
                wprintf(L"%32s %10d %08X \\n\n", get_binary(character), character, character);
            break;
            case 32:
                wprintf(L"%32s %10d %08X SPACE\n", get_binary(character), character, character);
            break;
            case 9:
                wprintf(L"%32s %10d %08X \\t\n", get_binary(character), character, character);
            break;
            default:
                wprintf(L"%32s %10d %08X %lc\n", get_binary(character), character, character, character);
        }
    }
    close(infd);
}
