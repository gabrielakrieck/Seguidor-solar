
#include <Servo.h> // inclui a biblioteca Servo

  //Declaração dos servos
  Servo horizontal; //Servo horizontal
  Servo vertical;   //Servo veLDR3_valical
  
  //Posição dos servos
  int servoh = 90;   
  int servov = 0;    
  
  //Limites de posição dos servos:
  //Servo veLDR3_valical
  int ServoV_MAX = 120;
  int ServoV_MIN = 0;
  
  //Servo horizontal
  int ServoH_MAX = 180;
  int ServoH_MIN = 90;

  // Conexão dos sensores LDR
  //  nome  = porta_analogica;
  int LDR1 = 0; //LDR1
  int LDR3 = 1; //LDR3
  int LDR4 = 2; //LDR4
  int LDR2 = 3; //LDR2
  
  //Outras variáveis de interesse
  int tempo_delay=10;
  int tolerancia=50;
  int LDR1_val;
  int LDR2_val;
  int LDR3_val;
  int LDR4_val;
  int dvert;
  int dhoriz;

  //SETUP
  void setup()
  {
    Serial.begin(9600);
    horizontal.attach(6); //SERVO HORIZONTAL NA POLDR3_valA 6 
    vertical.attach(5); //SERVO VELDR3_valICAL NA POLDR3_valA 5
  
    horizontal.write(servoh); //POSIÇÃO INICIAL SERVO HORIZONTAL = 90º
    vertical.write(servov); //POSIÇÃO INICIAL SERVO VELDR3_valICAL = 90º
    delay(3000);
  }

  //LOOP
  void loop() 
  {
    LDR1_val=analogRead(LDR4); // VALOR LIDO DO LDR1
    LDR2_val=analogRead(LDR2); // VALOR LIDO DO LDR2
    LDR3_val=analogRead(LDR3); // VALOR LIDO DO LDR3
    LDR4_val=analogRead(LDR1); // VALOR LIDO DO LDR4
    

    dvert=LDR1_val-LDR4_val;  // verifica a diferença entre cima e baixo
    dhoriz=LDR3_val-LDR2_val; // verifica a diferença entre direita e esqueLDR2a
  
    
    if (-1*tolerancia > dvert || dvert > tolerancia) //Verifica se a diferença dos valores do LDR1 e do LDR4 ultrapassa a tolerância. Se sim, move o motor vertical.
    {
      if (LDR1_val > LDR4_val)
      {
        servov = ++servov;
          if (servov > ServoV_MAX) 
          { 
            servov = ServoV_MAX;
          }
      }
      else if (LDR1_val < LDR4_val)
      {
        servov= --servov;
        if (servov<ServoV_MIN)
        {
          servov=ServoV_MIN;
        }
      }
      vertical.write(servov);
    }
  
    if (-1*tolerancia > dhoriz || dhoriz > tolerancia) //Verifica se a diferença dos valores do LDR2 e do LDR3 ultrapassa a tolerância. Se sim, move o motor horizontal.
    {
      if (LDR3_val>LDR2_val)
      {
        servoh=--servoh;
        if (servoh<ServoH_MIN)
        {
          servoh=ServoH_MIN;
        }
      }
      else if (LDR3_val < LDR2_val)
      {
        servoh=++servoh;
        if (servoh>ServoH_MAX)
        {
          servoh=ServoH_MAX;
        }
      }
      horizontal.write(servoh);
    }
    
    delay(tempo_delay);
}




