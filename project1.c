#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct Product {
	int productId;
	char productName[50];
	char category[50];
	int price;
	struct Product *next;
	
};
typedef struct Product Product;
typedef Product* ProductPtr;
	
 struct Basket {
	int basketId;
    Product *productPtr;
	int amount;	
	struct Basket *next;
};
typedef struct Basket Basket;
typedef Basket *BasketPtr;

 struct Customer {
	unsigned int customerId;
	char customerName[50];
	char customerSurname[50];
	Basket *basketPtr;
	struct Customer *next;
};
typedef struct Customer Customer;
typedef Customer *CustomerPtr;

// Function prototypes
void readCustomerFile(CustomerPtr customerTopPtr);
void readProductFile(ProductPtr productHeadPtr);
void readBasketFile(CustomerPtr customerTopPtr, ProductPtr productHeadPtr);
void instructions();
void insertProduct(ProductPtr *productHeadPtr, int id, char name[50], char category[50], int price);
void printProductList(ProductPtr productheadPtr);
void printCustomerList(CustomerPtr customerTopPtr);
void pushCustomer(CustomerPtr *customerTopPtr, int id, char name[50], char surname[50]);
void deleteCustomer(CustomerPtr *customerTopPtr, char name[20], char surname[20]);
void printCustomersBuySameProduct(CustomerPtr headPtr, int selectedProductId);
void insertBasketToCustomer(CustomerPtr currentCustomer,  int basketId);
void insertProductToBasket(CustomerPtr currentCustomer, ProductPtr currentProductPtr);
CustomerPtr findCurrentCustomer(CustomerPtr customerTopPtr, int customerId);
ProductPtr findCurrentProduct(ProductPtr productHeadPtr, int productId);
int getNumberOfCustomers(CustomerPtr customerTopPtr);

int main(int argc, char **argv) {
	//1. read customer file and in order to keep list implement a stack data structure
	
	CustomerPtr customerTopPtr;
	readCustomerFile(customerTopPtr);

	 
	//2. read product file
	ProductPtr productHeadPtr;
	readProductFile(productHeadPtr);
	
	//3. read basket file
	readBasketFile(customerTopPtr, productHeadPtr);
	    
	 instructions();
	 
	 
	 
	 int choice; 
	 int isContinue = 1;
	 scanf("%d", &choice);
	 
	 
			  
			  
	     switch(choice){
	     		
	     	case 1:
	     	printf("Please add new Customer, enter information of Customer");
				char newCustomerName[50];
				char newCustomerSurname[50];
				scanf("%s", newCustomerName);
				scanf("%s", newCustomerSurname);
			     int newCustomerId = getNumberOfCustomers(customerTopPtr) + 1;
				
			    pushCustomer(&customerTopPtr,  newCustomerId, newCustomerName, newCustomerSurname);
				printCustomerList(customerTopPtr);	
			 
			 break;
			case 2:
			while (isContinue != -1){
				// 2.a list customers
			printf("Customer List\n");
			printCustomerList(customerTopPtr);
			// 2.b Select one of the customers
			printf("\nEnter id for a specific customer: ");
			int customerId;
			scanf("%d", &customerId); // read customerId 
			// Find choosen customer and add new basket it
			CustomerPtr currentCustomer = findCurrentCustomer(customerTopPtr, customerId);
		     int newBasketId = currentCustomer->basketPtr->basketId + 1;
		     insertBasketToCustomer(currentCustomer, newBasketId);
			
			// 2.c List the Products	
			printf("\nProduct List\n");
			printProductList(productHeadPtr);
			// 2.d Add a Product
			int productId;
			printf("\nProduct id: ");
			scanf("%d", &productId); // read product id
			// Search for the product
			ProductPtr currentProduct = findCurrentProduct(productHeadPtr, productId);
			insertProductToBasket(currentCustomer, currentProduct);
			
			printf("\nPlease enter -1 to exit. In order to continue press any button: ");
			scanf("%d", &isContinue);
			} // end of case 2 while	
		
			break; // end of case 2
			case 3:
				printCustomerList(customerTopPtr); // print all customers
				newCustomerName[50];
				newCustomerSurname[50];
				// Prompt the user to enter a name and surname
				printf("\nCustomer Name: ");
				scanf("%49s", newCustomerName);
				printf("Customer Surname: ");
				scanf("%49s", newCustomerSurname);
				deleteCustomer(&customerTopPtr, newCustomerName, newCustomerSurname); // remove customer
				printf("\n");	
				printCustomerList(customerTopPtr); // print customerList
			break; // end of case 3
			case 4:
			printProductList(productHeadPtr);
				printf("\nSelect a product with id number: ");
				int productId;
				scanf("%d", &productId);
				//printCustomersBuySameProduct(customerToptr, selectedProductId);
				
			break;
			case 5:
				
				
			case 6:
			exit(1); 
			break;
	     	
	} // end of switch

} // end of main

void instructions(){
	printf("\n1: Add a customer\n"
	       "2: Add basket\n"
		   "3: Remove customer\n"
		   "4: List the customers who bought a specific product\n"
		   "5: List the total shopping amounts of each customer\n"
		   "6: Exit\n");
} // end of instructions

