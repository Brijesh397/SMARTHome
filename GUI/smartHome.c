/************INCLUDES*****************/
#include "smartHome.h"

/***********GLOBAL VARIABLES**************/
uint16_t  temperature = 22;
int  roomTemperature = 22;
int  weatherTemperature = 22;
char weatherIcon[4] = {0};
bool coolingEnabled = true;
bool heatingEnabled = false;
bool wifiConnected = false;
bool espInitialised = false;
currentScreen_t	activeScreen;
char weatherType[20] = "Cloudy";

char* days[7] =
{
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thur",
    "Fri",
    "Sat"
};

char* months[13] =
    {
        "Invalid Month", // Placeholder for index 0
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sepr",
        "Oct",
        "Nov",
        "Dec"
    };


// Define the screen objects
lv_obj_t* temperatureScreen = NULL;
lv_obj_t* navScreen = NULL;
lv_obj_t* homeScreen = NULL;
lv_obj_t* lightFanScreen = NULL;
lv_obj_t* settingsScreen = NULL;
lv_obj_t* wifiTurningOnScreen = NULL;
lv_obj_t* wifiLoadingScreen = NULL;
lv_obj_t* wifiConnectScreen = NULL;
lv_obj_t * wifiConnectingMessageBox = NULL;
lv_obj_t* wifiConnectingFailedMessageBox = NULL;
lv_obj_t* wifiConnectingSuccessfullMessageBox = NULL;
lv_obj_t* wifiErrorMessageBox = NULL;
lv_obj_t* calendarScreen = NULL;
lv_obj_t* timeScreen = NULL;
lv_obj_t* bootScreen = NULL;

//Boot Screen Objects
lv_obj_t* smartHomeLabel;
lv_obj_t* bootSpinner = NULL;
lv_obj_t* bootLabel = NULL;

// Define the temperature screen objects
lv_obj_t* tempControlLabel = NULL;
lv_obj_t* temperautreArc = NULL;
lv_obj_t* ui_Panel1 = NULL;
lv_obj_t* ui_Panel2 = NULL;
lv_obj_t* temperatureLabel = NULL;
lv_obj_t* celciusLabel = NULL;
lv_obj_t* coolingButton = NULL;
lv_obj_t* coolingButtonLabel = NULL;
lv_obj_t* heatingButton = NULL;
lv_obj_t* heatingButtonLabel = NULL;
lv_obj_t* temperatureMenuButton = NULL;
lv_obj_t* noWifiTemperatureScreen = NULL;

// Define the nav screen objects
lv_obj_t* homeButton = NULL;
lv_obj_t* homeButtonLabel = NULL;
lv_obj_t* temperatureButton = NULL;
lv_obj_t* temperatureButtonLabel = NULL;
lv_obj_t* lightFanButton = NULL;
lv_obj_t* lightFanButtonLabel = NULL;
lv_obj_t* settingsButton = NULL;
lv_obj_t* settingsButtonLabel = NULL;

//Home Screen Objects
lv_obj_t* homeScreenLabel = NULL;
lv_obj_t* timeDatePanel = NULL;
lv_obj_t* timeLabel = NULL;
lv_obj_t* dateLabel = NULL;
lv_obj_t* temperatuePanel = NULL;
lv_obj_t* homeTemperatureLabel = NULL;
lv_obj_t* roomTemperatureLabel = NULL;
lv_obj_t* homeCelciusLabel = NULL;
lv_obj_t* weatherPanel = NULL;
lv_obj_t* weatherLabel = NULL;
lv_obj_t* weatherTemperatureLabel = NULL;
lv_obj_t* weatherCelciusLabel = NULL;
lv_obj_t* weatherImage = NULL;
lv_obj_t* co2Panel = NULL;
lv_obj_t* co2Label = NULL;
lv_obj_t* co2PercentLabel = NULL;
lv_obj_t* homeMenuButton = NULL;
lv_obj_t* noWifiHomeScreen = NULL;

//Light & Fan Screen
lv_obj_t* lightFanMenuButton = NULL;
lv_obj_t* lightPanel1 = NULL;
lv_obj_t* lightLabel1 = NULL;
lv_obj_t* lightSwitch1 = NULL;
lv_obj_t* lightImage1 = NULL;
lv_obj_t* lightPanel2 = NULL;
lv_obj_t* lightLabel2 = NULL;
lv_obj_t* lightSwitch2 = NULL;
lv_obj_t* lightImage2 = NULL;
lv_obj_t* fanPanel1 = NULL;
lv_obj_t* fanLabel1 = NULL;
lv_obj_t* fanSwitch1 = NULL;
lv_obj_t* fanImage1 = NULL;
lv_obj_t* fanPanel2 = NULL;
lv_obj_t* fanLabel2 = NULL;
lv_obj_t* fanSwitch2 = NULL;
lv_obj_t* fanImage2 = NULL;
lv_obj_t* noWifiLightFanScreen = NULL;

//Settings Screen
lv_obj_t* settingsMenuButton = NULL;
lv_obj_t* wifiButton = NULL;
lv_obj_t* wifiButtonLabel = NULL;
lv_obj_t* dateTimeButton = NULL;
lv_obj_t* dateTimeButtonLabel = NULL;

//Wifi Screen
lv_obj_t* wifiMenuButton = NULL;
lv_obj_t* wifiScreen = NULL;
lv_obj_t* wifiScreenPanel = NULL;
lv_obj_t* connectDetailsLabel = NULL;
lv_obj_t* nameLabel = NULL;
lv_obj_t* nameLabelAnswer = NULL;
lv_obj_t* ipAddressLabel = NULL;
lv_obj_t* ipAddressLabelAnswer = NULL;
lv_obj_t* securityLabel = NULL;
lv_obj_t* securityLabelAnswer = NULL;
lv_obj_t* conectWifiButton = NULL;
lv_obj_t* conectWifiButtonLabel = NULL;
lv_obj_t* disconectWifiButton = NULL;
lv_obj_t* disconectWifiButtonLabel = NULL;

//Wifi turning On Screen
lv_obj_t* wifiTurningOnMenuButton = NULL;
lv_obj_t* wifiTurningOnLoadingLabel = NULL;
lv_obj_t* wifiTurningOnLoadingSpinner = NULL;

//Wifi Loading Screen
lv_obj_t* wifiLoadingMenuButton = NULL;
lv_obj_t* wifiLoadingLabel = NULL;
lv_obj_t* wifiLoadingSpinner = NULL;

//Wifi Connecting Message Box
lv_obj_t* wifiConnectingLabel = NULL;
lv_obj_t* wifiConnectingSpinner = NULL;

//Wifi Connecting Failed Message Box
lv_obj_t* wifiConnectingFailedLabel = NULL;

//Wifi Connecting Successful Message Box
lv_obj_t* wifiConnectingSuccessfullLabel = NULL;

//Wifi Error Message; Box
lv_obj_t* wifiErrorLabel = NULL;

//Wifi Connect Screen
lv_obj_t* wifiConnectMenuButton = NULL;
lv_obj_t* wifi1Panel = NULL;
lv_obj_t* wifi1PanelLabel = NULL;
lv_obj_t* wifi1PanelButton;
lv_obj_t* wifi1PanelButtonLabel;
lv_obj_t* wifi2Panel = NULL;
lv_obj_t* wifi2PanelLabel = NULL;
lv_obj_t* wifi2PanelButton;
lv_obj_t* wifi2PanelButtonLabel;
lv_obj_t* wifi3Panel = NULL;
lv_obj_t* wifi3PanelLabel = NULL;
lv_obj_t* wifi3PanelButton;
lv_obj_t* wifi3PanelButtonLabel;
lv_obj_t* wifi4Panel = NULL;
lv_obj_t* wifi4PanelLabel = NULL;
lv_obj_t* wifi4PanelButton;
lv_obj_t* wifi4PanelButtonLabel;
lv_obj_t* wifi5Panel = NULL;
lv_obj_t* wifi5PanelLabel = NULL;
lv_obj_t* wifi5PanelButton;
lv_obj_t* wifi5PanelButtonLabel;
lv_obj_t* wifi6Panel = NULL;
lv_obj_t* wifi6PanelLabel = NULL;
lv_obj_t* wifi6PanelButton = NULL;
lv_obj_t* wifi6PanelButtonLabel = NULL;
lv_obj_t* wifi7Panel = NULL;
lv_obj_t* wifi7PanelLabel = NULL;
lv_obj_t* wifi7PanelButton = NULL;
lv_obj_t* wifi7PanelButtonLabel = NULL;
lv_obj_t* wifi8Panel = NULL;
lv_obj_t* wifi8PanelLabel = NULL;
lv_obj_t* wifi8PanelButton = NULL;
lv_obj_t* wifi8PanelButtonLabel = NULL;
lv_obj_t* wifi9Panel = NULL;
lv_obj_t* wifi9PanelLabel = NULL;
lv_obj_t* wifi9PanelButton = NULL;
lv_obj_t* wifi9PanelButtonLabel = NULL;
lv_obj_t* wifi10Panel = NULL;
lv_obj_t* wifi10PanelLabel = NULL;
lv_obj_t* wifi10PanelButton = NULL;
lv_obj_t* wifi10PanelButtonLabel = NULL;

//Wifi Password Screen
lv_obj_t* wifiPasswordScreen = NULL;
lv_obj_t* wifiPasswordScreenNameLabel = NULL;
lv_obj_t* wifiPasswordScreenNameAnswer = NULL;
lv_obj_t* wifiPasswordScreenPasswordLabel = NULL;
lv_obj_t* wifiPasswordTextArea = NULL;
lv_obj_t* ui_Keyboard1 = NULL;
lv_obj_t* closeImageButton = NULL;

//Calendar Screen
lv_obj_t* calendar = NULL;
lv_obj_t* calendarTickButton = NULL;
lv_obj_t* calendarCrossButton = NULL;
lv_obj_t* calendarScreenLabel = NULL;

//Time Screen
lv_obj_t* timeScreenLabel = NULL;
lv_obj_t* timeScreenCrossButton = NULL;
lv_obj_t* timeScreenTickButton = NULL;
lv_obj_t* hourLabel = NULL;
lv_obj_t* hourRoller = NULL;
lv_obj_t* minutesLabel = NULL;
lv_obj_t* minutesRoller = NULL;
lv_obj_t* secondsLabel = NULL;
lv_obj_t* secondsRoller = NULL;
lv_obj_t* amPMLabel = NULL;
lv_obj_t* amPMRoller = NULL;

/**************FUNCTIONS*************************/
uint8_t stringToDayOfWeek(char *day)
{
	for(int i=0; i<7; i++)
	{
		if(!(strcmp(day,days[i])))
		{
			return i;
		}
	}
	return 0;
}

uint8_t stringToMonth(char *month)
{
	for(int i=0; i<13; i++)
	{
		if(!(strcmp(month,months[i])))
		{
			return i;
		}
	}
	return 0;
}

char* dayOfWeekToString(day_t day)
{
    if(day >= SUNDAY && day <= SATURDAY)
    {
        return days[day];
    }
    else
    {
        return "Invalid Day";
    }
}

char* monthToString(month_t month)
{
    if(month >= JANUARY && month <= DECEMBER)
    {
        return months[month];
    }
    else
    {
        return "Invalid Month";
    }
}

