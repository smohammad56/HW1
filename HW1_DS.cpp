#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>


struct Book {
	std::string title;
	std::string full_name;
	std::string first_name;
	std::string last_name;
	int word_count;
	int line_count;
	float frequency[26];

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
 
	int char_count = 0;
	int char_value = 0;



	std::string full_name;
	std::string first_name;
	std::string last_name;
	std::string full_name1 = "";
	std::string first_name1 = "";
	std::string last_name1 = "";



	struct Book b1;
	b1.word_count = 0;
	b1.line_count = 0;
	for (int i = 0; i < 26; i++)
	{
		b1.frequency[i] = 0;
	}

	while (!(file.eof())) {

		getline(file, line);
		std::cout << line << std::endl;

		if (b1.line_count == 0) {
			b1.title = line;
		}
		else if (b1.line_count == 1) {
			int flag = 0;
			full_name1 = line;
			for (int k = 0; k < line.size(); k++) {
				if (line[k] == ' ') {
					flag = 1;
				}
				if (flag == 1) {
					last_name1 += line[k];
				}
				if (flag == 0)
				{
					first_name1 += line[k];
				}
			}
			last_name1.erase(0,1);

			full_name = full_name1;
			first_name = first_name1;
			last_name = last_name1;
			/*b1.last_name = line.substr(0, line.find(' '));
			b1.first_name = line.substr(line.find(' '), line.length());*/
		}
		else if (line != "Contents:"){
			for (int j = 0; j < line.size(); j++) {
				if (int(line[j]) >= 97)
				{
					char_value = int(line[j]) - 97;
				}
				else
				{
					char_value = int(line[j]) - 65;
				}
				if (line[j] == ' ' || line[j] == '\n')
				{
					b1.word_count++;
				}
				else if (char_value >= 0 && char_value <= 25)
				{
					char_count++;
					b1.frequency[char_value] += 1;
				}
			}
		}
		b1.line_count++;
	}
	file.close();


	b1.line_count -= 3;
	//b1.full_name = b1.first_name + " " + b1.last_name;
	//memset(&(b1.full_name), 0, sizeof(b1.full_name));
	b1.full_name = full_name;
	b1.first_name = first_name;
	b1.last_name = last_name;

	for (int i = 0; i < 26; i++)
	{
		std::cout << char(i + 97) << ": " << b1.frequency[i] << std::endl;
		b1.frequency[i] /= char_count;
		b1.frequency[i] *= 100;
	}

	std::cout << "Title: " << b1.title << std::endl;
	std::cout << "Full Name: " << b1.full_name << std::endl;
	std::cout << "First Name: " << b1.first_name << std::endl;
	std::cout << "Last Name: " << b1.last_name << std::endl;
	std::cout << "Line Count: " << b1.line_count << std::endl;
	std::cout << "Word Count: " << b1.word_count << std::endl;
	std::cout << "Character Count: " << char_count << std::endl;
	for (int i = 0; i < 26; i++)
	{
		std::cout << char(i + 97) << ": " << b1.frequency[i] << "%" << std::endl;
	}

	return 0;
}