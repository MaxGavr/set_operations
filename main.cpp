#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/**Предельная мощность множеств A и B.*/
const int setCardinality = 100;

/**Прототипы используемых функций.*/
vector<int> setIntersection(vector<int>, vector<int>);
vector<int> setDifference(vector<int>, vector<int>);
vector<int> setSymDiff(vector<int>, vector<int>);
vector<int> setUnion(vector<int>, vector<int>);
vector<int> setComplement(vector<int>);
vector<pair<int, int>> setCartesian(vector<int>, vector<int>);
bool contains(vector<int>, int);
bool contains(vector<pair<int, int>> dset, pair<int, int> sPair);
void fillUniversum();

/**Создание универсума U, мощностью 1000.*/
vector<int> U;
const size_t universumSize = 1000;

/** Функция нахождения пересечения двух множеств.
 *  Аргументы функции - два множества: A и B.
 *  Функция возвращает множество C.
 */
vector<int> setIntersection(vector<int> A, vector<int> B)
{
    vector<int> C; ///выделение памяти под пересечение

    if (A.empty() || B.empty()) ///если одно из множеств пустое
        return C;               ///возвращаем пустое множество

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого множества
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго множества
                {
                    if (A.at(i) == B.at(j)) ///если элементы равны
                        C.push_back(A.at(i)); ///добавляем их значение в пересечение
                }
        }

    sort(C.begin(), C.end()); ///сортировка полученного множества
    return C;
}

/** Функция нахождения разности двух множеств.
 *  Аргументы функции - два множества: A и B.
 *  Функция возвращает множество R.
 */
vector<int> setDifference(vector<int> A, vector<int> B)
{
    vector<int> R; ///выделение памяти под разность

    if (A.empty()) ///если первое множество пустое
        return R;  ///возвращаем пустое множество
    if (B.empty()) ///если второе множество пустое
        return A;  ///возвращаем первое множество

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого множества
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго множества
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(R, A.at(i))) ///проверяем, содержится ли элемент a в разности
                                if (!contains(B, A.at(i))) ///если нет, то проверяем, содержится ли элемент b в разности
                                    R.push_back(A.at(i)); ///если нет, то добавляем его в разность
                        }
                }
        }

    sort(R.begin(), R.end()); ///сортировка полученного множества
    return R;
}

/** Функция нахождения симметрической разности двух множеств.
 *  Аргументы функции - два множества: A и B.
 *  Функция возвращает множество S.
 */
vector<int> setSymDiff(vector<int> A, vector<int> B)
{
    vector<int> S; ///выделение памяти под объединение

    if (A.empty()) ///если первое множество пустое
        return B;  ///возвращаем второе множество
    if (B.empty()) ///если второе множество пустое
        return A;  ///возвращаем первое множество

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого множества
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго множества
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(S, A.at(i)) && !contains(B, A.at(i))) ///то проверяем, содержится ли элемент a в симметрической разности и в множестве B
                                S.push_back(A.at(i)); ///если нет, то добавляем его
                            if (!contains(S, B.at(i)) && !contains(A, B.at(i))) ///проверяем, содержится ли элемент b в симметрической разности и в множестве A
                                S.push_back(B.at(i)); ///если нет, то добавляем его
                        }
                }
        }

    sort(S.begin(), S.end()); ///сортировка полученного множества
    return S;
}

/** Функция нахождения объединения двух множеств.
 *  Аргументы функции - два множества: A и B.
 *  Функция возвращает множество D.
 */
vector<int> setUnion(vector<int> A, vector<int> B)
{
    vector<int> D; ///выделение памяти под объединение

    if (A.empty() && B.empty()) ///если оба множества пустые
        return D; ///возвращаем пустое множество
    if (A.empty()) ///если множество A - пустое
        return B;  ///возвращаем множество B
    if (B.empty()) ///если множество B - пустое
        return A;  ///возвращаем множество A

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого множества
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго множества
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(D, A.at(i))) ///то проверяем, содержится ли элемент a в объединении
                                D.push_back(A.at(i));  ///если нет, то добавляем его в объединение
                            if (!contains(D, B.at(j))) ///проверяем, содержится ли элемент b в объединении
                                D.push_back(B.at(j));  ///если нет, то добавляем его в объединение
                        }
                    else if (!contains(D, A.at(i)))
                        D.push_back(A.at(i));
                }
        }

    sort(D.begin(), D.end()); ///сортировка полученного множества
    return D;
}

