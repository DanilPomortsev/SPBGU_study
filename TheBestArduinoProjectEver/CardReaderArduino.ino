#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>  

uint8_t SS_PIN = 10;
uint8_t RST_PIN = 9;
uint8_t EEPROM_START_ADDR = 5;
uint8_t EEPROM_KEY = 100;
uint8_t MAX_TAGS = 10; // максимальное количество меток
uint8_t savedTags = 0;// текущее количество меток
bool needClear; 

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; 

void setup() { 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.PCD_Init(); 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("Welcome, you can start applying cards"));
  pinMode(A5, INPUT_PULLUP);//кнопка регестрации
  pinMode(A4, INPUT_PULLUP);//кнопка удаления
  pinMode(8, OUTPUT);// зелёная лампочка
  pinMode(2, OUTPUT);// красная лампочка

  if (EEPROM.read(EEPROM_START_ADDR) != EEPROM_KEY){
    for (uint16_t i = 0; i < EEPROM.length(); ++i){
      EEPROM.write(i, 0x00);
    }
    EEPROM.write(EEPROM_START_ADDR, EEPROM_KEY);
  }
  else {
    savedTags = EEPROM.read(EEPROM_START_ADDR + 1);
  }
}

// функция сравнивающая массивы на равенство
bool compareUIDs(uint8_t *in1, uint8_t *in2, uint8_t size) {
  for (uint8_t i = 0; i < size; i++) {  
    if (in1[i] != in2[i]) return false; 
  }
  return true;                          
}

// функция ищущая метку среди зарегестрированных
int16_t foundTag(uint8_t *tag, uint8_t size) {
  uint8_t buf[8];   
  uint16_t address; 
  for (uint8_t i = 0; i < savedTags; i++) { 
    address = (i * 8) + EEPROM_START_ADDR + 2;  
    EEPROM.get(address, buf);               
    if (compareUIDs(tag, buf, size)) return address; 
  }
  return -1;                                
}

// функция сохраняющая метку
void saveTags(uint8_t *tag, uint8_t size){
  int16_t tagAddr = foundTag(tag, size); // проверяем зарегестрированна ли метка
  if(tagAddr == -1){
    // метка не зарегестрированна, нужно внести её
    uint16_t newTagAddr = (savedTags*8) + EEPROM_START_ADDR + 2;
    if(savedTags < MAX_TAGS) {
      for(uint16_t i = 0; i < size; ++i)
        EEPROM.write(i+newTagAddr, tag[i]);
      EEPROM.write(EEPROM_START_ADDR+1, ++savedTags);
    }
    greenLight();
    Serial.print("SR ");
    printTag(rfid.uid.uidByte, rfid.uid.size);
  }
  else{
    // метка уже была зарегестрированна, выводи ошибку
    redLight();
    Serial.println(F("AR"));
  }
}

// функция удаляющая метку
void delTags(uint8_t *tag, uint8_t size){
  int16_t tagAddr = foundTag(tag, size); // ищем метку
  uint16_t newTagAddr = (savedTags*8) + EEPROM_START_ADDR + 2;
  if (tagAddr != -1){
    // такая метка есть, удаляем
    Serial.print("SD ");
    printTag(rfid.uid.uidByte, rfid.uid.size);
    for(uint8_t i = 0; i < 8; ++i){
      EEPROM.write(tagAddr + i, 0x00);
      EEPROM.write(tagAddr + i, EEPROM.read((newTagAddr-8)+i));
      EEPROM.write((newTagAddr-8)+i, 0x00);
    }
    EEPROM.write(EEPROM_START_ADDR + 1, --savedTags);
    greenLight();
  }
  else {
    // такой метки нет, выдаём ошибку
    redLight();
    Serial.println(F("NR"));
  }
}


//функция выводящая метку
void printTag(uint8_t *tag, uint8_t size){
  for(uint8_t i = 0; i < size; ++i){
    Serial.print(tag[i], HEX);
    }
  Serial.print("\n");
}

// загорание зелёной лампочки
void greenLight(){
  analogWrite(8, 255);
  delay(900);
  analogWrite(8, 0);
}

// загорание красной лампочки
void redLight(){
  analogWrite(2, 255);
  delay(900);
  analogWrite(2, 0);
}

void loop() {
  if (!digitalRead(A5)){
    uint32_t start = millis();        
    bool needClear = 0;    
    // если кнопка регистрации зажата в течении 3 сек выводим всё
    while (!digitalRead(A5)) {   
      if (millis() - start >= 5000) { 
        Serial.println("AO");
        greenLight();           
        break;                        
      }
    }
    if (rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial()) // если метка поднесена, и кнопка нажата регестрируем
      saveTags(rfid.uid.uidByte, rfid.uid.size);
    }
  if (!digitalRead(A4)){
      uint32_t start = millis();        
      bool needClear = 0;    
      // если кнопка удаление зажата в течении 3 сек удаляем все 
      while (!digitalRead(A4)) {   
      if (millis() - start >= 3000) { 
        needClear = true;
        Serial.println("AD");
        greenLight();            
        break;                        
      }
    }
    // если нужно очищаем метки
    if (needClear){
      for (uint16_t i = 0; i < EEPROM.length(); ++i)
        EEPROM.write(i, 0x00);
      EEPROM.write(EEPROM_START_ADDR, EEPROM_KEY);
    }
    // если поднесена метка удаляем её
    if(rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial())
      delTags(rfid.uid.uidByte, rfid.uid.size);
  }
  // если кнопки не нажаты но метка поднесена ищем её в списке меток
  else if(rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial()){
      if(foundTag(rfid.uid.uidByte, rfid.uid.size) != -1){
        Serial.print(F("F "));
        printTag(rfid.uid.uidByte, rfid.uid.size);
        greenLight();
      }
      else{
        Serial.println(F("NF"));
        redLight();
      }
    }
}
