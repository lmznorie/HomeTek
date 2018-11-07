/*
VERSION FINAL; 18 MARZO DEL 2013; 4.01 P.M.
VERSION 2.0 [AGREGADO ALARMA, PUERTON, Y LUZ AUTOMATICA] 25 DE MARZO DEL 2013; 11.25 A.M.
*/

//Incluir las siguientes librerías: 

#include <IRremote.h> //Librería para el receptor infrarrojo (IR)
#include <Servo.h> //Librería para los servomotores 

//Declaración de variables y asignación de pines

int valFotorluz;
int valFotorauto;
int valAlarma;
bool nocauto;
bool alarmaon;
bool caron = false;
//Entradas/Salidas Analógicas 

int Fotorluz = A2;
int Fotorauto = A3;

//Entradas/Salidas Digitales

int Elevador1 = 1;
int Elevador2 = 2;
int LuzSala =3;
int PuertaCerrada = 4;
int PuertaAbierta = 5;
int Lampara1 = 6;
int Lampara2 = 7;
int Alarma = 12;


//Señal del receptor infrarrojo (IR) [INICIO]
int CIR = 9;
IRrecv irrecv(CIR);
decode_results valorIR;
long int codir; //Variable para almacenar el código leído por el receptor infrarrojo (IR)
//Señal del receptor infrarrojo (IR) [FIN]

Servo SerAuto;
Servo SerPuerta;

//Alarma [INICIO]
int Bocina=11; 
int notas[] = {1915, 1014}; //Tonos 
int n=0; 
int m= 0; 
int tnota=100; 
int pausa=100; 
//Alarma [FIN]

//Códigos, control remoto Samsung 31T-016 INICIO
long int CSPOWER =4105841032;
long int CSPMODE =3135877228;
long int CSSMODE =2618744002;
long int CSTVVIDEO =3459683302;
long int CSUNO =3778927144;
long int CSDOS =2908251746;
long int CSTRES =657459652;
long int CSCUATRO =4120482440;
long int CSCINCO =1931099650;
long int CSSEIS =742730860;
long int CSSIETE =1167253836;
long int CSOCHO =1747313982;
long int CSNUEVE =2340753640;
long int CSCERO =3119867746;
long int CSCHSCAN =2479124606;
long int CSSLEEP =1441014914;
long int CSADDDEL =3248603014;
long int CSSURROUND =551334792;
long int CSZOOM =158659426;
long int CSSURF =2424074206;
long int CSMTS =1150532780;
long int CSPSIZE =2308325960;
long int CSTURBO =538772752;
long int CSDISPLAY =1908947622;
long int CSMUTE =591444258;
long int CSMENU =1723810024;
long int CSCHMAS =1595074756;
long int CSCHMENOS =412973352;
long int CSVOLMAS =1752382022;
long int CSVOLMENOS =2209452902;
long int CSPRECH =3398220998;
//Códigos, control remoto Samsung 31T-016 FIN

void setup(){   
  
  Serial.begin(9600); //Abrie el puerto serie a una velocidad de 9600 bps
   irrecv.enableIRIn(); //Inicio del receptor infrarrojo (IR)
  
  pinMode(Elevador1, OUTPUT);
  pinMode(Elevador2, OUTPUT);
  pinMode(LuzSala, OUTPUT);
  pinMode(PuertaAbierta, OUTPUT);
  pinMode(PuertaCerrada, OUTPUT);
  pinMode(Lampara1, OUTPUT);
  pinMode(Lampara2, OUTPUT);
  pinMode(Bocina, OUTPUT);
  pinMode(Alarma, INPUT);
 
  SerAuto.attach(A4); 
  SerPuerta.attach(A5); 
  

  
} //Fin del void setup

