#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
// Mohammad Abu Shams.
// 1200549

typedef struct node {
	char name[50];
	char activeIngredient[50];
	char category[50];
	char indication[200];
	char expiryDate[50];
	int count;
	char company[50];
	struct node *Left;
	struct node *Right;
} Medicine;
typedef Medicine *TMedicine;

typedef struct {
	char name[50];
	char activeIngredient[50];
	char code[4];
	char category[50];
	char indication[50][50];
	int noOfIndications;
	char expiryDate[50];
	int count;
	char company[50];
} medicine2;

typedef struct {
	int size;
	int noOfMedicine;
	medicine2 **medicine2;
} hashTable;

TMedicine insertMedicine(TMedicine, TMedicine);
TMedicine FindMedicine(TMedicine, char[]);
TMedicine LoadMedicinesIntoTree(TMedicine);
TMedicine searchMedicine(TMedicine, char[]);
TMedicine deleteMedicine(TMedicine, char[]);
TMedicine FindByCompany(TMedicine root, char company[]);

int main() {
	TMedicine root = NULL;
	int choice;
	while (1) {
		printf(" \n 1.Read the file&create the tree\n"); // Menu.
		printf(" 2.Insert a new medicine\n");
		printf(" 3.Find a medicine\n");
		printf(" 4.List the medicines in the tree in alphabetical order\n");
		printf(" 5.List all medicines of same category\n");
		printf(
				" 6.List all medicines that treat a specific disease and specify if available or not\n");
		printf(" 7.Delete a medicine from the tree\n");
		printf(" 8.Delete all medicines from a specific company\n");
		printf(" 9.Save all information to a file called Pharmacy.txt\n");
		printf(" 10.Go to the hash project\n");
		printf(" 11.Exit the program\n");
		printf("Please enter your choice:"); //Enter the choice.
		scanf("%d", &choice);
		switch (choice) {
		case 1: //If 1 selected.
			root = LoadMedicinesIntoTree(root); // Called the function read from file.
			printf(
					"\n------------------------------------------------------------------------------------------------------------------\n");
			ListAllMedicinesBelongAlphabetical(root); //
			printf(
					"\n------------------------------------------------------------------------------------------------------------------\n");
			break;
		case 2: //If 2 selected.
		{
			int e;
			TMedicine New;
			New = (TMedicine) malloc(sizeof(Medicine)); // Reserve a space in memory.
			char name[50], activeIngredient[50], category[50], indication[50],
					expiryDate[50], company[50];
			int count;
			printf("Please Enter An information of the new medicine:\n");
			printf("Enter the name of the medicine: ");
			scanf("%C"); // To store the enter.
			fgets(name, 50, stdin); // To read the lines.
			name[strlen(name) - 1] = '\0'; //To make the last character null instead of \n (new Line).

			printf("Enter the active ingredient of the medicine: ");
			fgets(activeIngredient, 50, stdin);
			activeIngredient[strlen(activeIngredient) - 1] = '\0';

			printf("Enter the category of the medicine: ");
			fgets(category, 50, stdin);
			category[strlen(category) - 1] = '\0';

			printf("Enter the indication of the medicine: ");
			fgets(indication, 50, stdin);
			indication[strlen(indication) - 1] = '\0';

			printf("Enter the expiry date of the medicine: ");
			fgets(expiryDate, 50, stdin);
			expiryDate[strlen(expiryDate) - 1] = '\0';

			printf("Enter the count of the medicine: ");
			scanf("%d", &count);

			printf("Enter the company of the medicine: ");
			scanf("%C");
			fgets(company, 50, stdin);
			company[strlen(company) - 1] = '\0';

			strcpy(New->name, name);
			strcpy(New->activeIngredient, activeIngredient);
			strcpy(New->category, category);
			strcpy(New->indication, indication);
			strcpy(New->expiryDate, expiryDate);
			New->count = count;
			strcpy(New->company, company);

			printf("DONE");
			New->Right = New->Left = NULL; // Right and Left of the tree is NULL.
			insertMedicine(root, New); // Called the function insert.
			break;
		}
		case 3: {
			TMedicine checkMed;
			checkMed = (TMedicine) malloc(sizeof(Medicine));
			char Name[100];
			printf("Enter the name of the medicine you want to search for: ");
			scanf("%C");
			fgets(Name, 100, stdin);
			Name[strlen(Name) - 1] = '\0';
			checkMed = searchMedicine(root, Name);
			if (checkMed != NULL) {
				printf("Medicine found!\n");
				printf(
						"Do you want to update the information of this medicine? (y/n) ");
				char choice;
				scanf("%c", &choice);
				if (choice == 'y')
					updateMedicine(root, checkMed);
			} else
				printf("NOT Found!!\n");
			break;
		}
		case 4: //If 4 selected.
			if (root == NULL)
				printf("Empty Tree,No Medicines yet");
			else {
				printf(
						"\n------------------------------------------------------------------------------------------------------------------\n");
				ListAllMedicinesBelongAlphabetical(root);
				printf(
						"\n----------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 5: { //If 5 selected.
			int available = 0;
			char category[200], e;
			if (root == NULL)
				printf("Empty Tree,No Medicines yet\n\n");
			else {
				printf("Please enter a category name:\n");
				scanf("%c");
				scanf("%[^\n]", category); // To still read until the end of the line (enter).
				printf(
						"\n----------------------------------------------------------------------------------------------------------------------\n");
				ListAllMedicinesBelongCategory(root, category, &available);
				if (available == 0)
					printf("Not Available!!"); // There is no medicine with the same category.
				printf(
						"\n----------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		}

		case 6: {

			char disease[50];
			int count = 0;
			printf("Enter the disease name: ");
			scanf("%c");
			scanf("%[^\n]", disease);
			listByDisease(root, disease, &count);
			if (count == 0)
				printf("Not Available!!\n"); // There is no medicine with this disease.
			break;
		}
		case 7: {

			char nameMedicine[50];
			printf("Enter the name of the medicine you want to delete: \n");
			scanf("%c");
			scanf("%[^\n]", nameMedicine);
			if (root == NULL)
				printf("The Tree Is Empty!\n");
			else
				root = deleteMedicine(root, nameMedicine);
			break;
		}

		case 8: {
			char nameCompany[50];
			printf("Enter the company name: ");
			scanf("%c");
			scanf("%[^\n]", nameCompany);
			TMedicine T;
			T = (TMedicine) malloc(sizeof(Medicine));
			T = FindByCompany(root, nameCompany);
			while (T != NULL) {
				printf("Name:%s\n", T->name);
				root = deleteMedicine(root, T->name);
				T = FindByCompany(root, nameCompany);
			}
			break;
		}
		case 9: {
			FILE *fp = fopen("Pharmacy.txt", "w"); // Open the output file in write mode.
			if (fp == NULL) {
				printf("Error opening Pharmacy.txt file.");
				return 1;
			}
			saveToFile(root, fp);
			fclose(fp);
			printf("done");
			break;
		}
		case 10: // Go to hash project.
		{
			hashProject();

			break;
		}

		case 11: //If 11 selected.
			exit(0); // End.
			break;
		default:
			printf("ERROR! enter the number between 1-11 please!");
			break;
		}
	}
	return 0;
}
TMedicine LoadMedicinesIntoTree(TMedicine T) //Create a function to load all medicines in file( Meds.txt ) to the tree.
{
	//T = MakeEmpty( T );
	FILE *medicinesFile;
	medicinesFile = fopen("Meds.txt", "r"); //Open the file.
	if (medicinesFile != NULL) //If there is information in the file
	{
		while (!feof(medicinesFile)) // Still reading the file until end of file.
		{
			TMedicine med;
			med = (TMedicine) malloc(sizeof(Medicine)); // Reserve a space in memory.
			fscanf(medicinesFile, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%d:%[^\n]",
					med->name, med->activeIngredient, med->category,
					med->indication, med->expiryDate, &med->count,
					med->company); // Read from the file.
			fgetc(medicinesFile); // Used to read a character (new line) at the end of the line.
			T = insertMedicine(T, med); // To insert the information to the tree.
		}
		printf("DONE!!\n\n"); //Print this for user to ensure that the reading operation is done.
		fclose(medicinesFile); //Close the input file.
	} else {
		printf("Not Found  medicines file\n"); //File not found!.
	}

	return T;
}
TMedicine insertMedicine(TMedicine root, TMedicine New) { // Function to insert a new medicine.

	if (root == NULL) //Check if the root equal NULL.
	{
		root = (TMedicine) malloc(sizeof(Medicine)); // Reserve a space in memory.
		if (root == NULL) //If it is still NULL.
			printf("Out of space\n"); // There is no space.
		else {
			root = New; // Make the new node (medicine) is the root.
			New->Left = New->Right = NULL; // The right and the left of the root is NULL.
		}
	}
	if (strcasecmp(New->name, root->name) < 0) // Go left if the new medicine is less than root.
		root->Left = insertMedicine(root->Left, New);
	else if (strcasecmp(New->name, root->name) > 0) // Go right if the new medicine is greater than root.
		root->Right = insertMedicine(root->Right, New);
	return root;
}

TMedicine searchMedicine(TMedicine root, char name[]) { // Function to search for a medicine.

	if (root == NULL)
		return NULL;
	else if (strcasecmp(root->name, name) == 0) // The medicine exist.
		return root;
	else if (strcasecmp(name, root->name) < 0)
		return searchMedicine(root->Left, name); // Go left if the entered medicine is less than root.
	else
		return searchMedicine(root->Right, name); // Go right if the entered medicine is greater than root.
}

void updateMedicine(TMedicine root, TMedicine New) { // Function to update all information for the medicine.
	printf("\tMenu\t\n");
	printf("1-Update the information of a medicine.\n");
	printf("2-Update the quantity of a medicine.\n");
	printf("(Any Number)Exit\n");
	printf("Enter your option:\n");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("Please enter a new information of medicine:\n");
		char name[50], activeIngredient[50], category[50], indication[50],
				expiryDate[50], company[50];
		int count;
		printf("Enter the name of the medicine: ");
		scanf("%C");
		fgets(name, 50, stdin); // To take the two words with space if it is exist.
		name[strlen(name) - 1] = '\0';

		printf("Enter the active ingredient of the medicine: ");
		//scanf("%C");
		fgets(activeIngredient, 50, stdin);
		activeIngredient[strlen(activeIngredient) - 1] = '\0';

		printf("Enter the category of the medicine: ");
		//scanf("%C");
		fgets(category, 50, stdin);
		category[strlen(category) - 1] = '\0';

		printf("Enter the indication of the medicine: ");
		//scanf("%C");
		fgets(indication, 50, stdin);
		indication[strlen(indication) - 1] = '\0';

		printf("Enter the expiry date of the medicine: ");
		//scanf("%C");
		fgets(expiryDate, 50, stdin);
		expiryDate[strlen(expiryDate) - 1] = '\0';

		printf("Enter the count of the medicine: ");
		scanf("%d", &count);

		printf("Enter the company of the medicine: ");
		scanf("%C");
		fgets(company, 50, stdin);
		company[strlen(company) - 1] = '\0';

		root = deleteMedicine(root, New->name); // If update the root.

		TMedicine T;
		T = (TMedicine) malloc(sizeof(Medicine)); // Reserve a space in memory.

		strcpy(T->name, name);
		strcpy(T->activeIngredient, activeIngredient);
		strcpy(T->category, category);
		strcpy(T->indication, indication);
		strcpy(T->expiryDate, expiryDate);
		T->count = count;
		strcpy(T->company, company);
		T->Left = T->Right = NULL;
		root = insertMedicine(root, T);
	} else if (choice == 2) // Update the count only.
			{
		printf("Please enter a new quantity:\n");
		int count;
		scanf("%d", &count);
		New->count = count;
	}

}
TMedicine MakeEmpty(TMedicine m) { // Function to make empty the tree.
	if (m != NULL) {
		MakeEmpty(m->Left);
		MakeEmpty(m->Right);
		free(m);
	}
	return NULL;

}
void ListAllMedicinesBelongAlphabetical(TMedicine t) // Function to print the medicines alphabetically.( in order -left-root-right).
{
	if (t != NULL) //Check if the tree is NULL.
	{
		ListAllMedicinesBelongAlphabetical(t->Left); //Call the print function on the left subtree of the root.
		printf(
				"name:%s\tactiveIngredient:%s\tcategory:%s\tindication:%s\texpiryDate:%s\tcount:%d\tcompany:%s\n\n",
				t->name, t->activeIngredient, t->category, t->indication,
				t->expiryDate, t->count, t->company);
		ListAllMedicinesBelongAlphabetical(t->Right); //Call the print function on the right subtree of the root.
	}
}
void listByDisease(TMedicine root, char disease[], int *count) { // Function to print the medicine that treated the entered disease.
	if (root == NULL) {
		return;
	}
	listByDisease(root->Left, disease, count);
	if (strstr(root->indication, disease) != NULL) { // If found the entered disease.
		printf("%s: available in this medicine\n", root->name);
		(*count)++; // The number of the medicines that that treated the entered disease.
	}
	listByDisease(root->Right, disease, count);
}
void ListAllMedicinesBelongCategory(TMedicine t, char c[], int *avb) // Function to print the medicines with the same category.
{
	if (t != NULL) //Check if the tree is NULL.
	{
		ListAllMedicinesBelongCategory(t->Left, c, avb); // Call the print function on the left subtree of the root.
		if (strcmp(t->category, c) == 0) // Check if the category name in the root is the same that it was given.
				{
			(*avb)++;
			printf(
					"name:%s\tactiveIngredient:%s\tcategory:%s\tindication:%s\texpiryDate:%s\tcount:%d\tcompany:%s\n\n",
					t->name, t->activeIngredient, t->category, t->indication,
					t->expiryDate, t->count, t->company);
		} // Print the information.
		ListAllMedicinesBelongCategory(t->Right, c, avb); //call the print function on the right subtree of the root.
	}
}
TMedicine findMin(TMedicine root) { // Function to find the minimum value in the left to become the root.
	if (root != NULL) {
		while (root->Left != NULL)
			root = root->Left;
	}
	return root;
}
TMedicine deleteMedicine(TMedicine root, char name[]) { // Function to delete the medicine.
	TMedicine temp;
	if (root == NULL) {
		printf("Medicine Not Found!\n");
	} else if (strcasecmp(name, root->name) < 0) {
		root->Left = deleteMedicine(root->Left, name);
	} else if (strcasecmp(name, root->name) > 0) {
		root->Right = deleteMedicine(root->Right, name);
	} else {
		if (root->Left == NULL && root->Right == NULL) {
			free(root); // Delete
			root = NULL;
		} else if (root->Left == NULL) {
			temp = root;
			root = root->Right;
			free(temp);
		} else if (root->Right == NULL) {
			temp = root;
			root = root->Left;
			free(temp);
		} else {
			temp = findMin(root->Right); // Find the minimum value in the left to become the root.
			strcpy(root->name, temp->name);
			root->Right = deleteMedicine(root->Right, temp->name);
		}
	}
	return root;
}
TMedicine FindByCompany(TMedicine root, char company[]) { // Function to delete the medicine by the name of the company.
	if (root != NULL) {
		if (strcmp(root->company, company) == 0) // The company is exist.
			return root;
		TMedicine T = FindByCompany(root->Left, company);
		if (T != NULL)
			return T;

		return FindByCompany(root->Right, company);

	}
	return NULL;

}

void saveToFile(TMedicine root, FILE *fp) { // Function to save the data to the output file.
	if (root == NULL) {
		return;
	}
	saveToFile(root->Left, fp);
	fprintf(fp, "%s:%s:%s:%s:%s:%d:%s\n", root->name, root->activeIngredient,
			root->category, root->indication, root->expiryDate, root->count,
			root->company);
	saveToFile(root->Right, fp);

}
// PROJECT 2 !!
int collisions = 0;
void addMedicineToLinear(medicine2, hashTable*);
hashTable* createHashTable(hashTable*, int);

char* trim(char *str) { // Remove all spaces from the string in the first and in the last.
	int len = strlen(str);
	while (isspace(str[0]) || isspace(str[len - 1])) {
		if (isspace(str[0])) //Check if the first character is space.
			for (int j = 0; j < len; j++) { //Delete the space and shift the string to the left.
				str[j] = str[j + 1];
			}
		if (isspace(str[len - 1])) // Check if last character is space.
			str[len - 1] = '\0';
	}
	return str;
}

void readPharmacyFile(hashTable *linearTable) { // Function to read the medicines from the file.

	FILE *Pharmacy;
	Pharmacy = fopen("Pharmacy.txt", "r"); // Open the file.
	if (Pharmacy == NULL) {
		printf("File not Found\n"); // There is no thing in the file.
		return; // Out.
	}

	char *token, temp[300];
	int i = 0;

	while (fgets(temp, 300, Pharmacy)) {
		medicine2 medicine2; //To store the medicines info temporary before insert it to the tree.
		medicine2.count = 0;
		char indication[200];

		temp[strlen(temp) - 1] = '\0'; //To make the last character null instead of \n (new Line).
		int count = 0;
		token = strtok(temp, ":"); //Split the line according to :
		while (token != NULL) { //Assign each token to it's field.
			if (count == 0)
				strcpy(medicine2.name, trim(token)); //Assign name of the medicine.

			else if (count == 1) //Assign active ingredient hours.
				strcpy(medicine2.activeIngredient, trim(token));

			else if (count == 2) //Assign category of the medicine.
				strcpy(medicine2.category, trim(token));

			else if (count == 3) //Assign indications of the medicine.
				strcpy(indication, trim(token));

			else if (count == 4) //Assign exipryDate of the medicine.
				strcpy(medicine2.expiryDate, trim(token));

			else if (count == 5) //Assign count of the medicine.
				medicine2.count = atoi(trim(token)); // Convert the integer to string.

			else { //Assign company of the medicine.
				strcpy(medicine2.company, trim(token));
			}
			token = strtok(NULL, ":");
			count++;
		}
		int j = 0;
		medicine2.noOfIndications = 0;
		token = strtok(indication, ","); // Split the indications according to ,
		while (token != NULL) {
			strcpy(medicine2.indication[j], trim(token));
			medicine2.noOfIndications++;
			token = strtok(NULL, ",");
			j++;
		}
		medicine2.code[0] = medicine2.name[0];
		medicine2.code[1] = medicine2.name[1];
		medicine2.code[2] = medicine2.name[2];
		medicine2.code[3] = '\0'; // The code contain the first 3 character from the name to hash using these character.

		addMedicineToLinear(medicine2, linearTable); // Add medicines to the linear hashing.
		i++;
	}
	printf("File Loaded\n");
	fclose(Pharmacy); // Close the file.
}

void readFromUser(hashTable *linearTable) { //Function to Add new medicine from the user and insert it to the table.
	medicine2 c;
	char indication[200];
	c.count = 0;
	char temp[300], *token;
//Read medicine information from the user.
	printf(
			"Enter medicine name, active ingredient, category, expiry date, count, company(each separated by : ):\n");
	scanf("%c"); // To store the enter (insert).
	fgets(temp, sizeof temp, stdin); // To read the lines.
	temp[strlen(temp) - 1] = '\0'; //To make the last character null instead of \n (new Line).
	strcpy(c.name, trim(strtok(temp, ":")));
	strcpy(c.activeIngredient, trim(strtok(NULL, ":")));
	strcpy(c.category, trim(strtok(NULL, ":")));
	strcpy(c.expiryDate, trim(strtok(NULL, ":")));
	c.count = atoi(trim(strtok(NULL, ":")));
	strcpy(c.company, trim(strtok(NULL, ":")));
	printf("Enter indications(each separated by comma):");

//Reading indications from the user then separate it and insert it to the table.
	scanf("%c"); // To store the enter.
	fgets(temp, sizeof temp, stdin); // To read the lines.
	temp[strlen(temp) - 1] = '\0'; //To make the last character null instead of \n (new Line).
	token = strtok(temp, ","); // Splitting according to coma.
	c.noOfIndications = 0;
	for (int i = 0; token != NULL; i++) {
		strcpy(c.indication[i], trim(token));
		c.noOfIndications++; //Number of indications to print them instead of print all.
		token = strtok(NULL, ",");
	}
	addMedicineToLinear(c, linearTable);
	printf("medicine Added To The Tables!!!\n"); // Done.

}

void copyMedicine(medicine2 *c1, medicine2 c2) { //Copy medicine information to other medicine variable ( medicine to the address of the pointer).
	strcpy(c1->name, c2.name);
	strcpy(c1->activeIngredient, c2.activeIngredient);
	strcpy(c1->code, c2.code);
	strcpy(c1->category, c2.category);
	c1->count = c2.count;
	strcpy(c1->company, c2.company);
	strcpy(c1->expiryDate, c2.expiryDate);
	c1->noOfIndications = c2.noOfIndications;

	for (int i = 0; i < c2.count; i++) {
		strcpy(c1->indication[i], c2.indication[i]);
	}
}
int nextPrime(int n) { //Find the first prime number > n.

	while (!isPrime(++n)) {

	}
	return n;
}

int isPrime(int n) { //Check if the number is prime.
	if (n < 2)
		return 0;
	for (int i = 2; i < sqrt(n); i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;

}

void reHashLinear(hashTable *ht) { //Rehash the hash table.
	int size = ht->size * 2;
	size = nextPrime(size); // The new size = prime number >2*old size.

	medicine2 **temp = ht->medicine2;
	medicine2 **newTable = (medicine2*) malloc(sizeof(medicine2*) * size); // Reserve a space in memory.
	for (int j = 0; j < size; j++) {
		newTable[j] = NULL;
	}
	ht->medicine2 = newTable;

	int oldSize = ht->size;
	ht->size = size;
	ht->noOfMedicine = 0;

	for (int i = 0; i < oldSize; i++) {
		if (temp[i] == NULL)
			continue;

		addMedicineToLinear(*temp[i], ht);
		free(temp[i]);
	}
}
void addMedicineToLinear(medicine2 c, hashTable *ht) { //Add a medicine to the linear hash table.

	if (((int) (0.75 * (ht->size))) <= ht->noOfMedicine) { //Rehash the linear table if its 0.75 ( the load factor ).
		reHashLinear(ht); // Rehash.

	}
	int index = linearHashing(c.code, ht); // To put the medicines in the new table.
	ht->medicine2[index] = (medicine2*) malloc(sizeof(medicine2));
	copyMedicine(ht->medicine2[index], c);
	ht->noOfMedicine++;

}
hashTable* createHashTable(hashTable *ht, int tableSize) { //Create hash table with initial cells.
	ht = (hashTable*) malloc(sizeof(hashTable)); // Reserve a space in memory.
	if (ht == NULL)
		printf("Out of space\n");

	ht->medicine2 = (medicine2**) malloc(sizeof(medicine2*) * tableSize);
	if (ht->medicine2 == NULL)
		printf("Out of space\n");
	ht->noOfMedicine = 0;
	ht->size = tableSize;
	for (int i = 0; i < tableSize; i++) { //Make the array empty.
		ht->medicine2[i] = NULL;
	}

	return ht;
}

long hash(char *name) { //String hashing.

	long n = 0;

	while (*name != '\0')
		n = ((n << 5) + *name++);

	return abs(n);
}

int linearHashing(char *code, hashTable *ht) { //Find the index for linear hashing.
	long n = hash(code);
	int index = n % ht->size;
	for (int i = 1; ht->medicine2[index] != NULL && i != ht->size; i++) {
		index = (n + i) % ht->size;

	}
	return index;
}

void printMedicineInfo(medicine2 c) { //Print information of a medicine.
	printf(
			"medicine name:%s\t Code:%s \tActiveIngredient:%s\t Category:%s\t expiryDate: %s \t count: %d\t company: %s"
					"\tIndications:", c.name, c.code, c.activeIngredient,
			c.category, c.expiryDate, c.count, c.company);

	for (int i = 0; i < c.noOfIndications; i++) { //Print indications.
		printf("%s", c.indication[i]);
		if (i != c.noOfIndications - 1)
			printf(", ");
	}
}

void printTableWithEmpty(hashTable *linearTable) { //Print hashed tables (including empty spots).

	printf(
			"*************************************************************************************************************\n");
	printf("Linear hash table:\n");

	for (int i = 0; i < linearTable->size; i++) {
		printf("*index %d : ", i);
		if (linearTable->medicine2[i] != NULL)
			printMedicineInfo(*linearTable->medicine2[i]);
		printf("\n");
	}
	printf(
			"************************************************************************************************************\n");
}

int searchTable(char *name, hashTable *ht) { //Search for medicine.

	char code[4];
	code[0] = name[0];
	code[1] = name[1];
	code[2] = name[2];
	code[3] = '\0';
	long h = hash(code);
	int index = h % ht->size;
	collisions = 0; //More than one value to be hashed by a particular hash function hash to the same slot in the table.

//Keep scanning until find the element or reach the end of the table.
	for (int i = 1; i < ht->size; i++) {
		if (strcasecmp(ht->medicine2[index]->name, name) == 0)
			return index;
		collisions++;
		index = (h + i) % ht->size; // Insertion.
	}
	return -1;
}

void deleteMedicineFromTable(char *name, hashTable *ht) { //Delete a specific record.
	printf("Name: %s\n", name);
	int index = searchTable(name, ht); //Find the index in linear table.
	if (index < 0) {
		printf("Medicine Not Found\n");
	} else {
		free(ht->medicine2[index]);

		ht->medicine2[index] = NULL;
		printf("Deleted From Table\n");
	}
}

void saveToFile2(FILE *out, hashTable *ht) { //Save the table to a file.
	out = fopen("Pharmacy.txt", "w");

	for (int i = 0; i < ht->size; i++) {
		if (ht->medicine2[i] == NULL) {
			continue;
		}
		medicine2 c;

		copyMedicine(&c, *ht->medicine2[i]);
		fprintf(out, "%s:%s:%s:", c.name, c.activeIngredient, c.category);

		for (int i = 0; i < c.noOfIndications; i++) {
			fprintf(out, "%s", c.indication[i]);
			if (i != c.noOfIndications - 1)
				fprintf(out, ", ");
		}
		fprintf(out, "%s:%d:%s", c.expiryDate, c.count, c.company);
		fprintf(out, "\n");
	}
	fclose(out); // Closed the file..
}

void hashProject() {
	FILE *out;
	hashTable *linearTable;
	linearTable = createHashTable(linearTable, 7);

	readPharmacyFile(linearTable); //Read medicine file.

	int menu;
	while (1) {
		printf(
				"================================================================================================================\n");
		printf("1. Print hashed table\n");
		printf("2. Print the size of hash table\n");
		printf("3. Print the used hash function\n");
		printf("4. Insert a new record into the hash table\n");
		printf(
				"5. Search for a specific medicine and print the number of collisions\n");
		printf("6. Delete a specific record\n");
		printf("7. Save the data back to the file Pharmacy.txt\n");
		printf("8. Exit\n");
		printf(
				"================================================================================================================\n");
		printf("Enter a number: ");

		scanf("%d", &menu);

		switch (menu) {
		case 1: //Print table with empty slots.
			printTableWithEmpty(linearTable);
			break;
		case 2: {

			printf("The size of the table: %d\n", linearTable->size);
			printf("Number of Used Cells: %d\n", linearTable->noOfMedicine);
			break;
		}
		case 3: {

			printf(
					"I used Hashing String First Type (ASCII) By Linear Hashing\n");
		}
			break;
		case 4: //Insert a new medicine to the table.
			readFromUser(linearTable);
			break;

		case 5: { //Search for medicine.
			char temp[300];
			int index;
			printf("Enter the name of the medicine:");
			scanf("%c");
			fgets(temp, sizeof temp, stdin);
			temp[strlen(temp) - 1] = '\0';

			index = searchTable(temp, linearTable); //search in table

			if (index == -1)
				printf("Not Found\n");
			else {
				printf("Index = %d\n", index);
				printf("Number Of Collisions: %d\n", collisions);
			}

		}
			break;

		case 6: { //Delete a specific record.
			char temp[300];
			printf("Enter the name of the medicine:");
			scanf("%c");
			fgets(temp, sizeof temp, stdin);
			temp[strlen(temp) - 1] = '\0';
			deleteMedicineFromTable(temp, linearTable);
		}
			break;

		case 7: { //Save the table to file.
			saveToFile2(out, linearTable);
			printf("Saved To File!!!\n");
		}
			break;

		case 8: //exit the program
			return;
			break;

		default:
			printf("Enter a number from 1-8\n");

		}
	}
	printf("Hello world!\n");
}
