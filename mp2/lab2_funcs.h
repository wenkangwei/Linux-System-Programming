
/* lab2_funcs.h
 * Wenkang Wei
 * wenkanw
 * ECE 2220, Section1, Fall 2017
 * MP2
 *
 * Purpose:
 *          This file is to declare the functions defined
 *			in lab2_funcs.c file.It is used in lab2.c file
 *			so that the functions in lab2_funcs.c can be called
 *			by lab2.c
 *			
 *
*/

#ifndef LAB2_FUNCS_H
#define LAB2_FUNCS_H

#define uchar unsigned char

// functions prototypes
int generate_HexText(char *plaintext, unsigned long int *plainbits);
int generate_Key(char *key_text, uchar *keyword ,unsigned long int *hex_key, int *key_length);
uchar generate_signature(unsigned long int ciphertext);
int get_HexValue(char *plaintext, unsigned long int *plainbits);
int key_len(uchar bin_key);
void print_bits(unsigned long int bits);
void print_keyword(uchar bits);
void print_hex(unsigned long int bits);

#endif