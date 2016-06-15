#include<iostream>
#include<fstream>
#include<string>
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"
#include "openssl/bio.h"
using namespace std;

void generateKey(){
	/*生成公钥*/
	RSA* rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
	BIO *bp = BIO_new(BIO_s_file());
	BIO_write_filename(bp, "public.pem");
	PEM_write_bio_RSAPublicKey(bp, rsa);
	BIO_free_all(bp);
	/*生成私钥*/
	unsigned char passwd[] = "1234";
	bp = BIO_new_file("private.pem", "w+");
	PEM_write_bio_RSAPrivateKey(bp, rsa, EVP_des_ede3(), passwd, 4, NULL, NULL);
	BIO_free_all(bp);
	RSA_free(rsa);
}

string bio_read_privateKey(string data){
	OpenSSL_add_all_algorithms();
	BIO* bp = BIO_new(BIO_s_file());
	BIO_read_filename(bp, "private.pem");
	unsigned char passwd[] = "1234";
	RSA* rsaK = PEM_read_bio_RSAPrivateKey(bp, NULL, NULL, passwd);
	if(NULL == rsaK){
		perror("read key file fail!");
	}else{
		printf("read success! \n");
	}
	int nLen = RSA_size(rsaK);
	unsigned char *pEncode = new unsigned char[nLen + 1];
	int ret = RSA_private_decrypt(data.length(), (const unsigned char*)data.c_str(), pEncode, rsaK, RSA_PKCS1_PADDING);
	char buf[1024];
	for(int i = 0; i< nLen; ++i){
		sprintf(buf+i*2, "%02x", pEncode[i]);
	}
	buf[nLen*2] = 0;
	string strRet(buf);
	delete [] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;
}

string bio_read_publicKey(string data){
	OpenSSL_add_all_algorithms();
	BIO* bp = BIO_new(BIO_s_file());
	BIO_read_filename(bp, "public.pem");
	RSA* rsaK = PEM_read_bio_RSAPublicKey(bp, NULL, NULL, NULL);
	if(NULL == rsaK){
		perror("read key file fail!");
	}else{
		printf("read success!");
		int nLen = RSA_size(rsaK);
		printf("len:%d \n", nLen);
	}
	int nLen = RSA_size(rsaK);
	char* pEncode = new char(nLen + 1);
	int ret = RSA_public_encrypt(data.length(), (const unsigned char*)data.c_str(), (unsigned char*)pEncode, rsaK, RSA_PKCS1_PADDING);
	char buf[1024];
	for(int i = 0; i< nLen; ++i){
		sprintf(buf+i*2, "%02x", pEncode[i]);
	}
	buf[nLen*2] = 0;
	string strRet(buf);
	delete [] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;
}

void encryptFile(string inputFile, string outputFile){
	ifstream file(inputFile.c_str());
	ofstream outfile(outputFile.c_str());
	string tsum;
	string ss;
	while (getline(file, ss)){
		tsum.append(ss.append("\n"));
	}
	cout << "will encrypto data: " << tsum << endl;
	string mw = bio_read_publicKey(tsum);
	cout << mw << endl;
	outfile << mw;
	outfile.flush();
	outfile.close();
	file.close();
}

void decryptFile(string inputFile, string outputFile){
	ifstream file(inputFile.c_str());
	ofstream outfile(outputFile.c_str());
	string tsum,ss;
	while(getline(file, ss)){
		tsum.append(ss);
	}
	string cw = bio_read_privateKey(tsum);
	cout << "decrypto data: " << cw;
	outfile << cw;
	outfile.flush();
	outfile.close();
	file.close();
}

int main(){
	//generateKey();

	string str = "asda[jfkosdjaiojfiojjcioajoscasjcasojdioasjiodjaspcopajsopdjasopjdpaskdopas";
	printf("origin string: %s \n", str.c_str());
	string m = bio_read_publicKey(str);
	printf("encrypto string: \n--------%s---------\n\n", m.c_str());
	string miwen = m;
	string c = bio_read_privateKey(miwen);
	printf("decrypto string: \n--------%s---------\n\n", c.c_str());
	
	/*printf("----------encrypto file--------------\n");
	encryptFile("e:/before.txt", "e:/my.txt");
	printf("----------finished--------------\n");
	printf("----------decrypto file--------------\n");
	decryptFile("e:/my.txt", "e:/after.txt");
	printf("----------finished--------------\n");*/
	return 0;
}