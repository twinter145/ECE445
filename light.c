/*
	LED Control, Bluetooth interface, and button input program
	
	Thomas Winter
	
 */

//#define PCB
#define BREADBOARD

#ifdef BREADBOARD
#define CLOCK_MASK	0x04
#define LED_MASK	0x02
#define DATA_MASK	0x02
#define GREEN_LED	A0
#define RED_LED		A1
#endif // BREADBOARD

#ifdef PCB
#define CLOCK_MASK	0x40
#define LED_MASK	0x01
#define DATA_MASK	0x80
#define GREEN_LED	A0
#define RED_LED		A1
#endif // PCB

const long temp_data[] PROGMEM = {
0x00006cff, 0x00006eff, 0x000070ff, 0x000071ff, 0x000073ff, 0x000074ff, 0x000076ff, 0x000077ff,
0x000079ff, 0x00007aff, 0x00007cff, 0x00007dff, 0x00007eff, 0x000080ff, 0x000081ff, 0x000082ff,
0x000084ff, 0x000385ff, 0x000786ff, 0x000a88ff, 0x000e89ff, 0x00118aff, 0x00158bff, 0x00188dff,
0x001b8eff, 0x001e8fff, 0x002190ff, 0x002491ff, 0x002792ff, 0x002a93ff, 0x002d95ff, 0x003096ff,
0x003297ff, 0x003598ff, 0x003799ff, 0x003a9aff, 0x003d9bff, 0x003f9cff, 0x00419dff, 0x00449eff,
0x00469fff, 0x0048a0ff, 0x004ba1ff, 0x004da2ff, 0x004fa3ff, 0x0051a4ff, 0x0053a5ff, 0x0055a6ff,
0x0057a7ff, 0x0059a8ff, 0x005ba9ff, 0x005da9ff, 0x005faaff, 0x0061abff, 0x0063acff, 0x0065adff,
0x0067aeff, 0x0069afff, 0x006ab0ff, 0x006cb0ff, 0x006eb1ff, 0x0070b2ff, 0x0071b3ff, 0x0073b4ff,
0x0075b4ff, 0x0076b5ff, 0x0078b6ff, 0x007ab7ff, 0x007bb8ff, 0x007db8ff, 0x007eb9ff, 0x0080baff,
0x0081bbff, 0x0083bbff, 0x0084bcff, 0x0086bdff, 0x0087beff, 0x0089beff, 0x008abfff, 0x008bc0ff,
0x008dc1ff, 0x008ec1ff, 0x0090c2ff, 0x0091c3ff, 0x0092c3ff, 0x0094c4ff, 0x0095c5ff, 0x0096c5ff,
0x0097c6ff, 0x0099c7ff, 0x009ac7ff, 0x009bc8ff, 0x009dc9ff, 0x009ec9ff, 0x009fcaff, 0x00a0cbff,
0x00a1cbff, 0x00a3ccff, 0x00a4cdff, 0x00a5cdff, 0x00a6ceff, 0x00a7ceff, 0x00a8cfff, 0x00aad0ff,
0x00abd0ff, 0x00acd1ff, 0x00add1ff, 0x00aed2ff, 0x00afd3ff, 0x00b0d3ff, 0x00b1d4ff, 0x00b2d4ff,
0x00b3d5ff, 0x00b4d6ff, 0x00b5d6ff, 0x00b6d7ff, 0x00b7d7ff, 0x00b8d8ff, 0x00b9d8ff, 0x00bad9ff,
0x00bbdaff, 0x00bcdaff, 0x00bddbff, 0x00bedbff, 0x00bfdcff, 0x00c0dcff, 0x00c1ddff, 0x00c2ddff,
0x00c3deff, 0x00c4deff, 0x00c5dfff, 0x00c6dfff, 0x00c7e0ff, 0x00c8e0ff, 0x00c9e1ff, 0x00cae1ff,
0x00cae2ff, 0x00cbe3ff, 0x00cce3ff, 0x00cde4ff, 0x00cee4ff, 0x00cfe5ff, 0x00d0e5ff, 0x00d1e5ff,
0x00d1e6ff, 0x00d2e6ff, 0x00d3e7ff, 0x00d4e7ff, 0x00d5e8ff, 0x00d6e8ff, 0x00d6e9ff, 0x00d7e9ff,
0x00d8eaff, 0x00d9eaff, 0x00daebff, 0x00daebff, 0x00dbecff, 0x00dcecff, 0x00ddedff, 0x00ddedff,
0x00deedff, 0x00dfeeff, 0x00e0eeff, 0x00e1efff, 0x00e1efff, 0x00e2f0ff, 0x00e3f0ff, 0x00e4f1ff,
0x00e4f1ff, 0x00e5f1ff, 0x00e6f2ff, 0x00e6f2ff, 0x00e7f3ff, 0x00e8f3ff, 0x00e9f4ff, 0x00e9f4ff,
0x00eaf4ff, 0x00ebf5ff, 0x00ebf5ff, 0x00ecf6ff, 0x00edf6ff, 0x00eef7ff, 0x00eef7ff, 0x00eff7ff,
0x00f0f8ff, 0x00f0f8ff, 0x00f1f9ff, 0x00f2f9ff, 0x00f2f9ff, 0x00f3faff, 0x00f4faff, 0x00f4fbff,
0x00f5fbff, 0x00f6fbff, 0x00f6fcff, 0x00f7fcff, 0x00f8fdff, 0x00f8fdff, 0x00f9fdff, 0x00f9feff,
0x00fafeff, 0x00fbfeff, 0x00fbffff, 0x00fcffff, 0x00ffffff, 0x00fffbff, 0x00fffaff, 0x00fff9ff,
0x00fff9fe, 0x00fff8fd, 0x00fff7fc, 0x00fff7fb, 0x00fff6fa, 0x00fff6f9, 0x00fff5f8, 0x00fff5f7,
0x00fff4f6, 0x00fff4f5, 0x00fff3f4, 0x00fff3f3, 0x00fff2f3, 0x00fff2f2, 0x00fff1f1, 0x00fff1f0,
0x00fff0f0, 0x00fff0ef, 0x00fff0ee, 0x00ffefed, 0x00ffefed, 0x00ffeeec, 0x00ffeeec, 0x00ffeeeb,
0x00ffedea, 0x00ffedea, 0x00ffede9, 0x00ffece9, 0x00ffece8, 0x00ffece7, 0x00ffebe7, 0x00ffebe6,
0x00ffebe6, 0x00ffebe5, 0x00ffeae5, 0x00ffeae4, 0x00ffeae4, 0x00ffe9e3, 0x00ffe9e3, 0x00ffe9e3,
0x00ffe9e2, 0x00ffe8e2, 0x00ffe8e1, 0x00ffe8e1, 0x00ffe8e0, 0x00ffe7e0, 0x00ffe7e0
};

