#include <iostream>
using namespace std;

class Window {
public:
    string title;
    string color;
    int size;

    Window* next;
    Window* prev;

    Window(string t, string c, int s) {
        title = t;
        color = c;
        size = s;
        next = NULL;
        prev = NULL;
    }
};

class WindowManager {
    Window* head;

public:
    WindowManager() {
        head = NULL;
    }
    void createWindow(string t, string c, int s = 100) {

        Window* newWindow = new Window(t, c, s);

        if (head == NULL) {
            head = newWindow;
            return;
        }

        Window* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newWindow;
        newWindow->prev = temp;
    }
    void display() {

        Window* temp = head;

        cout << "\nWindows:\n";

        while (temp != NULL) {
            cout << temp->title
                 << " | Color: " << temp->color
                 << " | Size: " << temp->size;

            if (temp == head)
                cout << " (Active)";

            cout << endl;

            temp = temp->next;
        }
    }


    void activateWindow(string t) {

        if (head == NULL)
            return;

        Window* temp = head;

        while (temp != NULL && temp->title != t) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Window not found\n";
            return;
        }

    
        if (temp == head)
            return;

    
        if (temp->prev != NULL)
            temp->prev->next = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;

    
        temp->next = head;
        temp->prev = NULL;

        head->prev = temp;
        head = temp;
    }

    
    void resizeWindow(string t, int newSize) {

        Window* temp = head;

        while (temp != NULL) {

            if (temp->title == t) {
                temp->size = newSize;
                return;
            }

            temp = temp->next;
        }

        cout << "Window not found\n";
    }

    void deleteWindow(string t) {

        if (head == NULL)
            return;

        Window* temp = head;

        while (temp != NULL && temp->title != t) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Window not found\n";
            return;
        }

        if (temp == head) {

            head = head->next;

            if (head != NULL)
                head->prev = NULL;

            delete temp;
            return;
        }

        
        temp->prev->next = temp->next;

        if (temp->next != NULL)
            temp->next->prev = temp->prev;

        delete temp;
    }
};

int main() {

    WindowManager wm;

    wm.createWindow("Chrome", "Blue");
    wm.createWindow("VS Code", "Black");
    wm.createWindow("YouTube", "Red");

    wm.display();

    cout << "\nAfter Activating VS Code:\n";
    wm.activateWindow("VS Code");
    wm.display();

    cout << "\nAfter Resizing Chrome:\n";
    wm.resizeWindow("Chrome", 200);
    wm.display();

    cout << "\nAfter Deleting YouTube:\n";
    wm.deleteWindow("YouTube");
    wm.display();

    return 0;
}