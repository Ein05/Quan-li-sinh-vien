#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Student structure
struct Student {
    char fullName[50];
    char studentID[20];
    float mathScore;
    float literatureScore;
    float englishScore;
};

// Array to store student list
struct Student studentList[100];
int studentCount = 0;

// Function prototypes
void addStudent();
void displayStudent(struct Student student);
void displayAllStudents();
void searchStudentByID(char* studentID);
void editStudentByID(char* studentID);
void deleteStudentByID(char* studentID);
float calculateGPA(struct Student student);
float calculateOverallGPA();
void saveToFile();
void readFromFile();
void displayMenu();

int main() {
    int choice;
    char studentID[20];

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                printf("Enter student ID to search: ");
                scanf("%s", studentID);
                searchStudentByID(studentID);
                break;
            case 4:
                printf("Enter student ID to edit: ");
                scanf("%s", studentID);
                editStudentByID(studentID);
                break;
            case 5:
                printf("Enter student ID to delete: ");
                scanf("%s", studentID);
                deleteStudentByID(studentID);
                break;
            case 6:
                printf("Overall GPA: %.2f\n", calculateOverallGPA());
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                readFromFile();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function to add a new student
void addStudent() {
    struct Student newStudent;
    printf("Enter student's full name: ");
    getchar(); // Clear newline character from buffer
    fgets(newStudent.fullName, sizeof(newStudent.fullName), stdin);
    newStudent.fullName[strcspn(newStudent.fullName, "\n")] = '\0'; // Remove newline character
    printf("Enter student ID: ");
    fgets(newStudent.studentID, sizeof(newStudent.studentID), stdin);
    newStudent.studentID[strcspn(newStudent.studentID, "\n")] = '\0'; // Remove newline character
    printf("Enter math score: ");
    scanf("%f", &newStudent.mathScore);
    printf("Enter literature score: ");
    scanf("%f", &newStudent.literatureScore);
    printf("Enter English score: ");
    scanf("%f", &newStudent.englishScore);

    studentList[studentCount] = newStudent;
    studentCount++;
}

// Function to display information of a student
void displayStudent(struct Student student) {
    printf("Full name: %s\n", student.fullName);
    printf("Student ID: %s\n", student.studentID);
    printf("Math score: %.2f\n", student.mathScore);
    printf("Literature score: %.2f\n", student.literatureScore);
    printf("English score: %.2f\n", student.englishScore);
    printf("GPA: %.2f\n", calculateGPA(student));
}

// Function to display information of all students
void displayAllStudents() {
    printf("Student List:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d:\n", i + 1);
        displayStudent(studentList[i]);
        printf("\n");
    }
}

// Function to search for a student by ID
void searchStudentByID(char* studentID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(studentList[i].studentID, studentID) == 0) {
            printf("Student found:\n");
            displayStudent(studentList[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %s not found.\n", studentID);
    }
}

// Function to edit information of a student by ID
void editStudentByID(char* studentID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(studentList[i].studentID, studentID) == 0) {
            printf("Enter new information for student %s:\n", studentID);
            addStudent();
            studentList[i] = studentList[studentCount - 1]; // Update student information
            studentCount--;
            printf("Student information updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %s not found.\n", studentID);
    }
}

// Function to delete information of a student by ID
void deleteStudentByID(char* studentID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(studentList[i].studentID, studentID) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                studentList[j] = studentList[j + 1];
            }
            studentCount--;
            printf("Student with ID %s deleted successfully.\n", studentID);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %s not found.\n", studentID);
    }
}

// Function to calculate GPA of a student
float calculateGPA(struct Student student) {
    return (student.mathScore + student.literatureScore + student.englishScore) / 3.0;
}

// Function to calculate overall GPA of all students
float calculateOverallGPA() {
    float totalGPA = 0;
    for (int i = 0; i < studentCount; i++) {
        totalGPA += calculateGPA(studentList[i]);
    }
    return studentCount > 0 ? totalGPA / studentCount : 0; // Avoid division by zero
}

// Function to save student list to a text file
void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "Full name: %s\n", studentList[i].fullName);
        fprintf(file, "Student ID: %s\n", studentList[i].studentID);
        fprintf(file, "Math score: %.2f\n", studentList[i].mathScore);
        fprintf(file, "Literature score: %.2f\n", studentList[i].literatureScore);
        fprintf(file, "English score: %.2f\n", studentList[i].englishScore);
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Student information saved to file successfully!\n");
}

// Function to read student list from a text file
void readFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student tempStudent;
    while (fscanf(file, "Full name: %[^\n]\n", tempStudent.fullName) == 1) {
        fscanf(file, "Student ID: %[^\n]\n", tempStudent.studentID);
        fscanf(file, "Math score: %f\n", &tempStudent.mathScore);
        fscanf(file, "Literature score: %f\n", &tempStudent.literatureScore);
        fscanf(file, "English score: %f\n", &tempStudent.englishScore);
        studentList[studentCount] = tempStudent;
        studentCount++;
    }

    fclose(file);
    printf("Student information read from file successfully!\n");
}

// Function to display program menu
void displayMenu() {
    printf("\n-------------- Main menu -------------\n");
    printf("1. Add a new student\n");
    printf("2. Display information of all students\n");
    printf("3. Search for a student by ID\n");
    printf("4. Edit information of a student by ID\n");
    printf("5. Delete information of a student by ID\n");
    printf("6. Calculate overall GPA\n");
    printf("7. Save student information to file\n");
    printf("8. Read student information from file\n");
    printf("0. Exit\n");
    printf("----------------------------------------\n");
}
