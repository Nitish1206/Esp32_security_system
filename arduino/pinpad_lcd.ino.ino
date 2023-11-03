#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
// #include <WiFi.h>
// #include <MySQL_Connection.h>
// #include <MySQL_Cursor.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS]      = {19, 18, 5, 17}; // GPIO19, GPIO18, GPIO5, GPIO17 connect to the row pins
byte colPins[COLS] = {16, 4, 0, 2};   // GPIO16, GPIO4, GPIO0, GPIO2 connect to the column pins


// const char* ssid = "your_wifi_ssid";
// const char* password = "your_wifi_password";

// const char* db_host = "your_mysql_server";
// const char* db_user = "your_username";
// const char* db_password = "your_password";
// const char* db_name = "your_database";

// Initialize instances of the necessary classes
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
// WiFiClient client;
// MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);

  // Initialize WiFi and connect to it
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // // Initialize the SQL database connection
  // if (conn.connect(db_host, db_user, db_password, db_name)) {
  //   Serial.println("Connected to MySQL Server");
  // } else {
  //   Serial.println("Connection to MySQL Server failed");
  // }
}
void loop() {
  // Display "Enter ID" on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter ID:");
  lcd.setCursor(0, 1);
  // Wait for the user to enter the ID
  String enteredID = getInputFromKeypad();

  // Check the ID in the database
  if (checkIDInDatabase(enteredID)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    lcd.setCursor(0, 1);

    // Wait for the user to enter the password
    String enteredPassword = getInputFromKeypad();

    // Check the password in the database
    if (checkPasswordInDatabase(enteredID, enteredPassword)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Granted");
      delay(5000);  // Wait for 5 seconds
      ESP.restart(); // Restart the ESP32
    } else {
      displayAccessDenied();
    }
  } else {
    displayAccessDenied();
  }
}
String getInputFromKeypad() {
  String input = "";
  char key = keypad.getKey();
  while (key != '#') {
    if (key) {
      if (key == '*') {
        lcd.setCursor(0, 1); // Set the cursor to the 2nd row
        lcd.print("                "); // Clear the 2nd row
        lcd.setCursor(0, 1); // Reset the cursor to the 2nd row
        input = "";  // Clear the input buffer
      } else {
        input += key;
        lcd.setCursor(0, 1);
        lcd.print(input);
      }
    }
    key = keypad.getKey();
  }
  return input;
}


bool checkIDInDatabase(String id) {
  return id.equals("75");
}
// bool checkIDInDatabase(String id) {

//   if (id == 75){

//   }
//   // Implement code to check the ID in the database
//   // Return true if ID is correct, false otherwise
// }
bool checkPasswordInDatabase(String id, String password) {
  // Implement your logic to check the ID and password in the database
  // For example, you can compare them to expected values or query a database
  return id.equals("75") && password.equals("76");
}

// bool checkPasswordInDatabase(String id, String password) {
//   // Implement code to check the password in the database
//   // Return true if password is correct, false otherwise
// }

void displayAccessDenied() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Denied");
  delay(2000);
}

