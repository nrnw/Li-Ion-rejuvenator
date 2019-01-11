#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x3F,16,4);  // set the LCD address and type

//variable definitions
float max_voltage=10;
float min_voltage=1;
int discharging_delay =4;
int notifiy_delay=5;
float a0reading;
bool wait_to_begin=1;//to use for wait until user press *  
bool cycle_alarm =0;// to use for buzzer when cycle done
bool charge=0;//to switch charging
bool discharge=0;//to switch discharging
bool a=0;//to avoid blinking of the lcd "Start btn press msg" 
char enteredKey;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad


//pin definitions
const int buzzer_pin=13;
const int rly_chg_pin=12;
const int rly_dchg_pin=11;

//---------------------------------other functions------------------------------------
void disp_batt_v(){// this function will display battery terminal voltage in LCD screen

a0reading=float(analogRead(A0))/100;//read analog pin voltage
//show battery voltage
lcd.setCursor(0,0);
lcd.print("Batt voltage:");
//lcd.print(a0reading*0.004882812);
lcd.print(a0reading);
lcd.print(" V ");
//Serial.println(a0reading);

  
}



void keypadEvent( KeypadEvent key ){  
  switch ( customKeypad.getState() ) {  
  
  case PRESSED:  
        switch (key) { 
      
        case '1': 
        enteredKey='1';
        break;
        
        case '2': 
        enteredKey='2';
        break;

        case '3': 
        enteredKey='3';
        break;

        case '4': 
        enteredKey='4';
        break;

        case '5': 
        enteredKey='5';
        break;


        case '6': 
        enteredKey='6';
        break;

        case '7': 
        enteredKey='7';
        break;


        case '8': 
        enteredKey='8';
        break;

        case '9': 
        enteredKey='9';
        break;

        case '0': 
        enteredKey='0';
        break;
      
        case '*': 
        enteredKey='*';
        break;

        case '#': 
        enteredKey='#';
        break;
      
        case 'A': 
        enteredKey='A';
        break;

        case 'B': 
        enteredKey='B';
        break;

        case 'C': 
        enteredKey='C';
        break;

        case 'D': 
        enteredKey='D';
        break;
        
      
      }
  
  
  
  case RELEASED:  
    
  break;  
  
  
  case HOLD:  
  switch (key) {  
  
  case 'A':
    Serial.println("hold A");  
    enteredKey='E';  
  break;  
  
  
  case 'B':  
    enteredKey='F'; 
  break;  
  
  
   case 'C':  
    enteredKey='G'; 
  break;  
  
  
  case 'D':  
    enteredKey='H'; 
  break;  
  }  
  break;  
  
  
  case IDLE: 
   
  break;  
  }  
}  


void set_max_voltage(){
  int k=0; // counter to detect key presses
  String value_String;

  digitalWrite(buzzer_pin, HIGH);
  delay(200);
  digitalWrite(buzzer_pin, LOW);
    
  lcd.setCursor(0,1);
  lcd.print("Max voltage ?       "); 
  lcd.setCursor(0,2);
  lcd.print("                    "); 


  
  while(k<2){
  char keyval=customKeypad.getKey();
    
    
    if(keyval && keyval!='A' && keyval!='B' && keyval!='C' && keyval!='D' && keyval!='*' && keyval!='#'  ){//if key pressed && fool proof
    btn_beep();
    value_String = String(value_String + keyval) ;
      if(k==0){
          value_String=value_String +'.';
      }
    Serial.println(keyval);
    Serial.println(value_String);
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.print(value_String); 
    lcd.setCursor(7,2);
    lcd.print("V");
    k++;
    }
      
  }

  
  max_voltage=value_String.toFloat();
  Serial.println(max_voltage);
  Serial.println("all done!");


  EEPROM.write(0, int(max_voltage*10));//addr, val(0~255)


 
  delay(300);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
  delay(100);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  lcd.setCursor(0,1);
  lcd.print("Max voltage saved!"); 
  
}


void set_min_voltage(){
  int k=0; // counter to detect key presses
  String value_String;

  digitalWrite(buzzer_pin, HIGH);
  delay(200);
  digitalWrite(buzzer_pin, LOW);
    
  lcd.setCursor(0,1);
  lcd.print("Min voltage ?       "); 
  lcd.setCursor(0,2);
  lcd.print("                    "); 


  
  while(k<2){
  char keyval=customKeypad.getKey();
  
    if(keyval && keyval!='A' && keyval!='B' && keyval!='C' && keyval!='D' && keyval!='*' && keyval!='#'  ){//if key pressed && fool proof
    btn_beep();
    value_String = String(value_String + keyval) ;
      if(k==0){
          value_String=value_String +'.';
      }
    Serial.println(keyval);
    Serial.println(value_String);
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.print(value_String); 
    lcd.setCursor(7,2);
    lcd.print("V");
    k++;
    }
      
  }

  
  min_voltage=value_String.toFloat();
  Serial.println(min_voltage);
  Serial.println("all done!");


  EEPROM.write(1, int(min_voltage*10));//addr, val(0~255)


 
  delay(300);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
  delay(100);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  lcd.setCursor(0,1);
  lcd.print("Min voltage saved!"); 
  
}




