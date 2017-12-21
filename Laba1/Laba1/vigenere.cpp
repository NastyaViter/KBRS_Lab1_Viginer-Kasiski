#include "vigenere.h";
#define FIRST_LETTER 'a'
#define LAST_LETTER 'z'

vigenere::vigenere(char* _key, int _key_length) {
	key_length = _key_length;
	key = new char[key_length];
	for (int i = 0; i < key_length; i++) {
		key[i] = tolower(_key[i]);
	}
}

int vigenere::cipher_symbol(int old_symbol, int i) {
	int move = key[i % key_length] - FIRST_LETTER;
	int new_symbol = old_symbol + move;
	if (new_symbol > LAST_LETTER) {
		new_symbol -= (LAST_LETTER - FIRST_LETTER + 1);
	}
	return new_symbol;
}

int vigenere::decipher_symbol(int old_symbol, int i) {
	int move = key[i % key_length] - FIRST_LETTER;
	int new_symbol = old_symbol - move;
	if (new_symbol < FIRST_LETTER) {
		new_symbol += (LAST_LETTER - FIRST_LETTER + 1);
	}
	return new_symbol;
}

void vigenere::encrypt(char* text, char* cipher_text, int text_length) {
	for (int i = 0; i < text_length; i++) {
		cipher_text[i] = cipher_symbol(text[i], i);
	}
	cipher_text[text_length] = '\0';
}

char* vigenere::decrypt(char* cipher_text, int text_length) {
	char* text = new char[text_length + 1];

	for (int i = 0; i < text_length; i++) {
		text[i] = decipher_symbol(cipher_text[i], i);
	}
	text[text_length] = '\0';

	return text;
}