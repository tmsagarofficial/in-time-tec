#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<conio.h>

#define MAX_NAME_LENGTH 15
#define MAX_FILENAME_LENGTH 15
#define MAX_USERS 25

// Object Structure to represent each user.
typedef struct
{
    int userId;
    char userName[MAX_NAME_LENGTH];
    int userAge;
} User;

bool checkFileExists(const char *filename);
void createFile(const char *filename);
void addUser(const char *filename);
void displayUsers(const char *filename);
bool updateUser(const char *filename, int userIdToUpdate);
bool deleteUser(const char *filename, int userIdToDelete);

bool checkFileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

// Creating a new file if it doesn't exist.
void createFile(const char *filename)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error: Unable to create file.\n");
        exit(1);
    }
    fclose(file);
}

// Adding a new user to the file.
void addUser(const char *filename)
{
    User newUser;
    FILE *file = fopen(filename, "a");

    if (file == NULL)
    {
        printf("Error: Unable to open file for adding user.\n");
        return;
    }

    printf("Enter User ID: ");
    scanf("%d", &newUser.userId);

    printf("Enter User Name: ");
    scanf("%s", newUser.userName);

    printf("Enter User Age: ");
    scanf("%d", &newUser.userAge);

    // Writing to file.
    fprintf(file, "%d:%s:%d\n",
            newUser.userId,
            newUser.userName,
            newUser.userAge);

    fclose(file);
    system("cls");
    printf("User added successfully.\n");
}

// Displaying all the users read from the file.
void displayUsers(const char *filename)
{
    system("cls");
    User currentUser;
    FILE *file = fopen(filename, "r");
    char line[100];

    if (file == NULL)
    {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    printf("\nUser List:\n");
    printf("ID\tName\t\tAge\n\n");

    bool isEmpty = true;
    // Reading file and printing users.
    while (fgets(line, sizeof(line), file))
    {
        isEmpty = false;
        
        line[strcspn(line, "\n")] = 0;

        
        char *token = strtok(line, ":");
        if (token)
        {
            currentUser.userId = atoi(token);

            token = strtok(NULL, ":");
            if (token)
            {
                strcpy(currentUser.userName, token);

                token = strtok(NULL, ":");
                if (token)
                {
                    currentUser.userAge = atoi(token);

                    printf("%d\t%s\t\t%d\n",
                           currentUser.userId,
                           currentUser.userName,
                           currentUser.userAge);
                }
            }
        }
    }
    if (isEmpty) {
        printf("No members\n");
    }
    fclose(file);
}

// Updating/Modifying a user's details in the file
bool updateUser(const char *filename, int userIdToUpdate)
{
    FILE *originalFile = fopen(filename, "r");
    FILE *tempFile = fopen("usersCopy.txt", "w");
    char line[100];
    User currentUser;
    bool userFound = false;

    if (originalFile == NULL || tempFile == NULL)
    {
        printf("Error: Unable to open files for updating.\n");
        return false;
    }

    while (fgets(line, sizeof(line), originalFile))
    {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ":");
        currentUser.userId = atoi(token);

        if (currentUser.userId == userIdToUpdate)
        {
            userFound = true;

            printf("Enter new Name: ");
            scanf("%s", currentUser.userName);

            printf("Enter new Age: ");
            scanf("%d", &currentUser.userAge);

            fprintf(tempFile, "%d:%s:%d\n",
                    currentUser.userId,
                    currentUser.userName,
                    currentUser.userAge);
        }
        else
        {

            token = strtok(NULL, ":");
            strcpy(currentUser.userName, token);

            token = strtok(NULL, ":");
            currentUser.userAge = atoi(token);

            fprintf(tempFile, "%d:%s:%d\n",
                    currentUser.userId,
                    currentUser.userName,
                    currentUser.userAge);
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    remove(filename);
    rename("usersCopy.txt", filename);

    if (userFound)
    {
        system("cls");
        printf("User updated successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", userIdToUpdate);
    }

    return userFound;
}

// Deleting a user record by ID in the file.
bool deleteUser(const char *filename, int userIdToDelete)
{
    FILE *originalFile = fopen(filename, "r");
    FILE *tempFile = fopen("usersCopy.txt", "w");
    char line[100];
    User currentUser;
    bool userFound = false;

    if (originalFile == NULL || tempFile == NULL)
    {
        printf("Error: Unable to open files for deletion.\n");
        return false;
    }

    while (fgets(line, sizeof(line), originalFile))
    {

        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ":");
        currentUser.userId = atoi(token);

        if (currentUser.userId != userIdToDelete)
        {

            token = strtok(NULL, ":");
            strcpy(currentUser.userName, token);

            token = strtok(NULL, ":");
            currentUser.userAge = atoi(token);

            fprintf(tempFile, "%d:%s:%d\n",
                    currentUser.userId,
                    currentUser.userName,
                    currentUser.userAge);
        }
        else
        {
            userFound = true;
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    remove(filename);
    rename("usersCopy.txt", filename);

    if (userFound)
    {
        system("cls");
        printf("User deleted successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", userIdToDelete);
    }

    return userFound;
}

int main()
{
    const char *filename = "users.txt";
    int choice, userId;

    // Create file if it doesn't exist
    if (!checkFileExists(filename))
    {
        createFile(filename);
    }

    while (1)
    {
        system("cls");
        printf("\nUser Management System\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addUser(filename);
            break;
        case 2:
            displayUsers(filename);
            break;
        case 3:
            displayUsers(filename);
            printf("Enter User ID to update: ");
            scanf("%d", &userId);
            updateUser(filename, userId);
            break;
        case 4:
            displayUsers(filename);
            printf("Enter User ID to delete: ");
            scanf("%d", &userId);
            deleteUser(filename, userId);
            break;
        case 5:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}