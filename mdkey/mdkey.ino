/*
PS/2 Keyboard to MiniDisc
By Ravn Gundersen <ravn@sixbynine.no>
---------------------------------------
This project adds PS/2 Keyboard support
to Sony Mini disc decks. 

Connect IRDATA to IR receiver datapin
on the player pcb, as well as 5V and GND.


Project requires the following external libraries:
PS2KeyAdvanced
PS2KeyMap

Default connection on Arduino:
PS/2 Data pin 	8
PS/2 Clock pin	2
MD/IR Data pin	3

Default Special keys:
Exit / Stop     Esc
Edit title/save Enter
Previous track  Up
Next track      Down
Play            F1
Pause           F2
Record          F3
Eject           F12

*/

#include <PS2KeyAdvanced.h>
#include <PS2KeyMap.h>
#define DATAPIN	8			// PS/2 Data
#define IRQPIN	2			// PS/2 Clock/IRQ 
#define IRDATA	3			// IR output pin
#define ALLOW_REMOTE	0	// Set to 1 to allow for both keyboard and remote control to work simultaneous. Note that this slows down keyboard some!
PS2KeyAdvanced keyboard;
PS2KeyMap keymap;

// IR Codes
#define CMD_A		"101110011110"  //A - Continue
#define CMD_B		"011110011110"  //B - Shuff1e
#define CMD_C		"111110011110"  //C- Program
#define CMD_D		"110110011110"  //D 
#define CMD_E		"010110011110"  //E
#define CMD_F		"000000011110"  //F-1
#define CMD_G		"100000011110"  //G-2
#define CMD_H		"010000011110"  //H-3
#define CMD_I		"110000011110"  //I-4
#define CMD_J		"001000011110"  //J-5
#define CMD_K		"101000011110"  //K-6
#define CMD_L		"011000011110"  //L-7
#define CMD_M		"111000011110"  //M-8
#define CMD_N		"000100011110"  //N-9
#define CMD_O		"100100011110"  //O-10
#define CMD_P		"000000111110"  //P-11
#define CMD_Q		"100000111110"  //Q-12
#define CMD_R		"010000111110"  //R-13
#define CMD_S		"110000111110"  //S-14
#define CMD_T		"001000111110"  //T-15
#define CMD_U		"101000111110"  //U-16
#define CMD_V		"011000111110"  //V-17
#define CMD_W		"111000111110"  //W-18
#define CMD_X		"000100111110"  //X-19
#define CMD_Y		"100100111110"  //Y-20
#define CMD_Z		"010100111110"  //Z-21
#define CMD_DASH	"110100111110"  //DASH-22
#define CMD_SPACE	"001100111110"  //Space- 23
#define CMD_DOT		"101100111110"  //DOT-24
#define CMD_APOST	"011100111110"  //Apostrophe-25
#define CMD_SLASH	"010100011110"  // /- >25
#define CMD_QUEST	"011001011110"  //?-REPEAT
#define CMD_EXL		"111001011110"  //!-A-B
#define CMD_LPAR	"110011011110"  //(A.Space
#define CMD_RPAR	"001011011110"  //) M.Scan
#define CMD_NAME	"001111011110"  
#define CMD_CHAR	"011011011110"
#define CMD_NUM		"111011011110"
#define CMD_CLEAR	"111100011110"
#define CMD_PLAY	"010101011110"
#define CMD_PAUSE	"100101011110"
#define CMD_STOP	"000101011110"
#define CMD_PREV	"000001011110"
#define CMD_NEXT	"100001011110"
#define CMD_REC		"101101011110"
#define CMD_SBACK	"110101011110"
#define CMD_SFWD	"001101011110"
#define CMD_TREC	"000011011110"
#define CMD_MSYNC	"111111011110"
#define CMD_EJECT	"011010011110"
#define CMD_SCROLL	"100110011110"
#define CMD_DISPLAY	"000110011110"
#define CMD_ONOFF	"101010011110"
#define CMD_NAME	"001111011110"



// Globals
uint16_t ps2code;
uint16_t ps2raw;
unsigned int currentmodifier = 2;

void setup() {
	Serial.begin(115200);
	Serial.println("MD Keybord start");
	if ( ALLOW_REMOTE == 1 ) {
		pinMode(IRDATA, INPUT);
	}
	else {
		pinMode(IRDATA, OUTPUT);
		digitalWrite(IRDATA, HIGH);
	}
	keyboard.begin(DATAPIN, IRQPIN);
	keyboard.setNoBreak(1);		// Disable break codes
	keyboard.setNoRepeat(1);	// Disable repeat
}

