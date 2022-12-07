/********************************************************************************
* setup.c: Innehåller initieringsrutiner.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static inline void init_ports(void);
static inline void init_timers(void);

/********************************************************************************
* setup: Initierar mikrodatorns I/O-portar samt timerkretsar Timer 0 - Timer 2.
********************************************************************************/
void setup(void)
{
   init_ports();
   init_timers();
   return;
}

/********************************************************************************
* init_ports: Sätter lysdiodernas pinnar till utportar genom att ettställa
*             motsvarande bitar i datariktningsregister DDRB.
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   return;
}

/********************************************************************************
* init_timers: Initierar timerkretsar Timer 0 - Timer 2 så att timergenererat
*              avbrott sker var 0.128 ms per timerkrets.
*
*              1. Vi aktiverar avbrott globalt genom att ettställa I-flaggan
*                 i statusregister SREG via assemblerinstruktionen SEI.
*
*              2. Vi ställer in uppräkningsfrekvens av Timer 0 så att avbrott
*                 sker var 0.128:e ms via ettställning av biten CS01 (Clock
*                 Select 0 bit 1) i kontrolregistret TCCR0B (Timer/Counter
*                 Control Register 0 B).
*
*              3. Vi aktiverar avbrott på Timer 0 i Normal Mode (avbrott vid
*                 overflow) genom att ettställa biten TOIE0 (Timer/Counter 
*                 Overflow Interrupt Enable 0) i maskregistret TIMSK0 
*                 (Timer/Counter Mask Register 0). Avbrottrutinens
*                 avbrottsvektor i Normal Mode är TIMER0_OVF_vect.
*
*              4. Vi ställer in Timer 1 i CTC Mode (Clear Timer On Compare Match)
*                 så att uppräkning sker till det värde vi lägger i register
*                 OCR1A (Output Compare Register 1 A), vilket är 256, så att
*                 räknar upp till samma värde som Timer 0 (som fick overflow
*                 vid 256, men eftersom Timer 1 är 16 bitar så måste vi sätta
*                 maxvärdet lägre, annars sker uppräkning till 65 535, vilket
*                 tar ca 33 ms). Vi ställer samtidigt in uppräkningshastigheten
*                 så att avbrott sker var 0.128:e ms via ettställning av biten
*                 CS11 (Clock Select 1 bit 1) i kontrollregistret TCCR1B
*                 (Timer/Counter Control Register 1 B).
*
*              5. Vi aktiverar avbrott på Timer 1 när räknaren TCNT1 har räknat
*                 upp till värdet i register OCR1A (256) via ettställning av
*                 biten OCIE1A (Output Compare Interrupt Enable 1 A) i
*                 maskregistret TIMSK1 (Timer/Counter Mask Register 1).
*                 Notera att biten slutar på A, då värdet vi räknade upp till
*                 lades i OCR1A (notera A, det finns också ett B-register OCR1B).
*                 Vi kommer då få avbrott var 0.128:e millisekund precis som
*                 för Timer 0. Avbrottsvektorn är TIMER1_COMPA_vect.
*
*              6. Vi ställer in uppräkningsfrekvens av Timer 2 så att avbrott
*                 sker var 0.128:e ms via ettställning av biten CS21 (Clock
*                 Select 2 bit 1) i kontrolregistret TCCR2B (Timer/Counter
*                 Control Register 2 B).
*
*              7. Vi aktiverar avbrott på Timer 2 i Normal Mode (avbrott vid
*                 overflow) genom att ettställa biten TOIE2 (Timer/Counter
*                 Overflow Interrupt Enable 2) i maskregistret TIMSK2
*                 (Timer/Counter Mask Register 2). Avbrottrutinens
*                 avbrottsvektor i Normal Mode är TIMER2_OVF_vect.
********************************************************************************/
static inline void init_timers(void)
{
   asm("SEI");
   TCCR0B = (1 << CS01);
   TIMSK0 = (1 << TOIE0);

   TCCR1B = (1 << WGM12) | (1 << CS11);
   OCR1A = 256;
   TIMSK1 = (1 << OCIE1A);

   TCCR2B = (1 << CS21);
   TIMSK2 = (1 << TOIE2);
   return;
}