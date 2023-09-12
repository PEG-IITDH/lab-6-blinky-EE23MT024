#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#define led  int[3]  [0x02,0x04,0x08]
#define SYST_CSR             (*((volatile uint32_t *)0xE000E010))
#define SYST_RVR             (*((volatile uint32_t *)0xE000E014))
#define SYST_CVR             (*((volatile uint32_t *)0xE000E018))
#define MASK_BITS 0x11

void system_config(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x01;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x11;
}


void SysTick_Handler(void)
{
    GPIO_PORTF_DATA_R =0x00;
    SYST_CSR=0x00;
    GPIO_PORTF_ICR_R = MASK_BITS;
    GPIO_PORTF_IM_R |= MASK_BITS;
}

void portf_Handler(void)
{
    SYST_CVR&=0x00;
    if(GPIO_PORTF_MIS_R & 0X01)
    {
        GPIO_PORTF_DATA_R =0x0E;
        GPIO_PORTF_ICR_R = MASK_BITS;
        GPIO_PORTF_IM_R &= ~MASK_BITS;
        SYST_RVR = 16*1000000;
        SYST_CSR|=0x07;



    }


}

int main(void)

 {
    system_config();
    SYST_CVR&=0x00;
    SYST_RVR=16000000;

    GPIO_PORTF_DATA_R&=0x00;
    GPIO_PORTF_IM_R &= ~MASK_BITS;
    GPIO_PORTF_IS_R &= ~MASK_BITS;
    GPIO_PORTF_IBE_R &= ~MASK_BITS;
    GPIO_PORTF_IEV_R &= ~MASK_BITS;

    NVIC_PRI7_R = (NVIC_PRI7_R & 0xF1FFFFFF) | (7 << 21);
    NVIC_EN0_R |= 1 << 30;
    GPIO_PORTF_ICR_R = MASK_BITS;
    GPIO_PORTF_IM_R |= MASK_BITS;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x1FFFFFFF) | (3 << 29) ;
    while(1)
    {


    }

}
