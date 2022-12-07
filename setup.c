/********************************************************************************
* setup.c: Inneh�ller initieringsrutiner.
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
* init_ports: S�tter lysdiodernas pinnar till utportar genom att ettst�lla
*             motsvarande bitar i datariktningsregister DDRB.
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   return;
}

/********************************************************************************
* init_timers: Initierar timerkretsar Timer 0 - Timer 2 s� att timergenererat
*              avbrott sker var 0.128 ms per timerkrets.
*
*              1. Vi aktiverar avbrott globalt genom att ettst�lla I-flaggan
*                 i statusregister SREG via assemblerinstruktionen SEI.
*
*              2. Vi st�ller in uppr�kningsfrekvens av Timer 0 s� att avbrott
*                 sker var 0.128:e ms via ettst�llning av biten CS01 (Clock
*                 Select 0 bit 1) i kontrolregistret TCCR0B (Timer/Counter
*                 Control Register 0 B).
*
*              3. Vi aktiverar avbrott p� Timer 0 i Normal Mode (avbrott vid
*                 overflow) genom att ettst�lla biten TOIE0 (Timer/Counter 
*                 Overflow Interrupt Enable 0) i maskregistret TIMSK0 
*                 (Timer/Counter Mask Register 0). Avbrottrutinens
*                 avbrottsvektor i Normal Mode �r TIMER0_OVF_vect.
*
*              4. Vi st�ller in Timer 1 i CTC Mode (Clear Timer On Compare Match)
*                 s� att uppr�kning sker till det v�rde vi l�gger i register
*                 OCR1A (Output Compare Register 1 A), vilket �r 256, s� att
*                 r�knar upp till samma v�rde som Timer 0 (som fick overflow
*                 vid 256, men eftersom Timer 1 �r 16 bitar s� m�ste vi s�tta
*                 maxv�rdet l�gre, annars sker uppr�kning till 65 535, vilket
*                 tar ca 33 ms). Vi st�ller samtidigt in uppr�kningshastigheten
*                 s� att avbrott sker var 0.128:e ms via ettst�llning av biten
*                 CS11 (Clock Select 1 bit 1) i kontrollregistret TCCR1B
*                 (Timer/Counter Control Register 1 B).
*
*              5. Vi aktiverar avbrott p� Timer 1 n�r r�knaren TCNT1 har r�knat
*                 upp till v�rdet i register OCR1A (256) via ettst�llning av
*                 biten OCIE1A (Output Compare Interrupt Enable 1 A) i
*                 maskregistret TIMSK1 (Timer/Counter Mask Register 1).
*                 Notera att biten slutar p� A, d� v�rdet vi r�knade upp till
*                 lades i OCR1A (notera A, det finns ocks� ett B-register OCR1B).
*                 Vi kommer d� f� avbrott var 0.128:e millisekund precis som
*                 f�r Timer 0. Avbrottsvektorn �r TIMER1_COMPA_vect.
*
*              6. Vi st�ller in uppr�kningsfrekvens av Timer 2 s� att avbrott
*                 sker var 0.128:e ms via ettst�llning av biten CS21 (Clock
*                 Select 2 bit 1) i kontrolregistret TCCR2B (Timer/Counter
*                 Control Register 2 B).
*
*              7. Vi aktiverar avbrott p� Timer 2 i Normal Mode (avbrott vid
*                 overflow) genom att ettst�lla biten TOIE2 (Timer/Counter
*                 Overflow Interrupt Enable 2) i maskregistret TIMSK2
*                 (Timer/Counter Mask Register 2). Avbrottrutinens
*                 avbrottsvektor i Normal Mode �r TIMER2_OVF_vect.
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