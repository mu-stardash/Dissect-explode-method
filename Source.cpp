#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <clocale>
#include <Windows.h>

using namespace std;

string userText;                                // Строка с текстом
int columns = 2, rows = 4, blocks = 8, len = 0; // Количество столбцов, строк, блоков, длина текста
int x = 0, y = 0;                               // Количество строк и столбцов в полученной таблице
int ostatok = 0;                                // Переменная для оставшихся неполных строк (столбцов)
char A[1000][1000];                             // Двумерный массив для заполнения таблицы
int current = 0;                                // Текущий элемент
// Массив ключей столбцов
int ckey[2] = { 1, 2 };                         // задан один из вариантов ключей в начале программы
// Массив ключей строк
int rkey[4] = { 1, 4, 3, 2 };
int final_key[8];                               // Массив ключей блоков, рассчитанных по формуле K = n(ri-1)+sj (по условию задачи)
char block[8][1000];                            // Двумерный массив зашифрованных блоков
int cur_key = 0, cur_col = 0;                   // Значение текущего ключа и столбца
int numberOfCharacters = 0;                     // Количество символов в тексте

/*
 * Получить информацию о тексте
 * len длина текста
 * userText строка с текстом
 */

void GetInformationText()
{
    len = userText.size(); 
    cout << "Текст:\n" << userText << endl; // выводим текст
    cout << "Длина текста:\n" << len << endl; // его длину
   /* cout << "Таблица с текстом:\n";
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            cout << A[i][j];
        }
        cout << endl;
    }*/ 
    cout << endl;
    cout << "Текущая нумерация блоков по формуле:" << endl; // номера блоков по формуле
    for (int i = 0; i < 8; i++)
        cout << final_key[i] + 1 << " ";
    cout << endl; cout << endl;
}

/*
 * Получить финальную строку блоков
 * current текущий элемент
 * rows кол-во строк
 * columns кол-во столбцов
 * rkey массив ключей строк
 * ckey массив ключей столбцов
 * final_key массив финального ключа
 * ri ключ строки
 * sj ключ столбца
 */

void GetFinalText()
{
    current = 0;
    for (int i = 0; i < rows; i++)  // по всем строкам
    {
        int ri = rkey[i];           // присваиваем значение итого ключа строки
        for (int j = 0; j < columns; j++) // по всем столбцам
        {
            int sj = ckey[j];       // присваиваем значение житого ключа столбца
            final_key[current] = (((columns * ri) - columns) + sj); // узнаем номер блока по формуле для текующего значение по строке-столбцу
            current++;              // переходим к следающему элементу
        }
    }
    for (int i = 0; i < current; i++) 
        final_key[i]--; // уменьшаем номера блоков на 1 для дальнейшей работы
}

/*
 * Ввести новые ключи строк и столбцов
 * rkey массив ключей строк
 * ckey массив ключей столбцов
 * final_key массив финального ключа
 * mas текущий массив строки (столбца), введенного с клавиатуры
 */

void EnterNewKeys()
{
    int mas[4] = { 0 };
    cout << "Введите ключ по столбцам (1, 2 без повторений в любом порядке):" << endl;
    cin >> mas[0];  // первый ключ столбца
    if (mas[0] != 1 && mas[0] != 2)
    {
        cout << "Вводите правильные значения!" << endl; 
        return; 
    }
    cin >> mas[1]; // второй
    if (mas[1] != 1 && mas[1] != 2) 
    {
        cout << "Вводите правильные значения!" << endl;
        return;
    }
    if (mas[0] == mas[1])
    { 
        cout << "Значения не могут повторяться!" << endl; 
        return;
    }
    for (int i = 0; i < 2; i++) 
        ckey[i] = mas[i]; // запоминаем ключи столбцов в массив

    cout << "Введите ключ по строкам (1, 2, 3, 4 без повторений в любом порядке):" << endl;
    cin >> mas[0]; 
    if (mas[0] != 1 && mas[0] != 2 && mas[0] != 3 && mas[0] != 4)
    {
        cout << "Вводите правильные значения!" << endl;
        return; 
    }
    cin >> mas[1];
    if (mas[1] != 1 && mas[1] != 2 && mas[1] != 3 && mas[1] != 4)
    {
        cout << "Вводите правильные значения!" << endl;
        return;
    }
    cin >> mas[2]; 
    if (mas[2] != 1 && mas[2] != 2 && mas[2] != 3 && mas[2] != 4) 
    {
        cout << "Вводите правильные значения!" << endl;
        return;
    }
    cin >> mas[3];
    if (mas[3] != 1 && mas[3] != 2 && mas[3] != 3 && mas[3] != 4)
    {
        cout << "Вводите правильные значения!" << endl;
        return;
    }
    if (mas[0] == mas[1] || mas[0] == mas[2] || mas[1] == mas[2] || mas[0] == mas[3] || mas[1] == mas[3] || mas[2] == mas[3])
    { 
        cout << "Значения не могут повторяться!" << endl;
        return; 
    }

    for (int i = 0; i < 4; i++) 
        rkey[i] = mas[i]; // запоминаем ключи строк в массив

    GetFinalText(); // сразу узнаем новые номера блоков
    cout << "Финальная строка:" << endl;
    for (int i = 0; i < 8; i++)
        cout << final_key[i] + 1 << " ";
    cout << endl; cout << endl;
}

