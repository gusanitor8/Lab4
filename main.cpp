#include <iostream>
using namespace std;


/**
 * Structure which represents the data of a product
 */
struct Data{
    string product;
    double unitPrice;
    double costPerUnit;
    int soldUnits;
    double salesPerProduct;
    double utilityPerProduct;
};

/**
 * Static structure data array is defined
 */
const int SIZE = 16;
static Data dataArray[SIZE];

/**
 * Function which returns data as an structure array pointer
 * @return structure array pointer
 */
Data* dataSource(){
    //Julio
    Data element1 = {"porcion pastel de chocolate",60, 20,300,18000,12000,};
    Data element2 = {"White Mocha", 19.20,400,12800,5120};
    Data element3 = {"Cafe Americano 8oz", 22,13.20,1590,34980,13992};
    Data element4 = {"Latte 8oz",24,17.20,200,4800,1360};
    Data element5 = {"Toffee Coffee",28,20.10,390, 10920,3081};
    Data element6 = {"Capuccino 8oz", 17.20,1455,34920,9894};
    Data element7 = {"Smores Latte", 32,23,800,25600,7200};
    Data element8 = {"Cafe Tostado Molido", 60,20,60,3600,2400};

    //Agosto
    Data element9 = {"Porcion Pastel de Chocolate", 60,20,250,15000,10000};
    Data element10 = {"White Mocha", 32,19.20,380,12160,4864};
    Data element11 = {"Cafe Americano 8oz",  22,13.20,800,17600,7040};
    Data element12 = {"Latte 8oz", 24,17.20,250,6000,1700,};
    Data element13 = {"Toffee Coffee", 20.10,600,16800,4740 };
    Data element14 = {"Capuccino 8oz",24,17.20,1200,28800,8160};
    Data element15 = {"Smores Latte",32,23,1540,49280,13860};
    Data element16 = {"Cafe Tostado Molido",60,20,15,900,600};

    static Data dataArr[16] = {element1,element2, element3, element4, element5, element6, element7, element8,
                        element9, element10, element11, element12, element13, element14, element15, element16};

    return &dataArr[0];
}

/**
 * Main function
 * @return returns 0 if executed correctly
 */
int main() {
    Data *arrPtr = dataSource();

    int i = 0;
    for (Data *arrPtr = dataSource() ; i < 17 ; arrPtr++){
        Data datos = *arrPtr;

        i = i + 1;
    }

    cout << "FINAL" << endl;

    return 0;
}
