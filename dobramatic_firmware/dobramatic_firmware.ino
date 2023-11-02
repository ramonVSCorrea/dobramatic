/******************************************************************************
                  --PROJETO: DOBRADOR DE ROUPAS AUTOMÁTICO--

  GRUPO: Flávio Junio de Jesus
         Josimar Ferreira Faustino
         Lucas Dias Cardoso
         Ramon Vinícius Silva Corrêa
         Yuri Ferreira Lourenço

  TURMA: TEEL01N - 4
*******************************************************************************/
                  /*--INCLUSÃO DE BIBLIOTECAS--*/
                  
#include <Servo.h> //Inclui a biblioteca para Servo motor 
                  
/******************************************************************************/
                   /*--DEFINIÇÃO DE SERVOS--*/

Servo servo1;  //Define um nome para o primeiro servo
Servo servo2;  //Define um nome para o segundo servo
Servo servo3;  //Define um nome para o terceiro servo

/******************************************************************************/
              /*--DEFINE PINO E VARIÁVEIS PARA O LDR--*/

#define ldrPin A0 //Define o pino A0 como pino do LDR

int ldrValor = 0; //Valor lido do LDR

/******************************************************************************/
                /*--VARIÁVEIS PARA SERVO--*/

int servo1Pos = 180; //Variável para a posição do Servo1
int servo2Pos = 0; //Variável para a posição do Servo2
int servo3Pos = 0; //Variável para a posição do Servo3

/******************************************************************************/
                /*--VARIÁVEIS PARA BOTÃO--*/

int button = 5; //Define o pino 5 como botão
int pres = 0; //Lê o nível lógico do botão

/******************************************************************************/
                     /*--VARIÁVEIS PARA DELAY--*/

int dLay = 850; //Define o tempo de Delay dos motores 

/*****************************************************************************/
                    /*--VARIÁVEIS PARA BUZZER--*/

int buzzer = 6; //Define o pino 6 como Buzzer
int i = 0; //Variável para "for"

/*****************************************************************************/

int liga = 0; //Variável para habilitar a dobra da camisa

void setup() //Setup do Programa
{
         /*--DEFINIÇÃO E CONFIGURAÇÃO DOS PINOS PARA OS SERVOS--*/

  servo1.attach(2); //Define o pino 2 como sinal para o primeiro servo
  servo2.attach(3); //Define o pino 3 como sinal para o segundo servo
  servo3.attach(4); //Define o pino 4 como sinal para o terceiro servo
  
  servo1.write(servo1Pos); //Inicia o servo1 na posição 180°
  servo2.write(servo2Pos); //Inicia o servo2 na posição 0°
  servo3.write(servo3Pos); //Inicia o servo3 na posição 0°

  Serial.begin(9600); //Inicia o monitor serial do Arduino
  
  /***********************************************************************/
                        /*--CONFIGURAÇÕES DO BOTÃO--*/
                        
  pinMode (button, INPUT_PULLUP); //Define o pino do botão como entrada

  /***********************************************************************/
                      /*--CONFIGURAÇÕES BUZZER--*/

  pinMode(buzzer, OUTPUT); //Define o pino do Buzzer como saída       
}
  /***********************************************************************/

void loop() //Inicia o loop do Programa
{
  ldrValor = analogRead(ldrPin); //Lê o valor registrado pelo LDR

  Serial.println(ldrValor); //Imprime o valor lido pelo LDR no monitor serial da IDE Arduino

  /********************************************************************/
             /*--LEITURA DO BOTÃO E DO LDR--*/
               
  pres = digitalRead(button); //Lê o nível lógico do botão

  /*******************************************************************/
                    /*--INICIA FUNÇOES--*/
                    
  if(pres == HIGH){dobrar();} //Se o botão for pressionado inicia a função dobra()
  
  if((ldrValor <= 800)&&(liga == 1)) //Se a camisa for retirada do dobrador 
  {
    liga = 0; //Habilita a dobra de outra camisa  
  } 

  while((ldrValor >= 1000)&&(liga == 0))
  {
    delay(2000); //Espera 2 segundos caso o LDR tenha detectado algum engano
    ldrValor = analogRead(ldrPin); //Lê o valor registrado pelo LDR

    if(ldrValor <= 800) //Se o LDR detectar um valor menor que 800
    {
      liga = 1; //Muda a variável liga para 1, fazendo com que saia do while
    }
    else //Senão 
    {
      delay(3500); //Espera 3,5 segundos
      dobrar(); //Inicia função para dobrar a camisa
    }   
  }
}

/****************************************************************************/
                    /*--CRIAÇÃO DE FUNÇÕES--*/

void dobrar() // Função para movimentar os motores
{
  /******************************************************************/
                 /*--MOVIMENTA O PRIMEIRO MOTOR--*/
                      
    if(servo1Pos == 180) //Se o motor estiver na posição de 180°
  {
    servo1Pos = 0; //A variável servo1Pos recebe o valor 0
    servo1.write(servo1Pos); //Posiciona o motor na posição de 0°
  }
  
  delay(dLay); //Espera um tempo de 800 milissegundos
  
    if(servo1Pos == 0) //Se o motor estiver na posição de 0°
  {
    servo1Pos = 180; //A variável servo1Pos recebe o valor 180
    servo1.write(servo1Pos); //O motor vai para a posição de 180°
  }
  
  delay(dLay); //Espera um tempo de 800 milissegundos
    
  /******************************************************************/
                 /*--MOVIMENTA O SEGUNDO MOTOR--*/

    if(servo2Pos == 0) //Se o motor estiver na posição de 0°
  {
    servo2Pos = 180; //A variável servo2Pos recebe o valor 180
    servo2.write(servo1Pos); //Posiciona o motor na posição de 180°
  }
  
  delay(dLay); //Espera um tempo de 800 milissegundos
  
    if(servo2Pos == 180) //Se o motor estiver na posição de 180°
  {
    servo2Pos = 0; //A variável servo2Pos recebe o valor 0
    servo2.write(servo2Pos); //O motor vai para a posição de 0°
  }
  
  delay(dLay); //Espera um tempo de 800 milissegundos
                    
  /******************************************************************/
                   /*--MOVIMENTA O TERCEIRO MOTOR--*/
                      
    if(servo3Pos == 0) //Se o motor estiver na posição de 0°
  {
    servo3Pos = 180; //A variável servo3Pos recebe o valor 180
    servo3.write(servo3Pos); //Posiciona o motor na posição de 180°
  }
  
  delay(790); //Espera um tempo de 790 milissegundos
  
    if(servo3Pos == 180) //Se o motor estiver na posição de 180°
  {
    servo3Pos = 0; //A variável servo3Pos recebe o valor 0
    servo3.write(servo3Pos); //O motor vai para a posição de 0°
  }
  
  delay(790); //Espera um tempo de 800 milissegundos

 /******************************************************************/
                      /*--ATIVA O BUZZER--*/

   for(i=0; i<2; i++) //Executa o bloco 2 vezes
   {
      tone(buzzer, 1500); //Ativa o buzzer
      delay(500); //Espera 300 milissegundos
      noTone(buzzer); //Desativa o buzzer
      delay(500); //Espera 300 milissegundos
   }

  /******************************************************************/

  liga = 1; //Desabilita a função dobrar() enquanto a camisa ainda está no dobrador
}
