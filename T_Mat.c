#include "T_Mat.h"
#include "MKL25Z4.h"
#include <stdio.h>

#define columnas 4
#define filas 4

char teclas[filas][Columnas] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


void GPIOS() {
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;  
    for (int i = 0; i <(filas + columnas); i++){
        i < columnas? PORTA->PCR[i] |= PORT_PCR_MUX(1): ;
        i >= columnas? PORTA->PCR[i] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK: ;
    }
    for (int i = 4; i <(filas + columnas) ; i++){
        PTA -> PSOR|= (1<<i);
    }
}

char keyLogger(){
    for (int i = 0; i < filas; i++){
        PTA -> PSOR|= (0<<i);
        for (int j = 0; j < columnas; j++){
            if (!(PTA-> PDIR&(1<<j))){
                return teclas[i][j];
            }
        }
        PTA -> PSOR|= (1<<i);   
    }
}