#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>

/*

Salma Mohammad
Daniel Vennemeyer
Chau Nguyen

*/

//declare the Book structure with all members
struct Book {
	std::string title{""};
	std::string full_name{""};
	std::string first_name{""};
	std::string last_name{""};
	int word_count{0};
	int line_count{0};
	float frequency[26];
};

int main() {
	std::string filename;
	std::string line;
	std::ifstream file;
	std::ofstream output_file{"CardCatalog.txt"};
	char ask_process;
	char ask_frequency;

	do {
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

		//check if file CardCatalog exists, else create it

		if (!(output_file)) {
			output_file.open("CardCatalog.txt", std::ios::app);
		}

		struct Book b1;
		b1.word_count = 0;
		b1.line_count = 0;
		for (int i = 0; i < 26; i++)
		{
			b1.frequency[i] = 0;
		}

		//read the file until the end

		while (!(file.eof())) {

			//read file line by line 

			getline(file, line);
			std::cout << line << std::endl;

			//store title line into b1

			if (b1.line_count == 0) {
				b1.title = line;
			}

			//store the name into full_name

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
				last_name1.erase(0, 1);

				full_name = full_name1;
				first_name = first_name1;
				last_name = last_name1;
				
			}

			//counts numbers of each character, line, and word to provide character count, line count and word count

			else if (line != "Contents:") {
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


		//calculates character frequency using character count 

		for (int i = 0; i < 26; i++)
		{
			//std::cout << char(i + 97) << ": " << b1.frequency[i] << std::endl;
			b1.frequency[i] /= char_count;
			b1.frequency[i] *= 100;
		}

		if (output_file.is_open()) {

			output_file << "\n";

			output_file << "Title: " << b1.title << std::endl;
			output_file << "Full Name: " << b1.full_name << std::endl;
			output_file << "First Name: " << b1.first_name << std::endl;
			output_file << "Last Name: " << b1.last_name << std::endl;
			output_file << "Line Count: " << b1.line_count << std::endl;
			output_file << "Word Count: " << b1.word_count << std::endl;
			//std::cout << "Character Count: " << char_count << std::endl;
		}

		std::cout << "Would you like to see the letter frequency? (Enter y/n)" << std::endl;
		std::cin >> ask_frequency;

		// If the user says yes to letter frequency, the letter frequency data outputs to file

		if (ask_frequency == 'y') {
			for (int i = 0; i < 26; i++)
			{
				output_file << char(i + 97) << ": " << b1.frequency[i] << "%" << std::endl;
			}
		}

		std::cout << "Would you like to process another book? (Enter y/n)" << std::endl;
		std::cin >> ask_process;

	} while (ask_process == 'y'); //whole code into a do-while statement in order to repeat the process each time user inputs y

	output_file.close();

	return 0;
}