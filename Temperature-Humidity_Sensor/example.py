import dht11py;
import time;
print dht11py.mywiringPiSetup();
i=0;
while i < 10000:
	time.sleep( 3 )
	print dht11py.dht11_Readpy();
	i += 1
