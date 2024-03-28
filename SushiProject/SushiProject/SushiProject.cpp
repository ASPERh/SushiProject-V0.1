#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Класс, представляющий суши
class Sushi {
private:
    string name;
    double price;
public:
    Sushi(string n, double p) : name(n), price(p) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

// Класс, представляющий позицию заказа суши
class OrderItem {
private:
    Sushi sushi;
    int quantity;
public:
    OrderItem(const Sushi& s, int q) : sushi(s), quantity(q) {}

    Sushi getSushi() const {
        return sushi;
    }

    int getQuantity() const {
        return quantity;
    }
};

// Класс, представляющий заказ
class Order {
private:
    vector<OrderItem> items;
public:
    // Добавление суши в заказ
    void addItem(const Sushi& sushi, int quantity) {
        if (quantity > 0) { // Проверяем, что выбрано не ноль роллов
            items.push_back(OrderItem(sushi, quantity));
        }
    }

    // Удаление суши из заказа по номеру
    void removeItem(int index) {
        if (index >= 0 && index < static_cast<int>(items.size())) {
            items.erase(items.begin() + index);
        }
    }

    // Получение общей стоимости заказа
    double getTotalPrice() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getSushi().getPrice() * item.getQuantity();
        }
        return total;
    }

    // Вывод информации о заказе
    void displayOrder() const {
        cout << "Заказ: \n";
        if (items.empty()) {
            cout << "Нет выбранных суши\n";
        }
        else {
            for (size_t i = 0; i < items.size(); ++i) {
                cout << i + 1 << ". " << items[i].getSushi().getName() << " x " << items[i].getQuantity()
                    << " - " << items[i].getSushi().getPrice() << " гривен\n";
            }
            cout << "Общая стоимость: " << getTotalPrice() << " гривен\n";
        }
    }
};

// Функция для отображения меню и выбора блюд
void showMenu(const vector<Sushi>& menu, Order& order) {
    cout << "Меню:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].getName() << " - " << menu[i].getPrice() << " гривен\n";
    }

    int choice;
    cout << "Выберите суши для добавления в заказ (введите номер, 0 - завершить выбор): ";
    cin >> choice;
    while (choice != 0) {
        if (choice > 0 && choice <= static_cast<int>(menu.size())) {
            int quantity;
            cout << "Введите количество порций: ";
            cin >> quantity;
            order.addItem(menu[choice - 1], quantity);
        }
        else {
            cout << "Некорректный выбор. Пожалуйста, введите номер из меню.\n";
        }
        cout << "Продолжить выбор (0 - завершить выбор): ";
        cin >> choice;
    }
}

// Функция для удаления позиции из заказа с подтверждением
void removeItemsWithConfirmation(Order& order) {
    char confirm;
    do {
        int index;
        cout << "Введите номер суши для удаления из заказа (или 0 для отмены): ";
        cin >> index;
        if (index != 0) {
            order.removeItem(index - 1);
            cout << "Суши удалены из заказа.\n";
        }
        else {
            break;
        }
        cout << "Хотите удалить еще суши из заказа? (y/n): ";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y');
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");

    // Создание меню суши
    vector<Sushi> menu = {
        Sushi("Ролл с лососем", 250.0),
        Sushi("Унаги ролл", 350.0),
        Sushi("Филадельфия", 300.0)
    };

    // Создание заказа
    Order order;

    // Показать меню и добавить выбранные суши в заказ
    showMenu(menu, order);

    // Вывести информацию о заказе
    order.displayOrder();

    // Удалить суши из заказа с подтверждением
    removeItemsWithConfirmation(order);

    // Вывести информацию о заказе после удаления
    order.displayOrder();

    return 0;
}
