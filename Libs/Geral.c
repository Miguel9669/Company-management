#include "Geral.h"
#include "structs.h"
#include "constVariables.h"
#include "Admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/**
 * @brief Converts the company's category to a representative string.
 * @param company The company for which to get the category string.
 * @return The representative string of the category.
 */
static char *categoryString(Company company) {
    static char *string[] = {"Micro Empresa", "Pequena e média empresa", "Grande empresa"};
    return string[company.category - 1];
}

/**
 * @brief Retrieves an integer value from a file, creating the file if it doesn't exist.
 *
 * This function opens a file specified by the given path in binary read mode. If the file does not exist,
 * it creates the file, writes the integer value 0 to it, and reopens it in binary read and write mode.
 * The function then reads an integer value from the file, closes the file, and returns the read integer.
 *
 * @param txt The file path.
 * @return The integer value read from the file.
 */
int getNumberFromFile(char *txt) {
    int var = 0;
    FILE *numberCompanies = fopen(txt, "rb");
    if (numberCompanies == NULL) {
        numberCompanies = fopen(txt, "wb");
        fwrite(&var, sizeof(int), 1, numberCompanies);
        fclose(numberCompanies);
        numberCompanies = fopen(txt, "rb+");
    }
    fread(&var, sizeof(int), 1, numberCompanies);
    fclose(numberCompanies);
    return var;
}

/**
 * @brief Updates an integer value in a file.
 *
 * This function opens a file specified by the given path in binary read and write mode.
 * If the file doesn't exist, it displays an error message and returns. Otherwise, it sets
 * the file position to the beginning, writes the provided integer value to the file, and
 * closes the file.
 *
 * @param number The integer value to be written to the file.
 * @param txt The file path.
 */
void updateNumberFromFile(int number, char *txt) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        puts("We couldn't find that file!!");
    }
    fseek(var, 0, SEEK_SET);
    fwrite(&number, sizeof(int), 1, var);
    fclose(var);
}

/**
 * @brief Updates a structure in a file at a specific position.
 *
 * This function opens a file specified by the given path in binary read and write mode.
 * If the file doesn't exist, it returns without making any changes. Otherwise, it sets
 * the file position to the specified position, writes the provided structure to the file,
 * and then closes the file.
 *
 * @param txt The file path.
 * @param position The position in the file where the structure will be updated.
 * @param company Pointer to the Company structure containing the data to be written.
 * @param structSize The size of the structure in bytes.
 */
void updateStructCompany(char *txt, long position, Company *company, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var != NULL) {
        fseek(var, position, SEEK_SET);
        fwrite(company, structSize, 1, var);
        fclose(var);
    }
}

/**
 * @brief Updates Information structure in a file.
 *
 * This function opens the file specified by the given path in binary write mode. If the
 * file doesn't exist, it creates a new one. Then, it writes the Information structures
 * from the provided Informations object to the file and closes it.
 *
 * @param txt The file path.
 * @param informations Pointer to the Informations object containing the data to be written.
 */
void updateStructInformation(char *txt, Informations *informations) {
    FILE *var = fopen(txt, "wb");
    if (var == NULL) {
        perror(ERROR_OPENING);
        return;
    }
    if (fwrite(informations->information, sizeof(Information), informations->numberInformation, var) != informations->numberInformation) {
        perror(ERROR_WRITING);
    }
    fclose(var);
}

/**
 * @brief Updates comments in a file for all companies.
 *
 * This function opens the file specified by the FILE_FOR_COMMENTS macro in binary write mode.
 * If the file doesn't exist, it creates a new one. Then, it writes the Comment structures for
 * each company to the file and closes it.
 *
 * @param companies Pointer to the Companies object containing the comments data.
 */
void updateComments(Companies *companies) {
    FILE *comments = fopen(FILE_FOR_COMMENTS, "wb");
    for (int i = 0; i < companies->numberCompanies; ++i) {
        fwrite(companies->company[i].comments, sizeof(Comment), companies->company[i].numberComments, comments);
    }
    fclose(comments);
}

/**
 * @brief Loads comments from a file for all companies.
 *
 * This function opens the file specified by the FILE_FOR_COMMENTS macro in binary read mode.
 * If the file doesn't exist, it creates a new one and then opens it. It reads Comment structures
 * from the file for each company and allocates memory for comments. Finally, it closes the file.
 *
 * @param companies Pointer to the Companies object to store the loaded comments.
 */
