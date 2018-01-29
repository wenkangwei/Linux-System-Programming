/* lab3.c
 * Wenkang Wei
 * wenkanw
 * ECE 2220,Section-1 Fall 2017
 * MP3
 * Subject: ECE222-1,#3
 *
 * Purpose: 
 *			This program is to retrive encrypted password and key from two given packets
 *          and then decode the password using addition operation with the decrypted keys.
 *			After decrypting the password, print out the encrypted key and encrypted password
 *			and decrypted password
 *
 * Assumptions:
 *  #1   The user is prompted to enter two "packets."  The packets will have a
 *       maximum of 80 characters.
 *
 *  #2:  The string and character type library cannot be used under
 *       any circumstances.  You are encouraged to develop your own
 *       functions to perform any similar operations that are needed.
 *  
 *  #3   No changes to the code in main.  Your code must be placed in
 *       functions.  Additional functions are encouraged.  
 *
 * Bugs:
 *		unknown
 *
 * Notes:
 *
 * See the ECE 2220 programming guide
 *
 * If your formatting is not consistent you must fix it.  You can easily
 * reformat (and automatically indent) your code using the astyle 
 * command.  In a terminal on the command line do
 *
 *     astyle --style=kr lab3.c
 *
 * See "man astyle" for different styles.  Replace "kr" with one of
 * ansi, java, gnu, linux, or google to see different options.  Or, set up 
 * your own style.
 */

// do not include any additional libraries
#include <stdio.h>

// do not change this constant
#define MAXPACKETSIZE 80
#define uchar unsigned char
// function prototypes
int process_input(const char *pwpacket, const char *keypacket, char *encpw, char *enckey);
void decrypt_password(const char *encpw, const char *enckey, char *password);
uchar char_to_int_Map(const char c );
char int_to_char_Map(uchar integer );
int usr_strcp(char *dst, char *sub, int dst_len);
int usr_strlen(const char *str);
int extract_subStr(char esc_char, const char *str_pt, char *subStr, int len);
void clean_Buffer(char *str_pt, int len);

// do not change any code in main.  We are grading based on the format
// of the output as given in the printfs in main.
int main()
{
    char packet1[MAXPACKETSIZE];
    char packet2[MAXPACKETSIZE];
    char encpw[MAXPACKETSIZE];
    char enckey[MAXPACKETSIZE];
    char password[MAXPACKETSIZE];
    int  error_code;

    printf("\nMP3: Extracting and decrypting embedded passwords\n");
    printf("Inputs: Two at most 80 character \"packets.\"\n");
    printf("Escape characters: '%%', '$', and '*'\n");
    printf("\tCtrl-d to quit\n\n");

    // each call to fgets collects one line of input and stores in input_line
    // BEWARE: fgets includes the end-of-line character '\n' in input_line
    while ((fgets(packet1, sizeof packet1, stdin) != NULL) 
            && (fgets(packet2, sizeof packet2, stdin) != NULL)) {

        // clear for next round
        encpw[0] = enckey[0] = password[0] = '\0';

        // print input packets
        printf("\npacket 1:\n%s\n", packet1);
        printf("packet 2:\n%s\n", packet2);

        // process input
        error_code = process_input(packet1, packet2, encpw, enckey);

        if(error_code == 0) {
            // print parsed input
            printf("encrypted password: %s\n", encpw);
            printf("encryption key:     %s\n", enckey);

            // perform decryption
            decrypt_password(encpw, enckey, password);

            // print decrypted password
            printf("decrypted password: %s\n\n", password);
        } else {
            printf("# ERROR: invalid input packets\n\n");
        }
    }
    printf("\nGoodbye\n");
    return 0;
}

/* Parse the two input packets.
 *
 * Each packet contains up to 80 characters.  The first packet contains
 * the encrypted password, and the second packet contains the encryption
 * key.  Each of these two strings is broken into three pieces (substrings) in
 * their respective packets - piece 1 is marked with '%'s, piece 2
 * is marked with '$'s, and piece 3 is marked with '*'s.
 *
 * Packets contain only printable characters.  
 *
 * Input: The two packets are collected using fgets.  Recall the end-of-line
 *        character is included in the input string and marks the end of the 
 *        input.  This string must not be changed.
 *
 * Output:  There are three outputs from this function.
 *
 *   The return value is an error code.  Error code 0 represents no error.
 *   Any other value is an error.
 *
 *  If there are no errors, then two strings are also returned.  The first,
 *  encpw, contains the encrypted password.  The second, enckey, contains
 *  the encryption key.  If an error occurs, these two output strings
 *  are undefined.
 */
int process_input(const char *pwpacket, const char *keypacket, char *encpw, char *enckey)
{
	// extract password string
	// check whether string is valid and extract first part of password
	if(extract_subStr('%',pwpacket,encpw, MAXPACKETSIZE)) 
		return 3;
	// check whether string is valid and extract secondary part of password
	if(extract_subStr('$',pwpacket,encpw,MAXPACKETSIZE))
		return 3;
	// check whether string is valid and extract third part of password
	if(extract_subStr('*',pwpacket,encpw,MAXPACKETSIZE))
		return 3;

	// extract key string
	if (extract_subStr('%',keypacket,enckey, MAXPACKETSIZE)) 
		return 3;
	if(extract_subStr('$',keypacket,enckey, MAXPACKETSIZE))  
		return 3;
	if(extract_subStr('*',keypacket,enckey,MAXPACKETSIZE))   
		return 3;
	// check whether key and password are valid
	if(usr_strlen(enckey)==usr_strlen(encpw)) 
		return 0;
	else
	    return 3;

}

