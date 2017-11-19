#define abierto 1
#define cerrado 2
#define parado 3
#define abriendo 4
#define cerrando 5
 
char comando='d';
char estado;
int motor= 8;  //motor de 12vc
int vcc= 9;  //Alimentacion motor
int fc=11;  // final de carrera
int fcc=12;  //final de carrera 2
int irled =10; //led infrarrojo
int ireciver =7; //receptor infrarrojo

void setup() {
 Serial.begin(9600);
 pinMode(motor,OUTPUT);
 pinMode(vcc,OUTPUT);
 pinMode(irled,OUTPUT);
 pinMode(fcc,INPUT);
 pinMode(fc,INPUT);
 pinMode(ireciver,INPUT);
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(3,OUTPUT);
}

void loop() {
 if(Serial.available()>0){
  comando=Serial.read();
  Serial.println(comando);
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
  case abierto:
  digitalWrite(vcc,LOW);
  digitalWrite(3, LOW);
  digitalWrite(irled,LOW);
  break;
  case cerrado:
  digitalWrite(vcc,LOW);
  digitalWrite(3, LOW);
  digitalWrite(irled,LOW);
  break;
  case parado:
  digitalWrite(vcc,LOW);
  digitalWrite(3, LOW);
  digitalWrite(irled,LOW);
  break;
  case abriendo:
  digitalWrite(motor,HIGH);
  digitalWrite(vcc,HIGH);
  digitalWrite(irled,HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  break;
  case cerrando:
  digitalWrite(motor, LOW);
  digitalWrite(vcc,HIGH);
  digitalWrite(irled,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(3, HIGH);
  break;
}
  if((digitalRead(fcc)>0) && (estado == abriendo)){
    comando='c';
    Serial.println("Final de carrera 1");
    digitalWrite(4,HIGH);
    }

  if((digitalRead(fc)>0) && (estado == cerrando)){
    comando='c';
    Serial.println("Final de carrea 2");
    digitalWrite(5,HIGH);
    }    
    int b =digitalRead(ireciver);
   if(((estado==abriendo)|| (estado==cerrando)) && b != 0){ 
    comando='c';
    Serial.println(b);
   Serial.println("Led infrarrojo");}
}
