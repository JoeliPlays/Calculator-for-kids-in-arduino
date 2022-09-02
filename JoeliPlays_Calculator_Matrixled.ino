#include <Keypad.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
//ejemplo para crear animaciones en módulo matriz LED con Arduino basado en MAX7219


//--Teclado variables--
//Codigo de prueba del teclado

const byte filas = 4; 
const byte columnas = 4;
byte pinesFilas[]  = {13,12,11,10};
byte pinesColumnas[] = {9,8,7,6};
char teclas[4][4] = {{'1','2','3','+'},
                     {'4','5','6','-'},
                     {'7','8','9','*'},
                     {'C','0','=','/'}};
Keypad teclado = Keypad( makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas);

String scrolear = "Holaaaa, diviertete amigo!";
String proximo_mensaje;
 
#define HARDWARE_TYPE MD_MAX72XX::DR0CR0RR1_HW
#define NUM_OF_MATRIX 4
 
#define CLK_PIN   5 
#define DATA_PIN  4
#define CS_PIN    3
 
#define DELAY_ANIMATION 700
 

#define BUF_SIZE  75
char mensaje[BUF_SIZE] ; 
int men1;
char mensaje2[BUF_SIZE] ;

char mensaje3[BUF_SIZE] ;
int men3;

char mensaje4[BUF_SIZE];

char resultado_char[BUF_SIZE] ;
int respuesta_int;
 
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, NUM_OF_MATRIX);
// Text parameters
#define CHAR_SPACING  1 // pixels between characters


void setup() {
  // inicializar el objeto mx
  mx.begin();
 
  // poniendo la matriz en modo de prueba
  mx.control(MD_MAX72XX::TEST, true);
  delay(2000);
 
  // desactivando el modo de prueba
  mx.control(MD_MAX72XX::TEST, false);
 
  // Establecer intencidad a un valor de 5
  mx.control(MD_MAX72XX::INTENSITY, 10);

  Serial.begin(9600);
  Serial.println("Teclado 4x4 con Biblioteca Keypad");
  Serial.println();
}

 void printText(uint8_t modStart, uint8_t modEnd, char *pMsg)
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3: // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

 
void parte1(){
  int ct = 0;
  char tecla = teclado.getKey();
  while (tecla!= '+' and tecla!= '-' and tecla!= '*' and tecla!= '/' and tecla!= 'C' and tecla!= '=' and ct <=1){
    if (tecla == '0'){
      Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
  }
    if (tecla == '1'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '2'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '3'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '4'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '5'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '6'){
     Serial.println(ct);
     mensaje[ct]=tecla;
      ct++;
    }
    if (tecla == '7'){
     Serial.println(ct);
     mensaje[ct]=tecla;
      ct++;
    }
    if (tecla == '8'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }
    if (tecla == '9'){
     Serial.println(ct);
     mensaje[ct]=tecla;
     ct++;
    }

     tecla = teclado.getKey();
    delay(200);
  }
  Serial.println(mensaje);
    printText(0, NUM_OF_MATRIX-1, mensaje);
      delay(1000);
}

void parte2(){
  int ct = 0;
  char tecla = teclado.getKey();
  while (tecla!= '0' and tecla!= '1' and tecla!= '2' and tecla!= '3' and tecla!= '4' and tecla!= '5' and tecla!= '6' and tecla!= '7' and tecla!= '8' and tecla!= '9' and tecla!= '=' and tecla!= 'C' and ct <=0){
    if (tecla == '+'){
      Serial.println(ct);
     mensaje2[ct]=tecla;
     ct++;
  }
    if (tecla == '-'){
     Serial.println(ct);
     mensaje2[ct]=tecla;
     ct++;
    }
    if (tecla == '*'){
     Serial.println(ct);
     mensaje2[ct]=tecla;
     ct++;
    }
    if (tecla == '/'){
     Serial.println(ct);
     mensaje2[ct]=tecla;
     ct++;
    }
     tecla = teclado.getKey();
    delay(200);
  }
  Serial.println(mensaje2);
    printText(0, NUM_OF_MATRIX-1, mensaje2);
      delay(1000);
}

void parte3(){
  int ct = 0;

  char tecla = teclado.getKey();
  while (tecla!= '+' and tecla!= '-' and tecla!= '*' and tecla!= '/' and tecla!= 'C' and tecla!= '=' and ct <=1){
    if (tecla == '0'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
  }
    if (tecla == '1'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '2'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '3'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '4'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '5'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '6'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
      ct++;
    }
    if (tecla == '7'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
      ct++;
    }
    if (tecla == '8'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }
    if (tecla == '9'){
     Serial.println(ct);
     mensaje3[ct]=tecla;
     ct++;
    }

     tecla = teclado.getKey();
    delay(200);
  }
  Serial.println(mensaje3);
    printText(0, NUM_OF_MATRIX-1, mensaje3);
      delay(1000);
}


void parte4 (){
  char tecla = teclado.getKey();
  while (tecla != '='){tecla = teclado.getKey(); delay (200);}
  String letra1 = String(mensaje);
  men1 = letra1.toInt();
  Serial.print("Numero en int: ");Serial.println(men1);
      //convertir_int(mensaje3, men3);
  String letra2 = String(mensaje3);
  men3 = letra2.toInt();
  Serial.print("simbolo: ");Serial.println(mensaje2);
      //calcu(men1, men3, mensaje2 , respuesta_int);
  Serial.println(mensaje2[0]);

   if (mensaje2[0]){
    switch (mensaje2[0]){
      case '+':
      respuesta_int = men1 + men3;
      break;

      case '-':
      respuesta_int = men1 - men3;
      break;

      case '*':
      respuesta_int = men1 * men3;
      break;

      case '/':
      respuesta_int = men1 / men3;
      break;
      
    }
    
  }
  Serial.print("La operacion: ");Serial.println(respuesta_int);
  delay(200);
  String num_letra;
  num_letra += respuesta_int ;
  num_letra.toCharArray(resultado_char, 76);
  printText(0, NUM_OF_MATRIX-1, resultado_char);
  Serial.println(resultado_char);
  delay(1000);
}

void actualizar_mensaje(){
 
  while( Serial.available() ){
 
    char c = Serial.read();
 
    if( c == '\n' ){
      scrolear = proximo_mensaje;
      proximo_mensaje = "";
      break;
    }
    else
      proximo_mensaje += c;
    
  }
}

void slide_text(int ms_delay){
  int col = 0;
  int last_pos;
  bool completo = false;
  
  mx.clear();
 
  while( completo == false ){
    last_pos = printText(col, scrolear);
    delay(ms_delay);
    col++;
    if( last_pos > (int)mx.getColumnCount() )
      completo = true;
  }
}

int printText(int pos, const String text){
  int w;
  
  for( int i = 0; i < text.length(); i++ ){
    // imprimir letra
 
    w = mx.setChar( pos, text[i] );
    // la proxima letra empieza donde termina esta
    pos = pos - w; 
    // Se deja una columna entre letras.
    mx.setColumn(pos, B00000000);
    
    pos = pos - 1;
    
    if( pos < 0 )
      break;
      
  }
  mx.update();
  
  return pos;
}



void loop() {
  slide_text(50);
  actualizar_mensaje();
  parte1(); 
  parte2();
  parte3();
  parte4();
   
}
 
