# STM32F407 + ESP32 – AT Firmware + FreeRTOS + LVGL

In this project I have attempted to create a SMART Home device.

Features: 
* Using STM32 HAL along with FreeRTOS.
* Using ESP32 running AT Firmware for Wi-Fi Functionality.
  * Communicating with the ESP module using UART.
  * Gather incoming data using UART Interrupts in a buffer
  * Created my own drivers to interpret the incoming data and use it accordingly, have not used any libraries.
* Using LVGL for the GUI.
* Wi-Fi functionality.
* Gather geolocation using the google geolocation API.
  * Establishing SSL connection with googleapis.
  * Gather latitude and longitude data.  
* Gather weather information from OpenWeatherMap using geolocation.
  * Establishing TCP connection with openweathermap
  * Gathering weather (Temperature, Condition, Weather Icon) data.
  * Updating the SMART Home Panel based on the gathered data.
* Gather Time and Date using NTP Server.
  * Getting current UTC Time Stamp from NTP Server.
  * Getting Time zone using the Google Time Zone API with the help of the geolocation data and Time Stamp.
  * Calculating Local Time based on the UTC Timestamp and offset gathered from Google Time Zone API. 
* Gather Room Temperature using the MCP900 temp sensor and depending on Room Temperature and set Temperature turn on or of the Cooling / Heating.
* Can control Light and Fans.
* If you do not have internet access, then can set Time and Date manually.
VIDEO:
[<img src="https://i.ytimg.com/vi/Hc79sDi3f0U/maxresdefault.jpg" width="50%">](https://www.youtube.com/watch?v=407N6XnhPog "Now in Android: 55")

IMAGES:
* Home Screen:  
![Home Screen](https://github.com/user-attachments/assets/e183c80f-2757-4bdb-9e91-a8914fc68261)
* Temperature Screen:  
![Temperature Screen](https://github.com/user-attachments/assets/431b4609-8a92-442b-ad04-d34ac3354316)
* WiFi Screen:  
![Wifi Screen](https://github.com/user-attachments/assets/b0ff5c12-5b9d-41bc-b240-ec5cd2636130)
* NAV Screen:  
![NAV Screen](https://github.com/user-attachments/assets/17b5fbf4-e6b5-4732-ae96-7da9a1fab323)

Features To be added:
* Able to control everything using an Android/IOS application using MQTT protocol from anywhere in the world.
  * Create an Android APP.
  * Setup AWS MQTT Broker.
  * Establish communication between the ESP module and android app over MQTT using the AWS MQTT broker.
