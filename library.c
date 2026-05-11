#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STUDENTS 100

// Date structure
struct Date {
    int day, month, year;
};

// Book structure
struct Book {
    int id;
    char name[50];
    int quantity;
};

// Student structure
struct Student {
    char name[50];
    int rollNo;
    char bookName[50];
    struct Date issueDate;
    struct Date dueDate;
};

struct Book books[MAX_BOOKS];
struct Student students[MAX_STUDENTS];

int bookCount = 0;
int studentCount = 0;

// Convert date to total days
int dateToDays(struct Date d) {
    return d.year * 365 + d.month * 30 + d.day;
}

// Input date
struct Date inputDate() {
    struct Date d;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}

// Add Book
void addBook() {
    printf("\nEnter Book ID: ");
    scanf("%d", &books[bookCount].id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", books[bookCount].name);

    printf("Enter Quantity: ");
    scanf("%d", &books[bookCount].quantity);

    bookCount++;
    printf("Book added successfully!\n");
}

// Display Books
void displayBooks() {
    printf("\n--- Book List ---\n");
    for(int i = 0; i < bookCount; i++) {
        printf("ID: %d | Name: %s | Quantity: %d\n",
               books[i].id, books[i].name, books[i].quantity);
    }
}

// Issue Book (with validation)
void issueBook() {
    char bookName[50];
    int found = 0;

    printf("\nEnter Student Name: ");
    scanf(" %[^\n]", students[studentCount].name);

    printf("Enter Roll No: ");
    scanf("%d", &students[studentCount].rollNo);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", bookName);

    // Check book availability
    for(int i = 0; i < bookCount; i++) {
        if(strcmp(books[i].name, bookName) == 0) {
            found = 1;

            if(books[i].quantity > 0) {
                strcpy(students[studentCount].bookName, bookName);

                printf("Enter Issue Date\n");
                students[studentCount].issueDate = inputDate();

                printf("Enter Due Date\n");
                students[studentCount].dueDate = inputDate();

                books[i].quantity--;  // decrease quantity
                studentCount++;

                printf("Book issued successfully!\n");
            } else {
                printf("Book is out of stock!\n");
            }
            break;
        }
    }

    if(!found) {
        printf("Book not found in library!\n");
    }
}

// Display Students
void displayStudents() {
    printf("\n--- Issued Students ---\n");
    for(int i = 0; i < studentCount; i++) {
        printf("Name: %s | Roll: %d | Book: %s | Issue: %02d/%02d/%d | Due: %02d/%02d/%d\n",
               students[i].name,
               students[i].rollNo,
               students[i].bookName,
               students[i].issueDate.day,
               students[i].issueDate.month,
               students[i].issueDate.year,
               students[i].dueDate.day,
               students[i].dueDate.month,
               students[i].dueDate.year);
    }
}

// Submit Book
void submitBook() {
    int roll, found = 0;
    struct Date actualDate;

    printf("\nEnter Roll No: ");
    scanf("%d", &roll);

    for(int i = 0; i < studentCount; i++) {
        if(students[i].rollNo == roll) {
            found = 1;

            printf("Enter Actual Submission Date\n");
            actualDate = inputDate();

            int dueDays = dateToDays(students[i].dueDate);
            int actualDays = dateToDays(actualDate);

            int fine = 0;
            if(actualDays > dueDays) {
                fine = (actualDays - dueDays) * 10;
            }

            printf("Fine: ₹%d\n", fine);

            // Increase book quantity back
            for(int k = 0; k < bookCount; k++) {
                if(strcmp(books[k].name, students[i].bookName) == 0) {
                    books[k].quantity++;
                    break;
                }
            }

            // Remove student record
            for(int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;
            printf("Book submitted successfully!\n");
            break;
        }
    }

    if(!found) {
        printf("Student not found!\n");
    }
}

// Main Function
int main() {
    int choice;

    do {
        printf("\n====== Library Management System ======\n");
        printf("1. Add Book\n");
        printf("2. Issue Book\n");
        printf("3. Submit Book\n");
        printf("4. Display Students\n");
        printf("5. Display Books\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: submitBook(); break;
            case 4: displayStudents(); break;
            case 5: displayBooks(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}

