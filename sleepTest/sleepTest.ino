/* Simplied example of DeepSleep Functionality provided by ESP32
 *  
 * esp_deep_sleep_enable_timer_wakeup(time in microseconds) has to be placed in setup
 * esp_deep_sleep_start() can be placed anywehre in loop to start the sleep mode.
 */

void setup() {
  Serial.begin(115200);
  esp_deep_sleep_enable_timer_wakeup(5000000); //5secs. Input take MicroSeconds.
}

void loop() {
  for(int i = 0; i<10; i++)
  {
    Serial.println("Working hard");
    delay(500);
    if(i == 9) {
      Serial.println("Taking a break");
      esp_deep_sleep_start();
      Serial.println("This line is never printed");
    }
  }
}
