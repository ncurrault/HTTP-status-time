#include <pebble.h>
#include <window.h>


char* wubz[12][60] = {
	{},
	{
		"Continue",
		"Switching Protocols",
		"Processing"
	},{
		"OK",
		"Created",
		"Accepted",
		"Non-Authoritative Information",
		"No Content",
		"Reset Content",
		"Partial Content",
		"Multi-Status",
		"Already Reported",
		"IM Used"
	},{
		"Multiple Choices",
		"Moved Permanently",
		"Found",
		"See Other",
		"Not Modified",
		"Use Proxy",
		"Switch Proxy",
		"Temporary Redirect",
		"Permanent Redirect"
	},{
		"Bad Request",
		"Unauthorized",
		"Payment Required",
		"Forbidden",
		"Not Found",
		"Method Not Allowed",
		"Not Acceptable",
		"Proxy Authentication Required",
		"Request Timeout",
		"Conflict",
		"Gone",
		"Length Required",
		"Precondition Failed",
		"Request Entity Too Large",
		"Request-URI Too Long",
		"Unsupported Media Type",
		"Requested Range Not Satisfiable",
		"Expectation Failed",
		"I'm a teapot",
		"Authentication Timeout",
		"Enhance Your Calm",
		"--",
		"Unprocessable Entity",
		"Locked",
		"Failed Dependency",
		"--",
		"Upgrade Required",
		"--",
		"Precondition Required",
		"Too Many Requests",
		"--",
		"Request Header Fields Too Large",
		"--",
		"--",
		"--",
		"--",
		"--",
		"--",
		"--",
		"--",
		"Login Timeout",
		"--",
		"--",
		"--",
		"No Response",
		"--",
		"--",
		"--",
		"--",
		"Retry With",
		"Blocked by Windows Parental Controls",
		"Unavailable For Legal Reasons"
	}, {
		"Internal Server Error",
		"Not Implemented",
		"Bad Gateway",
		"Service Unavailable",
		"Gateway Timeout",
		"HTTP Version Not Supported",
		"Variant Also Negotiates",
		"Insufficient Storage",
		"Loop Detected",
		"Bandwidth Limit Exceeded",
		"Not Extended",
		"Network Authentication Required"
	}
};

char * get_time_str (struct tm * tick_time)
{
	// Need to be static because it's used by the system later.
	static char time_text[] = "00:00";
	
	char * time_format;
	if (clock_is_24h_style())
	{
		time_format = "%R";
	}
	else
	{
		time_format = "%I:%M";
	}
	
	strftime(time_text, sizeof(time_text), time_format, tick_time);

	// Kludge to handle lack of non-padded hour format string
	// for twelve hour clock.
	if (!clock_is_24h_style() && (time_text[0] == '0'))
	{
		memmove(time_text, &time_text[1], sizeof(time_text) - 1);
		//time_text[0] = ' ';
	}

	return time_text;
}

void handle_minute_tick(struct tm * tick_time, TimeUnits units_changed) {
	set_time_text(get_time_str(tick_time));
	
	int hour = tick_time->tm_hour;
	int min = tick_time->tm_min;
	
	set_status_text(wubz[hour % 12][min]);
}

void handle_init() {
	show_window();
	
	time_t* theCurrentTime = malloc(sizeof(*theCurrentTime));
	time(theCurrentTime);
	handle_minute_tick(localtime(theCurrentTime), MINUTE_UNIT);
	
	tick_timer_service_subscribe(MINUTE_UNIT,handle_minute_tick);
}
void handle_deinit()
{
	//destroy_ui();
	tick_timer_service_unsubscribe();
}
int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}