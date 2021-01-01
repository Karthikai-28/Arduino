void setup() {
    Serial.begin(9600);
}

void loop() {
    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float R0;  // Get the value of R0 via in H2
    float sensorValue;

    /*--- Get a average data by testing 100 times ---*/
    //Heather 5v 60 s
    analogWrite(A1, 1023);
    delay(6000);

    //Heather 1.4 V 90 s
    analogWrite(A1, (1023/5)*1.4 );
    for(int i = 0; i<100; i++){
        sensorValue = sensorValue + analogRead(A0);
        delay(900);
    }

    sensorValue = sensorValue/100.0;
    /*-----------------------------------------------*/

    sensor_volt = sensorValue/1024*5.0;
    RS_air = (5.0-sensor_volt)/sensor_volt;
    R0 = RS_air/(26+(1/3));

    Serial.print("R0 = ");
    Serial.println(R0);
    delay(1000);
}
