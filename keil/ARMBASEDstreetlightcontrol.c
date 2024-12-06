#include <lpc214x.h>
#include "armuart.h"
#include <stdio.h>

int adcreading[5];
int ADC_result(void);
int compare;

void delay(unsigned int t){
   unsigned int a,j;
   for(a = 0; a < t; a++)
   { for(j = 0; j<10000; j++);}
 	 }
	 
int main() {
    PINSEL1 = 0x00080000; // Configure AD0.1 pin for ADC functionality
	  PINSEL2=  0x00000000;
	  IODIR1=   0x00030000;
    AD0CR=0x00200200|(1<<1);
    while (1) {
       compare = ADC_result();
			 if(compare>600){   //Set according to your lux need
				 IOCLR1=0x00030000;
			 }
			 else{
				 IOSET1=0x00030000;
			 }
    }
}

int ADC_result(void){
unsigned int result;
        unsigned int i=0;
        // Start ADC conversion on AD0.1
        AD0CR = AD0CR | (1 << 24);
        // Wait for conversion to complete (DONE bit in AD0GDR)
        while ((AD0GDR & 0x80000000) == 0);
        print("  ADC :");
        // Extract 10-bit result from AD0GDR
        result = AD0GDR;   // result at 15 - 6 bit 
        result = result >> 6;// we want 10bit at 0-9 so we are shifting by 6
        result = result & 0x000003FF;
	      compare = result;
        while(i<=3){
					adcreading[i]=(result%10);
					result=result/10;
					i++;
				}
				while(i!=0){
					i=i-1;
					print1(adcreading[i]+'0');
				}
				return compare;
}


