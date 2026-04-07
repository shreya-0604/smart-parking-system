#include <Servo.h>
#include <LiquidCrystal.h>

Servo gate;

// Sensors
int IR = 2;        
int EXIT = 4;      

// Parking slots
int slot1 = 11;
int slot2 = 12;
int slot3 = 13;
int slot4 = A0;
int slot5 = A1;
int slot6 = A2;

int totalSlots = 6;
int availableSlots = 6;

LiquidCrystal lcd(7,6,5,4,9,10);

void setup()
{
  pinMode(IR, INPUT);
  pinMode(EXIT, INPUT);

  pinMode(slot1, OUTPUT);
  pinMode(slot2, OUTPUT);
  pinMode(slot3, OUTPUT);
  pinMode(slot4, OUTPUT);
  pinMode(slot5, OUTPUT);
  pinMode(slot6, OUTPUT);

  digitalWrite(slot1,LOW);
  digitalWrite(slot2,LOW);
  digitalWrite(slot3,LOW);
  digitalWrite(slot4,LOW);
  digitalWrite(slot5,LOW);
  digitalWrite(slot6,LOW);

  gate.attach(3);

  lcd.begin(16,2);

  // -------- WELCOME MESSAGE --------
  lcd.setCursor(0,0);
  lcd.print("WELCOME TO");

  lcd.setCursor(0,1);
  lcd.print("SMART PARKING");

  delay(2000);
  lcd.clear();

  // -------- TOTAL SLOTS --------
  lcd.setCursor(0,0);
  lcd.print("Total Slots:");

  lcd.setCursor(0,1);
  lcd.print(totalSlots);

  delay(2000);
  lcd.clear();
}

void loop()
{
  // -------- AVAILABLE SLOTS --------
  lcd.setCursor(0,0);
  lcd.print("Available:");

  lcd.setCursor(0,1);
  lcd.print(availableSlots);
  lcd.print("   ");

  // -------- ENTRY --------
  if(digitalRead(IR)==LOW)
  {
    if(availableSlots == 0)
    {
      lcd.clear();
      lcd.print("Parking Full");
      delay(2000);
      lcd.clear();
      return;
    }

    lcd.clear();
    lcd.print("Car Detected");
    delay(1000);

    allocateSlot();
  }

  // -------- EXIT --------
  if(digitalRead(EXIT)==LOW)
  {
    if(availableSlots < totalSlots)
    {
      availableSlots++;

      lcd.clear();
      lcd.print("Car Exit");

      lcd.setCursor(0,1);
      lcd.print("Slots Left:");
      lcd.print(availableSlots);

      delay(2000);
      lcd.clear();
    }
  }
}

// -------- AUTO SLOT ALLOCATION --------
void allocateSlot()
{
  if(digitalRead(slot1)==LOW)
  {
    digitalWrite(slot1,HIGH);
    availableSlots--;
    showSlot(1,"GO STRAIGHT");
  }
  else if(digitalRead(slot2)==LOW)
  {
    digitalWrite(slot2,HIGH);
    availableSlots--;
    showSlot(2,"STRAIGHT LEFT");
  }
  else if(digitalRead(slot3)==LOW)
  {
    digitalWrite(slot3,HIGH);
    availableSlots--;
    showSlot(3,"STRAIGHT RIGHT");
  }
  else if(digitalRead(slot4)==LOW)
  {
    digitalWrite(slot4,HIGH);
    availableSlots--;
    showSlot(4,"STRAIGHT BACK");
  }
  else if(digitalRead(slot5)==LOW)
  {
    digitalWrite(slot5,HIGH);
    availableSlots--;
    showSlot(5,"BACK RIGHT");
  }
  else if(digitalRead(slot6)==LOW)
  {
    digitalWrite(slot6,HIGH);
    availableSlots--;
    showSlot(6,"BACK LEFT");
  }
}

// -------- DISPLAY SLOT --------
void showSlot(int num, String dir)
{
  lcd.clear();

  lcd.print("Slot: ");
  lcd.print(num);

  lcd.setCursor(0,1);
  lcd.print(dir);

  gate.write(90);
  delay(3000);
  gate.write(0);

  delay(1500);
  lcd.clear();
}
