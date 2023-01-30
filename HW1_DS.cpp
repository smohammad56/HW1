#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;


struct Book {
	string title;
	string first_name;
	string last_name;
	int word_count;
	double frequency;
	int line_count;

};



int main() {
	string filename;
	string line;
	ifstream file;

	do {
		cout << "Enter filename: ";
		cin >> filename;
		file.open(filename);
	} while (file.fail());

	int i = 0;

	struct Book b1;
	int letter_array[26];

	while (!(file.eof())) {

		getline(file, line);
		cout << line << endl;

		if (i == 0) {
			b1.title = line;
		}
		else if (i == 1) {
			int flag = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					flag = 1;
				}
				if (flag == 1) {
					b1.last_name += line[i];
				}
				if (flag == 0)
				{
					b1.first_name += line[i];
				}
			}
			b1.last_name.erase(0,1);
		}
		else if (line != "Contents:"){
			for (int i = 0; i < line.size(); i++) {
				letter_array[int(line[i]) - 97] += 1;


			}

		}
		i++;
	}

	cout << b1.title;
	cout << b1.first_name;
	cout << b1.last_name;
	cout << letter_array;

}