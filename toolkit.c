/*****
 * Project 01: Binary toolkit
 * COSC 208, Introduction to Computer Systems, Fall 2024
 *****/

#include <stdio.h>
#include <string.h>

#define MAX_BINARY_LEN 32

//Takes in a string that represents a decimal number
//and returns integer representation of that number
int convertCharArrToDecimal(char decimalStr[])
{
    int decimal = 0; 
    int tens = 1;
    //converts each character from the end into a integer, sums them into a decimal
    for (int i = strlen(decimalStr) -1 ; i >= 0; i--){ 
        //if the number is negative
        if(decimalStr[i] == '-'){
            decimal = -decimal; 
        }
        else{
        decimal += ((decimalStr[i] - 48) * tens);
        tens *= 10;
        }
    }
    return decimal;
}

//Takes in a string that represents a number of bits
//and returns integer representation of bits
int convertCharArrToBits(char* bitsChar)
{
    int tensForBits = 1;
    int bits = 0; 
    //change ASCII value (char) into int value, starting from end to the beginning
    for (int i = strlen(bitsChar) - 1; i >= 0; i--){
        bits += ((bitsChar[i] - 48) * tensForBits);
        tensForBits *= 10;
    }
    return bits;
}

//Prints sum of powers of two (in full integers) that construct a binary number
//Helper function for converting binary to decimal
void printAllNums(int powerArr[], int len, char sign) 
{
    //print the first number
    if (len >= 1)
    {
        //if it is a signed binary, first number is negative
        if (sign == 's')
        {
            printf("-%d ", 1 << powerArr[0]);
        }
        else
        {
            printf("%d ", 1 << powerArr[0]);
        }
    }
    //print the rest of numbers that construct binary
    for (int i = 1; i < len; i++){
        printf("+ %d ", 1 << powerArr[i]);
    }
    printf("\n");
}

//Converts binary number to a decimal number without any print statements
//returns decimal represnetation of the number
int noPrintBinaryToDecimal(char binary[], char* option)
{
    int decimal = 0;
    int len = strlen(binary);
    //change binary string to decimal string
    for (int i = 2; i < len; i++){
        decimal <<= 1;
        //first number is negative, if the binary is signed
        if (i == 2 && option[0] == 's' && binary[2] == '1'){
            decimal -= (binary[i] - '0');
        }
        //otherwise number is positive
        else{
            decimal += (binary[i] - '0');
        }
    
    }
    return decimal;
}
    
//Checks if there is are more 1s left in the binary number after the provided index
//returns 1 if there are more 1s left and 0 if there are no more 1s after the index
int checkIfOneIsLater(char binary[], int index)
{
    int len = strlen(binary);
    //iterate through the rest of binary after index and check if next number is 1
    for (int i = index +1; i < len; i++)
    {
        if (binary[i] == '1')
        {
            return 1;
        }
    }
    //return 0, if no 1 is present
    return 0;
}


