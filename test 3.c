#include <stdio.h> // Standard Input and Output
#include <stdlib.h> // Standard Library
#include <string.h> //String Handling Library

#define MAX_STUDENTS 100

// Structure for storing date
struct Date {
    int day, month, year;
};

// Structure for storing GPA score
struct GPA {
    float math, literature, english, avg;
};

// Structure for storing name
struct Name {
    char surname[20], firstName[20];
};

// Structure for storing student information
struct Student {
    int studentID;
    struct Name name;
    char gender[10];
    struct Date dob;
    struct GPA score;
};

// Global variables
struct Student studentList[MAX_STUDENTS];
int studentCount = 0;

// Open file
void opFile() {
    FILE *fptr;
    // Create or open file
    fptr = fopen("C:\\Users\\Admin\\Desktop\\C and C++\\SM_C.txt", "r");
    // Check to see if the file has been created
    if (fptr == NULL) {
        printf("Error creating or opening file!\n");
        exit(1);
    }
    else {
        printf("File has been opened successfully\n");
    }
    fclose(fptr);
}

// Function to display the program menu
void mainMenu () { //
    printf("\n====== STUDENT MANAGEMENT SYSTEM ======");
    printf("\n1. ADD STUDENTS");
    printf("\n2. DISPLAY STUDENT INFORMATION");
    printf("\n3. EDIT STUDENT INFORMATION");
    printf("\n4. DELETE STUDENT");
    printf("\n5. SAVE STUDENT INFORMATION TO FILE");
    printf("\n6. ARRANGE GPA");
    printf("\n7. READ FILE");
    printf("\n0. EXIT");
    printf ("\n======================================");
}

// Structure for storing GPA score
void addGPA(struct GPA* s) {
    float math, literature, english, avg;
    do {
        printf("Math: ");
        scanf("%f", &math);
        if (math < 0 || math > 10) {
            printf("Math score must be between 0 and 10. Please try again.\n");
        }
    } while (math < 0 || math > 10);

    do {
        printf("Literature: ");
        scanf("%f", &literature);
        if (literature < 0 || literature > 10) {
            printf("Literature score must be between 0 and 10. Please try again.\n");
        }
    } while (literature < 0 || literature > 10);

    do {
        printf("English: ");
        scanf("%f", &english);
        if (english < 0 || english > 10) {
            printf("English score must be between 0 and 10. Please try again.\n");
        }
    } while (english < 0 || english > 10);

    s->math = math;
    s->literature = literature;
    s->english = english;
    s->avg = (math + literature + english) / 3;
}

// Function to add name for a student
void addName(struct Name* n) {
    printf("First name: ");
    scanf("%s", n->firstName);
    printf("Surname: ");
    scanf("%s", n->surname);
}

// Function to add date for a student
void addDate(struct Date* d) {
    int day, month, year;
    do {
        printf("Year: ");
        scanf("%d", &year);
        if (year < 1900 || year > 2023) {
            printf("Please try again.\n");
        }
    } while (year < 1900 || year > 2023);

    do {
        printf("Month: ");
        scanf("%d", &month);
        if (month < 1 || month > 12) {
            printf("Please try again.\n");
        }
    } while (month < 0 || month > 12);

    int leapYear = year / 400;
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            do {
                printf("Day (1-31): ");
                scanf("%d", &day);
                if (day < 1 || day > 31) {
                    printf("Invalid day. Please try again.\n");
                }
            } while (day < 1 || day > 31);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            do {
                printf("Day (1-30): ");
                scanf("%d", &day);
                if (day < 1 || day > 30) {
                    printf("Invalid day. Please try again.\n");
                }
            } while (day < 1 || day > 30);
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                do {
                    printf("Day (1-29): ");
                    scanf("%d", &day);
                    if (day < 1 || day > 29) {
                        printf("Invalid day. Please try again.\n");
                    }
                } while (day < 1 || day > 29);
            } else {
                do {
                    printf("Day (1-28): ");
                    scanf("%d", &day);
                    if (day < 1 || day > 28) {
                        printf("Invalid day. Please try again.\n");
                    }
                } while (day < 1 || day > 28);
            }
            break;
    }

    d->year = year;
    d->month = month;
    d->day = day;
    printf("Day: %d\n",day);
}

// Function to add new student
void newStudent(int m) {
    for
        (int i = 0; i < m; i++) {
        printf("\n*Student %d: \n", i+1);
        struct Student st;
        printf("Student ID: ");
        scanf("%d", &st.studentID);
        printf("Gender: ");
        scanf("%s", st.gender);
        printf("---Name---\n");
        addName(&st.name);
        printf("---Date of Birth---\n");
        addDate(&st.dob);
        printf("---GPA Scores---\n");
        addGPA(&st.score);
        studentList[studentCount++] = st;
    }
}

// Function to display student information
void displayStudent() { // Removed argument since it's not used in the function
    printf("%-15s %-15s %-15s %-12s %-10s %-10s %-15s %-10s %-10s\n",
           "Student ID", "First Name", "Sur Name", "Date", "Gender", "Math", "Literature", "English", "Avg");

    for(int i = 0; i < studentCount; i++){
        printf("%-15d %-15s %-15s %02d/%02d/%-8d %-10s %-10.2f %-15.2f %-10.2f %-10.2f\n",
               studentList[i].studentID, studentList[i].name.firstName, studentList[i].name.surname,
               studentList[i].dob.day, studentList[i].dob.month, studentList[i].dob.year,
               studentList[i].gender, studentList[i].score.math, studentList[i].score.literature,
               studentList[i].score.english, studentList[i].score.avg);
    }
}

