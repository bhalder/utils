#include <stdio.h>
#include <string.h>

// Important macros for ELF parsing
#define MAG0 0x00 // 7F
#define MAG1 0x01 // 'E'
#define MAG2 0x02 // 'L'
#define MAG3 0x03 // 'F'

#define CLASS 0x04 // 32-bit or 64-bit
#define DATA 0x05 // Endianess 1 : Little, 2 : Big
#define VER 0x06 // Version 1 : Original version of ELF
#define OS_ABI 0x07 // OS type
// Skipping a few
#define TYPE 0x10 // 1 : Relocatable, 2 : Executable, 3 : Shared, 4 : Core
#define ENTRY 0x18 // Entry point of the program
#define HEAD32 0x1C // 32 bit address of program header
#define HEAD64 0x20 // 64 bit address of program header

int main( int argc, char *argv[] ) {

    FILE * fp = NULL;
    if( argc != 3 ) {
        printf("Error. Usage ./elf_parser <binary> <flag>\n");
        return 0;
    }

    fp = fopen(argv[1], "rwb" );
    if( fp == NULL ) {
        printf("Error. File not found.\n");
        return;
    }

    unsigned char buffer[4096]; // Buffer to hold the inital 1024 bytes of Binary
    // We shall parse whatever is there in this 1024 bytes

    int i = 0;
    int j = 0;


    if( strcmp( argv[2], "--dump") == 0 || strcmp( argv[2], "-d" ) == 0 ) {
        while( fread( buffer, 1, 4096, fp  ) > 0 ) { 
            for( i = 0; i < 4096; i++ ) {
                if( j == 0 ) {
                    printf("[%4x]   ", (unsigned int) (&buffer[i] - &buffer[0]));
                }
                if( 0x21 <= buffer[i] && buffer[i] <= 0x7E  ) 
                    printf("%2c",buffer[i]);
                else
                    printf("%2.2x", buffer[i]);
                printf(" ");
                j++;
                if( j == 8 ) {
                    printf("\n");
                    j = 0;
                }
            }
        }
        printf("\n\n");
        return 0;
    } else if ( strcmp( argv[2], "--parse" ) == 0 || strcmp( argv[2], "-p") == 0 ) {
        fread( buffer, 1, 4096, fp  );
        unsigned char * elf_address = strstr( buffer, "ELF");
        int start_index = elf_address - buffer;
        printf("MAGIC NUMBER : %2x\n", buffer[0]);
        int type = (unsigned int ) buffer[4];
        unsigned long entry_point = 0;
        if( type == 0 ) {
            entry_point = *((unsigned long *) &buffer[ENTRY]);
            printf("TYPE : 32-bit\n");
        } else {
            entry_point = *((unsigned long *) &buffer[ENTRY]);
            printf("TYPE : 64-bit\n");
        } 

        printf("ENTRY POINT : %x", entry_point);

                
        printf("\n");
        return 0;
    } 
}
