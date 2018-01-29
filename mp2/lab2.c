/* lab2.c
 * Wenkang Wei
 * wenkanw
 * ECE 2220, Section1, Fall 2017
 * MP2
 *
 * Purpose:
 *          This program is to encrypte the input 16-digit hex plaintext with key and
 *          decode the given ciphertext with given key and signature.
 *          
 *          In encryption process, the  program take 16-digit hex plaintext and 2-digit hex 
 *          key as input and then generate the matching ciphertext and dynamic signature
 *          In decryption process, it is to generate the original plaintext using the input arguments
 *          ciphertext, key and signature and evaluate whether it is from trusted source 
 *
 *
 * Assumptions:
 *  #1:  The menu driven input is provided and must be used exactly
 *       as written.  A user can enter three commands, e.g.,:
 *            enc 0123456789abcdef 73
 *            dec f5fbc946ec523e08 73 F
 *            quit
 *       Encoding takes 16 hex digits for plaintext and 2 hex digits as the key
 *       Decoding takes 16 hex digits for ciphertext, 2 hex digits as the key, 
 *            and one hex digit as the signature 
 *
 *  #2:  The sscanf function and the string and character type libraries cannot
 *       be used except as already provided.  These libraries are for checking 
 *       inputs in main.  They cannot be used for any other purpose.
 *  
 *  #3:  No arrays can be used (excpet as already provided for collecting
 *       keyboard input).  You must use bitwise operators and masks for all 
 *       encoding and decoding.  If you want to use an array as a lookup table 
 *       you must first propose your design and get it approved.  Designs that
 *       use tables to avoid bitwise operators will not be approved.  There
 *       are many good and simple designs that do not require tables.
 *
 *  #4   No changes to the code in main are permitted.  Your code must be placed
 *       in functions.  Additional functions are encouraged.  
 *
 * Bugs:
 *      unknown
 *
 *
 * Tips: For a 64-bit OS, you can use unsigned long int to hold 64 bits
 *
 *       To print a long int use the %ld or %lx format
 *
 *       To set a 64-bit value use 1L instead of just 1.  This forces the
 *       compiler to use 64 instead of 32 bits.  This is needed within
 *       expressions using x as an unsigned long int such as "x & (1L <<  i)".
 *       If you use 1 instead of 1L (and i is an int not a long int), the 
 *       compiler performns the << using 32 bits, and this is not what you want.  
 *
 *       To get gdb to print in hex (x for hex) use 
 *           p /x ciphertext
 *       to print in binary (t for two) use
 *           p /t ciphertext
 *
 * See the ECE 223 programming guide
 *
 * If your formatting is not consistent you must fix it.  You can easily
 * reformat (and automatically indent) your code using the astyle 
 * command.  If it is not installed use the Ubuntu Software Center to 
 * install astyle.  Then in a terminal on the command line do
 *
 *     astyle --style=kr lab1.c
 *
 * See "man astyle" for different styles.  Replace "kr" with one of
 * ansi, java, gnu, linux, or google to see different options.  Or, set up 
 * your own style.
 *
 * To create a nicely formated PDF file for printing install the enscript 
 * command.  To create a PDF for "file.c" in landscape with 2 columns do:
 *     enscript file.c -G2rE -o - | ps2pdf - file.pdf
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lab2_funcs.h"

#define MAXLINE 100
#define TEXTSIZE 16
#define KEWORDSIZE 2
#define SIGNATURESIZE 1
#define uchar unsigned char

// function prototypes
void encode(char *, char *);
void decode(char *, char *, char);
int generate_HexText(char *plaintext, unsigned long int *plainbits);
int generate_Key(char *key_text, uchar *keyword ,unsigned long int *hex_key, int *key_length);
uchar generate_signature(unsigned long int ciphertext);
int get_HexValue(char *plaintext, unsigned long int *plainbits);
int key_len(uchar bin_key);
void print_bits(unsigned long int bits);
void print_keyword(uchar bits);
void print_hex(unsigned long int bits);

int main()
{
    char line[MAXLINE];
    char command[MAXLINE];
    char inputtext[MAXLINE];
    char inputkey[MAXLINE];
    char signature[MAXLINE];
    int  items;
    int i, invalid, invalidkey;

    printf("\nMP2: Vigenere cipher with signature\n");
    printf("Commands:\n\tenc 16-hex-digits 2-hex-digits (keyword)\n");
    printf("\tdec 16-hex-digits 2-hex-digits (keyword) 1-hex-digit (signature)\n\tquit\n");

    // each call to fgets collects one line of input and stores in line
    while (fgets(line, MAXLINE, stdin) != NULL) {
        items = sscanf(line, "%s%s%s%s", command, inputtext, inputkey, signature);
        if (items == 1 && strcmp(command, "quit") == 0) { 
            break;
        } else if (items == 3 && strcmp(command, "enc") == 0) { 
            // encoding
            if (strlen(inputtext) != TEXTSIZE || strlen(inputkey) != KEWORDSIZE) {
                printf("Invalid input to encoder: %s %s\n", inputtext, inputkey);
                printf("  Line was: %s\n", line);
            } else {
                // verify that intput contains hex digits only
                for (i=0, invalid=0; i < strlen(inputtext) && !invalid; i++) {
                    if (!isxdigit(inputtext[i])) 
                        invalid = 1;
                }
                for (i=0, invalidkey=0; i < strlen(inputkey) && !invalidkey; i++) {
                    if (!isxdigit(inputkey[i])) 
                        invalidkey = 1;
                }
                if (invalid || invalidkey) {
                    printf("Invalid characters in plaintext: %s or key: %s\n", 
                            inputtext, inputkey);
                } else {
                    encode(inputtext, inputkey);
                }
            }
        } else if (items == 4 && strcmp(command, "dec") == 0) {  
            // decoding
            if (strlen(inputtext) != TEXTSIZE || strlen(inputkey) != KEWORDSIZE 
                    || strlen(signature) != SIGNATURESIZE) {
                printf("Invalid input to decoder: %s %s %s\n", inputtext, 
                        inputkey, signature);
                printf("  Line was: %s\n", line);
            } else {
                // verify all digits are hex characters 
                for (i=0, invalid=0; i < strlen(inputtext) && !invalid; i++) {
                    if (!isxdigit(inputtext[i])) 
                        invalid = 1;
                }
                for (i=0, invalidkey=0; i < strlen(inputkey) && !invalidkey; i++) {
                    if (!isxdigit(inputkey[i])) 
                        invalidkey = 1;
                }
                if (invalid || invalidkey || !isxdigit(signature[0])) {
                    printf("Invalid decoder digits: %s or key: %s or signature %s\n", 
                            inputtext, inputkey, signature);
                } else {
                    decode(inputtext, inputkey, signature[0]);
                }
            }
        } else {
            printf("# :%s", line);
        }
    }
    printf("Goodbye\n");
    return 0;
}


/* encode: calculates the ciphertext and the signature 
 *
 * input:  plaintext is exactly 16 hex digits
 *         keyword is exactly 2 hex digits
 *
 * assumptions: The input has already been tested to contain the correct number
 *              of valid hex digits
 *
 *              The keyword must be verified to be valid for a key.  If the
 *              keyword is not valid, return from the function without 
 *              encoding the plaintext
 *
 * There is no return value, but the prints described below are required
 */