void loop() {
	if (keyboard.available()) {
		if ( ALLOW_REMOTE == 1 ) {
			pinMode(IRDATA, OUTPUT);
			digitalWrite(IRDATA, HIGH); 
			delay(25);
		}
		ps2raw = keyboard.read();
		ps2code = keymap.remapKey(ps2raw);
		Serial.print("RAW value: ");
		Serial.print(ps2raw);
		Serial.print(" ASCII value : ");
		Serial.println(ps2code);
		if ( ps2code >= 32 and ps2code <= 126 ) {		// Standard keys
			if ( ps2code == 32 ) 	// Space
				sendcmd(CMD_SPACE,0);
			if ( ps2code == 33 )  // !
				sendcmd(CMD_EXL,0);
			if ( ps2code == 38 )  // /
				sendcmd(CMD_SLASH,0);
			if ( ps2code == 46 )  // .
				sendcmd(CMD_DOT,0);   
			if ( ps2code == 47 )  // -
				sendcmd(CMD_DASH,0); 
			if ( ps2code == 48 )	// 0
				sendcmd(CMD_O,3);	
			if ( ps2code == 49 )	// 1
				sendcmd(CMD_F,3);	
			if ( ps2code == 50 )	// 2
				sendcmd(CMD_G,3);	
			if ( ps2code == 51 )	// 3
				sendcmd(CMD_H,3);	
			if ( ps2code == 52 )	// 4
				sendcmd(CMD_I,3);	
			if ( ps2code == 53 )	// 5
				sendcmd(CMD_J,3);	
			if ( ps2code == 54 )	// 6
				sendcmd(CMD_K,3);	
			if ( ps2code == 55 )	// 7
				sendcmd(CMD_L,3);	
			if ( ps2code == 56 )	// 8
				sendcmd(CMD_M,3);	
			if ( ps2code == 57 )	// 9
				sendcmd(CMD_N,3);		
			if ( ps2code == 65 )	// A
				sendcmd(CMD_A,2);		
			if ( ps2code == 66 )	// B
				sendcmd(CMD_B,2);		
			if ( ps2code == 67 )	// C
				sendcmd(CMD_C,2);		
			if ( ps2code == 68 )	// D
				sendcmd(CMD_D,2);		
			if ( ps2code == 69 )	// E
				sendcmd(CMD_E,2);		
			if ( ps2code == 70 )	// F
				sendcmd(CMD_F,2);		
			if ( ps2code == 71 )	// G
				sendcmd(CMD_G,2);		
			if ( ps2code == 72 )	// H
				sendcmd(CMD_H,2);		
			if ( ps2code == 73 )	// I
				sendcmd(CMD_I,2);		
			if ( ps2code == 74 )	// J
				sendcmd(CMD_J,2);		
			if ( ps2code == 75 )	// K
				sendcmd(CMD_K,2);		
			if ( ps2code == 76 )	// L
				sendcmd(CMD_L,2);		
			if ( ps2code == 77 )	// M
				sendcmd(CMD_M,2);		
			if ( ps2code == 78 )	// N
				sendcmd(CMD_N,2);		
			if ( ps2code == 79 )	// O
				sendcmd(CMD_O,2);		
			if ( ps2code == 80 )	// P
				sendcmd(CMD_P,2);		
			if ( ps2code == 81 )	// Q
				sendcmd(CMD_Q,2);	
			if ( ps2code == 82 )	// R
				sendcmd(CMD_R,2);		
			if ( ps2code == 83 )	// S
				sendcmd(CMD_S,2);		
			if ( ps2code == 84 )	// T
				sendcmd(CMD_T,2);	
			if ( ps2code == 85 )	// U
				sendcmd(CMD_U,2);	
			if ( ps2code == 86 )	// V
				sendcmd(CMD_V,2);		
			if ( ps2code == 87 )	// W
				sendcmd(CMD_W,2);		
			if ( ps2code == 88 )	// X
				sendcmd(CMD_X,2);		
			if ( ps2code == 89 )	// Y
				sendcmd(CMD_Y,2);		
			if ( ps2code == 90 )	// Z
				sendcmd(CMD_Z,2);		
			if ( ps2code == 92 )  // '
				sendcmd(CMD_APOST,0); 
			if ( ps2code == 95 )  // ?
				sendcmd(CMD_QUEST,0); 
			if ( ps2code == 97 )	// a
				sendcmd(CMD_A,1);		
			if ( ps2code == 98 )	// b
				sendcmd(CMD_B,1);		
			if ( ps2code == 99 )	// c
				sendcmd(CMD_C,1);		
			if ( ps2code == 100 )	// d
				sendcmd(CMD_D,1);		
			if ( ps2code == 101 )	// e
				sendcmd(CMD_E,1);		
			if ( ps2code == 102 )	// f
				sendcmd(CMD_F,1);		
			if ( ps2code == 103 )	// g
				sendcmd(CMD_G,1);		
			if ( ps2code == 104 )	// h
				sendcmd(CMD_H,1);		
			if ( ps2code == 105 )	// i
				sendcmd(CMD_I,1);		
			if ( ps2code == 106 )	// j
				sendcmd(CMD_J,1);		
			if ( ps2code == 107 )	// k
				sendcmd(CMD_K,1);		
			if ( ps2code == 108 )	// l
				sendcmd(CMD_L,1);		
			if ( ps2code == 109 )	// m
				sendcmd(CMD_M,1);		
			if ( ps2code == 110 )	// n
				sendcmd(CMD_N,1);		
			if ( ps2code == 111 )	// o
				sendcmd(CMD_O,1);		
			if ( ps2code == 112 )	// p
				sendcmd(CMD_P,1);		
			if ( ps2code == 113 )	// q
				sendcmd(CMD_Q,1);		
			if ( ps2code == 114 )	// r
				sendcmd(CMD_R,1);		
			if ( ps2code == 115 )	// s
				sendcmd(CMD_S,1);		
			if ( ps2code == 116 )	// t
				sendcmd(CMD_T,1);		
			if ( ps2code == 117 )	// u
				sendcmd(CMD_U,1);		
			if ( ps2code == 118 )	// v
				sendcmd(CMD_V,1);		
			if ( ps2code == 119 )	// w
				sendcmd(CMD_W,1);		
			if ( ps2code == 120 )	// x
				sendcmd(CMD_X,1);		
			if ( ps2code == 121 )	// y
				sendcmd(CMD_Y,1);		
			if ( ps2code == 122 )	// z
				sendcmd(CMD_Z,1);		
		}
		else {	// Special keys
			if ( ps2raw == 277 )     // Left
				sendcmd(CMD_SBACK,0);
			if ( ps2raw == 278 )     // Right
				sendcmd(CMD_SFWD,0);
			if ( ps2raw == 279 )     // Up
				sendcmd(CMD_PREV,0);
			if ( ps2raw == 280 )     // DOWN
				sendcmd(CMD_NEXT,0);
			if ( ps2raw == 284 ) {    // Backspace
				sendcmd(CMD_SBACK,0);	
				delay(100);
				sendcmd(CMD_CLEAR,0);
			}
			if ( ps2raw == 282 )     // Delete
				sendcmd(CMD_CLEAR,0);
			if ( ps2raw == 283 )     // ESC
				sendcmd(CMD_STOP,0);
			if ( ps2raw == 286 )     // Enter
				sendcmd(CMD_NAME,0);
			if ( ps2raw == 353 )    // F1
				sendcmd(CMD_PLAY,0);
			if ( ps2raw == 354 )    // F2
				sendcmd(CMD_PAUSE,0);    
			if ( ps2raw == 355 )    // F3
				sendcmd(CMD_REC,0);
			if ( ps2raw == 364 )    //F12
				sendcmd(CMD_EJECT,0);
		}
	}
}


