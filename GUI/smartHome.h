#ifndef SMART_HOME_H
#define SMART_HOME_H

#ifdef __cplusplus
extern "C"
{
#endif

/*************INCLUDES*****************/
#include "../../lvgl/lvgl.h"
#include <esp.h>
#include "main.h"

/*************ENUMS*********************/
typedef enum
{
	TEMPERATURESCREEN = 0,
	NAVSCREEN,
	HOMESCREEN,
	LIGHTANDFANSCREEN,
	SETTINGSCREEN,
	DATE,
	TIME,
	WIFITURNINGON,
	WIFISCREEN,
	WIFILOADING,
	WIFICONNECT,
	WIFICONNECTING,
	WIFIPASSWORD,
	BOOT
}currentScreen_t;

typedef enum
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
}day_t;

typedef enum
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}month_t;

/**************EXTERN VATIABLES********************/
extern char* days[7];
extern char* months[13];
extern  uint16_t  temperature;
extern  bool  coolingEnabled;
extern  bool  heatingEnabled;
extern  int  roomTemperature;
extern int  weatherTemperature;
extern bool wifiConnected;
extern bool espInitialised;
extern currentScreen_t	activeScreen;
extern char timeArray[14];
extern char dateArray[21];
extern char weatherIcon[4];
extern char weatherType[20];

/***************FUNCTION PROTOTYPE******************/
void createTemperatureScreen(void);
void createNavScreen(void);
void createhomeScreen(void);
void createSettingsScreen(void);
void createWifiLoadingScreen(void);
void createWifiConnectScreen(void);
void createLightFanScreen(void);
void createWifiScreen(void);
char* dayOfWeekToString(day_t day);
uint8_t stringToDayOfWeek(char *day);
uint8_t stringToMonth(char *month);
char* monthToString(month_t month);
void createWifiConnectingMessageBox(void);
void createWifiPasswordScreen(void);
void createWifiConnectingFailedMessageBox(void);
void createWifiConnectingSuccessfullMessageBox(void);
void creatCalendarScreen(void);
void creatTimeScreen(void);
void createBootScreen(void);
void createWifiTurningOnScreen(void);
void createWifiErrorMessageBox(void);
void setWeatherIcon(void);

/***************LVGL********************************/
//Screen Objects
extern lv_obj_t* temperatureScreen;
extern lv_obj_t* navScreen;
extern lv_obj_t* homeScreen;
extern lv_obj_t* lightFanScreen;
extern lv_obj_t* settingsScreen;
extern lv_obj_t* wifiTurningOnScreen;
extern lv_obj_t* wifiLoadingScreen;
extern lv_obj_t* wifiConnectScreen;
extern lv_obj_t* wifiPasswordScreen;
extern lv_obj_t* wifiConnectingMessageBox;
extern lv_obj_t* wifiConnectingFailedMessageBox;
extern lv_obj_t* wifiConnectingSuccessfullMessageBox;
extern lv_obj_t* wifiErrorMessageBox;
extern lv_obj_t* calendarScreen;
extern lv_obj_t* timeScreen;
extern lv_obj_t* bootScreen;

//Boot Screen Objects
extern lv_obj_t* smartHomeLabel;
extern lv_obj_t* bootSpinner;
extern lv_obj_t* bootLabel;

//Temperature Screen Objects
extern lv_obj_t* tempControlLabel;
extern lv_obj_t* temperautreArc;
extern lv_obj_t* ui_Panel1;
extern lv_obj_t* ui_Panel2;
extern lv_obj_t* temperatureLabel;
extern lv_obj_t* celciusLabel;
extern lv_obj_t* coolingButton;
extern lv_obj_t* coolingButtonLabel;
extern lv_obj_t* heatingButton;
extern lv_obj_t* heatingButtonLabel;
extern lv_obj_t* temperatureMenuButton;
extern lv_obj_t* noWifiTemperatureScreen;

//Nav Screen Objects
extern lv_obj_t* homeButton;
extern lv_obj_t* homeButtonLabel;
extern lv_obj_t* temperatureButton;
extern lv_obj_t* temperatureButtonLabel;
extern lv_obj_t* lightFanButton;
extern lv_obj_t* lightFanButtonLabel;
extern lv_obj_t* settingsButton;
extern lv_obj_t* settingsButtonLabel;