// Function to edit information of a student by ID
void editStudentByID(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].studentID == studentID) {
            printf("Current information for student %d:\n", studentID);
            printf("Name: %s %s\n", studentList[i].name.firstName, studentList[i].name.surname);
            printf("Gender: %s\n", studentList[i].gender);
            printf("Date of Birth: %d/%d/%d\n", studentList[i].dob.day,
                   studentList[i].dob.month, studentList[i].dob.year);
            printf("Math Score: %.2f\n", studentList[i].score.math);
            printf("Literature Score: %.2f\n", studentList[i].score.literature);
            printf("English Score: %.2f\n", studentList[i].score.english);

            printf("\nEnter new information for student %d:\n", studentID);
            addName(&studentList[i].name);
            printf("Gender: ");
            scanf("%s", studentList[i].gender);
            printf("Date of Birth:\n");
            addDate(&studentList[i].dob);
            printf("Math Score: ");
            scanf("%f", &studentList[i].score.math);
            printf("Literature Score: ");
            scanf("%f", &studentList[i].score.literature);
            printf("English Score: ");
            scanf("%f", &studentList[i].score.english);
            studentList[i].score.avg = (studentList[i].score.math + studentList[i].score.literature +
                                        studentList[i].score.english) / 3;

            printf("Student information updated successfully.\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", studentID);
}

// Function to edit information of a student by ID
void deleteStudentByID(int studentID) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].studentID == studentID) {
            for (int j = i; j < studentCount - 1; j++) {
                studentList[j] = studentList[j + 1];
            }
            studentCount--;
            printf("Student with ID %d deleted successfully.\n", studentID);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", studentID);
    }
}

// Function to calculate average GPA of all students
float arrGPAAllStudents() {
    float totalScore = 0;
    for (int i = 0; i < studentCount; i++) {
        totalScore += (studentList[i].score.math + studentList[i].score.literature + studentList[i].score.english) / 3;
    }
    return totalScore / studentCount;
}

// Function to read student information from a text file
void readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    char buffer[1000];
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        struct Student st;
        sscanf(buffer, "%d %s %s %d/%d/%d %s %f %f %f %f",
               &st.studentID,
               st.name.firstName,
               st.name.surname,
               &st.dob.day,
               &st.dob.month,
               &st.dob.year,
               st.gender,
               &st.score.math,
               &st.score.literature,
               &st.score.english,
               &st.score.avg);
        studentList[studentCount++] = st;

        if (studentCount >= MAX_STUDENTS) {
            printf("Maximum number of students reached.\n");
            break;
        }
    }

    fclose(file);
}

// Function to save student list to a text file
void saveFile(const char* filename) {
    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error creating or opening file!\n");
        exit(1);
    }

    fprintf(fptr, "%-10s %-20s %-20s %-14s %-16s %-10s %-10s %-10s %-10s\n",
           "Student ID", "First Name", "Sur Name", "Date", "Gender", "Math", "Literature", "English", "Avg");
    for (int i = 0; i < studentCount; i++) {
        fprintf(fptr, "%-10d %-20s %-20s %02d/%02d/%-8d %-10s %10.2f %10.2f %10.2f %10.2f\n",
               studentList[i].studentID, studentList[i].name.firstName, studentList[i].name.surname,
               studentList[i].dob.day, studentList[i].dob.month, studentList[i].dob.year,
               studentList[i].gender, studentList[i].score.math, studentList[i].score.literature,
               studentList[i].score.english, studentList[i].score.avg);
    }
    fclose(fptr);
    printf("Student information saved to file successfully!\n");
}

int main() {
    int choice = 0;
    int n;
    do {
        mainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 0: // EXIT THE PROGRAM
                printf("You have exited the program\n");
                break;
            case 1: // ADD MORE STUDENTS
                printf("Input the number of students: ");
                scanf("%d", &n);
                newStudent(n);
                break;
            case 2: // SHOW STUDENT INFORMATION
                displayStudent();
                break;
            case 3: // EDIT STUDENT INFORMATION
                printf("Enter student ID to edit: ");
                int editID; // Added variable to store student ID
                scanf("%d", &editID);
                editStudentByID(editID);
                break;
            case 4: // DELETE STUDENT INFORMATION
                printf("Enter student ID to delete: ");
                int deleteID;
                scanf("%d", &deleteID);
                deleteStudentByID(deleteID);
                break;
            case 5: // SAVE FILE
                saveFile("C:\\Users\\Admin\\Desktop\\C and C++\\SM_C.txt");
                printf("The file has been saved\n");
                break;
            case 6: // ARRANGE
                printf("Average GPA of all students: %.2f\n", arrGPAAllStudents());
                break;
            case 7: // READ FILE
                readFile("C:\\Users\\Admin\\Desktop\\C and C++\\SM_C.txt");
                break;
            default:
                printf("You entered incorrectly, please select again!\n");
                break;
        }
    }
    while(choice != 0);
    return 0; }
