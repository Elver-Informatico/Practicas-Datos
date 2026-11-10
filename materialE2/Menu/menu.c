#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "odbc.h"
#include <sql.h>
#include <sqlext.h>

static int ShowMainMenu();
static void ShowProductsMenu();
static int ShowProductsSubMenu();
static void ShowCustomersMenu();
static int ShowCustomersSubMenu();
static void ShowOrdersMenu();
static int ShowOrdersSubMenu();
static void Find();
static void Stock();
static void FindCustomers();
static void ListProducts();
static void Balance();
static void Open();
static void Range();
static void Detail();


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
		ShowCustomersMenu();
            }
                break;

            case 3: {
		  ShowOrdersMenu();
            }
		    break;

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    return 0;
}

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16];

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

 int ShowProductsSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

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

static void SQLQuery(char * statement, char * input, char ** output_columns, int number_columns) {
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

    printf("%s = ", input);
    (void) fflush(stdout);
    if (fgets(x, (int) sizeof(x), stdin) != NULL) {
	if(x[strlen(x)-1] == '\n')
		x[strlen(x)-1] = 0;
        char query[BufferLength + 28];
        /* snprintf is not defined if ansi flag is enabled */
        (void) snprintf(query, (size_t)(BufferLength + 27), statement, x, x, x);

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
    }
    
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
void Stock() {
    SQLQuery("select quantityinstock from products where productcode = '%s';", "ProductId", NULL, 0);
}

void Find() {
    SQLQuery("select productcode, productname from products where productname LIKE '%%%s%%' ORDER BY productcode;", "Nombre del producto", NULL, 0);
}

int ShowCustomersSubMenu() {
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

void ShowCustomersMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice) {
            case 1: {
                FindCustomers();
            	break;
            }

            case 2: {
                ListProducts();
            	break;
            }

            case 3: {
		Balance();
		break;
            }

            case 4: {
		return;
            }
                break;

        }
    } while (nChoice != 4);

}
void FindCustomers() {
    SQLQuery("select customername, contactfirstname, contactlastname, customernumber from customers where contactfirstname LIKE '%%%s%%' OR contactlastname LIKE '%%%s%%' ORDER BY customernumber;", "Nombre de contacto", NULL, 0);
}
void ListProducts() {
    SQLQuery("select productname, SUM(quantityordered) from customers NATURAL JOIN orders NATURAL JOIN orderdetails NATURAL JOIN products where customernumber = '%s' GROUP BY productname ORDER BY MIN(productcode);", "Customernumber", NULL, 0);
}

void Balance() {
    SQLQuery("WITH paid_money(paid_money) AS (SELECT SUM(amount) FROM payments WHERE customernumber = '%s' GROUP BY customernumber), total_money(total_money) AS (SELECT SUM(quantityordered*priceeach) FROM orderdetails NATURAL JOIN Orders WHERE customernumber = '%s' GROUP BY customernumber) select (total_money - paid_money) FROM total_money CROSS JOIN paid_money;", "Customernumber", NULL, 0);
}

int ShowOrdersSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
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

void ShowOrdersMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {
            case 1: {
                Open();
            	break;
            }

            case 2: {
                Range();
            	break;
            }

            case 3: {
		Detail();
		break;
            }

            case 4: {
		return;
            }
                break;

        }
    } while (nChoice != 4);

}
void Open() {
    SQLQuery("select ordernumber from orders where shippeddate IS NULL ORDER BY ordernumber;", "Ordernumber", NULL, 0);
}
void Range() {
    SQLQuery("select ordernumber, orderdate, shippeddate from orders where orderdate BETWEEN SPLIT_PART('%s', ' - ', 1)::date AND SPLIT_PART('%s', ' - ', 2)::date ORDER BY ordernumber;", "Fechas (YYYY-MM-DD - YYYY-MM-DD)", NULL, 0);
}

void Detail() {
    SQLQuery("WITH info AS (SELECT 1 AS orden, 0 AS linea, orderdate::text AS c1, status::text AS c2, NULL::text AS c3 FROM orders WHERE ordernumber = '%s'), coste AS (SELECT 2 AS orden, 0 AS linea, SUM(quantityordered * priceeach)::text AS c1, NULL::text AS c2, NULL::text AS c3 FROM orderdetails WHERE ordernumber = '%s'), prod AS (SELECT 3 AS orden, orderlinenumber AS linea, productcode::text AS c1, quantityordered::text AS c2, priceeach::text AS c3 FROM orderdetails WHERE ordernumber = '%s') SELECT c1, c2, c3 FROM (SELECT * FROM info UNION ALL SELECT * FROM coste UNION ALL SELECT * FROM prod) AS t ORDER BY orden, linea;", "Ordernumber", NULL, 0);
}
