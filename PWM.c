#include "PWM.h"
#include <avr/io.h>

void PWM_Init() {
	// Configurar el pin OC1A (PB1) como salida
	DDRB |= (1 << PB1);
	
	// Configurar el modo PWM de 8 bits con TOP = 0xFF
	TCCR1A |= (1 << WGM10) | (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << CS11); // Prescaler de 8
	
	// Configurar OC1A para la salida de PWM no invertida
	TCCR1A |= (1 << COM1A1);
	
	// Inicializar el PWM con un ciclo de trabajo del 0%
	OCR1A = 0;
}

void PWM_SetDutyCycle(uint8_t dutyCycle) {
	// Establecer el ciclo de trabajo (0-255)
	OCR1A = dutyCycle;
}
