/********************************************************************************
* header.h: Inneh�ller diverse definitioner och deklarationer f�r implementering
*           av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Inneh�ller information om I/O-register s�som PORTB. */
#include <avr/interrupt.h> /* Inneh�ller information om avbrottsvektorer s�som PCINT0_vect. */

/* Makrodefinitioner: */
#define LED1 PORTB0 /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define LED2 PORTB1 /* Lysdiod 2 ansluten till pin 9 (PORTB1). */
#define LED3 PORTB2 /* Lysdiod 3 ansluten till pin 10 (PORTB2). */

#define LED1_TOGGLE PINB = (1 << LED1) /* Togglar lysdiod 1. */
#define LED2_TOGGLE PINB = (1 << LED2) /* Togglar lysdiod 2. */
#define LED3_TOGGLE PINB = (1 << LED3) /* Togglar lysdiod 3. */

/********************************************************************************
* TIMERX_MAX_COUNT: Makron som inneh�ller maxv�rde som uppr�kning ska ske till
*                   g�llande antalet exekverade timeravbrott. Vi st�ller in
*                   timerkretsarna s� att avbrott sker var 0.128:e ms. D�rmed
*                   ber�knas antalet avbrott som kr�vs f�r �nskad tid i ms,
*                   avrundat till n�rmaste heltal.
*
*                   Exempelvis, f�r 100 ms kr�vs 100 / 0.128 = 781.25 avbrott,
*                   vilket avrundas till 781.
********************************************************************************/
#define TIMER0_MAX_COUNT (uint16_t)(100 / 0.128 + 0.5) /* Timer 0 l�per ut var 100:e ms. */
#define TIMER1_MAX_COUNT (uint16_t)(200 / 0.128 + 0.5) /* Timer 1 l�per ut var 200:e ms. */
#define TIMER2_MAX_COUNT (uint16_t)(500 / 0.128 + 0.5) /* Timer 2 l�per ut var 500:e ms. */

/********************************************************************************
* setup: Initierar mikrodatorns I/O-portar samt timerkretsar Timer 0 - Timer 2.
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */