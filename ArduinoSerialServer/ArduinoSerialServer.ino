// TestMicroSerialPort v0.1
//=========================
// P. Poliakoff 2017
//=========================
//this program is just a demonstrator for a command prompt on a Arduino micro
//
// Hardware
//=========
// Arduino Micro connected to PC via USB ( Power provided by USB)
// Leds  (+ resistance) on pins 2,3,..9

String cmd="";

void setup() {
  Serial.begin(9600);
  Serial.print(">");
}

void loop() {
  int charReceived;
  if(Serial.available()>0)
    {
    charReceived=Serial.read();
    if(charReceived!=10)
      {
      cmd+=char(charReceived);
      }
    else
      {
      cmd.toLowerCase();
      if(cmd!="")
        {
        if (cmd=="help" || cmd=="?")
          {
          Serial.println("Supported commands");
          Serial.println("  HELP | ? : display this message");
          Serial.println("  VER : display the program version");
          }
        else if (cmd=="ver")
          {
          Serial.println("Test Micro Serial Port v0.1");
          }
        else
          {
          Serial.println("Unknown command "+cmd );
          }

          //TODO!!!
          // add control of output ports, PWM, and read analog ports!!
        } 
      cmd="";
      Serial.println("");
      Serial.print(">");
      }
    }
  }
