#include <stdio.h>
#define LINEAR 1
#define FORM 0

const double TAX = 0.13;

struct Item {		
	
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];

};

void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);

// Add new function prototypes and definitions //
double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int noOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

// application user interface function PROTOTYPES:

int yes(void);
void GroceryInventorySystem(void);
int menu(void);

// ----------------------------------------
// place function DEFINITIONS below here...
// ----------------------------------------

/////////////////////////////////////////////////////////////////////////
////////////////////////////////*Milestone1*////////////////////////////
///////////////////////////////////////////////////////////////////////

// Print message of Title Milestone //
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
}

void printTitle(void) {
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void printFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal > 0) {
		printf("                                           Grand Total: |%12.2f\n", gTotal);

	}
}
// Function to clear the buffer //
void flushKeyboard(void) {								

	char c;

	while ((c = getchar()) != '\n' && c != EOF) {}
}

void pause(void) {

	printf("Press <ENTER> to continue...");
	flushKeyboard();
}


// Read a Value of type integer from the User keyboard a display a message if the Value is Invalid//
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

// Read a Value of type integer from the User keyboard and check if is between the Lower and Upper limit//
int getIntLimited(int lowerLimit, int upperLimit) {

	int value = getInt();

	while (value < lowerLimit || value > upperLimit) {

		printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);

		value = getInt();
	}
	return value;

}
// Read a Value of type Double  from the User keyboard a display a message if the Value is Invalid//
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
// Read a Value of type integer from the User keyboard and check if is between the Lower and Upper limit//
double getDoubleLimited(double lowerLimit, double upperLimit) {

	double value = getDouble();

	while (value < lowerLimit || value > upperLimit) {

		printf("Invalid value, %lf < value < %lf: ", lowerLimit, upperLimit);

		value = getDouble();
	}
	return value;
}

// Check if the character between Y and N  are accetable //
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
			if (i == 'Y' || i == 'y')
			{
				response = 1;
			}
			else
			{
				response = 0;
			}
		}
	}
	return response;
}
// Menu Option that can be selected by the User //
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

	menuOption = getIntLimited(0, 7);

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
////////////////////////////////////////////////////////////////////////////
/////////////////////////////*End Of Milestone1*///////////////////////////
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
////////////////////////////////*Milestone2*////////////////////////////
///////////////////////////////////////////////////////////////////////



// Calculate the Total Price of the Item included Tax  //
double totalAfterTax(struct Item item) {

	return item.price *(1 + item.isTaxed*TAX) * item.quantity;
}

// Check the quantity of items if low than the Minimum Limit //
int isLowQuantity(struct Item item) {		

	return item.quantity < item.minQuantity ? 1 : 0;
}

// Create Items,  quantity, MIN quantiy,price and if taxed//
struct Item itemEntry(int sku) {

	struct Item item;
	item.sku = sku;

	printf("%11s: %d\n", "SKU", sku);
	printf("%11s: ", "Name");
	scanf("%20[^\n]", item.name);
	flushKeyboard();
	printf("%11s: ", "Price");
	item.price = getDouble();
	printf("%11s: ", "Quantity");
	item.quantity = getInt();
	printf("Minimum Qty: ");
	item.minQuantity = getInt();
	printf("%11s: ","Is Taxed");
	item.isTaxed = yes();
	flushKeyboard();
	return  item;
}

// Display Items in different Format depending on the MinQuanty and if Taxed //
void displayItem(struct Item item, int linear) {

	if (linear == 1) {

		printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|",item.sku,item.name,item.price,item.isTaxed ? "Yes" : "No" ,item.quantity,item.minQuantity,totalAfterTax(item));

		if (item.quantity < item.minQuantity) {

			printf("***\n");
		}
		else {

			printf("\n");
		}
	}
	else {
		
		printf("%11s: %d\n", "SKU", item.sku);
		printf("%11s: %s\n", "Name",item.name);
		printf("%11s: %.2lf\n", "Price",item.price);
		printf("%11s: %d\n", "Quantity",item.quantity);
		printf("Minimum Qty: %d\n",item.minQuantity);
		printf("%11s: %s", "Is Taxed", item.isTaxed ? "Yes" : "No\n");

		if (item.quantity < item.minQuantity) {

			printf("\nWARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}

// Display Items and print the total price//
void listItems(const struct Item item[], int noOfItems) {
	
	int i;
	double grandTot = 0;

	printTitle();

	for (i = 0; i < noOfItems; i++) {

		printf("%-4d", i + 1);
		displayItem(item[i], 1);
		grandTot += totalAfterTax(item[i]);
	}
	printFooter(grandTot);

}
// Find Item and set an index /
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {

	int i;

	for (i = 0; i < NoOfRecs; i++) {

		if (sku == item[i].sku) {

			*index = i;
		
			return 1;
		}  
	}	
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////*End of Milestone2*////////////////////////////
//////////////////////////////////////////////////////////////////////////////

