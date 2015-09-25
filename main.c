#include <msp430.h>

int main ( void )
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    P1DIR |= BIT3;                  // Set P1.0 to output direction
    P1REN |= BIT3;                  // Enable pullup resistor on P1.3
    P1IE |= BIT3;                   // Enable the interrupts on P1.3
    P1IES |= BIT3;                  // Hi/Low edge on P1.3
    P1IFG &= ~BIT3;                 // Clear the interrupt flag on P1.3
    P1OUT &= ~0x01;                 // Turn off the led on P1.0

    _BIS_SR(CPUOFF + GIE);          // Turn off CPU and enable interrupts

    for ( ;; )
    {
        volatile unsigned int i;    // volatile to prevent optimization
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1 ( void )
{
    P1OUT ^= BIT0;                  // Flip led on P1.0
    P1IES ^= BIT3;                  // Flip Hi/low edge
    P1IFG &= ~BIT3;                 // Clear interrupt flag on P1.3
}
