//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// Tomodatchi
// 
// Made by Katy Diederichs
// License: CC-BY-SA 3.0
// Downloaded from: https://123d.circuits.io/circuits/1637498-tomodatchi

/////////////////////////////////////////////////////////////////
// Sketch by Angela Gu and Kaitlyn Diederichs for McHacks 2016 //
/////////////////////////////////////////////////////////////////

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // set interface pins for lcd screen
int led = 13;
int left_button = 6;
int select_button = 7;
int right_button = 8;

int sick_led = A0;
int ok_led = A1;
int good_led = A2;
int poo_led = A3;
int bulb = A4;

int option = 0;
int age = 0;
int belly = 0;
int happy = 0;
int poo = 50;
int sick = 50;
int perfect = 0;

void newLife();
boolean isSick();
boolean isPoop();  
void decay();
void meds(); 
void change_diaper();
void older();  
void isHappy();
boolean isDead();
void feed();
void play();


int counter = 0;
  
void setup() {

  pinMode(led, OUTPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(select_button, INPUT);
  
  pinMode(sick_led, OUTPUT);
  pinMode(ok_led, OUTPUT);
  pinMode(good_led, OUTPUT);
  pinMode(poo_led, OUTPUT);
  pinMode(bulb, OUTPUT);
  
  option = 0;
  counter = 0;
  
  newLife();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, I'm bob! ");
  lcd.setCursor(0, 1);
  lcd.print("love me <3      ");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("love me <3      ");
	delay(1500);
}


void loop() {
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    
  decay();
  older();
  if(isDead()){
    digitalWrite(bulb, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("I'M DEAD  X o X ");
    lcd.setCursor(0, 1);
    lcd.print("Age:            ");
    lcd.setCursor(8, 1);
    lcd.print(age);
    return;
  } else
  { digitalWrite(bulb, LOW); }
  isHappy();
  
  lcd.setCursor(0, 0);
  
  lcd.print("AGE:            ");
  lcd.setCursor(8, 0);
  lcd.print(age);
  delay(500);
  
  lcd.setCursor(0,0);
  
  lcd.print("FeedPlayHealPoop");  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(belly);
  lcd.setCursor(4,1);
  lcd.print(happy);
  lcd.setCursor(8,1);
  lcd.print(sick);
  lcd.setCursor(12,1);
  lcd.print(poo);
    
  int cursor_location = 0;
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  lcd.setCursor(cursor_location, 0);
  // print the number of seconds since reset:
  
  bool select_pressed = false;
  
  while (!select_pressed)
  {
    option = cursor_location;
    lcd.setCursor(0,0);
    switch(option)
    {
      case 0:
        lcd.print("FEEDPlayHealPoop");
       	break;
      case 4:
      	lcd.print("FeedPLAYHealPoop");
      	break;
      case 8:
      	lcd.print("FeedPlayHEALPoop");
      	break;
      case 12:
      	lcd.print("FeedPlayHealPOOP");
      	break;
      default:
        lcd.print("oops!");
    }
    
    cursor_location = option;
    
    select_pressed = (digitalRead(select_button) == HIGH);
    
    if (select_pressed) {break;}
    	
    
    
  
    bool right_pressed = false;
    bool left_pressed = false;
    
    while(!(left_pressed || right_pressed))
    {
      select_pressed = (digitalRead(select_button) == HIGH);
    
      if (select_pressed) {break;}
      if ((digitalRead(left_button) == HIGH)&&(cursor_location > 0))
      {
      	cursor_location -= 4;
        left_pressed = true;
      } else if ((digitalRead(right_button) == HIGH) && (cursor_location < 12))
      {
        cursor_location += 4;
        right_pressed = true;
      }
      delay(10);
    }
    
    if (select_pressed)
      break;
    
   select_pressed = (digitalRead(select_button) == HIGH);
   
  }
  
  if(option == 0){
    feed();
    option = 0;
  } else if(option == 4){
    play();
    option = 0;
  } else if(option == 8){
    meds();
    option = 0;
  } else if(option == 12){
    change_diaper();
    option = 0;
  }
  
counter ++;
  
} // end of main loop

void newLife(){
  option = 0;
  age = 0;
  belly = 0;
  happy = 0;
  poo = 50;
  sick = 50;
  perfect = 0;
}

boolean isSick(){
        if (sick > 50 + age*3){
            return true;
        }
        else{
            return false;
        }
    }
    
boolean isPoop(){
        if (poo > 55 + age*3 ){
            return true;
          	digitalWrite(poo_led, LOW);
        }
        else{
            return false;
            digitalWrite(poo_led, HIGH);
        }
    }
    
void decay(){
  if(isSick()){
    digitalWrite(sick_led, LOW);
    digitalWrite(ok_led, HIGH);
    digitalWrite(good_led, HIGH);
    belly-=15;
    happy-=20;
    poo+=10;
    sick+=15;
    }else if (isPoop() || belly < 0 || happy <0){
      digitalWrite(sick_led, HIGH);
      digitalWrite(ok_led, LOW);
      digitalWrite(good_led, HIGH);
      sick+=10;
      poo+=5;
      happy-=10;
      belly-=7;
    } else{
          
      digitalWrite(sick_led, HIGH);
      digitalWrite(ok_led, LOW);
      digitalWrite(good_led, HIGH);
    
      poo+=10;
      belly-=7;
      happy-=7;
    }
}
    
void meds(){
  if(isSick()){
    sick = 0;
  }
}
    
void change_diaper(){
  if(isPoop()){
    poo = 0;
  }
}
    
void older(){
  if (perfect > 3 + age){
    age++;
    perfect = 0;
    happy +=10;
  }
}
     
void isHappy(){
  if (happy > 150 & belly > 150){
    perfect++;
    digitalWrite(good_led, LOW);
    digitalWrite(ok_led, HIGH);
    digitalWrite(sick_led, HIGH);
  } else{
    digitalWrite(good_led, HIGH);
    if (isSick()){ digitalWrite(ok_led, HIGH);	digitalWrite(sick_led, LOW);}
    else { digitalWrite(ok_led, LOW);	digitalWrite(sick_led, HIGH);}
  }
}
     
boolean isDead(){
  if(sick > 150 + 2*age || age == 16){
    return true;
  }else{
    return false;
  }
  
  digitalWrite(sick_led, HIGH);
  digitalWrite(ok_led, HIGH);
  digitalWrite(good_led, HIGH);
  digitalWrite(poo_led, HIGH);
  
}
     
void feed(){
  happy +=20;
  belly +=50;
  if (happy > 175){
    happy = 175;
  }
  if (belly > 200){
    belly = 200;
  }
}
     
void play(){
  happy +=40;
  if (happy > 175){
    happy = 175;
  }
}
     

