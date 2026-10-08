#include <bits/stdc++.h>

using namespace std;

//Abstract class
class AbstractCar
{
public:
    virtual void refuel() = 0;
    virtual void startEngine() = 0;
    virtual ~AbstractCar() {}
};

class Car : public AbstractCar
{
private:
    string sManufacturer;
    string sColor;
    double dPrice;

public:
    // Setter and Getter for Manufacturer
    void setManufacturer(const string& mfg) { sManufacturer = mfg; }
    string getManufacturer() const { return sManufacturer; }

    // Setter and Getter for Color 
    void setColor(const string& col) { sColor = col; }
    string getColor() const { return sColor; }

    // Setter and Getter for Price
    void setPrice(double pri)
    {
        if(pri < 15000)
            cout << "Gia xe khong hop le!" << endl;
        else
            dPrice = pri;
    }
    double getPrice() const { return dPrice; }

public:
    Car(string mfg, string col, double pri) : sManufacturer(mfg), sColor(col) { setPrice(pri); } // Constructor
    /*
    Car(string mfg, string col, double pri)
    {
        sManufacturer = mfg;
        sColor = col;
        dPrice = pri;
    }
    */

public:
    virtual void drive() {}
    double calculateTripCost(double dDistance) { return dDistance*0.1; }
    double calculateTripCost(double dDistance, double dEnergyPrice) { return dDistance*dEnergyPrice; } 
};

//Derived class
class GasolineCar : public Car
{
public:
    GasolineCar(string mfg, string col, double pri) : Car(mfg, col, pri) {}

    void refuel() override { cout << "Dang bom xang RON 95 cho xe " << getManufacturer() << endl; }
    void startEngine() override { cout << "Xe xang " << getManufacturer() << " no may: Vroom Vroom!" << endl; }
    void drive() override { cout << getManufacturer() << " " << getColor() << " dang luot di bang dong co dot trong manh me!" << endl; }
};

class ElectricCar : public Car
{
public:
    ElectricCar(string mfg, string col, double pri) : Car(mfg, col, pri) {}

    void refuel() override { cout << "Dang cam xac nhanh cho xe dien " << getManufacturer() << endl; }
    void startEngine() override { cout << "Xe dien " << getManufacturer() << " no may: ...!" << endl; }
    void drive() override { cout << getManufacturer() << " " << getColor() << " dang luot di cuc ki em ai bang dong co dien thong minh!" << endl; }
};

int main()
{
    /*Car car1 = Car("Toyota", "Do", 25000);
    car1.drive();

    Car car2("Honda", "Xanh", 30000);
    car2.drive();

    Car car3("Ford", "Trang", 10000);
    car3.setPrice(20000);
    car3.drive();*/

    Car* myGarage[2];
    myGarage[0] = new GasolineCar("Toyota", "Do", 25000);
    myGarage[1] = new ElectricCar("Tesla", "Trang", 50000);

    /*for(int i=0; i<2; i++)
    {
        myGarage[i]->refuel();
        myGarage[i]->startEngine();
    }*/

    for(int i=0; i<2; i++)
    {
        myGarage[i]->drive();
        cout << myGarage[i]->calculateTripCost(150) << endl;
        cout << myGarage[i]->calculateTripCost(150, 0.12) << endl;
    } 

    delete myGarage[0];
    delete myGarage[1];

    return 0;
}