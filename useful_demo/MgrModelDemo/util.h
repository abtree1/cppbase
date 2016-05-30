#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(obj) if(obj){delete (obj);(obj)=NULL;}
#endif

extern inline int RandInt(int min,int max);