void encode(char plaintext[], char keyword[])
{
    // these definitions only work for a 64-bit architecture
    unsigned long int plainbits = 9;
    unsigned long int ciphertext = 0;
    unsigned long int key=0;
    uchar bin_keyword=0;
    int key_length=-1;
    int signature = -1;

    printf("\nEncoding plaintext: %s with key %s\n", plaintext, keyword);

    // convert ASCII text to binary value
    generate_HexText(plaintext,&plainbits);
    printf("Plaintext as hex number: %016lx\n",plainbits );
    print_bits(plainbits);              //print plaintext in binary value
    print_hex(plainbits);               //print plaintext in hex value
    
    /*convert ASCII keyword to binary value and evaluate keyword before generating key*/
   if(! generate_Key(keyword,&bin_keyword, &key, &key_length))
   {
        // Print the keyword, the length of the keyword, and the binary 
        // form of the keyword.
        printf("Generate key from input: %s, Key length: %d Keyword: ", keyword, key_length);
        print_keyword(bin_keyword);     //print keyword in binary value
        print_bits(key);                //print key in 64 bit binary value
        print_hex(key);                 //print key in hex value

        ciphertext=key^plainbits;       //generate ciphertext


        // Print the ciphertext in binary and hex.  See example output file
        printf("Ciphertext\n");
        print_bits(ciphertext);         //print ciphertext in 64-bit value
        print_hex(ciphertext);          //print ciphertext in hex value

        // print the parity bits, one bit per line.  
        signature= generate_signature(ciphertext);
        printf("B0 : %d\n",signature&1 );
        printf("B1 : %d\n", (signature&2)>>1);
        printf("B2 : %d\n", (signature&4)>>2);
        printf("B3 : %d\n", (signature&8)>>3);

        // print the ciphertext, keyword, and signature all in hex format
        printf("Ciphertext with signature: %16lx  %s %X\n\n", ciphertext, keyword, signature);

    }
    else
    {
       printf("keyword is invalid: %s, %x\n", keyword, bin_keyword);
    }
}

