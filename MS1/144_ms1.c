
#include <stdio.h>


// ---------------------------------------
// place function PROTOTYPES below here...
// ---------------------------------------


// user interface tools function PROTOTYPES:

void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);


// application user interface function PROTOTYPES:

int yes(void);
void GroceryInventorySystem(void);
int menu(void);



// ----------------------------------------
// place function DEFINITIONS below here...
// ----------------------------------------


void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

void printTitle(void){
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void printFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");

	if (gTotal > 0) {
		printf("			                                Grand Total:|%12.2f", gTotal);
	}
}

void flushKeyboard(void) {

	char c;

	while ((c= getchar())  != '\n' && c != EOF){ }
}

void pause(void) {

	printf("Press <ENTER> to continue...");
	flushKeyboard();
}

int getInt(void) {

	int a = 0;
	char b = '\0';

	while (b != '\n') {

		scanf("%d%c", &a, &b);
		if (b != '\n') {

			flushKeyboard();
			printf("Invalid integer, please try again: ");
		}
	}
	return a;
}

int getIntLimited(int lowerLimit, int upperLimit) {

	int value = getInt();

	while (value < lowerLimit || value > upperLimit) {

		printf("Invalid value, %d < value < %d: ", lowerLimit , upperLimit);

		value = getInt();
	} 
	return value;

}

double getDouble(void) {

	double a = 0;
	char b = '\0';

	while (b != '\n') {

		scanf("%lf%c", &a, &b);
		if (b != '\n') {

			flushKeyboard();
			printf("Invalid number, please try again: ");
		}
	}
	return a;
}
double getDoubleLimited(double lowerLimit, double upperLimit) {

	double value = getDouble();

	while (value < lowerLimit || value > upperLimit) {

		printf("Invalid value, %lf < value < %lf: ", lowerLimit, upperLimit);

		value = getDouble();
	}
	return value;
}

int yes(void) {

	char i = getchar();
	int response = -1;

	while (response == -1) {
		if (i != 'Y' && i != 'y' && i != 'N' && i != 'n') {
			printf("Only (Y)es or (N)o are acceptable: ");
			flushKeyboard();
			i = getchar();
		}
		else {
			if ( i == 'Y' || i == 'y')
			{
				response =  1;
			}
			else
			{
				response = 0;
			}
		}
	}
	return response;
}

int menu(void) {

	int menuOption;

	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- Delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");

	menuOption = getIntLimited( 0 , 7);

	return menuOption;
} 


void GroceryInventorySystem(void) {

	int menuOption;
	int done = 0;

	welcome();

	printf("\n");

	while (done == 0) {

		menuOption = menu();


		switch (menuOption) {

		case 1:
			printf("List Items under construction!\n");
			pause();
			break;
		
		case 2:
			printf("Search Items under construction!\n");
			pause();
			break;
		case 3:
			printf("Checkout Item under construction!\n");
			pause();
			break;
		case 4:
			printf("Stock Item under construction!\n");
			pause();
			break;
		case 5:
			printf("Add/Update Item under construction!\n");
			pause();
			break;
		case 6:
			printf("Delete Item under construction!\n");
			pause();
			break;
		case 7:
			printf("Search by name under construction!\n");
			pause();
			break;
		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			done = yes();
			break;

		default:
			break;
		}
	}

}