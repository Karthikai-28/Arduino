void setup() {
    Serial.begin(9600);
}

void loop() {
    float RS_gas = 0;
    float ratio = 0;
    float sensorValue = 0;
    float sensor_volt = 0;


    //Heather 5v 60 s
    analogWrite(A1, 1023);
    delay(6000);

    //Heather 1.4 V 90 s
    analogWrite(A1, (1023/5)*1.4 );
    for(int i = 0; i<900; i++){
        sensorValue = analogRead(A0);
        int sensor_volt = sensorValue/1024*5.0;
        RS_gas = (5.0-sensor_volt)/sensor_volt;
        ratio = RS_gas/0.72; //Replace R0 with the value found using the calibration code
        float ppm = 100 * pow(log10(40)/log10(0.09), ratio);//Formula for co 2 concentration
        Serial.println(ppm);
        delay(100);
    }
}
