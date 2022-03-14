#pragma once

namespace functions {
	void q_sleep(int ms);
	void smoothing(double delay, double control_time, float x, float y);
	float c_amount(float value, float perc);
	float get_scope(float value);
	float get_barrel(float value);
	float spray(float sens, int fov, float value);

	void key_input(int key);
	void send_space();
	void sendKeyPress();
	float convert(float usersens, int fov, float val);
	void move_mouse(double speed, float x, float y);
}