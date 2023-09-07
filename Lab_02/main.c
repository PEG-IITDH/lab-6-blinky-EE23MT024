#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#define STCTRL *((volatile long *) 0xE000E010)    // control and status
#define STRELOAD *((volatile long *) 0xE000E014)    // reload value
#define STCURRENT *((volatile long *) 0xE000E018)    // current value
#define COUNT_FLAG  (1 << 16)   // bit 16 of CSR automatically set to 1
                                            //   when timer expires
#define ENABLE      (1 << 0)    // bit 0 of CSR to enable the timer
#define CLKINT      (1 << 2)    // bit 2 of CSR to specify CPU clock
#define CLOCK_MHZ 16
#define MASK_BITS 0x11
            void Delay(int ms)
            {
                STCURRENT=0;
                STRELOAD = ms;                       // reload value for 'ms' milliseconds
                STCTRL |= (CLKINT | ENABLE);        // set internal clock, enable the timer

                while ((STCTRL & COUNT_FLAG) == 0)  // wait until flag is set
                {
                    ;   // do nothing
                }
                STCTRL = 0;                // stop the timer

                return;
            }

int main(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;
            GPIO_PORTF_LOCK_R = 0x4C4F434B;
            GPIO_PORTF_CR_R = 0x01;
            GPIO_PORTF_DIR_R = 0x0E;
            GPIO_PORTF_DEN_R = 0x1F;
            GPIO_PORTF_PUR_R = 0x11;
            int led = 0;
            int sw1;
            int n = 0;
            while(1)
            {
                sw1 = ~GPIO_PORTF_DATA_R & 0x10;
                Delay(1000);
                if(sw1==0x10 && n==0)
                {
                n=1;
                if(led==0)
                {
                    GPIO_PORTF_DATA_R = 0x02;
                    led++;
                }
                else if(led==1)
                {
                    GPIO_PORTF_DATA_R = 0x08;
                    led++;
                }
                else if(led==2)
                {
                    GPIO_PORTF_DATA_R = 0x04;
                    led=0;
                }
                }
                else if(sw1==0)
                {
                    n=0;
                    GPIO_PORTF_DATA_R = 0x00;
                }

            }


}
