#define parado 1
#define abriendo 2
#define cerrando 3
#define obstaculo 4
 
char comando='d';   //variable para almacenar el dato entrante
char estado; //variable de estados
int motor= 8;  //motor de 12vc
int vcc= 9;  //Alimentacion motor
int fc=11;  // final de carrera
int fcc=12;  //final de carrera 2
int irled =10; //led infrarrojo
int ireciver =7; //receptor infrarrojo
int sirena = 6; // Sirena para el portón (5v)
int leda = 5; //indicador para cuando abrió
int ledc = 4; // indicador para cuando cerró

void setup() {
 Serial.begin(9600);
 pinMode(motor,OUTPUT);
 pinMode(vcc,OUTPUT);
 pinMode(irled,OUTPUT);
 pinMode(fcc,INPUT);
 pinMode(fc,INPUT);
 pinMode(ireciver,INPUT);
 pinMode(leda,OUTPUT);
 pinMode(ledc,OUTPUT);
 pinMode(sirena,OUTPUT);
}

void loop() {
 if(Serial.available()>0){
  comando=Serial.read();
  Serial.println(comando); //recibe el dato bluetooth y lo almacena
}
 switch (comando){
  case 'a':
  estado=abriendo;
  break;
  case'b':
  estado=cerrando;
  break;
  case 'c':
  estado=parado;
  break;
}
 switch (estado){
  case parado:
  digitalWrite(vcc,LOW);
  digitalWrite(irled,LOW);
  digitalWrite(sirena, LOW);
  break;
  case obstaculo:
  digitalWrite(motor,HIGH);
  digitalWrite(vcc,HIGH);
  digitalWrite(irled,HIGH);
  digitalWrite(sirena, HIGH);
  digitalWrite(ledc,HIGH);
  digitalWrite(leda,HIGH);
  break;
  case abriendo:
  digitalWrite(motor,HIGH);
  digitalWrite(vcc,HIGH);
  digitalWrite(irled,HIGH);
  digitalWrite(sirena, HIGH);
  digitalWrite(ledc,LOW);
  digitalWrite(leda,LOW);
  break;
  case cerrando:
  digitalWrite(motor, LOW);
  digitalWrite(vcc,HIGH);
  digitalWrite(irled,HIGH);
  digitalWrite(sirena, HIGH);
  digitalWrite(ledc,LOW);
  digitalWrite(leda,LOW);
  break;
}
  if((digitalRead(fcc)>0) && (estado == abriendo)){
    comando='c';
    Serial.println("Abierto");
    digitalWrite(leda,HIGH);
    }
  if((digitalRead(fcc)>0) && (estado == obstaculo)){
    digitalWrite(vcc,LOW);
    delay(10000);
    comando='b';
    Serial.println("Intentado cerrar...");
    }
  if((digitalRead(fc)>0) && (estado == cerrando)){
    comando='c';
    Serial.println("Cerrado");
    digitalWrite(ledc,HIGH);
    }    
    int b =digitalRead(ireciver);  //recive la lectura del receptor infrarrojo
   if( (estado==cerrando) && b != 0){ 
    comando='c';
    Serial.println("Obstaculo encontrado");
    }
}
