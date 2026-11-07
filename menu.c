#include <stdio.h>
#include <stdlib.h>
#include "odbc.h"
#include <sql.h>
#include <sqlext.h>

/* #include "menu_template.h" */
/* #ifndef A2BIS_MENU_TEMPLATE_H */
/* #define A2BIS_MENU_TEMPLATE_H */

/* Prototypes:
 * Since in this example this functions are not used outside menu_template
 * it does not make sense to create an include file and export them
 * BUT in your code it will make sense to break this file in many files
 * and create several include files with the prototypes
 *
 * A static function in C is a function that has a scope that is limited
 * to its object file. This means that the static function is only
 * visible in its object file. Therefore,
 * you need to remove the static keyword from the declaration
 * if the function is declared in a file and used in another
 * */

static int ShowMainMenu();
static void ShowProductsMenu();
static int ShowProductsSubMenu();
static void ShowFairyMenu();
static int ShowFairySubMenu();
static void Find();
static void Stock();

/* #endif //A2BIS_MENU_TEMPLATE_H */

/**
 * @file menu_template.c
 * @author rmarabini
 * @date 15 April 2020
 * @brief File containing an example of a menu system with submenus
 *
 * The following program allows a user to select a nursery rhyme
 * or a fairy tail from a menu. The menu has two levels, the top
 * one allows to select between fairy tails or nursery rhymes. The
 * second level (sub-menus) allow to select either a particular
 * rhyme or tail.
 *
 * @see https://bytes.com/topic/c/answers/567136-creating-menus-sub-menus
 */


/**
 * @brief Entry point, shows and process main menu.
 *
 * This function implements a loop that prints the main
 * menu, analyze the user selection and calls the
 * corresponding submenu
 *
 * @return 0 if no error
 * @author rmarabini
 */
int main(void) {
    int nChoice = 0;

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu();
            }
                break;

            case 2: {
                //ShowFairyMenu();
            }
                break;

            case 3: {
                printf("Bye Bye\n\n");
            }

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    return 0;
}


/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author rmarabini
 */

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do {
        printf("Choose sub-menu\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief prints rhyme menu and allows to select an option.
 *
 * @return selected option
 * @author rmarabini
 */

 int ShowProductsSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief Shows and processes the fairy menu.
 *
 * This function implements a loop that prints the fairy
 * menu, analyze the user selection and prints
 * the selected fairy tail
 *
 * @return selected option
 * @author rmarabini
 */

void ShowProductsMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {
            case 1: {
                Stock();
            }
                break;

            case 2: {
                Find();
            }
                break;

            case 3: {
		return;
            }
                break;

        }
    } while (nChoice != 3);

}

void Stock() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char y[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ;
    }

    printf("ProductId = ");
    (void) fflush(stdout);
    while (fgets(x, (int) sizeof(x), stdin) != NULL) {
        char query[BufferLength + 28];
        /* snprintf is not defined if ansi flag is enabled */
        (void) snprintf(query, (size_t)(BufferLength + 27), "select quantityinstock from products where productcode = %s;", x);

	printf("%s\n", query);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("y = %s\n", y);
        }

        ret2 = SQLCloseCursor(stmt);
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
           return ;
        }

        printf("ProductId = ");
        ret = fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return;
    }

    return;
}

void Find() {

}
