#include <iostream>

using namespace std;

struct node
{
    int code; //Код работы
    string name; //Наименование работы
    double price; //Расценка
    int object_code; //Код объекта
    int volume; //Физический объем работы
    node *next; //Указатель на следующий
};

class queue
{
private:
    node *head, *tail; //Указатели на первый и последний элементы
    int size; //Для количества элементов структуры
public:
    queue():head(NULL),tail(NULL),size(0){};
    void add(int code, string name, double price, int object_code, int volume); //Функция добавления элемента
    void show(int size); //Функция просмотра элементов
    int count(); //Функция подсчета кол-ва элементов
    void delete_elem(int size, int delete_elem); //Функция удаления элементов
    int search(int size, int element);//Функция поиска элемента
    void summ(int temp, int object_code);//Функция подсчета суммы выполненных работ
    int search_object(int size, int element);//Функция поиска кода объекта
};

void queue::add(int code, string name, double price, int object_code, int volume) //Функция добавления элемента
{
    size++; //Увеличиваем счетчик элементров
    node *temp = new node; //Выделение памяти для нового элемента списка
    temp->next = head; //Замыкание контура, последний элемент - это начало списка
    temp->code = code; //Записываем в выделенную ячейку памяти значение код работы
    temp->name = name; //Записываем в выделенную ячейку памяти значение наименования работы
    temp->price = price; //Записываем в выделенную ячейку памяти значение стоимости
    temp->object_code = object_code; //Записываем в выделенную ячейку памяти значение кода объекта
    temp->volume = volume; //Записываем в выделенную ячейку памяти значение физического объема работы
    
    if (head != NULL) //В том случае если список не пустой
    {
        tail->next = temp; //Запись данных в следующее за последним элементом поле
        tail = temp; //Последний активный элемент=только что созданный
    }
    else
    {
        head = tail = temp;//Если список пуст то создается первый элемент
    }
}

int queue::count()
{
    return size; //Возвращаем число элементов списка
}

void queue::show(int temp) //Функция показа всех элементов списка
{
    node *tempHead = head; //Указываем на голову
    
    temp = size; //Временная переменная равная числу элементов в списке
    if (temp == 0) // Проверка на наличие элементов списка
        cout << "Список работ пуст" << endl;
    else // Если список не пуст, то выполняем следующее
    {
        while (temp != 0) //Пока не выполнен признак прохода по всему списку
        {
            cout << tempHead -> code << endl; //Очередной элемент списка на экран
            cout << tempHead -> name << endl;
            cout << tempHead -> price << endl;
            cout << tempHead -> object_code << endl;
            cout << tempHead -> volume << endl;
            tempHead = tempHead -> next; //Указываем, что нужен следующий элемент
            temp--; //Один элемент считан, значит осталось на один меньше
        }
    }
}

void queue::summ(int temp, int object_code) //Функция подсчета стоимости выполненных работ на заданном объекте
{
    int const N = 1000; //объявляем константу, которая определяем размерность массива
    double mass[N]; //Объявляем массив
    for (int i=0; i<N; i++)//Приравниваем все элементы массива равным нулю
        mass[i] = 0;
    node *tempHead = head; //Указываем на голову
    temp = size;//Временная переменная равная числу элементов в списке
    
    if (search_object(temp, object_code) == 0) // Вызываем функцию поиска наличия кода объекта в нашем списке
        cout << "Такой работы не найдено" << endl;
    else //Если хотя бы одна работа найдена, то выполняем следующее
    {
            temp = size;//Временная переменная равная числу элементов в списке
            while (temp != 0)//Пока не выполнен признак прохода по всему списку
            {
                for(int i=0; i<N; i++)//Перебираем весь массив
                {
                    if((tempHead->object_code == object_code) && (i = object_code))//Будем считать, что код работы = индексу массива. Если искомый код объекта равен коду объекта из списка и индекс массива равен коду объека, то складываем сумму работ для этого кода
                    {
                        mass[i] = mass[i]+tempHead->price;
                        break;
                    }
                }
                tempHead = tempHead->next; //Указываем, что нужен следующий элемент
                temp--; //Один элемент считан, значит осталось на один меньше
            }
    }
    for (int i=0; i<N; i++)//Перебираем весь массив
        if(mass[i] != 0)//Если значение массива не равно нулю
        {
            cout << i << endl; //Выводим код объекта
            cout << mass[i] << endl; //Выводим стоимость работ
        }
}

