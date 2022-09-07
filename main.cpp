#include <iostream>
#include <pthread.h>
using namespace std;


/**
 * Structure which represents the data of a product
 */
struct Data{
    string product;
    double unitPrice;
    double costPerUnit;
    int soldUnits;
};

/**
 * Structure to store thread results
 */
struct prodResult{
    double salesPerProd;
    double utility;
};

/**
 * Static structure data array is defined
 */
const int SIZE = 16;
const int PRODUCTS = 8;
//static int resultIndex = 0;
//static prodResult resultArr[SIZE];
//static Data dataArray[SIZE];
prodResult resultArr[SIZE];
int resultIndex;
pthread_mutex_t arrMutex;

/**
 * Function which returns data as an structure array pointer
 * @return structure array pointer
 */
Data* dataSource(){
    //Julio
    Data element1 = {"porcion pastel de chocolate",60, 20,300};
    Data element2 = {"White Mocha", 32,19.20,400};
    Data element3 = {"Cafe Americano 8oz", 22,13.20,1590};
    Data element4 = {"Latte 8oz",24,17.20,200};
    Data element5 = {"Toffee Coffee",28,20.10,390};
    Data element6 = {"Capuccino 8oz", 24,17.20, 1455};
    Data element7 = {"Smores Latte", 32,23,800};
    Data element8 = {"Cafe Tostado Molido", 60,20,60};

    //Agosto
    Data element9 = {"Porcion Pastel de Chocolate", 60,20,250};
    Data element10 = {"White Mocha", 32,19.20,380};
    Data element11 = {"Cafe Americano 8oz",  22,13.20,800};
    Data element12 = {"Latte 8oz", 24,17.20,250};
    Data element13 = {"Toffee Coffee", 28,20.10,600};
    Data element14 = {"Capuccino 8oz",24,17.20,250};
    Data element15 = {"Smores Latte",32,23,1540};
    Data element16 = {"Cafe Tostado Molido",60,20,15};

    static Data dataArr[SIZE] = {element1,element2, element3, element4, element5, element6, element7, element8,
                        element9, element10, element11, element12, element13, element14, element15, element16};

    return &dataArr[0];
}

/***
 * Function which calculates the sales and utility of each product using threads
 * @param argument  void pointer to be casted for a Data pointer
 * @return returns a void pointer to be casted for an array of type prodResult
 */
void* productData(void* argument){
    Data *datosPtr;
    datosPtr = (Data*) argument;

    prodResult resultados;
    resultados.salesPerProd = datosPtr->unitPrice * datosPtr->soldUnits;
    resultados.utility = resultados.salesPerProd - (datosPtr->soldUnits * datosPtr->costPerUnit);

    pthread_mutex_lock(&arrMutex);
    resultArr[resultIndex] = resultados;
    resultIndex += 1;
    pthread_mutex_unlock(&arrMutex);

    return (void*) resultArr;
}

/**
 * Calculates the total sales and prints them on the screen
 * @param results pointer to an array of prodResult type
 * @param arrSize the size of the array
 * @return returns the calculation
 */
int totalSales(prodResult* results, int arrSize){
    double sum = 0;

    for(int i = 0; i < arrSize; i++){
        sum += results->salesPerProd;
    }

    cout << "\nVentas totales: " << sum << endl;

    return sum;
}

/**
 * Calculates the total utility and prints them on the screen
 * @param results pointer to an array of prodResult type
 * @param arrSize the size of the array
 * @return returns the calculation
 */
int totalUtility(prodResult* results, int arrSize){
    double sum = 0;

    for(int i = 0; i < arrSize; i++){
        sum += results->utility;
    }

    cout << "\nUtilidad total: " << sum << endl;

    return sum;
}

/**
 * Function which prints monthly utility and sales per product
 * @param dataPtr pointer to an array of type Data which contains the  product name
 * @param resultPtr  pointer to an array of type prodResult which containts monthly utility and sales information
 * @param step Integer that indicates the number of elements that will be printed
 * @return returns 0 if executed correctly
 */
int printData(Data* dataPtr, prodResult* resultPtr, int step){
    cout << "\nJulio: " << endl;
    for(int i = 0; i < step; i++ ){
        cout << dataPtr->product << ": Q" << resultPtr->salesPerProd << endl;
        dataPtr++;
        resultPtr++;
    }
    totalSales((resultPtr - step), step);
    totalUtility((resultPtr - step), step);


    cout << "\nAgosto: " << endl;
    for(int i = 0; i < step; i++ ){
        cout << dataPtr->product << ": Q" << resultPtr->salesPerProd << endl;
        dataPtr++;
        resultPtr++;
    }
    totalSales((resultPtr - step), step);
    totalUtility((resultPtr - step), step);

    return 0;
}


/**
 * Main function
 * @return returns 0 if executed correctly
 */
int main() {
    Data *arrPtr = dataSource();

    //thread declaration
    pthread_t threadId;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    void* return_value;

    //thread creation
    int i = 0;
    for (Data *arrPtr = dataSource() ; i < SIZE ; arrPtr++){
        Data datos = *arrPtr;

        pthread_create(&threadId, &attr, productData, (void*)arrPtr);
        pthread_join(threadId, &return_value);

        i++;
    }

    printData(dataSource(), (prodResult*) return_value, PRODUCTS);


    return 0;
}
