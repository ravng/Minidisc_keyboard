# Minidisc_keyboard

This project adds PS/2 Keyboard port to Sony Mini disc HiFI Decks.


Tested on Sony MDS-JE510 but I see no reason for it not to work on other Sony decks as well.

There is two versions available:


mdkey:  Hardwired version (for mounting PS/2 connector internally in a deck)

mdkey-ir: Using an IR diode to convert PS/2 keyboard to wireless MD keyboard.

See Hookup folder for instruction how to connect.

Tested on Arduino UNO and Sony MDS-JE510


-----------------------------------------------------------------------------------------
COMPILING

Copy correct IR code file from ircodes to project directory and change IRcode include if
needed (default is RM-D7M).


-----------------------------------------------------------------------------------------
USAGE


Navigate tracks with UP/DOWN keys.

Edit name for selected track with ENTER.

Input the song name, it will automatically change between upper,lower,number and symbol.

Use LEFT/RIGHT arrows to navigate within the title.

Use Backspace to erase backwards, or DELETE to delete selected character.

Use ESC to exit without saving or ENTER to save.
  

Other keys:

F1 Play
  
F2 Pause
  
F3 Record

F5 Display
  
ESC Stop
 
F12 Eject
    

VALID INPUT CHARACTERS

A-Z a-z 0-9 . - / ' ? ! Space




-----------------------------------------------------------------------------------------
NOTES


Keyboard layout:

You might need to adjust the key actions depending on your keyboard layout for some keys

like: / - ' ? !


Missing characters:

I have copied the IR codes from my RM-D7M remote. This remote lacks some symbols, like :

I am sure there exists IR codes for those symbols as well, so if anyone can help out

that would be great!

