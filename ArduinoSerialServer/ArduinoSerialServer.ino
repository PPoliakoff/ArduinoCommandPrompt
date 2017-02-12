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

String input="";

void executeCommand(String message);
int stringToByte(String n);
int stringToPortNumber(String n);
int stringToPinMode(String n);
int stringToDigitalValue(String n);

void setup() {
  Serial.begin(9600);
  Serial.print(">");
}

void loop() {
  int charReceived;
  if(Serial.available()>0)
    {
    charReceived=Serial.read();
    switch(charReceived)
      {
      case 10: //enter
        executeCommand(input);
        input="";
        Serial.println("");
        Serial.print(">");
      break;
      case 8: //backspace
        if (input.length()>0)
          {
          input=input.substring(0,input.length()-1);
          }
        break;
      default:
        input+=char(charReceived);
      break;
      }
    }
}

void executeCommand(String message)
{
      message.toLowerCase();

      String cmd="";
      String param1="";
      String param2="";
           
      int openParenthesis=message.indexOf('(');
      int closeParenthesis=message.indexOf(')');
      int comma=message.indexOf(',');
      
      if(openParenthesis>=0 && closeParenthesis>openParenthesis)
        { 
          //handle the parameters
          cmd=message.substring(0,openParenthesis);
          if(comma>-1)
            {
              param1=message.substring(openParenthesis+1,comma);
              param2=message.substring(comma+1,closeParenthesis);
            }
           else
            {
              param1=message.substring(openParenthesis+1,closeParenthesis);
            }
        }
        else
        {
          // no parameter
          cmd=message;
        }
      //debug: Serial.println(cmd+"/"+param1+"/"+param2 );

      if(cmd!="")
        {
        if (cmd=="pinmode")
          {
            if(param1.length()<=0 || param2.length()<=0)
            {
               Serial.println(cmd+" requires 2 parameters");
            }
            else
            { 
              int portNumber=stringToPortNumber(param1);
              int pinModevalue= stringToPinMode(param2);
              if(portNumber>=0 && pinModevalue>=0)
              {
                pinMode(portNumber,pinModevalue);
                //Serial.println(cmd+String( portNumber)+String(pinModevalue));
              }
            }
          }
          
        else if (cmd=="digitalwrite")
          {
            if(param1.length()<=0 || param2.length()<=0)
            {
               Serial.println(cmd+" requires 2 parameters");
            }
            else
            { 
              int portNumber=stringToPortNumber(param1);
              int digitalvalue= stringToDigitalValue(param2);
              if(portNumber>=0 && digitalvalue>=0)
              {
                digitalWrite(portNumber,digitalvalue);
                //Serial.println(cmd+String( portNumber)+String(digitalvalue));
              }
              else
              {
                Serial.println("Syntax error :"+message);
              }
            }
          }
        else if (cmd=="digitalread")
          {
            if(param1.length()<=0 || param2.length()>0)
            {
               Serial.println(cmd+" requires 1 parameter");
            }
            else
            { 
              int portNumber=stringToPortNumber(param1);
           
              if(portNumber>=0)
              {
                Serial.println(digitalRead(portNumber));
              }
              else
              {
                Serial.println("Syntax error :"+message);
              }
            }
          }
        else if (cmd=="analogwrite")
          {
            if(param1.length()<=0 || param2.length()<=0)
            {
               Serial.println(cmd+" requires 2 parameters");
            }
            else
            { 
              int portNumber=stringToPortNumber(param1);
              int analogValue= stringToByte(param2);
              if(portNumber>=0 && analogValue>=0)
              {
                analogWrite(portNumber,analogValue);
                //Serial.println(cmd+String( portNumber)+String(analogValue));
              }
              else
              {
                Serial.println("Syntax error :"+message);
              }
            }
          }
        else if (cmd=="analogread")
          {
            if(param1.length()<=0 || param2.length()>0)
            {
               Serial.println(cmd+" requires 1 parameter");
            }
            else
            { 
              int portNumber=stringToPortNumber(param1);
           
              if(portNumber>=0)
              {
                Serial.println(analogRead(portNumber));
              }
              else
              {
                Serial.println("Syntax error :"+message);
              }
            }
          }
          
        else if (cmd=="help" || cmd=="?")
          {
          Serial.println("Supported commands");
          Serial.println("  HELP | ?                                : display this message");
          Serial.println("  VERSION                                 : display the program version");
          Serial.println("  PinMode(port,input|output|input_pullup) : configure a digital port");
          Serial.println("  DigitalWrite(port,HIGH|LOW)             : set the digital output state");
          Serial.println("  DigitalRead(port)                       : get the digital inputstate");
          Serial.println("  AnalogWrite(port,[0..255])              : set the PWM on a digital port");
          Serial.println("  AnalogRead(analogPort)                        : get the analog measurement from an analog port");
          }
        else if (cmd=="version")
          {
          Serial.println("Arduino Serial Server v0.2");
          }
        else
          {
          Serial.println("Unknown command "+message);
          }

          //TODO!!!
          // add control PWM, and read analog ports!!
        } 
}

int stringToByte(String n)
{
    bool valid=n.length()<=3;
    int retval=-1;
    for(int i=0; i<n.length() &&valid==true; i++)
      {
      valid=isDigit(n.charAt(i));
      }
  if(valid)
    {
      retval=n.toInt();
    }
  if(valid==false || retval<0 ||retval>255)
      {
        retval=-1;
        Serial.println("Invalid value: "+n);       
      }
  return retval;
}

int stringToPortNumber(String n)
{
    bool valid=n.length()<=2;
    int retval=-1;
    for(int i=0; i<n.length() &&valid==true; i++)
      {
      valid=isDigit(n.charAt(i));
      }
      
  if(valid)
    {
      retval=n.toInt();
    }
   else
    {
      Serial.println("Invalid Port Number: "+n);
    }
  return retval;
}

int stringToPinMode(String n)
{
  if(n=="input")
    return 0;
  else if(n=="output")
    return 1;
  else if(n=="input_pullup")
    return 2;
  else
  {
    Serial.println("Invalid Pin Mode: "+n);
    return -1;
  }
}

int stringToDigitalValue(String n)
{
  if(n=="high")
    return 1;
  else if(n=="low")
    return 0;
  else
  {
    Serial.println("Invalid value: "+n);
    return -1;
  }
}