// convert binary to decimal
int binaryToDecimal(char binary[], char* option){
    int decimal = 0;
    int len = strlen(binary);
    int power = len-3; //checking powers of two starting from left
    int powerArr[power]; //initializing power array, length of powers
    int indexArr = 0;
    //change binary string to decimal string, start at two because of 0b
    for (int i = 2; i < len; i++){
        decimal <<= 1; //performing n^2
        if (i == 2 && option[0] == 's' && binary[2] == '1'){ //if decimal is a negative
            decimal -= (binary[i] - '0'); //converting char value into int and subtracting
            if ((binary[i] - '0') ==1){  //printing powers of two if number is 1
                powerArr[indexArr] = power;
                indexArr++;
                if (power == (len-3))
                {
                    printf("-2^%d ", power);
                }
                else if (power != (len-3))
                {
                    printf(" 2^%d ", power);
                }
                if (checkIfOneIsLater(binary, i) == 1) 
                {
                    printf ("+");
                };
            }
        }
        else{
            decimal += (binary[i] - '0'); //else if positive number
            if ((binary[i] - '0') == 1){
                powerArr[indexArr] = power;
                indexArr++;
                if (power != (len-3))
                {
                    printf(" 2^%d ", power);
                }
                else
                {
                    printf("2^%d ", power);
                }
                if (checkIfOneIsLater(binary, i) == 1)
                {
                    printf ("+");
                };
            }
            
        }
        power--; 
    }
    
    printf("\n");
    printAllNums(powerArr, indexArr, option[0]);

    return decimal;
}
void decimalToBinary(int decimal, int bits){
    int absoluteVal;
    char binary[bits + 3]; //intiliazing binary array with regard to 0b and null character
    binary[0] = '0';
    binary[1] = 'b';
    int position = bits + 1; //place in numbers
    if(decimal < 0){ 
        absoluteVal = -decimal;
    }
    else{
        absoluteVal = decimal;
    }
    if (decimal < 0){
        printf("The absolute value of %d is %d\n", decimal, absoluteVal); //print absolute value of decimal
    }
    

    while(absoluteVal > 0){ //repeated division to get binary and create binary array
        if (absoluteVal % 2 == 0){
            printf("%d is even --> 0\n", absoluteVal);
            if(position >= 2){
                binary[position] = '0';
            }
        }
        else{
            printf("%d is odd --> 1\n", absoluteVal);
            if(position >= 2){
            binary[position] = '1';
            }
        }
        position--; //moving toward 0b, creating array from rightmost to leftmost
        if (absoluteVal != 1){ 
            printf("%d / 2 = ", absoluteVal);
        }
        else{
            printf("%d / 2", absoluteVal);
        }
        absoluteVal /= 2;
    }
    
    for (int i = position; i >= 2; i--){ //pad empty bit slots with 0 to get to number of bits needed
        binary[i] = '0';
    }
    printf(" is zero\n"); 
     binary[bits + 2] = '\0';
     printf("%s\n", binary);
    
    if(decimal < 0){ //using NOT bitwise on binary
        printf("~%s = 0b", binary);
        for (int i = 2; i < bits + 2; i ++){ //flipping bits, if it's 0 change to 1 and vice versa
            if (binary[i] == '0'){
                binary[i] = '1';
                printf("%c", binary[i]);
                }
            else{
                binary[i] = '0';
                printf("%c", binary[i]);

                }
        }
        printf("\n");
        printf("%s + 0b1 = ",binary);

        int carry = 1; //1 in binary is 0b0001 --> how much we're adding to the ~binary

        for(int i = bits + 1; i > 1; i--){  //right to left iteration of bit
            if(binary[i] == '0' && carry == 1){ //binary arithmetic starts here
                binary[i] = '1'; // 1+0 = 1
                carry = 0;
            }
            else if(binary[i] == '1' && carry == 1){
                binary[i] = '0';
                carry = 1; //1 + 1 = 0, carry 1 to next
            }
        }
        printf("%s\n", binary);
        printf("%s\n", binary);
    }
}

