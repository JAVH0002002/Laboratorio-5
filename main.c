#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"

void ADC_Init() {
	// Configurar AVCC como referencia de voltaje
	ADMUX |= (1 << REFS0);
	// Habilitar el ADC y configurar el preescaler a 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
	// Seleccionar el canal de ADC
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	// Iniciar la conversión ADC
	ADCSRA |= (1 << ADSC);
	// Esperar hasta que la conversión esté completa
	while (ADCSRA & (1 << ADSC));
	// Retornar el valor del ADC
	return ADC;
}

int main(void) {
	// Inicializar PWM y ADC
	PWM_Init();
	ADC_Init();
	
	// Configurar el pin del LED como salida
	DDRD |= (1 << PD5);
	
	uint16_t adcValue;
	uint8_t dutyCycle;
	
	while (1) {
		// Leer el valor del ADC desde el canal 0 (ADC0)
		adcValue = ADC_Read(0);
		// Escalar el valor del ADC al rango de 0-255
		dutyCycle = adcValue >> 2;
		// Establecer el ciclo de trabajo del PWM
		PWM_SetDutyCycle(dutyCycle);
		// Encender el LED
		PORTD |= (1 << PD5);
		// Esperar un momento para la siguiente lectura
		_delay_ms(100);
	}
	
	return 0;
}
