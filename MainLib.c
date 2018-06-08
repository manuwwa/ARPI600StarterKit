#include <python2.7/Python.h>
#include<wiringPi.h>
#include "DHT11.h"
static PyObject *
mywiringPiSetup(PyObject *self)
{
	if (wiringPiSetup() < 0)Py_BuildValue("i",1);
	return Py_BuildValue("i",0);
}
static PyMethodDef Methods[] = {
	    {"mywiringPiSetup", mywiringPiSetup, METH_VARARGS, "Greet an entity."},
    {"dht11_Readpy", dht11_Readpy, METH_VARARGS, "Greet an entity."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initdht11py()
{
   

   Py_InitModule("SensorsLib", Methods);

}