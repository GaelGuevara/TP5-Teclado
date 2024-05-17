#include "T_Mat.h"
#include "MKL25Z4.h"
#include <stdio.h>

#define columnas 4
#define filas 4

int columnas[columnas] = {0,1,2,3};
int filas[filas] = {4,5,6,7};

char teclas[filas][columnas] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


void GPIOS() {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;  
    for (int i = 0; i < columnas; i++){
        PORTA->PCR[columnas[i]]|=PORT_PCR_MUX(0)|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
    }
    for (int i = 0; i <filas ; i++){
        PORTA->PCR[filas[i]] |= PORT_PCR_MUX(1);
        PTA -> PSOR|= (1<<i);
    }
}

char keyLogger(){
    for (int i = 0; i < filas; i++){
        PTA -> PSOR|= (0<<filas[i]);
        for (int j = 0; j < columnas; j++){
            if (!(PTA-> PDIR&(1<<columnas[j]))){
                return teclas[i][j];
            }
        }
        PTA -> PSOR|= (1<<i);   
    }
}
