// Práctica encender y apagar un LED a través de botón pulsador
const int LED = 13;
const int BOTON = 7;
int val;
int val2=0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT);
}

void loop() {
  val = digitalRead(BOTON);
  digitalWrite(LED, HIGH);

  
  if (val == HIGH && val2==0) {
    val2=1;
    digitalWrite(LED, LOW);
    delay(350); 
    
    digitalWrite(LED, HIGH);
    delay(5000);
    val2=0;
  } 
}