void loadComments(Companies *companies) {
    FILE *comments = fopen(FILE_FOR_COMMENTS, "rb");
    if (comments == NULL) {
        comments = fopen(FILE_FOR_COMMENTS, "wb");
        fclose(comments);
        comments = fopen(FILE_FOR_COMMENTS, "rb");
    }
    int numberComments = 0;
    for (int i = 0; i < companies->numberCompanies; ++i) {
        companies->company[i].comments = (Comment *) malloc(sizeof(Comment) * companies->company[i].maxComments);
        fseek(comments, sizeof(Comment) * numberComments, SEEK_SET);
        fread(companies->company[i].comments, sizeof(Comment), companies->company[i].numberComments, comments);
        numberComments += companies->company[i].numberComments;
    }
    fclose(comments);
}

/**
 * @brief Updates a specific Activity structure in a file at the specified position.
 *
 * This function opens the file specified by the given file path in binary read and write mode.
 * If the file exists, it moves the file pointer to the specified position and writes the provided
 * Activity structure to the file. Finally, it closes the file.
 *
 * @param txt File path of the file to be updated.
 * @param position Position in the file where the Activity structure should be updated.
 * @param activity Pointer to the Activity structure containing the updated data.
 * @param structSize Size of the Activity structure.
 */
void updateStructActivities(char *txt, long position, Activity *activity, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var != NULL) {
        fseek(var, position, SEEK_SET);
        fwrite(activity, structSize, 1, var);
    }
    fclose(var);
}

/**
 * @brief Loads data into an array of Company structures from a file.
 *
 * This function opens the file specified by the given file path in binary read and write mode.
 * If the file does not exist, it creates the file. Then it reads the data from the file into the
 * array of Company structures. Finally, it closes the file.
 *
 * @param number Number of Company structures to be loaded.
 * @param txt File path of the file to be read.
 * @param company Pointer to the array of Company structures to store the loaded data.
 * @param structSize Size of each Company structure.
 */
void loadStructCompany(int number, char *txt, Company *company, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        var = fopen(txt, "wb");
        if (var == NULL) {
            return;
        }
        fclose(var);
        var = fopen(txt, "rb+");
    }

    if (var != NULL) {
        fread(company, structSize, number, var);
    }
    fclose(var);
}

/**
 * @brief Loads data into an array of Information structures from a file.
 *
 * This function opens the file specified by the given file path in binary read mode. If the file
 * does not exist, it creates the file. Then it reads the data from the file into the array of
 * Information structures. Finally, it closes the file.
 *
 * @param number Number of Information structures to be loaded.
 * @param txt File path of the file to be read.
 * @param information Pointer to the array of Information structures to store the loaded data.
 * @param structSize Size of each Information structure.
 */
void loadStructInformation(int number, char *txt, Information *information, int structSize) {
    FILE *var = fopen(txt, "rb");
    if (var == NULL) {
        var = fopen(txt, "wb");
        fclose(var);
        return;
    }
    fread(information, structSize, number, var);
    fclose(var);
}

/**
 * @brief Finds the user who commented the most on a company.
 *
 * This function takes a Company structure as input and analyzes the comments to determine the user
 * who has made the most comments. It returns the name of the user with the highest comment count
 * and sets the number of comments made by that user in the provided variable.
 *
 * @param company The Company structure containing comments.
 * @param numberComments Pointer to store the number of comments made by the user with the most comments.
 * @return A dynamically allocated string containing the name of the user with the most comments.
 */
char* userCommentedTheMost(Company company, int *numberComments) {
    Name name[company.numberComments];
    int nameCounter[company.numberComments];

    for (int i = 0; i < company.numberComments; ++i) {
        strcpy(name[i].name, company.comments[i].user.name);
        nameCounter[i] = 0;
    }

    for (int i = 0; i < company.numberComments; ++i) {
        nameCounter[i]++;
        for (int j = i + 1; j < company.numberComments; ++j) {
            if (strcmp(name[i].name, name[j].name) == 0) {
                nameCounter[i]++;
                strcpy(name[j].name, "");
            }
        }
    }

    int maxComments = 0;
    char finalName[MAX_NAME];

    for (int i = 0; i < company.numberComments; ++i) {
        if (nameCounter[i] > maxComments) {
            maxComments = nameCounter[i];
            strcpy(finalName, name[i].name);
        }
    }
    *numberComments = maxComments;
    return strdup(finalName);
}

