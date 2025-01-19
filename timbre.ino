const int LED = 13;              // Pin del LED (timbre)
const int BOTON = 7;             // Pin del botón
const unsigned long TIEMPO_ESPERA = 10000;  // Tiempo de espera entre pulsaciones (10 segundos)
const unsigned long TIEMPO_ESPERA_30SEG = 30000;  // Tiempo de espera después de 3 pulsaciones (30 segundos)
const int MAX_PULSACIONES = 3;   // Número máximo de pulsaciones antes de esperar 30 segundos

unsigned long tiempoUltimaPulsacion = 0;  // Almacena el último tiempo de pulsación
unsigned long tiempoUltimaEspera = 0;     // Almacena el tiempo de la última espera de 30 segundos
unsigned long tiempoUltimaInactividad = 0; // Almacena el tiempo de inactividad (sin pulsación de botón)

int contadorPulsaciones = 0;  // Cuenta las pulsaciones del botón

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT);
}

void loop() {
  int estadoBoton = digitalRead(BOTON);

  // Solo consideramos la pulsación si ha pasado un tiempo suficiente desde la última
  if (estadoBoton == HIGH && (millis() - tiempoUltimaPulsacion) > 50) {
    tiempoUltimaPulsacion = millis(); // Actualizamos el tiempo de la última pulsación

    // Reiniciar el contador de inactividad si se presiona el botón
    tiempoUltimaInactividad = millis();
    
    // Si el contador de pulsaciones es menor a 3, encendemos el LED
    if (contadorPulsaciones < MAX_PULSACIONES) {
      digitalWrite(LED, HIGH);
      delay(100);  // Mantén el LED encendido por 100ms
      digitalWrite(LED, LOW);
      contadorPulsaciones++; // Incrementamos el contador
    }

    // Si ya han sido 3 pulsaciones, esperamos 30 segundos antes de permitir más pulsaciones
    if (contadorPulsaciones == MAX_PULSACIONES) {
      tiempoUltimaEspera = millis(); // Actualizamos el tiempo de la última espera
      while (millis() - tiempoUltimaEspera < TIEMPO_ESPERA_30SEG) {
        // Espera 30 segundos, pero sigue revisando el botón (no bloquea el programa)
      }
      contadorPulsaciones = 0; // Reiniciamos el contador
    }

    // Después de cada pulsación, espera el tiempo mínimo antes de permitir otra
    delay(TIEMPO_ESPERA);  // Puedes ajustar este tiempo si lo deseas
  
  }
  
  // Verificar si han pasado 30 segundos sin pulsaciones
  if (millis() - tiempoUltimaInactividad > TIEMPO_ESPERA_30SEG) {
    contadorPulsaciones = 0; // Reiniciar el contador de pulsaciones después de 30 segundos de inactividad
  }
  
}
