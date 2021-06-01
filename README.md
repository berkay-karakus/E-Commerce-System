# E-Commerce-System
## Simulation for an e-commerce system

   1. Firstly, current customer, product and some prepared baskets of customers are read from seperate files(customers.txt , products.txt, basket.txt)
  
 
     //1. read customer file and in order to keep list implement a stack data structure
	CustomerPtr customerTopPtr;
	readCustomerFile(customerTopPtr);
	//2. read product file
	ProductPtr productHeadPtr;
	readProductFile(productHeadPtr);
	//3. read basket file
	readBasketFile(customerTopPtr, productHeadPtr);
  
     
  2. While doing these readings appropriate data structures are used in order to keep records


  
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
	 
3. Then, user is asked to select an operation according to given instructions and informations are updated via the request.

       void instructions(){
       printf("\n1: Add a customer\n"
        "2: Add basket\n"
        "3: Remove customer\n"
        "4: List the customers who bought a specific product\n"
        "5: List the total shopping amounts of each customer\n"
        "6: Exit\n");
        } // end of instructions


  
  