/**
 * @brief Generates a report for a company.
 *
 * This function takes an Informations structure, an index, and a Company structure as input to generate
 * a report for the specified company. It includes information such as the number of visits, rating/visit
 * percentage, and the user who commented the most (if comments exist).
 *
 * @param informations The Informations structure containing visit information.
 * @param index The index of the company in the Informations structure.
 * @param company The Company structure for which the report is generated.
 */
void reportForCompany(Informations informations, int index, Company *company) {
    int searchCounter = informations.information[index].searchCounter;
    int numberCommentsUser;
    char name[MAX_NAME];
    strcpy(name, userCommentedTheMost(*company, &numberCommentsUser));
    char headerTxt[25];
    sprintf(headerTxt,"Report Company: %s!\n", company->nameCompany);
    header(headerTxt);
    printf("Company visits: %d!\n", searchCounter);
    printf("Rating/Visit percentage: %d%%!\n", searchCounter != 0 ?(int)((companyAverageRating(company)/searchCounter) * 100) : 0);
    printf("Comment/Visit percentage: %d%%!\n", searchCounter != 0 ? (int)(((double)company->numberComments/searchCounter) * 100): 0);
    if (company->numberComments > 0)
        printf("The user |%s| was the one who commented the most with %d comments!", name, numberCommentsUser);
}

/**
 * @brief Finds the most searched companies and stores their indices in an array.
 *
 * This function takes a Companies structure, its size, an Informations structure, and an array as input.
 * It finds the companies with the highest search counter and stores their indices in the array. The array
 * is expected to be pre-allocated with sufficient space.
 *
 * @param companies The Companies structure containing company information.
 * @param size The size of the array and the number of companies to find.
 * @param informations The Informations structure containing visit information.
 * @param array The array to store the indices of the most searched companies.
 */
void mostSearchedCompanies(Companies companies, int size, Informations informations, int *array) {
    int actualHighNumbers = 0;

    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        actualHighNumbers = 0;
        for (int j = 0; j < companies.numberCompanies; j++) {
            int searchCounter = informations.information[j].searchCounter;


            int included = 0;
            for (int h = 0; h < i; h++) {
                if (j == array[h]) {
                    included = 1;
                    break;
                }
            }

            if (!included && searchCounter > actualHighNumbers) {
                actualHighNumbers = searchCounter;
                array[i] = j;
            }
        }
    }
}

/**
 * @brief Finds the most rated companies and stores their indices in an array.
 *
 * This function takes a Companies structure, its size, and an array as input.
 * It finds the companies with the highest average rating and stores their indices in the array. The array
 * is expected to be pre-allocated with sufficient space.
 *
 * @param companies The Companies structure containing company information.
 * @param size The size of the array and the number of companies to find.
 * @param array The array to store the indices of the most rated companies.
 */
void mostRatedCompanies(Companies companies, int size, int *array) {
    double actualHighNumbers;
    int counter;
    for(int i = 0; i < size; i++){
        actualHighNumbers = -1;
        for(int j = 0; j < companies.numberCompanies; j++){
            Company company = companies.company[j];
            double companyRate = companyAverageRating(&company);
            if(companyRate > actualHighNumbers){
                counter = 0;
                for(int h = 0; h < size; h++){
                    if(j == array[h]){
                        counter = 1;
                    }
                }
                if(counter == 0){
                    actualHighNumbers = companyRate;
                    array[i] = j;
                }

            }
        }
    }
}

/**
 * @brief Updates information counters and saves the changes to the file.
 *
 * This function takes an Informations structure, an index, and a pointer to an integer as input.
 * It updates the search counters in the Informations structure, increments the value pointed to by the
 * integer pointer, and prints the updated counters. Then, it saves the changes to the file.
 *
 * @param informations The Informations structure containing search counters.
 * @param index The index of the information to be updated.
 * @param valueToAdd A pointer to an integer value to be incremented.
 */
void addToInformation(Informations *informations, int index, int *valueToAdd) {
    informations->information[index].searchCounter++;
    *valueToAdd += 1;
    updateStructInformation(FILE_WITH_EXTRA_INFORMATION, informations);
}

