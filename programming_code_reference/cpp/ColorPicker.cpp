#include<iostream>
#include <math.h> 

// https://www.rapidtables.com/convert/color/hsl-to-rgb.html

#define INV255 0.003921568627451f // 1/255
#define MAX3(a,b,c) ((a)>(b)?(a)>(c)?(a):(c):(b)>(c)?(b):(c))
#define MIN3(a,b,c) ((a)<(b)?(a)<(c)?(a):(c):(b)<(c)?(b):(c))

float CheckPos(float a){
	return a < 0.0f ? a * -1.0f : a;
}

const char HEXCHAR[] = {'0', '1', '2', '3', '4', '5', '6' ,'7', '8','9', 'A', 'B', 'C', 'D', 'E', 'F'};

template<typename T>
T GetHexValue(char c){
	switch(c){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': return 10;
		case 'B': return 11;
		case 'C': return 12;
		case 'D': return 13;
		case 'E': return 14;
		case 'F': return 15;
		default: return 0;
	}
}

void RGBtoHEX(float R, float G, float B){
	char h[7];
	int r = int(R);
	int g = int(G);
	int b = int(B);
	
	h[0] = HEXCHAR[(r & 0x00F0) >> 4];
	h[1] = HEXCHAR[(r & 0x000F)];
	h[2] = HEXCHAR[(g & 0x00F0) >> 4];
	h[3] = HEXCHAR[(g & 0x000F)];
	h[4] = HEXCHAR[(b & 0x00F0) >> 4];
	h[5] = HEXCHAR[(b & 0x000F)];
	h[6] = 0;
	printf("HEX:0x%s\n", h);
}

void TestRGBtoHEX(){
	RGBtoHEX(0, 0, 0);
    RGBtoHEX(255, 255, 255);
    RGBtoHEX(255, 0, 0);
    RGBtoHEX(0, 255, 0);
    RGBtoHEX(0, 0, 255);
    RGBtoHEX(255, 255, 0);
    RGBtoHEX(0, 255, 255);
    RGBtoHEX(255, 0, 255);
    RGBtoHEX(111, 222, 44);
}

// RGB to
void RGBtoCMYK(float R, float G, float B){
	R *= INV255;
	G *= INV255;
	B *= INV255;
	
	float K = 1 - MAX3(R,G,B);
	float K1 = 1 - K;
	K1 = K1 <= 0.0f ? 1.0f : K1; // Clamp to 1.0 if <= 0.0
	float C = (1-R-K)/K1;
	float M = (1-G-K)/K1;
	float Y = (1-B-K)/K1;
	
	printf("C:%.2f M:%.2f Y:%.2f K:%.2f\n", C, M, Y, K);
}

void TestRGBtoCMYK(){
	RGBtoCMYK(0, 0, 0);
    RGBtoCMYK(255, 255, 255);
    RGBtoCMYK(255, 0, 0);
    RGBtoCMYK(0, 255, 0);
    RGBtoCMYK(0, 0, 255);
    RGBtoCMYK(255, 255, 0);
    RGBtoCMYK(0, 255, 255);
    RGBtoCMYK(255, 0, 255);
}

void RGBtoHSL(float R, float G, float B){
	R *= INV255;
	G *= INV255;
	B *= INV255;
	
	float Cmax = MAX3(R,G,B);
	float Cmin = MIN3(R,G,B);
	float delta = Cmax - Cmin;
	// printf("M:%f m:%f d:%f\n", Cmax, Cmin, delta);
	float H = 0.0f;
	float S = 0.0f;
	float L = (Cmax+Cmin) * 0.5f;
	
	if(delta != 0.0) {
		if(Cmax == R){
			H = int((G-B)/delta) % 6;
		} 
		else if(Cmax == G) {
			H = (B-R)/delta + 2;
		}
		else if(Cmax == B) {
			H = (R-G)/delta + 4;
		}
		H *= 60;
		H = H < 0 ? H + 360 : H;
		S = delta / (1 - CheckPos(2 * L - 1));
	}
	printf("H:%3d S:%3d L:%3d\n", int(H), int(S * 100), int(round(L * 100)));
}

void TestRGBtoHSL(){
	RGBtoHSL(0, 0, 0);
    RGBtoHSL(255, 255, 255);
    RGBtoHSL(255, 0, 0);
    RGBtoHSL(0, 255, 0);
    RGBtoHSL(0, 0, 255);
    RGBtoHSL(255, 255, 0);
    RGBtoHSL(0, 255, 255);
    RGBtoHSL(255, 0, 255);
    RGBtoHSL(191, 191, 191);
    RGBtoHSL(128, 128, 128);
    RGBtoHSL(128, 0, 0);
    RGBtoHSL(128, 128, 0);
    RGBtoHSL(0, 128, 0);
    RGBtoHSL(128, 0, 128);
    RGBtoHSL(0, 128, 128);
    RGBtoHSL(0, 0, 128);
}

void RGBtoHSV(float R, float G, float B){
	R *= INV255;
	G *= INV255;
	B *= INV255;
	
	float Cmax = MAX3(R,G,B);
	float Cmin = MIN3(R,G,B);
	float delta = Cmax - Cmin;
	// printf("M:%f m:%f d:%f\n", Cmax, Cmin, delta);
	float H = 0.0f;
	float S = 0.0f;
	float V = Cmax;
	if(delta != 0.0) {
		if(Cmax == R){
			H = int((G-B)/delta) % 6;
		} 
		else if(Cmax == G) {
			H = (B-R)/delta + 2;
		}
		else if(Cmax == B) {
			H = (R-G)/delta + 4;
		}
		H *= 60;
		H = H < 0 ? H + 360 : H;
		S = delta / Cmax;
	}
	printf("H:%3d S:%3d V:%3d\n", int(H), int(S * 100), int(round(V * 100)));
}

