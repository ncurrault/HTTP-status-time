#include "window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_28_bold;
static TextLayer *s_time;
static TextLayer *s_status;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_time
  s_time = text_layer_create(GRect(0, 0, 144, 50));
  text_layer_set_text(s_time, "4:04");
  text_layer_set_text_alignment(s_time, GTextAlignmentCenter);
  text_layer_set_font(s_time, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time);
  
  // s_status
  s_status = text_layer_create(GRect(4, 42, 136, 123));
  text_layer_set_text(s_status, "Time Not Found");
  text_layer_set_font(s_status, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_status);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_time);
  text_layer_destroy(s_status);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window(void) {
  window_stack_remove(s_window, true);
}

void set_time_text(char* text) {
	text_layer_set_text(s_time, text);
}
void set_status_text(char* text) {
	text_layer_set_text(s_status, text);
}
