/*
PS/2 Keyboard to MiniDisc
By Ravn Gundersen <ravn@sixbynine.no>
---------------------------------------
This project adds PS/2 Keyboard support
to Sony Mini disc decks. 

Connect IRDATA to IR receiver datapin
on the player pcb, as well as 5V and GND.


Project requires the following external libraries:
PS2KeyAdvanced	By Paul Carpenter https://github.com/techpaul/PS2KeyAdvanced
PS2KeyMap 		By Paul Carpenter https://github.com/techpaul/PS2KeyMap


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
Display			F5
Eject           F12

*/

#include <PS2KeyAdvanced.h>
#include <PS2KeyMap.h>
#include "RM-D7M.h"			// Set to correct IR code file.
#define DATAPIN	8			// PS/2 Data
#define IRQPIN	2			// PS/2 Clock/IRQ 
#define IRDATA	3			// IR output pin
#define ALLOW_REMOTE	0	// Set to 1 to allow for both keyboard and remote control to work simultaneous. Note that this slows down keyboard some!
PS2KeyAdvanced keyboard;
PS2KeyMap keymap;

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
	keyboard.resetKey(); 
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
			if ( ps2code == 40 )  // .
				sendcmd(CMD_RPAR,0);   
			if ( ps2code == 42 )  // .
				sendcmd(CMD_LPAR,0);   
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
			if ( ps2raw == 286 ) {    // Enter
				sendcmd(CMD_NAME,0);
				currentmodifier = 2;
			}
			if ( ps2raw == 353 )    // F1
				sendcmd(CMD_PLAY,0);
			if ( ps2raw == 354 )    // F2
				sendcmd(CMD_PAUSE,0);    
			if ( ps2raw == 355 )    // F3
				sendcmd(CMD_REC,0);
			if ( ps2raw == 357 )    // F5
				sendcmd(CMD_DISPLAY,0);
			if ( ps2raw == 364 )    //F12
				sendcmd(CMD_EJECT,0);
		}
	}
}


void sendcmd(char data[12], unsigned int modifier) {
	if ( modifier != 0 and modifier != currentmodifier ) {
		if ( currentmodifier == 3 and modifier == 1 )
			modifier=4;
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
		if ( modifier == 4 ) {
			dosend(CMD_CHAR);
			delay(50);
			dosend(CMD_CHAR);
		}	
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
