#include <WS2803.h>

#define WIDTH 10
#define HEIGHT 15

int ClkPin =10;
int DataPin =12;
int aktFarbe =0;
char feld[10 * 4][15 * 4];
char* chars[256];
bool taste[150];
int aktuellesProgramm =0;

void gbham(int xstart,int ystart,int xend,int yend, WS2803::Color farbe);
void rasterCircle(int x0, int y0, int radius, WS2803::Color farbe);

typedef void (*programme)();
programme progs[] ={
	logo,
	text,
	balken,
	springenderPunkt,
	lichtstimmung,
	lauflicht,
	screensaver,
	game_of_life,
	quadrat,
	kreis,
	starfield,
	plasma
};

WS2803::Color farben[] ={
	WS2803::Red,
	WS2803::Green,
	WS2803::Blue,
	WS2803::White
};

WS2803* ws28;

//Hilfsfunktion um x, y Koordinate in 1-Dimensionalen Index umzurechnen
int getIndex(int x, int y) {
	if(x <0 || x >=WIDTH)
		return -1;
	if(y <0 || y >=HEIGHT)
		return -1;
	return x + (y * WIDTH);
}

void nextProg() {
	aktuellesProgramm++;
	if(aktuellesProgramm >=sizeof(progs) / sizeof(programme))
		aktuellesProgramm =0;
}

void setup() {
	ws28 =new WS2803(ClkPin, DataPin, 150);
	
	ws28->Clear();
	
	//LEDs runter-faden
	ws28->Fill(WS2803::White);
	ws28->show();
	for(int i =255;i >=0;i -=10) {
		ws28->Fill(i, i, i);
		ws28->show();
	}

	ws28->Clear();
	Serial.begin(9600);
}

void loop() {
	//Eingänge lesen
/*	for(int i =0;i <150;i++) {
		if(digitalRead(i)) taste[i] =true;
		else taste[i] =false;
	}
	//Programm umschalten
	if(taste[1] && taste[8])
		nextProg();*/
//	ws28->setPixel(getindex(10, 2), 255, 0, 255);		//Setzt das Pixel an Position 10, 2 auf Magenta

	ws28->Clear();

	progs[aktuellesProgramm]();
	
	ws28->show();
	
	delay(100);
}

void drawText(int x, int y, char** text, int len) {
	for(int i =0;i <len;i++) {
		drawChar(x + i * 5, y, text[i]);
	}
}

void drawText2(int x, int y, char* text, int len) {
	for(int i =0;i <len;i++) {
		drawChar(x + i * 5, y, chars[text[i]]);
	}
}

void drawChar(int x, int y, char* c) {
	for(int tx =0;tx <4;tx++) {
		for(int ty =0;ty <5;ty++) {
			if(c[tx + (ty * 4)]) ws28->setPixel(getIndex(tx + x, y - ty), WS2803::Red);
		}
	}
}