/**
 * @brief Lists the top companies based on either search count or rating.
 *
 * This function takes a Companies structure, an Informations structure, a boolean indicating whether
 * the list is based on search count, and the size of the top list. It then generates a list of the top
 * companies and prints the results.
 *
 * @param companies The Companies structure containing company information.
 * @param informations The Informations structure containing search counters.
 * @param searched A boolean indicating whether the list is based on search count.
 * @param sizeOfTop The size of the top list to be generated.
 */
void listMostCompanies(Companies companies, Informations informations, bool searched, int sizeOfTop){
    if (companies.numberCompanies > 0) {
        int size = companies.numberCompanies >= sizeOfTop ? sizeOfTop : companies.numberCompanies;
        int array[size];
        if (searched) {
            mostSearchedCompanies(companies, size, informations, array);
            char top[sizeof("Top %d Most searched")];
            sprintf(top, "Top %d Most searched", sizeOfTop);
            header(top);
        } else {
            mostRatedCompanies(companies, size, array);
            char top[sizeof("Top %d with the best Rates")];
            sprintf(top, "Top %d with the best Rates", sizeOfTop);
            header(top);
        }
        for (int i = 0; i < size; i++) {
            printf("The %d company is : |%s| ", i + 1, companies.company[array[i]].nameCompany);
            if (searched) {
                printf("with %d\n", informations.information[array[i]].searchCounter);
            } else {
                printf("with %.2lf\n", companyAverageRating(&companies.company[array[i]]));
            }

        }
        if (sizeOfTop > companies.numberCompanies) {
            puts("There is no more companies!");
        }
    } else
        puts("No Companies!!");
}

/**
 * @brief Loads activity data from a file into an array of Activity structures.
 *
 * This function reads activity data from a binary file and stores it in an array of Activity structures.
 *
 * @param number The number of activities to load.
 * @param txt The filename from which to load the activity data.
 * @param activity An array to store the loaded activity data.
 * @param structSize The size of each Activity structure in bytes.
 */
void loadStructActivity(int number, char *txt, Activity *activity, int structSize) {
    FILE *var = fopen(txt, "rb+");
    if (var == NULL) {
        var = fopen(txt, "wb");
        if (var == NULL) {
            return;
        }
        fclose(var);
        var = fopen(txt, "rb+");
    }

    if (var != NULL) {
        fread(activity, structSize, number, var);
    }
    fclose(var);
}

/**
 * @brief Displays comments for a company.
 *
 * This function displays comments for a given company. It provides options for administrators and Companies
 * to view hidden comments and manage comment visibility.
 *
 * @param company Pointer to the Company structure containing comments.
 * @param admin Boolean indicating whether the user is an administrator.
 * @return Returns the index of the selected comment.
 */
int showComments(Company *company, bool admin) {
    int count = 1;
    header("COMMENTS");
    for (int i = 0; i < company->numberComments; ++i) {
        if (company->comments[i].commentHide == false && !admin && strcmp(company->comments[i].user.name, "") != 0) {
            printf("Comment Number: %d, Title: %s\n",
                   count,
                   company->comments[i].title);
            count++;
        } else if(admin) {
            printf("Comment Number: %d, Title: %s, Hide: %s\n",
                   count,
                   company->comments[i].title,
                   company->comments[i].commentHide == false ? "False" : "True");
            count++;
        }
    }
    if (count == 1) {
        puts("No Comments!");
        return 0;
    } else {
        int commentSelected = GetOption("", 1, company->numberComments, false, false, "");
        int opcao;
        do {
            header(company->comments[commentSelected - 1].title);
            printf("User: %s\nContent: %s\n----------------------------------------------------------------\n",
                   company->comments[commentSelected - 1].user.name,
                   company->comments[commentSelected - 1].commentText);
            if (!admin) {
                puts("\n0 Leave");
                opcao = inputNumber("");
            }
            if (admin)
                opcao = 0;
        } while (opcao != 0);
        return commentSelected;
    }
}

/**
 * @brief Converts a boolean variable to a string.
 *
 * This function takes a boolean variable and returns a string representation.
 *
 * @param variable The boolean variable to be converted.
 * @return Returns a string ("false" for false, "true" for true).
 */
char *boolString(bool variable){
    switch (variable) {
        case 0:
            return "false";
        case 1:
            return "true";
    }
}

