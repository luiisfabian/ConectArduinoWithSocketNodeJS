
const int sensorPin= A0;
int Led =13;
int Alarma=12;
const int LEDPin = 11;
const int LDRPin = A1;
const int threshold = 600; //Limite para determinar si la intensidad de la luz es baja
String mensajeEntrante;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Led,OUTPUT);  
  pinMode(Alarma,OUTPUT);
    pinMode(LEDPin, OUTPUT);
  pinMode(LDRPin, INPUT);
}

void loop() {
 
  
  while(Serial.available()>0){
      mensajeEntrante=Serial.readString();    
      if(mensajeEntrante.indexOf("dameLaTemperatura") > -1){

      //Serial.println("Hace frio");
        response();
      }else {
        Serial.println("comando no encontraod: " + mensajeEntrante);
        
      }
  }
  //parte ALARMA
  }

void response() {

  //parte ALARMA
  int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10;
  //esta funcion siguiente calcula los grados centigrados del sensor
  float GradosC = (getVoltage(sensorPin) - 0.5) * 100.0;
  Serial.print("Temperatura: ");
  Serial.print(celsius);
  Serial.print(" C - Grados ");
  Serial.println(GradosC);
     delay(500);
  if(GradosC>30)
    {
      //enciende alarma y led
        digitalWrite(Alarma, HIGH);
      digitalWrite(Led, HIGH);
      tone( 12, 1000, 500);//establece el tono
    }
  else {
        //apaga alarma y led
      digitalWrite(Alarma, LOW);
        digitalWrite(Led, LOW);
    }
  int estado_pin_button = digitalRead(3);
  //validamos el estado del boton
  if(estado_pin_button==0) {
    digitalWrite(Alarma, LOW);
    digitalWrite(Led, LOW);
    delay(10000);
  }//fin alarma
  
  //Parte LUZ
    int Intensidad = analogRead(LDRPin);
    Serial.print("Intensidad Luz: ");
    Serial.println(Intensidad);
    Serial.println("");
  if (Intensidad > threshold) 
    {
        //enciende LED
    digitalWrite(LEDPin, HIGH);
  }
  else {
          //apaga LED
      digitalWrite(LEDPin, LOW);
    }
  //fin luz
}

float getVoltage(int pin)
{
  //return (analogRead(pin) * 0.48875855);
  return (5.0 * analogRead(pin) * 100)/1024.0;
}


  
