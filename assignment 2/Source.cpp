//Name: HIfzurrehman Moosa
//ID: G20968325
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

const int arrSize = 8;
int totalBannedWords = 0;
const int MaxWords = 99999;
int repAmnt[MaxWords];
int counter = 0;
string repWords[MaxWords];
string bannedWrds[arrSize];
vector <string> txt1;
vector <string> txt2;
vector <string> txt3;
vector <string> txt4;

struct words 
{
	string word;
	int count{}; // initialized to 0
};
words bannedWord[arrSize];

void lineSeperation()
{
	cout << endl;
	cout << endl;
	for (int i = 0; i < 120; i++)
	{
		cout << "=";
	}
	cout << endl;
	cout << endl;
}
void displayVector(vector <string> vec)
{
	for (int i = 0; i < vec.size(); i++) //for loop to go through the entire vector
	{
		cout << vec[i] << " " ; //outputs data in the vector in location 'i' till for loop ends
	}
	cout << endl;
}

void errorCheck(ifstream& file) //function to check if file exists
{
	if (!file)
	{
		cout << "ERROR: "; //error shown if file not found 
		cout << "Can't open input file\n";
	}	
}

//function to find how frequently a word is used
int wordFrequency(string& words) // Gets the string word
{
	int fCount = repAmnt[0]; //count is set to the first index of array repAmnt
	int j = 0;
	for (int i = 0; i < counter; i++)
	{
		if (repAmnt[i] > fCount)
		{
			fCount = repAmnt[i];
			j = i;

		}
	}
	repAmnt[j] = 0;
	words = repWords[j];
	return fCount;
}

//function to find all instances of a word and update count
void findRepeatingWords(string word) // Gets the word
{
	for (int i = 0; i < counter; i++)
	{
		if (word == repWords[i])// Compares the word with repeating word if there is any, it increments the count and returns.
		{
			repAmnt[i] += 1;
			return;
		}
	}
	if (counter < MaxWords) 
	{
		repWords[counter] = word; 
		repAmnt[counter] = 1;
		counter++;
	}
}

void readFile(string filePath, vector <string>& vec) //function to read file
{
	ifstream txtFile(filePath); //open file
	errorCheck(txtFile); //function to check for errors
	cout << "Reading " << filePath << "..." << endl;
	string txtWord; //variable to store each word

	while (!txtFile.eof()) //while loop to go through entire file
	{
		txtFile >> txtWord; //each word is stored into the variable
		vec.push_back(txtWord); //the string value in the variable is added to the vector
		findRepeatingWords(txtWord); 
	}
	errorCheck(txtFile); //function to check for errors
	txtFile.close();
	cout << endl;
	cout << filePath << " original text: " << endl;
	cout << endl;
	displayVector(vec);
	cout << endl << "Top 10 most frequent words in this file : " << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "'" << txtWord << "'" << " found " << wordFrequency(txtWord) << " times" << endl;
	}
}

void filterWords(vector <string>& vec, string filePath) //function to filter all words and replace banned words with ***
{
	totalBannedWords = 0;
	for (int i = 0; i < arrSize; i++)//resets the count for baned words everytime the function is called
	{
		bannedWord[i].count = 0;
	}
	for (int i = 0; i < arrSize; i++) //for loop going through all the banned words
	{
		for (int j = 0; j < vec.size(); j++) //nested for loop to go through the vector ocntaining all words from file.txt
		{
			if (vec[j].find(bannedWord[i].word) != std::string::npos) //compares banned words with all file.txt words, https://stackoverflow.com/questions/29148693/searching-for-a-word-in-c-string-s-in-vectors, https://www.cplusplus.com/reference/string/string/npos/
				{
					totalBannedWords += 1;				//if substring is found total goes up by 1
					bannedWord[i].count += 1;			//count of current banned word goes up by 1
					vec[j].replace(vec[j].find(bannedWord[i].word),bannedWord[i].word.length(), "***"); 
					//found substring is replaced with *** 
				}
		}
	}
	cout << endl;
	cout << filePath << " filtered text: " << endl;
	cout << endl;
	displayVector(vec); //function call to display the vector
	cout << endl;
	for (int i = 0; i < arrSize; i++) //for loop to go through the full array
	{
		cout << "'" << bannedWord[i].word << "'" << " was found " << bannedWord[i].count << " times" << endl; //outputs the banned word and how many times it has been found
	}
	cout << endl;
	cout << "Total banned words found : " << totalBannedWords << endl; //outputs total amount of banned words found
	cout << endl;
}

void newFile(vector <string> vec, string filePath)
{
	ofstream out(filePath);
	for (int i = 0; i < vec.size(); i++)
	{
		out << vec[i] << " ";
	}
	cout << "Creating new file..." << endl;
	cout << "New file created : " << filePath;
	lineSeperation();
}

int main()
{
	ifstream bannedTxtFile("banned.txt");
	errorCheck(bannedTxtFile); //function call to check if file exists 
	while (!bannedTxtFile.eof())
	{
		for (int i = 0; i < 8; ++i)
		{
			bannedTxtFile >> bannedWord[i].word; //each banned word is assigned a location in the array
		}
	}
	bannedTxtFile.close();
	cout << "All Banned Words" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "- " << bannedWord[i].word << endl; //outputs all words in array
	}
	lineSeperation();
	//function calls for eaxh file to be read, filtered then saved as a new file
	readFile("text1.txt", txt1);
	filterWords(txt1, "text1.txt");
	newFile(txt1, "text1Filtered.txt");

	readFile("text2.txt", txt2);
	filterWords(txt2, "text2.txt");
	newFile(txt2, "text2filtered.txt");

	readFile("text3.txt", txt3);
	filterWords(txt3, "text3.txt");
	newFile(txt3, "text3filtered.txt");

	readFile("text4.txt", txt4);
	filterWords(txt4, "text4.txt");
	newFile(txt4, "text4filtered.txt");
}