void queue::delete_elem(int temp, int delete_elem) //Функция удаления элемента
{
    node *tempHead = head;//Указываем на голову
    
    temp = size;//Временная переменная равная числу элементов в списке
    
    if (search(temp, delete_elem) == 0)// Вызываем функцию поиска наличия удаляемого элемента в нашем списке
        cout << "Такой работы не найдено" << endl;
    else //Если удаляемый элемент существует
    {
            if(tempHead->code == delete_elem) //Если удаляемый элемент из структуры первый
            {
                head = head->next; // В голову кладем следующий элемент
                size--; //Уменьшаем количество элементов
                cout << "Работа удалена" << endl;
            }
            else //Если удаляемый элемент не первый
            {
                while (temp != 0) //Пока не выполнен признак прохода по всему списку
                {
                    if(tempHead -> next -> code == delete_elem) //Если следующий элемент после у текущего равен удаляемуму
                    {
                        tempHead -> next = tempHead -> next -> next; //В указатель на следующий указываем элемент через один
                        cout << "Работа удалена" << endl;
                        size--; //Уменьшаем количество элементов
                    }
                    tempHead = tempHead -> next; //Указываем, что нужен следующий элемент
                    temp--; //Один элемент считан, значит осталось на один меньше
                }
            }
    }
}

int queue::search(int temp, int element) // Функция поиска элемента
{
    int count = 0; //Счетчик
    node *tempHead = head; //Указываем на голову
    
    temp = size; //Временная переменная равная числу элементов в списке
    while (temp != 0) //Пока не выполнен признак прохода по всему списку
        {
            if(tempHead -> code == element) //Если код объекта равен искаемуму элементу
                count++; //Прибавляем 1 к счетчику
            tempHead = tempHead->next; //Указываем, что нужен следующий элемент
            temp--; //Один элемент считан, значит осталось на один меньше
        }
    return count; //Возвращаем значение счетчика
}

int queue::search_object(int temp, int element) //Функция поиска кода объекта
{
    int count = 0; //Счетчик
    node *tempHead = head; //Указываем на голову
    
    temp = size; //Временная переменная равная числу элементов в списке
    while (temp != 0) //Пока не выполнен признак прохода по всему списку
    {
        if(tempHead -> object_code == element) //Если код работы равен искаемуму элементу
            count++; //Прибавляем 1 к счетчику
        tempHead = tempHead->next; //Указываем, что нужен следующий элемент
        temp--; //Один элемент считан, значит осталось на один меньше
    }
    return count; //Возвращаем значение счетчика
}

class work
{
private:
    int code1, object_code1, volume1;
    string name1;
    double price1;
public:
    queue obj;
    work (int code, string name, double price, int object_code, int volume) //Конструктор
    {
        code1 = code;
        name1 = name;
        price1 = price;
        object_code1 = object_code;
        volume1 = volume;
        obj.add(code1, name1, price1, object_code1, volume1);
    }
};

int main ()
{
    queue obj;
    int conf, code;
    do
    {
        cout << "1. Добавление работы\n2. Посмотреть все выполненые работы\n3. Удалить работу\n4. Определить суммарную стоимость всех работ на заданном объекте\n5. Выход.\nВыберите действие:" << endl;
        
        cin >> conf;
        
        switch (conf)
        {
            case 1:
                obj.add(2, "Name2", 1000, 9, 300);
                obj.add(3, "Name3", 1000, 9, 300);
                obj.add(4, "Name4", 1000, 10, 300);
                obj.add(5, "Name5", 1000, 9, 300);
                obj.add(6, "Name6", 1000, 10, 300);
                break;
            case 2:
                obj.show(obj.count());
                break;
            case 3:
                cout << "Введите код работы, которую нужно удалить" << endl;
                cin >> code;
                obj.delete_elem(obj.count(), code);
                break;
            case 4:
                cout << "Введите код объекта, сумму работ которого нужно посчитать" << endl;
                cin >> code;
                obj.summ(obj.count(), code);
                break;
            case 5:
                break;
        }
    } while (conf != 5);
    
    return 0;
}
