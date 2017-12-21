#pragma once
#include <stdio.h>;
#include <ctype.h>;
class vigenere {
private:
	char* key;
	int key_length;
	int cipher_symbol(int old_symbol, int i);
	int decipher_symbol(int old_symbol, int i);

public:
	void encrypt(char* text, char* cipher_text, int n);
	char* decrypt(char* text, int n);
	vigenere(char*, int);
	~vigenere() {
		delete key;
	}
};