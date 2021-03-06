// -------------------------------------------
//  Name:ALBERTO LAURENZI
//  ID:150954162
//  Email:alaurenzi@myseneca.ca
//	Previous Milestone: Milestone1 - Completed; Milestone2 - Completed; Milestone3 - Completed.
//  Description:Assembly Portion
//	Date: 08/01/2017
// -------------------------------------------

#include <stdio.h>
#include <string.h>

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
#define MAX_ITEM_NO 500
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define DATAFILE "144_fp_items.txt"

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

//Prototypes Milestone2//
double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int noOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
//Prototypes Milestone3//
void search(const struct Item item[], int NoOfRecs);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void updateItem(struct Item* itemptr);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);
//Prototypes Milestone4//
void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);
void trySaveItems(const struct Item item[], char fileName[], int NoOfRecs);

// application user interface function PROTOTYPES:

//Prototypes Milestone1//
int yes(void);
void GroceryInventorySystem(void);
int menu(void);

// ----------------------------------------
// place function DEFINITIONS below here...
// ----------------------------------------

/////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*Milestone1*>>>>>>>>>>>>>>>>>>>>>>>>>>>/
///////////////////////////////////////////////////////////////////////

// Print message of Title Milestone //
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n");
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
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");

	menuOption = getIntLimited(0, 7);

	return menuOption;
}


void GroceryInventorySystem(void) {

	/*
	
	TIPO NOMEVARIABILE [DIMENSIONE]
	struct Item Items[MAX_ITEM_NO];
	struct Item *Items;
	
	*/
	struct Item Items[MAX_ITEM_NO];
	int Hold;
	int menuOption;
	int done = 0;

	welcome();

	if (loadItems(Items, DATAFILE, &Hold) == 0){

		printf("Could not read from %s.\n", DATAFILE);

		return;
	 }

	printf("\n");

	while (done == 0) {

		menuOption = menu();

		switch (menuOption) {

		case 1:
			listItems(Items, Hold);
			pause();
			break;

		case 2:
			search(Items, Hold);
			pause();
			break;
		case 3:
			adjustQuantity(Items, Hold, CHECKOUT);
			trySaveItems(Items, DATAFILE, Hold);
			pause();
			break;
		case 4:
			adjustQuantity(Items, Hold, STOCK);
			trySaveItems(Items, DATAFILE, Hold);
			pause();
			break;
		case 5:
			addOrUpdateItem(Items, &Hold);
			trySaveItems(Items, DATAFILE, Hold);
			pause();
			break;
		case 6:
			printf("Not implemented!\n");
			pause();
			break;
		case 7:
			printf("Not implemented!\n");
			pause();
			break;
		case 0:
			printf("Exit the program? (Y)es/(N)o): ");
			done = yes();
			break;

		default:
			break;
		}
	}

}
////////////////////////////////////////////////////////////////////////////
//>><<<<<<<<<<<<<<<<<<<<<<<<<*End Of Milestone1*>>>>>>>>>>>>>>>>>>>>>>>>>//
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*Milestone2*>>>>>>>>>>>>>>>>>>>>>>>>>>//
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
	item.price = getDoubleLimited(0.01,1000.00);
	printf("%11s: ", "Quantity");
	item.quantity = getIntLimited(1, MAX_QTY);
	printf("Minimum Qty: ");
	item.minQuantity = getIntLimited(0,100);
	printf("%11s: ", "Is Taxed");
	item.isTaxed = yes();
	flushKeyboard();
	return  item;
}