// Breadboard config
#ifdef BREADBOARD
int clock = 10;
int data = 9;
int temp_down = 2;
int temp_up = 3;
int brightness_down = 4;
int brightness_up = 5;
int gradient_up = 7;
int gradient_down = 6;
#endif

// PCB config
#ifdef PCB
int clock = 6;
int data = 7;
int temp_down = 9;
int temp_up = 8;
int brightness_down = 11;
int brightness_up = 10;
int gradient_up = 12;
int gradient_down = 13;
#endif

int frame_count = 0;
int bit_count = 0;
int press_count = 101;
int temp_count = 254;
int gradient_position = 0;
int brightness = 2;
int max_global_brightness = 31;
int serial_data;

boolean ready = false;

const unsigned long start_frame = 0x00000000;
unsigned long color;

unsigned long strip[61];
//unsigned long strip[183];

unsigned char in_buf[4];
unsigned char out_buf[4];

#ifdef BREADBOARD
void send_frame(unsigned long frame) {
	bit_count = 0;
		
	while(bit_count < 32) {
		if(frame & 0x80000000) {
			PORTB |= DATA_MASK;
		} else {
			PORTB &= ~DATA_MASK;
		}
		frame <<= 1;
		bit_count++;
		PORTB |= CLOCK_MASK;
		PORTB &= ~CLOCK_MASK;
	}
	PORTB &= ~DATA_MASK;
}
#endif // BREADBOARD

