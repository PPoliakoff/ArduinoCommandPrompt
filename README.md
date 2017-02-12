# ArduinoCommandPrompt

## Server running in the Arduino

The server offers via the serial port over USB a prompt the allows to access to the arduino functionalities

### The supported commands are 
* Help
* Version
* PinMode(port,OUTPUT|INPUT|INPUT_PULLUP)
* DigitalWrite(port,HIGH|LOW)
* digitalRead(port)
* ReadAnalog(analogPort)
* AnalogWrite(port,value)

The commands are case insensitive


Stil to do allow to specify range of ports e.g. 2-6

## Client running on the PC

The client could be any serial terminal (even the one included in the Arduino IDE)
The client provided here is developped in C#. 
It is massively ispired from the [.net serial port example](https://msdn.microsoft.com/en-us/library/system.io.ports.serialport(v=vs.110).aspx)