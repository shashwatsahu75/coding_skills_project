#include <bits/stdc++.h>
using namespace std;

#define FILE_STU "students.txt"
#define FILE_CRE "credentials.txt"

string activeUser, activeRole;

bool doLogin() {
    string uIn, pIn;
    cout << "USERNAME: ";
    cin >> uIn;
    cout << "PASSWORD: ";
    cin >> pIn;

    ifstream fin(FILE_CRE);
    if (!fin) {
        cout << "Credential file missing!" << endl;
        return 0;
    }

    string usr, pass, role;
    while (fin >> usr >> pass >> role) {
        if (usr == uIn && pass == pIn) {
            activeUser = usr;
            activeRole = role;
            return 1;
        }
    }
    return 0;
}

void addStu() {
    int r;
    string nm;
    float mk;

    cout << "Roll: ";
    cin >> r;
    cout << "Name: ";
    cin >> nm;
    cout << "Mark: ";
    cin >> mk;

    ofstream fout(FILE_STU, ios::app);
    if (!fout) {
        cout << "Unable to write file!" << endl;
        return;
    }

    fout << r << " " << nm << " ";
    fout << fixed << setprecision(2) << mk << "\n";

    cout << "Student added!" << endl;
}

void showAll() {
    ifstream fin(FILE_STU);
    if (!fin) {
        cout << "No file found!" << endl;
        return;
    }

    cout << "Roll\tName\tMark\n";
    cout << "----\t----\t----\n";

    int r;
    string nm;
    float mk;

    while (fin >> r >> nm >> mk) {
        cout << r << "\t" << nm << "\t";
        cout << fixed << setprecision(2) << mk << "\n";
    }
}

void findStu() {
    int key;
    cout << "Enter roll to search: ";
    cin >> key;

    ifstream fin(FILE_STU);
    if (!fin) {
        cout << "File missing!" << endl;
        return;
    }

    int r;
    string nm;
    float mk;

    while (fin >> r >> nm >> mk) {
        if (r == key) {
            cout << "Found: " << r << " " << nm << " ";
            cout << fixed << setprecision(2) << mk << "\n";
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void removeStu() {
    int key;
    cout << "Roll to delete: ";
    cin >> key;

    ifstream fin(FILE_STU);
    if (!fin) {
        cout << "File not present!" << endl;
        return;
    }

    ofstream temp("temp.txt");
    int r;
    string nm;
    float mk;
    bool ok = false;

    while (fin >> r >> nm >> mk) {
        if (r == key) {
            ok = true;
            continue;
        }
        temp << r << " " << nm << " ";
        temp << fixed << setprecision(2) << mk << "\n";
    }

    fin.close();
    temp.close();

    remove(FILE_STU);
    rename("temp.txt", FILE_STU);

    if (ok) cout << "Student deleted!" << endl;
    else cout << "Roll not found!" << endl;
}

void editStu() {
    int key;
    cout << "Enter roll to update: ";
    cin >> key;

    ifstream fin(FILE_STU);
    if (!fin) {
        cout << "File missing!" << endl;
        return;
    }

    ofstream temp("temp.txt");
    int r;
    string nm;
    float mk;
    bool ok = false;

    while (fin >> r >> nm >> mk) {
        if (r == key) {
            ok = true;
            string nn;
            float nmks;

            cout << "New Name: ";
            cin >> nn;
            cout << "New Mark: ";
            cin >> nmks;

            temp << r << " " << nn << " ";
            temp << fixed << setprecision(2) << nmks << "\n";
        } else {
            temp << r << " " << nm << " ";
            temp << fixed << setprecision(2) << mk << "\n";
        }
    }

    fin.close();
    temp.close();

    remove(FILE_STU);
    rename("temp.txt", FILE_STU);

    if (ok) cout << "Student updated!" << endl;
    else cout << "Roll not found!" << endl;
}

void adminPanel() {
    while (true) {
        cout << "\nADMIN MENU\n";
        cout << "1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout\n";
        int ch;
        cin >> ch;

        if (ch == 1) addStu();
        else if (ch == 2) showAll();
        else if (ch == 3) findStu();
        else if (ch == 4) editStu();
        else if (ch == 5) removeStu();
        else break;
    }
}

void staffPanel() {
    while (true) {
        cout << "\nSTAFF MENU\n";
        cout << "1.Add\n2.Display\n3.Search\n4.Update\n5.Logout\n";
        int ch;
        cin >> ch;

        if (ch == 1) addStu();
        else if (ch == 2) showAll();
        else if (ch == 3) findStu();
        else if (ch == 4) editStu();
        else break;
    }
}

void guestPanel() {
    while (true) {
        cout << "\nGUEST MENU\n";
        cout << "1.Display\n2.Search\n3.Logout\n";
        int ch;
        cin >> ch;

        if (ch == 1) showAll();
        else if (ch == 2) findStu();
        else break;
    }
}

int main() {
    if (!doLogin()) {
        cout << "Invalid login!" << endl;
        return 0;
    }

    cout << "Logged in as: " << activeRole << "\n";

    if (activeRole == "admin") adminPanel();
    else if (activeRole == "staff") staffPanel();
    else guestPanel();

    return 0;
}
