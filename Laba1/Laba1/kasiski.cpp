#include "kasiski.h";
#define LGRAMM 3
#define ALPHABET_LENGTH 26
#define FIRST_LETTER 'a'
#define MAX_GCD 100
#include <iostream>;


using namespace std;

int gcd(int a, int b) {
	while (a != b) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}

int kasiski::analyse_key_length(char* cipher_text, int text_length) {

	map<int, vector<int> > lgramms;
	map<int, vector<int> >::iterator it;
	vector<int> distances;
	int* gcd_counter;
	int tmp_key_value, tmp_gcd;

	for (int i = 0; i < text_length; i++) {
		cipher_text[i] -= FIRST_LETTER;
	}


	for (int i = 0; i <= text_length - LGRAMM; i++) {
		tmp_key_value = cipher_text[i] * ALPHABET_LENGTH * ALPHABET_LENGTH
			+ cipher_text[i + 1] * ALPHABET_LENGTH + cipher_text[i + 2];
		it = lgramms.find(tmp_key_value);
		if (it != lgramms.end()) {
			it->second.push_back(i);
		}
		else {
			lgramms.insert(pair<int, vector<int> >(tmp_key_value, vector<int>(1, i)));
		}
	}



	for (it = lgramms.begin(); it != lgramms.end(); it++) {
		if (it->second.size() > 1) {

			for (int i = 0; i < it->second.size() - 1; i++) {
				distances.push_back(it->second[i + 1] - it->second[i]);
			}
		}
	}


	if (distances.empty()) {
		return false;
	}



	gcd_counter = new int[MAX_GCD + 1];
	for (int i = 0; i < MAX_GCD + 1; i++) {
		gcd_counter[i] = 0;
	}


	for (int i = 0; i < distances.size(); i++) {
		for (int j = i + 1; j < distances.size(); j++) {
			tmp_gcd = gcd(distances[i], distances[j]);
			if (tmp_gcd <= MAX_GCD) {
				gcd_counter[tmp_gcd]++;
			}
		}
	}

	key_length = 0;
	for (int i = 2; i <= MAX_GCD; i++) {
		if (gcd_counter[i] > gcd_counter[key_length]) {
			key_length = i;
		}
	}

	delete[] gcd_counter;
	lgramms.clear();

	return key_length;
}

void kasiski::analyse_cipher_text(char* cipher_text, char* decipher_text, int text_length, double* original_frequences){
	double** cipher_frequences = new double*[key_length];
	int* move = new int[key_length];
	double min_distance, distance;

	for (int i = 0; i < key_length; i++) {
		cipher_frequences[i] = new double[ALPHABET_LENGTH];
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			cipher_frequences[i][j] = 0;
		}
		move[i] = 0;
	}

	for (int i = 0; i < text_length; i++) {
		cipher_frequences[i%key_length][cipher_text[i]]++;
	}

	for (int i = 0; i < text_length%key_length; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			cipher_frequences[i][j] /= (text_length / key_length + 1);
		}
	}
	for (int i = text_length%key_length; i < key_length; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			cipher_frequences[i][j] /= (text_length / key_length);
		}
	}


	for (int i = 0; i < key_length; i++) {
		min_distance = 2 * ALPHABET_LENGTH;
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			distance = 0;
			for (int k = 0; k < ALPHABET_LENGTH; k++) {
				distance += abs(original_frequences[k] - cipher_frequences[i][(k + j) % ALPHABET_LENGTH]);
			}
			if (distance < min_distance) {
				min_distance = distance;
				move[i] = j;
			}
		}
	}

	for (int i = 0; i < text_length; i++) {
		decipher_text[i] = cipher_text[i] - move[i%key_length] + FIRST_LETTER;
		if (decipher_text[i] < FIRST_LETTER) {
			decipher_text[i] += ALPHABET_LENGTH;
		}
	}
	decipher_text[text_length] = '\0';

	for (int i = 0; i < key_length; i++) {
		delete[] cipher_frequences[i];
	}
	delete[] cipher_frequences;
	delete[] move;
}