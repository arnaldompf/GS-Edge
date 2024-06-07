//Chamando a biblioteca do LCD
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // Portas do LCD

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(13, INPUT); // definindo como entrada porta 13 
  pinMode(9, OUTPUT); // definindo como saída porta 9
  pinMode(8, INPUT); // definindo como entrada porta 8
  pinMode(6, INPUT); // definindo como entrada porta 6
  Serial.begin(9600); 
  lcd.begin(16,2); //Ligando o LCD
}

void loop()
{
  
  int currentState = digitalRead(13); // Lê o atual estado do sensor na porta 13
  Serial.print("Estado Atual: "); // Imprime o estado atual no monitor serial 
  Serial.println(currentState); // Imprime o estado atual no monitor serial
  delay(1000); // Intervalo
  
  if (currentState != 0) { // Caso estado seja diferente de 0
  	digitalWrite(9, HIGH); // Sinal 1 para porta 9
  }
  
  else {				   // Caso contrario
  	digitalWrite(9, LOW);  // Sinal 0 para porta 9
  }
  
  
  int balance = analogRead(A0);
  int weight = map(balance, 0, 914, 0, 30000);
  
  lcd.clear();
  lcd.setCursor(0, 0);  // Setando Primeira linha do visor
  lcd.print("PoseiDrone"); // Imprimindo a mensagem 
  lcd.setCursor(0, 1); // Segunda linha do visor         
  lcd.print ("Peso: "); // Imprimindo mensagem
  lcd.print(weight); // Imprimindo mensagem
  lcd.print ("g"); 
  delay(5000);
  Serial.print("Peso: "); // Imprime o estado atual no monitor serial 
  Serial.println(weight); // Imprime o estado atual no monitor serial
  
  
  // Código para transformar o sinal sensor 1 em centimetros 
  long duration, cm;
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(5);
  digitalWrite(8, LOW);
  
  pinMode(8, INPUT);
  duration = pulseIn(8, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  
  // Print no serial da distancia em centimetros
  Serial.print("Distancia dos Animais: ");
  Serial.print(cm);
  Serial.print("CM");
  Serial.println();
  // Print no visor distancia dos animais
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PoseiDrone");
  lcd.setCursor(0,1);
  lcd.print("Dist.Peixes:");
  lcd.print(cm);
  lcd.print("cm");
  delay(5000);
  
  if (cm < 40){	 
  tone(7, 2000); // Aciona o buzzer
  }
  
  else {
  noTone(7); // Desliga o buzzer
  }
  	
  // Código para transformar o sinal sensor 2 em centimetros 
  long duration1, cm1;
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  delayMicroseconds(2);
  digitalWrite(6, HIGH);
  delayMicroseconds(5);
  digitalWrite(6, LOW);
  
  pinMode(6, INPUT);
  duration1 = pulseIn(6, HIGH);
  
  cm1 = microsecondsToCentimeters1(duration1);
  
  // Print no serial da distancia dos resuídos em centimetros
  Serial.print("Distancia resuidos: ");
  Serial.print(cm1);
  Serial.print("CM");
  Serial.println();
  // Print no visor distancia dos residuos
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PoseiDrone");
  lcd.setCursor(0,1);
  lcd.print("Dist. Lixos:");
  lcd.print(cm1);
  lcd.print("cm");
  delay(5000);
  
  // Transformar entrada em graus celsius
  int reading = analogRead(A1);
  float voltage = reading * 0.0048828125;
  voltage = (voltage - 0.5);
  float temperature = voltage / 0.01;
  // Envia o valor para porta serial
  Serial.print("Temperatura: ");
  Serial.println(temperature);
  // Print no visor temperatura
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PoseiDrone");
  lcd.setCursor(0,1);
  lcd.print("Temp.: ");
  lcd.print(temperature);
  lcd.print(" C");
  delay(5000);
  
}


// Código para transformar o sinal em centimetros 
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
  }

long microsecondsToCentimeters1(long microseconds1) {
  return microseconds1 / 29 / 2;
  }