void text() {
	static bool init =false;
	static char E[] ={1,1,1,1,
			  1,0,0,0,
			  1,1,1,0,
			  1,0,0,0,
			  1,1,1,1};
	static char A[] ={0,1,1,0,
			  1,0,0,1,
			  1,1,1,1,
			  1,0,0,1,
			  1,0,0,1};
	static char B[] ={1,1,1,0,
			  1,0,0,1,
			  1,1,1,0,
			  1,0,0,1,
			  1,1,1,1};
	static char C[] ={0,1,1,1,
			  1,0,0,0,
			  1,0,0,0,
			  1,0,0,0,
			  0,1,1,1};
	static char D[] ={1,1,1,0,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,1,1,0};
	static char F[] ={1,1,1,1,
			  1,0,0,0,
			  1,1,1,0,
			  1,0,0,0,
			  1,0,0,0};
	static char G[] ={0,1,1,0,
			  1,0,0,0,
			  1,0,1,1,
			  1,0,0,1,
			  0,1,1,0};
	static char H[] ={1,0,0,1,
			  1,0,0,1,
			  1,1,1,1,
			  1,0,0,1,
			  1,0,0,1};
	static char I[] ={1,1,1,0,
			  0,1,0,0,
			  0,1,0,0,
			  0,1,0,0,
			  1,1,1,0};
	static char J[] ={1,1,1,1,
			  0,0,1,0,
			  0,0,1,0,
			  1,0,1,0,
			  0,1,0,0};
	static char K[] ={1,0,0,1,
			  1,0,1,0,
			  1,1,0,0,
			  1,0,1,0,
			  1,0,0,1};
	static char L[] ={1,0,0,0,
			  1,0,0,0,
			  1,0,0,0,
			  1,0,0,0,
			  1,1,1,0};
	static char M[] ={1,1,1,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,1,1,1};
	static char N[] ={1,0,0,1,
			  1,1,0,1,
			  1,0,1,1,
			  1,0,0,1,
			  1,0,0,1};
	static char O[] ={0,1,1,0,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  0,1,1,0};
	static char P[] ={1,1,1,0,
			  1,0,0,1,
			  1,1,1,0,
			  1,0,0,0,
			  1,0,0,0};
	static char Q[] ={0,1,1,0,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,1,1,
			  0,1,1,1};
	static char R[] ={1,1,1,0,
			  1,0,0,1,
			  1,1,1,0,
			  1,0,1,0,
			  1,0,0,1};
	static char S[] ={1,1,1,1,
			  1,0,0,0,
			  1,1,1,1,
			  0,0,0,1,
			  1,1,1,1};
	static char T[] ={1,1,1,0,
			  0,1,0,0,
			  0,1,0,0,
			  0,1,0,0,
			  0,1,0,0};
	static char U[] ={1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  0,1,1,0};
	static char V[] ={1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,1,0,
			  0,1,0,0};
	static char W[] ={1,1,1,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,0,0,1,
			  1,1,1,1};
	static char X[] ={1,0,0,1,
			  1,0,0,1,
			  0,1,1,0,
			  1,0,0,1,
			  1,0,0,1};
	static char Y[] ={1,0,0,1,
			  1,0,0,1,
			  0,1,1,0,
			  0,0,1,0,
			  0,1,0,0};
	static char Z[] ={1,1,1,1,
			  0,0,0,1,
			  0,1,1,0,
			  1,0,0,0,
			  1,1,1,1};
	static char N1[] ={0,0,1,1,
			   0,1,0,1,
			   0,0,0,1,
			   0,0,0,1,
			   0,0,0,1};
	static char N2[] ={0,1,1,1,
			   0,0,0,1,
			   0,0,1,1,
			   0,1,0,0,
			   0,1,1,1};
	static char N3[] ={0,1,1,1,
			   0,0,0,1,
			   0,0,1,1,
			   0,0,0,1,
			   0,1,1,1};
	static char N4[] ={0,1,0,0,
			   0,1,0,1,
			   0,1,1,1,
			   0,0,0,1,
			   0,0,0,1};
	static char N5[] ={0,1,1,1,
			   0,1,0,0,
			   0,1,1,0,
			   0,0,0,1,
			   0,1,1,1};
	static char N6[] ={0,1,1,0,
			   0,1,0,0,
			   0,1,1,1,
			   0,1,0,1,
			   0,1,1,1};
	static char N7[] ={1,1,1,0,
			   0,0,1,0,
			   0,1,1,1,
			   0,0,1,0,
			   0,0,1,0};
	static char N8[] ={0,1,1,1,
			   0,1,0,1,
			   0,1,1,1,
			   0,1,0,1,
			   0,1,1,1};
	static char N9[] ={0,1,1,1,
			   0,1,0,1,
			   0,1,1,1,
			   0,0,0,1,
			   0,0,0,1};
	static char N0[] ={1,1,1,1,
			   1,0,0,1,
			   1,0,0,1,
			   1,0,0,1,
			   1,1,1,1};
	static char SPACE[] ={0,0,0,0,
			      0,0,0,0,
			      0,0,0,0,
			      0,0,0,0,
			      0,0,0,0};

	if(!init) {
		char* tmp['Z' - 'A' + 1] ={A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
		init =true;
		for(char i ='A';i <='Z';i++) {
			chars[i] =tmp[i - 'A'];
		}
		for(char i ='a';i <='z';i++) {
			chars[i] =tmp[i - 'a'];
		}
		chars[' '] =SPACE;
		tmp[0] =N0;
		tmp[1] =N1;
		tmp[2] =N2;
		tmp[3] =N3;
		tmp[4] =N4;
		tmp[5] =N5;
		tmp[6] =N6;
		tmp[7] =N7;
		tmp[8] =N8;
		tmp[9] =N9;
		for(int i ='0';i <='9';i++) {
			chars[i] =tmp[i - '0'];

		}
	}

	static int Xpos =0;
	static char* text[] ={H, A, L, L, O, SPACE, C, H, R, I, S, T, O, P, H};
	static char text2[] ="Elektro Heikes";
	drawText2(Xpos, 14, text2, sizeof(text2) - 1);
//	drawText(Xpos, 14, text, 15);

	Serial.println((sizeof(text2) - 1) * 5 - 2);
	Xpos--;
	if(Xpos <=-(14 * 5 - 2))
		Xpos =9;

	delay(0);
}

void logo() {
	WS2803::Color farbe;
	
	farbe.Red =0;
	farbe.Green =255;
	farbe.Blue =255;

	//oben
	gbham(3, 3, 6, 3, farbe);
	gbham(2, 4, 7, 4, farbe);
	gbham(3, 5, 6, 5, farbe);
	gbham(4, 6, 5, 6, farbe);

	//unten
	gbham(4, 9, 5, 9, farbe);
	gbham(3, 10, 6, 10, farbe);
	gbham(2, 11, 7, 11, farbe);
	gbham(3, 12, 6, 12, farbe);

	//links
	gbham(0, 6, 0, 9, farbe);
	gbham(1, 5, 1, 10, farbe);

	//rechts
	gbham(8, 5, 8, 10, farbe);
	gbham(9, 6, 9, 9, farbe);
}

void balken() {
	static char amplituden[10] ={10};

	for(int i =0;i <10;i++) {
		gbham(i, 0, i, amplituden[i], WS2803::Grey);
		amplituden[i] =1 + random(14);
	}
}

void lauflicht() {
	static int pos =0;
	
	ws28->setPixel(pos !=0 ? pos - 1 : 149, WS2803::Black);	//Lösche alten Pixel
	ws28->setPixel(pos, farben[aktFarbe]);			//Setze neuen Pixel
	
	pos++;
	if(pos ==150) {
		pos =0;
		aktFarbe++;
		if(aktFarbe ==sizeof(farben) / sizeof(WS2803::Color))		//sizeof(farben) / sizeof(WS2803::Color) entspricht der Grösse des Array
			aktFarbe =0;
	}
}

void lichtstimmung() {
	static bool init =false;
	static WS2803::Color farben[256];
	static int counter =0;

	if(!init) {
		init =true;
		for(int i =0;i <256;i++) {
			farben[i].Red =mymap(sin(i / 180.0 * M_PI), -1, 1, 0, 255);
			farben[i].Green =mymap(sin((i * 1.3) / 180.0 * M_PI), -1, 1, 0, 255);
			farben[i].Blue =0;
		}
	}
	ws28->Fill(farben[counter]);
	counter++;
	if(counter >=256)
		counter =0;
}

void lichtstimmung2() {
	static int reihe =0;
	
	/*for(int x =0;x <10;x++) {
		ws28->setPixel(getIndex(x, reihe), farben[aktFarbe]);
	}*/
	ws28->Fill(farben[aktFarbe - 1 >= 0 ? aktFarbe - 1 : (sizeof(farben) / sizeof(WS2803::Color)) - 1]);
	for(int i =0;i <=reihe;i++)
		gbham(0, i, 9, i, farben[aktFarbe]);
	
	reihe++;
	if(reihe ==15) {
		reihe =0;
		aktFarbe++;
		if(aktFarbe ==sizeof(farben) / sizeof(WS2803::Color))
			aktFarbe =0;
	}
}

char checkfield(int x, int y) {
	int tmpX, tmpY;
	int living_neighbour =0;
	char ret;

	for(int j =-1;j <=1;j++) {
		for(int i =-1;i <=1;i++) {
			tmpX =x + i;
			tmpY =y + j;
			if(tmpX >=10 || tmpX <0 || tmpY >=15 || tmpY <0) {
			}
			else {
				if(feld[tmpX][tmpY] >0) living_neighbour++;
			}
		}
	}

	if(living_neighbour <=1 || living_neighbour >=4) ret =0;
	else if(living_neighbour ==3) ret =10;
	else ret =feld[x][y];

	if(ret <0) ret =0;

	return ret;
}

void game_of_life() {
	static bool init =false;
	char tmp[10 * 4][15 * 4];

	if(!init) {
		init =true;
		randomSeed(random());

		for(int x =0;x <10 * 4;x++) {
			for(int y =0;y <15 * 4;y++) {
				feld[x][y] =(random(256) > 196 ? 10 : 0);
			}
		}
		/*feld[0][2] =10;
		feld[1][2] =10;
		feld[2][2] =10;
		feld[1][0] =10;
		feld[2][1] =10;*/
	}

	for(int x =0;x <10 * 4;x++) {
		for(int y =0;y <15 * 4;y++) {
			if(feld[x][y] >0) ws28->setPixel(getIndex(x, y), WS2803::Red);
			tmp[x][y] =checkfield(x, y);
		}
	}

//	feld =tmp;
	bool gleich =true;
	for(int x =0;x <10 * 4;x++) {
		for(int y =0;y <15 * 4;y++) {
			if(feld[x][y] !=tmp[x][y]) gleich =false;
			feld[x][y] =tmp[x][y];
		}
	}
	if(gleich) init =false;
}

float mymap(float value, float au, float ao, float zu, float zo) {
	float ausgang =(abs(au) + abs(ao));
	float ziel =(abs(zu) + abs(zo));

	float faktor =ziel / ausgang;

	return value * faktor + zu - (au * faktor);
}

void screensaver() {
	static int x1 =random(10);
	static int x2 =random(10);
	static int y1 =random(15);
	static int y2 =random(15);
	static int rx1 =1;
	static int rx2 =-1;
	static int ry1 =1;
	static int ry2 =-1;
	static WS2803::Color farbe;
	static int counter =0;

	farbe.Red =mymap(sin(counter / 180.0 * M_PI), -1, 1, 0, 255);
	farbe.Green =mymap(cos(counter / 180.0 * M_PI), -1, 1, 0, 255);
	farbe.Blue =0;

	counter +=3;
	gbham(x1, y1, x2, y2, farbe);
	x1 +=rx1;
	x2 +=rx2;
	y1 +=ry1;
	y2 +=ry2;
	
	if(x1 >9) {
		rx1 =-1;
		x1 =9;
	}
	if(x1 <0) {
		rx1 =1;
		x1 =0;
	}
	if(x2 >9) {
		x2 =9;
		rx2 =-1;
	}
	if(x2 <0) {
		x2 =0;
		rx2 =1;
	}
	if(y1 >14) {
		y1 =14;
		ry1 =-1;
	}
	if(y1 <0) {
		y1 =0;
		ry1 =1;
	}
	if(y2 >14) {
		y2 =14;
		ry2 =-1;
	}
	if(y2 <0) {
		y2 =0;
		ry2 =1;
	}

//	delayMicroseconds(20);
}

void kreis() {
	static int radius =4;
	static int gk =-1;

	rasterCircle(5, 15 / 2, radius, WS2803::Grey);

	radius +=gk;
	if(radius ==0) {
		radius =0;
		gk =1;
	}
	if(radius ==4) {
		radius =4;
		gk =-1;
	}
}

void starfield() {
	const int anzSterne =40;
	static struct {
		float x, y;
		float speed;
	}sterne[anzSterne];
	static bool init =false;
	WS2803::Color farbe;

	if(!init) {
		init =true;
		for(int i =0;i <anzSterne;i++) {
			sterne[i].x =random(10);
			sterne[i].y =random(15);
			sterne[i].speed =random(4000) / 4000.0;
		}
	}

	for(int i =0;i <anzSterne;i++) {
		farbe.Red =0/*WS2803::White.Red * mymap(sterne[i].speed, 0, 1, 0, 100)*/;
		farbe.Green =WS2803::White.Green * mymap(sterne[i].speed, 0, 1, 0, 100);
		farbe.Blue =0/*WS2803::White.Blue * mymap(sterne[i].speed, 0, 1, 0, 100)*/;
		ws28->setPixel(getIndex(sterne[i].x, sterne[i].y), farbe);
		sterne[i].y -=sterne[i].speed;
		if(sterne[i].y <0) {
			sterne[i].x =random(10);
			sterne[i].y =15;
		}
	}
}

void drawQuadrat(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	gbham(x1, y1, x2, y2, WS2803::White);
	gbham(x2, y2, x3, y3, WS2803::White);
	gbham(x3, y3, x4, y4, WS2803::White);
	gbham(x4, y4, x1, y1, WS2803::White);
}

void quadrat() {
	drawQuadrat(0, 0, 0, 12, 8, 12, 8, 0);
}

void springenderPunkt() {
	static int posX =random(10);
	static int posY =random(15);
	static int mX =(random(100) > 50 ? 1 : -1);
	static int mY =(random(100) > 50 ? 1 : -1);

	posX +=mX;
	posY +=mY;

	if(posX >9) {
		posX =9;
		mX =-1 - random(2);
	}
	if(posX <0) {
		posX =0;
		mX =1 + random(2);
	}
	if(posY >14) {
		posY =14;
		mY =-1 - random(2);
	}
	if(posY <0) {
		posY =0;
		mY =1 + random(2);
	}

	ws28->setPixel(getIndex(posX, posY), WS2803::White);
}

void plasma() {
	static WS2803::Color palette[256];
	static bool init =false;
	static int counter =0;

	if(!init) {
		init =true;
		for(int i =0;i <256;i++) {
			palette[i].Red =mymap(sin(map(i, 0, 255, 0, 360) / 180.0 * M_PI), -1, 1, 0, 255);
			palette[i].Green =mymap(cos(map(i, 0, 255, 0, 360) / 180.0 * M_PI), -1, 1, 0, 255);
			palette[i].Blue =0;
			/*palette[i].Red =1;
			palette[i].Green =mymap(cos(map(i, 0, 255, 0, 360) / 180.0 * M_PI), -1, 1, 0, 255);
			palette[i].Blue =mymap(sin(map(i, 0, 255, 0, 360) / 180.0 * M_PI), -1, 1, 0, 255);*/
			/*palette[i].Red =mymap(sin(map(i, 0, 255, 0, 360) / 180.0 * M_PI), -1, 1, 0, 255);
			palette[i].Green =mymap(sin(map(i, 0, 255, 0, 360) / 180.0 * M_PI + 2 * M_PI / 3.0), -1, 1, 0, 255);
			palette[i].Blue =mymap(sin(map(i, 0, 255, 0, 360) / 180.0 * M_PI + 4 * M_PI / 3.0), -1, 1, 0, 255);*/
		}
	}

	for(int x =0;x <10;x++) {
		for(int y =0;y <15;y++) {
			WS2803::Color farbe;
			int tmp;

			tmp =mymap(sin(x * 100 + counter * 1.3), -1, 1, 0, 255);
			tmp +=mymap(sin(100 * (x + y) + counter * 0.4), -1, 1, 0, 255);
			tmp =mymap(tmp, 0, 2 * 255, 0, 255);
			farbe.Red =palette[tmp].Red;
			farbe.Green =palette[tmp].Green;
			farbe.Blue =palette[tmp].Blue;
			/*farbe.Red =tmp;
			farbe.Green =tmp;
			farbe.Blue =tmp;*/
			ws28->setPixel(getIndex(x, y), farbe);
		}
	}
	counter++;
	if(counter ==256)
		counter =0;
}

/* signum function */
int sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}
 
