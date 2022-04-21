#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Product
{

private:
    string name;
    unsigned int quantity;
    double price;

    void check(string name, double price) const //Входните данни на конструктора с параметри трябва да бъдат валидирани
    {
        if (name.empty())
            throw "Name cannot be empty";
        if (price <= 0) //Цената трябва да бъде положителна
            throw "Price must be positive";
    }

public:
    Product() {} //Конструктор по подразбиране

    Product(string name, unsigned int quantity, double price) : name(name), quantity(quantity), price(price) //Конструктор с параметри
    {
        check(name, price);
    }

    Product(const Product &other) : name(other.name), quantity(other.quantity), price(other.price) //Копиращ конструктор
    {
    }

    Product &operator=(const Product &other) //Предефиниран оператор=
    {
        if (this != &other)
        {
            this->name = other.name;
            this->quantity = other.quantity;
            this->price = other.price;
        }

        return *this;
    }

    ~Product() {}

    // Getter-и за всички полета
    string Name() const
    {
        return this->name;
    }
    unsigned int Quantity() const
    {
        return this->quantity;
    }
    double Price() const
    {
        return this->price;
    }

    // Setter-и за цена и количество
    void setQuantity(unsigned int quantity)
    {
        this->quantity = quantity;
    }

    void setPrice(double price)
    {
        this->price = price;
    }
};

class Property
{
private:
    string address;
    double rent;
    string type;

    void check(string address, double rent, string type) const //Входните данни на конструктора с параметри трябва да бъдат валидирани
    {
        if (address.empty())
            throw "Address cannot be empty";
        if (rent <= 0) //Цената трябва да бъде положителна
            throw "Rent must be positive";
        if (type != "supermarket" && type != "pharmacy" && type != "non-stop" && type != "other")
            throw "Type cannot be empty";
    }

public:
    Property() {} //Конструктор по подразбиране // Не пишеше за конструктор по подразбиране но за всеки случай сложих

    Property(string address, double rent, string type) : address(address), rent(rent), type(type) //Конструктор с параметри
    {
        check(address, rent, type);
    }

    Property(const Property &other) : address(other.address), rent(other.rent), type(other.type) //Копиращ конструктор
    {
    }

    Property &operator=(const Property &other) //Предефиниран оператор=
    {
        if (this != &other)
        {
            this->address = other.address;
            this->rent = other.rent;
            this->type = other.type;
        }

        return *this;
    }

    ~Property() {}

    // Getter-и за всички полета, освен за наема

    string Address() const
    {
        return this->address;
    }

    string Type() const
    {
        return this->type;
    }

    // Getter за наема

    double Rent() const
    {
        if (this->type == "supermarket")
            return this->rent + 0.4 * this->rent;
        else if (this->type == "pharmacy")
            return this->rent + 0.3 * this->rent;
        else if (this->type == "non-stop")
            return this->rent + 0.2 * this->rent;
        else
            return this->rent;
    }
};

class Store : public Property
{

private:
    string name;
    Product *products;
    unsigned int size;
    unsigned int capacity;

    void checkName(string name) const //Входните данни на конструктора с параметри трябва да бъдат валидирани
    {
        if (name.empty())
            throw "Name cannot be empty";
    }

public:
    Store() {} //Конструктор по подразбиране // Не пишеше за конструктор по подразбиране но за всеки случай сложих

    Store(string name, string address, double rent, string type) : Property(address, rent, type), name(name), size(0), capacity(5) //Конструктор с параметри
    {
        checkName(name);
        this->products = new Product[capacity];
    }

    Store(const Store &other) : Property(other), name(other.name), size(other.size), capacity(other.capacity) //Копиращ конструктор
    {
        this->products = new Product[capacity];
        for (int i = 0; i < size; i++)
            this->products[i] = other.products[i];
    }

    Store &operator=(const Store &other) //Предефиниран оператор=
    {
        if (this != &other)
        {
            Property::operator=(other);
            this->name = other.name;
            this->size = other.size;
            this->capacity = other.capacity;
            delete[] this->products;
            this->products = new Product[capacity];
            for (int i = 0; i < size; i++)
                this->products[i] = other.products[i];
        }

        return *this;
    }

    ~Store()
    {
        delete[] this->products;
    }

    // Getter за името
    string Name() const
    {
        return this->name;
    }

