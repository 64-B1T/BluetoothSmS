#include <SoftwareSerial.h>
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
//                      Rx  Tx
SoftwareSerial mySerial(0, 1); //take your RX and TX pin of your Bluetooth Module
#define maxnumber  20           //maximum number length
#define maxtext   100           //maximum length of text
#define PIN_RESET 9  // Connect RST to pin 9 (req. for SPI and I2C)
#define PIN_DC    8  // Connect DC to pin 8 (required for SPI)
#define PIN_CS    10 // Connect CS to pin 10 (required for SPI)
#define DC_JUMPER 0

char innumber[maxnumber] = "";
char intext[maxtext] = "";

MicroOLED oled(PIN_RESET, PIN_DC, PIN_CS);

String bluedata;
String command;
byte value;
byte valueall[15];
char valuechar[15];

void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 oled.begin();    // Initialize the OLED
  delay(1000);
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
       // Delay 1000 ms
  oled.clear(PAGE);
  oled.display();
  
  oled.setFontType(1); 
  oled.setCursor(0, 0);
 oled.print("64-B1T HWH");
 oled.display();
 delay(2000); 
 oled.clear(ALL);
 oled.clear(PAGE);
 
}
void loop()
{
 //is a message available? Save the number and text into two variable innumber and intext
 if(getnumberandtext(innumber, intext))
 {
  String str(intext);
  String str2(innumber);
  Serial.print(str2);
  Serial.print(": ");
  Serial.print(str);
  Serial.print("\n");
   oled.display();
   oled.setCursor(0, 10);
   oled.print(str2);
   oled.setCursor(10, 30);
   oled.print(str);
   oled.display();
  // oled.clear(ALL);
  oled.clear(PAGE);
  
 }else{
  oled.display();
   oled.setCursor(0, 10);
   oled.print("Stasis");
   oled.setCursor(10, 30);
   oled.print("Mode");
   oled.display();
  // oled.clear(ALL);
  oled.clear(PAGE);
 }
 
}


unsigned char getnumberandtext(char* numberptr, char* textptr)
{
  int i = 0;
  char* ptr = 0;
  char instring[maxnumber + maxtext] = "";
  int  enable=0;
 
  //wait for incoming message and save it in instring[].
  while(mySerial.available() > 0)
  {
    instring[i] = mySerial.read();
    i++;
    enable = 1;
  }
 
  //is a message available?
  if(enable)
  {
    enable = 0;
    ptr = instring;
    for(i = 0; *ptr != '\n'; i++)
    {
      *numberptr = *ptr;
      numberptr++;
      ptr++;
    }
   
    for(i = i; i<maxnumber; i++)
    {
       *numberptr = 0;
       numberptr++;
    }
   
    ptr += 1;
   
    for(i = 0; *ptr != '\0'; i++)
    {
      *textptr = *ptr;
      textptr++;
      ptr++;
    }
   
     for(i = i; i<maxtext; i++)
    {
      *textptr = 0;
      textptr++;
    }
   
    return(1);
  }
}

