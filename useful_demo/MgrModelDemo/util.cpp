#include <stdlib.h>
#include "util.h"

inline int RandInt(int min,int max){
	return (int)(min + (rand()/(RAND_MAX+1.0))*(max - min + 1));
}