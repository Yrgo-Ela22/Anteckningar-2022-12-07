/********************************************************************************
* interrupts.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR (TIMER0_OVF_vect): Avbrottsrutin f�r Timer 0 i Normal Mode, d�r avbrott
*                        sker var 0.128:e ms vid overflow av r�knaren TCNT0.
*                        Varje exekverat avbrott r�knas via variabeln counter.
*                        Efter 100 ms (ca 781 avbrott) togglas lysdiod 1 och
*                        r�knaren nollst�lls inf�r n�sta uppr�kning.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= TIMER0_MAX_COUNT)
   {
      LED1_TOGGLE;
      counter = 0;
   }

   return;
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect): Avbrottsrutin f�r Timer 1 i CTC Mode, d�r avbrott
*                          sker var 0.128:e ms n�r r�knaren r�knat upp till 256.
*                          Varje exekverat avbrott r�knas via variabeln counter.
*                          Efter 200 ms (ca 1563 avbrott) togglas lysdiod 2 och
*                          r�knaren nollst�lls inf�r n�sta uppr�kning.
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= TIMER1_MAX_COUNT)
   {
      LED2_TOGGLE;
      counter = 0;
   }

   return;
}

/********************************************************************************
* ISR (TIMER2_OVF_vect): Avbrottsrutin f�r Timer 2 i Normal Mode, d�r avbrott
*                        sker var 0.128:e ms vid overflow av r�knaren TCNT2.
*                        Varje exekverat avbrott r�knas via variabeln counter.
*                        Efter 500 ms (ca 3906 avbrott) togglas lysdiod 3 och
*                        r�knaren nollst�lls inf�r n�sta uppr�kning.
********************************************************************************/
ISR (TIMER2_OVF_vect)
{
   static volatile uint16_t counter = 0;

   if (++counter >= TIMER2_MAX_COUNT)
   {
      LED3_TOGGLE;
      counter = 0;
   }

   return;
}