/***************LVGL CALLBACKS*****************************/
//Temperature Screen Callbacks
void temperatureArcCallback(lv_event_t* e)
{
	temperature = lv_arc_get_value(temperautreArc);
	lv_label_set_text_fmt(temperatureLabel, "%d", temperature);
}

void coolingButtonCallback(lv_event_t* e)
{
	lv_event_code_t coolingCode = lv_event_get_code(e);
	if (coolingCode == LV_EVENT_VALUE_CHANGED) {
		if (heatingEnabled)
		{
			lv_obj_clear_state(heatingButton, LV_STATE_CHECKED);
			heatingEnabled = false;
			coolingEnabled = true;
		}
		else
		{
			if(coolingEnabled)
			{
				coolingEnabled = false;
			}
			else
			{
				coolingEnabled = true;
			}
		}
	}
}

void heatingButtonCallback(lv_event_t* e)
{
	lv_event_code_t heatingCode = lv_event_get_code(e);
	if (heatingCode == LV_EVENT_VALUE_CHANGED) {
		if (coolingEnabled)
		{
			lv_obj_clear_state(coolingButton, LV_STATE_CHECKED);
			heatingEnabled = true;
			coolingEnabled = false;
		}
		else
		{
			if(heatingEnabled)
			{
				heatingEnabled = false;
			}
			else
			{
				heatingEnabled = true;
			}
		}
	}
}

void menuButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createNavScreen();
	}
}

void temperatureButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createTemperatureScreen();
	}
}

void homeButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createhomeScreen();
	}
}

void lightFanButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createLightFanScreen();
	}
}

void settingsButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createSettingsScreen();
	}
}

void wifiButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		if(espInitialised == false)
		{
			lv_obj_del(lv_disp_get_scr_act(NULL));
			createWifiTurningOnScreen();
		}
		else
		{
			lv_obj_del(lv_disp_get_scr_act(NULL));
			createWifiScreen();
		}

	}
}

void dateTimeButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		creatCalendarScreen();
	}
}

void connectWifiButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createWifiLoadingScreen();
	}
}

void disconectWifiButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		if(espDisconnect() == HAL_OK)
		{
			strcpy(SSID,"Not Connected");
			strcpy(IPADDRESS,"Not Connected");
			lv_label_set_text_fmt(nameLabelAnswer, "%s",SSID);
			lv_label_set_text_fmt(ipAddressLabelAnswer, "%s",IPADDRESS);
			wifiConnected = false;
		}
	}
}

void wifiConnectCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t* user_data = lv_event_get_user_data(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createWifiPasswordScreen();
		if(user_data->class_p == wifi1PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[0].ssid);
		}
		else if(user_data->class_p == wifi2PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[1].ssid);
		}
		else if(user_data->class_p == wifi3PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[2].ssid);
		}
		else if(user_data->class_p == wifi4PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[3].ssid);
		}
		else if(user_data->class_p == wifi5PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[4].ssid);
		}
		else if(user_data->class_p == wifi6PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[5].ssid);
		}
		else if(user_data->class_p == wifi7PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[6].ssid);
		}
		else if(user_data->class_p == wifi8PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[7].ssid);
		}
		else if(user_data->class_p == wifi9PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[8].ssid);
		}
		else if(user_data->class_p == wifi10PanelButton)
		{
			lv_label_set_text_fmt(wifiPasswordScreenNameAnswer, "%s",ssidList[9].ssid);
		}
	}
}

void wifiPasswordKeyboardEvent(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_READY)
	{
		strcpy(PASSWORD,lv_textarea_get_text(wifiPasswordTextArea));
		strcpy(SSID,lv_label_get_text(wifiPasswordScreenNameAnswer));
		createWifiConnectingMessageBox();

	}
}

void closeButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createWifiConnectScreen();
	}
}

void calendarCallback(lv_event_t* e)
{
    lv_calendar_date_t clicked_date;

	// Get the date that was clicked
	if (lv_calendar_get_pressed_date(calendar, &clicked_date))
	{
		lv_calendar_date_t empty_dates[1] = {0};
		// Clear any existing highlights
		lv_calendar_set_highlighted_dates(calendar, empty_dates, 0);

		// Highlight the clicked date
		lv_calendar_set_highlighted_dates(calendar, &clicked_date, 1);
		gDate.Date = clicked_date.day;
		gDate.Month = clicked_date.month;
		gDate.Year = (clicked_date.year % 100);
		gDate.WeekDay = get_day_of_week(clicked_date.year,clicked_date.month,clicked_date.day);
	}
}

void calendarTickButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		creatTimeScreen();
	}
}

void calendarCrossButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createSettingsScreen();
	}
}

void timeScreenTickButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		createhomeScreen();
	}
}

void timeScreenCrossButtonCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_obj_del(lv_disp_get_scr_act(NULL));
		creatCalendarScreen();
	}
}

void timeScreenCallback(lv_event_t* e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char temp[10] = {0};
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		lv_roller_get_selected_str(hourRoller,temp,10);
		gTime.Hours = atoi(temp);

		lv_roller_get_selected_str(minutesRoller,temp,10);
		gTime.Minutes = atoi(temp);

		lv_roller_get_selected_str(secondsRoller,temp,10);
		gTime.Seconds = atoi(temp);

		gTime.TimeFormat = lv_roller_get_selected(amPMRoller);
	}
}

void setWeatherIcon(void)
{
	if(!(strcmp(weatherIcon,"01d")))
	{
		lv_img_set_src(weatherImage, &PNG01d);
	}
	else if(!(strcmp(weatherIcon,"01n")))
	{
		lv_img_set_src(weatherImage, &PNG01n);
	}
	else if(!(strcmp(weatherIcon,"02d")))
	{
		lv_img_set_src(weatherImage, &PNG02d);
	}
	else if(!(strcmp(weatherIcon,"02n")))
	{
		lv_img_set_src(weatherImage, &PNG02n);
	}
	else if(!(strcmp(weatherIcon,"03d")))
	{
		lv_img_set_src(weatherImage, &PNG03dn);
	}
	else if(!(strcmp(weatherIcon,"03n")))
	{
		lv_img_set_src(weatherImage, &PNG03dn);
	}
	else if(!(strcmp(weatherIcon,"04d")))
	{
		lv_img_set_src(weatherImage, &PNG04dn);
	}
	else if(!(strcmp(weatherIcon,"04n")))
	{
		lv_img_set_src(weatherImage, &PNG04dn);
	}
	else if(!(strcmp(weatherIcon,"09d")))
	{
		lv_img_set_src(weatherImage, &PNG09dn);
	}
	else if(!(strcmp(weatherIcon,"09n")))
	{
		lv_img_set_src(weatherImage, &PNG09dn);
	}
	else if(!(strcmp(weatherIcon,"10d")))
	{
		lv_img_set_src(weatherImage, &PNG10d);
	}
	else if(!(strcmp(weatherIcon,"10n")))
	{
		lv_img_set_src(weatherImage, &PNG10n);
	}
	else if(!(strcmp(weatherIcon,"11d")))
	{
		lv_img_set_src(weatherImage, &PNG11dn);
	}
	else if(!(strcmp(weatherIcon,"11n")))
	{
		lv_img_set_src(weatherImage, &PNG11dn);
	}
	else if(!(strcmp(weatherIcon,"13d")))
	{
		lv_img_set_src(weatherImage, &PNG13dn);
	}
	else if(!(strcmp(weatherIcon,"13n")))
	{
		lv_img_set_src(weatherImage, &PNG13dn);
	}
	else if(!(strcmp(weatherIcon,"50d")))
	{
		lv_img_set_src(weatherImage, &PNG50dn);
	}
	else if(!(strcmp(weatherIcon,"50n")))
	{
		lv_img_set_src(weatherImage, &PNG50dn);
	}
}

