
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <sstream>
#include <fcntl.h>
#include <cctype>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <cwctype>
#include <map>
//#define RESUME
//#define PLAY
//#define STRIG_FINDER



#ifdef STRING_FINDER
int main()
{
     std::setlocale(LC_ALL, "");
     std::locale::global(std::locale("")); // Устанавливаем локаль для корректной работы с русскими символами
     _setmode(_fileno(stdout), _O_U16TEXT); // Устанавливаем вывод в формате UTF-16
     _setmode(_fileno(stdin), _O_U16TEXT); // Устанавливаем ввод в формате UTF-16
     std::wstring fileName = L"Text.txt"; // "Text.txt" имя исследуемого текстового файла

     std::wifstream file(fileName);
     if (!file) {
         std::wcout << L"Не удалось открыть файл." << std::endl;
         return 1;
     }

     int longestLength = 0;
     int shortestLength = INT_MAX;
     int totalLength = 0;
     int lineCount = 0;

     std::wstring line;
     while (std::getline(file, line)) {
         int length = line.length();
         if (length > longestLength) {
             longestLength = length;
         }
         if (length < shortestLength) {
             shortestLength = length;
         }
         totalLength += length;
         lineCount++;
     }

     file.close();

     if (lineCount > 0) {
         double averageLength = static_cast<double>(totalLength) / lineCount;

         std::wcout << L"Самая длинная строка: " << longestLength << std::endl;
         std::wcout << L"Самая короткая строка: " << shortestLength << std::endl;
         std::wcout << L"Средняя длина строк: " << averageLength << std::endl;
     }
     else {
         std::wcout << L"Файл пуст." << std::endl;
     }

     ////////////////////////////////////////
     ////////////////////////////////////////
     std::wcout << L"\n\n";
     std::wcout << L"Поиск количества слов, начинающихся с заданных символов в файлах с Unicode-символами" << std::endl;
     std::wcout << L"\n\n";
     // Запрашиваем символы от пользователя
     wchar_t* searchChars = new wchar_t[100]; // выделяем память динамически
     std::wcout << L"Введите символы для поиска: ";
     std::wcin.getline(searchChars, 100);
     file.clear();//сброс состояния файла
     // Открываем файл для чтения
     file.open(fileName, std::ios::binary);
     //std::wifstream file(fileName, std::ios::binary);//открывается в режиме бинарного доступа, т.е. данные читаются без изменений
     file.imbue(std::locale(file.getloc(), new std::codecvt_utf8_utf16<wchar_t>));// Указываем кодировку UTF-8 или UTF-16 (иначе ру-букв не видит)для гарантии правильности интерпретации и обработки символов UTF-8 и UTF-16.
     if (!file)
     {
         std::wcerr << L"Не удалось открыть файл" << std::endl;
         return 1;
     }
     file.seekg(0, std::ios::beg);//перемещение указателя чтения в начало файла перед повтоорным чтением
     // Подсчитываем количество слов, начинающихся с заданных символов
     int wordCount = 0;
     std::wstring word;
     while (file >> word)
     {
         if (wcsncmp(word.c_str(), searchChars, wcslen(searchChars)) == 0)
         {
             wordCount++;
         }
     }

     // Выводим результат
     std::wcout << L"Количество слов, начинающихся с символов " << searchChars << L": " << wordCount << std::endl;

     // Закрываем файл
     file.close();
     delete[] searchChars; // освобождаем память после использования
     //return 0;
     ////////////////////////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////////////////////////

     //file.clear();//сброс состояния файла
     //file.seekg(0, std::ios::beg);
     std::wstring fruitNames; // Строка для хранения названий фруктов
     //std::map<std::wstring, int> fruitCountMap;
     // Ввод названий фруктов
     std::wcout << L"Введите названия фруктов (разделите их запятыми): ";
     std::getline(std::wcin, fruitNames);

     // Ввод пути к файлу
    // std::wcout << L"Введите путь к файлу: ";
     //std::getline(std::wcin, filePath);

     // Открываем файл для чтения
     file.open(fileName, std::ios::binary);
     if (!file)
     {
         std::wcerr << L"Не удалось открыть файл" << std::endl;
         return 1;
     }

     // Устанавливаем локаль для корректной обработки Unicode-символов
    std::locale::global(std::locale(""));

    std::transform(fruitNames.begin(), fruitNames.end(), fruitNames.begin(), [](wchar_t c) { return std::towlower(c); });

    std::map<std::wstring, int> fruitCountMap;

    //std::wstring word;

    std::wstringstream ss(fruitNames);
    while (std::getline(ss, word, L',')) {
        std::transform(word.begin(), word.end(), word.begin(), [](wchar_t c) { return std::towlower(c); });

        fruitCountMap[word] = 0;
    }

    file.clear();
    file.seekg(0, std::ios::beg);

    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), [](wchar_t c) { return std::towlower(c); });

        if (fruitCountMap.find(word) != fruitCountMap.end()) {
            fruitCountMap[word]++;
        }
    }

    std::wcout << L"Результат:" << std::endl;
    for (const auto& pair : fruitCountMap) {
        std::wcout << pair.first << L" - " << pair.second << std::endl;
    }

    file.close();


     return 0;
}
#endif STRING_FINDER
#ifdef RESUME

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // Создание окна
    HWND hwnd;
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"ResumeWindow";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Failed to register window class", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowEx(0, L"ResumeWindow", L"Resume", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Отображение окна
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Запуск цикла обработки сообщений
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static std::wstring resume = L"Это мое краткое резюме. Я имею опыт в программировании на C++ и знаком с Win API.";
    static int numWindows = 3;

    switch (msg)
    {
    case WM_CREATE:
    {
        // Вывод резюме в окна сообщений
        int startPos = 0;
        int chunkSize = resume.length() / numWindows;

        for (int i = 0; i < numWindows-1; i++)
        {
            std::wstring chunk = resume.substr(startPos, chunkSize);
            MessageBox(hwnd, chunk.c_str(), L"Resume", MB_OK);
            startPos += chunkSize;
        }

        // Вывод последнего окна сообщения с средним числом символов на странице в заголовке
        std::wstring lastChunk = resume.substr(startPos);
        std::wstring lastWindowTitle = L"Resume (Average Chars/Page: " + std::to_wstring(resume.length() / numWindows) + L")";
        MessageBox(hwnd, lastChunk.c_str(), lastWindowTitle.c_str(), MB_OK);

        break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}
#endif RESUME


#ifdef PLAY
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
    int secretNumber;
    int guess;
    int attempts = 0;

    do
    {
        // Генерируем случайное число от 1 до 100
        srand(GetTickCount());
        secretNumber = rand() % 100 + 1;

        // Запрашиваем у пользователя число
        TCHAR message[100];
        _stprintf_s(message, _T("Угадайте число от 1 до 100\n\nПопыток: %d"), attempts);
        guess = MessageBox(0, message, _T("Угадай число"), MB_ICONQUESTION | MB_OKCANCEL);

        if (guess != IDCANCEL)
        {
            attempts++;
            if (guess < secretNumber)
            {
                MessageBox(0, _T("Загаданное число больше"), _T("Подсказка"), MB_ICONINFORMATION | MB_OK);
            }
            else if (guess > secretNumber)
            {
                MessageBox(0, _T("Загаданное число меньше"), _T("Подсказка"), MB_ICONINFORMATION | MB_OK);
            }
        }
        else
        {
            break;
        }

    } while (guess != secretNumber);

    if (guess == secretNumber)
    {
        TCHAR resultMessage[100];
        _stprintf_s(resultMessage, _T("Поздравляю! Вы угадали число %d\n\nПопыток: %d"), secretNumber, attempts);
        MessageBox(0, resultMessage, _T("Победа!"), MB_ICONINFORMATION | MB_OK);
    }
    else
    {
        MessageBox(0, _T("Игра завершена"), _T("Поражение"), MB_ICONINFORMATION | MB_OK);
    }

    return 0;
}
#endif PLAY

