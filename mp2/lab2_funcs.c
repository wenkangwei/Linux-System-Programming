
/* lab2_funcs.c
 * Wenkang Wei
 * wenkanw
 * ECE 2220, Section1, Fall 2017
 * MP2
 *
 * Purpose:
 *          This program is to define the functions used for
 *          encryption and decryption. These functions are declared in 
 *          lab2_funcs.h and called
 *          in lab2.c
 *
*/
#include "lab2_funcs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/*
*   @brief: key_len
*           this function is to obtain the length of the key
*           and return it. if the key is invalid, return negative
*           value
*   @para   *key
*           this pass the key  to the function by address accessing
*   @return len
*           it is the length of the key. If it is invalid, it return 
*           -1
*/
int key_len(uchar bin_key)
{
    int len=0;
    while(bin_key!=0)
    {
        len++;
        bin_key>>=1;
    }

    return len;
}

/*
*   @brief: generate_HexText
*           this function is to convert the ASCII text input to
*           an unsigned long int hex code and return
*           1~9: 48 ~57  a~f:97~102 A~F: 65~70
*           
*   @para   *plaintext
*           the address storing the ASCII plaintext
*
*   @return hex_text
*           the hex value storing plaintext
*           
*/
 int generate_HexText(char *text, unsigned long int *bits)
{
 

    // convert ASCII to binary value
    //if invalid text, return 1;
    if(get_HexValue(text,bits)) return 1;

    return 0;
}

/*
*	@brief:	generate_Key
*			this function is to convert the ASCII keyword input to
*           a key in an unsigned long int type and return
*           1~9: 48 ~57  a~f:97~102 A~F: 65~70
*			
*   @para   *hex_key
*           the address storing the key generated
*	@para	*keyword
*			the address storing the keyword
*
*	@para *key_length
*			the valid length of the keyword
*   @return 
*          0: keyword is valid and key generated
*		   1: keyword is invalid
*/
int generate_Key(char *key_text, uchar *keyword ,unsigned long int *hex_key, int *key_length)
{

    int times=0;
    int remainder=0;
   
    // convert ASCII key value to binary value
    get_HexValue(key_text,(unsigned long int *)keyword);
  
      
     // evaluate the length of keyword 
   *key_length=key_len((uchar)(*keyword));

    // if key length<2 or >8 or all are 1, invalid input
   if (*key_length<=2||*key_length>8||(*keyword==~(-1<<*key_length)))
   {
       return 1;
   }

    // generate key with the same length as plaintext
    *hex_key=0;
    times=64/(*key_length);
    remainder=64%(*key_length);
    for (int i = 0; i <times ; ++i)
    {
        *hex_key<<=*key_length;
        *hex_key|=*keyword;
    }
    *hex_key<<=remainder;
    *hex_key|=(*keyword>>(*key_length-(remainder)));

	return 0;
}





/*
*   @brief: generate_HexText
*           this function is to convert the ASCII text input to
*           an unsigned long int hex code and return
*           1~9: 48 ~57  a~f:97~102 A~F: 65~70
*           
*   @para   *plaintext
*           the address storing the ASCII plaintext
*   @para   *plainbits
*           the address storing the binary value of the bit
*
*   @return 
*           1: invalid value input
*           0: convert data successfully
*           
*/

int get_HexValue(char *text, unsigned long int *bits)
{
    int i=0;
    uchar temp=0;               //store binary value of each char
    while(text[i]!='\0')
        {
            // convert each char to a hex value letter
            if (text[i]>=48&&text[i]<=57)   
            {
                temp=(uchar) (text[i]-48); //convert 0~9 ASCII code to hex
            }
            else if (text[i]>=65&&text[i]<=70)
            {
                temp=(uchar) (text[i]-55); //convert A~F to hex
            }
            else if (text[i]>=97&&text[i]<=102)
            {
                temp=(uchar) (text[i]-87); //convert a~f to hex
            }
            else
            {
               return 1;    //return 1 if invalid text is input
            }

            i++;
            // or operation add each char to binary result
            *bits<<=4;
            *bits|=temp;
        }    
    return 0;
}


/*
*   @brief: print_bits
*           print input in binary value with a space char between each 4 bits
*   @para   bits
*           value need printing
*           
*/

void print_bits(unsigned long int bits)
{
   
    int cnt=0;
    printf(" ");
    for (int i = sizeof(bits)*8; i >0 ; --i)
    {
        cnt++;
        // print a space char between each 4 bits
        printf("%d",(int)((bits)>>(i-1))&1 );
        if(cnt==4 && i!=1)
        {
            printf(" ");
            cnt=0;
        }
    }
     printf("\n");
}


/*
*   @brief: print_hex
*           print input value in hex value  with 4 space char 
*           between each letter 
*   @para   bits
*           value need printing
*           
*/
void print_hex(unsigned long int bits)
{

   uchar mask=0x0f;
    for (int i = (sizeof(bits)*8)/4; i >0 ; --i)
    {
        
        // each 4 bits print a space char    
        printf("    %lx",((bits)>>4*(i-1))&mask );
        
    }
    printf("\n");
}

/*
*   @brief: print_keyword
*           print input in binary value with valid length
*   @para   bits
*           value need printing
*           
*/

void print_keyword(uchar bits)
{
   
    // obtain valid length of keyword 
    for (int i = key_len(bits); i >0 ; --i)
    {
        // print each bit of keyword
        printf("%d",(int)((bits)>>(i-1))&1 );
       
    }
    printf("\n");
}

/*
*   @brief: generate_signature
*           generate dynamic signature
*   @para   ciphertext
*           the hex value of ciphertext
*   @return signature:
*           return signature in unsigned char type
*           
*/
uchar generate_signature(unsigned long int ciphertext)
{
    uchar signature=0;
    unsigned int sum=0;
    unsigned long int mask=1;
    uchar index=1;

    // encrypt first bit
    while(index<=64)
    {
        sum=((ciphertext>>(index))&mask)==0? sum:sum+1;
        index+=2;
      
    }

    if((sum&0x01)!=0) signature|=1;

    // encrypt second bit
    sum=0;  //clean data
    mask=1;
    while(mask!=0)
    {
        sum=(ciphertext&mask)==0? sum:sum+1;
        mask<<=3;
    }
    
    if((sum&1)!=0) signature|=2;

    // encrypt third bit
    sum=0;
    index=12;
    mask=1<<12;
    while(index<=25)
    {
        index++;
        sum=((mask&ciphertext)==0)? sum:sum+1;
        mask<<=1;
    }
    
    if((sum&1)!=0) signature|=4;

    // encrypt fourth bit
    sum=0;
    mask=0x01;
    index=1;
    while(index<=64)
    {
        sum=((ciphertext>>(index-1))&mask)==0? sum:sum+1;
        index*=2;
    }
    if((sum&0x01)!=0) signature|=8;


    return signature;
}