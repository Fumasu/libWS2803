#include <WS2803.h>

#define WIDTH 10

int ClkPin =10;
int DataPin =11;
int pos =0;
int aktFarbe =0;

WS2803::Color farben[] ={
	WS2803::Red,
	WS2803::Green,
	WS2803::Blue,
	WS2803::White
};

WS2803* ws28;

//Hilfsfunktion um x, y Koordinate in 1-Dimensionalen Index umzurechnen
int getIndex(int x, int y) {
	return x + (y * WIDTH);
}

void setup() {
	ws28 =new WS2803(ClkPin, DataPin, 150);
	
	ws28->Clear();
}

void loop() {
//	ws28->setPixel(getindex(10, 2), 255, 0, 255);		//Setzt das Pixel an Position 10, 2 auf Magenta
	
	ws28->setPixel(pos !=0 ? pos - 1 : 149, WS2803::Black);	//Lösche alten Pixel
	ws28->setPixel(pos, farben[aktFarbe]);			//Setze neuen Pixel
	
	pos++;
	if(pos ==150) {
		pos =0;
		aktFarbe++;
		if(aktFarbe ==sizeof(farben) / sizeof(WS2803::Color))		//sizeof(farben) / sizeof(WS2803::Color) entspricht der Grösse des Array
			aktFarbe =0;
	}
	
	ws28->show();
	
	delay(1 / 60.0);
}