void TestRGBtoHSV(){
	RGBtoHSV(0, 0, 0);
    RGBtoHSV(255, 255, 255);
    RGBtoHSV(255, 0, 0);
    RGBtoHSV(0, 255, 0);
    RGBtoHSV(0, 0, 255);
    RGBtoHSV(255, 255, 0);
    RGBtoHSV(0, 255, 255);
    RGBtoHSV(255, 0, 255);
    RGBtoHSV(191, 191, 191);
    RGBtoHSV(128, 128, 128);
    RGBtoHSV(128, 0, 0);
    RGBtoHSV(128, 128, 0);
    RGBtoHSV(0, 128, 0);
    RGBtoHSV(128, 0, 128);
    RGBtoHSV(0, 128, 128);
    RGBtoHSV(0, 0, 128);
}

// HSL to
void HSLtoRGB(float H, float S, float L) {
	S *= 0.01f;
	L *= 0.01f;
	
	float C = (1 - CheckPos(2*L - 1)) * S;
	float X = C * (1 - CheckPos( float( int(H/60) % 2 - 1.0f) ));
	float m = L - (C * 0.5f);
	// printf("C:%3f X:%3f m:%3f\n", C, X, m);
	
	float R = 0.0f, G = 0.0f, B = 0.0f;
	if(H < 60){
		R = C; G = X; B = 0;
	}
	else if(H < 120){
		R = X; G = C; B = 0;
	}
	else if(H < 180){
		R = 0; G = C; B = X;
	}
	else if(H < 240){
		R = 0; G = X; B = C;
	}
	else if(H < 300){
		R = X; G = 0; B = C;
	}
	else {
		R = C; G = 0; B = X;
	}
	R = round((R+m) * 255.0f);
	G = round((G+m) * 255.0f);
	B = round((B+m) * 255.0f);

	printf("R:%3d G:%3d B:%3d\n", int(R), int(G), int(B));
}

void TestHSLtoRGB(){
	HSLtoRGB(0, 0, 0);
    HSLtoRGB(0, 0, 100);
    HSLtoRGB(0, 100, 50);
    HSLtoRGB(120, 100, 50);
    HSLtoRGB(240, 100, 50);
    HSLtoRGB(60, 100, 50);
    HSLtoRGB(180, 100, 50);
    HSLtoRGB(300, 100, 50);
    HSLtoRGB(0, 0, 75);
    HSLtoRGB(0, 0, 50);
    HSLtoRGB(0, 100, 25);
    HSLtoRGB(60, 100, 25);
    HSLtoRGB(120, 100, 25);
    HSLtoRGB(300, 100, 25);
    HSLtoRGB(180, 100, 25);
    HSLtoRGB(240, 100, 25);
}

// HSV to
void HSVtoRGB(float H, float S, float V) {
	S *= 0.01f;
	V *= 0.01f;
	
	float C = V * S;
	float X = C * (1 - CheckPos( float( int(H/60) % 2 - 1.0f) ));
	float m = V - C;
	// printf("C:%3f X:%3f m:%3f\n", C, X, m);
	
	float R = 0.0f, G = 0.0f, B = 0.0f;
	if(H < 60){
		R = C; G = X; B = 0;
	}
	else if(H < 120){
		R = X; G = C; B = 0;
	}
	else if(H < 180){
		R = 0; G = C; B = X;
	}
	else if(H < 240){
		R = 0; G = X; B = C;
	}
	else if(H < 300){
		R = X; G = 0; B = C;
	}
	else {
		R = C; G = 0; B = X;
	}
	R = round((R+m) * 255.0f);
	G = round((G+m) * 255.0f);
	B = round((B+m) * 255.0f);

	printf("R:%3d G:%3d B:%3d\n", int(R), int(G), int(B));
}

void TestHSVtoRGB(){
	HSVtoRGB(0, 0, 0);
    HSVtoRGB(0, 0, 100);
    HSVtoRGB(0, 100, 100);
    HSVtoRGB(120, 100, 100);
    HSVtoRGB(240, 100, 100);
    HSVtoRGB(60, 100, 100);
    HSVtoRGB(180, 100, 100);
    HSVtoRGB(300, 100, 100);
    HSVtoRGB(0, 0, 75);
    HSVtoRGB(0, 0, 50);
    HSVtoRGB(0, 100, 50);
    HSVtoRGB(60, 100, 50);
    HSVtoRGB(120, 100, 50);
    HSVtoRGB(300, 100, 50);
    HSVtoRGB(180, 100, 50);
    HSVtoRGB(240, 100, 50);
}

// CMYK to
void CMYKtoRGB(float C, float M, float Y, float K) {
	K = 1.0 - K;

	float R = round(255.0f * (1-C) * K);
	float G = round(255.0f * (1-M) * K);
	float B = round(255.0f * (1-Y) * K);

	printf("R:%3d G:%3d B:%3d\n", int(R), int(G), int(B));
}

void TestCMYKtoRGB(){
	CMYKtoRGB(0,0,0,1);
	CMYKtoRGB(0,0,0,0);
	CMYKtoRGB(0,1,1,0);
	CMYKtoRGB(1,0,1,0);
	CMYKtoRGB(1,1,0,0);
	CMYKtoRGB(0,0,1,0);
	CMYKtoRGB(1,0,0,0);
	CMYKtoRGB(0,1,0,0);
}


int main(){
	// TestRGBtoHEX();
	TestRGBtoCMYK();
	// TestRGBtoHSL();
	// TestRGBtoHSV();
	
	// TestHSLtoRGB();
	// TestHSVtoRGB();
	// TestCMYKtoRGB();

}