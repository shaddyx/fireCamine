#include "Arduino.h"

#include "r.h"
//The setup function is called once at startup of the sketch
#define PIN 0
#define PIN1 1
#define PIN2 2
#define mValue 1
#define mxValue 100

int pwmValue = mValue;
int pwmValue1 = mValue;
int pwmValue2 = mValue;
int trend = 0;
int trend1 = 0;
int trend2 = 0;
unsigned int counter = 0;
unsigned long timer = 0;
unsigned int divider = mxValue;
char blinkState = 0;

void setup()
{
	random_init(0xabcd); // initialize 16 bit seed
	pinMode(PIN, OUTPUT);
	pinMode(PIN1, OUTPUT);
	pinMode(PIN2, OUTPUT);

}

bool everyMs(long time, unsigned long* timer){
	unsigned long m = millis();
	if (*timer == 0){
		*timer = m;
	}
	if (m - time >= *timer){
		*timer = 0;
		return true;
	}
	return false;
}

void getPwm(int *pwmValue, int *trend){
	unsigned int r = u_random();

	if (r < 5000){
		*trend = - (u_random() & 16);
	} else if (r > 60000){
		*trend = u_random() & 16;
	}

	(*pwmValue) += *trend;

	if (*pwmValue < mValue) {
		*pwmValue = mValue;
	}

	if (*pwmValue > mxValue) {
		*pwmValue = mxValue;
	}

}

// The loop function is called in an endless loop
void loop()
{

	if (everyMs(10, &timer)){
		getPwm(&pwmValue, &trend);
		getPwm(&pwmValue1, &trend1);
		getPwm(&pwmValue2, &trend2);
	}

	counter ++;
	digitalWrite(PIN0, ((counter % divider) + 1) <= pwmValue);
	digitalWrite(PIN1, ((counter % divider) + 1) <= pwmValue1);
	digitalWrite(PIN2, ((counter % divider) + 1) <= pwmValue2);
}
