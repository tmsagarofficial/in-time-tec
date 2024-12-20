#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

int checkFileExists(const char *filename);
void createFile(const char *filename);
void addUser(const char *filename);
void displayUsers(const char *filename);
int updateUser(const char *filename, int userIdToUpdate);
int deleteUser(const char *filename, int userIdToDelete);

int checkFileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

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

void displayUsers(const char *filename)
{
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

    int isEmpty = 1;
    // Reading file and printing users.
    while (fgets(line, sizeof(line), file))
    {
        isEmpty = 0;
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

int updateUser(const char *filename, int userIdToUpdate)
{
    FILE *file = fopen(filename, "r");
    char line[100];
    User currentUser;
    int userFound = 0;
    char buffer[1000] = "";

    if (file == NULL){
        printf("Error: Unable to open files for updating.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ":");
        currentUser.userId = atoi(token);

        if (currentUser.userId == userIdToUpdate)
        {
            userFound = 1;
            printf("Enter new Name: ");
            scanf("%s", currentUser.userName);
            printf("Enter new Age: ");
            scanf("%d", &currentUser.userAge);
            sprintf(buffer, "%d:%s:%d\n", currentUser.userId, currentUser.userName, currentUser.userAge);
        }
        else
        {
            strcat(buffer, line);
            strcat(buffer, "\n");
        }
    }

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL){
        printf("Error: Unable to open files for updating.\n");
        return 0;
    }

    fprintf(file, "%s", buffer);
    fclose(file);

    if (userFound==1)  {
        system("cls");
        printf("User updated successfully.\n");
    }
    else    {
        printf("User with ID %d not found.\n", userIdToUpdate);
    }

    return userFound==1;
}

int deleteUser(const char *filename, int userIdToDelete)
{
    FILE *file = fopen(filename, "r+");
    char line[100];
    User currentUser;
    int userFound = 0;
    int lineNumber = 0;

    if (file == NULL)
    {
        printf("Error: Unable to open files for deletion.\n");
        return 0;
    }

    // Find the line number of the user to be deleted
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, ":");
        currentUser.userId = atoi(token);

        if (currentUser.userId == userIdToDelete)
        {
            userFound = 1;
            break;
        }

        lineNumber++;
    }

    if (userFound)
    {
        fseek(file, -strlen(line) - 1, SEEK_CUR);
        char buffer[1000] = "";
        fgets(line, sizeof(line), file);
        strcat(buffer, line);

        while (fgets(line, sizeof(line), file))
        {
            strcat(buffer, line);
        }

        rewind(file);
        fprintf(file, "%s", buffer);
        fseek(file, 0, SEEK_END);
        fprintf(file, "\n");
        system("cls");
        printf("User deleted successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", userIdToDelete);
    }

    fclose(file);

    return userFound==1;
}

int main()
{
    const char *filename = "users.txt";
    int choice, userId;
    int runnning = 1;

    if (!checkFileExists(filename))    {
        createFile(filename);
    }
    do    {
        
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
            runnning = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (runnning);

    return 0;
}