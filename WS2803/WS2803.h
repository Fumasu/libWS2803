#ifndef _WS2803_H_
#define _WS2803_H_

#include <stdint.h>
#include <math.h>

#include <Arduino.h>

//#define fastWrite(_pin_, _state_) ( _pin_ < 8 ? (_state_ ?  PORTD |= 1 << _pin_ : PORTD &= ~(1 << _pin_ )) : (_state_ ?  PORTB |= 1 << (_pin_ -8) : PORTB &= ~(1 << (_pin_ -8)  )))
#define fastWrite(_pin_, _state_) digitalWrite(_pin_, _state_)

class WS2803 {
public:
	typedef struct {
		unsigned char Red;
		unsigned char Green;
		unsigned char Blue;
	}Color;
	
	static Color Black, Red, Green, Blue, White;		//Vordefinierte Farben
	
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
};

WS2803::Color WS2803::Black ={0, 0, 0};
WS2803::Color WS2803::Red ={255, 0, 0};
WS2803::Color WS2803::Green ={0, 255, 0};
WS2803::Color WS2803::Blue ={0, 0, 255};
WS2803::Color WS2803::White ={255, 255, 255};

WS2803::WS2803(int ClkPin, int DataPin, int anzLeds) : m_iClkPin(ClkPin), m_iDataPin(DataPin), m_iAnzLeds(anzLeds) {
	m_iChips =ceil(anzLeds / 6);
	m_vLed =new Color[anzLeds];
	
	pinMode(m_iClkPin, OUTPUT);
	pinMode(m_iDataPin, OUTPUT);
	
	fastWrite(m_iClkPin, LOW);
	fastWrite(m_iDataPin, LOW);
	
	delayMicroseconds(600);
}

void WS2803::setPixel(int led, unsigned char Red, unsigned char Green, unsigned char Blue) {
	if(led <=0 || led >=m_iAnzLeds)
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
	
	if(m_iAnzLeds%6 !=0) {							//Falls die Anzahl der LED's nicht glatt durch 6 teilbar ist
		for(int i =0;i <6 - m_iAnzLeds%6;i++) {		//dann werden die restlichen (nicht vorhandenen LED's) auf Schwarz gesetzt
			SendByte(WS2803::Black.Red);
			SendByte(WS2803::Black.Green);
			SendByte(WS2803::Black.Blue);
		}
	}
}

void WS2803::SendByte(unsigned char b) {
	fastWrite(m_iClkPin, LOW);

	for(int digit =7;digit >=0;digit--) {
		if(b & (1<<digit)) {
			fastWrite(m_iDataPin, HIGH);
		}
		else {
			fastWrite(m_iDataPin, LOW);
		}
		
		fastWrite(m_iClkPin, HIGH);
	}
	
	fastWrite(m_iClkPin, LOW);
}

void WS2803::Fill(unsigned char Red, unsigned char Green, unsigned char Blue) {
	for(int i =0;i <m_iAnzLeds;i++) {
		setPixel(i, Red, Green, Blue);
	}
}

void WS2803::Clear() {
	Fill(0, 0, 0);
}

void WS2803::Fill(Color c) {
	Fill(c.Red, c.Green, c.Blue);
}

#endif