# Minidisc_keyboard

This project adds PS/2 Keyboard support
to Sony Mini disc decks like the MD-JE510

It support two operation modes:

Hardwired:
Intended to use internlly in the deck.
Connect IRDATA to IR receiver datapin
on the player pcb, as well as 5V and GND.
Set SIGNALTYPE to 0

Wireless:
Connect IRDATA to IR transmitter diode.
Set SIGNALTYPE to 1