/* Perform decryption on the encrypted password using character addition.
 *
 * Each character is converted to an integer in the range 0...51, where a is 0,
 * b is 1, c is 2, ..., z is 25, A is 26, B is 27, ..., Z is 51.  The 
 * decryption operation is then performed by adding the encryption key to the 
 * encrypted password using addition modulo 52.
 *
 * Input: The encrypted password string and the encryption key are assumed
 *        to be valid and are assumed to be the same length (as verified
 *        by the process input function).
 *
 * Output:  The decrypted password generated by the above rules
 */
void decrypt_password(const char *encpw, const char *enckey, char *password)
{
	int len=0;
	int index=0;
	// get the length of the encrypted password to ensure the boundary of decrypted password 
    len=usr_strlen(encpw);
    // clean the array data for the next packet
    clean_Buffer(password, MAXPACKETSIZE);	
    // map the characters and decrypt password
    while(index <len)
    {
    	password[index]=int_to_char_Map(char_to_int_Map(encpw[index])+char_to_int_Map(enckey[index]));
    	index++;
    }
    password[index]='\0';

}


/*
* @brief clean_Buffer
*			clean the data of an array.
*			The input should be address of the array 
*			and the length of array
* @para *str_pt
*			input the address of the array
* @para len
*			length of the array
*/

void clean_Buffer(char *str_pt, int len)
{
	for (int i = 0; i < len; ++i)
	    {
	    	str_pt[i]=0;
	    }
}

/*
*	@brief char_to_int_Map
*		this function is to convert each printable 
*		character to integer. a~z: 0~25. A~Z: 26~51
*		Input should be a value within a~z or A~Z
*	@para  c:
*		printable character, it should be character from a~z or A~Z
*	@preturn 
*		mapped integer
*/
uchar char_to_int_Map(const char c )
{
	return (c<='z' && c>='a')? c-97 : c-39;
}


/*
*	@brief int_to_char_Map
*		this function is to convert each integer 
*		 back to printable character. a~z: 0~25. A~Z: 26~51
*		Input should be a value within 0~51
*	@para  integer:
*		integer
*	@preturn 
*		mapped character
*/
char int_to_char_Map(uchar integer )
{
	while(integer>51)
	{		
		integer-=52;
	}
		return integer<=25? integer+97 :integer+39;
}


/*
*	@brief usr_strlen
*		this function is to return the length of a string
*	@para  *str:
*		pointer pointing at the first address of a string
*	@preturn 
*		length of string without counting '\0' character
*/ 
int usr_strlen(const char *str)
{
	int length=0;
	while(*str!='\0')
	{
		length++;
		str++;
	}
	return length;
}


/*
*	@brief extract_subStr
*		this function is to extract the substring in the packet
*		based on the escape character you input  
*	@para  esc_char:
*		escape character, which set the boundary of substring
*	@para *str_pt:
*		string point pointing to a source string
*	@para *subStr:
*		string pointer pointing to the space storing substring
*	@para len:
*		length of the array storing substring
*	@return 
*		1: fail to achieve substring. 0: achieve substring successfully
*		
*/
int extract_subStr(char esc_char,const char *str_pt, char *subStr, int len)
{
	char str_temp[MAXPACKETSIZE];
	uchar esc_cnt=0; //used to check how many same escape characters are detected.
	int index=0;
	//stop extracting substring if substring is longer than destination array or 
	// detected 2 escape characters, or the str_pt is at the end of source string
	while(esc_cnt!=2&& index<MAXPACKETSIZE-1)
	{
		if(*str_pt==esc_char) 
		{
			str_pt++;
			esc_cnt++;
			if(*str_pt==esc_char) return 0;
		}
		
		//start extracting substring when the first escape character is detected
		if(esc_cnt==1)
		{
			str_temp[index] =*str_pt;	//extract character and substring index ++
			index++;
		}
		str_pt++;						//check next character in source string
	}
	if( esc_cnt==2)
	{
		str_temp[index] ='\0';			//add escape char at the end of substring
		usr_strcp(subStr,str_temp,len);	//copy substring to the destination array.
		return 0;
	}
	else 
		return 1;

}


/*
*	@brief usr_strcp
*		this function is to copy substring to the end of destination string
*	@para  *dst
*		destination string 
*	@para *sub
*		substring needed being copied to destination string
*	@return:
*		1: fail to copy string. 0: copy successfully
*/
int usr_strcp(char *dst, char *sub, int dst_len)
{
	int index=0;
	// check whether the dst array is a correct string
	while(dst[index]!='\0' && index< dst_len-1)
		index++;
	//if it is string, start copying substring to the end of the destination string
	if (dst[index]=='\0')
	{
		dst=&dst[index];						//move pointer to position of '\0' character
		while(*sub!='\0'&& index< dst_len-1)	//check boundary
		{
			*dst=*sub;
			dst++;								//move to address of next char in destination string
			sub++;								//move to address of next char in substring
			index++;
		}
		*dst='\0';
		return 0;
	}
	return 1;
}