void loop() {
 
  
  // Mostrar en el monitor serial el valor recibido por el receptor infrarrojo (IR) [INICIO]
    if (irrecv.decode(&valorIR)) //Condición para que se muestre solo cuando es un valor diferente, (cuando se presiona otro botón)
    {
      
      Serial.println("El código del botón presionado es: ");
      Serial.println(valorIR.value); //Muestra el código del botón presionado en el control remoto
      irrecv.resume(); //Recibe el nuevo valor
     
   
    }
  // Mostrar en el monitor serial el valor recibido por el receptor infrarrojo (IR) [FIN]
   
  codir = valorIR.value; //Asignacion del código leído por el receptor infrarrojo (IR)

  valFotorluz = analogRead(Fotorluz);
  delay(10);
  
  valFotorauto = analogRead(Fotorauto);
   delay(10);
   
  valAlarma = digitalRead(Alarma);
  delay(10);
  
 
 
  if (codir==CSPOWER) {
   SerPuerta.write(5); 
   digitalWrite(PuertaCerrada, HIGH);
   digitalWrite(PuertaAbierta, LOW);
   digitalWrite(Lampara1, LOW);
   digitalWrite(Lampara2, LOW);
   digitalWrite(Elevador1, LOW);
   digitalWrite(Elevador2, LOW);
   nocauto = false;
   alarmaon = false;
   digitalWrite(LuzSala, LOW);
   SerPuerta.write(5); 
   SerAuto.write(8); 
  }
  
  if (codir==CSVOLMAS) {
   SerPuerta.write(5); 
   digitalWrite(PuertaCerrada, HIGH);
   digitalWrite(PuertaAbierta, LOW);
  }
  
    if (codir==CSVOLMENOS) {
   SerPuerta.write(150); 
   digitalWrite(PuertaAbierta, HIGH);
   digitalWrite(PuertaCerrada, LOW);
  }
  
     if (codir==CSUNO) {
   digitalWrite(Lampara1, HIGH);
  }
  
     if (codir==CSCUATRO) {
   digitalWrite(Lampara1, LOW);

  }
  
       if (codir==CSDOS) {
   digitalWrite(Lampara2, HIGH);
  }
  
     if (codir==CSCINCO) {
   digitalWrite(Lampara2, LOW);

  }
  
         if (codir==CSCHMAS) {
   digitalWrite(Elevador1, HIGH);
   digitalWrite(Elevador2, LOW);
  }
  
     if (codir==CSCHMENOS) {
   digitalWrite(Elevador1, LOW);
   digitalWrite(Elevador2, HIGH);

  }

  if (codir==CSPRECH) {
   digitalWrite(Elevador1, LOW);
   digitalWrite(Elevador2, LOW);

  }
  
    if (codir==CSNUEVE) {
   nocauto = true;

  }
  
  
    if (codir==CSZOOM) {
   nocauto = false;
  }
  

     if (nocauto == true)
     {
       if (valFotorluz>950) {
   digitalWrite(LuzSala, HIGH);

  }
  
         if (valFotorluz<900) {
   digitalWrite(LuzSala, LOW);

  }
  
     }  
     
     
    if (codir ==CSTRES) {
   digitalWrite(LuzSala, HIGH);

  }
  
     
     
    if (codir == CSSEIS) {
   digitalWrite(LuzSala, LOW);

  }
      
      
       if (valFotorauto>500) {
        
          SerAuto.write(98);
          delay(4100); 
           SerAuto.write(8);
      
    }
    
  
   //Para abrir la cochera, es necesario presionar primero el boton MTS
   if (caron==true){ 
     
    if (codir == CSMUTE) {
        
          SerAuto.write(98);
          delay(4100); 
           SerAuto.write(8);
           caron = false;
    }
   }
   
    if (codir == CSMTS) {
           caron = true;
          
    }
    
     if (valFotorauto<400) {
           SerAuto.write(8);
          
    }

     if (codir==CSSURF) {
   alarmaon = true;
  }
  
  
     if (codir==CSDISPLAY) {
   alarmaon = false;
  }
  
  
  if (alarmaon==true){
  if (valAlarma != 0) {
    for(n=0;n<2;n++){ 

     for(m=0;m<=tnota;m++){ 
     digitalWrite(Bocina,HIGH); 
     delayMicroseconds(notas[n]); 

     digitalWrite(Bocina,LOW); 
     delayMicroseconds(notas[n]);  

     } 
     
     delay(pausa); //tiempo en silencio entre escalas 
     
     } 
    }
   }

} //Fin del void loop
