#pragma once
#include <vector>;
#include <map>;
#include <ctype.h>;
class kasiski{
public:
	int analyse_key_length(char* cipher_text, int text_length);
	void analyse_cipher_text(char* cipher_text, char* decipher_text, int text_length, double* original_frequences);
	int key_length;
};