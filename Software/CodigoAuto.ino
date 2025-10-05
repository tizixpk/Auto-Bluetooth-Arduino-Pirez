
#include <AFMotor.h>
#include <SoftwareSerial.h>

// Configuración del módulo Bluetooth
SoftwareSerial BT(10, 11); // RX | TX

// Definimos pines del L298N
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

char comando;

void setup() {
  // Configurar pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Iniciar comunicación
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Listo para recibir comandos desde Bluetooth");
}

void loop() {
  if (BT.available()) {
    comando = BT.read();
    Serial.println(comando);

    switch (comando) {
      case 'F': adelante(); break;
      case 'B': atras(); break;
      case 'L': izquierda(); break;
      case 'R': derecha(); break;
      case 'S': detener(); break;
    }
  }
}

void adelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void atras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void izquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void derecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