void set_discharging_delay(){
  int k=0; // counter to detect key presses
  String value_String;

  digitalWrite(buzzer_pin, HIGH);
  delay(200);
  digitalWrite(buzzer_pin, LOW);
    
  lcd.setCursor(0,1);
  lcd.print("Delay to discharge? "); 
  lcd.setCursor(0,2);
  lcd.print("                    "); 


  
  while(k<2){
  char keyval=customKeypad.getKey();
  
    if(keyval && keyval!='A' && keyval!='B' && keyval!='C' && keyval!='D' && keyval!='*' && keyval!='#'  ){//if key pressed && fool proof
    btn_beep();
    value_String = String(value_String + keyval) ;
      
    Serial.println(keyval);
    Serial.println(value_String);
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.print(value_String); 
    lcd.setCursor(5,2);
    lcd.print("s");
    k++;
    }
      
  }

  
  discharging_delay=value_String.toInt();
  Serial.println(discharging_delay);
  Serial.println("all done!");


  EEPROM.write(2, discharging_delay);//addr, val(0~255)


 
  delay(300);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
  delay(100);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  lcd.setCursor(0,1);
  lcd.print("Dischrg delay saved!"); 
  
}


void set_notifiy_delay(){
  int k=0; // counter to detect key presses
  String value_String;

  digitalWrite(buzzer_pin, HIGH);
  delay(200);
  digitalWrite(buzzer_pin, LOW);
    
  lcd.setCursor(0,1);
  lcd.print("Delay to notify?    "); 
  lcd.setCursor(0,2);
  lcd.print("                    "); 


  
  while(k<2){
  char keyval=customKeypad.getKey();
  
    if(keyval && keyval!='A' && keyval!='B' && keyval!='C' && keyval!='D' && keyval!='*' && keyval!='#'  ){//if key pressed && fool proof
    btn_beep();
    value_String = String(value_String + keyval) ;
      
    Serial.println(keyval);
    Serial.println(value_String);
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.print(value_String); 
    lcd.setCursor(5,2);
    lcd.print("s");
    k++;
    }
      
  }

  
  notifiy_delay=value_String.toInt();
  Serial.println(notifiy_delay);
  Serial.println("all done!");


  EEPROM.write(3, notifiy_delay);//addr, val(0~255)


 
  delay(300);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
  delay(100);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  lcd.setCursor(0,1);
  lcd.print("Notify delay saved! "); 
  
}





void btn_beep(){
  delay(100);
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);
    
}

//----------------------------------initializing--------------------------------------
void setup()
{

  max_voltage=float(EEPROM.read(0))/10;//restore values from eeprom
  min_voltage=float(EEPROM.read(1))/10;//restore values from eeprom
  discharging_delay = EEPROM.read(2);
  notifiy_delay=EEPROM.read(3);

  
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

  //Put welcome msg
  lcd.setCursor(0,0);// column,row
  lcd.print("********************");
  lcd.setCursor(0,1);
  lcd.print("Battery Rejuvenator");
  lcd.setCursor(0,2);// column,row
  lcd.print("     For Ni-MH");
  lcd.setCursor(0,3);// column,row
  lcd.print("********************");



pinMode(buzzer_pin, OUTPUT);
pinMode(rly_chg_pin, OUTPUT);
pinMode(rly_dchg_pin, OUTPUT);
delay(200);
digitalWrite(buzzer_pin, LOW);
digitalWrite(rly_chg_pin, HIGH);
digitalWrite(rly_dchg_pin, HIGH); 
  
  Serial.begin(9600);

  lcd.clear();

  customKeypad.setHoldTime(2000);
  customKeypad.addEventListener(keypadEvent); // Keypad event listener - Interrupt 
}