/* decode: checks the keword and signature and prints the plaintext 
 *
 * input: ciphertext as 16 hex digits
 *        keyword as 2 hex digits
 *        signature as 1 hex character
 *
 * assumptions: The keyword must be verified to be valid for a key.  If the
 *              keyword is not valid, return from the function without 
 *              checking the signature or decoding the ciphertext
 *
 *              Next, the signature must be verified to be valid.  If not, return
 *              from the function without decoding the ciphertext
 *
 *              This function assumes that the ciphertext, keyword, and
 *              signature have already been verified to contain the
 *              correct number of hex digits and no incorrect digits.
 *
 *  The prints included below provide the format required for the output.
 * 
 */
void decode(char ciphertext[], char keyword[], char signature)
{
    // print the input values

    unsigned long int cipherbits = 0;
    unsigned long int plaintext = 0;
    unsigned long int key=0;
    uchar bin_keyword=0;
    int key_length=0;
    char calc_signature=0;
    unsigned long int hex_signature=0;

    printf("\nDecoding: %s with signature %c and key: %s\n", ciphertext, signature, keyword);
    // convert ASCII key to binary key value
    // convert ciphertext to binary value
   if(!generate_Key(keyword,&bin_keyword, &key, &key_length))
    {
   
        // Print the keyword, the length of the keyword, and the binary 
        // form of the keyword.
        printf("Generate key from input: %s, Key length: %d Keyword: ", keyword, key_length);
        print_keyword(bin_keyword);     //print keyword in binary value
        print_bits(key);                //print key in 64-bit value
        print_hex(key);                 //print key in hex value


        generate_HexText(ciphertext,&cipherbits);   //convert ciphertext to binary value
        get_HexValue(&signature,&hex_signature);    //get signature hex value
        signature=(char)hex_signature;
        plaintext=cipherbits^key;                   //decode and get plaintext

        // convert the ciphertext to a variable and print as hex and in binary
        printf("Cipher as hex number: %lx\n", cipherbits);
        print_bits(cipherbits);                     //print cipherbits in binary value
        print_hex(cipherbits);                      //print cipherbits in hex value

        // calculate and print the signature using the ciphertext
        calc_signature=(char)generate_signature(cipherbits);
        // printf("cals_signature: %x  signature: %x \n", calc_signature,signature);
        printf("B0 : %d\n", calc_signature&1 );
        printf("B1 : %d\n", (calc_signature&2)>>1);
        printf("B2 : %d\n", (calc_signature&4)>>2);
        printf("B3 : %d\n", (calc_signature&8)>>3);
        // if the signature does not match the calculation print this message then return
        if (calc_signature!= signature)
        {
          
            printf("Message is not from a trusted source!\n");
        }
        else
        {
            // you must print the original text in binary format 
            printf("Plaintext\n");
            print_bits(plaintext);      //print plaintext in 64-bit value
            print_hex(plaintext);       //print plaintext in hex value
            // print the original text in hex:
            printf(" Original plaintext: %016lX\n\n", plaintext);
            
        }
    }
    else
    {
        printf("keyword is invalid: %s, %x\n", keyword, bin_keyword);
    }
}