/**
* @brief Displays detailed information about a company.
*
* This function prints various details about a company, such as its name,
* NIF, activity, address, city, postal code, category, active status, and
        * average rating.
*
* @param company A pointer to the Company structure containing company details.
*/
void showCompany(Company *company){
    header(company -> nameCompany);
    printf("Company Information:\n");
    printf("Name: %s\n", company->nameCompany);
    printf("NIF: %d\n", company->nif);
    printf("Activity: %s\n", company->activity);
    printf("Address: %s\n", company->local.adress);
    printf("City: %s\n", company->local.city);
    printf("Postal Code: %s\n", company->local.codigoPostal);
    printf("Category: %s\n", categoryString(*company));
    printf("Active: %s\n", boolString(company->active));
    printf("Rating average: %.2lf\n", companyAverageRating(company));
}

/**
 * @brief Gets and validates a new name for a company.
 *
 * This function prompts the user to enter a new name for a company and
 * ensures that the name is unique within the existing companies.
 *
 * @param companies A pointer to the Companies structure containing company data.
 * @param index The index of the company in the array to update its name.
 */
void getNameForCompany(Companies *companies, int index) {
    char newName[MAX_NAME_COMPANY];
    getString(newName, MSG_GET_NAME, MAX_NAME_COMPANY);
    if (isCompanyExists(companies, newName, 0, companies->numberCompanies)) {
        do {
            puts("There is a company with that name!!");
            getString(newName, MSG_GET_NAME, MAX_NAME_COMPANY);
        } while (isCompanyExists(companies, newName, 0, companies->numberCompanies));
    }
    strcpy(companies->company[index].nameCompany, newName);
}

/**
 * @brief Gets and validates a new NIF (Tax Identification Number) for a company.
 *
 * This function prompts the user to enter a new NIF for a company and
 * ensures that the entered NIF is valid and unique within the existing companies.
 *
 * @param company A pointer to the Company structure to update its NIF.
 * @param companies A pointer to the Companies structure containing company data.
 * @param numberCompanies The number of existing companies in the array.
 */
void getNifForCompany(Company *company, Companies *companies, int numberCompanies) {
    do {
        company->nif = inputNumber(MSG_GET_NIF);

        if (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1) {
            puts(verifyNif(company->nif) == -1 ? ERROR_NIF : EXISTENT_NIF);
        }
    } while (verifyNif(company->nif) == -1 || isCompanyExists(companies, "", company->nif, numberCompanies) == 1);

}

/**
 * @brief Gets and validates an activity for a company using a specified activity selection function.
 *
 * This function interacts with the user to select an activity for a company based on the provided
 * activity selection function. It continues to prompt until a valid activity option is chosen.
 *
 * @param activities A pointer to the Activities structure containing available activities.
 * @param function A function pointer to the activity selection function.
 * @return Returns the selected activity option.
 */
int getActivityForCompany(Activities *activities, int (*function)(Activities *activities1)) {
    int optionActivity;
    do {
        optionActivity = function(activities);
    } while (optionActivity <= 0);
    return optionActivity;
}

/**
 * @brief Gets and validates the postal code for a company.
 *
 * This function interacts with the user to input and validate the postal code for a company.
 * It continues to prompt until a valid postal code is entered.
 *
 * @param company A pointer to the Company structure to store the postal code.
 */
void getPostalCode(Company *company) {
    do {
        getString(company->local.codigoPostal, MSG_GET_CODPOSTAL, MAX_CODIGO);
        if (!verifyPostalCode(company->local.codigoPostal)) {
            puts("Postal Code invalid!");
        }
    } while (!verifyPostalCode(company->local.codigoPostal));
}

/**
 * @brief Reallocates memory for a dynamic array within a given data structure.
 *
 * This function checks if the current number of elements equals the maximum capacity
 * and reallocates memory if needed. The reallocation increases the capacity by doubling it.
 *
 * @param number The current number of elements in the array.
 * @param max The maximum capacity of the array.
 * @param companies A pointer to the Companies structure if reallocating companies.
 * @param activities A pointer to the Activities structure if reallocating activities.
 * @param informations A pointer to the Informations structure if reallocating information.
 * @param structType An enum indicating the type of structure to be reallocated (COMPANIES, ACTIVITIES, or INFORMATIONS).
 */
