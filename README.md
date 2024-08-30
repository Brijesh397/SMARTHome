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

Features To be added:
* Able to control everything using an Android/IOS application using MQTT protocol from anywhere in the world.
  * Create an Android APP.
  * Setup AWS MQTT Broker.
  * Establish communication between the ESP module and android app over MQTT using the AWS MQTT broker.
