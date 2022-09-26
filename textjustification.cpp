#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;


string flush_left(string line, int width) {
    std::string spaces;

    int padding = (width - line.size()) - 1;
    spaces = string(padding, ' ');

    return line + spaces;

}

string flush_right(string line, int width) {
    std::string spaces;

    int padding = (width - line.size()) - 1;
    spaces = string(padding, ' ');

    return spaces + line;

}




string r_trim(string line) {


    return line;
}

int countOf(string line, string value) {
    int indexOfValue = 0;
    int countofValue = 0;
    int position = 0;

    while (indexOfValue != -1) {
        indexOfValue = line.find(value, position);
        if (indexOfValue != -1) {
            countofValue++;
            position = indexOfValue + 1;
        }
    }

    return countofValue;
}

string insertSpaces(string line, int padding_spaces, int spaces) {
    int positionOfSpace = 0;
    while (positionOfSpace != -1 && padding_spaces > 0) {
        if (positionOfSpace == line.size()) {
            positionOfSpace = -1;
        }
        positionOfSpace = line.find(" ", positionOfSpace);
        //string 5spaces = string(spaces, " ");
        if (positionOfSpace != -1) {
            line.insert(positionOfSpace, string(spaces, ' '));
            padding_spaces = padding_spaces - spaces;
            //positionOfSpace += spaces + 1;
            positionOfSpace = line.find_first_not_of(' ', positionOfSpace);
       }

    }
    return line;
}


string full_justify(string line, int width) {

    int padding_spaces = (width - line.size());
    int spaceSlots = countOf(line, " ");
    // int positionOfSpace = 0;

    // when padding is less than space slots
    if (padding_spaces < spaceSlots) {
        //cout << "Im here" << endl;
        line = insertSpaces(line, padding_spaces, 1);

    }
    
    // when padding divided by space slots has no remainder, add the result of the division to each space slot.
    if (padding_spaces % spaceSlots == 0) {
        int spaces = padding_spaces / spaceSlots; 
        line = insertSpaces(line, padding_spaces, spaces);
    }
    // when padding divide by space slots has a remainder: if(padding % space_slots != 0)
    if (padding_spaces % spaceSlots != 0 && padding_spaces > spaceSlots) {
        //cout << "Im here" << endl;
        int spaces = padding_spaces / spaceSlots;
        int remainder = padding_spaces % spaceSlots;
        line = insertSpaces(line, padding_spaces, spaces);
        line = insertSpaces(line, remainder, 1);
    }

   return line;
}




int main(int argc, char** argv) {


    //string test1 = string(-1, ' ');
    //cout << test1 << endl;
    // Error check if there aren't enough command line arguments
    if (argc != 5) {
        cerr << "Not correct amount of arguments. 4 total arguments are required." << endl;
        return 1;
    }
    
    
    
    // Interpreting command line arguments here:
    
    std::string commandIn = argv[1];
    std::string commandOut = argv[2];
    int width = atoi(argv[3]);
    std::string inputJustify = argv[4];

    std::string yourText;

    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(commandIn); 
    yourText.assign( (std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));


    
    inputFile.close();

    if (yourText.back() == '\n') {
        yourText = yourText.substr(0, yourText.size() - 1);
    }

    

    int text_size = yourText.size();


    vector<string> wordVector;

    int startindex = 0;
    int position_index = width - 1;
    std::string borders = string(width + 4, '-');
    
    
    // The following code will split the words into line and place
    // them into a vector. Splitting is done through the int width variable
    int iter = 0;
    while (position_index != startindex) {

        if (yourText[position_index] == ' ') {
            wordVector.push_back(r_trim(yourText.substr(startindex, position_index - startindex)));
            startindex = position_index + 1;
            position_index = position_index + 16 + 1;
           
            if (position_index >= text_size) {
                wordVector.push_back(r_trim(yourText.substr(startindex, text_size - startindex)));
                position_index = startindex;
            }
        }
        else {
            position_index--;

        }
    }


    
    
    // Prints if flush_left is wanted
    if (inputJustify == "flush_left") {
        outputFile.open(commandOut);
        outputFile << borders << endl;
        for (int i = 0; i < wordVector.size(); i++) {
            //outputFile << "|" << wordVector[i] << "|" << endl;
            outputFile << "| " << flush_left(wordVector[i], width) << "  |" << endl;   
        }
        outputFile << borders;
        outputFile.close();
    }
    // Prints if flush_right is wanted
    else if (inputJustify == "flush_right") {
        outputFile.open(commandOut);
        outputFile << borders << endl;
        for (int i = 0; i < wordVector.size(); i++) {
            outputFile << "|  " << flush_right(wordVector[i], width) << " |" << endl;
        }
        outputFile << borders << endl;
        outputFile.close(); 
    }
    // Prints if full_justify is wanted
    else if (inputJustify == "full_justify") {
        outputFile.open(commandOut);
        outputFile << borders << endl;
        for (int i = 0; i < wordVector.size(); i++) {
            if (i == wordVector.size() - 1) {
                outputFile << "| " << flush_left(wordVector[i], width) << "  |" << endl;
            }
            else {
                outputFile << "| " << full_justify(wordVector[i], width) << " |" << endl;
            }
        }
        outputFile << borders << endl;
        outputFile.close(); 
    }
    else {
        cerr << "Could not identify the input justify." << endl;
        return 1;
    }

   
    

    return 0;

}
    // Some tests I've made
    //string testSentence = "Hi my name is Andrew";
    //string testFlush = full_justify(testSentence, 75);
    //cout << testFlush << endl;
    //int countofSpaces = countOf(testSentence, " ");
    //int indexOfValue = testSentence.find(" ", 15);
    //cout << countofSpaces << endl;

    //string testline = flush_left("Hi my name is Andrew", 40);
    //cout << testline << endl;