/** Функция нахождения дополнения множества.
 *  Аргумент функции - множество M.
 *  Функция возвращает множество E.
 */
vector<int> setComplement(vector<int> M)
{
    vector<int> E; ///выделение памяти под дополнение

    if (M.empty()) ///если множество пустое
        return U;  ///возвращаем универсум

    for (size_t i = 0; i < universumSize; i++) ///обход по всем элементам универсума
        {
            for (size_t j = 0; j < M.size(); j++) ///обход по всем элементам множества M
                {
                    if (U.at(i) != M.at(j)) ///если элементы не равны
                        {
                            if (!contains(M, U.at(i))) ///проверяем, содержится ли элемент u в множестве M
                                if (!contains(E, U.at(i))) ///если нет, то проверяем, содержится ли элемент u в дополнении
                                    E.push_back(U.at(i)); ///если нет, то добавляем его
                        }
                }
        }

    sort(E.begin(), E.end()); ///сортировка полученного множества
    return E;
}

/** Функция нахождения декартова произведения двух множеств.
 *  Аргументы функции - два множества: first и second.
 *  Функция возвращает множество P.
 */
vector<pair<int, int>> setCartesian(vector<int> first, vector<int> second)
{
    vector<pair<int, int>> P; ///выделение памяти под декартово произведение

    if (first.empty() || second.empty()) ///если одно из множеств - пустое
        {
            return P; ///возвращаем пустое множество
        }

    for (size_t i = 0; i < first.size(); i++) ///обход по всем элементам множества first
        for (size_t j = 0; j < second.size(); j++) ///обход по всем элементам множества second
            {
                pair<int, int> newPair(first.at(i), second.at(j)); ///выделение памяти под кортеж, первым элементом которого
                ///является элемент множества first, а вторым - множества second.
                if (!contains(P, newPair)) ///если кортеж не содержится в декартовом произведении
                    P.push_back(newPair);  ///то добавляем его в декартово произведение
            }

    return P;
}

/** Функция, которая определяет, содержится ли элемент в множестве.
 *  Аргументы функции - множество dset и элемент element.
 *  Функция возвращает true, если элемент содержится в множестве,
 *  и false, если не содержится.
 */
bool contains(vector<int> dset, int element)
{
    for (size_t i = 0; i < dset.size(); i++) ///обход по всем элементам множества dset
        if (dset.at(i) == element)
            return true;
    return false;
}

/** Функция, которая определяет, содержится ли кортеж в множестве.
 *  Аргументы функции множество dset и кортеж sPair.
 *  Функция возвращает true, если кортеж содержится в множестве,
 *  и false, если не содержится.
 */
bool contains(vector<pair<int, int>> dset, pair<int, int> sPair)
{
    for (size_t i = 0; i < dset.size(); i++) ///обход по всем элементам множества
        if (dset.at(i) == sPair)
            return true;
    return false;
}

/** Функция, которая заполненяет универсум значениями
 *  от одного до universumSize включительно.
 */
void fillUniversum()
{
    for (size_t i = 1; i <= universumSize; i++) ///каждое натуральное число от 1 до universumSize включительно
        {
            U.push_back(i); ///добавление этого числа в универсум
        }
}

///Функция корректного считывания с клавиатуры числового значения
void readInteger(int& number)
{
    cin >> number;
    while (!cin.good())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Введено некорректное значение. Повторите ввод: ";
            cin >> number;
        }
}

