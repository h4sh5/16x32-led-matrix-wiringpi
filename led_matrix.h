//set variable names for specific pins

static short int OE =  3;
static short int CLK = 5;
static short int rows[4] = {29,31,33,35};
static short int A = 29;
static short int B = 31;
static short int C = 33;
static short int D = 35;
static short int R1 = 11;
static short int STB = 36;



short int * rowconv(int val){
	//Converting an integer value into a 16bit ABCD pin list

	//first have a char array
	static char row[4];
	static short int introw[4];

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

    //typecast into the int array. Subtracting the char '0' converts it into a decimal value (like '1' -> 1)
    introw[0] = (short int) row[0] - '0';
    introw[1] = (short int) row[1] - '0';
    introw[2] = (short int) row[2] - '0';
    introw[3] = (short int) row[3] - '0';

    return introw;

}


void display( short int image[16][32], float seconds ) { 
//displays the array image on the LED board for given amount of seconds

	int times = seconds * 3750;

	int time;
	short int row;
	short int col;
	for (time=0; time<times; time++) { 
	//main loop for display. time is just a variable for looping, it doesn't do anything
		for (row=0; row<16; row++) {
			
			digitalWrite(STB, 0);

			for (col=0; col<32; col++){
				digitalWrite(R1, image[row][col]);
				digitalWrite(CLK, 0);
				digitalWrite(CLK, 1);

			}

			digitalWrite(OE, 1);

			digitalWrite(A, rowconv(row)[3]);
			digitalWrite(B, rowconv(row)[2]);
			digitalWrite(C, rowconv(row)[1]);
			digitalWrite(D, rowconv(row)[0]);

			digitalWrite(STB, 1);
			digitalWrite(OE, 0);
		}
	}




}