//Home Screen Objects
extern lv_obj_t* homeScreenLabel;
extern lv_obj_t* timeDatePanel;
extern lv_obj_t* timeLabel;
extern lv_obj_t* dateLabel;
extern lv_obj_t* temperatuePanel;
extern lv_obj_t* homeTemperatureLabel;
extern lv_obj_t* roomTemperatureLabel;
extern lv_obj_t* homeCelciusLabel;
extern lv_obj_t* weatherPanel;
extern lv_obj_t* weatherLabel;
extern lv_obj_t* weatherTemperatureLabel;
extern lv_obj_t* weatherCelciusLabel;
extern lv_obj_t* weatherImage;
extern lv_obj_t* co2Panel;
extern lv_obj_t* co2Label;
extern lv_obj_t* co2PercentLabel;
extern lv_obj_t* homeMenuButton;
extern lv_obj_t* noWifiHomeScreen;

//Light & Fan Screen
extern lv_obj_t* lightFanMenuButton;
extern lv_obj_t* lightPanel1;
extern lv_obj_t* lightLabel1;
extern lv_obj_t* lightSwitch1;
extern lv_obj_t* lightImage1;
extern lv_obj_t* lightPanel2;
extern lv_obj_t* lightLabel2;
extern lv_obj_t* lightSwitch2;
extern lv_obj_t* lightImage2;
extern lv_obj_t* fanPanel1;
extern lv_obj_t* fanLabel1;
extern lv_obj_t* fanSwitch1;
extern lv_obj_t* fanImage1;
extern lv_obj_t* fanPanel2;
extern lv_obj_t* fanLabel2;
extern lv_obj_t* fanSwitch2;
extern lv_obj_t* fanImage2;
extern lv_obj_t* noWifiLightFanScreen;

//Settings Screen
extern lv_obj_t* settingsMenuButton;
extern lv_obj_t* wifiButton;
extern lv_obj_t* wifiButtonLabel;
extern lv_obj_t* dateTimeButton;
extern lv_obj_t* dateTimeButtonLabel;

//Wifi Screen
extern lv_obj_t* wifiMenuButton;
extern lv_obj_t* wifiScreen;
extern lv_obj_t* wifiScreenPanel;
extern lv_obj_t* connectDetailsLabel;
extern lv_obj_t* nameLabel;
extern lv_obj_t* nameLabelAnswer;
extern lv_obj_t* ipAddressLabel;
extern lv_obj_t* ipAddressLabelAnswer;
extern lv_obj_t* securityLabel;
extern lv_obj_t* securityLabelAnswer;
extern lv_obj_t* conectWifiButton;
extern lv_obj_t* conectWifiButtonLabel;
extern lv_obj_t* disconectWifiButton;
extern lv_obj_t* disconectWifiButtonLabel;

//Wifi turning On Screen
extern lv_obj_t* wifiTurningOnMenuButton;
extern lv_obj_t* wifiTurningOnLoadingLabel;
extern lv_obj_t* wifiTurningOnLoadingSpinner;

//Wifi Loading Screen
extern lv_obj_t* wifiLoadingMenuButton;
extern lv_obj_t* wifiLoadingLabel;
extern lv_obj_t* wifiLoadingSpinner;

//Wifi Connecting Message Box
extern lv_obj_t* wifiConnectingLabel;
extern lv_obj_t* wifiConnectingSpinner;

//Wifi Connecting Failed Message Box
extern lv_obj_t* wifiConnectingFailedLabel;

//Wifi Connecting Successful Message Box
extern lv_obj_t* wifiConnectingSuccessfullLabel;

//Wifi Error Message; Box
extern lv_obj_t* wifiErrorLabel;