#ifdef PCB
void send_frame(unsigned long frame) {
	bit_count = 0;
		
	while(bit_count < 32) {
		if(frame & 0x80000000) {
			PORTD |= DATA_MASK;
		} else {
			PORTD &= 0x7f; // ~DATA_MASK
		}
		frame <<= 1;
		bit_count++;
		PORTD |= CLOCK_MASK;
		PORTD &= 0xbf; // ~CLOCK_MASK
	}
	PORTD &= 0x7f; // ~DATA_MASK
}
#endif // PCB

void send_strip(unsigned long * strip) {
	frame_count = 0;
	send_frame(start_frame);
	while(frame_count < 61) {
		send_frame(strip[frame_count]);
		frame_count++;
	}
}

void set_strip(unsigned long * strip, unsigned long color) {
	int diff;
	float value;
	unsigned long temp_color;
	unsigned long red;
	unsigned long green;
	unsigned long blue;
	
	red = color & 0x000000ff;
	green = (color & 0x0000ff00) >> 8;
	blue = (color & 0x00ff0000) >> 16;
	temp_color = color;
	frame_count = 0;
	while(frame_count < 60) {
		diff = gradient_position - frame_count;
		if(diff < 0) {
			diff *= -1;
		}
		diff = 60 - diff;
		temp_color &= 0xff000000;
		value = red;
		value /= 60;
		value *= diff;
		value += 0.5;
		temp_color += (unsigned long)value;
		value = green;
		value /= 60;
		value *= diff;
		value += 0.5;
		temp_color += (unsigned long)value << 8;
		value = blue;
		value /= 60;
		value *= diff;
		value += 0.5;
		temp_color += (unsigned long)value << 16;
		strip[frame_count] = temp_color;
		//strip[frame_count] = color;
		frame_count++;
	}
}

#define BLUETOOTH
//#define RPI

#ifdef BLUETOOTH
void send_state() {
	out_buf[0] = 0x00;
	out_buf[1] = (unsigned char)(press_count + 1);
	out_buf[2] = (unsigned char)(0xe0 + brightness);
	out_buf[3] = (unsigned char)(0xc0 + gradient_position);
	Serial.write(out_buf, 4);
}
#endif // BLUETOOTH

#ifdef RPI
void send_state() {
	Serial.print("Color Temp: ");
	Serial.println(press_count + 1, DEC);
	Serial.print("Brightness: ");
	Serial.println(brightness, DEC);
	Serial.print("Gradient Pos: ");
	Serial.println(gradient_position, DEC);
	Serial.print("\n");
}
#endif // RPI

void display_state() {
	press_count = (int)in_buf[1] - 1;
	brightness = (int)in_buf[2] & 0x1f;
	gradient_position = (int)in_buf[3] & 0x3f;
	set_strip(strip, pgm_read_dword_near(temp_data + press_count) + (((unsigned long)in_buf[2]) << 24));
	send_strip(strip);
}

