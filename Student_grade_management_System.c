#include <stdio.h>

#define MAX_STUDENTS 5
#define MAX_SUBJECTS 5
#define NAME_LEN     50


int  totalStudents = 0;                          
char subjectNames[MAX_SUBJECTS][NAME_LEN] = {
    "Economics", "English", "Management", "Psychology", "Programming"
};


typedef struct {
    char name[NAME_LEN];
    int  id;
    float grades[MAX_SUBJECTS]; 
    float average;
    char  letterGrade;
} Student;

Student students[MAX_STUDENTS];

void  printMenu(void);
void  addStudent(void);
void  viewAllStudents(void);
void  viewStudent(int id);
void  editGrades(int id);
void  deleteStudent(int id);
void  displayTopStudent(void);
float computeAverage(float grades[], int count);   
char  getLetterGrade(float average);               
int   findStudent(int id);                         
void  printStudentRow(Student s);                 


int main(void)
{
    int choice, id;

    printf("\n  Welcome to the Student Grade Management System\n");
    printf("       Albukhary International University\n");
        printf("----------------------------------------------\n");

    do {
        printMenu();
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                printf("  Enter Student ID to view: ");
                scanf("%d", &id);
                viewStudent(id);
                break;
            case 4:
                printf("  Enter Student ID to edit grades: ");
                scanf("%d", &id);
                editGrades(id);
                break;
            case 5:
                printf("  Enter Student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case 6:
                displayTopStudent();
                break;
            case 7:
                printf("\n  Thank you for using the Grade Management System!\n\n");
                break;
            default:
                printf("\n  [!] Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}


void printMenu(void)
{
    printf("\n");
        printf("----------------------------------------------\n");

    printf("  MAIN MENU\n");
        printf("----------------------------------------------\n");

    printf("  1. Add Student\n");
    printf("  2. View All Students\n");
    printf("  3. View Student by ID\n");
    printf("  4. Edit Student Grades\n");
    printf("  5. Delete Student\n");
    printf("  6. Display Top Student\n");
    printf("  7. Exit\n");
        printf("----------------------------------------------\n");

}


void addStudent(void)
{
   
    int i;
    float grade;

    if (totalStudents >= MAX_STUDENTS) {
        printf("\n  [!] Student list is full (max %d).\n", MAX_STUDENTS);
        return;
    }

    Student s;
    s.id = totalStudents + 26101000;   

    printf("\n  --- Add New Student ---\n");
    printf("  Student ID (auto): %d\n", s.id);
    printf("  Enter name: ");
    scanf(" %[^\n]", s.name);      

    printf("\n  Enter grades for %d subjects (0 - 100):\n", MAX_SUBJECTS);
    for (i = 0; i < MAX_SUBJECTS; i++) {
        printf("  %s: ", subjectNames[i]);
        scanf("%f", &grade);
      
        if (grade < 0)   grade = 0;
        if (grade > 100) grade = 100;
        s.grades[i] = grade;
    }

   
    s.average     = computeAverage(s.grades, MAX_SUBJECTS);
    s.letterGrade = getLetterGrade(s.average);

    students[totalStudents] = s;
    totalStudents++;

    printf("\n  [✓] Student '%s' (ID: %d) added successfully.\n", s.name, s.id);
    printf("  Average: %.2f | Grade: %c\n", s.average, s.letterGrade);
}


void viewAllStudents(void)
{
    int i;

    printf("\n  --- All Students ---\n");
    if (totalStudents == 0) {
        printf("  No students found.\n");
        return;
    }

        printf("----------------------------------------------\n");

    printf("  %-6s %-20s %-8s %-6s\n", "ID", "Name", "Average", "Grade");
        printf("----------------------------------------------\n");


    for (i = 0; i < totalStudents; i++) {
        printStudentRow(students[i]);  
    }
        printf("----------------------------------------------\n");

    printf("  Total students: %d\n", totalStudents);
}


void printStudentRow(Student s)
{
    printf("  %-6d %-20s %-8.2f %-6c\n",
           s.id, s.name, s.average, s.letterGrade);
}

void viewStudent(int id)
{
    int idx = findStudent(id);   
    int i;

    if (idx == -1) {
        printf("\n  [!] Student ID %d not found.\n", id);
        return;
    }

    Student s = students[idx];
    printf("\n  --- Student Details ---\n");
    printf("  ID   : %d\n", s.id);
    printf("  Name : %s\n", s.name);
        printf("----------------------------------------------\n");

    printf("  %-20s %-8s\n", "Subject", "Grade");
        printf("----------------------------------------------\n");

    for (i = 0; i < MAX_SUBJECTS; i++) {
        printf("  %-20s %.2f\n", subjectNames[i], s.grades[i]);
    }
        printf("----------------------------------------------\n");

    printf("  Average      : %.2f\n", s.average);
    printf("  Letter Grade : %c\n",   s.letterGrade);
}

void editGrades(int id)
{
    int idx = findStudent(id);
    int i;
    float grade;

    if (idx == -1) {
        printf("\n  [!] Student ID %d not found.\n", id);
        return;
    }

    printf("\n  Editing grades for: %s\n", students[idx].name);
    for (i = 0; i < MAX_SUBJECTS; i++) {
        printf("  %s (current: %.2f): ", subjectNames[i], students[idx].grades[i]);
        scanf("%f", &grade);
        if (grade < 0)   grade = 0;
        if (grade > 100) grade = 100;
        students[idx].grades[i] = grade;
    }

    students[idx].average     = computeAverage(students[idx].grades, MAX_SUBJECTS);
    students[idx].letterGrade = getLetterGrade(students[idx].average);

    printf("\n  [✓] Grades updated. New average: %.2f | Grade: %c\n",
           students[idx].average, students[idx].letterGrade);
}

void deleteStudent(int id)
{
    int idx = findStudent(id);
    int i;

    if (idx == -1) {
        printf("\n  [!] Student ID %d not found.\n", id);
        return;
    }

    printf("\n  Deleting student: %s (ID: %d)\n", students[idx].name, id);

    for (i = idx; i < totalStudents - 1; i++) {
        students[i] = students[i + 1];
    }
    totalStudents--;

    printf("  [✓] Student deleted successfully.\n");
}

void displayTopStudent(void)
{
    int   i, topIdx = 0;
    float topAvg    = -1;

    if (totalStudents == 0) {
        printf("\n  No students available.\n");
        return;
    }

    for (i = 0; i < totalStudents; i++) {
        if (students[i].average > topAvg) {
            topAvg  = students[i].average;
            topIdx  = i;
        }
    }

    printf("\n  --- Top Performing Student ---\n");
    viewStudent(students[topIdx].id);
}

float computeAverage(float grades[], int count)
{
    float sum = 0.0f;
    int   i;

    for (i = 0; i < count; i++) {
        sum += grades[i];
    }
    return (count > 0) ? (sum / count) : 0.0f;
}

char getLetterGrade(float average)
{
    if (average >= 90) return 'A';
    else if (average >= 80) return 'B';
    else if (average >= 70) return 'C';
    else if (average >= 60) return 'D';
    else return 'F';
}
int findStudent(int id)
{
    int i;
    for (i = 0; i < totalStudents; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}