//Wifi Connect Screen
extern lv_obj_t* wifiConnectMenuButton;
extern lv_obj_t* wifi1Panel;
extern lv_obj_t* wifi1PanelLabel;
extern lv_obj_t* wifi1PanelButton;
extern lv_obj_t* wifi1PanelButtonLabel;
extern lv_obj_t* wifi2Panel;
extern lv_obj_t* wifi2PanelLabel;
extern lv_obj_t* wifi2PanelButton;
extern lv_obj_t* wifi2PanelButtonLabel;
extern lv_obj_t* wifi3Panel;
extern lv_obj_t* wifi3PanelLabel;
extern lv_obj_t* wifi3PanelButton;
extern lv_obj_t* wifi3PanelButtonLabel;
extern lv_obj_t* wifi4Panel;
extern lv_obj_t* wifi4PanelLabel;
extern lv_obj_t* wifi3PanelButton;
extern lv_obj_t* wifi3PanelButtonLabel;
extern lv_obj_t* wifi5Panel;
extern lv_obj_t* wifi5PanelLabel;
extern lv_obj_t* wifi5PanelButton;
extern lv_obj_t* wifi5PanelButtonLabel;
extern lv_obj_t* wifi6Panel;
extern lv_obj_t* wifi6PanelLabel;
extern lv_obj_t* wifi6PanelButton;
extern lv_obj_t* wifi6PanelButtonLabel;
extern lv_obj_t* wifi7Panel;
extern lv_obj_t* wifi7PanelLabel;
extern lv_obj_t* wifi7PanelButton;
extern lv_obj_t* wifi7PanelButtonLabel;
extern lv_obj_t* wifi8Panel;
extern lv_obj_t* wifi8PanelLabel;
extern lv_obj_t* wifi8PanelButton;
extern lv_obj_t* wifi8PanelButtonLabel;
extern lv_obj_t* wifi9Panel;
extern lv_obj_t* wifi9PanelLabel;
extern lv_obj_t* wifi9PanelButton;
extern lv_obj_t* wifi9PanelButtonLabel;
extern lv_obj_t* wifi10Panel;
extern lv_obj_t* wifi10PanelLabel;
extern lv_obj_t* wifi10PanelButton;
extern lv_obj_t* wifi10PanelButtonLabel;

//Wifi Password Screen
extern lv_obj_t* wifiPasswordScreenNameLabel;
extern lv_obj_t* wifiPasswordScreenNameAnswer;
extern lv_obj_t* wifiPasswordScreenPasswordLabel;
extern lv_obj_t* wifiPasswordTextArea;
extern lv_obj_t* ui_Keyboard1;
extern lv_obj_t* closeImageButton;

//Calendar Screen
extern lv_obj_t* calendar;
extern lv_obj_t* calendarCrossButton;
extern lv_obj_t* calendarTickButton;
extern lv_obj_t* calendarScreenLabel;

//Time Screen
extern lv_obj_t* timeScreenLabel;
extern lv_obj_t* timeScreenCrossButton;
extern lv_obj_t* timeScreenTickButton;
extern lv_obj_t* hourLabel;
extern lv_obj_t* hourRoller;
extern lv_obj_t* minutesLabel;
extern lv_obj_t* minutesRoller;
extern lv_obj_t* secondsLabel;
extern lv_obj_t* secondsRoller;
extern lv_obj_t* amPMLabel;
extern lv_obj_t* amPMRoller;

//Images
LV_IMG_DECLARE(menuPNG);
LV_IMG_DECLARE(bulbPNG);
LV_IMG_DECLARE(fanPNG);
LV_IMG_DECLARE(noWifiPNG);
LV_IMG_DECLARE(crossPNG);
LV_IMG_DECLARE(tickPNG);
LV_IMG_DECLARE(wifiPNG);
LV_IMG_DECLARE(PNG01d);
LV_IMG_DECLARE(PNG01n);
LV_IMG_DECLARE(PNG02d);
LV_IMG_DECLARE(PNG02n);
LV_IMG_DECLARE(PNG03dn);
LV_IMG_DECLARE(PNG04dn);
LV_IMG_DECLARE(PNG09dn);
LV_IMG_DECLARE(PNG10d);
LV_IMG_DECLARE(PNG10n);
LV_IMG_DECLARE(PNG11dn);
LV_IMG_DECLARE(PNG13dn);
LV_IMG_DECLARE(PNG50dn);


#ifdef __cplusplus
}
#endif

#endif
