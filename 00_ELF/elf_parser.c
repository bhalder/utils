#include <stdio.h>

int main( int argc, char *argv[] ) {

    FILE * fp = NULL;
    if( argc != 2 ) {
        printf("Error. Usage ./elf_parser <binary>\n");
        return 0;
    }

    fp = fopen(argv[1], "r" );
    if( fp == NULL ) {
        printf("Error. File not found.\n");
        return;
    }
}
