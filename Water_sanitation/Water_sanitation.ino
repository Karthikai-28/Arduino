#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    

#define tempOffSet 0.00

#define DEBUG false
#define responseTime 20

#define ONE_WIRE_BUS 4                // Data wire is plugged into port 2 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);        // Setup a oneWire instance to communicate with any OneWire 
                                      //devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire);  // Pass our oneWire reference to Dallas Temperature. 

SoftwareSerial bluetoothSerial(2, 3);      // RX, TX


void setup()
{
  
  //setup RGB LED as indicator instead of softserial
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  bluetoothSerial.begin(115200);
  while (!bluetoothSerial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  sendTobluetooth("AT+CWMODE=2",responseTime,DEBUG); // configure as access point
  sendTobluetooth("AT+CIFSR",responseTime,DEBUG); // get ip address
  sendTobluetooth("AT+CIPMUX=1",responseTime,DEBUG); // configure for multiple connections
  sendTobluetooth("AT+CIPSERVER=1,80",responseTime,DEBUG); // turn on server on port 80
 
  sendToUno("Safepools.pH Hardware is ready!",responseTime,DEBUG);
  

}


void loop()
{
  ///// Read pH Regularly //////
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(Serial.available()>0){
     String message = readSerialMessage();
    if(find(message,"debugdebugBluetooth:")){
      String result = sendTobluetooth(message.substring(13,message.length()),responseTime,DEBUG);
      if(find(result,"OK"))
        sendData("\nOK");
      else
        sendData("\nEr");
    }
  }
  if(bluetoothSerial.available()>0){
    
    String message = readbluetoothSerialMessage();
    
    if(find(message,"debugBluetooth:")){
       String result = sendTobluetooth(message.substring(8,message.length()),responseTime,DEBUG);
      if(find(result,"OK"))
        sendData("\n"+result);
      else
        sendData("\nATCE1001");               //At command ERROR CODE for Failed Executing statement
    }else
    if(find(message,"getT")){
      float temp = 0;
      sensors.requestTemperatures();          // Send the command to get temperatures
      temp = sensors.getTempCByIndex(0);
      sensors.requestTemperatures();          // Send the command to get temperatures
      temp = sensors.getTempCByIndex(0);
      if(temp==85)  
        sendData("\nTE1001");                 //Temperature ERROR CODE for INITIALIZE
      else if(temp==0 || temp==-127)
        sendData("\nTE1002");                  //Temperature ERROR CODE for NOT CONNECTED
      else{
        String temperature = "";
        temperature+=temp+tempOffSet;
        sendData("\n"+temperature);
      }
    }else
    if(find(message,"getP")){
      //sending ph level:
      if(pHValue==0){
        sendData("\nPE1001");                 //pH ERROR CODE for NOT OPEN
      }else{
        String ph = "";
        ph+=pHValue;
        sendData("\n"+ph);
      }
    }else if(find(message,"pHOff")){
      //sending ph level:
      digitalWrite(12,0);
    }else if(find(message,"pHOn")){
      //sending ph level:
      digitalWrite(12,1);
    }
    else{
      sendData("\nErrRead");                 //Command ERROR CODE for UNABLE TO READ
    }
  }
  delay(responseTime);
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}




/*
* Name: sendData
* Description: Function used to send string to tcp client using cipsend
* Params: 
* Returns: void
*/
void sendData(String str){
  String len="";
  len+=str.length();
  sendTobluetooth("AT+CIPSEND=0,"+len,responseTime,DEBUG);
  delay(100);
  sendTobluetooth(str,responseTime,DEBUG);
  delay(100);
  sendTobluetooth("AT+CIPCLOSE=5",responseTime,DEBUG);
}


/*
* Name: find
* Description: Function used to match two string
* Params: 
* Returns: true if match else false
*/
boolean find(String string, String value){
  if(string.indexOf(value)>=0)
    return true;
  return false;
}


/*
* Name: readSerialMessage
* Description: Function used to read data from Arduino Serial.
* Params: 
* Returns: The response from the Arduino (if there is a reponse)
*/
String  readSerialMessage(){
  char value[100]; 
  int index_count =0;
  while(Serial.available()>0){
    value[index_count]=Serial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
* Name: readbluetoothSerialMessage
* Description: Function used to read data from debugBluetooth Serial.
* Params: 
* Returns: The response from the debugBluetooth (if there is a reponse)
*/
String  readbluetoothSerialMessage(){
  char value[100]; 
  int index_count =0;
  while(bluetoothSerial.available()>0){
    value[index_count]=bluetoothSerial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}



/*
* Name: sendTobluetooth
* Description: Function used to send data to debugBluetooth.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the debugBluetooth (if there is a reponse)
*/
String sendTobluetooth(String command, const int timeout, boolean debug){
  String response = "";
  bluetoothSerial.println(command); // send the read character to the debugBluetooth
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(bluetoothSerial.available())
    {
    // The esp has data so display its output to the serial window 
    char c = bluetoothSerial.read(); // read the next character.
    response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}

/*
* Name: sendTobluetooth
* Description: Function used to send data to debugBluetooth.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the debugBluetooth (if there is a reponse)
*/
String sendToUno(String command, const int timeout, boolean debug){
  String response = "";
  Serial.println(command); // send the read character to the debugBluetooth
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}