/*****************CREATE SCREEN FUNCTIONS***********************/
void createTemperatureScreen(void)
{
	activeScreen = TEMPERATURESCREEN;

	temperatureScreen = lv_obj_create(NULL);
	lv_scr_load(temperatureScreen);

	lv_obj_set_style_bg_color(temperatureScreen, lv_color_hex(0xEAEDF2), LV_PART_MAIN | LV_STATE_DEFAULT);

	if(wifiConnected == false)
	{
		noWifiTemperatureScreen = lv_img_create(temperatureScreen);
		lv_img_set_src(noWifiTemperatureScreen, &noWifiPNG);
		lv_obj_set_width(noWifiTemperatureScreen, 30);
		lv_obj_set_height(noWifiTemperatureScreen, 30);
		lv_obj_set_x(noWifiTemperatureScreen, -10);
		lv_obj_set_y(noWifiTemperatureScreen, 5);
		lv_obj_set_align(noWifiTemperatureScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}
	else if(wifiConnected == true)
	{
		noWifiTemperatureScreen = lv_img_create(temperatureScreen);
		lv_img_set_src(noWifiTemperatureScreen, &wifiPNG);
		lv_obj_set_width(noWifiTemperatureScreen, 30);
		lv_obj_set_height(noWifiTemperatureScreen, 30);
		lv_obj_set_x(noWifiTemperatureScreen, -10);
		lv_obj_set_y(noWifiTemperatureScreen, 5);
		lv_obj_set_align(noWifiTemperatureScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}


	tempControlLabel = lv_label_create(temperatureScreen);
	lv_obj_set_width(tempControlLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(tempControlLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(tempControlLabel, 0);
	lv_obj_set_y(tempControlLabel, 5);
	lv_obj_set_align(tempControlLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(tempControlLabel, "Temperature Control");
	lv_obj_set_style_text_color(tempControlLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(tempControlLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(tempControlLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	temperatureMenuButton = lv_imgbtn_create(temperatureScreen);
	lv_imgbtn_set_src(temperatureMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(temperatureMenuButton, 30);
	lv_obj_set_width(temperatureMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(temperatureMenuButton, 8);
	lv_obj_set_y(temperatureMenuButton, 8);

	temperautreArc = lv_arc_create(temperatureScreen);
	lv_obj_set_width(temperautreArc, 180);
	lv_obj_set_height(temperautreArc, 180);
	lv_obj_set_align(temperautreArc, LV_ALIGN_CENTER);
	lv_arc_set_range(temperautreArc, 16, 35);
	lv_arc_set_value(temperautreArc, temperature);
	lv_arc_set_bg_angles(temperautreArc, 150, 30);
	lv_obj_set_style_pad_left(temperautreArc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(temperautreArc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(temperautreArc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(temperautreArc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(temperautreArc, lv_color_hex(0xA2A9B8), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(temperautreArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(temperautreArc, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_arc_color(temperautreArc, lv_color_hex(0x7F85F9), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(temperautreArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(temperautreArc, lv_color_hex(0xF9B23D), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(temperautreArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(temperautreArc, lv_color_hex(0x7F85F9), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(temperautreArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(temperautreArc, 5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(temperautreArc, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(temperautreArc, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(temperautreArc, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(temperautreArc, 3, LV_PART_KNOB | LV_STATE_DEFAULT);

	ui_Panel1 = lv_obj_create(temperatureScreen);
	lv_obj_set_width(ui_Panel1, 140);
	lv_obj_set_height(ui_Panel1, 140);
	lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_scrollbar_mode(ui_Panel1, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(ui_Panel1, 350, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Panel1, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_Panel2 = lv_obj_create(temperatureScreen);
	lv_obj_set_width(ui_Panel2, 120);
	lv_obj_set_height(ui_Panel2, 120);
	lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_scrollbar_mode(ui_Panel2, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(ui_Panel2, 350, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	temperatureLabel = lv_label_create(temperatureScreen);
	lv_obj_set_width(temperatureLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(temperatureLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(temperatureLabel, 0);
	lv_obj_set_y(temperatureLabel, -10);
	lv_obj_set_align(temperatureLabel, LV_ALIGN_CENTER);
	lv_label_set_text_fmt(temperatureLabel, "%d", temperature);
	lv_obj_clear_flag(temperatureLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(temperatureLabel, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(temperatureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(temperatureLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

	celciusLabel = lv_label_create(temperatureScreen);
	lv_obj_set_width(celciusLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(celciusLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(celciusLabel, 0);
	lv_obj_set_y(celciusLabel, 15);
	lv_obj_set_align(celciusLabel, LV_ALIGN_CENTER);
	lv_label_set_text(celciusLabel, "°Celcius");
	lv_obj_clear_flag(celciusLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(celciusLabel, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(celciusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(celciusLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	coolingButton = lv_btn_create(temperatureScreen);
	lv_obj_set_width(coolingButton, 100);
	lv_obj_set_height(coolingButton, 50);
	lv_obj_set_x(coolingButton, 8);
	lv_obj_set_y(coolingButton, -8);
	lv_obj_set_align(coolingButton, LV_ALIGN_BOTTOM_LEFT);
	lv_obj_add_flag(coolingButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags
	lv_obj_clear_flag(coolingButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
		LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_bg_color(coolingButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(coolingButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(coolingButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(coolingButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(coolingButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(coolingButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(coolingButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(coolingButton, 255, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
	if (coolingEnabled)
	{
		lv_obj_add_state(coolingButton, LV_STATE_CHECKED);

	}
	else
	{
		lv_obj_clear_state(coolingButton, LV_STATE_CHECKED);
	}

	coolingButtonLabel = lv_label_create(coolingButton);
	lv_obj_set_width(coolingButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(coolingButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(coolingButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(coolingButtonLabel, "Cooling");
	lv_obj_clear_flag(coolingButtonLabel, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(coolingButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(coolingButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(coolingButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(coolingButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(coolingButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(coolingButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(coolingButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	heatingButton = lv_btn_create(temperatureScreen);
	lv_obj_set_width(heatingButton, 100);
	lv_obj_set_height(heatingButton, 50);
	lv_obj_set_x(heatingButton, -8);
	lv_obj_set_y(heatingButton, -8);
	lv_obj_set_align(heatingButton, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_add_flag(heatingButton, LV_OBJ_FLAG_CHECKABLE);     /// Flags
	lv_obj_clear_flag(heatingButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
		LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_bg_color(heatingButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(heatingButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(heatingButton, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(heatingButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(heatingButton, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(heatingButton, 255, LV_PART_MAIN | LV_STATE_PRESSED);
	if (heatingEnabled)
	{
		lv_obj_add_state(heatingButton, LV_STATE_CHECKED);
	}
	else
	{
		lv_obj_clear_state(heatingButton, LV_STATE_CHECKED);
	}

	heatingButtonLabel = lv_label_create(heatingButton);
	lv_obj_set_width(heatingButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(heatingButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(heatingButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(heatingButtonLabel, "Heating");
	lv_obj_clear_flag(heatingButtonLabel, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(heatingButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(heatingButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(heatingButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(heatingButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(heatingButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(heatingButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(heatingButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	//Temperature Arc Event
	lv_obj_add_event_cb(temperautreArc, temperatureArcCallback, LV_EVENT_VALUE_CHANGED, NULL);

	//Cooling Button Event
	lv_obj_add_event_cb(coolingButton, coolingButtonCallback, LV_EVENT_ALL, NULL);

	//Heating Button Event
	lv_obj_add_event_cb(heatingButton, heatingButtonCallback, LV_EVENT_ALL, NULL);

	//Menu Button Event
	lv_obj_add_event_cb(temperatureMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);
}


void createNavScreen(void)
{
	activeScreen = NAVSCREEN;

	navScreen = lv_obj_create(NULL);
	lv_scr_load(navScreen);

	lv_obj_set_style_bg_color(navScreen, lv_color_hex(0xEAEDF2), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(navScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	homeButton = lv_btn_create(navScreen);
	lv_obj_set_width(homeButton, 200);
	lv_obj_set_height(homeButton, 40);
	lv_obj_set_x(homeButton, 0);
	lv_obj_set_y(homeButton, 15);
	lv_obj_set_align(homeButton, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(homeButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(homeButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(homeButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(homeButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(homeButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	homeButtonLabel = lv_label_create(homeButton);
	lv_obj_set_width(homeButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(homeButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(homeButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(homeButtonLabel, "Home");
	lv_obj_clear_flag(homeButtonLabel,
		LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
		LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(homeButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(homeButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(homeButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(homeButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(homeButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(homeButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(homeButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	temperatureButton = lv_btn_create(navScreen);
	lv_obj_set_width(temperatureButton, 200);
	lv_obj_set_height(temperatureButton, 40);
	lv_obj_set_x(temperatureButton, 0);
	lv_obj_set_y(temperatureButton, 70);
	lv_obj_set_align(temperatureButton, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(temperatureButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(temperatureButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(temperatureButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(temperatureButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(temperatureButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	temperatureButtonLabel = lv_label_create(temperatureButton);
	lv_obj_set_width(temperatureButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(temperatureButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(temperatureButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(temperatureButtonLabel, "Temperature");
	lv_obj_clear_flag(temperatureButtonLabel,
		LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
		LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(temperatureButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(temperatureButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(temperatureButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(temperatureButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(temperatureButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(temperatureButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(temperatureButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	lightFanButton = lv_btn_create(navScreen);
	lv_obj_set_width(lightFanButton, 200);
	lv_obj_set_height(lightFanButton, 40);
	lv_obj_set_x(lightFanButton, 0);
	lv_obj_set_y(lightFanButton, 125);
	lv_obj_set_align(lightFanButton, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(lightFanButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(lightFanButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(lightFanButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(lightFanButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(lightFanButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	lightFanButtonLabel = lv_label_create(lightFanButton);
	lv_obj_set_width(lightFanButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(lightFanButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(lightFanButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(lightFanButtonLabel, " Lights & Fan");
	lv_obj_clear_flag(lightFanButtonLabel, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(lightFanButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(lightFanButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(lightFanButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(lightFanButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(lightFanButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(lightFanButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(lightFanButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	settingsButton = lv_btn_create(navScreen);
	lv_obj_set_width(settingsButton, 200);
	lv_obj_set_height(settingsButton, 40);
	lv_obj_set_x(settingsButton, 0);
	lv_obj_set_y(settingsButton, -20);
	lv_obj_set_align(settingsButton, LV_ALIGN_BOTTOM_MID);
	lv_obj_add_flag(settingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(settingsButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(settingsButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(settingsButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(settingsButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	settingsButtonLabel = lv_label_create(settingsButton);
	lv_obj_set_width(settingsButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(settingsButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(settingsButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(settingsButtonLabel, "Settings");
	lv_obj_clear_flag(settingsButtonLabel, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(settingsButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(settingsButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(settingsButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(settingsButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(settingsButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(settingsButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(settingsButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	//Temperature Button Event
	lv_obj_add_event_cb(temperatureButton, temperatureButtonCallback, LV_EVENT_ALL, NULL);

	//Home Button Event
	lv_obj_add_event_cb(homeButton, homeButtonCallback, LV_EVENT_ALL, NULL);

	//Fan & Light Button Event
	lv_obj_add_event_cb(lightFanButton, lightFanButtonCallback, LV_EVENT_ALL, NULL);

	//Fan & Light Button Event
	lv_obj_add_event_cb(settingsButton, settingsButtonCallback, LV_EVENT_ALL, NULL);
}


void createhomeScreen(void)
{
	activeScreen = HOMESCREEN;

	homeScreen = lv_obj_create(NULL);
	lv_scr_load(homeScreen);

	if(wifiConnected == false)
	{
		noWifiHomeScreen = lv_img_create(homeScreen);
		lv_img_set_src(noWifiHomeScreen, &noWifiPNG);
		lv_obj_set_width(noWifiHomeScreen, 30);
		lv_obj_set_height(noWifiHomeScreen, 30);
		lv_obj_set_x(noWifiHomeScreen, -10);
		lv_obj_set_y(noWifiHomeScreen, 5);
		lv_obj_set_align(noWifiHomeScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiHomeScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiHomeScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}
	else if(wifiConnected == true)
	{
		noWifiTemperatureScreen = lv_img_create(temperatureScreen);
		lv_img_set_src(noWifiTemperatureScreen, &wifiPNG);
		lv_obj_set_width(noWifiTemperatureScreen, 30);
		lv_obj_set_height(noWifiTemperatureScreen, 30);
		lv_obj_set_x(noWifiTemperatureScreen, -10);
		lv_obj_set_y(noWifiTemperatureScreen, 5);
		lv_obj_set_align(noWifiTemperatureScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}

	homeScreenLabel = lv_label_create(homeScreen);
	lv_obj_set_width(homeScreenLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(homeScreenLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(homeScreenLabel, 0);
	lv_obj_set_y(homeScreenLabel, 15);
	lv_obj_set_align(homeScreenLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(homeScreenLabel, "SMART HOME");
	lv_obj_set_style_text_color(homeScreenLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(homeScreenLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(homeScreenLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	homeMenuButton = lv_imgbtn_create(homeScreen);
	lv_imgbtn_set_src(homeMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(homeMenuButton, 30);
	lv_obj_set_width(homeMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(homeMenuButton, 10);
	lv_obj_set_y(homeMenuButton, 8);
	lv_obj_clear_flag(homeMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
		LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	timeDatePanel = lv_obj_create(homeScreen);
	lv_obj_set_width(timeDatePanel, 145);
	lv_obj_set_height(timeDatePanel, 70);
	lv_obj_set_x(timeDatePanel, 10);
	lv_obj_set_y(timeDatePanel, 45);
	lv_obj_clear_flag(timeDatePanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_bg_color(timeDatePanel, lv_color_hex(0xEAEDF2), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(timeDatePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	timeLabel = lv_label_create(timeDatePanel);
	lv_obj_set_width(timeLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(timeLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(timeLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text_fmt(timeLabel, "%s",timeArray);
	lv_obj_set_style_text_color(timeLabel, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(timeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(timeLabel, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

	dateLabel = lv_label_create(timeDatePanel);
	lv_obj_set_width(dateLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(dateLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(dateLabel, 0);
	lv_obj_set_y(dateLabel, 15);
	lv_obj_set_align(dateLabel, LV_ALIGN_CENTER);
	lv_label_set_text_fmt(dateLabel, "%s",dateArray);
	lv_obj_set_style_text_color(dateLabel, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(dateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	temperatuePanel = lv_obj_create(homeScreen);
	lv_obj_set_width(temperatuePanel, 145);
	lv_obj_set_height(temperatuePanel, 100);
	lv_obj_set_x(temperatuePanel, -10);
	lv_obj_set_y(temperatuePanel, 45);
	lv_obj_set_align(temperatuePanel, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(temperatuePanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_bg_color(temperatuePanel, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(temperatuePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	homeTemperatureLabel = lv_label_create(temperatuePanel);
	lv_obj_set_width(homeTemperatureLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(homeTemperatureLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(homeTemperatureLabel, 0);
	lv_obj_set_y(homeTemperatureLabel, -5);
	lv_obj_set_align(homeTemperatureLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(homeTemperatureLabel, "Temperature");
	lv_obj_set_style_text_color(homeTemperatureLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(homeTemperatureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(homeTemperatureLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	roomTemperatureLabel = lv_label_create(temperatuePanel);
	lv_obj_set_width(roomTemperatureLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(roomTemperatureLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(roomTemperatureLabel, 0);
	lv_obj_set_y(roomTemperatureLabel, 5);
	lv_obj_set_align(roomTemperatureLabel, LV_ALIGN_CENTER);
	lv_label_set_text_fmt(roomTemperatureLabel, "%d", roomTemperature);
	lv_obj_clear_flag(roomTemperatureLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(roomTemperatureLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(roomTemperatureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(roomTemperatureLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

	homeCelciusLabel = lv_label_create(temperatuePanel);
	lv_obj_set_width(homeCelciusLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(homeCelciusLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(homeCelciusLabel, 0);
	lv_obj_set_y(homeCelciusLabel, 30);
	lv_obj_set_align(homeCelciusLabel, LV_ALIGN_CENTER);
	lv_label_set_text(homeCelciusLabel, "°Celcius");
	lv_obj_clear_flag(homeCelciusLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(homeCelciusLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(homeCelciusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(homeCelciusLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	weatherPanel = lv_obj_create(homeScreen);
	lv_obj_set_style_bg_color(weatherPanel, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(weatherPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_width(weatherPanel, 145);
	lv_obj_set_height(weatherPanel, 100);
	lv_obj_set_x(weatherPanel, 10);
	lv_obj_set_y(weatherPanel, -15);
	lv_obj_set_align(weatherPanel, LV_ALIGN_BOTTOM_LEFT);
	lv_obj_clear_flag(weatherPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	weatherLabel = lv_label_create(weatherPanel);
	lv_obj_set_width(weatherLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(weatherLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(weatherLabel, 0);
	lv_obj_set_y(weatherLabel, -5);
	lv_obj_set_align(weatherLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(weatherLabel, "Weather");
	lv_obj_set_style_text_color(weatherLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(weatherLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(weatherLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	weatherTemperatureLabel = lv_label_create(weatherPanel);
	lv_obj_set_width(weatherTemperatureLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(weatherTemperatureLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(weatherTemperatureLabel, 0);
	lv_obj_set_y(weatherTemperatureLabel, 5);
	lv_obj_set_align(weatherTemperatureLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(weatherTemperatureLabel, "%d°", weatherTemperature);
	lv_obj_clear_flag(weatherTemperatureLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(weatherTemperatureLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(weatherTemperatureLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(weatherTemperatureLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

	weatherCelciusLabel = lv_label_create(weatherPanel);
	lv_obj_set_width(weatherCelciusLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(weatherCelciusLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(weatherCelciusLabel, 0);
	lv_obj_set_y(weatherCelciusLabel, 30);
	lv_obj_set_align(weatherCelciusLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(weatherCelciusLabel, "%s", weatherType);
	lv_obj_clear_flag(weatherCelciusLabel,
		LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
		LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
		LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(weatherCelciusLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(weatherCelciusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(weatherCelciusLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	weatherImage = lv_img_create(weatherPanel);
	setWeatherIcon();
	lv_obj_set_width(weatherImage, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(weatherImage, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(weatherImage, 5);
	lv_obj_set_y(weatherImage,10);
	lv_obj_set_align(weatherImage, LV_ALIGN_RIGHT_MID);
	lv_obj_add_flag(weatherImage, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_clear_flag(weatherImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	co2Panel = lv_obj_create(homeScreen);
	lv_obj_set_width(co2Panel, 145);
	lv_obj_set_height(co2Panel, 70);
	lv_obj_set_x(co2Panel, -10);
	lv_obj_set_y(co2Panel, -15);
	lv_obj_set_align(co2Panel, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_clear_flag(co2Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
		LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
		LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_bg_color(co2Panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(co2Panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	co2Label = lv_label_create(co2Panel);
	lv_obj_set_width(co2Label, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(co2Label, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(co2Label, -5);
	lv_obj_set_y(co2Label, 0);
	lv_obj_set_align(co2Label, LV_ALIGN_LEFT_MID);
	lv_label_set_text(co2Label, "C02");
	lv_obj_set_style_text_color(co2Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(co2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(co2Label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

	co2PercentLabel = lv_label_create(co2Panel);
	lv_obj_set_width(co2PercentLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(co2PercentLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(co2PercentLabel, LV_ALIGN_RIGHT_MID);
	lv_label_set_text(co2PercentLabel, "10%");
	lv_obj_set_style_text_color(co2PercentLabel, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(co2PercentLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(co2PercentLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

	//Menu Button Event
	lv_obj_add_event_cb(homeMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);
}


void createLightFanScreen(void)
{
	activeScreen = LIGHTANDFANSCREEN;

	lightFanScreen = lv_obj_create(NULL);
	lv_scr_load(lightFanScreen);

	lv_obj_clear_flag(lightFanScreen, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);      /// Flags
	lv_obj_set_scrollbar_mode(lightFanScreen, LV_SCROLLBAR_MODE_ON);
	lv_obj_set_scroll_dir(lightFanScreen, LV_DIR_VER);
	lv_obj_set_style_pad_left(lightFanScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(lightFanScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(lightFanScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(lightFanScreen, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

	if(wifiConnected == false)
	{
		noWifiLightFanScreen = lv_img_create(lightFanScreen);
		lv_img_set_src(noWifiLightFanScreen, &noWifiPNG);
		lv_obj_set_width(noWifiLightFanScreen, 30);
		lv_obj_set_height(noWifiLightFanScreen, 30);
		lv_obj_set_x(noWifiLightFanScreen, -10);
		lv_obj_set_y(noWifiLightFanScreen, 5);
		lv_obj_set_align(noWifiLightFanScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiLightFanScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiLightFanScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}
	else if(wifiConnected == true)
	{
		noWifiTemperatureScreen = lv_img_create(temperatureScreen);
		lv_img_set_src(noWifiTemperatureScreen, &wifiPNG);
		lv_obj_set_width(noWifiTemperatureScreen, 30);
		lv_obj_set_height(noWifiTemperatureScreen, 30);
		lv_obj_set_x(noWifiTemperatureScreen, -10);
		lv_obj_set_y(noWifiTemperatureScreen, 5);
		lv_obj_set_align(noWifiTemperatureScreen, LV_ALIGN_TOP_RIGHT);
		lv_obj_add_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
		lv_obj_clear_flag(noWifiTemperatureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	}

	lightFanMenuButton = lv_imgbtn_create(lightFanScreen);
	lv_imgbtn_set_src(lightFanMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(lightFanMenuButton, 30);
	lv_obj_set_width(lightFanMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(lightFanMenuButton, 10);
	lv_obj_set_y(lightFanMenuButton, 8);
	lv_obj_clear_flag(lightFanMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	lightPanel1 = lv_obj_create(lightFanScreen);
	lv_obj_set_width(lightPanel1, 145);
	lv_obj_set_height(lightPanel1, 100);
	lv_obj_set_x(lightPanel1, 10);
	lv_obj_set_y(lightPanel1, 50);
	lv_obj_clear_flag(lightPanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	lightLabel1 = lv_label_create(lightPanel1);
	lv_obj_set_width(lightLabel1, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(lightLabel1, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(lightLabel1, 0);
	lv_obj_set_y(lightLabel1, 5);
	lv_obj_set_align(lightLabel1, LV_ALIGN_BOTTOM_LEFT);
	lv_label_set_text(lightLabel1, "Light 1");
	lv_obj_set_style_text_color(lightLabel1, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(lightLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(lightLabel1, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	lightSwitch1 = lv_switch_create(lightPanel1);
	lv_obj_set_width(lightSwitch1, 50);
	lv_obj_set_height(lightSwitch1, 25);
	lv_obj_set_align(lightSwitch1, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(lightSwitch1, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE);    /// Flags

	lv_obj_set_style_bg_color(lightSwitch1, lv_color_hex(0x7F85F9), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(lightSwitch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lightImage1 = lv_img_create(lightPanel1);
	lv_img_set_src(lightImage1, &bulbPNG);
	lv_obj_set_height(lightImage1, 50);
	lv_obj_set_width(lightImage1, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(lightImage1, 0);
	lv_obj_set_y(lightImage1, -5);
	lv_obj_add_flag(lightImage1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_clear_flag(lightImage1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	lightPanel2 = lv_obj_create(lightFanScreen);
	lv_obj_set_width(lightPanel2, 145);
	lv_obj_set_height(lightPanel2, 100);
	lv_obj_set_x(lightPanel2, -10);
	lv_obj_set_y(lightPanel2, 50);
	lv_obj_set_align(lightPanel2, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(lightPanel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	lightLabel2 = lv_label_create(lightPanel2);
	lv_obj_set_width(lightLabel2, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(lightLabel2, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(lightLabel2, 0);
	lv_obj_set_y(lightLabel2, 5);
	lv_obj_set_align(lightLabel2, LV_ALIGN_BOTTOM_LEFT);
	lv_label_set_text(lightLabel2, "Light 2");
	lv_obj_set_style_text_color(lightLabel2, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(lightLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(lightLabel2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	lightSwitch2 = lv_switch_create(lightPanel2);
	lv_obj_set_width(lightSwitch2, 50);
	lv_obj_set_height(lightSwitch2, 25);
	lv_obj_set_align(lightSwitch2, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(lightSwitch2, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE);    /// Flags

	lv_obj_set_style_bg_color(lightSwitch2, lv_color_hex(0x7F85F9), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(lightSwitch2, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lightImage2 = lv_img_create(lightPanel2);
	lv_img_set_src(lightImage2, &bulbPNG);
	lv_obj_set_height(lightImage2, 50);
	lv_obj_set_width(lightImage2, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(lightImage2, 0);
	lv_obj_set_y(lightImage2, -5);
	lv_obj_add_flag(lightImage2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_clear_flag(lightImage2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	fanPanel1 = lv_obj_create(lightFanScreen);
	lv_obj_set_width(fanPanel1, 145);
	lv_obj_set_height(fanPanel1, 100);
	lv_obj_set_x(fanPanel1, 10);
	lv_obj_set_y(fanPanel1, 30);
	lv_obj_set_align(fanPanel1, LV_ALIGN_BOTTOM_LEFT);
	lv_obj_clear_flag(fanPanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	fanLabel1 = lv_label_create(fanPanel1);
	lv_obj_set_width(fanLabel1, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(fanLabel1, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(fanLabel1, 0);
	lv_obj_set_y(fanLabel1, 5);
	lv_obj_set_align(fanLabel1, LV_ALIGN_BOTTOM_LEFT);
	lv_label_set_text(fanLabel1, "Fan 1");
	lv_obj_set_style_text_color(fanLabel1, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(fanLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(fanLabel1, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	fanSwitch1 = lv_switch_create(fanPanel1);
	lv_obj_set_width(fanSwitch1, 50);
	lv_obj_set_height(fanSwitch1, 25);
	lv_obj_set_align(fanSwitch1, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(fanSwitch1, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE);      /// Flags

	lv_obj_set_style_bg_color(fanSwitch1, lv_color_hex(0x7F85F9), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(fanSwitch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	fanImage1 = lv_img_create(fanPanel1);
	lv_img_set_src(fanImage1, &fanPNG);
	lv_obj_set_height(fanImage1, 50);
	lv_obj_set_width(fanImage1, LV_SIZE_CONTENT);   /// 1
	lv_obj_add_flag(fanImage1, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_clear_flag(fanImage1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	fanPanel2 = lv_obj_create(lightFanScreen);
	lv_obj_set_width(fanPanel2, 145);
	lv_obj_set_height(fanPanel2, 100);
	lv_obj_set_x(fanPanel2, -10);
	lv_obj_set_y(fanPanel2, 30);
	lv_obj_set_align(fanPanel2, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_clear_flag(fanPanel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	fanLabel2 = lv_label_create(fanPanel2);
	lv_obj_set_width(fanLabel2, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(fanLabel2, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(fanLabel2, 0);
	lv_obj_set_y(fanLabel2, 5);
	lv_obj_set_align(fanLabel2, LV_ALIGN_BOTTOM_LEFT);
	lv_label_set_text(fanLabel2, "Fan 2");
	lv_obj_set_style_text_color(fanLabel2, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(fanLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(fanLabel2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	fanSwitch2 = lv_switch_create(fanPanel2);
	lv_obj_set_width(fanSwitch2, 50);
	lv_obj_set_height(fanSwitch2, 25);
	lv_obj_set_align(fanSwitch2, LV_ALIGN_TOP_RIGHT);
	lv_obj_clear_flag(fanSwitch2, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE);      /// Flags

	lv_obj_set_style_bg_color(fanSwitch2, lv_color_hex(0x7F85F9), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(fanSwitch2, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	fanImage2 = lv_img_create(fanPanel2);
	lv_img_set_src(fanImage2, &fanPNG);
	lv_obj_set_height(fanImage2, 50);
	lv_obj_set_width(fanImage2, LV_SIZE_CONTENT);   /// 1
	lv_obj_add_flag(fanImage2, LV_OBJ_FLAG_CLICKABLE);     /// Flags
	lv_obj_clear_flag(fanImage2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	//Menu Button Event
	lv_obj_add_event_cb(lightFanMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);
}

void createSettingsScreen(void)
{
	activeScreen = SETTINGSCREEN;

	settingsScreen = lv_obj_create(NULL);
	lv_scr_load(settingsScreen);

	settingsMenuButton = lv_imgbtn_create(settingsScreen);
	lv_imgbtn_set_src(settingsMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(settingsMenuButton, 30);
	lv_obj_set_width(settingsMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(settingsMenuButton, 8);
	lv_obj_set_y(settingsMenuButton, 8);
	lv_obj_clear_flag(settingsMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	wifiButton = lv_btn_create(settingsScreen);
	lv_obj_set_width(wifiButton, 200);
	lv_obj_set_height(wifiButton, 40);
	lv_obj_set_x(wifiButton, 0);
	lv_obj_set_y(wifiButton, 15);
	lv_obj_set_align(wifiButton, LV_ALIGN_TOP_MID);
	lv_obj_add_flag(wifiButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
	lv_obj_clear_flag(wifiButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(wifiButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(wifiButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(wifiButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	wifiButtonLabel = lv_label_create(wifiButton);
	lv_obj_set_width(wifiButtonLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiButtonLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifiButtonLabel, LV_ALIGN_CENTER);
	lv_label_set_text(wifiButtonLabel, "WiFi");
	lv_obj_clear_flag(wifiButtonLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    dateTimeButton = lv_btn_create(settingsScreen);
    lv_obj_set_width(dateTimeButton, 200);
    lv_obj_set_height(dateTimeButton, 40);
    lv_obj_set_x(dateTimeButton, 0);
    lv_obj_set_y(dateTimeButton, 70);
    lv_obj_set_align(dateTimeButton, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(dateTimeButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(dateTimeButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(dateTimeButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(dateTimeButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(dateTimeButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    dateTimeButtonLabel = lv_label_create(dateTimeButton);
    lv_obj_set_width(dateTimeButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(dateTimeButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(dateTimeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(dateTimeButtonLabel, "Set Date & Time");
    lv_obj_clear_flag(dateTimeButtonLabel,
                      LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_color(dateTimeButtonLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(dateTimeButtonLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(dateTimeButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(dateTimeButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(dateTimeButtonLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(dateTimeButtonLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(dateTimeButtonLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	//Menu Button Event
	lv_obj_add_event_cb(settingsMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);

	//Wifi Button Event
	lv_obj_add_event_cb(wifiButton, wifiButtonCallback, LV_EVENT_ALL, NULL);

	//date Time Button Event
	lv_obj_add_event_cb(dateTimeButton, dateTimeButtonCallback, LV_EVENT_ALL, NULL);
}

void createWifiScreen(void)
{
	activeScreen = WIFISCREEN;

	espGetIP();
	espGetSSID(SSID);

	wifiScreen = lv_obj_create(NULL);
	lv_scr_load(wifiScreen);

	wifiMenuButton = lv_imgbtn_create(wifiScreen);
	lv_imgbtn_set_src(wifiMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(wifiMenuButton, 30);
	lv_obj_set_width(wifiMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(wifiMenuButton, 10);
	lv_obj_set_y(wifiMenuButton, 8);
	lv_obj_clear_flag(wifiMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

    connectDetailsLabel = lv_label_create(wifiScreen);
    lv_obj_set_width(connectDetailsLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(connectDetailsLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(connectDetailsLabel, 0);
    lv_obj_set_y(connectDetailsLabel, 10);
    lv_obj_set_align(connectDetailsLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(connectDetailsLabel, "Connection Details");
    lv_obj_set_style_text_color(connectDetailsLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(connectDetailsLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(connectDetailsLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifiScreenPanel = lv_obj_create(wifiScreen);
    lv_obj_set_width(wifiScreenPanel, 300);
    lv_obj_set_height(wifiScreenPanel, 100);
    lv_obj_set_x(wifiScreenPanel, 0);
    lv_obj_set_y(wifiScreenPanel, 45);
    lv_obj_set_align(wifiScreenPanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(wifiScreenPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    nameLabel = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(nameLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(nameLabel, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(nameLabel, "Name :");
    lv_obj_set_x(nameLabel, 0);
    lv_obj_set_y(nameLabel, 5);
    lv_obj_set_style_text_font(nameLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    nameLabelAnswer = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(nameLabelAnswer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(nameLabelAnswer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(nameLabelAnswer, 60);
    lv_obj_set_y(nameLabelAnswer, 5);
    lv_label_set_text_fmt(nameLabelAnswer, "%s",SSID);

    ipAddressLabel = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(ipAddressLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ipAddressLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ipAddressLabel, 0);
    lv_obj_set_y(ipAddressLabel, 30);
    lv_label_set_text(ipAddressLabel, "IP Address :");
    lv_obj_set_style_text_font(ipAddressLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ipAddressLabelAnswer = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(ipAddressLabelAnswer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ipAddressLabelAnswer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ipAddressLabelAnswer, 95);
    lv_obj_set_y(ipAddressLabelAnswer, 30);
    lv_label_set_text_fmt(ipAddressLabelAnswer, "%s",IPADDRESS);

    securityLabel = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(securityLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(securityLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(securityLabel, 0);
    lv_obj_set_y(securityLabel, 55);
    lv_label_set_text(securityLabel, "Security :");
    lv_obj_set_style_text_font(securityLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    securityLabelAnswer = lv_label_create(wifiScreenPanel);
    lv_obj_set_width(securityLabelAnswer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(securityLabelAnswer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(securityLabelAnswer, 80);
    lv_obj_set_y(securityLabelAnswer, 55);
    lv_label_set_text(securityLabelAnswer, "NA");

    conectWifiButton = lv_btn_create(wifiScreen);
    lv_obj_set_width(conectWifiButton, 140);
    lv_obj_set_height(conectWifiButton, 70);
    lv_obj_set_x(conectWifiButton, 15);
    lv_obj_set_y(conectWifiButton, -15);
    lv_obj_set_align(conectWifiButton, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_style_bg_color(conectWifiButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(conectWifiButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    conectWifiButtonLabel = lv_label_create(conectWifiButton);
    lv_obj_set_width(conectWifiButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(conectWifiButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(conectWifiButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(conectWifiButtonLabel, "Connect \nWiFi");
    lv_obj_set_style_text_align(conectWifiButtonLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(conectWifiButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    disconectWifiButton = lv_btn_create(wifiScreen);
    lv_obj_set_width(disconectWifiButton, 140);
    lv_obj_set_height(disconectWifiButton, 70);
    lv_obj_set_x(disconectWifiButton, -15);
    lv_obj_set_y(disconectWifiButton, -15);
    lv_obj_set_align(disconectWifiButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_style_bg_color(disconectWifiButton, lv_color_hex(0xF9B23D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(disconectWifiButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    disconectWifiButtonLabel = lv_label_create(disconectWifiButton);
    lv_obj_set_width(disconectWifiButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(disconectWifiButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(disconectWifiButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(disconectWifiButtonLabel, "Disconect\nWiFi");
    lv_obj_set_style_text_align(disconectWifiButtonLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(disconectWifiButtonLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

	//Menu Button Event
	lv_obj_add_event_cb(wifiMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);

	//Connect Wifi Button Event
	lv_obj_add_event_cb(conectWifiButton, connectWifiButtonCallback, LV_EVENT_ALL, NULL);

	//DisConnect Wifi Button Event
	lv_obj_add_event_cb(disconectWifiButton, disconectWifiButtonCallback, LV_EVENT_ALL, NULL);
}

void createWifiLoadingScreen(void)
{
	activeScreen = WIFILOADING;

	wifiLoadingScreen = lv_obj_create(NULL);
	lv_scr_load(wifiLoadingScreen);

	wifiLoadingMenuButton = lv_imgbtn_create(wifiLoadingScreen);
	lv_imgbtn_set_src(wifiLoadingMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(wifiLoadingMenuButton, 30);
	lv_obj_set_width(wifiLoadingMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(wifiLoadingMenuButton, 8);
	lv_obj_set_y(wifiLoadingMenuButton, 8);
	lv_obj_clear_flag(wifiLoadingMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	wifiLoadingLabel = lv_label_create(wifiLoadingScreen);
	lv_obj_set_width(wifiLoadingLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiLoadingLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiLoadingLabel, 0);
	lv_obj_set_y(wifiLoadingLabel, 60);
	lv_obj_set_align(wifiLoadingLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(wifiLoadingLabel, "Searching for available networks");
	lv_obj_clear_flag(wifiLoadingLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiLoadingLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiLoadingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiLoadingLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiLoadingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiLoadingLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiLoadingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiLoadingLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	wifiLoadingSpinner = lv_spinner_create(wifiLoadingScreen, 1000, 90);
	lv_obj_set_width(wifiLoadingSpinner, 80);
	lv_obj_set_height(wifiLoadingSpinner, 80);
	lv_obj_set_x(wifiLoadingSpinner, 0);
	lv_obj_set_y(wifiLoadingSpinner, 20);
	lv_obj_set_align(wifiLoadingSpinner, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiLoadingSpinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags

	lv_obj_set_style_arc_color(wifiLoadingSpinner, lv_color_hex(0xF9B23D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(wifiLoadingSpinner, 150, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	//Menu Button Event
	lv_obj_add_event_cb(wifiLoadingMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);
}

void createWifiTurningOnScreen(void)
{
	activeScreen = WIFITURNINGON;

	wifiTurningOnScreen = lv_obj_create(NULL);
	lv_scr_load(wifiTurningOnScreen);

	wifiTurningOnMenuButton = lv_imgbtn_create(wifiTurningOnScreen);
	lv_imgbtn_set_src(wifiTurningOnMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(wifiTurningOnMenuButton, 30);
	lv_obj_set_width(wifiTurningOnMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(wifiTurningOnMenuButton, 8);
	lv_obj_set_y(wifiTurningOnMenuButton, 8);
	lv_obj_clear_flag(wifiTurningOnMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	wifiTurningOnLoadingLabel = lv_label_create(wifiTurningOnScreen);
	lv_obj_set_width(wifiTurningOnLoadingLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiTurningOnLoadingLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiTurningOnLoadingLabel, 0);
	lv_obj_set_y(wifiTurningOnLoadingLabel, 60);
	lv_obj_set_align(wifiTurningOnLoadingLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(wifiTurningOnLoadingLabel, "Turning On WiFi");
	lv_obj_clear_flag(wifiTurningOnLoadingLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiTurningOnLoadingLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiTurningOnLoadingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiTurningOnLoadingLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiTurningOnLoadingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiTurningOnLoadingLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiTurningOnLoadingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiTurningOnLoadingLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	wifiTurningOnLoadingSpinner = lv_spinner_create(wifiTurningOnScreen, 1000, 90);
	lv_obj_set_width(wifiTurningOnLoadingSpinner, 80);
	lv_obj_set_height(wifiTurningOnLoadingSpinner, 80);
	lv_obj_set_x(wifiTurningOnLoadingSpinner, 0);
	lv_obj_set_y(wifiTurningOnLoadingSpinner, 20);
	lv_obj_set_align(wifiTurningOnLoadingSpinner, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiTurningOnLoadingSpinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags

	lv_obj_set_style_arc_color(wifiTurningOnLoadingSpinner, lv_color_hex(0xF9B23D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(wifiTurningOnLoadingSpinner, 150, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	//Menu Button Event
	lv_obj_add_event_cb(wifiTurningOnMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);
}

void createWifiConnectScreen(void)
{
	activeScreen = WIFICONNECT;

	wifiConnectScreen = lv_obj_create(NULL);
	lv_scr_load(wifiConnectScreen);

	lv_obj_clear_flag(wifiConnectScreen, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);      /// Flags
	lv_obj_set_scrollbar_mode(wifiConnectScreen, LV_SCROLLBAR_MODE_ON);
	lv_obj_set_scroll_dir(wifiConnectScreen, LV_DIR_VER);
	lv_obj_set_style_pad_left(wifiConnectScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(wifiConnectScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(wifiConnectScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(wifiConnectScreen, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

	wifiConnectMenuButton = lv_imgbtn_create(wifiConnectScreen);
	lv_imgbtn_set_src(wifiConnectMenuButton, LV_IMGBTN_STATE_RELEASED, NULL, &menuPNG, NULL);
	lv_obj_set_height(wifiConnectMenuButton, 30);
	lv_obj_set_width(wifiConnectMenuButton, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_x(wifiConnectMenuButton, 10);
	lv_obj_set_y(wifiConnectMenuButton, 8);
	lv_obj_clear_flag(wifiConnectMenuButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
					  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
					  LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags


	wifi1Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi1Panel, 300);
	lv_obj_set_height(wifi1Panel, 50);
	lv_obj_set_x(wifi1Panel, 0);
	lv_obj_set_y(wifi1Panel, 50);
	lv_obj_set_align(wifi1Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi1Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi1PanelLabel = lv_label_create(wifi1Panel);
	lv_obj_set_width(wifi1PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi1PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi1PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi1PanelLabel, "%.20s",ssidList[0].ssid);

	wifi1PanelButton = lv_btn_create(wifi1Panel);
    lv_obj_set_width(wifi1PanelButton, 80);
    lv_obj_set_height(wifi1PanelButton, 30);
    lv_obj_set_x(wifi1PanelButton, -10);
    lv_obj_set_y(wifi1PanelButton, 0);
    lv_obj_set_align(wifi1PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi1PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi1PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi1PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi1PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi1PanelButtonLabel = lv_label_create(wifi1PanelButton);
    lv_obj_set_width(wifi1PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi1PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi1PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi1PanelButtonLabel, "Connect");

	wifi2Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi2Panel, 300);
	lv_obj_set_height(wifi2Panel, 50);
	lv_obj_set_x(wifi2Panel, 0);
	lv_obj_set_y(wifi2Panel, 110);
	lv_obj_set_align(wifi2Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi2Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi2PanelLabel = lv_label_create(wifi2Panel);
	lv_obj_set_width(wifi2PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi2PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi2PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi2PanelLabel, "%.20s",ssidList[1].ssid);

	wifi2PanelButton = lv_btn_create(wifi2Panel);
    lv_obj_set_width(wifi2PanelButton, 80);
    lv_obj_set_height(wifi2PanelButton, 30);
    lv_obj_set_x(wifi2PanelButton, -10);
    lv_obj_set_y(wifi2PanelButton, 0);
    lv_obj_set_align(wifi2PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi2PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi2PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi2PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi2PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi2PanelButtonLabel = lv_label_create(wifi2PanelButton);
    lv_obj_set_width(wifi2PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi2PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi2PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi2PanelButtonLabel, "Connect");

	wifi3Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi3Panel, 300);
	lv_obj_set_height(wifi3Panel, 50);
	lv_obj_set_x(wifi3Panel, 0);
	lv_obj_set_y(wifi3Panel, 170);
	lv_obj_set_align(wifi3Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi3Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi3PanelLabel = lv_label_create(wifi3Panel);
	lv_obj_set_width(wifi3PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi3PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi3PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi3PanelLabel, "%.20s",ssidList[2].ssid);

	wifi3PanelButton = lv_btn_create(wifi3Panel);
    lv_obj_set_width(wifi3PanelButton, 80);
    lv_obj_set_height(wifi3PanelButton, 30);
    lv_obj_set_x(wifi3PanelButton, -10);
    lv_obj_set_y(wifi3PanelButton, 0);
    lv_obj_set_align(wifi3PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi3PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi3PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi3PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi3PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi3PanelButtonLabel = lv_label_create(wifi3PanelButton);
    lv_obj_set_width(wifi3PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi3PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi3PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi3PanelButtonLabel, "Connect");

	wifi4Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi4Panel, 300);
	lv_obj_set_height(wifi4Panel, 50);
	lv_obj_set_x(wifi4Panel, 0);
	lv_obj_set_y(wifi4Panel, 230);
	lv_obj_set_align(wifi4Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi4Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi4PanelLabel = lv_label_create(wifi4Panel);
	lv_obj_set_width(wifi4PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi4PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi4PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi4PanelLabel, "%.20s",ssidList[3].ssid);

	wifi4PanelButton = lv_btn_create(wifi4Panel);
    lv_obj_set_width(wifi4PanelButton, 80);
    lv_obj_set_height(wifi4PanelButton, 30);
    lv_obj_set_x(wifi4PanelButton, -10);
    lv_obj_set_y(wifi4PanelButton, 0);
    lv_obj_set_align(wifi4PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi4PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi4PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi4PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi4PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi4PanelButtonLabel = lv_label_create(wifi4PanelButton);
    lv_obj_set_width(wifi4PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi4PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi4PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi4PanelButtonLabel, "Connect");

	wifi5Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi5Panel, 300);
	lv_obj_set_height(wifi5Panel, 50);
	lv_obj_set_x(wifi5Panel, 0);
	lv_obj_set_y(wifi5Panel, 290);
	lv_obj_set_align(wifi5Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi5Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi5PanelLabel = lv_label_create(wifi5Panel);
	lv_obj_set_width(wifi5PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi5PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi5PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi5PanelLabel, "%.20s",ssidList[4].ssid);

	wifi5PanelButton = lv_btn_create(wifi5Panel);
    lv_obj_set_width(wifi5PanelButton, 80);
    lv_obj_set_height(wifi5PanelButton, 30);
    lv_obj_set_x(wifi5PanelButton, -10);
    lv_obj_set_y(wifi5PanelButton, 0);
    lv_obj_set_align(wifi5PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi5PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi5PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi5PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi5PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi5PanelButtonLabel = lv_label_create(wifi5PanelButton);
    lv_obj_set_width(wifi5PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi5PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi5PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi5PanelButtonLabel, "Connect");

	wifi6Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi6Panel, 300);
	lv_obj_set_height(wifi6Panel, 50);
	lv_obj_set_x(wifi6Panel, 0);
	lv_obj_set_y(wifi6Panel, 350);
	lv_obj_set_align(wifi6Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi6Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi6PanelLabel = lv_label_create(wifi6Panel);
	lv_obj_set_width(wifi6PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi6PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi6PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi6PanelLabel, "%.20s",ssidList[5].ssid);

	wifi6PanelButton = lv_btn_create(wifi6Panel);
    lv_obj_set_width(wifi6PanelButton, 80);
    lv_obj_set_height(wifi6PanelButton, 30);
    lv_obj_set_x(wifi6PanelButton, -10);
    lv_obj_set_y(wifi6PanelButton, 0);
    lv_obj_set_align(wifi6PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi6PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi6PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi6PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi6PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi6PanelButtonLabel = lv_label_create(wifi6PanelButton);
    lv_obj_set_width(wifi6PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi6PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi6PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi6PanelButtonLabel, "Connect");

	wifi7Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi7Panel, 300);
	lv_obj_set_height(wifi7Panel, 50);
	lv_obj_set_x(wifi7Panel, 0);
	lv_obj_set_y(wifi7Panel, 410);
	lv_obj_set_align(wifi7Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi7Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi7PanelLabel = lv_label_create(wifi7Panel);
	lv_obj_set_width(wifi7PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi7PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi7PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi7PanelLabel, "%.20s",ssidList[6].ssid);

	wifi7PanelButton = lv_btn_create(wifi7Panel);
    lv_obj_set_width(wifi7PanelButton, 80);
    lv_obj_set_height(wifi7PanelButton, 30);
    lv_obj_set_x(wifi7PanelButton, -10);
    lv_obj_set_y(wifi7PanelButton, 0);
    lv_obj_set_align(wifi7PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi7PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi7PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi7PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi7PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi7PanelButtonLabel = lv_label_create(wifi7PanelButton);
    lv_obj_set_width(wifi7PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi7PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi7PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi7PanelButtonLabel, "Connect");

	wifi8Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi8Panel, 300);
	lv_obj_set_height(wifi8Panel, 50);
	lv_obj_set_x(wifi8Panel, 0);
	lv_obj_set_y(wifi8Panel, 470);
	lv_obj_set_align(wifi8Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi8Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi8PanelLabel = lv_label_create(wifi8Panel);
	lv_obj_set_width(wifi8PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi8PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi8PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi8PanelLabel, "%.20s",ssidList[7].ssid);

	wifi8PanelButton = lv_btn_create(wifi8Panel);
    lv_obj_set_width(wifi8PanelButton, 80);
    lv_obj_set_height(wifi8PanelButton, 30);
    lv_obj_set_x(wifi8PanelButton, -10);
    lv_obj_set_y(wifi8PanelButton, 0);
    lv_obj_set_align(wifi8PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi8PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi8PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi8PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi8PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi8PanelButtonLabel = lv_label_create(wifi8PanelButton);
    lv_obj_set_width(wifi8PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi8PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi8PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi8PanelButtonLabel, "Connect");

	wifi9Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi9Panel, 300);
	lv_obj_set_height(wifi9Panel, 50);
	lv_obj_set_x(wifi9Panel, 0);
	lv_obj_set_y(wifi9Panel, 530);
	lv_obj_set_align(wifi9Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi9Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi9PanelLabel = lv_label_create(wifi9Panel);
	lv_obj_set_width(wifi9PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi9PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi9PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi9PanelLabel, "%.20s",ssidList[8].ssid);

	wifi9PanelButton = lv_btn_create(wifi9Panel);
    lv_obj_set_width(wifi9PanelButton, 80);
    lv_obj_set_height(wifi9PanelButton, 30);
    lv_obj_set_x(wifi9PanelButton, -10);
    lv_obj_set_y(wifi9PanelButton, 0);
    lv_obj_set_align(wifi9PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi9PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi9PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi9PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi9PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi9PanelButtonLabel = lv_label_create(wifi9PanelButton);
    lv_obj_set_width(wifi9PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi9PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi9PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi9PanelButtonLabel, "Connect");

	wifi10Panel = lv_obj_create(wifiConnectScreen);
	lv_obj_set_width(wifi10Panel, 300);
	lv_obj_set_height(wifi10Panel, 50);
	lv_obj_set_x(wifi10Panel, 0);
	lv_obj_set_y(wifi10Panel, 590);
	lv_obj_set_align(wifi10Panel, LV_ALIGN_TOP_MID);
	lv_obj_clear_flag(wifi10Panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifi10PanelLabel = lv_label_create(wifi10Panel);
	lv_obj_set_width(wifi10PanelLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifi10PanelLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(wifi10PanelLabel, LV_ALIGN_LEFT_MID);
	lv_label_set_text_fmt(wifi10PanelLabel, "%.20s",ssidList[9].ssid);

	wifi10PanelButton = lv_btn_create(wifi10Panel);
    lv_obj_set_width(wifi10PanelButton, 80);
    lv_obj_set_height(wifi10PanelButton, 30);
    lv_obj_set_x(wifi10PanelButton, -10);
    lv_obj_set_y(wifi10PanelButton, 0);
    lv_obj_set_align(wifi10PanelButton, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(wifi10PanelButton, LV_OBJ_FLAG_PRESS_LOCK);      /// Flags
    lv_obj_set_style_radius(wifi10PanelButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(wifi10PanelButton, lv_color_hex(0x7F85F9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wifi10PanelButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifi10PanelButtonLabel = lv_label_create(wifi10PanelButton);
    lv_obj_set_width(wifi10PanelButtonLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifi10PanelButtonLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(wifi10PanelButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(wifi10PanelButtonLabel, "Connect");

	//Menu Button Event
	lv_obj_add_event_cb(wifiConnectMenuButton, menuButtonCallback, LV_EVENT_ALL, NULL);

	//Connect Button Event
	lv_obj_add_event_cb(wifi1PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi1PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi2PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi2PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi3PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi3PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi4PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi4PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi5PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi5PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi6PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi6PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi7PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi7PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi8PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi8PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi9PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi9PanelButton);

	//Connect Button Event
	lv_obj_add_event_cb(wifi10PanelButton, wifiConnectCallback, LV_EVENT_ALL, &wifi10PanelButton);
}

void createWifiPasswordScreen(void)
{
	activeScreen = WIFIPASSWORD;

	wifiPasswordScreen = lv_obj_create(NULL);
	lv_scr_load(wifiPasswordScreen);

	wifiPasswordScreenNameLabel = lv_label_create(wifiPasswordScreen);
    lv_obj_set_width(wifiPasswordScreenNameLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifiPasswordScreenNameLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(wifiPasswordScreenNameLabel, 10);
    lv_obj_set_y(wifiPasswordScreenNameLabel, 30);
    lv_label_set_text(wifiPasswordScreenNameLabel, "Name :");
    lv_obj_set_style_text_font(wifiPasswordScreenNameLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    wifiPasswordScreenNameAnswer = lv_label_create(wifiPasswordScreen);
    lv_obj_set_width(wifiPasswordScreenNameAnswer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifiPasswordScreenNameAnswer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(wifiPasswordScreenNameAnswer, 75);
    lv_obj_set_y(wifiPasswordScreenNameAnswer, 30);
    lv_label_set_text(wifiPasswordScreenNameAnswer, "NA");

    wifiPasswordScreenPasswordLabel = lv_label_create(wifiPasswordScreen);
    lv_obj_set_width(wifiPasswordScreenPasswordLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(wifiPasswordScreenPasswordLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(wifiPasswordScreenPasswordLabel, 10);
    lv_obj_set_y(wifiPasswordScreenPasswordLabel, -40);
    lv_obj_set_align(wifiPasswordScreenPasswordLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(wifiPasswordScreenPasswordLabel, "Password :");

    wifiPasswordTextArea = lv_textarea_create(wifiPasswordScreen);
    lv_obj_set_width(wifiPasswordTextArea, 200);
    lv_obj_set_height(wifiPasswordTextArea, 40);
    lv_obj_set_x(wifiPasswordTextArea, -20);
    lv_obj_set_y(wifiPasswordTextArea, -40);
    lv_obj_set_align(wifiPasswordTextArea, LV_ALIGN_RIGHT_MID);
    lv_textarea_set_placeholder_text(wifiPasswordTextArea, "Password...");
    lv_textarea_set_password_mode(wifiPasswordTextArea, true);

    ui_Keyboard1 = lv_keyboard_create(wifiPasswordScreen);
    lv_obj_set_width(ui_Keyboard1, 320);
    lv_obj_set_height(ui_Keyboard1, 130);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_BOTTOM_MID);
    lv_keyboard_set_textarea(ui_Keyboard1, wifiPasswordTextArea);


    closeImageButton = lv_img_create(wifiPasswordScreen);
    lv_img_set_src(closeImageButton, &crossPNG);
    lv_obj_set_width(closeImageButton, 30);
    lv_obj_set_height(closeImageButton, 30);
    lv_obj_set_x(closeImageButton, -10);
    lv_obj_set_y(closeImageButton, 10);
    lv_obj_set_align(closeImageButton, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(closeImageButton, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_clear_flag(closeImageButton, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags

	//Close Button Event
	lv_obj_add_event_cb(closeImageButton, closeButtonCallback, LV_EVENT_ALL, NULL);

	//Keyboard Event
	lv_obj_add_event_cb(ui_Keyboard1, wifiPasswordKeyboardEvent, LV_EVENT_READY, NULL);

}

void createWifiConnectingMessageBox(void)
{
	activeScreen = WIFICONNECTING;

	wifiConnectingMessageBox = lv_obj_create(lv_scr_act());
	lv_obj_set_width(wifiConnectingMessageBox, 200);
	lv_obj_set_height(wifiConnectingMessageBox, 150);
	lv_obj_set_align(wifiConnectingMessageBox, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiConnectingMessageBox, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifiConnectingLabel = lv_label_create(wifiConnectingMessageBox);
	lv_obj_set_width(wifiConnectingLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiConnectingLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiConnectingLabel, 0);
	lv_obj_set_y(wifiConnectingLabel, 5);
	lv_obj_set_align(wifiConnectingLabel, LV_ALIGN_TOP_MID);
	lv_label_set_text(wifiConnectingLabel, "Connecting");
	lv_obj_clear_flag(wifiConnectingLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiConnectingLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiConnectingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiConnectingLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiConnectingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiConnectingLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiConnectingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiConnectingLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);

	wifiConnectingSpinner = lv_spinner_create(wifiConnectingMessageBox, 1000, 90);
	lv_obj_set_width(wifiConnectingSpinner, 60);
	lv_obj_set_height(wifiConnectingSpinner, 60);
	lv_obj_set_x(wifiConnectingSpinner, 0);
	lv_obj_set_y(wifiConnectingSpinner, 20);
	lv_obj_set_align(wifiConnectingSpinner, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiConnectingSpinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags

	lv_obj_set_style_arc_color(wifiConnectingSpinner, lv_color_hex(0xF9B23D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(wifiConnectingSpinner, 150, LV_PART_INDICATOR | LV_STATE_DEFAULT);

}

void createWifiErrorMessageBox(void)
{
	wifiErrorMessageBox = lv_obj_create(lv_scr_act());
	lv_obj_set_width(wifiErrorMessageBox, 200);
	lv_obj_set_height(wifiErrorMessageBox, 150);
	lv_obj_set_align(wifiErrorMessageBox, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiErrorMessageBox, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifiErrorLabel = lv_label_create(wifiErrorMessageBox);
	lv_obj_set_width(wifiErrorLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiErrorLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiErrorLabel, 0);
	lv_obj_set_y(wifiErrorLabel, 0);
	lv_obj_set_align(wifiErrorLabel, LV_ALIGN_CENTER);
	lv_label_set_text(wifiErrorLabel, "WiFi Error");
	lv_obj_clear_flag(wifiErrorLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiErrorLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiErrorLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiErrorLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiErrorLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiErrorLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiErrorLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiErrorLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);
}

void createWifiConnectingFailedMessageBox(void)
{
	wifiConnectingFailedMessageBox = lv_obj_create(lv_scr_act());
	lv_obj_set_width(wifiConnectingFailedMessageBox, 200);
	lv_obj_set_height(wifiConnectingFailedMessageBox, 150);
	lv_obj_set_align(wifiConnectingFailedMessageBox, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiConnectingFailedMessageBox, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifiConnectingFailedLabel = lv_label_create(wifiConnectingFailedMessageBox);
	lv_obj_set_width(wifiConnectingFailedLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiConnectingFailedLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiConnectingFailedLabel, 0);
	lv_obj_set_y(wifiConnectingFailedLabel, 0);
	lv_obj_set_align(wifiConnectingFailedLabel, LV_ALIGN_CENTER);
	lv_label_set_text(wifiConnectingFailedLabel, "Connecting Failed");
	lv_obj_clear_flag(wifiConnectingFailedLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiConnectingFailedLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiConnectingFailedLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiConnectingFailedLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiConnectingFailedLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiConnectingFailedLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiConnectingFailedLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiConnectingFailedLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);
}

void createWifiConnectingSuccessfullMessageBox(void)
{
	wifiConnectingSuccessfullMessageBox = lv_obj_create(lv_scr_act());
	lv_obj_set_width(wifiConnectingSuccessfullMessageBox, 200);
	lv_obj_set_height(wifiConnectingSuccessfullMessageBox, 150);
	lv_obj_set_align(wifiConnectingSuccessfullMessageBox, LV_ALIGN_CENTER);
	lv_obj_clear_flag(wifiConnectingSuccessfullMessageBox, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
					  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE);     /// Flags

	wifiConnectingSuccessfullLabel = lv_label_create(wifiConnectingSuccessfullMessageBox);
	lv_obj_set_width(wifiConnectingSuccessfullLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(wifiConnectingSuccessfullLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(wifiConnectingSuccessfullLabel, 0);
	lv_obj_set_y(wifiConnectingSuccessfullLabel, 0);
	lv_obj_set_align(wifiConnectingSuccessfullLabel, LV_ALIGN_CENTER);
	lv_label_set_text(wifiConnectingSuccessfullLabel, "Connection \nSuccessful");
	lv_obj_clear_flag(wifiConnectingSuccessfullLabel,
					  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
					  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
	lv_obj_set_style_text_color(wifiConnectingSuccessfullLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(wifiConnectingSuccessfullLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(wifiConnectingSuccessfullLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(wifiConnectingSuccessfullLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_opa(wifiConnectingSuccessfullLabel, 255, LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(wifiConnectingSuccessfullLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(wifiConnectingSuccessfullLabel, 255, LV_PART_MAIN | LV_STATE_PRESSED);
}

void creatCalendarScreen(void)
{
	activeScreen = DATE;

	calendarScreen = lv_obj_create(NULL);
	lv_scr_load(calendarScreen);
    lv_obj_clear_flag(calendarScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    calendarScreenLabel = lv_label_create(calendarScreen);
    lv_obj_set_width(calendarScreenLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(calendarScreenLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(calendarScreenLabel, 0);
    lv_obj_set_y(calendarScreenLabel, 10);
    lv_obj_set_align(calendarScreenLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(calendarScreenLabel, "Set Date");
    lv_obj_set_style_text_color(calendarScreenLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(calendarScreenLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(calendarScreenLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    calendar = lv_calendar_create(calendarScreen);
    lv_obj_t * calendarHeader = lv_calendar_header_dropdown_create(calendar);
    lv_calendar_set_showed_date(calendar, 2024, 1);
    lv_calendar_set_today_date(calendar, 2024, 1, 1);
    lv_obj_set_width(calendar, 320);
    lv_obj_set_height(calendar, 200);
    lv_obj_set_align(calendar, LV_ALIGN_BOTTOM_MID);

    calendarCrossButton = lv_imgbtn_create(calendarScreen);
    lv_imgbtn_set_src(calendarCrossButton, LV_IMGBTN_STATE_RELEASED, NULL, &crossPNG, NULL);
    lv_obj_set_width(calendarCrossButton, 30);
    lv_obj_set_height(calendarCrossButton, 30);
    lv_obj_set_x(calendarCrossButton, 10);
    lv_obj_set_y(calendarCrossButton, 5);

    calendarTickButton = lv_imgbtn_create(calendarScreen);
    lv_imgbtn_set_src(calendarTickButton, LV_IMGBTN_STATE_RELEASED, NULL, &tickPNG, NULL);
    lv_obj_set_width(calendarTickButton, 30);
    lv_obj_set_height(calendarTickButton, 30);
    lv_obj_set_x(calendarTickButton, -10);
    lv_obj_set_y(calendarTickButton, 5);
    lv_obj_set_align(calendarTickButton, LV_ALIGN_TOP_RIGHT);

    // Add the event handler for clicks
    lv_obj_add_event_cb(calendar, calendarCallback, LV_EVENT_CLICKED, NULL);

    //Tick Button Callback
    lv_obj_add_event_cb(calendarTickButton, calendarTickButtonCallback, LV_EVENT_CLICKED, NULL);

    //Cross Button Callback
    lv_obj_add_event_cb(calendarCrossButton, calendarCrossButtonCallback, LV_EVENT_CLICKED, NULL);
}

void creatTimeScreen(void)
{
	activeScreen = TIME;

	timeScreen = lv_obj_create(NULL);
	lv_scr_load(timeScreen);
    lv_obj_clear_flag(timeScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    timeScreenLabel = lv_label_create(timeScreen);
    lv_obj_set_width(timeScreenLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(timeScreenLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(timeScreenLabel, 1);
    lv_obj_set_y(timeScreenLabel, 10);
    lv_obj_set_align(timeScreenLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(timeScreenLabel, "SET TIME");
    lv_obj_set_style_text_color(timeScreenLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(timeScreenLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(timeScreenLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    timeScreenCrossButton = lv_imgbtn_create(timeScreen);
    lv_imgbtn_set_src(timeScreenCrossButton, LV_IMGBTN_STATE_RELEASED, NULL, &crossPNG, NULL);
    lv_obj_set_width(timeScreenCrossButton, 30);
    lv_obj_set_height(timeScreenCrossButton, 30);
    lv_obj_set_x(timeScreenCrossButton, 10);
    lv_obj_set_y(timeScreenCrossButton, 5);

    timeScreenTickButton = lv_imgbtn_create(timeScreen);
    lv_imgbtn_set_src(timeScreenTickButton, LV_IMGBTN_STATE_RELEASED, NULL, &tickPNG, NULL);
    lv_obj_set_width(timeScreenTickButton, 30);
    lv_obj_set_height(timeScreenTickButton, 30);
    lv_obj_set_x(timeScreenTickButton, -10);
    lv_obj_set_y(timeScreenTickButton, 5);
    lv_obj_set_align(timeScreenTickButton, LV_ALIGN_TOP_RIGHT);

    hourLabel = lv_label_create(timeScreen);
    lv_obj_set_width(hourLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(hourLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(hourLabel, 10);
    lv_obj_set_y(hourLabel, -40);
    lv_obj_set_align(hourLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(hourLabel, "HOUR");
    lv_obj_set_style_text_font(hourLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    hourRoller = lv_roller_create(timeScreen);
    lv_roller_set_options(hourRoller, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12", LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(hourRoller, 100);
    lv_obj_set_width(hourRoller, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(hourRoller, 15);
    lv_obj_set_y(hourRoller, 30);
    lv_obj_set_align(hourRoller, LV_ALIGN_LEFT_MID);
    lv_roller_set_selected(hourRoller, 0, LV_ANIM_ON);
    lv_obj_set_style_bg_color(hourRoller, lv_color_hex(0x7F85F9), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(hourRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    minutesLabel = lv_label_create(timeScreen);
    lv_obj_set_width(minutesLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(minutesLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(minutesLabel, 75);
    lv_obj_set_y(minutesLabel, -40);
    lv_obj_set_align(minutesLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(minutesLabel, "MINUTES");
    lv_obj_set_style_text_font(minutesLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    minutesRoller = lv_roller_create(timeScreen);
    lv_roller_set_options(minutesRoller,
                          "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59\n00",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(minutesRoller, 100);
    lv_obj_set_width(minutesRoller, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(minutesRoller, 90);
    lv_obj_set_y(minutesRoller, 30);
    lv_obj_set_align(minutesRoller, LV_ALIGN_LEFT_MID);
    lv_roller_set_selected(minutesRoller, 0, LV_ANIM_ON);
    lv_obj_set_style_bg_color(minutesRoller, lv_color_hex(0x7F85F9), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(minutesRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    secondsLabel = lv_label_create(timeScreen);
    lv_obj_set_width(secondsLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(secondsLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(secondsLabel, 160);
    lv_obj_set_y(secondsLabel, -40);
    lv_obj_set_align(secondsLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(secondsLabel, "SECONDS");
    lv_obj_set_style_text_font(secondsLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    secondsRoller = lv_roller_create(timeScreen);
    lv_roller_set_options(secondsRoller,
                          "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59\n00",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(secondsRoller, 100);
    lv_obj_set_width(secondsRoller, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(secondsRoller, 175);
    lv_obj_set_y(secondsRoller, 30);
    lv_obj_set_align(secondsRoller, LV_ALIGN_LEFT_MID);
    lv_roller_set_selected(secondsRoller, 0, LV_ANIM_ON);
    lv_obj_set_style_bg_color(secondsRoller, lv_color_hex(0x7F85F9), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(secondsRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    amPMLabel = lv_label_create(timeScreen);
    lv_obj_set_width(amPMLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(amPMLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(amPMLabel, 250);
    lv_obj_set_y(amPMLabel, -40);
    lv_obj_set_align(amPMLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(amPMLabel, "AM/PM");
    lv_obj_set_style_text_font(amPMLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    amPMRoller = lv_roller_create(timeScreen);
    lv_roller_set_options(amPMRoller, "AM\nPM", LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(amPMRoller, 100);
    lv_obj_set_width(amPMRoller, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(amPMRoller, 255);
    lv_obj_set_y(amPMRoller, 30);
    lv_obj_set_align(amPMRoller, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_bg_color(amPMRoller, lv_color_hex(0x7F85F9), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(amPMRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    //Tick Button Callback
    lv_obj_add_event_cb(timeScreenTickButton, timeScreenTickButtonCallback, LV_EVENT_CLICKED, NULL);

    //Cross Button Callback
    lv_obj_add_event_cb(timeScreenCrossButton, timeScreenCrossButtonCallback, LV_EVENT_CLICKED, NULL);

    // Add event handler to detect changes
    lv_obj_add_event_cb(hourRoller, timeScreenCallback, LV_EVENT_VALUE_CHANGED, NULL);

    // Add event handler to detect changes
    lv_obj_add_event_cb(minutesRoller, timeScreenCallback, LV_EVENT_VALUE_CHANGED, NULL);

    // Add event handler to detect changes
    lv_obj_add_event_cb(secondsRoller, timeScreenCallback, LV_EVENT_VALUE_CHANGED, NULL);

    // Add event handler to detect changes
    lv_obj_add_event_cb(amPMRoller, timeScreenCallback, LV_EVENT_VALUE_CHANGED, NULL);
}

void createBootScreen(void)
{
	activeScreen = BOOT;

	bootScreen = lv_obj_create(NULL);
	lv_scr_load(bootScreen);

    smartHomeLabel = lv_label_create(bootScreen);
    lv_obj_set_width(smartHomeLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(smartHomeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(smartHomeLabel, 0);
    lv_obj_set_y(smartHomeLabel, 50);
    lv_obj_set_align(smartHomeLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(smartHomeLabel, "SMART HOME");
    lv_obj_set_style_text_color(smartHomeLabel, lv_color_hex(0x171935), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(smartHomeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(smartHomeLabel, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);

    bootSpinner = lv_spinner_create(bootScreen, 1000, 90);
    lv_obj_set_width(bootSpinner, 50);
    lv_obj_set_height(bootSpinner, 50);
    lv_obj_set_x(bootSpinner, 0);
    lv_obj_set_y(bootSpinner, 10);
    lv_obj_set_align(bootSpinner, LV_ALIGN_CENTER);
    lv_obj_clear_flag(bootSpinner, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(bootSpinner, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(bootSpinner, lv_color_hex(0xF9B23D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(bootSpinner, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(bootSpinner, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    bootLabel = lv_label_create(bootScreen);
    lv_obj_set_width(bootLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(bootLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(bootLabel, 0);
    lv_obj_set_y(bootLabel, 60);
    lv_obj_set_align(bootLabel, LV_ALIGN_CENTER);
    lv_label_set_text(bootLabel, "Booting Up.....");
    lv_obj_set_style_text_font(bootLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
}