void setup() {
	pinMode(clock, OUTPUT);     
	pinMode(data, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	pinMode(temp_down, INPUT);
	pinMode(temp_up, INPUT);
	pinMode(brightness_down, INPUT);
	pinMode(brightness_up, INPUT);
	pinMode(gradient_down, INPUT);
	pinMode(gradient_up, INPUT);

	digitalWrite(GREEN_LED, HIGH);
	digitalWrite(RED_LED, HIGH);

	Serial.begin(9600);
	//Serial.write("sending test\n");

	strip[60] = 0xffffffff;
	set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
	send_strip(strip);
	send_state();
}

//#define TOGGLE_TEST

#ifdef PCB
void loop() {
	#ifdef TOGGLE_TEST
	PORTD = CLOCK_MASK;
	PORTD = 0x00;
	#endif // TOGGLE_TEST
	
	#ifndef TOGGLE_TEST
	while(Serial.available()) {
		serial_data = Serial.read();
		//Serial.write((unsigned char)serial_data);
		if(serial_data == 0) {
			digitalWrite(A0, LOW);
			ready = true;
			in_buf[0] = 0x00;
			in_buf[1] = 0x00;
			in_buf[2] = 0x00;
			in_buf[3] = 0x00;
		} else {
			digitalWrite(A0, HIGH);
			if(ready) {
				if(in_buf[1] == 0) {
					in_buf[1] = (unsigned char)serial_data;
				} else if(in_buf[2] == 0) {
					in_buf[2] = (unsigned char)serial_data;
				} else if(in_buf[3] == 0) {
					in_buf[3] = (unsigned char)serial_data;
					gradient_position = (int)in_buf[3] & 0x3f;
					display_state();
					//temp_data_long = (long)temp_data;
					/*Serial.write(in_buf, 4);
					Serial.print("temp_data: ");
					Serial.println((long)temp_data, DEC);
					Serial.print("press_count: ");
					Serial.println(press_count, DEC);
					send_state();*/
					ready = false;
				}
			}
		}
	}
	if(!(PINB & 0x01)) { //digitalRead(temp_up) == LOW) {
		press_count++;
		if(press_count > temp_count) {
			press_count = temp_count;
		} else if(press_count < 0) {
			press_count = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(3);
	} else if(!(PINB & 0x02)) { //digitalRead(temp_down) == LOW) {
		press_count--;
		if(press_count > temp_count) {
			press_count = temp_count;
		} else if(press_count < 0) {
			press_count = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(3);
	} else if(!(PINB & 0x08)) { //digitalRead(brightness_down) == LOW) {
		brightness--;
		if(brightness < 0) {
			brightness = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		delay(150);
	} else if(!(PINB & 0x04)) { //digitalRead(brightness_up) == LOW) {
		brightness++;
		if(brightness > max_global_brightness) {
			brightness = max_global_brightness;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		delay(150);
	} else if(!(PINB & 0x10)) { //digitalRead(gradient_down) == LOW) {
		gradient_position--;
		if(gradient_position < 0) {
			gradient_position = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		//delay(5);
	} else if(!(PINB & 0x20)) { //digitalRead(gradient_up) == LOW) {
		gradient_position++;
		if(gradient_position > 59) {
			gradient_position = 59;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		//delay(5);
	}
	#endif // !TOGGLE_TEST
}
#endif // PCB

#ifdef BREADBOARD
void loop() {
	while(Serial.available()) {
		serial_data = Serial.read();
		//Serial.write((unsigned char)serial_data);
		if(serial_data == 0) {
			digitalWrite(A0, LOW);
			ready = true;
			in_buf[0] = 0x00;
			in_buf[1] = 0x00;
			in_buf[2] = 0x00;
			in_buf[3] = 0x00;
		} else {
			digitalWrite(A0, HIGH);
			if(ready) {
				if(in_buf[1] == 0) {
					in_buf[1] = (unsigned char)serial_data;
				} else if(in_buf[2] == 0) {
					in_buf[2] = (unsigned char)serial_data;
				} else if(in_buf[3] == 0) {
					in_buf[3] = (unsigned char)serial_data;
					gradient_position = (int)in_buf[3] & 0x3f;
					display_state();
					//temp_data_long = (long)temp_data;
					/*Serial.write(in_buf, 4);
					Serial.print("temp_data: ");
					Serial.println((long)temp_data, DEC);
					Serial.print("press_count: ");
					Serial.println(press_count, DEC);
					send_state();*/
					ready = false;
				}
			}
		}
	}
	if(digitalRead(temp_up) == LOW) {
		press_count++;
		if(press_count > temp_count) {
			press_count = temp_count;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(150);
	} else if(digitalRead(temp_down) == LOW) {
		press_count--;
		if(press_count < 0) {
			press_count = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(150);
	} else if(digitalRead(brightness_down) == LOW) {
		brightness--;
		if(brightness < 0) {
			brightness = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		delay(150);
	} else if(digitalRead(brightness_up) == LOW) {
		brightness++;
		if(brightness > max_global_brightness) {
			brightness = max_global_brightness;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		delay(150);
	} else if(digitalRead(gradient_down) == LOW) {
		gradient_position--;
		if(gradient_position < 0) {
			gradient_position = 0;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(100);
	} else if(digitalRead(gradient_up) == LOW) {
		gradient_position++;
		if(gradient_position > 59) {
			gradient_position = 59;
		}
		set_strip(strip, pgm_read_dword_near(temp_data + press_count) + ((((unsigned long)brightness) << 24) + 0xe0000000));
		send_strip(strip);
		send_state();
		//delay(100);
	}
}
#endif // BREADBOARD

/*
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/














