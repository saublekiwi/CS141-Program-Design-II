/**------------------------------------------
    Program 1: ASCII Flowers
    Prompt for the number of flower layers and display

    Course: CS 141, Fall 2023
    System: Linux_x86_64 and G++
    Author: George Maratos and David Hayes + Martin Laugesen
 ---------------------------------------------**/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    // display the prompt to the user
    cout << "Program 1: ASCII Flowers\n"
         << "Choose from the following options:\n"
         << "   1. Display the HELLO graphic\n"
         << "   2. Display The Flower\n"
         << "   3. Exit the program\n"
         << "Your choice -> ";

    // read in the user's choice
    int menu_option;
    cin >> menu_option;

    // handle option to quit
    if (menu_option == 3) {
        exit(0);
    }

    // handle the HELLO graphic choice
    if (menu_option == 1) {
        char frame;
        cout << "Enter your frame character: ";
        cin >> frame;
        //top border
        cout << endl;
        for (int i=0; i<2; i++) {
            cout << setfill(frame) << setw(36) << ' ' << endl;
        }
        //message
        cout << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** **    **    *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "***** ***** **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** **    **    **    ** **"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << setfill(frame) << setw(3) << right << " "
             << "** ** ***** ***** ***** *****"
             << setfill(frame) << setw(3) << left << " " << endl
             << right;
        //bottom border
        for (int i=0; i<2; i++) {
            cout << setfill(frame) << setw(36) << " " << endl;
        }
    }

    // handle the floral pattern TODO for students
    if (menu_option == 2) {
        int sections = 0;
      
        cout << "Enter number of sections: ";
        cin >> sections;
        cout << endl;

        //loops through each section
        for (int section_num = 1; section_num <= sections; section_num++) {
          cout << setw(sections + 3) << setfill(' ') << "---" << endl;
          
          //loops through the top half of the section (+ the center line)
          for (int flower_line = 1; flower_line <= section_num; flower_line++) {
            char center = ':';
            if (flower_line == section_num) {
              center = '@';
            }
            
            cout << setw(sections - flower_line + 1) << '{';
            
            for (int flower_filling = 0; flower_filling < flower_line; flower_filling++) {
              cout << ':';
            }
            
            cout << center;
            
            for (int flower_filling = 0; flower_filling < flower_line; flower_filling++) {
              cout << ':';
            }
            
            cout << '}' << endl;
          }

          //loops through the bottom half of the section
          for (int flower_line = section_num - 1; flower_line > 0; flower_line--) {
            cout << setw(sections - flower_line + 1) << '{';
            
            for (int flower_filling = 2 * flower_line + 1; flower_filling > 0; flower_filling--) {
              cout << ':';
            }
            
            cout << '}' << endl;
          }
        }

        //draws the final edge
        cout << setw(sections + 3) << setfill(' ') << "---" << endl;
      
        //draws the stem (and leaves) of the flower
        for (int k = 0; k < sections; k++) {

          //right leaf
          if (k % 2 == 0) {
            cout << setw(sections + 4) << "|/\n";
            cout << setw(sections + 3) << "|\n";
          }

          //left leaf
          else {
            cout << setw(sections + 3) << "\\|\n";
            cout << setw(sections + 3) << "|\n";
          }
        }
    }
    return 0;
}