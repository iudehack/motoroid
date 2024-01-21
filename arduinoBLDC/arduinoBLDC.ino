/*Arduino Uno*/

/*pin Sensor Hall Motor*/
int pinA_shall=A0;
int pinB_shall=A1;
int pinC_shall=A2;
/*estado Sensor Hall Motor*/
boolean A_shall = false;
boolean B_shall = false; 
boolean C_shall = false;
/*pin PWM*/
int pinA_High =3, pinA_Low =5;
int pinB_High =6, pinB_Low =9;
int pinC_High =10, pinC_Low =11;
/*valor PWM*/
int phaseA_High, phaseA_Low;
int phaseB_High, phaseB_Low;
int phaseC_High, phaseC_Low;

int BLDC_V=0;

void setup()
{
	Serial.begin(9600);
	
	pinMode(pinA_shall, INPUT);
	pinMode(pinB_shall, INPUT);
	pinMode(pinC_shall, INPUT);
	pinMode(pinA_High,	OUTPUT);
	pinMode(pinA_Low,	OUTPUT);
	pinMode(pinB_High,	OUTPUT);
	pinMode(pinB_Low,	OUTPUT);
	pinMode(pinC_High,	OUTPUT);
	pinMode(pinC_Low,	OUTPUT);
}

void loop()
{
	readSensorHall();
	bldcControl();
	
  

}

void readSensorHall(){
	int umbralSensorHall = 2;
	int aA_shall=analogRead(pinA_shall);
	int bB_shall=analogRead(pinB_shall);
	int cC_shall=analogRead(pinC_shall);
	if(aA_shall>umbralSensorHall){A_shall = true;}
		else{A_shall = false;}
	if(bB_shall>umbralSensorHall){B_shall = true;}
		else{B_shall = false;}
	if(cC_shall>umbralSensorHall){C_shall = true;}
		else{C_shall = false;}
}

void bldcControl(){
	/*step*/
	int step;																//	A	B	C
	if(A_shall==true && B_shall ==false && C_shall ==true){step=1;}			//	1	0	1
	else if(A_shall==false && B_shall ==false && C_shall ==true){step=2;}	//	0	0	1
	else if(A_shall==false && B_shall ==true && C_shall ==true){step=3;}	//	0	1	1
	else if(A_shall==false && B_shall ==true && C_shall ==false){step=4;}	//	0	1	0	
	else if(A_shall==true && B_shall ==true && C_shall ==false){step=5;}	//	1	1	0	
	else if(A_shall==true && B_shall ==false && C_shall ==false){step=6;}	//	1	0	0


	switch(step){
	case 1: 
		phaseA_High =BLDC_V; phaseA_Low =0;
		phaseB_High =0; phaseB_Low =255;
		phaseC_High =0; phaseC_Low =0; break;	
	case 2:
		phaseA_High =0; phaseA_Low =0;
		phaseB_High =0; phaseB_Low =255;
		phaseC_High =BLDC_V; phaseC_Low =0; break;
	case 3:
		phaseA_High =BLDC_V; phaseA_Low =255;
		phaseB_High =0; phaseB_Low =0;
		phaseC_High =0; phaseC_Low =0; break;
	case 4:
		phaseA_High =0; phaseA_Low =255;
		phaseB_High =BLDC_V; phaseB_Low =0;
		phaseC_High =0; phaseC_Low =0; break;
	case 5:
		phaseA_High =0; phaseA_Low =0;
		phaseB_High =BLDC_V; phaseB_Low =0;
		phaseC_High =255; phaseC_Low =0; break;
	case 6:
		phaseA_High =BLDC_V; phaseA_Low =0;
		phaseB_High =0; phaseB_Low =0;
		phaseC_High =0; phaseC_Low =255; break;
	default: /*codigo control error "en caso de..."*/ break;
	}
	
	analogWrite(pinA_High, phaseA_High);
	analogWrite(pinA_Low, phaseA_Low);
	analogWrite(pinB_High, phaseB_High);
	analogWrite(pinB_Low, phaseB_Low);
	analogWrite(pinC_High, phaseC_High);
	analogWrite(pinC_High, phaseC_Low);

}