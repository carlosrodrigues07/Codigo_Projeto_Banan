class MQSensor {
  private:
    int sensorPin;
    float RL;
    float VC;
    float specificValue;

  public:
    MQSensor(int pin, float rl, float vc, float specific_value) {
      sensorPin = pin;
      RL = rl;
      VC = vc;
      specificValue = specific_value;
    }

    float calculateR0() {
      float sensor_VRL = readSensorVoltage();
      float sensor_RS = calculateRS(sensor_VRL);
      return sensor_RS / specificValue;
    }

    float readSensorVoltage() {
      float sensorRead = analogRead(sensorPin);
      // Calcular a tensão com base na leitura do sensor e tensão de referência
      return (sensorRead / 1023.0) * VC;
    }

    float calculateRS(float sensor_VRL) {
      // Calcular a resistência do sensor com base na tensão e resistência de carga
      return RL / ((VC / sensor_VRL) - 1.0);
    }
};

MQSensor MQSensor2(A0, 1.0, 5.0, 9.48);
MQSensor MQSensor3(A1, 1.0, 5.0, 58.65);
MQSensor MQSensor4(A2, 1.0, 5.0, 4.36);
MQSensor MQSensor6(A3, 1.0, 5.0, 9.91);
MQSensor MQSensor7(A4, 1.0, 5.0, 25.49);
MQSensor MQSensor135(A5, 1.0, 5.0, 3.61);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Lê Ro MQ-2
  float R0_MQ2 = MQSensor2.calculateR0();

  // Lê Ro MQ-3
  float R0_MQ3 = MQSensor3.calculateR0();

  // Lê Ro MQ-4
  float R0_MQ4 = MQSensor4.calculateR0();
  
  // Lê Ro MQ-6
  float R0_MQ6 = MQSensor6.calculateR0();
  
  // Lê Ro MQ-7
  float R0_MQ7 = MQSensor7.calculateR0();
  
  // Lê Ro MQ-135
  float R0_MQ135 = MQSensor135.calculateR0();

  // Exibe os resultados
  Serial.print("Valor R0 MQ2: ");
  Serial.println(R0_MQ2);
  Serial.print("Valor R0 MQ3: ");
  Serial.println(R0_MQ3);
  Serial.print("Valor R0 MQ4: ");
  Serial.println(R0_MQ4);
  Serial.print("Valor R0 MQ6: ");
  Serial.println(R0_MQ6);
  Serial.print("Valor R0 MQ7: ");
  Serial.println(R0_MQ7);
  Serial.print("Valor R0 MQ135: ");
  Serial.println(R0_MQ135);

  delay(90000); // Espera 90 segundos antes da próxima leitura
}
