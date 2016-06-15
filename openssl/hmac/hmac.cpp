#include "hmac.h"
#include "openssl/hmac.h"
#include <string>
#include <iostream>

using namespace std;

namespace encrypt{
	int HmacEncode(CCHAR* type, CCHAR* key, UINT32 key_len, CCHAR* input, UINT32 input_len, unsigned char* output, UINT32* output_len){
		const EVP_MD* engine = nullptr;
		if(strcmp("sha512", type) == 0){
			engine = EVP_sha512();
		}else if(strcmp("sha256", type) == 0){
			engine = EVP_sha256();
		}else if(strcmp("sha", type) == 0){
			engine = EVP_sha1();
		}else if(strcmp("md5", type) == 0){
			engine = EVP_md5();
		}else if(strcmp("sha224", type) == 0){
			engine = EVP_sha224();
		}else if(strcmp("sha384", type) == 0){
			engine = EVP_sha384();
		}else if(strcmp("sha", type) == 0){
			engine = EVP_sha();
		}else if(strcmp("md2", type) == 0){
			engine = EVP_mdc2();
		}else{
			cout << "Algorithm " << type << " is not supported by this program!" << endl;
			return -1;
		}

		//output = new unsigned char[1024];

		HMAC_CTX ctx;
		HMAC_CTX_init(&ctx);
		HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);
		HMAC_Update(&ctx, (unsigned char*)input, input_len);

		HMAC_Final(&ctx, output, output_len);
		HMAC_CTX_cleanup(&ctx);

		return 0;
	}
}