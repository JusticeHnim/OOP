public class Module1
{
    // interface
    interface AbstractCar
    {
        void refuel();
        void startEngine();
    }

    static abstract class Car implements AbstractCar
    {
        private String sManufacturer;
        private String sColor;
        private double dPrice;


        public Car(String manufacturer, String color, double price)
        {
            this.sManufacturer = manufacturer;
            this.sColor = color;
            setPrice(price);
        }
        
        // Setter and Getter for Manufacturer
        public void setManufacturer(String manufacturer) { this.sManufacturer = manufacturer; }
        public String getManufacturer() { return sManufacturer; }

        // Setter and Getter for Color
        public void setColor(String color) { this.sColor = color; }
        public String getColor() { return sColor; }

        // Setter and Getter for Price
        public void setPrice(double price)
        {
            if(price < 0)
            {
                System.out.println("Price cannot be negative. Setting price to 0.");
                this.dPrice = 0;
            }
            else
                this.dPrice = price;
        }
        public double getPrice() { return dPrice; }

        //Behavior methods
        public void drive()
        {
            System.out.println("The " + sColor + " car manufactured by " + sManufacturer + " is driving. Price: " + dPrice + " USD.");
        }
    }

    static class GasolineCar extends Car
    {
        public GasolineCar(String manufacturer, String color, double price) { super(manufacturer, color, price); }

        @Override 
        public void refuel() { System.out.println( "Refueling the gasoline car manufactured by " + getManufacturer() + "."); }

        @Override
        public void startEngine() { System.out.println("Starting the gasoline engine of the car manufactured by " + getManufacturer() + "."); }
    }

    static class ElectricCar extends Car
    {
        public ElectricCar(String manufacturer, String color, double price) { super(manufacturer, color, price); }

        @Override 
        public void refuel() { System.out.println( "Charging the electric car manufactured by " + getManufacturer() + "."); }

        @Override 
        public void startEngine() { System.out.println( "Starting the electric engine of the car manufactured by " + getManufacturer() + "."); }
    }
    // main
    public static void main(String[] args)
    {
        /*Car car1 = new Car("Toyota", "Red", 25000.0);
        car1.drive();

        Car car2 = new Car("Honda", "Blue", 30000.0);
        car2.setPrice(20000.0);
        car2.drive();*/

        AbstractCar[] myGarage = new AbstractCar[2];
        myGarage[0] = new GasolineCar("Toyota", "Red", 25000.0);
        myGarage[1] = new ElectricCar("Honda", "Blue", 30000.0);

        for(int i=0; i<2; i++)
        {
            myGarage[i].refuel();
            myGarage[i].startEngine();
        }
    }
}