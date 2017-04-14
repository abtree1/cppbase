#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFF_SIZE 64

extern void select();
extern void eventselect();
extern void overlapevent();
extern void overlapcompletion();
extern void completionport();