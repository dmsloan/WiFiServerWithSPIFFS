// this is an example Secrets.h file. Change the name to Secrets.h and replace the 
// XXXXXXX

#define SSID "XXXXXXXXXXX" // if your key is a string it needs to be in quotes. Note no semicolon after a hash define
                           // using the define of ssid conflicts with the WiFi library WiFi.SSID
//#define ssid "XXXXXXX"    // this does not work
#define PASSWORD "XXXXXXXXXXX"

// the following block is for WiFiMulti.h support on the ESP32. You can define as many as you choose.
#define ssid_from_AP_1 "XXXXXXX"
#define your_password_for_AP_1 "XXXXXXX"
#define ssid_from_AP_2 "XXXXXXX"
#define your_password_for_AP_2 "XXXXXXX"
#define ssid_from_AP_3 "XXXXXXX"
#define your_password_for_AP_3 "XXXXXXX"

#define sql_server_address "192.168.0.85"
#define sql_server_insert_name "pi_insert"
#define sql_server_insert_password "raspbery"