//==============================main loop==================================
void loop()
{
customKeypad.getKey();//read keypad
disp_batt_v();//measure and display battery voltage in LCD


while(wait_to_begin==1){//wait until user press "*" to start the cycle
        disp_batt_v();//here also we show the battery voltage
         digitalWrite(rly_chg_pin, HIGH);
         digitalWrite(rly_dchg_pin, HIGH); 

            
        if(cycle_alarm==1){// turn on buzzer too 
          digitalWrite(buzzer_pin, HIGH);
          delay(30);
          digitalWrite(buzzer_pin, LOW);
          delay(50);
                
        }
        
        if(a==0){//print msg only once to avoid blinking
        lcd.setCursor(0,1);// column,row
        lcd.print("Max:"); 
        lcd.print(max_voltage,1); //1 means one decimal  point
        lcd.print("V"); 
        lcd.print(" Min:"); 
        lcd.print(min_voltage,1); 
        lcd.print("V   "); 
        lcd.setCursor(0,2);
        lcd.print(" DT:"); 
        lcd.print(discharging_delay); 
        lcd.print("s"); 
        lcd.print(" NT:"); 
        lcd.print(notifiy_delay); 
        lcd.print("s"); 
         
        lcd.setCursor(0,3);// column,row
        lcd.print("Press * to start...");  
        //lcd.setCursor(0,2);
        //lcd.print("                    ");
        a=1;
        } 
       
        customKeypad.getKey();//read keypad during while loop

      switch(enteredKey){
            case '*': //do this if keypad * pressed
              wait_to_begin=0;
              enteredKey=' ';
              lcd.clear(); 
              btn_beep();
              discharge=0;// to avoid discharging when battery is full and stopped discharging and pressed * again
              
              
            break;

             case '#': //mute alarm
              cycle_alarm=0;
              btn_beep();
              enteredKey=' ';
              a=0;
            break;
            
            case 'E':
              set_max_voltage();
            break;

            case 'F':
              set_min_voltage();
              
            break;

            case 'G':
              set_discharging_delay();
            break;

            case 'H':
              set_notifiy_delay();
            break;

           }

          
   }


   

//check battery voltage
if(a0reading<max_voltage){ //if plugged battery is not charged full, start charging
  charge=1;
}else{// battery already chraged to the max voltage
  lcd.setCursor(0,1);// column,row
  lcd.print("Battery is full!");
  lcd.setCursor(0,3);// column,row
  lcd.print("Press * to discharge");
  customKeypad.getKey();
  if (enteredKey=='*'){//start discharging
            discharge=1;
            
     }
}


while(charge==1){
  Serial.println(wait_to_begin);
customKeypad.getKey();//read keypad


disp_batt_v();
   if (enteredKey=='#'){//stop everything if "#" pressed and wait until again "*" press
            wait_to_begin=1;
            a=0;//to display msg
            break;
     }

  lcd.setCursor(0,2);// column,row
  lcd.print("                    ");
  lcd.setCursor(0,3);// column,row
  lcd.print("Charging...         ");
  
digitalWrite(rly_chg_pin, LOW);
digitalWrite(rly_dchg_pin, HIGH); 

if(a0reading>=max_voltage){ //battery is charged full
   digitalWrite(rly_chg_pin, HIGH);
   digitalWrite(rly_dchg_pin, HIGH);
   charge=0;
   discharge=1;
  lcd.setCursor(0,2);// column,row
  lcd.print("   Battery full !");
    int original_delay=discharging_delay;
    while(discharging_delay>0){
    lcd.setCursor(0,3);
    lcd.print("Discharging in ");
    lcd.print(discharging_delay);
    lcd.print("s ");
    delay(1000);
    discharging_delay--;
    customKeypad.getKey();//read keypad


   disp_batt_v();
   if (enteredKey=='#'){//stop everything if "#" pressed and wait until again "*" press
            wait_to_begin=1;
            a=0;//to display msg
            break;
     }
    }
     discharging_delay=original_delay; //restore the delay value for next cycle
}
}

while(discharge==1){
    customKeypad.getKey();//read keypad


    disp_batt_v();
   if (enteredKey=='#'){//stop everything if "#" pressed and wait until again "*" press
            wait_to_begin=1;
            a=0;//to display msg
            break;
     }

  lcd.setCursor(0,1);// column,row
  lcd.print("                    ");
  lcd.setCursor(0,2);// column,row
  lcd.print("                    ");
  lcd.setCursor(0,3);// column,row
  lcd.print("Discharging...      ");

  digitalWrite(rly_chg_pin, HIGH);
  digitalWrite(rly_dchg_pin, LOW);

  if(a0reading<=min_voltage){ //battery is discharged to the threshold
   digitalWrite(rly_chg_pin, HIGH);
   digitalWrite(rly_dchg_pin, HIGH);
   charge=0;
   discharge=0;
  lcd.setCursor(0,2);// column,row
  lcd.print("Battery discharged !");

    int original_delay=notifiy_delay;
    while(notifiy_delay>0){
    lcd.setCursor(0,3);
    lcd.print("Notifying in ");
    lcd.print(notifiy_delay);
    lcd.print("s ");
    delay(1000);
    notifiy_delay--;
    customKeypad.getKey();//read keypad


   disp_batt_v();
   if (enteredKey=='#'){//stop everything if "#" pressed and wait until again "*" press
            wait_to_begin=1;
            a=0;//to display msg
            break;
     }
    }
    notifiy_delay=original_delay;//restore the delay value for next cycle
    
    lcd.setCursor(0,2);
    lcd.print("Cycle complete!     ");
     wait_to_begin=1;
     cycle_alarm=1;
     a=0;//to display msg
     break;
      
}
  
  
}


Serial.println(wait_to_begin);
}
