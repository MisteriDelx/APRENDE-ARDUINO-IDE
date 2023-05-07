/*
 * PRÁCTICA PARA PROBAR LA MULTITAREA EN ARDUINO Y LA FUNCIÓN millis()
 */
// Se declaran las variables con "define" en lugar de con int o long para poder usar nombres para cada variable
int LED1=12 ; // creamos 3 variables y les adjudicamos el valor que representa el 
                      //número de pin al que va conectado cada LED
int LED2=11;
int LED3=10;
int PULSADOR=A1; // el pulsador irá conectado al pin analógico A1 aunque podríamos utilizar un pin digital

unsigned long tiempo_anterior_LED1 = millis();
long intervalo_tiempo_LED1 = 1000; // el LED1 parpadeará cada 1 segundo
int estadoLED1 = LOW;            // el LED1 comenzará en estado bajo o apagado

unsigned long tiempo_anterior_Potencimetro= millis();
long intervalo_tiempoPotenciometro = 2000;

void setup() {
    // El código aquí representado sólo se ejecutará una vez
    Serial.begin(9600); //inicializamos la comunicación serie
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
  // No es necesario configurar la entrada analógica porque está configurada como entrada por defecto
}

void loop() {
  unsigned long actualTime = millis();
  
  // TAREA 1. Conmutar el estado del LED1 cada cierto intervalo de tiempo
  if(actualTime - tiempo_anterior_LED1 > intervalo_tiempo_LED1) {
  tiempo_anterior_LED1 = actualTime; // tiempo_anterior_LED1 para a tomar el valor de actualTime
      if (estadoLED1 == HIGH) {
        estadoLED1 = LOW; //cambiamos el estado del LED1
      }
      else {
        estadoLED1 = HIGH;
      }
      digitalWrite(LED1,estadoLED1);
    }
  
  // TAREA2. Variamos la luminosidad del LED2 desde la entrada del monitor serie
  if (Serial.available()) {
      int userInput = Serial.parseInt(); //declaramos una variable de tipo entero llamada userInput que tomará el valor del entero que le llegue por el puerto serie
      if (userInput >= 0 && userInput < 256) { //si el valor se encuentra entre 0 y 255 lo que equivale a 0V o 5 V  entonces...
        analogWrite(LED2, userInput); // mostramos el valor leído desde el monitor serie en el LED2
      }
    }
  
    // TAREA3. Encender el LED3 desde un pulsador
    if (analogRead(PULSADOR) >150) {
       digitalWrite(LED3, HIGH);
    }
    else {
      digitalWrite(LED3, LOW);
    }
}
