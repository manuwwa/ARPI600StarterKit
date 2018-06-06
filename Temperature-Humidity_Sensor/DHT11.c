
#include <stdio.h>
#include<wiringPi.h>
#include <python3.5/Python.h>


static PyObject *
DHT11_Readpy(PyObject *self, PyObject *PinNumber)
{
	int retnum=0;
	int Pin=0;
	    if (!PyArg_ParseTuple(PinNumber, "1", &Pin))
        return NULL;
	char *temperature;
	char *humidity;
	*temperature=0;
	*humidity=0;
		unsigned char t,i,j;
	unsigned char buf[5]={0,0,0,0,0};
	pinMode(Pin,OUTPUT); 	    //SET OUTPUT
	pullUpDnControl(Pin,PUD_UP);
    digitalWrite(Pin,0); 	    //Pin=0
    delay(20);         	        //Pull down Least 18ms
    digitalWrite(Pin,1); 	    //Pin =1
	delayMicroseconds(30);     	//Pull up 20~40us
	pinMode(Pin,INPUT);        //SET INPUT
	
    while (digitalRead(Pin) && t <100)//DHT11 Pull down 80us
	{
		t++;
		delayMicroseconds(1);
	};	 
	if(t >= 100)retnum= 1;
	t = 0;
    while (!digitalRead(Pin) && t<100)//DHT11 Pull up 80us
	{
		t++;
		delayMicroseconds(1);
	};
	if(t >= 100)retnum= 1;	    
	for(i=0;i < 5;i++)
	{
		buf[i] = 0;
		for(j=0;j<8;j++)
		{
			buf[i] <<= 1;
			t = 0;
			while(digitalRead(Pin) && t < 100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) retnum= 1;
			t = 0;
			while(!digitalRead(Pin) && t <100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) retnum= 1;
			delayMicroseconds(40);
			if(digitalRead(Pin))
				buf[i] += 1;
		}
	}
	if(buf[0]+buf[1]+buf[2]+buf[3]!=buf[4])retnum= 2;
	*humidity = buf[0];
	*temperature =buf[2];
	retnum= 0;
	
	return Py_BuildValue("iii",retnum,*temperature,*humidity);
}
char DHT11_Read(char *temperature,char *humidity, int Pin)	   
{                 
	unsigned char t,i,j;
	unsigned char buf[5]={0,0,0,0,0};
	pinMode(Pin,OUTPUT); 	    //SET OUTPUT
	pullUpDnControl(Pin,PUD_UP);
    digitalWrite(Pin,0); 	    //Pin=0
    delay(20);         	        //Pull down Least 18ms
    digitalWrite(Pin,1); 	    //Pin =1
	delayMicroseconds(30);     	//Pull up 20~40us
	pinMode(Pin,INPUT);        //SET INPUT
	
    while (digitalRead(Pin) && t <100)//DHT11 Pull down 80us
	{
		t++;
		delayMicroseconds(1);
	};	 
	if(t >= 100)return 1;
	t = 0;
    while (!digitalRead(Pin) && t<100)//DHT11 Pull up 80us
	{
		t++;
		delayMicroseconds(1);
	};
	if(t >= 100)return 1;	    
	for(i=0;i < 5;i++)
	{
		buf[i] = 0;
		for(j=0;j<8;j++)
		{
			buf[i] <<= 1;
			t = 0;
			while(digitalRead(Pin) && t < 100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) return 1;
			t = 0;
			while(!digitalRead(Pin) && t <100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100) return 1;
			delayMicroseconds(40);
			if(digitalRead(Pin))
				buf[i] += 1;
		}
	}
	if(buf[0]+buf[1]+buf[2]+buf[3]!=buf[4])return 2;
	*humidity = buf[0];
	*temperature =buf[2];
	return 0;
} 


int main(void)
{
	PyObject pinPy=Py_BuildValue("i",1);
	char temperature;  	    
	char humidity; 
	char value;

	if (wiringPiSetup() < 0)return 1;
	printf("Waveshare!\r\n");
	
  	while(1)
	{
		value = DHT11_Read(&temperature,&humidity,1);	
		if(value == 0)
		{ 
			printf("\ntemperature = %d\r\n",temperature);
			printf("humidity    = %d\r\n",humidity);
		}
		else if (value == 2)
		 	printf("\ncheck sum err\n");
		else
			printf("\ntime out\n");
 		delay(1000);
	}
}

