#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>


struct Book {
	std::string title;
	std::string first_name;
	std::string last_name;
	int word_count;
	float frequency[26];
	int line_count;

};

int main() {
	std::string filename;
	std::string line;
	std::ifstream file;

	do {
		std::cout << "Enter filename: ";
		std::cin >> filename;
		file.open(filename);
	} while (file.fail());

	int i = 0;
	int space_count = 0;
	int char_count = 0;

	struct Book b1;
	for (int i = 0; i < 26; i++)
	{
		b1.frequency[i] = 0;
	}


	while (!(file.eof())) {

		getline(file, line);
		std::cout << line << std::endl;

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
			/*b1.last_name = line.substr(0, line.find(' '));
			b1.first_name = line.substr(line.find(' '), line.length());*/
		}
		else if (line != "Contents:"){
			for (int j = 0; j < line.size(); j++) {
				if (int(line[j]) >= 97) 
					b1.frequency[int(line[j]) - 97] += 1;
				else
					b1.frequency[int(line[j]) - 65] += 1;
				if (line[j] == ' ')
					space_count++;
				char_count++;
			}
		}
		i++;
	}
	b1.line_count = i - 3;
	b1.word_count = i + space_count;
	for (i = 0; i < 26; i++)
	{
		b1.frequency[i] /= char_count;
		b1.frequency[i] *= 100;
	}

	std::cout << "Title: " << b1.title << std::endl;
	std::cout << "First Name: " << b1.first_name << std::endl;
	std::cout << "Last Name: " << b1.last_name << std::endl;
	std::cout << "Line Count: " << b1.line_count << std::endl;
	std::cout << "Word Count: " << b1.word_count << std::endl;
	for (i = 0; i < 26; i++)
	{
		std::cout << char(i + 97) << ": " << b1.frequency[i] << "%" << std::endl;
	}

	file.close();

}