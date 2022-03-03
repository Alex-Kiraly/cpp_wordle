#include <iostream>
#include <fstream>//reading file
#include <cstring>//strcopy
#include <ctime> //Nem igazán random, de ebben a helyzetben működik
using namespace std;

//NEM MŰKÖDIK WINDOWS
//Color definitions for the terminal
#define OUT_GREY "\033[100m"
#define OUT_GREEN "\033[42m"
#define OUT_YEL "\033[43m"
#define OUT_RESET "\033[0m"


int file_length() {
  int lines = 0;

  ifstream file("words.txt");
  string junk;
  while(file) {
    getline(file, junk); //Iterates through words and stores them in junk
    ++lines;
  }
  file.close();

  return lines;
}
//Used to set array of words' size
const int FILE_LENGTH = file_length();


char board[6][5] = {}; //The 2d array the inputed words are stored in
string word; //The word to be guessed


//Check for the orange label in game
bool word_contains(char c) {
  for(char ch: word) {
    if(ch == c) {
      return true;
    }
  }
  return false;
}

//Tests if input string is 5 letters, and is actually a word
bool valid_input(string input, string arr[]) {
  for(int i = 0; i < input.length(); i++) {
    input[i] = tolower(input[i]);
  }
  if (input.length() < 5) {
    cout << "Word is shorter than 5 letters. Try again\n";
    return false;
  }
  else if (input.length() > 5) {
    cout << "Word is greater than 5 letters. Try Again\n";
    return false;
  }

  //check if str is in word list
  bool exist = false;
  for(int i = 0; i < FILE_LENGTH; i++) {
    if(input == arr[i]) {
      exist = true;
    }
  }
  if(!exist) {
    cout << "Word is not proper 5 letter word\n";
  }

  return exist;
}

//Primary game function that has the game logic
int analyze() {
  cout << endl;

  int correct;
  for(int i = 0; i < 6; i++) {
    //Ends checks if next line is empty
    if(board[i][0] == NULL) {
      break;
    }
    correct = 0;
    for(int j = 0; j < 5; j++) {
      if(board[i][j] == word[j]) {
        cout << OUT_GREEN << board[i][j] << OUT_RESET;
        correct++;
      }
      else if(word_contains(board[i][j])) {
        cout << OUT_YEL << board[i][j] << OUT_RESET;
      }
      else {
        cout << OUT_GREY << board[i][j] << OUT_RESET;
      }
      if(correct == 5) {
        goto end;
      }
    }
    cout << endl;
  }

  end:
  cout << endl;
  return correct;
}

//Generates word to guess
string generate_word(string arr[]) {
  srand(time(0));
  string str;
  int num = rand() % FILE_LENGTH;

  return arr[num];
}

//Sets the array with all the words from wrods.txt
void set_words(string arr[]) {
  ifstream file("words.txt");
  int i = 0;
  while(file) {
    getline(file, arr[i++]);
  }
  file.close();
}


int main(int argc, char *argv[]) {
  //array will hold all words in file
  string all_words[FILE_LENGTH];
  set_words(all_words);

  word = generate_word(all_words);

  //Type DEBUG as command line argument to see the word
  if(argc > 1) {
    string str = argv[1];
    if(str.compare("DEBUG") == 0) {
      cout << "Word is: " << word << endl;
    }
  }

  string input;

  cout << OUT_GREEN << "Welcome to Wordle, try to guess the 5 letter word:" << OUT_RESET << endl;
  for(int i = 0; i < 6; i++) {
    cin >> input;

    while(!valid_input(input, all_words)) {
      cin >> input;
    }

    strcpy(board[i], input.c_str());
    if(analyze() == 5) {
      cout << "Congrats, you win!\n";
      break;
    }

  }

  cout << "Word was " << word << endl;
  cout << "Goodbye\n";
  return 0;
}
