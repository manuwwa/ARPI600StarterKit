
#include <python2.7/Python.h>
#include<wiringPi.h>



static PyObject *
dht11_Readpy(PyObject *self)
{
	int Pin=1;
	char *temperature; 
	char *humidity;
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
	if(t >= 100)return Py_BuildValue("iii",1,0,0);  
	t = 0;
    while (!digitalRead(Pin) && t<100)//DHT11 Pull up 80us
	{
		t++;
		delayMicroseconds(1);
	};
	if(t >= 100)return Py_BuildValue("iii",1,1,0);    
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
			if(t >= 100)return Py_BuildValue("iii",1,2,0);
			t = 0;
			while(!digitalRead(Pin) && t <100)
			{
				t++;
				delayMicroseconds(1);
			}
			if(t >= 100)return Py_BuildValue("iii",1,3,0);
			delayMicroseconds(40);
			if(digitalRead(Pin))
				buf[i] += 1;
		}
	}
	if(buf[0]+buf[1]+buf[2]+buf[3]!=buf[4])return Py_BuildValue("iii",2,0,0);
	*humidity = buf[0];
	*temperature =buf[2];

	
	return Py_BuildValue("iii",0,*temperature,*humidity);
}
static PyObject *
mywiringPiSetup(PyObject *self)
{
	if (wiringPiSetup() < 0)Py_BuildValue("i",1);
	return Py_BuildValue("i",0);
}
static PyMethodDef dht11Methods[] = {
	    {"mywiringPiSetup", mywiringPiSetup, METH_VARARGS, "Greet an entity."},
    {"dht11_Readpy", dht11_Readpy, METH_VARARGS, "Greet an entity."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initdht11py()
{
   

   Py_InitModule("dht11py", dht11Methods);

}