void reallocInStruct(int number, int max, Companies *companies, Activities *activities, Informations *informations,typeStruct structType){
    if (structType == COMPANIES) {
        if (max == number) {
            Company *pCompany = (Company *) realloc(companies->company,
                                                    (companies->maxCompanies) * 2 * sizeof(Company));
            if (pCompany != NULL) {
                companies->company = pCompany;
                companies->maxCompanies *= 2;
            } else {
                puts("Error: REALLOC FAIL.");
            }
        }
    } else if (structType == ACTIVITIES) {
        if (max == number) {
            Activity *pActivities = (Activity *) realloc(activities->activities,activities->maxActivities * 2 * sizeof(Activity));
            if(pActivities == NULL){
                puts("Error: Realloc Activity failed!!");
            } else {
                activities->activities = pActivities;
                activities->maxActivities *= 2;
            }
        }
    } else if (structType == INFORMATIONS) {
        if (max == number) {
            Information *pInformation = (Information *) realloc(informations->information, informations->maxInformation * 2 *
                                                                                           sizeof(Information));
            if (pInformation == NULL) {
                puts("Error: Realloc Information failed!!");
            } else {
                informations->information = pInformation;
                informations->maxInformation *= 2;
            }
        }
    }
}

/**
 * @brief Prompts the user for an integer input.
 *
 * This function displays a prompt, reads an integer input from the user, and handles
 * errors if the input is not a valid integer.
 *
 * @param txt The prompt message to display.
 * @return Returns the entered integer if successful, or -1 on error.
 */
int inputNumber(char *txt) {
    int variable;
    printf("%s\n", txt);
    while (scanf(" %d", &variable) != 1) {
        puts("ERROR: Only numbers.");
        cleanBuffer();
        return -1;
    }
    cleanBuffer();
    return variable;
}

/**
 * @brief Clears the input buffer.
 *
 * This function reads and discards any remaining characters in the input buffer,
 * stopping when a newline character or EOF (end-of-file) is encountered.
 */
void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/**
 * @brief Reads a string from the standard input.
 *
 * This function allocates memory for a string and reads it from the standard input.
 * It ensures that the input is properly terminated and does not exceed the specified length.
 *
 * @param txt The prompt to display before reading the string.
 * @param quant The maximum length of the input string.
 * @return Returns a dynamically allocated string containing the user input.
 */
char *inputString(char *txt, int quant) {
    char *var = (char *)malloc(quant + 1);
    size_t len;
    if (var == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        sleep(4);
        exit(EXIT_FAILURE);
    }

    do {

        printf("%s", txt);
        if (fgets(var, quant + 1, stdin) != NULL) {
            len = strlen(var);
            if (len > 1 && var[len - 1] == '\n') {
                var[len - 1] = '\0';
            } else {
                cleanBuffer();
            }
        }
        if (len > quant) {
            puts(INVALID_INPUT);
        }


    } while (len == 0 || len == 1 || len > quant);

    return var;
}

/**
 * @brief Changes the active status of a company based on its activity.
 *
 * This function checks the activity of a company against the activities database
 * and updates its active status accordingly. If the activity is inactive,
 * a message is displayed, and no changes are made.
 *
 * @param activities The database of activities.
 * @param companies The database of companies.
 * @param company The company to update.
 * @param index The index of the company in the database.
 */
void companyChangeActiveStatus(Activities *activities, Companies *companies, Company *company, int index) {
    for (int i = 0; i < activities->numberActivities; i++) {
        if (strcmp(companies->company[index].activity, activities->activities[i].activity) == 0) {
            if (activities->activities[i].Active == true) {
                company->active = companies->company[index].active == true ? false : true;
            } else
                puts("THE ACTIVITY IS INACTIVE!!");
        }
    }
}

/**
 * @brief Changes the active status of an activity.
 *
 * This function toggles the active status of an activity. If the activity is inactive,
 * it is activated; if active, it is deactivated.
 *
 * @param activity The activity to be updated.
 * @param companies The database of companies.
 * @param index The index of the activity in the database.
 */
void activitiesChangeActiveStatus(Activity *activity, Companies *companies, int index) {
    if (activity->Active == false) {
        activeActivity(activity, companies, index);
    } else {
        inactiveActivity(activity, companies, index);
    }
}

/**
 * @brief Verifies the allocation of memory for comments in a company.
 *
 * This function checks if the allocation of memory for comments in a company was successful.
 * If not, it prints an error message and exits the program with failure status.
 *
 * @param company The company to verify.
 */
