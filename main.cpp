/*********************************************************
* AUTHOR    : Sofia Pineda
* Lab#3     : Two Dimensional Arrays with Argc and Argv
* Last Edit : August 10th, 2018
**********************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

int **createArray(ifstream &file, int &row, int &col);
void promptFileName(string &name);
void displayFile(int **array, int row, int col);
void deleteContent(int **array, int row, int col);
void editContent(int **array, int row, int col);
int getValInput(int max, int min);
void randomContent(int **array, int row, int col);
char validChoice();


/**********************************************************
*
* TWO DIMENSIONAL ARRAYS
*_________________________________________________________
* This program recieves an input file and allows the user
* to edit it by: delete all content, change a cell, or
* reload matrix with random numbers.
*________________________________________________________
***********************************************************/
int main(int argc, char *argv[])
{
    // Declare Main 2D array
    int **arra, row, col;

    // Declare File Names
    ifstream inFile;
    string inName;

    // Declare Choice Char + loop
    char choice;
    bool edit = true;

    srand(time(NULL));

    // Read files from argc
    switch (argc)
    {
        // Case 1 means nothing was inputted in terms of files
        case 1: cout << "No input file found. Prompting file name." << endl;
        promptFileName(inName);
        break;

        // File was given. Open file.
        case 2: cout << "Input file found." << endl;
        inName = argv[1];
        break;

        default:
        cout << "Too many parameters! Good bye!" << endl;
        exit(0);
    }

    // Open file and check if valid
    inFile.open(inName.c_str());

    if(!inFile.is_open())
    {
        cout << "File not found. Terminating." << endl;
        exit(0);
    }

    // Create Array from file
    arra = createArray(inFile, row, col);

    // Display File
    displayFile(arra, row, col);

    // Prompt what they would like to do with file
    // from Assignment: "editing can include deleting all content,
    //                     changing the value(s) in any particular cell(s),
    //      or reloading the matrix with random numbers within a given range

    // Switch Statement (Should be in a loop)
    do
    {
        cout << "What would you like to do with the file?" << endl;
        cout << "(D)elete Content, (C)hange Value, (R)eload Matrix, (F)inished." << endl;

        choice = validChoice();

        switch(choice)
        {
            case 'D':
            case 'd': // call delete function. Once delete is called, end program
            deleteContent(arra, row, col);
            cout << "Content Deleted. Goodbye." << endl;
            exit(0);
            break;

            case 'C':
            case 'c': // call change function
            editContent(arra, row, col);
            cout << "Here is your new matrix." << endl;
            displayFile(arra, row, col);
            break;

            case 'R':
            case 'r': // call reload function
            randomContent(arra, row, col);
            cout << "Here is your new matrix." << endl;
            displayFile(arra, row, col);
            break;

            case 'F':
            case 'f': // Done!
            cout << "Finished editing. Goodbye." << endl;
            deleteContent(arra, row, col);
            edit = false;
            break;

            default: cout << "Quitting Program. Good bye." << endl;
            edit = false;
            exit(0);
        }
    } while(edit);

    return 0;
}

void promptFileName(string &name)
{
    cout << "Please enter a file name with an extension." << endl;
    cin >> name;

    if ((name.find_first_of(".txt") == string::npos) || name.empty())
    {
        cout << "Invalid name or no name given. Terminating." << endl ;
        exit(0);
    }

    cin.clear();
    cin.ignore(10000, '\n');
}

int **createArray(ifstream &file, int &row, int &col)
{

    // Get rows and cols from file
    file >> row >> col;

    int **array;

    array = new int*[row];

    for(int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            array[i] = new int[col];
    }

    // Load array
    for(int r = 0; r < row; ++r)
    {
        for(int t = 0; t < col; ++t)
            file >> array[r][t];
    }

    file.close();

    return array;
}

void displayFile(int **array, int row, int col)
{
    cout << "The array contents are:" << endl << endl;

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
            cout << setw(4) << array[i][j];

        cout << endl;
    }

    cout << endl << endl;
}

void deleteContent(int **array, int row, int col)
{
    cout << "You have chosen to delete content. Deleting content..." << endl;

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
            array[i][j] = 0;

        delete []array[i];

        array[i] = NULL;
    }

    delete []array;

    array = NULL;

}

void editContent(int **array, int row, int col)
{
    int rowInp;
    int colInp;
    int newVal;

    cout << "You have chosen to edit content. Input row and coloumn." << endl;

    cout << "What row would you like to edit?" << endl << endl;
    rowInp = getValInput(row, 0);

    cout << "What column would you like to edit?" << endl << endl;
    colInp = getValInput(col, 0);

    cout << "What is the new value of that cell?" << endl << endl;
    newVal = getValInput(1000, 0);

    array[rowInp-1][colInp-1] = newVal;

}

void randomContent(int **array, int row, int col)
{
    int minRan;
    int maxRan;

    int range;

    cout << "You have chosen to randomize the matrix." << endl;

    cout << "Choose what the max value should be." << endl;
    maxRan = getValInput(1000, 0);

    cout << "Choose what the min value should be." << endl;
    minRan = getValInput(maxRan, 0);

    range = maxRan - minRan;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            array[i][j] = int(minRan + rand() % range);
    }
}


int getValInput(int max, int min)
{
    int input;
    bool valid = false;

    do
    {
        cin >> input;

        if (input > max || input < min)
        {
            cout << "Invalid input. Please try again.";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
            valid = true;
    }
    while(!(valid));

    return input;
}

char validChoice()
{
    string inp;
    char choice;
    bool valid = false;

    do
    {
        cin >> inp;

        choice = inp.at(0);

        if (inp.find_first_not_of("DdCcRrFf") != string::npos)
        {
                cout << "Invalid choice. Try Again." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
        }

        else
            valid = true;

    }while(!(valid));

    return choice;
}
