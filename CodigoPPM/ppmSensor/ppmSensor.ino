class GasSensor {
  protected:
    int pin;
    float R0;
    float VC;
    float RL;

  public:
    GasSensor(int pin, float R0, float VC, float RL) {
      this->pin = pin;
      this->R0 = R0;
      this->VC = VC;
      this->RL = RL;
      pinMode(pin, INPUT);
    }

    float readSensor() {
      int sensorValue = analogRead(pin);
      return sensorValue * (VC / 1023.0);
    }

    float calculateRS(float VRL) {
      return ((VC / VRL) - 1) * RL;
    }

    float calculateRatio(float RS) {
      return RS / R0;
    }
};

class MQ2Sensor : public GasSensor {
  public:
    MQ2Sensor(int pin) : GasSensor(pin, 0.04, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((18.365 / ratio), (1 / 0.453));
    }
};

class MQ3Sensor : public GasSensor {
  public:
    MQ3Sensor(int pin) : GasSensor(pin, 0.01, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((0.5312 / ratio), (1 / 0.668));
    }
};

class MQ4Sensor : public GasSensor {
  public:
    MQ4Sensor(int pin) : GasSensor(pin, 0.02, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((23.114 / ratio), (1 / 0.376));
    }
};

class MQ6Sensor : public GasSensor {
  public:
    MQ6Sensor(int pin) : GasSensor(pin, 0.01, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((21.52 / ratio), (1 / 0.264));
    }
};

class MQ7Sensor : public GasSensor {
  public:
    MQ7Sensor(int pin) : GasSensor(pin, 0.01, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((17.32 / ratio), (1 / 0.065));
    }
};

class MQ135Sensor : public GasSensor {
  public:
    MQ135Sensor(int pin) : GasSensor(pin, 0.04, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((5.1927 / ratio), (1 / 0.352));
    }
};

const int MQ2_pin = A0;
const int MQ3_pin = A1;
const int MQ4_pin = A2;
const int MQ6_pin = A3;
const int MQ7_pin = A4;
const int MQ135_pin = A5;

MQ2Sensor mq2(MQ2_pin);
MQ3Sensor mq3(MQ3_pin);
MQ4Sensor mq4(MQ4_pin);
MQ6Sensor mq6(MQ6_pin);
MQ7Sensor mq7(MQ7_pin);
MQ135Sensor mq135(MQ135_pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float MQ2 = mq2.readSensor();
  float MQ3 = mq3.readSensor();
  float MQ4 = mq4.readSensor();
  float MQ6 = mq6.readSensor();
  float MQ7 = mq7.readSensor();
  float MQ135 = mq135.readSensor();

  float propano = MQ2;  // Exemplo, ajustar conforme necessário
  float Alcool = MQ3;
  float Ch4 = MQ4;
  float H2 = MQ6;
  float CO = MQ7;
  float CO2 = MQ135;

  float RS_A0 = mq2.calculateRS(propano);
  float RS_A1 = mq3.calculateRS(Alcool);
  float RS_A2 = mq4.calculateRS(Ch4);
  float RS_A3 = mq6.calculateRS(H2);
  float RS_A4 = mq7.calculateRS(CO);
  float RS_A5 = mq135.calculateRS(CO2);

  float ratio_A0 = mq2.calculateRatio(RS_A0);
  float ratio_A1 = mq3.calculateRatio(RS_A1);
  float ratio_A2 = mq4.calculateRatio(RS_A2);
  float ratio_A3 = mq6.calculateRatio(RS_A3);
  float ratio_A4 = mq7.calculateRatio(RS_A4);
  float ratio_A5 = mq135.calculateRatio(RS_A5);

  float MQ2ppm = mq2.calculatePPM(ratio_A0);
  float MQ3ppm = mq3.calculatePPM(ratio_A1);
  float MQ4ppm = mq4.calculatePPM(ratio_A2);
  float MQ6ppm = mq6.calculatePPM(ratio_A3);
  float MQ7ppm = mq7.calculatePPM(ratio_A4);
  float MQ135ppm = mq135.calculatePPM(ratio_A5);

  Serial.print("MQ2: = ");
  Serial.print(MQ2ppm);
  Serial.print(" ppm");

  Serial.print("MQ3: = ");
  Serial.print(MQ3ppm);
  Serial.print(" ppm");

  Serial.print("MQ4: = ");
  Serial.print(MQ4ppm);
  Serial.print(" ppm");

  Serial.print("MQ6: = ");
  Serial.print(MQ6ppm);
  Serial.print(" ppm");

  Serial.print("MQ7: = ");
  Serial.print(MQ7ppm);
  Serial.print(" ppm");

  Serial.print("MQ135: = ");
  Serial.print(MQ135ppm);
  Serial.print(" ppm");

  delay(300000);
}
