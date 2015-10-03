//------------------------------------------------------------------------------
// LZ_main.cc
//
// Created on: 22/ago/2015
//     Author: Gianmarco Doro
//
// Short menu that calls the chosen compressor
//------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "LZ_main.h"

using namespace std;

int main(int argc, char *argv[]) {

  int choice1=0;
  int choice2=0;
  
  system("clear");
  while (choice1 !=4) {
    ShowMenu();
    cin >> choice1;
    LaunchCompressor(choice1);
  }
  return 0;
}

void ShowMenu() {
  cout << "Welcome to \"LZ compressor\" menu! " << endl;
  cout << endl;
  cout << "Please select an option: " << endl;
  cout << "[1] LZ78 Compressor" << endl;
  cout << "[2] LZW Compressor" << endl;
  cout << "[3] About \"LZ compressor\"" << endl;
  cout << "[4] Exit" << endl;
  return;
}

void LaunchCompressor(int choice1) {
  int choice2 = 0;
  switch(choice1) {
    case 1: {
      LZ78Compressor LZ78;
      ShowCompressorMenu();
      cin >> choice2;
      LaunchOperation(LZ78, choice2);
      break;
    }
    case 2: {
      LZWCompressor LZW;
      ShowCompressorMenu();
      cin >> choice2;
      LaunchOperation(LZW, choice2);
      break;
    }
    case 3: {
      ShowHelp();
      break;
    }
    case 4: {
      exit(0);
    }
    default: {
      cout << "Please insert a valid choice" << endl << endl << endl;
    }
  }
  return;
}

void ShowCompressorMenu() {
  cout << endl << "Do you want to: " << endl;
  cout << "[1] Compress a string" << endl;
  cout << "[2] Decompress a string" << endl;
  cout << "[3] Compress a file" << endl;
  cout << "[4] Decompress a file" << endl;
  cout << "[5] Return to main menu" << endl;
}

void LaunchOperation (Compressor& Compressor, int choice2) {
  switch(choice2) {
    case 3: {
      std::ifstream input_file("../Data/input", std::ios_base::binary);
      if (!input_file.is_open()) {
        cout << "Input_file \"../Data/input\" could not be opened." << endl;
        return;
      }
      std::ofstream output_file("../Data/output.lz", std::ios_base::binary);
      if (!output_file.is_open()) {
        cout << "Output_file \"../Data/output.lz\" could not be opened." << endl;
        return;
      }

      Compressor.compress(input_file, output_file);
      break;
    }

    case 4: {
      std::ifstream input_file("../Data/output.lz", std::ios_base::binary);
      if (!input_file.is_open()) {
        cout << "Input_file \"../Data/output.lz\" could not be opened." << endl;
        return;
      }
      std::ofstream output_file("../Data/output", std::ios_base::binary);
      if (!output_file.is_open()) {
        cout << "Output_file \"../Data/output\" could not be opened." << endl;
        return;
      }

      Compressor.decompress(input_file, output_file);
      break;
    }

    case 5: {
      cout << endl << endl << endl;
      break;
    }

    default: {
      cout << "Please insert a valid choice" << endl << endl << endl;
    }
  }
  return;
}

void ShowHelp() {
  cout <<
  "\"LZ Compressor\" is a program that allows the compression and decompression of"
  << endl;
  cout << "simple strings (for demonstrative purposes) and/or files." << endl;
  cout << "The two available algortihms are LZ78 and LZW." << endl;
  cout << endl << endl << endl;
}