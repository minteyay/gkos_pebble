#include <Arduino.h>
#include <Pins.h>
#include <Bounce2.h>
#include <Keys.h>
#include <Keyboard.h>
#include <SPI.h>
#include <U8g2lib.h>

Bounce2::Button key_a = Bounce2::Button();
Bounce2::Button key_b = Bounce2::Button();
Bounce2::Button key_c = Bounce2::Button();
Bounce2::Button key_d = Bounce2::Button();
Bounce2::Button key_e = Bounce2::Button();
Bounce2::Button key_f = Bounce2::Button();
const uint16_t N_KEYS_GKOS = 6;
Bounce2::Button* keys_gkos[N_KEYS_GKOS] =
	{ &key_a, &key_b, &key_c, &key_d, &key_e, &key_f };
pin_size_t pins_gkos[N_KEYS_GKOS] = 
	{ Pins::KEY_A, Pins::KEY_B, Pins::KEY_C, Pins::KEY_D, Pins::KEY_E, Pins::KEY_F };
const uint16_t KEY_GKOS_DEBOUNCE_MS = 5; 

// TODO: m2 and m4 dont register keypresses
Bounce2::Button key_m1 = Bounce2::Button();
Bounce2::Button key_m2 = Bounce2::Button();
Bounce2::Button key_m3 = Bounce2::Button();
Bounce2::Button key_m4 = Bounce2::Button();
const uint16_t KEYS_MOUSE_N = 4;
Bounce2::Button* keys_mouse[KEYS_MOUSE_N] =
	{ &key_m1, &key_m2, &key_m3, &key_m4 };
pin_size_t pins_mouse[KEYS_MOUSE_N] =
	{ Pins::MOUSE_1, Pins::MOUSE_2, Pins::MOUSE_3, Pins::MOUSE_4 };
const uint16_t KEY_MOUSE_DEBOUNCE_MS = 10; 

Bounce2::Button key_menu = Bounce2::Button();
const uint16_t KEY_MENU_DEBOUNCE_MS = 5;

const uint8_t GKOS_MASKS[N_KEYS_GKOS] = { 1, 2, 4, 8, 16, 32 };
uint8_t gkos_keycode = 0;
uint8_t gkos_keycode_max = 0;
bool gkos_dirty = false;

U8G2_LS013B7DH03_128X128_F_4W_HW_SPI lcd(
	U8G2_R1, Pins::LCD_SCS, U8X8_PIN_NONE);
const uint8_t WHITE = 1;
const uint8_t BLACK = 0;

void setup() {
	for (int i = 0; i < N_KEYS_GKOS; i++) {
		keys_gkos[i]->attach(pins_gkos[i], INPUT);
		keys_gkos[i]->interval(KEY_GKOS_DEBOUNCE_MS);
		keys_gkos[i]->setPressedState(LOW);
	}
	for (int i = 0; i < KEYS_MOUSE_N; i++) {
		keys_mouse[i]->attach(pins_mouse[i], INPUT);
		keys_mouse[i]->interval(KEY_MOUSE_DEBOUNCE_MS);
		keys_mouse[i]->setPressedState(LOW);
	}
	key_menu.attach(Pins::MENU, INPUT);
	key_menu.interval(KEY_MENU_DEBOUNCE_MS);
	key_menu.setPressedState(LOW);

	pinMode(Pins::LED, OUTPUT);

	pinMode(Pins::LCD_COMIN, OUTPUT);
	digitalWrite(Pins::LCD_COMIN, LOW);

	SPI.setTX(Pins::LCD_SI);
	SPI.setSCK(Pins::LCD_SCLK);
	SPI.setCS(Pins::LCD_SCS);

	lcd.begin();
	lcd.clearBuffer();
	lcd.setDrawColor(WHITE);
	lcd.drawBox(0, 0, lcd.getWidth(), lcd.getHeight());
	lcd.setFont(u8g2_font_fub17_tf);
	lcd.setDrawColor(BLACK);
	lcd.setCursor(10, 40);
	lcd.print("hii :3");
	lcd.sendBuffer();

	Keyboard.begin();

	Serial.begin();
}

void loop() {
	for (int i = 0; i < N_KEYS_GKOS; i++) {
		keys_gkos[i]->update();
		if (keys_gkos[i]->pressed()) {
			gkos_keycode |= GKOS_MASKS[i];
			gkos_keycode_max |= GKOS_MASKS[i];
		}
		if (keys_gkos[i]->released()) {
			gkos_keycode &= ~(GKOS_MASKS[i]);
			if (gkos_keycode == 0) {
				gkos_dirty = true;
			}
		}
	}
	for (int i = 0; i < KEYS_MOUSE_N; i++) {
		keys_mouse[i]->update();
	}
	key_menu.update();

	if (gkos_dirty) {
		uint8_t keypress = Keys::ALPHA[gkos_keycode_max];
		Keyboard.press(keypress);
		Keyboard.releaseAll();
		gkos_keycode_max = 0;
		gkos_dirty = false;
	}
}