int main()
{
    setlocale(0,"");
    vector<int> A; ///выделение памяти под первое множество
    vector<int> B; ///выделение памяти под второе множество
    int numA; ///мощность первого множества
    int numB; ///мощность второго множества
    int temp; ///вспомогательная переменная

    ///ввод мощности первого множества с проверкой соответствия значения мощности условию
    do
        {
            cout << "Введите мощность первого множества: ";
            readInteger(numA);
            if (numA < 0)
                cout<<"Мощность множества не может быть отрицательной!"<<endl;
            if (numA > setCardinality)
                cout<<"Мощность множества превышает максимально допустимую("<<setCardinality<<")!"<<endl;
        }
    while (numA < 0 || numA > setCardinality);

    ///ввод мощности второго множества с проверкой соответствия значения мощности условию
    do
        {
            cout << "Введите мощность второго множества: ";
            readInteger(numB); ///ввод мощности второго множества
            if (numB < 0)
                cout<<"Мощность множества не может быть отрицательной!"<<endl;
            if (numB > setCardinality)
                cout<<"Мощность множества превышает максимально допустимую("<<setCardinality<<")!"<<endl;
        }
    while (numB < 0 || numB > setCardinality);

    int choice; ///переменная, отвечающая за выбор пользователя

    if(numA != 0) ///если мощность множества A не равна нулю
        {
            cout << "Выберите способ задания множества A:" << endl
                 << "1) Перечисление элементов;"           << endl
                 << "2) Задание множества высказыванием;"  << endl;
            readInteger(choice); ///выбор способов задания множества A


            switch (choice) ///ввод элементов множества в зависимости от выбора пользователя
                {
                case 1: ///если было выбрано перечисление
                    cout << "Введите элементы множества A:" << endl;
                    for (int i = 0; i < numA; i++) ///то для каждого элемента
                        {
                            ///ввод значения с проверкой на повторное вхождение элементов в множество
                            bool exists;
                            do
                                {
                                    cout << "Элемент №" << i+1 << " - ";
                                    readInteger(temp);
                                    if (exists = contains(A, temp))
                                        cout<<"Элемент уже содержится в множестве! Введите другое значение."<<endl;
                                }
                            while (exists);
                            A.push_back(temp); ///добавление значения в множество
                        }
                    break;
                case 2: ///если было выбрано задание множества высказыванием
                    for (int i = 1; i <= numA; i++)
                        {
                            A.push_back(abs(5*(i+1) + 2*(numA-i)));
                        }

                    break;
                }
        }
    else ///иначе, выводим информацию о том, что A - пустое множество
        {
            cout << "A - пустое множество." << endl << endl;
        }

    if(numB != 0) ///если мощность множества B не равна нулю
        {
            cout << "Выберите способ задания множества Б:" << endl
                 << "1) Перечисление элементов;"           << endl
                 << "2) Задание множества высказыванием;"  << endl;
            readInteger(choice); ///выбор способов задания множества B

            switch (choice) ///ввод элементов множества в зависимости от выбора пользователя
                {
                case 1: ///если было выбрано перечисление
                    cout << "Введите элементы множества B:" << endl;
                    for (int i = 0; i < numB; i++) ///то для каждого элемента
                        {
                            ///ввод значения с проверкой на повторное вхождение элементов в множество
                            bool exists;
                            do
                                {
                                    cout << "Элемент №" << i+1 << " - ";
                                    readInteger(temp);
                                    if (exists = contains(B, temp))
                                        cout<<"Элемент уже содержится в множестве! Введите другое значение."<<endl;
                                }
                            while (exists);
                            B.push_back(temp); ///добавление значения в множество
                        }
                    cout << endl;
                    break;
                case 2: ///если было выбрано задание множества высказыванием
                    for (int k = 1; k <= numB; k++)
                        {
                            B.push_back(abs(2*(numB-k) - 4*k));
                        }
                    break;
                }
        }
    else ///иначе, выводим информацию о том, что B - пустое множество
        {
            cout << "B - пустое множество." << endl << endl;
        }


    while(true) ///бесконечный цикл вывода меню
        {
            cout << "Выберите операцию:"                       << endl
                 << "1)Пересечение множеств A и B"             << endl
                 << "2)Объединение множеств A и B"             << endl
                 << "3)Разность множеств A и B"                << endl
                 << "4)Разность множеств B и A"                << endl
                 << "5)Симметрическая разность множеств A и B" << endl
                 << "6)Декартово произведение множеств A и B"  << endl
                 << "7)Декартово произведения множеств B и A"  << endl
                 << "8)Дополнение множества A"                 << endl
                 << "9)Дополнения множества B"                 << endl
                 << "10)Выход из программы"                    << endl
                 << "Ваш выбор: ";
            readInteger(choice); ///ввод номера операции

            switch (choice) ///Выполнение операции в зависимости от выбора пользователя
                {
                case 1: ///если было выбрано пересечение
                {
                    ///вызов функции нахождения пересечения множеств
                    vector<int> intersect = setIntersection(A, B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (intersect.empty()) ///если пересечение пусто
                        cout << "Пересечение пусто!";
                    else ///если не пусто
                        cout << "Пересечение: ";
                    for (size_t k: intersect) ///для каждого элемента из пересечения
                        {
                            cout << k << " "; ///выводим его значение
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
                break;
                case 2: ///если было выбрано объединение
                {
                    ///вызов функции нахождения объединения множеств и вывод его на экран
                    vector<int> un = setUnion(A, B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (un.empty()) ///если объединение пусто
                        cout << "Объединение пусто!";
                    else ///если не пусто
                        cout << "Объединение: ";
                    for (size_t s : un) ///для каждого элемента из объединения
                        {
                            cout << s  << " "; ///выводим его значение
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
                break;
                case 3: ///если была выбрана разность A и B
                {
                    ///вызов функции нахождения разности множеств A и B
                    vector<int> differenceAB = setDifference(A, B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (differenceAB.empty()) ///если разность - пустое множество
                        cout << "Разность A и B - пустое множество!";
                    else ///если не пустое
                        cout << "Разность A и B: ";
                    for (size_t s : differenceAB) ///для каждого элемента из разности
                        {
                            cout << s  << " "; ///выводим его значение
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
                break;
                case 4: ///если была выбрана разность B и A
                {
                    ///вызов функции нахождения разности множеств B и A
                    vector<int> differenceBA = setDifference(B, A);

                    if (system("CLS"))  ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (differenceBA.empty()) ///если разность - пустое множество
                        cout << "Разность B и A - пустое множество!";
                    else ///если не пустое
                        cout << "Разность B и A: ";
                    for (size_t s : differenceBA) ///для каждого элемента из разности
                        {
                            cout << s  << " "; ///выводим его значение
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
                break;
                case 5: ///если была выбрана симметрическая разность A и B
                {
                    ///вызов функции нахождения симметрической разности множеств A и B
                    vector<int> symdiff = setSymDiff(A, B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (symdiff.empty()) ///если симметрическая разность - пустое множество
                        cout << "Симметрическая разность A и B - пустое множество!";
                    else ///если не пустое
                        cout << "Симметрическая разность A и B: ";
                    for (size_t s : symdiff) ///для каждого элемента из симметрической разности
                        {
                            cout << s  << " "; ///выводим его значение
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                }
                break;
                case 6: ///если было выбрано декартово произведение A и B
                {
                    ///вызов функции нахождения декартова произведения множеств A и B
                    vector<pair<int,int>> productAB = setCartesian(A, B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (productAB.empty()) ///если декартово произведение - пустое множество
                        cout << "Декартово произведение множеств A и B - пустое множество!";
                    else ///если не пустое
                        cout << "Декартово произведение множеств A и B: ";
                    for (pair<int, int> p : productAB) ///для каждого кортежа из декартова произведения
                        {
                            cout << "<" << p.first << "," << p.second << ">" << " ";  ///вывод его на экран
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    break;
                }
                case 7: ///если было выбрано декартово произведение B и A
                {
                    ///вызов функции нахождения декартова произведения множеств B и A
                    vector<pair<int,int>> productBA = setCartesian(B, A);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (productBA.empty()) ///если декартово произведение - пустое множество
                        cout << "Декартово произведение множеств B и A - пустое множество!";
                    else ///если не пустое
                        cout << "Декартово произведение множеств B и A: ";
                    for (pair<int, int> p : productBA) ///для каждого кортежа из декартова произведения
                        {
                            cout << "<" << p.first << "," << p.second << ">" << " ";  ///вывод его на экран
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    break;
                }
                case 8: ///если было выбрано нахождение дополнения множества A
                {
                    fillUniversum(); ///заполнение универсума значениями

                    ///вызов функции нахождения дополнения множества A
                    vector<int> complementA = setComplement(A);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (complementA.empty()) ///если дополнение множества - пустое множество
                        cout << "Дополнение множества A - пустое множество!";
                    else ///если нет
                        cout << "Дополнение множества A: ";
                    for (size_t e : complementA) ///для каждого элемента из дополнения
                        {
                            cout << e << " "; ///вывод его значения
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    break;
                }
                case 9: ///если было выбрано нахождение дополнения множества B
                {
                    if(U.empty()) ///если универсум не был заполнен ранее
                        fillUniversum(); ///заполнение универсума значениями

                    ///вызов функции нахождения дополнения множества
                    vector<int> complementB = setComplement(B);

                    if (system("CLS")) ///очистка консоли
                        system("clear");

                    cout << "-----------------------------------------------------------------" << endl;
                    if (complementB.empty()) ///если дополнение множества - пустое множество
                        cout << "Дополнение множества B - пустое множество!";
                    else ///если нет
                        cout << "Дополнение множества B: ";
                    for (size_t e : complementB) ///для каждого элемента из дополнения
                        {
                            cout << e << " "; ///вывод его значения
                        }
                    cout << endl;
                    cout << "-----------------------------------------------------------------" << endl;
                    break;
                }
                case 10: ///если был выбран выход из программы
                    return 0; ///закрываем программу
                }

        }
    return 0;
}
