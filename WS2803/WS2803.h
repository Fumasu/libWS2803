#ifndef _WS2803_H_
#define _WS2803_H_

#include <stdint.h>
#include <math.h>

#include <Arduino.h>

//#define fastWrite(_pin, _state) fastDigitalWrite(_pin, _state)
//#define fastWrite(_pin_, _state_) ( _pin_ < 8 ? (_state_ ?  PORTD |= 1 << _pin_ : PORTD &= ~(1 << _pin_ )) : (_state_ ?  PORTB |= 1 << (_pin_ -8) : PORTB &= ~(1 << (_pin_ -8)  )))
#define fastWrite(_pin_, _state_) digitalWrite(_pin_, _state_)

uint8_t gamma_table[] ={
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 2, 2, 2, 3, 3, 3, 3, 3, 4,
        4, 4, 4, 5, 5, 5, 5, 6, 6, 6,
        7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
        10, 10, 11, 11, 12, 12, 13, 13, 13, 14,
        14, 15, 15, 16, 16, 17, 17, 18, 18, 19,
        19, 20, 21, 21, 22, 22, 23, 23, 24, 25,
        25, 26, 27, 27, 28, 29, 29, 30, 31, 31,
        32, 33, 33, 34, 35, 36, 36, 37, 38, 39,
        40, 40, 41, 42, 43, 44, 45, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 55, 56,
        57, 58, 59, 60, 61, 62, 63, 65, 66, 67,
        68, 69, 70, 71, 72, 73, 74, 75, 77, 78,
        79, 80, 81, 82, 84, 85, 86, 87, 88, 90,
        91, 92, 93, 95, 96, 97, 99, 100, 101, 103,
        104, 105, 107, 108, 109, 111, 112, 114, 115, 117,
        118, 119, 121, 122, 124, 125, 127, 128, 130, 131,
        133, 135, 136, 138, 139, 141, 142, 144, 146, 147,
        149, 151, 152, 154, 156, 157, 159, 161, 162, 164,
        166, 168, 169, 171, 173, 175, 176, 178, 180, 182,
        184, 186, 187, 189, 191, 193, 195, 197, 199, 201,
        203, 205, 207, 209, 211, 213, 215, 217, 219, 221,
        223, 225, 227, 229, 231, 233, 235, 237, 239, 241,
        244, 246, 248, 250, 252, 255
};

class WS2803 {
public:
	typedef struct {
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
	}Color;
	
	static Color Black, Red, Green, Blue, White, Grey;		//Vordefinierte Farben
	
	WS2803(int ClkPin, int DataPin, int anzLeds);
	
	void show();
	void setPixel(int led, Color c);
	void setPixel(int led, unsigned char Red, unsigned char Green, unsigned char Blue);
	
	void Clear();
	void Fill(Color c);
	void Fill(unsigned char Red, unsigned char Green, unsigned char Blue);
private:
	int m_iClkPin;
	int m_iDataPin;
	int m_iAnzLeds;
	int m_iChips;
	Color* m_vLed;
	
	void SendByte(unsigned char b);
	void setzePin(int pin);
	void loeschePin(int pin);
};

WS2803::Color WS2803::Black ={0, 0, 0};
WS2803::Color WS2803::Red ={255, 0, 0};
WS2803::Color WS2803::Green ={0, 255, 0};
WS2803::Color WS2803::Blue ={0, 0, 255};
WS2803::Color WS2803::White ={255, 255, 255};
WS2803::Color WS2803::Grey ={32, 32, 32};

void WS2803::setzePin(int pin) {
	if(pin ==10)
		PORTB |= _BV(PB4);
	else
		PORTB |= _BV(PB6);
}

void WS2803::loeschePin(int pin) {
	if(pin ==10)
		PORTB &= ~_BV(PB4);
	else
		PORTB &= ~_BV(PB6);
}

WS2803::WS2803(int ClkPin, int DataPin, int anzLeds) : m_iClkPin(ClkPin), m_iDataPin(DataPin), m_iAnzLeds(anzLeds) {
	m_iChips =(int)ceil((double)anzLeds / 6.0);
	m_vLed =new Color[anzLeds];
	
	pinMode(m_iClkPin, OUTPUT);
	pinMode(m_iDataPin, OUTPUT);
	
/*	fastWrite(m_iClkPin, LOW);
	fastWrite(m_iDataPin, LOW);*/
	loeschePin(m_iClkPin);
	loeschePin(m_iDataPin);
	
	delayMicroseconds(600);
}

void WS2803::setPixel(int led, unsigned char Red, unsigned char Green, unsigned char Blue) {
	if(led <0 || led >=m_iAnzLeds)
		return;
	
	m_vLed[led].Red =Red;
	m_vLed[led].Green =Green;
	m_vLed[led].Blue =Blue;
}

void WS2803::setPixel(int led, Color c) {
	setPixel(led, c.Red, c.Green, c.Blue);
}

void WS2803::show() {
	for(int i =0;i <m_iAnzLeds;i++) {
		SendByte(m_vLed[i].Red);
		SendByte(m_vLed[i].Green);
		SendByte(m_vLed[i].Blue);
	}
	
	if((m_iChips * 6) - m_iAnzLeds !=0) {
	//if(m_iAnzLeds%6 !=0) {							//Falls die Anzahl der LED's nicht glatt durch 6 teilbar ist
		for(int i =0;i <6 - m_iAnzLeds%6;i++) {		//dann werden die restlichen (nicht vorhandenen LED's) auf Schwarz gesetzt
			SendByte(WS2803::Black.Red);
			SendByte(WS2803::Black.Green);
			SendByte(WS2803::Black.Blue);
		}
	}
	
	delayMicroseconds(600);
}

void WS2803::SendByte(unsigned char b) {
	for(int digit =7;digit >=0;digit--) {
//		fastWrite(m_iClkPin, LOW);
		loeschePin(m_iClkPin);
		
		if(b & (1<<digit)) {
//			fastWrite(m_iDataPin, HIGH);
			setzePin(m_iDataPin);
		}
		else {
//			fastWrite(m_iDataPin, LOW);
			loeschePin(m_iDataPin);
		}
		
//		fastWrite(m_iClkPin, HIGH);
		setzePin(m_iClkPin);
	}
	
//	fastWrite(m_iClkPin, LOW);
	loeschePin(m_iClkPin);
}

void WS2803::Fill(unsigned char Red, unsigned char Green, unsigned char Blue) {
	for(int i =0;i <m_iAnzLeds;i++) {
		setPixel(i, gamma_table[Red], gamma_table[Green], gamma_table[Blue]);
	}
}

void WS2803::Clear() {
	Fill(0, 0, 0);
}

void WS2803::Fill(Color c) {
	Fill(c.Red, c.Green, c.Blue);
}

#endif