// This funtion read customer input file and create a stack data structure in order to implement list
void readCustomerFile(CustomerPtr customerTopPtr){ 
   
	FILE *cfPtr = fopen("customer.txt", "r");
	int customerId;
	char customerName[50];
	char customerSurname[50];
	
	    fscanf(cfPtr, "%d%49s%49s", &customerId, customerName, customerSurname); // read first line
	    pushCustomer(&customerTopPtr, customerId, customerName, customerSurname);
       	printf("%d\t%s %s\n", customerId, customerName, customerSurname); // print to the screen
       		while (!feof(cfPtr)){ // while not end of file
	fscanf(cfPtr, "%d%49s%49s", &customerId, customerName, customerSurname);
	pushCustomer(&customerTopPtr, customerId, customerName, customerSurname);
	printf("%d\t%s %s\n", customerId, customerName, customerSurname);
	}
	} // end of readCustomerFile	
	
	void readProductFile(ProductPtr productHeadPtr){
		FILE *cfPtr = fopen("product.txt", "r");
		int productId;
    	char productName[50];
        char category[50];
	    int price;
	    fscanf(cfPtr, "%d%49s%49s%d", &productId, productName, category, &price); // read first line
	    insertProduct(&productHeadPtr, productId, productName, category, price);
	    printf("%d\t%s\t%s\t%d\n", productId, productName, category, price); // print to the screen
	       while (!feof(cfPtr)){ // while not end of file
	       fscanf(cfPtr, "%d%49s%49s%d", &productId, productName, category, &price);
	       insertProduct(&productHeadPtr, productId, productName, category, price);
	        printf("%d\t%s\t%s\t%d\n", productId, productName, category, price);
	}
} // end of readProductFile
     
     void readBasketFile(CustomerPtr customerTopPtr, ProductPtr productHeadPtr){
     	FILE *cfPtr = fopen("basket.txt", "r");
     	int customerId, previousCustomerId;
     	int basketId, previousBasketId;
     	int productId;
     	
     	CustomerPtr currentCustomerPtr;
     	ProductPtr currentProductPtr;
     	
     	fscanf(cfPtr, "%d%d%d", &customerId, &basketId, &productId); // read first line
     	currentCustomerPtr = findCurrentCustomer(customerTopPtr, customerId);
     	currentProductPtr = findCurrentProduct(productHeadPtr, productId);
     	insertBasketToCustomer(currentCustomerPtr, basketId);// insert basket to specified customer
     	insertProductToBasket(currentCustomerPtr, currentProductPtr);
     	printf("%d\t%d\t%d\n", customerId, basketId, productId); // print to the screen
     	while (!feof(cfPtr)){ //while not end of file
     	previousCustomerId = customerId;
     	previousBasketId = basketId;
      		fscanf(cfPtr, "%d%d%d", &customerId, &basketId, &productId);
      		if (previousCustomerId != customerId){
	 		currentCustomerPtr = findCurrentCustomer(customerTopPtr, customerId);
	 	     insertBasketToCustomer(currentCustomerPtr, basketId);
		       }
		       	if (previousBasketId != basketId && previousCustomerId == customerId){
	 	      insertBasketToCustomer(currentCustomerPtr, basketId);
		 }
		  currentProductPtr = findCurrentProduct(productHeadPtr, productId);
          insertProductToBasket(currentCustomerPtr, currentProductPtr);

      		printf("%d\t%d\t%d\n", customerId, basketId, productId);
		 }
	 } // end of readBasketFile



void insertBasketToCustomer(CustomerPtr currentCustomer, int basketId){ 
	BasketPtr newBasketPtr = (BasketPtr)malloc(sizeof(Basket));
	newBasketPtr->productPtr = NULL;
	newBasketPtr->amount = 0;
	newBasketPtr->basketId = basketId;
	newBasketPtr->next = currentCustomer->basketPtr;
	currentCustomer->basketPtr = newBasketPtr;


} // end of insertBasketToCustomer

void insertProductToBasket(CustomerPtr currentCustomer, ProductPtr currentProduct){
	ProductPtr newProductPtr = (ProductPtr)malloc(sizeof(Product));
	newProductPtr->productId = currentProduct->productId;
	strcpy(newProductPtr->productName, currentProduct->productName);
	strcpy(newProductPtr->category, currentProduct->category);
	newProductPtr->price = currentProduct->price;
	newProductPtr->next = currentCustomer->basketPtr->productPtr;
	currentCustomer->basketPtr->productPtr = newProductPtr;
	
}




void pushCustomer(CustomerPtr *customerTopPtr, int id, char name[20], char surname[20]){
	CustomerPtr newPtr = (CustomerPtr)malloc(sizeof(Customer));
	newPtr->customerId = id;
	strcpy(newPtr->customerName, name);
	strcpy(newPtr->customerSurname, surname); 
	newPtr->basketPtr = NULL;
	newPtr->next = *customerTopPtr;
	*customerTopPtr = newPtr;
	
} // end of pushCustomer

