#include <iostream>;
#include <fstream>;
#include <ctime>;
#include <cstring>
#include "vigenere.h";
#include "kasiski.h";
#define FIRST_LETTER 'a'
#define LAST_LETTER 'z'
using namespace std;


bool is_letter(char symbol) {
	if ((symbol >= FIRST_LETTER && symbol <= LAST_LETTER) ||
		symbol >= toupper(FIRST_LETTER) && symbol <= toupper(LAST_LETTER)) {
		return true;
	}
	return false;
}

char* read_file(char* filename, long& file_length) {
	ifstream fin(filename);
	fin.seekg(0, fin.end);
	file_length = fin.tellg();
	fin.seekg(0, fin.beg);
	char* text = new char[file_length + 1];
	text[0] = '\0';
	char* line = new char[file_length + 1];
	while (fin.getline(line, file_length - strlen(text) + 1)) {
		strcat(text, line);
	}

	fin.close();
	delete[] line;
	return text;
}

char* transform_text(char* text, long& text_length) {
	long transformed_text_length = 0;

	for (int i = 0; i < text_length; i++) {
		if (is_letter(text[i])){
			transformed_text_length++;
		}
	}

	char* transformed_text = new char[transformed_text_length + 1];
	long j = 0;
	for (long i = 0; i < text_length; i++) {
		if (is_letter(text[i])) {
			transformed_text[j] = tolower(text[i]);
			j++;
		}
	}
	transformed_text[j] = '\0';
	text_length = transformed_text_length;
	return transformed_text;
}

void write_results(char* filename, int* x, int x_size, int* y, int y_size, double** results, double** results2) {
	ofstream fout(filename);
	fout.precision(6);

	for (int i = 0; i < x_size; i++) {
		for (int j = 0; j < y_size; j++) {
			fout << "Key length: " << x[i] << "; Text length: " << y[j] << "; Procent of Success: " << results[i][j] << ";" << endl;
		}
	}

	fout.close();
}

int main() {
	srand(time(NULL));
	double original_frequences[] = {
		0.08167, 0.01492, 0.02782,
		0.04253, 0.12702, 0.0228,
		0.02015, 0.06094, 0.06966,
		0.00153, 0.00772, 0.04025,
		0.02406, 0.06749, 0.07507,
		0.01929, 0.00095, 0.05987,
		0.06327, 0.09056, 0.02758,
		0.00978, 0.0236, 0.0015,
		0.01974, 0.00074
	};

	long file_length;
	char* original_file = read_file("001ssb.txt", file_length);
	cout << "file is read\n";
	char* transformed_file = transform_text(original_file, file_length);
	delete[] original_file;



	int text_length[] = { 100 };
	int text_length_num = sizeof(text_length) / 4;
	cout << text_length_num << endl;
	int key_length_num = 3;
	int* key_length = new int[key_length_num];
	double** results = new double*[key_length_num];
	double** results2 = new double*[key_length_num];
	int M = 100;
	int start_index;
	int analysed_key_length;
	kasiski K;


	for (int key_index = 0; key_index < key_length_num; key_index++) {
		results2[key_index] = new double[text_length_num];
		results[key_index] = new double[text_length_num];
		key_length[key_index] = key_index * 3 + 1;
		char* key = new char[key_length[key_index]];


		for (int text_index = 0; text_index < text_length_num; text_index++) {

			results[key_index][text_index] = 0;
			results2[key_index][text_index] = 0;
			char* text = new char[text_length[text_index] + 1];
			char* cipher_text = new char[text_length[text_index] + 1];
			char* analysed_text = new char[text_length[text_index] + 1];

			for (int j = 0; j < M; j++) {
				start_index = rand() % (file_length - text_length[text_index]);
				for (int k = 0; k < text_length[text_index]; k++) {
					text[k] = transformed_file[start_index + k];
				}
				text[text_length[text_index]] = '\0';

				for (int k = 0; k < key_length[key_index]; k++) {
					key[k] = rand() % (LAST_LETTER - FIRST_LETTER + 1) + FIRST_LETTER;
				}

				vigenere V(key, key_length[key_index]);
				V.encrypt(text, cipher_text, text_length[text_index]);
				analysed_key_length = K.analyse_key_length(cipher_text, text_length[text_index]);

				if (key_length[key_index] == analysed_key_length) {
					K.analyse_cipher_text(cipher_text, analysed_text, text_length[text_index], original_frequences);

					if (strcmp(text, analysed_text) == 0) {
						results[key_index][text_index]++;
					}
					else {
						results2[key_index][text_index]++;
					}
				}

			}
			results[key_index][text_index] /= M;
			cout << key_index << "-" << text_index << " is done\n";
			delete[] text;
			delete[] cipher_text;
			delete[] analysed_text;
		}

		delete[] key;
	}


	write_results("result.txt", key_length, key_length_num, text_length, text_length_num, results, results2);


	for (int i = 0; i < key_length_num; i++) {
		delete[] results[i];
	}
	delete[] results;
	delete[] key_length;


	delete[] transformed_file;
	return 0;
}