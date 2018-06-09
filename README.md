# DHT11ClibForPython

Project contains librery in C for simple use DHT11 temperature sensor

## Getting Started



### Prerequisites

Works with Standard Raspbian dystribution https://www.raspberrypi.org/downloads/raspbian/

### Installing

>sudo apt-get install python-dev

Download and unpack
in main folder run

>sudo python setup.py install


## Running 

running example shown in exampe.py file
Import lib

>import dht11py

Setup wiringPi lib

>dht11py.mywiringPiSetup()

use implemented method

>print dht11py.dht11_Readpy()

## License

This project is licensed under the GNU License.
