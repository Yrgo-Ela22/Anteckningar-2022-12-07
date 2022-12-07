/********************************************************************************
* main.c: Demonstration av timerkretsar Timer 0 - Timer 2, som anv�nds f�r 
*         att toggla tre lysdioder anslutna till pin 8 - 10 (PORTB0 - PORTB2)
*         med blinkhastigheten 100 ms, 200 ms samt 500 ms.
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Initierar mikrodatorns I/O-portar och timerkretsar vid start. Sedan
*       h�lls programmet ig�ng s� l�nge matningssp�nning tillf�rs. Resten av
*       programmet �r avbrottsgenererat.
********************************************************************************/
int main(void)
{
   setup();

   while (1)
   {

   }

   return 0;
}

