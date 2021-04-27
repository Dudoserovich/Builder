#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Предметная область - горячие напитки

enum FILLER {
    NONE,
    TEA,
    COFFEE,
    JAVA
};

enum ADDITING {
    A_NONE,
    CINNAMON,
    MILK,
    LOVE
};

enum ADD_SUGAR {
    A_S_NONE,
    BLACK_SUGAR,
    SIMPLE_SUGAR,
    MAJOR_SUGAR
};

class BaseDrink {
    ADDITING additing;
public:
    BaseDrink(ADDITING additing) : additing(additing) {
    }

    string toString()
    {
        switch (additing) {
            case ADDITING::MILK: return "MILK";
            case ADDITING::CINNAMON: return "CINNAMON";
            case ADDITING::LOVE: return "LOVE";
        }

        throw std::logic_error("err");
    }
};

class Drink {
    vector<BaseDrink *> items;
    FILLER filler;
    ADD_SUGAR addSugar;

    friend class MajorDrinkBuilder;
    friend class LowCostBuilder;

public:
    string toString()
    {
        string s = "";

        switch (filler) {
            case FILLER::TEA: s += "TEA"; break;
            case FILLER::COFFEE: s += "COFFEE"; break;
            case FILLER::JAVA: s += "JAVA"; break;
        }

        if (items.empty() == 0)
            s += ", ";

        switch (addSugar) {
            case ADD_SUGAR::BLACK_SUGAR: s += "BLACK_SUGAR"; break;
            case ADD_SUGAR::MAJOR_SUGAR: s += "MAJOR_SUGAR"; break;
            case ADD_SUGAR::SIMPLE_SUGAR: s += "SIMPLE_SUGAR"; break;
        }

        for (auto & item : items) {
            s += ", " + item->toString();
        }

        return s;
    }
};

class DrinkBuilder {
protected:
    vector<ADDITING> additing;
    FILLER filler;

public:
    void addFiller(ADDITING add) {
        additing.push_back(add);
    }

    void setAdditing(FILLER filler) {
        this->filler = filler;
    }

    virtual Drink* build() = 0;
};

class MajorDrinkBuilder: public DrinkBuilder {
public:
    virtual Drink* build() {
        Drink* drink = new Drink();
        for (auto & f : additing) {
            drink->items.push_back(new BaseDrink(f));
        }
        drink->filler = filler;
        drink->addSugar = ADD_SUGAR::MAJOR_SUGAR;
        return drink;
    }
};

class LowCostBuilder: public DrinkBuilder {
public:
    virtual Drink* build() {
        Drink* drink = new Drink();
        drink->filler = FILLER::TEA;
        //drink->addSugar = ADD_SUGAR::SIMPLE_SUGAR;
        return drink;
    }
};

void userGUI(DrinkBuilder &builder) {
    builder.addFiller(ADDITING::CINNAMON);
    builder.addFiller(ADDITING::LOVE);
    builder.addFiller(ADDITING::LOVE);
    builder.setAdditing(FILLER::JAVA);

    Drink *drink = builder.build();

    cout << "It's your's drink: " << drink->toString() << endl;
}

int main() {
    MajorDrinkBuilder builder1;
    LowCostBuilder builder2;

    userGUI(builder1);
    userGUI(builder2);
}