void verifyNumberComments(Company *company) {
    if (company->comments == NULL) {
        fprintf(stderr, "Error allocating comments\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Creates a name for a new activity.
 *
 * This function prompts the user to input the name of a new activity and checks
 * if an activity with the same name already exists. If it does, the user is prompted
 * to enter a different name until a unique one is provided.
 *
 * @param activities The database of activities.
 */
void createNameActivity(Activities *activities) {
    getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
    if (isActivityExist(activities, activities->activities[activities->numberActivities].activity)) {
        do {
            puts("There is an Activity with that name!!");
            getString(activities->activities[activities->numberActivities].activity, "Name of the Activity: ", ACTIVITY);
        } while (isActivityExist(activities, activities->activities[activities->numberActivities].activity));
    }
}

/**
 * @brief Verifies if a variable is within a specified range.
 *
 * This function checks if a given variable is within the specified range
 * (inclusive). If the variable is within the range, it returns 1; otherwise, it returns 0.
 *
 * @param variable The variable to be verified.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return Returns 1 if the variable is within the range, 0 otherwise.
 */
int verifyNumber(int variable, int min, int max){

    if ((variable < min) || (variable > max)){
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Verifies the validity of a Portuguese NIF (Tax Identification Number).
 *
 * This function checks if a given NIF is valid according to Portuguese rules.
 * If the NIF is valid, it returns the NIF; otherwise, it returns -1.
 *
 * @param nif The NIF to be verified.
 * @return Returns the valid NIF or -1 if invalid.
 */
int verifyNif(int nif) {
    int count = 0;
    while (nif > 0) {
        nif /= 10;
        count++;
    }

    if (count == 9) {
        return nif;
    } else {
        return -1;
    }
}

/**
 * @brief Verifies the validity of a Portuguese postal code.
 *
 * This function checks if a given postal code is valid according to Portuguese rules.
 * If the postal code is valid, it returns 1; otherwise, it returns 0.
 *
 * @param postalCode The postal code to be verified.
 * @return Returns 1 if the postal code is valid, 0 otherwise.
 */
int verifyPostalCode(char *postalCode) {
    if (strlen(postalCode) == 8 && isdigit(postalCode[0]) && isdigit(postalCode[1]) && isdigit(postalCode[2]) && isdigit(postalCode[3])) {
        if (postalCode[4] == '-' && isdigit(postalCode[5]) && isdigit(postalCode[6]) && isdigit(postalCode[7])) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Displays companies associated with a specific activity.
 *
 * This function prints the names of companies associated with a given activity.
 * Only active companies are displayed.
 *
 * @param activities The database of activities.
 * @param companies The database of companies.
 * @param index The index of the activity in the database.
 * @return Returns the number of companies associated with the activity.
 */
int showCompaniesInActivity(Activities *activities, Companies *companies, int index) {
    int count = 0;
    if (isCompanyExistInActivity(&(activities->activities[index]), companies)) {
        header("COMPANIES IN ACTIVITY");
        for (int i = 0; i < companies->numberCompanies; i++) {
            if (strcmp(activities->activities[index].activity, companies->company[i].activity) == 0 && companies->company[i].active) {
                printf("-> ");
                printf("%s\n", companies->company[i].nameCompany);
                count++;
            }
        }
    }
    return count;
}

/**
* @brief Displays information about active activities.
*
* This function prints the names of active activities. If admin is true,
        * inactive activities are also displayed with their indices.
*
* @param activities Pointer to the Activities structure.
* @param admin Boolean indicating admin status.
*/
void showActivity(Activities *activities, bool admin){
    int count = 1;
    if (activities->numberActivities > 0){
        for (int i = 0; i < activities->numberActivities; i++) {
            if (activities->activities[i].Active) {
                printf("%d", count);
                printf(" %s", activities->activities[i].activity);
                printf("\n");
                count++;
            } else {
                if (admin) {
                    count++;
                    printf("%d", i + 1);
                    printf(" %s", activities->activities[i].activity);
                    printf("\n");
                }
            }
        }
        if (count == 0) {
            puts("There is no activity to select!!");
        }
    } else {
        puts("There is no activity to select!!");
    }

}

/**
 * @brief Gets a numeric option within a specified range.
 *
 * This function prompts the user for a numeric option within the specified range,
 * with the option to display a header and additional information.
 *
 * @param txt Prompt message.
 * @param min Minimum allowed option value.
 * @param max Maximum allowed option value.
 * @param showOption Boolean to display option details.
 * @param showHeader Boolean to display a header.
 * @param txtHeader Header message.
 * @return Returns the selected option.
 */
int GetOption(char *txt, int min, int max, bool showOption, bool showHeader, char *txtHeader) {
    int number;
    do {
        if (showHeader){
            header(txtHeader);
        }
        if(showOption){
            puts("\n------------------------------------------------------------------");
        }
        puts(txt);
        number = inputNumber("");
        if (!verifyNumber(number, min, max)) {
            puts("Invalid option!");
        }
    } while (!verifyNumber(number, min, max));
    return number;
}

/**
 * @brief Checks if a company with a given name or NIF exists.
 *
 * This function searches for a company with the specified name or NIF
 * within the given array of companies.
 *
 * @param companies Pointer to the Companies structure.
 * @param name Company name to check.
 * @param nif Company NIF to check.
 * @param numberCompanies Number of companies in the array.
 * @return Returns 1 if the company exists, 0 otherwise.
 */
int isCompanyExists(const Companies *companies, char *name, int nif, int numberCompanies) {
    for (int i = 0; i < numberCompanies; ++i) {
        if (strcmp(name, "") != 0) {
            if (strcmp(companies->company[i].nameCompany, name) == 0) {
                return 1;
            }
        }
        if (nif != 0) {
            if (companies->company[i].nif == nif) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief Checks if an activity with a given name exists.
 *
 * This function searches for an activity with the specified name
 * within the given array of activities.
 *
 * @param activities Pointer to the Activities structure.
 * @param name Activity name to check.
 * @return Returns 1 if the activity exists, 0 otherwise.
 */
int isActivityExist(Activities *activities, char *name) {
    for (int i = 0; i < activities->numberActivities; ++i) {
        if (strcmp(activities->activities[i].activity, name) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Finds the index of a company with a given NIF.
 *
 * This function searches for a company with the specified NIF
 * within the given array of companies.
 *
 * @param companies Pointer to the Companies structure.
 * @param nif Company NIF to search for.
 * @return Returns the index of the company or -1 if not found.
 */
int findCompanyIndexByNif(const Companies *companies, int nif) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (companies->company[i].nif == nif) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Counts the number of companies in a specific category.
 *
 * This function counts and returns the number of active companies
 * in the specified category within the given array of companies.
 *
 * @param companies Pointer to the Companies structure.
 * @param valueCategory Category value to count.
 * @return Returns the count of companies in the category.
 */
int numberCompaniesInCategory(Companies *companies, int valueCategory) {
    int count = 0;
    for (int i = 0; i < companies -> numberCompanies; i++){
        if (companies->company[i].category == valueCategory && companies->company[i].active == true){
            count++;
        }
    }
    return count;
}

/**
 * @brief Checks if a company with a given activity exists.
 *
 * This function searches for a company with the specified activity
 * within the given array of companies.
 *
 * @param activity Pointer to the Activity structure.
 * @param companies Pointer to the Companies structure.
 * @return Returns 1 if the company with the activity exists, 0 otherwise.
 */
int isCompanyExistInActivity(Activity *activity, const Companies *companies) {
    for (int i = 0; i < companies->numberCompanies; ++i) {
        if (strcmp(companies->company[i].activity, activity->activity) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Reads a string from the user.
 *
 * This function prompts the user to input a string and allocates memory to store it.
 *
 * @param dest Pointer to the destination string.
 * @param txt Prompt message.
 * @param charLen Maximum length of the string.
 */
void getString(char *dest, char *txt, int charLen){
    char *variable = inputString(txt, charLen);
    strcpy(dest, variable);
    free(variable);
}

/**
 * @brief Prints a header with a specified title.
 *
 * This function displays a header with a specified title in a consistent format.
 *
 * @param txt Title for the header.
 */
void header(char *txt) {
    puts("\n------------------------------------------------------------------------------------------");
    printf("                      %s\n", txt);
    puts("------------------------------------------------------------------------------------------");
}

/**
 * @brief Calculates the average rating of a company.
 *
 * This function computes and returns the average rating of a given company.
 *
 * @param company Pointer to the Company structure.
 * @return Returns the computed average rating.
 */
double companyAverageRating(Company *company) {
    if ((double)company->sumRates/company->numberRates > 0)
        return (double)company->sumRates/company->numberRates;
    else
        return 0;
}

