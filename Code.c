#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// 1. Structure definition
struct Student {
    int roll_no;
    char name[50];
    float marks[3];
    float total;
    float average;
};

// Function prototypes using pointers
void calculateResult(struct Student *s);
void addStudents(struct Student *s, int *count);
void displayStudents(struct Student *s, int count);
void searchStudent(struct Student *s, int count);
void saveToFile(struct Student *s, int count);
void retrieveFromFile();

int main() {
    // 2. Array of structures to store at least 5 students
    struct Student students[MAX];
    int count = 0, choice;

    do {
        printf("\n--- Student Record & Result Management System ---\n");
        printf("1. Add Student Records\n");
        printf("2. Display All Records\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Save Records to File\n");
        printf("5. Retrieve and Display Records from File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudents(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                saveToFile(students, count);
                break;
            case 5:
                retrieveFromFile();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// 3 & 4. Function to calculate total and average using a pointer
void calculateResult(struct Student *s) {
    s->total = s->marks[0] + s->marks[1] + s->marks[2];
    s->average = s->total / 3.0;
}

// Function to add student details
void addStudents(struct Student *s, int *count) {
    int n, i;
    printf("How many students do you want to add? (Max %d): ", MAX - *count);
    scanf("%d", &n);

    if (*count + n > MAX) {
        printf("Cannot exceed maximum limit of %d students.\n", MAX);
        return;
    }

    for (i = 0; i < n; i++) {
        struct Student *curr = (s + *count); // Pointer arithmetic
        printf("\nEnter details for Student %d:\n", *count + 1);
        printf("Roll Number: ");
        scanf("%d", &curr->roll_no);
        printf("Name: ");
        scanf(" %[^\n]", curr->name); // Reads full name with spaces

        for (int j = 0; j < 3; j++) {
            printf("Marks in Subject %d: ", j + 1);
            scanf("%f", &curr->marks[j]);
        }

        calculateResult(curr);
        (*count)++;
    }
    printf("Records added successfully!\n");
}

// Function to display all student records in memory
void displayStudents(struct Student *s, int count) {
    if (count == 0) {
        printf("\nNo records available to display.\n");
        return;
    }

    printf("\n%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n", 
           "Roll No", "Name", "Sub 1", "Sub 2", "Sub 3", "Total", "Average");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        struct Student *curr = (s + i);
        printf("%-10d %-20s %-8.2f %-8.2f %-8.2f %-10.2f %-10.2f\n",
               curr->roll_no, curr->name, curr->marks[0], curr->marks[1],
               curr->marks[2], curr->total, curr->average);
    }
}

// Function to search for a student by roll number
void searchStudent(struct Student *s, int count) {
    if (count == 0) {
        printf("\nNo records available to search.\n");
        return;
    }

    int roll, found = 0;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        struct Student *curr = (s + i);
        if (curr->roll_no == roll) {
            printf("\nRecord Found:\n");
            printf("Roll No: %d | Name: %s | Marks: %.2f, %.2f, %.2f | Total: %.2f | Average: %.2f\n",
                   curr->roll_no, curr->name, curr->marks[0], curr->marks[1],
                   curr->marks[2], curr->total, curr->average);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

// 5. Function to save records to a binary file
void saveToFile(struct Student *s, int count) {
    if (count == 0) {
        printf("\nNo records to save.\n");
        return;
    }

    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fwrite(s, sizeof(struct Student), count, fp);
    fclose(fp);
    printf("\n%d record(s) saved to 'students.dat' successfully.\n", count);
}

// 5. Function to retrieve and display records from the file
void retrieveFromFile() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nError opening file or no saved records found!\n");
        return;
    }

    struct Student temp;
    printf("\n--- Records Retrieved from File ---\n");
    printf("%-10s %-20s %-8s %-8s %-8s %-10s %-10s\n", 
           "Roll No", "Name", "Sub 1", "Sub 2", "Sub 3", "Total", "Average");
    printf("----------------------------------------------------------------------------\n");

    while (fread(&temp, sizeof(struct Student), 1, fp) == 1) {
        printf("%-10d %-20s %-8.2f %-8.2f %-8.2f %-10.2f %-10.2f\n",
               temp.roll_no, temp.name, temp.marks[0], temp.marks[1],
               temp.marks[2], temp.total, temp.average);
    }

    fclose(fp);
}