    //Ревизия - връща списък с имената на продуктите, чието количество е по-малко от 5
    vector<string> revision() const
    {
        vector<string> names;
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Quantity() < 5)
                names.push_back(this->products[i].Name());
        }
        return names;
    }

    //Добавяне на нов продукт в магазина - всеки един продукт е уникален по своето име
    void addProduct(string name, double price, unsigned int quantity)
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
                throw "Product already exists";
        }
        if (this->size == this->capacity)
        {
            Product *temp = new Product[this->capacity * 2];
            for (int i = 0; i < this->size; i++)
                temp[i] = this->products[i];
            delete[] this->products;
            this->products = temp;
            this->capacity *= 2;
        }
        this->products[this->size++] = Product(name, price, quantity);
    }

    //Зареждане на ново количество от даден продукт - Новото количество се добавя към старото

    void restock(string name, unsigned int quantity)
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
            {
                this->products[i].setQuantity(this->products[i].Quantity() + quantity);
                cout << "Successfully restocked" << name << endl;
                return;
            }
        }
        throw "Product does not exist";
    }

    //Купуване от даден продукт - Ако няма достатъчно количество, купувате колкото има

    void buyProduct(string name, unsigned int quantity)
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
            {
                if (this->products[i].Quantity() < quantity)
                {
                    this->products[i].setQuantity(0);
                    cout << "There aren't " << quantity << " " << name << " products in the store" << endl;
                    cout << "Successfully bought " << this->products[i].Quantity() << " " << name << endl;
                }
                else
                {
                    this->products[i].setQuantity(this->products[i].Quantity() - quantity);
                    cout << "Successfully bought " << quantity << " " << name << endl;
                }
                return;
            }
        }
        throw "Product does not exist";
    }

    // Проверка на количеството на даден продукт

    unsigned int quantity(string name) const
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
                return this->products[i].Quantity();
        }
        throw "Product does not exist";
    }

    // Проверка на цената на даден продукт

    double price(string name) const
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
                return this->products[i].Price();
        }
        throw "Product does not exist";
    }

    // Промяна на цената на даден продукт

    void setPrice(string name, double price)
    {
        for (int i = 0; i < size; i++)
        {
            if (this->products[i].Name() == name)
            {
                if (price > 0 && price != this->products[i].Price())
                {
                    this->products[i].setPrice(price);
                    cout << "Successfully changed the price of " << name << endl;
                    return;
                }
                else if (price <= 0)
                    throw "Invalid price";
                else if (price == this->products[i].Price())
                    cout << "Price is already " << price << endl;
            }
        }
        throw "Product does not exist";
    }

    // Отпечатване на информацията за магазина в конзолата
    void StoreInfo()
    {
        cout << "Name: " << this->name << endl;
        cout << "Address: " << this->Address() << endl;
        cout << "Type: " << this->Type() << endl;
        cout << "Rent: " << this->Rent() << endl;
        cout << "Products: " << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Name: " << this->products[i].Name() << endl;
            cout << "Price: " << this->products[i].Price() << endl;
            cout << "Quantity: " << this->products[i].Quantity() << endl;
        }
    }
};

void Options();
void AddProduct(Store *store);
void CheckQuantity(Store *store);
void CheckPrice(Store *store);
void Restock(Store *store);
void ChangePrice(Store *store);
void BuyProduct(Store *store);
void Revision(Store *store);

int main()
{
    string name, address, type;
    double rent;
    int option;
    Store *store = nullptr;

    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter type: ";
    getline(cin, type);
    cout << "Enter rent: ";
    cin >> rent;
    store = new Store(name, address, rent, type);

    while (true)
    {
        Options();
        cin >> option;
        switch (option)
        {
        case 1:
            AddProduct(store);
            break;
        case 2:
            CheckQuantity(store);
            break;
        case 3:
            CheckPrice(store);
            break;
        case 4:
            Restock(store);
            break;
        case 5:
            ChangePrice(store);
            break;
        case 6:
            BuyProduct(store);
            break;
        case 7:
            store->StoreInfo();
            break;
        case 8:
            Revision(store);
            break;
        case 9:
            delete store;
            return 0;
        }
    }
}
void Options()
{
    cout << "1. Add product" << endl;
    cout << "2. Check product quantity" << endl;
    cout << "3. Check product price" << endl;
    cout << "4. Restock product" << endl;
    cout << "5. Change product price" << endl;
    cout << "6. Buy product" << endl;
    cout << "7. Show shop's information" << endl;
    cout << "8. Revision" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose option: ";
}

void AddProduct(Store *store)
{
    string name;
    double price;
    unsigned int quantity;
    cout << "Enter product name: ";
    getline(cin >> ws, name);
    cout << "Enter product price: ";
    cin >> price;
    cout << "Enter product quantity: ";
    cin >> quantity;
    try
    {
        store->addProduct(name, price, quantity);
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void CheckQuantity(Store *store)
{
    string name;
    cout << "Enter product name: ";
    getline(cin, name);
    try
    {
        cout << "Quantity: " << store->quantity(name) << endl;
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void CheckPrice(Store *store)
{
    string name;
    cout << "Enter product name: ";
    getline(cin, name);
    try
    {
        cout << "Price: " << store->price(name) << endl;
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void Restock(Store *store)
{
    string name;
    unsigned int quantity;
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter quantity: ";
    cin >> quantity;
    try
    {
        store->restock(name, quantity);
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void ChangePrice(Store *store)
{
    string name;
    double price;
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter new price: ";
    cin >> price;
    try
    {
        store->setPrice(name, price);
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void BuyProduct(Store *store)
{
    string name;
    unsigned int quantity;
    cout << "Enter product name: ";
    getline(cin, name);
    cout << "Enter quantity: ";
    cin >> quantity;
    try
    {
        store->buyProduct(name, quantity);
    }
    catch (const char *msg)
    {
        cout << msg << endl;
    }
}

void Revision(Store *store)
{
    vector<string> names = store->revision();

    for (int i = 0; i < names.size(); i++)
    {
        cout << names[i] << endl;
    }
}