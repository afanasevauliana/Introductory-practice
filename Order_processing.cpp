#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

struct Order {
    int order_id;
    wstring customer_name;
    wstring customer_address;
    wstring product_name;
    double order_weight;
    double order_cost;
    double discount;
    bool delivery;
    wstring container_type;
};

vector<Order> orders;

void printOrders();
void editOrder();
void addOrder();
void deleteOrder();
void sortOrders(int sortByField, bool ascending);
void countOrdersByWeight(double weight);
void discountOrders();
void deliveryOrders();

int main() {
    // Установка локали для корректного вывода Unicode
    try {
        locale::global(locale("ru_RU.UTF-8"));
    } catch (const exception& e) {
        wcerr << L"Не удалось установить локаль: " << e.what() << endl;
    }

    wcout.imbue(locale());

    // Добавим тестовые заказы
    orders.push_back({1, L"Иван Иванов", L"ул. Ленина, 12", L"Телевизор", 15.5, 35000, 5, true, L"Коробка"});
    orders.push_back({2, L"Петр Петров", L"ул. Гагарина, 25", L"Холодильник", 50.0, 78000, 10, false, L"Паллет"});
    orders.push_back({3, L"Анна Смирнова", L"пр. Мира, 5", L"Ноутбук", 2.5, 90000, 15, true, L"Контейнер"});
    orders.push_back({4, L"Мария Кузнецова", L"ул. Победы, 35", L"Микроволновая печь", 10.0, 15000, 7, true, L"Ящик"});
    orders.push_back({5, L"Сергей Иванов", L"ул. Советская, 8", L"Смартфон", 0.5, 20000, 10, false, L"Коробка"});
    orders.push_back({6, L"Ольга Орлова", L"пр. Революции, 14", L"Планшет", 0.8, 25000, 12, true, L"Паллет"});
    orders.push_back({7, L"Дмитрий Павлов", L"ул. Кирова, 56", L"Кофеварка", 2.0, 5000, 8, false, L"Контейнер"});
    orders.push_back({8, L"Елена Сидорова", L"ул. Строителей, 40", L"Тостер", 1.5, 3500, 5, true, L"Ящик"});
    orders.push_back({9, L"Николай Ковалев", L"пр. Ленина, 10", L"Стиральная машина", 60.0, 22000, 15, false, L"Коробка"});
    orders.push_back({10, L"Юлия Шевченко", L"ул. Фрунзе, 30", L"Вентилятор", 3.0, 4000, 7, true, L"Паллет"});
    orders.push_back({11, L"Алексей Воронов", L"ул. Мира, 45", L"Пылесос", 7.5, 12000, 5, false, L"Ящик"});
    orders.push_back({12, L"Виктория Боброва", L"пр. Гагарина, 27", L"Плита электрическая", 30.0, 15000, 10, true, L"Коробка"});
    orders.push_back({13, L"Константин Гончаров", L"ул. Октябрьская, 18", L"Кофемашина", 4.0, 22000, 12, true, L"Контейнер"});
    orders.push_back({14, L"Людмила Морозова", L"ул. Молодежная, 60", L"Посудомоечная машина", 45.0, 40000, 8, false, L"Ящик"});
    orders.push_back({15, L"Роман Рожков", L"ул. Чкалова, 23", L"Чайник электрический", 1.2, 3000, 6, true, L"Паллет"});
    orders.push_back({16, L"Татьяна Белова", L"пр. Победы, 13", L"Электрогриль", 4.5, 8000, 9, false, L"Контейнер"});
    orders.push_back({17, L"Георгий Соколов", L"ул. Тимирязева, 72", L"Швейная машинка", 6.0, 11000, 10, true, L"Ящик"});
    orders.push_back({18, L"Владимир Костин", L"ул. Суворова, 15", L"Радио", 1.8, 2500, 5, false, L"Паллет"});
    orders.push_back({19, L"Ирина Куликова", L"ул. Набережная, 22", L"Газовая плита", 35.0, 25000, 12, true, L"Коробка"});
    orders.push_back({20, L"Михаил Чернов", L"пр. Ленина, 5", L"Очиститель воздуха", 4.0, 7000, 8, false, L"Контейнер"});

    int choice;

    while (true) {
        // Вывод меню
        wcout << L"Меню:\n";
        wcout << L"1. Получить список заказов\n";
        wcout << L"2. Редактировать заказ\n";
        wcout << L"3. Добавить новый заказ\n";
        wcout << L"4. Удалить заказ\n";
        wcout << L"5. Сортировка по полям\n";
        wcout << L"6. Определить количество заказов по весу\n";
        wcout << L"7. Заказы с предоставленной скидкой\n";
        wcout << L"8. Заказы для доставки\n";
        wcout << L"9. Выход\n";
        wcout << L"Введите номер действия: ";
        wcin >> choice;
        wcin.ignore(); // Чтобы избежать захвата символа новой строки

        switch (choice) {
            case 1:
                printOrders();
                break;
            case 2:
                editOrder();
                break;
            case 3:
                addOrder();
                break;
            case 4:
                deleteOrder();
                break;
            case 5:
                int field, order;
                wcout << L"Выберите поле для сортировки:\n";
                wcout << L"1. ID\n2. Имя покупателя\n3. Адрес\n4. Товар\n5. Вес\n6. Цена\n7. Скидка\n8. Доставка\n9. Тара\n";
                wcin >> field;
                wcout << L"Выберите порядок сортировки: 1 - по возрастанию, 2 - по убыванию: ";
                wcin >> order;
                sortOrders(field, order == 1);
                break;
            case 6:
                double weight;
                wcout << L"Введите значение веса: ";
                wcin >> weight;
                countOrdersByWeight(weight);
                break;
            case 7:
                discountOrders();
                break;
            case 8:
                deliveryOrders();
                break;
            case 9:
                return 0;
            default:
                wcout << L"Некорректный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}

// Функция для нахождения максимальной ширины столбцов (по количеству символов, а не байтов)
int getMaxWidth(int minWidth, const vector<Order>& orders, wstring Order::*field) {
    int maxLength = minWidth;
    for (const auto& order : orders) {
        maxLength = max(maxLength, (int)(order.*field).size());
    }
    return maxLength;
}

// Функция вывода списка заказов в таблице
void printOrders() {
    if (orders.empty()) {
        wcout << L"Список заказов пуст.\n";
        return;
    }

    // Определяем динамическую ширину столбцов
    const int idWidth = 5;
    const int weightWidth = 8;
    const int costWidth = 10;
    const int discountWidth = 8;
    const int deliveryWidth = 10;

    int nameWidth = getMaxWidth(15, orders, &Order::customer_name);
    int addressWidth = getMaxWidth(20, orders, &Order::customer_address);
    int productWidth = getMaxWidth(12, orders, &Order::product_name);
    int containerWidth = getMaxWidth(10, orders, &Order::container_type);

    // Функция для рисования разделителей
    auto printSeparator = [&]() {
        wcout << L"+" << wstring(idWidth + 2, L'-') << L"+"
              << wstring(nameWidth + 2, L'-') << L"+"
              << wstring(addressWidth + 2, L'-') << L"+"
              << wstring(productWidth + 2, L'-') << L"+"
              << wstring(weightWidth + 2, L'-') << L"+"
              << wstring(costWidth + 2, L'-') << L"+"
              << wstring(discountWidth + 2, L'-') << L"+"
              << wstring(deliveryWidth + 2, L'-') << L"+"
              << wstring(containerWidth + 2, L'-') << L"+\n";
    };

    // Вывод заголовков
    printSeparator();
    wcout << L"| " << setw(idWidth) << left << L"ID" 
          << L" | " << setw(nameWidth) << left << L"Покупатель" 
          << L" | " << setw(addressWidth) << left << L"Адрес" 
          << L" | " << setw(productWidth) << left << L"Товар" 
          << L" | " << setw(weightWidth) << right << L"Вес" 
          << L" | " << setw(costWidth) << right << L"Цена" 
          << L" | " << setw(discountWidth) << right << L"Скидка" 
          << L" | " << setw(deliveryWidth) << left << L"Доставка" 
          << L" | " << setw(containerWidth) << left << L"Тара" 
          << L" |\n";
    printSeparator();

    // Вывод данных
    for (const auto &order : orders) {
        wcout << L"| " << setw(idWidth) << left << order.order_id 
              << L" | " << setw(nameWidth) << left << order.customer_name 
              << L" | " << setw(addressWidth) << left << order.customer_address 
              << L" | " << setw(productWidth) << left << order.product_name 
              << L" | " << setw(weightWidth) << right << fixed << setprecision(1) << order.order_weight 
              << L" | " << setw(costWidth) << right << fixed << setprecision(2) << order.order_cost 
              << L" | " << setw(discountWidth) << right << fixed << setprecision(1) << order.discount 
              << L" | " << setw(deliveryWidth) << left << (order.delivery ? L"Да" : L"Нет") 
              << L" | " << setw(containerWidth) << left << order.container_type 
              << L" |\n";
    }

    printSeparator();
}

// Функция для редактирования заказа
void editOrder() {
    int orderId;
    wcout << L"Введите ID заказа для редактирования: ";
    wcin >> orderId;

    auto it = find_if(orders.begin(), orders.end(), [orderId](const Order& o) { return o.order_id == orderId; });

    if (it != orders.end()) {
        wcout << L"Редактирование заказа ID " << orderId << L"\n";
        wcout << L"Введите новое имя покупателя: ";
        wcin.ignore();  // Чтобы игнорировать остаточный символ новой строки
        getline(wcin, it->customer_name);
        wcout << L"Введите новый адрес покупателя: ";
        getline(wcin, it->customer_address);
        wcout << L"Введите новое наименование товара: ";
        getline(wcin, it->product_name);
        wcout << L"Введите новый вес товара: ";
        wcin >> it->order_weight;
        wcout << L"Введите новую цену товара: ";
        wcin >> it->order_cost;
        wcout << L"Введите новый размер скидки: ";
        wcin >> it->discount;
        wcout << L"Нужна ли доставка? (1 - Да, 0 - Нет): ";
        wcin >> it->delivery;
        wcout << L"Введите новый тип упаковки: ";
        wcin.ignore();  // Чтобы игнорировать остаточный символ новой строки
        getline(wcin, it->container_type);
    } else {
        wcout << L"Заказ с таким ID не найден.\n";
    }
}

// Функция для добавления нового заказа
void addOrder() {
    Order newOrder;
    wcout << L"Введите ID нового заказа: ";
    wcin >> newOrder.order_id;
    wcout << L"Введите имя покупателя: ";
    wcin.ignore();  // Чтобы игнорировать остаточный символ новой строки
    getline(wcin, newOrder.customer_name);
    wcout << L"Введите адрес покупателя: ";
    getline(wcin, newOrder.customer_address);
    wcout << L"Введите наименование товара: ";
    getline(wcin, newOrder.product_name);
    wcout << L"Введите вес товара: ";
    wcin >> newOrder.order_weight;
    wcout << L"Введите цену товара: ";
    wcin >> newOrder.order_cost;
    wcout << L"Введите размер скидки: ";
    wcin >> newOrder.discount;
    wcout << L"Нужна ли доставка? (1 - Да, 0 - Нет): ";
    wcin >> newOrder.delivery;
    wcout << L"Введите тип упаковки: ";
    wcin.ignore();  // Чтобы игнорировать остаточный символ новой строки
    getline(wcin, newOrder.container_type);

    orders.push_back(newOrder);
}

// Функция для удаления заказа
void deleteOrder() {
    int orderId;
    wcout << L"Введите ID заказа для удаления: ";
    wcin >> orderId;

    auto it = remove_if(orders.begin(), orders.end(), [orderId](const Order& o) { return o.order_id == orderId; });

    if (it != orders.end()) {
        orders.erase(it, orders.end());
        wcout << L"Заказ с ID " << orderId << L" был удален.\n";
    } else {
        wcout << L"Заказ с таким ID не найден.\n";
    }
}

// Функция для сортировки заказов
void sortOrders(int sortByField, bool ascending) {
    switch (sortByField) {
        case 1:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.order_id < b.order_id : a.order_id > b.order_id;
            });
            break;
        case 2:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.customer_name < b.customer_name : a.customer_name > b.customer_name;
            });
            break;
        case 3:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.customer_address < b.customer_address : a.customer_address > b.customer_address;
            });
            break;
        case 4:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.product_name < b.product_name : a.product_name > b.product_name;
            });
            break;
        case 5:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.order_weight < b.order_weight : a.order_weight > b.order_weight;
            });
            break;
        case 6:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.order_cost < b.order_cost : a.order_cost > b.order_cost;
            });
            break;
        case 7:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.discount < b.discount : a.discount > b.discount;
            });
            break;
        case 8:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.delivery < b.delivery : a.delivery > b.delivery;
            });
            break;
        case 9:
            sort(orders.begin(), orders.end(), [ascending](const Order& a, const Order& b) {
                return ascending ? a.container_type < b.container_type : a.container_type > b.container_type;
            });
            break;
        default:
            wcout << L"Некорректное поле для сортировки.\n";
            return;
    }

    wcout << L"Заказы отсортированы.\n";
}

// Функция для подсчета количества заказов по весу
void countOrdersByWeight(double weight) {
    int count = 0;
    for (const auto& order : orders) {
        if (order.order_weight > weight) count++;
    }
    wcout << L"Количество заказов с весом больше " << weight << L" кг: " << count << endl;
}

// Функция для получения заказов с предоставленной скидкой
void discountOrders() {
    wcout << L"Заказы с предоставленной скидкой:\n";
    for (const auto& order : orders) {
        if (order.discount > 0) {
            wcout << L"ID: " << order.order_id << L", Покупатель: " << order.customer_name 
                  << L", Товар: " << order.product_name << L", Вес: " << order.order_weight << endl;
        }
    }
}

// Функция для получения заказов для доставки
void deliveryOrders() {
    wcout << L"Заказы для доставки:\n";
    for (const auto& order : orders) {
        if (order.delivery) {
            wcout << L"ID: " << order.order_id << L", Товар: " << order.product_name 
                  << L", Вес: " << order.order_weight << endl;
        }
    }
}