#pragma once

typedef const char CCHAR;
typedef unsigned int UINT32;

namespace encrypt{
	int HmacEncode(CCHAR* type, CCHAR* key, UINT32 key_len, CCHAR* input, UINT32 input_len, unsigned char* output, UINT32* output_len);
}