/*
 * Зашифровать текст
 * numberOfCharacters кол-во символов в тексте
 * current текущий элемент
 * cur_col значение текущего столбца
 * cur_key значение текущего ключа
 * len длина строки
 * rows кол-во строк
 * columns кол-во столбцов
 * block двумерный массив зашифрованных блоков
 * final_key массив финального ключа
 */

void Encrypt()
{
    numberOfCharacters = 0; // для выхода из цикла
    cur_col = 0; cur_key = 0;

    for (int i = 0; i < x; i++) // по всем строкам
    {
        for (int j = 0; j < y; j++) // по всем стобцам
        {
            if (numberOfCharacters == len) break; //если просмотрели весь текст, то брик
            int k = final_key[cur_key];  // текущий ключ блока
            block[k][cur_col] = A[i][j]; // помещаем туда символ
            cur_key++;
            numberOfCharacters++;
            /* Если прошли все ключи блоков, то проходим их еще раз, пока не добавим все символы текста */
            if (cur_key > 7) 
            { 
                cur_key = 0;
                cur_col++; 
            }
        }
    }
    cout << "Зашифрованный текст:\n";
    for (int i = 0; i < (rows * columns); i++)
    {
        for (int j = 0; j <= cur_col; j++)
        {
            cout << block[i][j];
        }      
    }
    cout << endl;
    cout << "Символов: " << numberOfCharacters << endl; cout << endl;
}

/*
 * Расшифровать текст
 * userText строка с текстом
 * numberOfCharacters кол-во символов в тексте
 * current текущий элемент
 * cur_col значение текущего столбца
 * cur_key значение ткущего ключа
 * len длина строки
 * block двумерный массив зашифрованных блоков
 * final_key массив финального ключа
 * decrypted расшифрованная строка
 */

void Decrypt()
{
    len = userText.length();
    numberOfCharacters = 0;
    current = 0;
    vector <char> decrypted(len);
    for (int i = 0; i <= cur_col; i++) // по всем столбцам
    {
        for (int j = 0; j < 8; j++)    // по всем блокам
        {
            if (numberOfCharacters == len) break;
            decrypted[current] = block[final_key[j]][i]; // извлекаем зашифрованные символы
            current++;
            numberOfCharacters++;
        }
    }
    cout << "Расшифрованный текст:\n";
    for (int i = 0; i < len; i++)
    {
        cout << decrypted[i];
    }
    cout << endl;
    cout << "Символов: " << numberOfCharacters << endl; cout << endl;
}

/* 
* При изменении текста 
* userText строка с текстом
* current текущий элемент
* c символ с консоли
*/
void Text() {
    userText = ""; // обнуляем текст
    current = 0;
    char c;
    cout << "Введите ваш текст (он должен быть длинее числа блоков)\nЧтобы закончить ввод, нажмите Ctrl+Z:" << endl; cout << endl;

    /* Считывание текста с консоли */
    while (true) {
        c = getchar();
        if ((userText.length() == 0) && (c == EOF))
        {
            cout << "Вы ввели пустую строку!" << endl;
            cout << endl;
            continue;
        }
        else if (c == EOF)
        {
            break;
        }
        userText += c; //создаем строку из вводимых символов
    }

    if (userText.length() < 8) 
    {
        cout << "Длина текста должна быть больше количества блоков (восьми)!" << endl;
        cout << endl;
        return;
    }

    /* Создаем таблицу текста по заданному количеству строк и стобцов */
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            A[i][j] = userText[current];
            current++;
        }
    }
    current = 0;
    GetFinalText(); // сразу узнаем новые номера блоков
}

int main()
{
    /* Для корректного отображения русских символов */
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Открытие файла с исходным текстом
    ifstream fin("input.txt");

    if (!fin.is_open()) cout << "Файл не может быть открыт." << endl;
    // Копируем считываемый текст в строку userText с пробелами и переходом на новую строку
    else
        userText.assign((istreambuf_iterator<char>(fin.rdbuf())), istreambuf_iterator<char>());
    fin.close();

    len = userText.length(); // Вычисляем длину строки  
    x = len / columns;       // Определяем кол-во полных строк
    y = columns;             // Кол-во столбцов всегда равно 2

    /* Если остались лишние символы (не заполнен весь столбик), увеличиваем счетчик */
    ostatok = len % 2;
    if (ostatok) 
        x++;

    /* Создаем таблицу текста по заданному количеству строк и стобцов */
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            A[i][j] = userText[current];
            current++;
        }
    }

    current = 0;
    GetFinalText(); // сразу узнаем новые номера блоков

    /* Оформление и работа меню */
    bool flag = true;
    char choice;
    while (flag)
    {
        cout << "!Меню!\nВыберите, что хотитет сделать: " << endl;
        cout << "1) Узнать информацию о тексте" << endl;
        cout << "2) Ввести новые ключи шифровки" << endl;
        cout << "3) Зашифровать текст" << endl;
        cout << "4) Восстановить текст" << endl;
        cout << "5) Ввести новый текст" << endl;
        cout << "6) Выйти" << endl;

        cin >> choice;

        switch (choice)
        {
        case '1':
            GetInformationText();
            break;
        case '2':
            EnterNewKeys();
            break;
        case '3':
            Encrypt();
            break;
        case '4':
            Decrypt();
            break;
        case '5':           
            Text();
            break;
        case '6':
            exit(1);
            break;
        default:
            cout << "Введите корректный номер пункта меню!" << endl;
            break;
        }
    }
    return 0;
}