#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
	int your_choice, bit_variable;
	string sourc_file;
	cout << "Press 1 to Encrypt file.\nPress 2 to Decrypt file." << endl;
	cin >> your_choice;
	cout << "Enter File Name -" << endl;
	cin >> sourc_file;
	cout << "Enter Key -" << endl;
	cin >> bit_variable;
	if (your_choice == 1)//to enc
	{
		char c;
		ifstream fin;
		ofstream fout;
		fin.open(sourc_file.c_str(), ios::binary);
		sourc_file = "output";
		fout.open(sourc_file.c_str(), ios::binary);
		while (!fin.eof())
		{
			fin >> noskipws >> c;
			int source_copy = (c + bit_variable);
			fout << (char)source_copy;
		}
		fin.close();
		fout.close();
	}
	else if (your_choice == 2)//to denc
	{
		char c;
		ifstream fin;
		ofstream fout;
		fin.open(sourc_file.c_str(), ios::binary);
		sourc_file = "qutput";
		fout.open(sourc_file.c_str(), ios::binary);
		while (!fin.eof())
		{
			fin >> noskipws >> c;
			int source_copy = (c - bit_variable);
			fout << (char)source_copy;
		}
		fin.close();
		fout.close();
	}
	return 0;
}
