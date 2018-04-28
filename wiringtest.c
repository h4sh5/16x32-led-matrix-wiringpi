/*
A script to test using wiringpi to display things on the 16x32 LED board.

author: Haoxi Tan
email: heman0426@gmail.com
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


int * rowconv(int val){
	//Converting an integer value into a 16bit ABCD pin list

	//first have a char array
	static char row[4];
	static int introw[4];

	int remainder; 
 	int binary = 0, i = 1;

 	//converts the value into binary
	while(val != 0) {
        remainder = val%2;
        val = val/2;
        binary= binary + (remainder*i);
        i = i*10;

    }

    //put it into the char array
    sprintf(row, "%04d", binary);

    //typecast into the int array
    introw[0] = (int) row[0];
    introw[1] = (int) row[1];
    introw[2] = (int) row[2];
    introw[3] = (int) row[3];

    return introw;

}


void display( int image[16][32] ) { 
//displays the array image[] on the LED board.



}


int main(void) {


	//setup wiring pi with gpio mapping
	wiringPiSetupSys();

	//define pins
	int pins[8] = {3,5,29,31,33,35,11,36}; //OE,CLK,A,B,C,D,R1,STB(Latch)

	//put all pins into OUTPUT mode
	int i;
	for (i=0;i<8;i++) {
		pinMode(pins[i], OUTPUT);

	}

	int * row = rowconv(5);

	printf("%c%c%c%c\n",row[0],row[1],row[2],row[3]);

	return 0;


}