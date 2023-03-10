//joaogabrielbz_//

#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <string.h>

// SERVOMOTORCONFIGS
Servo myservo;
const int FECHADO = 180;
const int ABERTO = 90;

// KEYPADCONFIGS
const byte LINHAS = 4; 
const byte COLUNAS = 4; 

char hexaKeys[LINHAS][COLUNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rPins[LINHAS] = {5, 4, 3, 2};
byte cPins[COLUNAS] = {A3, A2, A1, A0};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rPins, cPins, LINHAS, COLUNAS);

//PAINEL
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);


//VARIAVEIS
String senha;
bool senhaCriada = false;


//METODOS
void trancado(){
    lcd.setCursor(0,1);
    lcd.print(">>ERRADO!");
     lcd.setCursor(11,1);
      lcd.print("(");
      lcd.setCursor(13,1);
      lcd.print(")");
    for (int i = 9; i > 0; i--) {
      lcd.setCursor(12,1);
      lcd.print(i);
      delay(1000);
  }
}

void aberto(){
    myservo.write(ABERTO);
    lcd.setCursor(0,1);
    lcd.print(">>CORRETO");
    lcd.setCursor(11,1);
      lcd.print("(");
      lcd.setCursor(13,1);
      lcd.print(")");
    for (int i = 9; i > 0; i--) {
      lcd.setCursor(12,1);
      lcd.print(i);
      delay(1000);
  }
}

bool menu(){
  myservo.write(FECHADO);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>(A) ABRIR");
  lcd.setCursor(0,1);
  lcd.print(">>(B) REDEFINIR");
  //char key = customKeypad.getKey();
         while(true) {
           char key = customKeypad.getKey();
           if(key == 'A'){
             return false;
           }
           if(key == 'B'){
             return true;
           }
            
          }
}  

String criaSenha(){
  lcd.setCursor(5,1);
  lcd.print("[____]");
  lcd.setCursor(6,1);
  while(senha.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          senha += key;
          lcd.print("#");
          }
        }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>SENHA CRIADA<<");
  lcd.setCursor(1, 1);
  lcd.print("   [      ]    ");
  String txt = "======";
  lcd.setCursor(5, 1);
  delay(300);
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(300);
  }
  lcd.clear();
  senhaCriada = true;
  return senha;    
}

bool confereSenha(String senha){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>SENHA: [____]");
  lcd.setCursor(10,0);

  String input = "";
  while(input.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          input += key;
          lcd.print("#");
          }
        }
  if(input == senha){
    return true;
  }
  else{
     return false;
  }
}

String redefinir(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(">>NOVA SENHA<<");
  lcd.setCursor(5,1);
  lcd.print("[____]");
  lcd.setCursor(6,1);
  senha = "";
  while(senha.length() < 4){
      char key = customKeypad.getKey();
         if(key >= '0' && key <= '9') {
          senha += key;
          lcd.print("#");
          }
        }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">SENHA RECRIADA<");
  lcd.setCursor(1, 1);
  lcd.print("   [      ]    ");
  String txt = "======";
  lcd.setCursor(5, 1);
  delay(300);
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(300);
  }
  lcd.clear();
  senhaCriada = true;
  return senha;
}

//PRINCIPAL
void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  myservo.attach(6,600,2300);
  myservo.write(FECHADO);

  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);
  lcd.print("   BEM VINDO!   ");
  delay(300);
  lcd.clear();
  delay(300);

  lcd.setCursor(5,1);
  lcd.print("[____]");
  delay(100); 
  lcd.setCursor(1, 0);
  String txt = ">>NOVA SENHA<<";
  for (byte i = 0; i < txt.length(); i++) {
    lcd.print(txt[i]);
    delay(100);
  }

  senha = criaSenha();
}
  
void loop(){ 
  if(!senhaCriada){
    senha = criaSenha();
  }
  else{
    while(true){
      if(menu() == false){
        if(confereSenha(senha) == true){
          aberto();
        } else{
          trancado();
        }
    } else{
      if(confereSenha(senha) == true){
        redefinir();
      }else{
        trancado();
      }
    }
  }
}
}
