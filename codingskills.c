#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    tcgetattr(0, &old);
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return buf;
}
#endif

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];

void title() {
    printf("         STUDENT LOGIN SYSTEM\n");
}

void menuTitle(char *menu) {
    printf("--------------- %s ---------------\n", menu);
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            pass[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else {
            pass[i++] = ch;
            printf("*");
        }
    }
}

int login() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];

    title();

    printf("USERNAME: ");
    scanf("%s", inUser);

    printf("PASSWORD: ");
    inputPassword(inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) return 0;

    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent() {
    title();
    int roll;
    char name[50];
    float mark;

    printf("Roll: ");
    scanf("%d", &roll);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Mark: ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    title();

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student data found!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;

    printf("Roll\tName\tMark\n");
    printf("----\t----\t----\n");

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        printf("%d\t%s\t%.2f\n", roll, name, mark);
    }

    fclose(fp);
}

void searchStudent() {
    title();
    char find[50];
    printf("Enter Name to search: ");
    scanf(" %[^\n]", find);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student data found!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (strcasecmp(name, find) == 0) {
            printf("\nFound: %d %s %.2f\n", roll, name, mark);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) printf("Student not found!\n");
}

void deleteStudent() {
    title();
    int delRoll;
    printf("Enter roll to delete: ");
    scanf("%d", &delRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll)
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        else found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("\nStudent deleted successfully!\n");
    else printf("\nRoll not found!\n");
}

void updateStudent() {
    title();
    int updateRoll;
    printf("Enter roll to update: ");
    scanf("%d", &updateRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            char newName[50];
            float newMark;
            printf("New Name: ");
            scanf(" %[^\n]", newName);
            printf("New Mark: ");
            scanf("%f", &newMark);
            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("\nStudent updated successfully!\n");
    else printf("\nRoll not found!\n");
}

void adminMenu() {
    int c;
    while (1) {
        title();
        menuTitle("ADMIN MENU");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();
        else return;
    }
}

void staffMenu() {
    int c;
    while (1) {
        title();
        menuTitle("STAFF MENU");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else return;
    }
}

void guestMenu() {
    int c;
    while (1) {
        title();
        menuTitle("GUEST MENU");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else return;
    }
}

int main() {
    if (!login()) {
        printf("\nInvalid login!\n");
        return 0;
    }

    printf("Logged in as: %s\n", currentRole);

    if (strcmp(currentRole, "ADMIN") == 0) adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0) staffMenu();
    else guestMenu();

    return 0;
}
