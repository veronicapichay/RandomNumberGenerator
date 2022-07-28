#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    //declarations, and housekeeping
    srand(time(0));
    int randNr, rows, cols, oddEven, minR, maxR, W1, sum, smallest, largest;
    float avg;
    char entry, yesNo, again;
    string filename;
    ofstream outFile;
    bool toFile = false, showSum = false, showAvg = false,
         showSmallest = false, showLargest = false;

    do // outer loop to repeat the program if the user desires
    {
        sum = 0;
        //welcome
        cout << "\t> This program will output a customized table of random numbers.\n";

        //INPUT SECTION **************************************************

        //user choice for columns
        cout << "\t> How many columns do you want (1-15)? ";
        cin >> cols;
        while (cols < 1 or cols > 15) 
        {
            cout << "\t\t> ERROR: 1-15 only: ";
            cin >> cols;
        }

        //user choice for rows
        cout << "\t> How many rows do you want (1-15)? ";
        cin >> rows;
        while (rows < 1 or rows > 15) 
        {
            cout << "\t\t> ERROR: 1-15 only: ";
            cin >> rows;
        }

        //user choice for Odds, Evens, or Both
        cout << "\t> Do you want (O)dd, (E)ven, or (B)oth types of numbers? ";
        cin >> entry;
        entry = toupper(entry);
        while (entry != 'O' and entry != 'E' and entry != 'B') 
        {
            cout << "\t\t> ERROR: O, E, or B only: ";
            cin >> entry;
            entry = toupper(entry);
        }
        //the oddEven variable sets the user's O/E/B choice to an integer
        //this integer gets used later to filter odd/even output
        if (entry == 'E') oddEven = 0;
        else if (entry == 'O') oddEven = 1;
        else oddEven = 2;

        //user choice to output to a file or not
        cout << "\t> Do you want to output to a file as well? Y/N: ";
        cin >> yesNo;
        yesNo = toupper(yesNo);
        while (yesNo != 'N' and yesNo != 'Y') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> yesNo;
            yesNo = toupper(yesNo);
        }
        if (yesNo == 'Y') 
        {
            cout << "\t> Enter an output filename (no spaces and ending in .txt): ";
            cin >> filename;
            toFile = true;
            outFile.open(filename);
        }

        //user choice for min & max rand desired
        cout << "\t> What is your minimum random number desired (0 - 10000): ";
        cin >> minR;
        while (minR < 0 or minR > 10000) 
        {
            cout << "\t\t> ERROR: 0 - 10000 only: ";
            cin >> minR;
        }
        cout << "\t> What is your maximum random number desired (1-99999 and must\n";
        cout << "\t> be greater than your minimum random number desired): ";
        cin >> maxR;
        while (maxR < 1 or maxR > 99999 or maxR <= minR) 
        {
            if (maxR < 1 or maxR > 99999) cout << "\t\t: ERROR: 0 - 99999 only: ";
            else cout << "\t\t> ERROR: max must be greater than min: ";
            cin >> maxR;
        }

        //user choice for displaying sum
        cout << "\t> Display the sum of the random numbers in the table (Y/N)? ";
        cin >> yesNo;
        yesNo = toupper(yesNo);
        while (yesNo != 'N' and yesNo != 'Y') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> yesNo;
            yesNo = toupper(yesNo);
        }
        if (yesNo == 'Y') showSum = true;

        //user choice for displaying average
        cout << "\t> Display the average of the random numbers in the table (Y/N)? ";
        cin >> yesNo;
        yesNo = toupper(yesNo);
        while (yesNo != 'N' and yesNo != 'Y') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> yesNo;
            yesNo = toupper(yesNo);
        }
        if (yesNo == 'Y') showAvg = true;

        //user choice for displaying largest
        cout << "\t> Display the largest random number generated in the table (Y/N)? ";
        cin >> yesNo;
        yesNo = toupper(yesNo);
        while (yesNo != 'N' and yesNo != 'Y') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> yesNo;
            yesNo = toupper(yesNo);
        }
        if (yesNo == 'Y') 
        {
            showLargest = true;
            largest = minR - 1;
        }

        //user choice for displaying smallest
        cout << "\t> Display the smallest random numbers generated in the table (Y/N)? ";
        cin >> yesNo;
        yesNo = toupper(yesNo);
        while (yesNo != 'N' and yesNo != 'Y') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> yesNo;
            yesNo = toupper(yesNo);
        }
        if (yesNo == 'Y') 
        {
            showSmallest = true;
            smallest = maxR + 1;
        }

        //extra credit section: dynamic field width
        if (maxR / 10000 > 1) W1 = 7;
        else if (maxR / 1000 > 1) W1 = 6;
        else if (maxR / 100 > 1) W1 = 5;
        else if (maxR / 10 > 1) W1 = 4;
        else W1 = 3;

        //OUTPUT SECTION **************************************** 

        //this is the program engine that generates the table
        cout << "\n\nRandom number table:\n\n";
        for (int i = 1; i <= rows; i++) 
        {
            for (int j = 1; j <= cols; j++) 
            {
                randNr = rand() % (maxR - minR + 1) + minR;

                //pseudo input validation loop for generating an odd/even
                //random number. 
                if (oddEven != 2) // if the user wants just odds or evens
                    //while loop will continue until an odd/even random
                    //number is generated, per the user's choice
                    while (randNr % 2 != oddEven) // mods by their choice
                        randNr = rand() % (maxR - minR + 1) + minR;

                cout << setw(W1) << randNr;
                if (toFile) outFile << setw(W1) << randNr;
                sum += randNr;
                if (randNr < smallest) smallest = randNr;
                if (randNr > largest) largest = randNr;
            }
            cout << endl;
            if (toFile) outFile << endl;
        }

        //outputs the various statistics, per the user's choices
        if (showSum or showAvg or showLargest or showSmallest) cout << "\n\n\t> Table statistics: \n";
        if (showSum) cout << "\t> Sum: " << sum << endl;
        cout << fixed << setprecision(2);
        if (showAvg) cout << "\t> Average: " << sum / (float)(rows * cols) << endl;
        if (showLargest) cout << "\t> Largest: " << largest << endl;
        if (showSmallest) cout << "\t> Smallest: " << smallest << endl;

        //ask if user wants to repeat the program
        cout << "\n\t> Repeat the program? Y/N --> ";
        cin >> again;
        again = tolower(again);
        while (again != 'y' and again != 'n') 
        {
            cout << "\t\t> ERROR: Y/N only: ";
            cin >> again;
            again = tolower(again);
        }
    } while (again == 'y');

    //housekeeping
    if (toFile) outFile.close();
    return 0;
}