//display how the computation looks like
void displayArithmetic(char first[], char second[], int num1, int num2, int result, int underflow, int overflow){
    int len = strlen(first); //assuming that second and result will be same number of bits as first num
    char carryBits[len+1]; //array to display carry during arithmetic/print
    carryBits[len-1] = ' ';
    char resultArr[len+1];
    if (num2 < 0){ //handling negative binary
        for (int i = 2; i < len; i++){
            if (second[i] == '0'){
                second[i] = '1';
                }
            else{
                second[i] = '0';
                }
        }
        int carryNeg = 1; //1 in binary is 0b0001

        for(int i = len - 1; i > 1; i--){  //right to left iteration of bit
            if(second[i] == '0' && carryNeg == 1){
                second[i] = '1'; // 1+0 = 1
                carryNeg = 0;
            }
            else if(second[i] == '1' && carryNeg == 1){
                second[i] = '0';
                carryNeg = 1; //1 + 1 = 0, carry 1 to next
            }
        }
    }
    
    int carry = 0;
    for (int i = len-1; i >= 1; i--) //handling display/carry when doing arithmetic
    {
        if (first[i] == '1' && first[i] == second[i] && carry == 0) //1 + 1 with no carry
        {
            resultArr[i] = '0';
            carryBits[i-1] = '1';
            carry = 1;
        }
        else if ((first[i] == '1' || second[i] == '1') &&  first[i] != second[i] && carry == 0) //1 + 0 with no carry
        {
            resultArr[i] = '1';
            carryBits[i-1] = ' ';
            carry = 0;
        }
        else if (first[i] == '0' && first[i] == second[i] && carry == 0) //0+0 with no carry
        {
            resultArr[i] = '0';
            carryBits[i-1] = ' ';
            carry = 0;
        }
        else if(first[i] == '1' && first[i] == second[i] && carry == 1) //1+1 with 1 carry
        {
            resultArr[i] = '1';
            carryBits[i-1] = '1';
            carry = 1;
        }
        else if ((first[i] == '1' || second[i] == '1') &&  first[i] != second[i] && carry == 1) //1+0 with 1 carry
        {
            resultArr[i] = '0';
            carryBits[i-1] = ' ';
            carry = 0;
        }
        else if (first[i] == '0' && first[i] == second[i] && carry == 1) //0 + 0 with 1 carry
        {
            resultArr[i] = '1';
            carryBits[i-1] = ' ';
            carry = 0;
        }
    }
    if (carry == 1) //if there is a carry, then put into display carry array
    {
        carryBits[1] = '1';
    }
    else{
        carryBits[1] = ' ';
    }
    carryBits[0] = ' ';
    resultArr[0] = '0';
    resultArr[1] = 'b';
    resultArr[len] = '\0';
    carryBits[len] = '\0';
    char binaryType[] = {'s', 'u'};
    int ress = noPrintBinaryToDecimal(resultArr, binaryType);
    printf("  %s\n", carryBits);
    printf("  %s\n", first);
    printf("+ %s\n", second);
    //seperation line to be displayed below, based on bits user entered will adjust length of -
    char printLine[len+3];
    for (int i = 0; i < len +2; i++)
    {
        printLine[i] = '-';
    }
    printLine[len+2] = '\0';
    printf("%s\n", printLine);
    printf("  %s\n", resultArr);

    //handle overflow and underflow 
    if(num2 > 0){ 
        if(((num1 > 0) && (num2 > 0) &&(ress < 0)) ||((num1 < 0) && (num2 < 0) && (ress > 0))){
            overflow = 1;
        }
    }
  
    if(num2 < 0){
        if(((num1 > 0) && (num2 > 0) &&(ress < 0)) ||((num1 < 0) && (num2 < 0) && (ress > 0))){
            underflow = 1;
        }
    }
    if (overflow == 1)
    {
        printf("overflow\n");
    }
    else if(underflow == 1)
    {
        printf("underflow\n");
    }
    printf("%d + %d = %d \n", num1, num2, ress);
}

//add or subtract binary numbers together!
void binaryArithmetic(char *firstNum, char *operation, char *secondNum){
    char binaryType[] = {'s', 'u'};
    int num1 = noPrintBinaryToDecimal(firstNum, binaryType);
    int num2 = noPrintBinaryToDecimal(secondNum, binaryType);
    int result = 0;
    int overflow = 0;
    int underflow = 0;

    if(operation[0] == '+'){ //addition handling, add numbers in binary form
        result = num1 + num2;
        if(((num1 > 0) && (num2 > 0) &&(result < 0)) ||((num1 < 0) && (num2 < 0) && (result > 0))){
            overflow = 1;
        }
    }
  
    if(operation[0] == '-'){ //subtraction
        num2 = -num2;
        result = num1 + num2;
        if(((num1 > 0) && (num2 > 0) &&(result < 0)) ||((num1 < 0) && (num2 < 0) && (result > 0))){
            underflow = 1;
        }
    }
    
    displayArithmetic(firstNum, secondNum, num1, num2, result, underflow, overflow);
}



int main(int argc, char *argv[]) {
    if (argc == 3) {
        // Store first argument in array
        char number[MAX_BINARY_LEN + 2 + 1];
        strcpy(number, argv[1]);
        // Store second argument in array
        char option[3];
        strcpy(option, argv[2]);
        //converting binary to decimal
        if (option[0] == 's' || option[0] == 'u'){
            int converted = binaryToDecimal(number,option);
            printf("%d \n", converted);
        }
        //converting decimal to binary
        else{
            int decimal = convertCharArrToDecimal(number);
            int bits = convertCharArrToBits(option);
            decimalToBinary(decimal, bits);
            return 0;
        }    
    }
    //performing arithmetic
    else if (argc == 4) {
        // Store first argument in array
        char firstNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(firstNum, argv[1]); 

        // Store second argument in array
        char operation[2];
        strcpy(operation, argv[2]);

        // Store third argument in array
        char secondNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(secondNum, argv[3]);

        binaryArithmetic(firstNum, operation, secondNum);
    }
    else {
        printf("Invalid number of arguments\n");
        return 1;
    }
}