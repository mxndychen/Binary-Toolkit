# Project 01: Binary toolkit

For this project, you'll work with a partner to implement a program that converts between binary and decimal numbers and performs bitwise operations.

### Important tips
* **Thoroughly read the project instructions before you write any code.** Research shows "that the ['new norm' in reading is _skimming_](https://www.theguardian.com/commentisfree/2018/aug/25/skim-reading-new-normal-maryanne-wolf), with word-spotting and browsing through the text. [...] When the reading brain skims like this, [...] we don’t have time to grasp complexity," which makes it harder to create a functional, well-designed program.
* **Start the project shortly after it is released and work on the project over multiple sessions.** This will give you time to think about how to solve problems, allow you to ask questions, and result in better outcomes. The opportunity to revise your project is contingent upon your git commit history demonstrating that you started the project shortly after it was released and you worked on the project over multiple sessions.
* **Follow good [program design](#program-design), [testing, and debugging](#testing-and-debugging) practices** The code you submit will be assessed for both functionality and design.

### Getting started
Clone your repository on your RPi. The code you need to write for this project will be added to the `toolkit.c` file included in your repository.

## Converting from binary to decimal
To convert a number from binary to decimal, a user should run the `toolkit` program with two command-line arguments:
* The binary representation of a number (e.g. `0b10010011`) – you can assume it will be at most 32 bits
* Whether to convert to a signed (`s`) or unsigned (`u`) decimal number

For example, to convert `0b10010011` to a signed decimal number, a user should run the command:
```bash
./toolkit 0b10010011 s
```
You can assume a user always provides valid command-line arguments.

The toolkit should output:
* The formula for conversion as a summation of powers of two
* The formula for conversion as a summation of decimal numbers
* The resulting decimal number

For example, when converting `0b10010011` to a signed decimal number, the program should output:
```
-2^7 + 2^4 + 2^1 + 2^0
-128 + 16 + 2 + 1
-109
```
As another example, when converting `0b10010011` to an unsigned decimal number, the program should output:
```
2^7 + 2^4 + 2^1 + 2^0
128 + 16 + 2 + 1
147
```

Your program **must use the logical shift bitwise operators** when performing the conversion. You may **not** use repeated multiplication by 2 or functions from the math library (e.g., `exp2` or `pow`). 

Remember, you can use the `%d` format specifier to print a signed decimal number and `%u` to print an unsigned decimal number.

## Converting from decimal to binary
To convert a number from decimal to a two's complement binary encoding, run the `toolkit` program with two command-line arguments:
* The decimal representation of a number (e.g., `-13`)
* The number of bits to use to represent the number in binary (e.g., `8`) – maximum of 32

For example, to convert `-13` to 8-bit binary using the negation method, run the command:
```bash
./toolkit -13 8
```
(You can assume a user always provides valid command-line arguments and that there will always be enough bits for the conversion.)

The toolkit should output:
* The conversion steps using the [repeated division](https://diveintosystems.org/book/C4-Binary/conversion.html#_decimal_to_binary_repeated_division) to convert it to binary, then using the [negation](https://diveintosystems.org/book/C4-Binary/signed.html#_negation) method if the value is negative.
* The resulting binary

For example, when converting `-13` to 8-bit binary, the program should output:
```
The absolute value of -13 is 13.
13 is odd --> 1
13 / 2 = 6 is even --> 0
6 / 2 = 3 is odd --> 1
3 / 2 is odd --> 1
1 / 2 is zero
0b00001101
~0b00001101 = 0b11110010
0b11110010 + 0b1 = 0b11110011
0b11110011

```
As another example, when converting `13` to 8-bit binary, the program should output:
```
13 / 2 = 6 is even --> 0
6 / 2 = 3 is odd --> 1
3 / 2 is odd --> 1
1 / 2 is zero
0b00001101
```

Your program can use regular division and modular operations to perform this conversion.  You may **not** use functions from the math library (e.g., `exp2` or `pow`).


## Binary arithmetic
To add or subtract two binary numbers together, run the `toolkit` program with three command-line arguments:
* The two's complement binary representation of the first number (e.g., `0b10010011`) – you can assume it will be at most 32 bits
* Whether to add (`+`) or subtract (`-`) the numbers
* The two's complement binary representation of the second number (e.g., `0b01011100`) – you can assume it will be at most 32 bits.
For example, to add `0b10011011` and `0b01011100`, run the command:
```bash
./toolkit 0b10011011 + 0b01011100
```

The toolkit should output:
* The "carry" bits
* The first and second numbers – for a subtraction operation, the second number should be converted to a negative number before printing it
* The resulting binary
* `overflow` or `underflow` if the computation resulted in either of these
* The equation and result in decimal
For example, when adding `0b10011011` and `0b01011100`, the program should output:
```
      11
  0b10011011
+ 0b01011100
------------
  0b11110111
-101 + 92 = -9
```
As another example, when subtracting `0b10011011` and `0b01011100`, the program should output:
```
   1   
  0b10011011
+ 0b10100100
------------
  0b00111111
underflow
-101 + -92 = 63
```

## Program design
A program whose design is **satisfactory** must adhere to **all of the following**:
* **Use logical shift operators when converting to/from binary:** Do not use repeated multiplication by 2 or functions from the math library (e.g., `exp2` or `pow`). 
* **Use multiple functions:** Do not put all of your code in the `main` function.
* **Avoid duplicated code:** Do not repeat the same (or very similar) code in multiple functions. Instead, put the repeated code into a separate "helper" function that is called by other functions that rely on this code.
* **Avoid global variables:** Use local variables and parameters instead.
* **Use constants:** Use the constants #defined in `toolkit.c` (e.g., `MAX_BINARY_LEN`). Define additional constants as needed to avoid putting fixed numeric (or character) values in function bodies.
* **Fix compilation warnings:** You may be tempted to ignore the warnings, but they almost always mean there is a bug in your code.
* **Include comments:** Each function (except for main), must be preceded by a short comment that describes what the function does.

A program that adheres to **half to three-quarters of the above** has a design that is **close to satisfactory**.

## Testing and debugging
The first step in debugging your code is to **fix any errors or warnings output by the compiler.**  If the program compiles without errors or warnings but still doesn't work as expected, then **add `printf` statements in strategic locations** to help you understand what your program is doing.

A program whose functionality is **satisfactory** must have two or fewer minor bugs, such as:
* Incorrect conversion from binary for an edge case (e.g., a 32-bit number)
* Improper sign for the first term when converting from binary
* Missing final step (e.g., `1/2 is zero`) when converting from a decimal number to binary
* Incorrect binary arithmetic result for an edge case (e.g., carry-out from left-most bit)
* Binary strings are not properly aligned in the output for binary arithmetic
* Missing `0b` before binary strings in the output for one of the tasks

A program whose functionality is **close to satisfactory** must have two or fewer major bugs, such as:
* Incorrect terms in the formula for converting from binary for a non-edge case
* Incorrect final result when converting from binary for a non-edge case
* Missing steps when converting from a positive decimal number to binary
* Missing negation steps when converting from a negative decimal number to binary
* Incorrect final result when performing binary arithmetic for a non-edge case
* Output includes extraneous characters due to improper handling of null characters
* Program reads or writes beyond the bounds of an array

## Submission instructions
You should **commit and push** your updated `toolkit.c` file to your git repository. However, do not wait until your entire program is working before you commit it to your git repository; you should commit your code each time you write and debug a piece of functionality.
