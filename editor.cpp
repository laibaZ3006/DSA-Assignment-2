#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

class TextEditor
{
private:
    vector<string> text;
    vector<string> recentFiles;

    string currentFile;

    int cursorLine;
    int cursorPos;

    string currentFont;
    int currentFontSize;
    int currentColor;

    bool wordWrap;

public:
    TextEditor()
    {
        cursorLine = 0;
        cursorPos = 0;

        currentFont = "Consolas";
        currentFontSize = 12;
        currentColor = 7;

        wordWrap = true;

        text.push_back("");
    }
    void displayMenu()
    {
        system("cls");

        setColor(currentColor);

        cout << "========================================\n";
        cout << "        CONSOLE TEXT EDITOR             \n";
        cout << "========================================\n";

        cout << "1. New File\n";
        cout << "2. Open File\n";
        cout << "3. Save File\n";
        cout << "4. Save As\n";
        cout << "5. Close File\n";
        cout << "6. View Recent Files\n";
        cout << "7. Type/Edit Text\n";
        cout << "8. Change Text Color\n";
        cout << "9. Change Font\n";
        cout << "10. Change Font Size\n";
        cout << "11. Find and Replace\n";
        cout << "12. Home Key\n";
        cout << "13. End Key\n";
        cout << "14. Page Up\n";
        cout << "15. Page Down\n";
        cout << "16. Select All\n";
        cout << "17. Toggle Word Wrap\n";
        cout << "18. Display Text\n";
        cout << "19. Exit\n";

        cout << "========================================\n";
    }

    
    void setColor(int color)
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, color);
    }

    void changeColor()
    {
        int color;

        cout << "\nAvailable Colors:\n";
        cout << "1. Blue\n";
        cout << "2. Green\n";
        cout << "3. Red\n";
        cout << "4. Yellow\n";
        cout << "5. White\n";

        cout << "Choose color: ";
        cin >> color;

        switch (color)
        {
        case 1:
            currentColor = 1;
            break;

        case 2:
            currentColor = 2;
            break;

        case 3:
            currentColor = 4;
            break;

        case 4:
            currentColor = 6;
            break;

        case 5:
            currentColor = 7;
            break;

        default:
            cout << "Invalid color!\n";
        }
    }

   

    void newFile()
    {
        text.clear();
        text.push_back("");

        currentFile = "";

        cursorLine = 0;
        cursorPos = 0;

        cout << "New file created successfully!\n";
    }

    void saveFile()
    {
        if (currentFile.empty())
        {
            saveAs();
            return;
        }

        ofstream fout(currentFile);

        for (int i = 0; i < text.size(); i++)
        {
            fout << text[i] << endl;
        }

        fout.close();

        cout << "File saved successfully!\n";
    }

    void saveAs()
    {
        cout << "Enter file name: ";
        cin >> currentFile;

        saveFile();

        addRecentFile(currentFile);
    }

    void openFile()
    {
        string filename;

        cout << "Enter file name: ";
        cin >> filename;

        ifstream fin(filename);

        if (!fin)
        {
            cout << "File not found!\n";
            return;
        }

        text.clear();

        string line;

        while (getline(fin, line))
        {
            text.push_back(line);
        }

        fin.close();

        currentFile = filename;

        addRecentFile(filename);

        cout << "File opened successfully!\n";
    }

    void closeFile()
    {
        text.clear();
        text.push_back("");

        currentFile = "";

        cout << "File closed successfully!\n";
    }

    void addRecentFile(string filename)
    {
        recentFiles.push_back(filename);
    }

    void viewRecentFiles()
    {
        cout << "\nRecent Files:\n";

        if (recentFiles.empty())
        {
            cout << "No recent files found.\n";
            return;
        }

        for (int i = 0; i < recentFiles.size(); i++)
        {
            cout << i + 1 << ". " << recentFiles[i] << endl;
        }
    }

    

    void typeText()
    {
        cin.ignore();

        cout << "\nEnter text line by line.\n";
        cout << "Type ':q' to stop typing.\n\n";

        string line;

        while (true)
        {
            getline(cin, line);

            if (line == ":q")
                break;

            text.push_back(line);
        }
    }

    void displayText()
    {
        cout << "\n=========== FILE CONTENT ===========\n";

        for (int i = 0; i < text.size(); i++)
        {
            if (wordWrap)
            {
                wordWrapDisplay(text[i]);
            }
            else
            {
                cout << text[i] << endl;
            }
        }

        cout << "====================================\n";
    }

    void wordWrapDisplay(string line)
    {
        int width = 50;

        for (int i = 0; i < line.length(); i += width)
        {
            cout << line.substr(i, width) << endl;
        }
    }

    
    void findAndReplace()
    {
        string findWord;
        string replaceWord;

        cin.ignore();

        cout << "Enter word to find: ";
        getline(cin, findWord);

        cout << "Enter replacement word: ";
        getline(cin, replaceWord);

        for (int i = 0; i < text.size(); i++)
        {
            size_t pos = text[i].find(findWord);

            while (pos != string::npos)
            {
                text[i].replace(pos, findWord.length(), replaceWord);

                pos = text[i].find(findWord, pos + replaceWord.length());
            }
        }

        cout << "Replacement completed successfully!\n";
    }

    
    void changeFont()
    {
        int choice;

        cout << "\nAvailable Fonts:\n";
        cout << "1. Arial\n";
        cout << "2. Consolas\n";
        cout << "3. Courier New\n";

        cout << "Choose font: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            currentFont = "Arial";
            break;

        case 2:
            currentFont = "Consolas";
            break;

        case 3:
            currentFont = "Courier New";
            break;

        default:
            cout << "Invalid choice!\n";
        }

        cout << "Current Font: " << currentFont << endl;
    }

    void changeFontSize()
    {
        cout << "Enter font size: ";
        cin >> currentFontSize;

        cout << "Font size changed to " << currentFontSize << endl;
    }

    
    void homeKey()
    {
        cursorPos = 0;

        cout << "Cursor moved to start of line.\n";
    }

    void endKey()
    {
        if (!text.empty())
        {
            cursorPos = text[cursorLine].length();
        }

        cout << "Cursor moved to end of line.\n";
    }

    void pageUp()
    {
        cursorLine = max(0, cursorLine - 5);

        cout << "Page Up pressed.\n";
    }

    void pageDown()
    {
        cursorLine = min((int)text.size() - 1, cursorLine + 5);

        cout << "Page Down pressed.\n";
    }

    

    void selectAll()
    {
        cout << "\n========== SELECTED TEXT ==========\n";

        for (int i = 0; i < text.size(); i++)
        {
            cout << text[i] << endl;
        }

        cout << "===================================\n";
    }

  

    void toggleWordWrap()
    {
        wordWrap = !wordWrap;

        if (wordWrap)
            cout << "Word Wrap Enabled\n";
        else
            cout << "Word Wrap Disabled\n";
    }
};



int main()
{
    TextEditor editor;

    int choice;

    while (true)
    {
        editor.displayMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            editor.newFile();
            break;

        case 2:
            editor.openFile();
            break;

        case 3:
            editor.saveFile();
            break;

        case 4:
            editor.saveAs();
            break;

        case 5:
            editor.closeFile();
            break;

        case 6:
            editor.viewRecentFiles();
            break;

        case 7:
            editor.typeText();
            break;

        case 8:
            editor.changeColor();
            break;

        case 9:
            editor.changeFont();
            break;

        case 10:
            editor.changeFontSize();
            break;

        case 11:
            editor.findAndReplace();
            break;

        case 12:
            editor.homeKey();
            break;

        case 13:
            editor.endKey();
            break;

        case 14:
            editor.pageUp();
            break;

        case 15:
            editor.pageDown();
            break;

        case 16:
            editor.selectAll();
            break;

        case 17:
            editor.toggleWordWrap();
            break;

        case 18:
            editor.displayText();
            break;

        case 19:
            cout << "Exiting editor...\n";
            return 0;

        default:
            cout << "Invalid choice!\n";
        }

        system("pause");
    }

    return 0;
}