// Display Items in different Format depending on the MinQuanty and if Taxed //
void displayItem(struct Item item, int linear) {

	if (linear == 1) {

		printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.isTaxed ? "Yes" : "No", item.quantity, item.minQuantity, totalAfterTax(item));

		if (item.quantity <= item.minQuantity) {

			printf("***\n");
		}
		else {

			printf("\n");
		}
	}
	else {

		printf("%11s: %d\n", "SKU", item.sku);
		printf("%11s: %s\n", "Name", item.name);
		printf("%11s: %.2lf\n", "Price", item.price);
		printf("%11s: %d\n", "Quantity", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		printf("%11s: %s", "Is Taxed", item.isTaxed ? "Yes\n" : "No\n");

		if (item.quantity <= item.minQuantity) {

			printf("WARNING: Quantity low, please order ASAP!!!\n");
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
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*End of Milestone2*>>>>>>>>>>>>>>>>>>>>>>>>>>>/
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*Milestone3*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/
//////////////////////////////////////////////////////////////////////////

// Search Item.SKU through the Array and display in FORM format //
void search(const struct Item item[], int NoOfRecs) {

	int skuInput;
	int index;
	int i = 0;
	int flag = 0;

	// input
	printf("Please enter the SKU: ");
	skuInput = getIntLimited(SKU_MIN, SKU_MAX);

	// search
	for (i = 0; i < NoOfRecs && flag == 0; i++) {

		flag = locateItem(item, NoOfRecs, skuInput, &index);
	}

	// display
	if (flag == 1) {

		displayItem(item[index], FORM);
	}
	else {

		printf("Item not found!\n");
	}
}
// Update Item.SKU //
void updateItem(struct Item* itemptr) {


	struct Item update_Item;
	printf("Enter new data:\n");
	update_Item = itemEntry(itemptr->sku);
	printf("Overwrite old data? (Y)es/(N)o: ");

	if (yes() == 1) {
		*itemptr = update_Item;
		printf("--== Updated! ==--\n");

	}
	else {

		printf("--== Aborted! ==--\n");
	}
	flushKeyboard();
}

// add Item if Array is not full //
void addItem(struct Item item[], int *NoOfRecs, int sku) {

	struct Item addItem;

	if (*NoOfRecs == MAX_ITEM_NO) {

		printf("Can not add new item; Storage Full!\n");

		return;
	}

	addItem = itemEntry(sku);
	printf("Add Item? (Y)es/(N)o: ");

	if (yes() == 1) {

		item[*NoOfRecs] = addItem;
		(*NoOfRecs)++;
		printf("--== Added! ==--\n");

	}
	else {

		printf("--== Aborted! ==--\n");
	}
	flushKeyboard();
}
// Add or Update Item if already exist //
void addOrUpdateItem(struct Item item[], int* NoOfRecs) {

	int skuInput;
	int index;

	printf("Please enter the SKU: ");
	skuInput = getIntLimited(SKU_MIN, SKU_MAX);

	if (locateItem(item, *NoOfRecs, skuInput, &index) == 1) {

		displayItem(item[index], FORM);

		printf("Item already exists, Update? (Y)es/(N)o: ");

		if (yes() == 1) {
			flushKeyboard();
			updateItem(&item[index]);
		}
		else {

			printf("--== Aborted! ==--\n");
			flushKeyboard();
			return;
		}
	}
	else
	{
		addItem(item, NoOfRecs, skuInput);

	}
}
// adjust Item's Quantity and update Indexed Item //
void adjustQuantity(struct Item item[], int NoOfRecs, int stock) {

	int skuInput;
	int index;
	char message[12];
	int stock_update;
	int stock_input;

	printf("Please enter the SKU: ");
	skuInput = getIntLimited(SKU_MIN, SKU_MAX);

	if (locateItem(item, NoOfRecs, skuInput, &index) == 0) {

		printf("SKU not found in storage!\n");

		return;

	}

	displayItem(item[index], FORM);

	if (stock == STOCK) {

		strcpy(message, "to stock\0");
		stock_update = MAX_QTY - item[index].quantity;
	}
	else {

		strcpy(message, "to checkout\0");
		stock_update = item[index].quantity;
	}

	printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", message, stock_update);
	stock_input = getIntLimited(0, stock_update);


	if (stock_input == 0) {

		printf("--== Aborted! ==--\n");

		return;
	}

	if (stock == STOCK) {

		item[index].quantity += stock_input;
		printf("--== Stocked! ==--\n");
	}
	else
	{
		item[index].quantity -= stock_input;
		printf("--== Checked out! ==--\n");
	}

	if (item[index].quantity < item[index].minQuantity) {
		printf("Quantity is low, please reorder ASAP!!!\n");
	}

}

////////////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*End of Milestone3*>>>>>>>>>>>>>>>>>>>>>>>>>>/
//////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*Milestone4*>>>>>>>>>>>>>>>>>>>>>>>>>>>/
///////////////////////////////////////////////////////////////////////


int main(void) {

	GroceryInventorySystem();

	return 0;
}




// Save Item data in the file pointed by dataFile // 
void saveItem(struct Item item, FILE* dataFile) {

	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, 
		item.isTaxed, item.name);
}

 // Load Item in the file pointed by dataFile //
int loadItem(struct Item* item, FILE* dataFile) {

	return (fscanf(dataFile,"%d,%d,%d,%lf,%d,%20[^\n]", &(*item).sku, &(*item).quantity, &(*item).minQuantity, &(*item).price, &(*item).isTaxed, (*item).name) == 6) ?  1 : 0;
}

// Save Item in the file specified by fileName //
int saveItems(const struct Item item[], char fileName[], int NoOfRecs) {

	FILE *fp = NULL;
	int i;

	// open file in mode Write //
	fp = fopen(fileName, "w");
	
	if (fp == NULL) {

		return 0;
	}
	// search through NoOfrecs //
	for (i = 0; i < NoOfRecs; i++) {

		saveItem(item[i], fp);
	}
	
	// close file and save data //
	fclose(fp);

	return 1;
	
}

// Load saved Items in the file specified by filename //
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr) {

	FILE* fp = NULL;
	int index = 0;

	// open file in mode Read //
	fp = fopen(fileName, "r");

	if (fp == NULL) {

		return 0;
	}
	// Read items while counting the num of the items read //
	while (loadItem(&item[index], fp) == 1) {

		index++;
	}
	// store number of the items read into NoOfRecsPtr pointer //
	*NoOfRecsPtr = index;

	// close file and save data //
	fclose(fp);

	return 1;
}

// function Assembly portion // 

void trySaveItems(const struct Item item[], char fileName[], int NoOfRecs) {

	if (saveItems(item, fileName, NoOfRecs) == 0) {

		printf("could not update data file %s\n", fileName);
	}
}

////////////////////////////////////////////////////////////////////////////////
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*End of Milestone4*>>>>>>>>>>>>>>>>>>>>>>>>>>/
//////////////////////////////////////////////////////////////////////////////