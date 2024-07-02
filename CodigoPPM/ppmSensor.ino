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

class MQ3Sensor : public GasSensor {
  public:
    MQ3Sensor(int pin) : GasSensor(pin, 0.065, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((0.516 / ratio), (1 / 0.672));
    }
};

class MQ5Sensor : public GasSensor {
  public:
    MQ5Sensor(int pin) : GasSensor(pin, 0.627, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((5.5442 / ratio), (1 / 0.243));
    }
};

class MQ7Sensor : public GasSensor {
  public:
    MQ7Sensor(int pin) : GasSensor(pin, 0.141, 5.0, 1) {}
    float calculatePPM(float ratio) {
      return pow((19.709 / ratio), (1 / 0.652));
    }
};

const int MQ3_pin = A0;
const int MQ5_pin = A1;
const int MQ7_pin = A2;

MQ3Sensor mq3(MQ3_pin);
MQ5Sensor mq5(MQ5_pin);
MQ7Sensor mq7(MQ7_pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float Alcool = 0.0;
  float H2 = 0.0;
  float CO = 0.0;
  
  Alcool = mq3.readSensor();
  H2 = mq5.readSensor();
  CO = mq7.readSensor();

  float RS_A0 = mq3.calculateRS(Alcool);
  float RS_A1 = mq5.calculateRS(H2);
  float RS_A2 = mq7.calculateRS(CO);

  float ratio_A0 = mq3.calculateRatio(RS_A0);
  float ratio_A1 = mq5.calculateRatio(RS_A1);
  float ratio_A2 = mq7.calculateRatio(RS_A2);

  float Alcoolppm = mq3.calculatePPM(ratio_A0);
  float H2ppm = mq5.calculatePPM(ratio_A1);
  float COppm = mq7.calculatePPM(ratio_A2);
  
  Serial.print("Alcool: = ");
  Serial.print(Alcoolppm);
  Serial.println(" ppm");

  Serial.print("H2: = ");
  Serial.print(H2ppm);
  Serial.println(" ppm");

  Serial.print("CO: = ");
  Serial.print(COppm);
  Serial.println(" ppm");

  delay(300000);
}
 