void gbham(int xstart,int ystart,int xend,int yend, WS2803::Color farbe)
/*--------------------------------------------------------------
 * Bresenham-Algorithmus: Linien auf Rastergeräten zeichnen
 *
 * Eingabeparameter:
 *    int xstart, ystart        = Koordinaten des Startpunkts
 *    int xend, yend            = Koordinaten des Endpunkts
 *
 * Ausgabe:
 *    void SetPixel(int x, int y) setze ein Pixel in der Grafik
 *         (wird in dieser oder aehnlicher Form vorausgesetzt)
 *---------------------------------------------------------------
 */
{
    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;
 
/* Entfernung in beiden Dimensionen berechnen */
   dx = xend - xstart;
   dy = yend - ystart;
 
/* Vorzeichen des Inkrements bestimmen */
   incx = sgn(dx);
   incy = sgn(dy);
   if(dx<0) dx = -dx;
   if(dy<0) dy = -dy;
 
/* feststellen, welche Entfernung größer ist */
   if (dx>dy)
   {
      /* x ist schnelle Richtung */
      pdx=incx; pdy=0;    /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dy;   el =dx;   /* Fehlerschritte schnell, langsam */
   } else
   {
      /* y ist schnelle Richtung */
      pdx=0;    pdy=incy; /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dx;   el =dy;   /* Fehlerschritte schnell, langsam */
   }
 
/* Initialisierungen vor Schleifenbeginn */
   x = xstart;
   y = ystart;
   err = el/2;
   ws28->setPixel(getIndex(x,y), farbe);
 
/* Pixel berechnen */
   for(t=0; t<el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
   {
      /* Aktualisierung Fehlerterm */
      err -= es;
      if(err<0)
      {
          /* Fehlerterm wieder positiv (>=0) machen */
          err += el;
          /* Schritt in langsame Richtung, Diagonalschritt */
          x += ddx;
          y += ddy;
      } else
      {
          /* Schritt in schnelle Richtung, Parallelschritt */
          x += pdx;
          y += pdy;
      }
      ws28->setPixel(getIndex(x,y), farbe);
   }
} /* gbham() */

void rasterCircle(int x0, int y0, int radius, WS2803::Color farbe) {
  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  ws28->setPixel(getIndex(x0, y0 + radius), farbe);
  ws28->setPixel(getIndex(x0, y0 - radius), farbe);
  ws28->setPixel(getIndex(x0 + radius, y0), farbe);
  ws28->setPixel(getIndex(x0 - radius, y0), farbe);

  while(x < y) {
    if(f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;

    ws28->setPixel(getIndex(x0 + x, y0 + y), farbe);
    ws28->setPixel(getIndex(x0 - x, y0 + y), farbe);
    ws28->setPixel(getIndex(x0 + x, y0 - y), farbe);
    ws28->setPixel(getIndex(x0 - x, y0 - y), farbe);
    ws28->setPixel(getIndex(x0 + y, y0 + x), farbe);
    ws28->setPixel(getIndex(x0 - y, y0 + x), farbe);
    ws28->setPixel(getIndex(x0 + y, y0 - x), farbe);
    ws28->setPixel(getIndex(x0 - y, y0 - x), farbe);
  }
}
