#include <pebble.h>
#include <string.h>
	
Window *window;
TextLayer *text_layer;
TextLayer *header_text;
TextLayer *currentweek;

/*static void second_tick(struct tm* tick_time, TimeUnits units_changed) { //formatted time HH:MM:SS
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	static char time[] = "00:00:00"; 
	strftime(time, sizeof(time), "%T", current_time);
	text_layer_set_text(text_layer, time);
	static const uint32_t const segments[] = { 995 }; //do not use values above 995 due to vibration glitch
}*/

static void weekday_tick(struct tm* tick_time, TimeUnits units_changed) { //formatted day
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	static char time[] = "XXXXXXX"; 
	strftime(time, sizeof(time), "%u", current_time);
}

void header_init(void){
	header_text=text_layer_create(GRect(0,0,144,28));
	text_layer_set_text(header_text,"Расписание");
	text_layer_set_text_color(header_text, GColorWhite);
	text_layer_set_background_color(header_text, GColorClear);
	text_layer_set_font(header_text, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(header_text, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(header_text));
	window_stack_push(window, true);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void header_deinit(void){
	text_layer_destroy(header_text);
}

void currentweek_init(void){

	currentweek = text_layer_create(GRect(0, 26, 144, 40));
	text_layer_set_text_color(currentweek, GColorWhite);
	text_layer_set_background_color(currentweek, GColorClear);
	text_layer_set_font(currentweek, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(currentweek, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(currentweek));
	window_stack_push(window, true);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	static char week[] = "XXXXXXX";
	strftime(week, sizeof(week), "%V", current_time);
	switch(atoi(week)%2)
	{
		case 0:
			text_layer_set_text(currentweek,"Числитель");
			break;
		case 1:
			text_layer_set_text(currentweek,"Знаменатель");
			break;
	}
}

void currentweek_deinit(void){
	text_layer_destroy(currentweek);
}
void handle_init(void){
	window = window_create();
	window_set_background_color(window,GColorBlack);
	window_set_fullscreen(window, true);
	text_layer = text_layer_create(GRect(0, 52, 144, 154));
	tick_timer_service_subscribe(DAY_UNIT, &weekday_tick);
	
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	static char time[] = "XXXXXXX";
	static char week[] = "XXXXXXX";
	strftime(time, sizeof(time), "%u", current_time);
	strftime(week, sizeof(week), "%V", current_time);
	int timey,weekey;
	timey = atoi(time);
	weekey = atoi(week);
	switch(weekey%2)
	{
		case 0: //чётная неделя, числитель
			switch(timey)
			{
		case 1: //понедельник
			text_layer_set_text(text_layer,"1: Физра Антей"); 
			break;
		case 2: //вторник
			text_layer_set_text(text_layer,"2: Информационные технологии в экономике 202\r\n\3: Информационные технологии 202"); 
			break;
		case 3: //среда
			text_layer_set_text(text_layer,"2: История 301\r\n3:Программирование 420\r\n4: Английский 415"); 
			break;
		case 4: //четверг
			text_layer_set_text(text_layer,"2: БЖД 415\r\n3: Программирование 202"); 
			break;
		case 5: //пятница
			text_layer_set_text(text_layer,"1: Матан 202\r\n2: Матан 218\r\n3: Информационная безопасность 411\r\n4: Информационная безопасность 411"); 
			break;
		case 6: //суббота
			text_layer_set_text(text_layer,"2:Правоведение 202\r\n3: Операционные системы 420"); 
			break;
		case 7: //воскресенье
			text_layer_set_text(text_layer,"Закрой расписание и иди отдыхать. Следующая неделя - знаменатель"); 
				break;
			}
		break;
			
		case 1: //нечётная неделя, знаменатель
			switch(timey)
			{
		case 1: //понедельник
			text_layer_set_text(text_layer,"1: Физра Антей"); 
			break;
		case 2: //вторник
			text_layer_set_text(text_layer,"2: Информационные технологии 202 \r\n\3: Информационные технологии в экономике 202"); 
			break;
		case 3: //среда
			text_layer_set_text(text_layer,"1: История 218\r\n2: История 301\r\n3: Программирование 420\r\n4:Английский 415"); 
			break;
		case 4: //четверг
			text_layer_set_text(text_layer,"1: Матан 218\r\n2:БЖД 301\r\n3: Программирование 202"); 
			break;
		case 5: //пятница
			text_layer_set_text(text_layer,"1: Матан 202\r\n2: Матан 218\r\n3: Информационная безопасность 411"); 
			break;
		case 6: //суббота
			text_layer_set_text(text_layer,"1: Операционные системы 420\r\n2: Правоведение 202"); 
			break;
		case 7: //воскресенте
			text_layer_set_text(text_layer,"Закрой расписание и иди отдыхать. Следующая неделя - числитель"); 
			break;

	}
		break;}
	text_layer_set_text_color(text_layer, GColorWhite);
	text_layer_set_background_color(text_layer, GColorClear);
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
	window_stack_push(window, true);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) { 
	text_layer_destroy(text_layer);
	tick_timer_service_unsubscribe();
	window_destroy(window);
}

int main(void) {
	handle_init();
	header_init();
	currentweek_init();
	app_event_loop();
	currentweek_deinit();
	header_deinit();
	handle_deinit();
}