void deleteCustomer(CustomerPtr *customerTopPtr, char name[50], char surname[50]){  
   if (strcmp(name, (*customerTopPtr)->customerName) == 0 && strcmp(surname, (*customerTopPtr)->customerSurname) == 0){
   	CustomerPtr tempPtr = *customerTopPtr; // hold top
   	*customerTopPtr = (*customerTopPtr)->next;
   	free(tempPtr);
   } else{
   	CustomerPtr previousPtr = *customerTopPtr;
    CustomerPtr currentPtr = (*customerTopPtr)->next; 
	while((currentPtr != NULL) && ((strcmp(name, currentPtr->customerName) != 0) || (strcmp(surname, currentPtr->customerSurname) != 0))){
		previousPtr = currentPtr;
		currentPtr = currentPtr->next;
		--currentPtr->customerId;
	}
	if (currentPtr != NULL){ // node found
	CustomerPtr tempPtr = currentPtr;
		previousPtr->next = currentPtr->next;
		free(tempPtr);
	} else{
		printf("Customer could not be found.");
		
	}	
	 
   }
     
}  // end of deleteCustomer

void printCustomerList(CustomerPtr customerTopPtr){
	CustomerPtr currentCustomer = customerTopPtr;
	while (currentCustomer != NULL){
		printf("%d\t%s %s\n", currentCustomer->customerId, currentCustomer->customerName, currentCustomer->customerSurname);
		currentCustomer = currentCustomer->next;
	}
} // end of printCustomerList



void insertProduct(ProductPtr *productHeadPtr, int id, char name[50], char category[50], int price){
	ProductPtr newPtr = (ProductPtr)malloc(sizeof(Product)); // allocate memory for new product
	if (newPtr != NULL){
	newPtr->productId = id;
	strcpy(newPtr->productName, name);
	strcpy(newPtr->category, category);
	newPtr->price = price;
	newPtr->next = NULL;
	ProductPtr previousPtr, currentPtr;
	previousPtr = NULL;
	currentPtr = *productHeadPtr;
	    while((currentPtr != NULL) && (strcmp(currentPtr->productName, newPtr->productName)) < 1){
	    	previousPtr = currentPtr;
	    	currentPtr = currentPtr->next;
		}
		if (previousPtr == NULL){ // ad head position
			newPtr->next = *productHeadPtr;
			*productHeadPtr = newPtr;
		} else{
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
	
	} else{
		printf("\nNo space available.");
	}
	    
} // end of insertProduct


void printProductList(ProductPtr productHeadPtr){
	ProductPtr currentProductPtr = productHeadPtr;
	while(currentProductPtr != NULL){
		printf("%d\t%s %s %d\n", currentProductPtr->productId, currentProductPtr->productName,
		 currentProductPtr->category, currentProductPtr->price);
		currentProductPtr = currentProductPtr->next;
	}
} // end of printProductList

void printCustomersBuySameProduct(CustomerPtr headPtr, int selectedProductId){
	CustomerPtr currentCustomerPtr;
	currentCustomerPtr = headPtr;
	while(currentCustomerPtr != NULL){
		
		while(currentCustomerPtr->basketPtr != NULL){
			BasketPtr  currentBasketPtr;
			currentBasketPtr = currentCustomerPtr->basketPtr;
			while(currentBasketPtr!= NULL){
				ProductPtr  currentProductPtr;
				currentProductPtr = currentBasketPtr->productPtr;
				while(currentProductPtr!= NULL){
					if(currentProductPtr->productId == selectedProductId ){
						printf("%s %s ", currentCustomerPtr->customerName, currentCustomerPtr->customerSurname);
				}
					currentProductPtr = currentProductPtr->next;
				}
				currentBasketPtr = currentBasketPtr->next;
			}
			//current
		}
		currentCustomerPtr = currentCustomerPtr->next;
		
	}
} // end of printCustomersBuySameProduct



int sizeOfCustomers(CustomerPtr headPtr){
	
	int count = 0;  // Initialize count
    CustomerPtr current = headPtr;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
} // end of sizeOfCustomers


CustomerPtr findCurrentCustomer(CustomerPtr customerTopPtr, int customerId){
		CustomerPtr currentCustomerPtr = customerTopPtr; 
			while(currentCustomerPtr != NULL){
				if (customerId == currentCustomerPtr->customerId)
				break;
				currentCustomerPtr = currentCustomerPtr->next;
			}
			return currentCustomerPtr;
} // end of findCurrentCustomer

ProductPtr findCurrentProduct(ProductPtr productHeadPtr, int productId){
	ProductPtr currentProductPtr = productHeadPtr;
	while(currentProductPtr != NULL){
				if (productId == currentProductPtr->productId)
				break;
				currentProductPtr = currentProductPtr->next;
			}
			return currentProductPtr;
} // end of findCurrentProduct

int getNumberOfCustomers(CustomerPtr customerTopPtr){
	 int numberOfCustomers = 0;
	CustomerPtr currentCustomer = customerTopPtr;
	while(currentCustomer != NULL){
		numberOfCustomers++;
		currentCustomer = currentCustomer->next;
	}
	return numberOfCustomers;
} // end of getNumberOfCustomers












