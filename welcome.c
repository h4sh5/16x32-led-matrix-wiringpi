/*
A script to test using wiringpi to display things on the 16x32 LED board.

author: Haoxi Tan
email: heman0426@gmail.com
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#include "led_matrix.h"



static short int CROSS[16][32] = 
{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


static short int WELCOME[16][32] = 
{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {0,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1},
 {0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1, 0,1,0,1,0,1,1,0},
 {0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1, 0,1,0,1,0,0,0,0},
 {0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1, 0,1,0,1,0,1,1,1},
 {0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0},
 {1,0,1,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

static short int HOME[16][32] = 
{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,1,0,1,1,1,1,1},
 {1,1,1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,0,0,1,1,0,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1},
 {1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int main(void) {


	//setup wiring pi with gpio mapping
	wiringPiSetupPhys();

	//define pins
	int pins[8] = {3,5,29,31,33,35,11,36}; //OE,CLK,A,B,C,D,R1,STB(Latch)

	//put all pins into OUTPUT mode
	int i;
	for (i=0;i<8;i++) {
		pinMode(pins[i], OUTPUT);

	}

	//fill up a 16x32 2d array with 0s, because 0 is the on 
	//signal for a pin

	/*
	int image[16][32];
	int a,b;
	for (a=0; a<16; a++){
		for (b=0;b<32;b++){
			image[a][b] = 0;
		}
	}*/

	while (1){
		display(CROSS, 1);
		display(WELCOME, 0.8);
		display(HOME, 0.8);
	}
	


	return 0;


}