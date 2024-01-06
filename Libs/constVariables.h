#ifndef COMPANY_MANAGEMENT_CONSTVARIABLES_H
#define COMPANY_MANAGEMENT_CONSTVARIABLES_H

#define MENU_START "1 User\n2 Admin\n3 Company\n0 Quit\n"
#define MENU_COMPANY "1 Manage data\n0 Quit"
#define MENU_ADMIN "1 Create\n2 Manage Company\n3 Manage Activity\n4 Reports\n0 Quit"
#define MENU_ADMIN_REPORTS "1 Top %d Most searched\n2 Top %d with the best Rates\n0 Leave"
#define MENU_USER_SEARCH "1 Name\n2 Category\n3 Activity Industry\n0 Leave\n"
#define MENU_INSIDE_COMPANY "1 Make a comment\n2 Rate company\n3 See comments \n0 Go back\n"
#define MENU_SEARCH_BY_CATEGORY "1 Micro Company\n2 Medium and Small Company\n3 Large Company\n"
#define MENU_MANAGE_COMPANY_COMPANY "1 Name\n2 Activity\n3 Address\n4 City\n5 Postal Code\n6 Category\n7 Set Active or inactive\n8 Manage Comments\n9 Reports\n0 Leave"
#define MENU_MANAGE_COMPANY_ADMIN "1 Name\n2 Activity\n3 Address\n4 City\n5 Postal Code\n6 Category\n7 Set Active or inactive\n8 Manage Comments\n9 Delete Company\n0 Leave"
#define MENU_REPORTS_IN_COMPANY_COMPANY "1 Report About Company %s\n0 leave"
#define MAX_NAME 60
#define MAX_EMAIL 100
#define COMMENT 200
#define TITLE 40
#define ACTIVITY 40
#define MAX_CODIGO 9
#define MAX_ADRESS 60
#define MAX_CITY 40
#define MAX_NAME_COMPANY 70
#define SEARCH_COMPANY "SEARCH COMPANY"
#define ADMIN_MENU "Admin Menu"
#define COMPANY_MENU "Company Menu"
#define SEARCH_NOT_FOUND "We couldn't find that company;"
#define SEARCH_NOT_FOUND_IN_CATEGORY "We couldn't find any company!!"
#define INVALID_INPUT "ERROR: INVALID. PLEASE TRY AGAIN."
#define MODIFY_MENU "exchange company data"
#define MSG_GET_NIF "Enter the NIF: "
#define EXISTENT_COMPANY "Existent company, Try again: "
#define EXISTENT_NIF "Existent nif, Try again: "
#define OPERATING_NIF_COMPANY "Target the NIF of the company you intend to operate: "
#define ERROR_NIF "NIF need to be between 100000000 - 999999999: "
#define COMMENT_NUMBER "Which comment you want to delete"
#define DISABLE_COMMENT "Which comment you want to disable"
#define MSG_GET_NAME "Enter the company name: "
#define MSG_GET_ADRESS "Enter the company address: "
#define MSG_GET_CITY "Enter the company city: "
#define MSG_GET_CODPOSTAL "Enter the company Postal Code: "
#define MENU_COMMENTS "1 Delete commentary\n2 Hide/Show commentary\n0 Quit\n"
#define INVALID_EMAIL "Invalid email structure. Please try again.\n"
#define GET_USER_EMAIL "Your email: "
#define GET_USER_NAME "Your name: "
#define FILE_NUMBER_COMPANIES_NAME "numberCompanies.bin"
#define FILE_NUMBER_ACTIVITIES_NAME "numberActivities.bin"
#define FILE_WITH_COMPANIES "companiesList.bin"
#define FILE_WITH_ACTIVITIES "activitiesList.bin"
#define FILE_FOR_COMMENTS "comments.bin"
#define FILE_WITH_EXTRA_INFORMATION "extra.bin"


#endif //COMPANY_MANAGEMENT_CONSTVARIABLES_H