void sendcmd(char data[12], unsigned int modifier) {
	if ( modifier != 0 and modifier != currentmodifier ) {
		// 0 = Does not matter
		// 1 = lowercase
		// 2 = uppercase
		// 3 = numbers
		// 4 = symbols
		if ( modifier == 1 ) 
			dosend(CMD_CHAR);
		if ( modifier == 2 )
			dosend(CMD_CHAR);
		if ( modifier == 3 )
			dosend(CMD_NUM);
		if ( modifier == 4 )
			dosend(CMD_NUM);
		currentmodifier=modifier;
		delay(800); // Wait for MDS-JE510 between state changes.
	}
	dosend(data);
	if ( ALLOW_REMOTE == 1 ) {
		pinMode(IRDATA, INPUT);
	}
}
void dosend(char data[12]) {
	for ( int a=0; a < 2; a++ ) {   // Must send pulse two times
		digitalWrite(IRDATA,LOW);     // Init IR
		delayMicroseconds(2600);
		for ( int b=0; b < 13; b++ ) {
			if ( data[b] == 48 ) {      //0=Short pulse
				digitalWrite(IRDATA,HIGH);
				delayMicroseconds(400);  
				digitalWrite(IRDATA,LOW);
				delayMicroseconds(800);  
			}
			if ( data[b] == 49 ) {      //1=Long Pulse
				digitalWrite(IRDATA,HIGH);
				delayMicroseconds(400);  
				digitalWrite(IRDATA,LOW);
				delayMicroseconds(1400);  
			}
		}
		digitalWrite(IRDATA, HIGH);  // End
		delay(23);
	}
	delay(60); // Need delay between repeats
}
