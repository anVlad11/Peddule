#include <pebble.h>

Window *window;
TextLayer *text_layer;

static void second_tick(struct tm* tick_time, TimeUnits units_changed) { //время в формате HH:MM:SS
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	static char time[] = "00:00:00"; 
	strftime(time, sizeof(time), "%T", current_time);
	text_layer_set_text(text_layer, time);
	static const uint32_t const segments[] = { 995 };
	VibePattern pat = {
  	.durations = segments,
  	.num_segments = ARRAY_LENGTH(segments),
	};
	vibes_enqueue_custom_pattern(pat);
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	window_set_background_color(window, GColorBlack);
	// Set the text, font, and text alignment
	tick_timer_service_subscribe(SECOND_UNIT, &second_tick);
	text_layer_set_text_color(text_layer, GColorWhite);
	text_layer_set_background_color(text_layer, GColorClear);
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
	window_stack_push(window, true);
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) { //TODO: Не забывать вписывать сюда вообще всё
	text_layer_destroy(text_layer);
	tick_timer_service_unsubscribe();
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
