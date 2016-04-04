#pragma once
void flush_cin_buffer();
void keep_window_open();
void keep_window_open(const char* msg);

int get_integer();
int get_integer_range(int, int);
int get_integer_range(int, int, const char*);