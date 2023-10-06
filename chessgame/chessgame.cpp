#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

#pragma region Цветные_прикольчики
const string red = "\033[31m";
const string nul = "\033[0m";
#pragma endregion

#pragma region Классы
class Figure {
public:
    int xcoord, ycoord;
    string color = "none";
    string type = "none";
    bool was_moved = false;

    Figure(string functype, string funccolor, int x, int y)
    {
        this->color = funccolor;
        this->type = functype;
        this->xcoord = x - 1;
        this->ycoord = converter(y);
        cout << "Настройка: " << type << '(' << color << ')' << " создан(а)" << endl;
    }

    ~Figure()
    {
        cout << "Настройка: " << type << '(' << color << ')' << " удален(а)" << endl;
    }
private:
    int converter(int a) {
        return (8 - a);
    }
};

class Gamemod {
#pragma region Публичные_методы
public:
#pragma region Переменные
    //Создаем поле
    char board[8][8];
    //Создаем все фигуры
    Figure figures[32] = {
        Figure("pawn", "white", 1, 2),
        Figure("pawn", "white", 2, 2),
        Figure("pawn", "white", 3, 2),
        Figure("pawn", "white", 4, 2),
        Figure("pawn", "white", 5, 2),
        Figure("pawn", "white", 6, 2),
        Figure("pawn", "white", 7, 2),
        Figure("pawn", "white", 8, 2),
        Figure("rook", "white", 1, 1),
        Figure("horse", "white", 2, 1),
        Figure("bishop", "white", 3, 1),
        Figure("queen", "white", 4, 1),
        Figure("king", "white", 5, 1),
        Figure("bishop", "white", 6, 1),
        Figure("horse", "white", 7, 1),
        Figure("rook", "white", 8, 1),
        Figure("pawn", "black", 1, 7),
        Figure("pawn", "black", 2, 7),
        Figure("pawn", "black", 3, 7),
        Figure("pawn", "black", 4, 7),
        Figure("pawn", "black", 5, 7),
        Figure("pawn", "black", 6, 7),
        Figure("pawn", "black", 7, 7),
        Figure("pawn", "black", 8, 7),
        Figure("rook", "black", 1, 8),
        Figure("horse", "black", 2, 8),
        Figure("bishop", "black", 3, 8),
        Figure("queen", "black", 4, 8),
        Figure("king", "black", 5, 8),
        Figure("bishop", "black", 6, 8),
        Figure("horse", "black", 7, 8),
        Figure("rook", "black", 8, 8)
    };
#pragma endregion


    Gamemod()
    {
        cout << "Игра Шахматы" << endl;
    }

    //Отвечает за ходы
    void turn(string color)
    {
        char argument;
        view_board();
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Сейчас ход команды: " << color << endl;
        move_figures(color);
        //Реализация ракировки
        for (int i = 0; i < 32; i++) {
            if (figures[i].color == color and figures[i].type == "pawn") {
                if (color == "white") {
                    if (figures[i].ycoord == 0) {
                        
                        cout << "Ваша пешка дошла до конца поля!" << endl << "Выдерите кем она станет:" << endl << "q - Королевой" << endl << "h - Конем" << endl << "b - Слоном" << endl << "r - Ладьей" << endl;
                        cin >> argument;
                        switch (argument) {
                        case('q'):
                            figures[i].type = "queen";
                            break;
                        case('h'):
                            figures[i].type = "horse";
                            break;
                        case('b'):
                            figures[i].type = "bishop";
                            break;
                        case('r'):
                            figures[i].type = "rook";
                            break;
                        }
                    }
                }
                else {
                    if (figures[i].ycoord == 7) {
                        cout << "Ваша пешка дошла до конца поля!" << endl << "Выдерите кем она станет:" << endl << "q - Королевой" << endl << "h - Конем" << endl << "b - Слоном" << endl << "r - Ладьей" << endl;
                        cin >> argument;
                        switch (argument) {
                        case('q'):
                            figures[i].type = "queen";
                            break;
                        case('h'):
                            figures[i].type = "horse";
                            break;
                        case('b'):
                            figures[i].type = "bishop";
                            break;
                        case('r'):
                            figures[i].type = "rook";
                            break;
                        }
                    }
                }
            }
        }
        //Конец реализации ракировки
    }



    ~Gamemod() {
        cout << "Спасибо за игру" << endl;
    }

#pragma endregion

#pragma region Приватные_методы
private:

    //Тут происходит основная магия
    void move_figures(string color)
    {
        string collector;
    HERE://Это от goto
        do
        {
            do
            {
                do
                {
                    cout << "Введите клетку с которой хотите сдвинуть фигуру(Например е2):" << endl;
                    cin >> collector;
                } while (!proverka(collector));
            } while (is_not_empty(collector));
        } while (!is_your_figure(collector, color));
        for (int k = 0; k < 32; k++) {
            if (figures[k].color == color) {
                if (figures[k].xcoord == decryption_x(collector) - 1 and figures[k].ycoord == converter(decryption_y(collector))) {
                    //Туточки начинается проверка, какая именно фигура будет ходить
                    if (figures[k].type == "pawn") {
                        if (pawn_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                    if (figures[k].type == "horse") {
                        if (horse_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                    if (figures[k].type == "bishop") {
                        if (bishop_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                    if (figures[k].type == "rook") {
                        if (rook_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                    if (figures[k].type == "king") {
                        if (king_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                    if (figures[k].type == "queen") {
                        if (queen_move(figures[k].xcoord, figures[k].ycoord, color, k) == true)
                        {
                            cout << "Ошибка, эта фигура не может никуда походить. Выберите другую" << endl << endl;
                            goto HERE;
                        }
                    }
                }
            }
        }
    }

#pragma region Логика_ходов_фигур

    //Тут логика хода пешки
    bool pawn_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
#pragma endregion

#pragma region  Вычисление_возможных_ходов
        if (color == "white") {
            if (board[y - 1][x] == 'o') {
                arr[y - 1][x] = 1;
            }
            if (figures[index].was_moved == false) {
                if (board[y - 2][x] == 'o' and board[y - 1][x] == 'o') {
                    arr[y - 2][x] = 3;//Если стоит 3 значит фигура может походить так только 1 раз
                }
            }

            if (figures[index].xcoord < 8 and (board[y - 1][x + 1] == 'p' or board[y - 1][x + 1] == 'r' or board[y - 1][x + 1] == 'h' or board[y - 1][x + 1] == 'k' or board[y - 1][x + 1] == 'q' or board[y - 1][x + 1] == 'b')) {
                arr[y - 1][x + 1] = 2;
            }
            if (figures[index].xcoord > 1 and (board[y - 1][x - 1] == 'p' or board[y - 1][x - 1] == 'r' or board[y - 1][x - 1] == 'h' or board[y - 1][x - 1] == 'k' or board[y - 1][x - 1] == 'q' or board[y - 1][x - 1] == 'b')) {
                arr[y - 1][x - 1] = 2;
            }
        }
        if (color == "black") {
            if (board[y + 1][x] == 'o') {
                arr[y + 1][x] = 1;
            }
            if (figures[index].was_moved == false) {
                if (board[y + 2][x] == 'o' and board[y + 1][x] == 'o') {
                    arr[y + 2][x] = 3;
                }
            }
            if (figures[index].xcoord < 7 and (board[y + 1][x + 1] == 'P' or board[y + 1][x + 1] == 'R' or board[y + 1][x + 1] == 'H' or board[y + 1][x + 1] == 'K' or board[y + 1][x + 1] == 'Q' or board[y + 1][x + 1] == 'B'))
            {
                arr[y + 1][x + 1] = 2;
            }
            if (figures[index].xcoord > 0 and (board[y + 1][x - 1] == 'P' or board[y + 1][x - 1] == 'R' or board[y + 1][x - 1] == 'H' or board[y + 1][x - 1] == 'K' or board[y + 1][x - 1] == 'Q' or board[y + 1][x - 1] == 'B'))
            {
                cout << board[y + 1][x + 1];
                arr[y + 1][x - 1] = 2;
            }
        }
#pragma endregion

        show_moves(arr);

#pragma region  Выполнение_перемешения
        if (is_empty(arr) == true)
        {
            return true;
        }
        string answer;
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }

        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 3)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
#pragma endregion

        return false;
    }

    //Тут логика для короля
    bool king_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        bool leftrak, rightrak;
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
#pragma endregion

#pragma region  Вычисление_возможных_ходов
        //расчет для клетки влево
        if (x > 0)
        {
            if (board[y][x - 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y][x - 1] == 'p' or board[y][x - 1] == 'h' or board[y][x - 1] == 'k' or board[y][x - 1] == 'q' or board[y][x - 1] == 'b' or board[y][x - 1] == 'r')) or (board[y][x] == 'k' and (board[y][x - 1] == 'P' or board[y][x - 1] == 'H' or board[y][x - 1] == 'K' or board[y][x - 1] == 'Q' or board[y][x - 1] == 'B' or board[y][x - 1] == 'R'))) {
                    arr[y][x - 1] = 2;
                }
                else {
                    arr[y][x - 1] = 0;
                }
            }
            else
            {
                arr[y][x - 1] = 1;
            }
        }

        //расчет для клетки вправо
        if (x < 7)
        {
            if (board[y][x + 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y][x + 1] == 'p' or board[y][x + 1] == 'h' or board[y][x + 1] == 'k' or board[y][x + 1] == 'q' or board[y][x + 1] == 'b' or board[y][x + 1] == 'r')) or (board[y][x] == 'k' and (board[y][x + 1] == 'P' or board[y][x + 1] == 'H' or board[y][x + 1] == 'K' or board[y][x + 1] == 'Q' or board[y][x + 1] == 'B' or board[y][x + 1] == 'R'))) {
                    arr[y][x + 1] = 2;
                }
                else {
                    arr[y][x + 1] = 0;
                }
            }
            else
            {
                arr[y][x + 1] = 1;
            }
        }

        //расчет для клетки вверх
        if (y > 0)
        {
            cout << "asd" << endl;
            if (board[y - 1][x] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y - 1][x] == 'p' or board[y - 1][x] == 'h' or board[y - 1][x] == 'k' or board[y - 1][x] == 'q' or board[y - 1][x] == 'b' or board[y - 1][x] == 'r')) or (board[y][x] == 'k' and (board[y - 1][x] == 'P' or board[y - 1][x] == 'H' or board[y - 1][x] == 'K' or board[y - 1][x] == 'Q' or board[y - 1][x] == 'B' or board[y - 1][x] == 'R'))) {

                    arr[y - 1][x] = 2;
                }
                else {
                    cout << "asd" << endl;
                    arr[y - 1][x] = 0;
                }
            }
            else
            {
                arr[y - 1][x] = 1;
            }
        }

        //расчет для клетки вниз
        if (y < 7)
        {
            if (board[y + 1][x] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y + 1][x] == 'p' or board[y + 1][x] == 'h' or board[y + 1][x] == 'k' or board[y + 1][x] == 'q' or board[y + 1][x] == 'b' or board[y + 1][x] == 'r')) or (board[y][x] == 'k' and (board[y + 1][x] == 'P' or board[y + 1][x] == 'H' or board[y + 1][x] == 'K' or board[y + 1][x] == 'Q' or board[y + 1][x] == 'B' or board[y + 1][x] == 'R'))) {
                    arr[y + 1][x] = 2;
                }
                else {
                    arr[y + 1][x] = 0;
                }
            }
            else
            {
                arr[y + 1][x] = 1;
            }
        }

        //расчет для клетки влево вверх
        if (x > 0 and y > 0)
        {
            if (board[y - 1][x - 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y - 1][x - 1] == 'p' or board[y - 1][x - 1] == 'h' or board[y - 1][x - 1] == 'k' or board[y - 1][x - 1] == 'q' or board[y - 1][x - 1] == 'b' or board[y - 1][x - 1] == 'r')) or (board[y][x] == 'k' and (board[y - 1][x - 1] == 'P' or board[y - 1][x - 1] == 'H' or board[y - 1][x - 1] == 'K' or board[y - 1][x - 1] == 'Q' or board[y - 1][x - 1] == 'B' or board[y - 1][x - 1] == 'R'))) {
                    arr[y - 1][x - 1] = 2;
                }
                else {
                    arr[y - 1][x - 1] = 0;
                }
            }
            else
            {
                arr[y - 1][x - 1] = 1;
            }
        }

        //расчет для клетки вправо вверх
        if (x < 7 and y > 0)
        {
            if (board[y - 1][x + 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y - 1][x + 1] == 'p' or board[y - 1][x + 1] == 'h' or board[y - 1][x + 1] == 'k' or board[y - 1][x + 1] == 'q' or board[y - 1][x + 1] == 'b' or board[y - 1][x + 1] == 'r')) or (board[y][x] == 'k' and (board[y - 1][x + 1] == 'P' or board[y - 1][x + 1] == 'H' or board[y - 1][x + 1] == 'K' or board[y - 1][x + 1] == 'Q' or board[y - 1][x + 1] == 'B' or board[y - 1][x + 1] == 'R'))) {
                    arr[y - 1][x + 1] = 2;
                }
                else {
                    arr[y - 1][x + 1] = 0;
                }
            }
            else
            {
                arr[y - 1][x + 1] = 1;
            }
        }

        //расчет для клетки вверх
        if (x > 0 and y < 7)
        {
            cout << "asd" << endl;
            if (board[y + 1][x - 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y + 1][x - 1] == 'p' or board[y + 1][x - 1] == 'h' or board[y + 1][x - 1] == 'k' or board[y + 1][x - 1] == 'q' or board[y + 1][x - 1] == 'b' or board[y + 1][x - 1] == 'r')) or (board[y][x] == 'k' and (board[y + 1][x - 1] == 'P' or board[y + 1][x - 1] == 'H' or board[y + 1][x - 1] == 'K' or board[y + 1][x - 1] == 'Q' or board[y + 1][x - 1] == 'B' or board[y + 1][x - 1] == 'R'))) {

                    arr[y + 1][x - 1] = 2;
                }
                else {
                    cout << "asd" << endl;
                    arr[y + 1][x - 1] = 0;
                }
            }
            else
            {
                arr[y + 1][x - 1] = 1;
            }
        }

        //расчет для клетки вниз
        if (x < 7 and y < 7)
        {
            if (board[y + 1][x + 1] != 'o')
            {
                if ((board[y][x] == 'K' and (board[y + 1][x + 1] == 'p' or board[y + 1][x + 1] == 'h' or board[y + 1][x + 1] == 'k' or board[y + 1][x + 1] == 'q' or board[y + 1][x + 1] == 'b' or board[y + 1][x + 1] == 'r')) or (board[y][x] == 'k' and (board[y + 1][x + 1] == 'P' or board[y + 1][x + 1] == 'H' or board[y + 1][x + 1] == 'K' or board[y + 1][x + 1] == 'Q' or board[y + 1][x + 1] == 'B' or board[y + 1][x + 1] == 'R'))) {
                    arr[y + 1][x + 1] = 2;
                }
                else {
                    arr[y + 1][x + 1] = 0;
                }
            }
            else
            {
                arr[y + 1][x + 1] = 1;
            }
        }

        //Ракировка
        if (color == "white")
        {//Длинная ракировка
            if (figures[index].was_moved == false and board[7][1] == 'o' and board[7][2] == 'o' and board[7][3] == 'o' and figures[8].was_moved == false) {
                arr[7][2] = 3;
            }//Короткая ракировка
            if (figures[index].was_moved == false and board[7][5] == 'o' and board[7][6] == 'o' and figures[15].was_moved == false) {
                arr[7][6] = 3;
            }
        }
        else
        {//Длинная ракировка
            if (figures[index].was_moved == false and board[0][1] == 'o' and board[0][2] == 'o' and board[0][3] == 'o' and figures[24].was_moved == false) {
                arr[0][2] = 3;
            }//Короткая ракировка
            if (figures[index].was_moved == false and board[0][5] == 'o' and board[0][6] == 'o' and figures[31].was_moved == false) {
                arr[0][6] = 3;
            }

        }
#pragma endregion

        show_moves(arr);

#pragma region  Выполнение_перемешения
        string answer;
        if (is_empty(arr) == true)
        {
            return true;
        }
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 3)
        {
            if (2 == decryption_x(answer) - 1 and 1 == decryption_y(answer)) {
                figures[12].xcoord = 2;
                figures[12].ycoord = 7;
                figures[8].xcoord = 3;
                figures[8].ycoord = 7;
            }
            if (6 == decryption_x(answer) - 1 and 1 == decryption_y(answer)) {
                figures[12].xcoord = 6;
                figures[12].ycoord = 7;
                figures[15].xcoord = 5;
                figures[15].ycoord = 7;
            }
            if (2 == decryption_x(answer) - 1 and 8 == decryption_y(answer)) {
                figures[28].xcoord = 2;
                figures[28].ycoord = 0;
                figures[24].xcoord = 3;
                figures[24].ycoord = 0;
            }
            if (6 == decryption_x(answer) - 1 and 8 == decryption_y(answer)) {
                figures[28].xcoord = 6;
                figures[28].ycoord = 0;
                figures[31].xcoord = 5;
                figures[31].ycoord = 0;
            }
        }
#pragma endregion

        return false;
    }

    //Тут логика хода королевы
    bool queen_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
        int minimum, maximum, minn, maxx;
        if (converter(x) > converter(y)) {
            minn = converter(x) - 1;
            maxx = converter(y) - 1;
        }
        else {
            minn = converter(y) - 1;
            maxx = converter(x) - 1;
        }
        if (x > y) {
            minimum = y;
            maximum = 7 - x;

        }
        else {
            minimum = x;
            maximum = 7 - y;
        }
#pragma endregion 

#pragma region Вычисление_возможных_ходов
        bool stopped = false;
        for (int i = 1; i <= y; i++) {
            if (stopped == false) {
                arr[y - i][x] = 1;
                if (board[y - i][x] != 'o') {
                    if ((board[y][x] == 'Q' and (board[y - i][x] == 'p' or board[y - i][x] == 'h' or board[y - i][x] == 'k' or board[y - i][x] == 'q' or board[y - i][x] == 'b' or board[y - i][x] == 'r')) or (board[y][x] == 'q' and (board[y - i][x] == 'P' or board[y - i][x] == 'H' or board[y - i][x] == 'K' or board[y - i][x] == 'Q' or board[y - i][x] == 'B' or board[y - i][x] == 'R'))) {
                        arr[y - i][x] = 2;
                    }
                    else {
                        arr[y - i][x] = 0;
                    }
                    stopped = true;
                }
            }
        }
        stopped = false;
        for (int i = 1; i <= 7 - y; i++) {
            if (stopped == false) {
                arr[y + i][x] = 1;
                if (board[y + i][x] != 'o') {
                    if ((board[y][x] == 'Q' and (board[y + i][x] == 'p' or board[y + i][x] == 'h' or board[y + i][x] == 'k' or board[y + i][x] == 'q' or board[y + i][x] == 'b' or board[y + i][x] == 'r')) or (board[y][x] == 'q' and (board[y + i][x] == 'P' or board[y - i][x] == 'H' or board[y + i][x] == 'K' or board[y + i][x] == 'Q' or board[y + i][x] == 'B' or board[y + i][x] == 'R'))) {
                        arr[y + i][x] = 2;
                    }
                    else {
                        arr[y + i][x] = 0;
                    }
                    stopped = true;
                }
            }
        }
        stopped = false;
        for (int i = 1; i <= x; i++) {
            if (stopped == false) {
                arr[y][x - i] = 1;
                if (board[y][x - i] != 'o') {

                    if ((board[y][x] == 'Q' and (board[y][x - i] == 'p' or board[y][x - i] == 'h' or board[y][x - i] == 'k' or board[y][x - i] == 'q' or board[y][x - i] == 'b' or board[y][x - i] == 'r')) or (board[y][x] == 'q' and (board[y][x - i] == 'P' or board[y][x - i] == 'H' or board[y][x - i] == 'K' or board[y][x - i] == 'Q' or board[y][x - i] == 'B' or board[y][x - i] == 'R'))) {
                        arr[y][x - i] = 2;
                    }
                    else {
                        arr[y][x - i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        stopped = false;
        for (int i = 1; i <= 7 - x; i++) {
            if (stopped == false) {
                arr[y][x + i] = 1;
                if (board[y][x + i] != 'o') {

                    if ((board[y][x] == 'Q' and (board[y][x + i] == 'p' or board[y][x + i] == 'h' or board[y][x + i] == 'k' or board[y][x + i] == 'q' or board[y][x + i] == 'b' or board[y][x + i] == 'r')) or (board[y][x] == 'q' and (board[y][x + i] == 'P' or board[y][x + i] == 'H' or board[y][x + i] == 'K' or board[y][x + i] == 'Q' or board[y][x + i] == 'B' or board[y][x + i] == 'R'))) {
                        arr[y][x + i] = 2;
                    }
                    else {
                        arr[y][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        for (int i = 1; i <= minimum; i++) {
            if (stopped == false) {
                arr[y - i][x - i] = 1;
                if (board[y - i][x - i] != 'o') {
                    if ((board[y][x] == 'Q' and (board[y - i][x - i] == 'p' or board[y - i][x - i] == 'h' or board[y - i][x - i] == 'k' or board[y - i][x - i] == 'q' or board[y - i][x - i] == 'b' or board[y - i][x - i] == 'r')) or (board[y][x] == 'q' and (board[y - i][x - i] == 'P' or board[y - i][x - i] == 'H' or board[y - i][x - i] == 'K' or board[y - i][x - i] == 'Q' or board[y - i][x - i] == 'B' or board[y - i][x - i] == 'R'))) {
                        arr[y - i][x - i] = 2;
                    }
                    else {
                        arr[y - i][x - i] = 0;
                    }
                    stopped = true;
                }
            }
        }
        //Расчет для налево вверх
        stopped = false;
        for (int i = 1; i <= maxx; i++) {
            if (stopped == false) {
                arr[y - i][x + i] = 1;
                if (board[y - i][x + i] != 'o') {

                    if ((board[y][x] == 'Q' and (board[y - i][x + i] == 'p' or board[y - i][x + i] == 'h' or board[y - i][x + i] == 'k' or board[y - i][x + i] == 'q' or board[y - i][x + i] == 'b' or board[y - i][x + i] == 'r')) or (board[y][x] == 'q' and (board[y - i][x + i] == 'P' or board[y - i][x + i] == 'H' or board[y - i][x + i] == 'K' or board[y - i][x + i] == 'Q' or board[y - i][x + i] == 'B' or board[y - i][x + i] == 'R'))) {
                        arr[y - i][x + i] = 2;
                    }
                    else {
                        arr[y - i][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Расчет для направо вверх
        stopped = false;
        for (int i = 1; i <= minn; i++) {
            if (stopped == false) {
                arr[y + i][x - i] = 1;
                if (board[y + i][x - i] != 'o') {

                    if ((board[y][x] == 'Q' and (board[y + i][x - i] == 'p' or board[y + i][x - i] == 'h' or board[y + i][x - i] == 'k' or board[y + i][x - i] == 'q' or board[y + i][x - i] == 'b' or board[y + i][x - i] == 'r')) or (board[y][x] == 'q' and (board[y + i][x - i] == 'P' or board[y + i][x - i] == 'H' or board[y + i][x - i] == 'K' or board[y + i][x - i] == 'Q' or board[y + i][x - i] == 'B' or board[y + i][x - i] == 'R'))) {
                        arr[y + i][x - i] = 2;
                    }
                    else {
                        arr[y + i][x - i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Расчет для налево вниз
        stopped = false;
        for (int i = 1; i <= maximum; i++) {
            if (stopped == false) {
                arr[y + i][x + i] = 1;
                if (board[y + i][x + i] != 'o') {

                    if ((board[y][x] == 'Q' and (board[y + i][x + i] == 'p' or board[y + i][x + i] == 'h' or board[y + i][x + i] == 'k' or board[y + i][x + i] == 'q' or board[y + i][x + i] == 'q' or board[y + i][x + i] == 'r')) or (board[y][x] == 'q' and (board[y + i][x + i] == 'P' or board[y + i][x + i] == 'H' or board[y + i][x + i] == 'K' or board[y + i][x + i] == 'Q' or board[y + i][x + i] == 'B' or board[y + i][x + i] == 'R'))) {
                        arr[y + i][x + i] = 2;
                    }
                    else {
                        arr[y + i][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Расчет для направо вниз
#pragma endregion

        show_moves(arr);

#pragma region Выполнение_перемещения
        string answer;
        if (is_empty(arr) == true)
        {
            return true;
        }
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }
#pragma endregion

        return false;
    }

    //Тут логика хода слона
    bool bishop_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
        int minimum, maximum, minn, maxx;
        if (converter(x) > converter(y)) {
            minn = converter(x) - 1;
            maxx = converter(y) - 1;
        }
        else {
            minn = converter(y) - 1;
            maxx = converter(x) - 1;
        }
        if (x > y) {
            minimum = y;
            maximum = 7 - x;
        }
        else {
            minimum = x;
            maximum = 7 - y;
        }
#pragma endregion
        
#pragma region Вычисление_возможных_ходов
        bool stopped = false;
        //Расчет для налево вверх
        for (int i = 1; i <= minimum; i++) {
            if (stopped == false) {
                arr[y - i][x - i] = 1;
                if (board[y - i][x - i] != 'o') {
                    if ((board[y][x] == 'B' and (board[y - i][x - i] == 'p' or board[y - i][x - i] == 'h' or board[y - i][x - i] == 'k' or board[y - i][x - i] == 'q' or board[y - i][x - i] == 'b' or board[y - i][x - i] == 'r')) or (board[y][x] == 'b' and (board[y - i][x - i] == 'P' or board[y - i][x - i] == 'H' or board[y - i][x - i] == 'K' or board[y - i][x - i] == 'Q' or board[y - i][x - i] == 'B' or board[y - i][x - i] == 'R'))) {
                        arr[y - i][x - i] = 2;
                    }
                    else {
                        arr[y - i][x - i] = 0;
                    }
                    stopped = true;
                }
            }
        }
        //Конец расчета для налево вверх
        //Расчет для направо вверх
        stopped = false;
        for (int i = 1; i <= maxx; i++) {
            if (stopped == false) {
                arr[y - i][x + i] = 1;
                if (board[y - i][x + i] != 'o') {

                    if ((board[y][x] == 'B' and (board[y - i][x + i] == 'p' or board[y - i][x + i] == 'h' or board[y - i][x + i] == 'k' or board[y - i][x + i] == 'q' or board[y - i][x + i] == 'b' or board[y - i][x + i] == 'r')) or (board[y][x] == 'b' and (board[y - i][x + i] == 'P' or board[y - i][x + i] == 'H' or board[y - i][x + i] == 'K' or board[y - i][x + i] == 'Q' or board[y - i][x + i] == 'B' or board[y - i][x + i] == 'R'))) {
                        arr[y - i][x + i] = 2;
                    }
                    else {
                        arr[y - i][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Конец расчета для направо вверх
        //Расчет для налево вниз
        stopped = false;
        for (int i = 1; i <= minn; i++) {
            if (stopped == false) {
                arr[y + i][x - i] = 1;
                if (board[y + i][x - i] != 'o') {

                    if ((board[y][x] == 'B' and (board[y + i][x - i] == 'p' or board[y + i][x - i] == 'h' or board[y + i][x - i] == 'k' or board[y + i][x - i] == 'q' or board[y + i][x - i] == 'b' or board[y + i][x - i] == 'r')) or (board[y][x] == 'b' and (board[y + i][x - i] == 'P' or board[y + i][x - i] == 'H' or board[y + i][x - i] == 'K' or board[y + i][x - i] == 'Q' or board[y + i][x - i] == 'B' or board[y + i][x - i] == 'R'))) {
                        arr[y + i][x - i] = 2;
                    }
                    else {
                        arr[y + i][x - i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Конец расчета для налево вниз
        //Расчет для направо вниз
        stopped = false;
        for (int i = 1; i <= maximum; i++) {
            if (stopped == false) {
                arr[y + i][x + i] = 1;
                if (board[y + i][x + i] != 'o') {

                    if ((board[y][x] == 'B' and (board[y + i][x + i] == 'p' or board[y + i][x + i] == 'h' or board[y + i][x + i] == 'k' or board[y + i][x + i] == 'q' or board[y + i][x + i] == 'b' or board[y + i][x + i] == 'r')) or (board[y][x] == 'b' and (board[y + i][x + i] == 'P' or board[y + i][x + i] == 'H' or board[y + i][x + i] == 'K' or board[y + i][x + i] == 'Q' or board[y + i][x + i] == 'B' or board[y + i][x + i] == 'R'))) {
                        arr[y + i][x + i] = 2;
                    }
                    else {
                        arr[y + i][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        //Конец расчета для направо вниз
#pragma endregion
        
        show_moves(arr);

#pragma region Выполнение_перемещения
        string answer;
        if (is_empty(arr) == true)
        {
            return true;
        }
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }
#pragma endregion
        
        return false;
    }

    //Тут логика хода ладьи
    bool rook_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
#pragma endregion

#pragma region  Вычисление_возможных_ходов

        bool stopped = false;
        for (int i = 1; i <= y; i++) {
            if (stopped == false) {
                arr[y - i][x] = 1;
                if (board[y - i][x] != 'o') {
                    if ((board[y][x] == 'R' and (board[y - i][x] == 'p' or board[y - i][x] == 'h' or board[y - i][x] == 'k' or board[y - i][x] == 'q' or board[y - i][x] == 'b' or board[y - i][x] == 'r')) or (board[y][x] == 'r' and (board[y - i][x] == 'P' or board[y - i][x] == 'H' or board[y - i][x] == 'K' or board[y - i][x] == 'Q' or board[y - i][x] == 'B' or board[y - i][x] == 'R'))) {
                        arr[y - i][x] = 2;
                    }
                    else {
                        arr[y - i][x] = 0;
                    }
                    stopped = true;
                }
            }
        }
        stopped = false;
        for (int i = 1; i <= 7 - y; i++) {
            if (stopped == false) {
                arr[y + i][x] = 1;
                if (board[y + i][x] != 'o') {
                    if ((board[y][x] == 'R' and (board[y + i][x] == 'p' or board[y + i][x] == 'h' or board[y + i][x] == 'k' or board[y + i][x] == 'q' or board[y + i][x] == 'b' or board[y + i][x] == 'r')) or (board[y][x] == 'r' and (board[y + i][x] == 'P' or board[y - i][x] == 'H' or board[y + i][x] == 'K' or board[y + i][x] == 'Q' or board[y + i][x] == 'B' or board[y + i][x] == 'R'))) {
                        arr[y + i][x] = 2;
                    }
                    else {
                        arr[y + i][x] = 0;
                    }
                    stopped = true;
                }
            }
        }
        stopped = false;
        for (int i = 1; i <= x; i++) {
            if (stopped == false) {
                arr[y][x - i] = 1;
                if (board[y][x - i] != 'o') {

                    if ((board[y][x] == 'R' and (board[y][x - i] == 'p' or board[y][x - i] == 'h' or board[y][x - i] == 'k' or board[y][x - i] == 'q' or board[y][x - i] == 'b' or board[y][x - i] == 'r')) or (board[y][x] == 'r' and (board[y][x - i] == 'P' or board[y][x - i] == 'H' or board[y][x - i] == 'K' or board[y][x - i] == 'Q' or board[y][x - i] == 'B' or board[y][x - i] == 'R'))) {
                        arr[y][x - i] = 2;
                    }
                    else {
                        arr[y][x - i] = 0;
                    }
                    stopped = true;
                }

            }
        }
        stopped = false;
        for (int i = 1; i <= 7 - x; i++) {
            if (stopped == false) {
                arr[y][x + i] = 1;
                if (board[y][x + i] != 'o') {

                    if ((board[y][x] == 'R' and (board[y][x + i] == 'p' or board[y][x + i] == 'h' or board[y][x + i] == 'k' or board[y][x + i] == 'q' or board[y][x + i] == 'b' or board[y][x + i] == 'r')) or (board[y][x] == 'r' and (board[y][x + i] == 'P' or board[y][x + i] == 'H' or board[y][x + i] == 'K' or board[y][x + i] == 'Q' or board[y][x + i] == 'B' or board[y][x + i] == 'R'))) {
                        arr[y][x + i] = 2;
                    }
                    else {
                        arr[y][x + i] = 0;
                    }
                    stopped = true;
                }

            }
        }
#pragma endregion

        show_moves(arr);

#pragma region  Выполнение_перемешения
        string answer;
        if (is_empty(arr) == true)
        {
            return true;
        }
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }
#pragma endregion

        return false;
    }

    //Тут логика хода коня
    bool horse_move(int x, int y, string color, int index)
    {
        refresh_board();

#pragma region Вычисление_нужных_данных
        int arr[8][8];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                arr[i][j] = 0;
            }
        }
#pragma endregion

#pragma region  Вычисление_возможных_ходов
        if (figures[index].xcoord > 1 and figures[index].ycoord < 7)
        {
            if (board[y + 1][x - 2] == 'o')
            {
                arr[y + 1][x - 2] = 1;
            }
            if ((board[y][x] == 'H' and (board[y + 1][x - 2] == 'p' or board[y + 1][x - 2] == 'h' or board[y + 1][x - 2] == 'k' or board[y + 1][x - 2] == 'q' or board[y + 1][x - 2] == 'b' or board[y + 1][x - 2] == 'r')) or (board[y][x] == 'h' and (board[y + 1][x - 2] == 'P' or board[y + 1][x - 2] == 'H' or board[y + 1][x - 2] == 'K' or board[y + 1][x - 2] == 'Q' or board[y + 1][x - 2] == 'B' or board[y + 1][x - 2] == 'R'))) {
                arr[y + 1][x - 2] = 2;
            }
        }
        if (figures[index].xcoord > 1 and figures[index].ycoord > 0)
        {
            if (board[y - 1][x - 2] == 'o')
            {
                arr[y - 1][x - 2] = 1;
            }
            if ((board[y][x] == 'H' and (board[y - 1][x - 2] == 'p' or board[y - 1][x - 2] == 'h' or board[y - 1][x - 2] == 'k' or board[y - 1][x - 2] == 'q' or board[y - 1][x - 2] == 'b' or board[y - 1][x - 2] == 'r')) or (board[y][x] == 'h' and (board[y - 1][x - 2] == 'P' or board[y - 1][x - 2] == 'H' or board[y - 1][x - 2] == 'K' or board[y - 1][x - 2] == 'Q' or board[y - 1][x - 2] == 'B' or board[y - 1][x - 2] == 'R'))) {
                arr[y - 1][x - 2] = 2;
            }
        }
        if (figures[index].xcoord > 0 and figures[index].ycoord > 1)
        {
            if (board[y - 2][x - 1] == 'o')
            {
                arr[y - 2][x - 1] = 1;
            }
            if ((board[y][x] == 'H' and (board[y - 2][x - 1] == 'p' or board[y - 2][x - 1] == 'h' or board[y - 2][x - 1] == 'k' or board[y - 2][x - 1] == 'q' or board[y - 2][x - 1] == 'b' or board[y - 2][x - 1] == 'r')) or (board[y][x] == 'h' and (board[y - 2][x - 1] == 'P' or board[y - 2][x - 1] == 'H' or board[y - 2][x - 1] == 'K' or board[y - 2][x - 1] == 'Q' or board[y - 2][x - 1] == 'B' or board[y - 2][x - 1] == 'R'))) {
                arr[y - 2][x - 1] = 2;
            }
        }
        if (figures[index].xcoord < 7 and figures[index].ycoord>1)
        {
            if (board[y - 2][x + 1] == 'o')
            {
                arr[y - 2][x + 1] = 1;
            }
            if ((board[y][x] == 'H' and (board[y - 2][x + 1] == 'p' or board[y - 2][x + 1] == 'h' or board[y - 2][x + 1] == 'k' or board[y - 2][x + 1] == 'q' or board[y - 2][x + 1] == 'b' or board[y - 2][x + 1] == 'r')) or (board[y][x] == 'h' and (board[y - 2][x + 1] == 'P' or board[y - 2][x + 1] == 'H' or board[y - 2][x + 1] == 'K' or board[y - 2][x + 1] == 'Q' or board[y - 2][x + 1] == 'B' or board[y - 2][x + 1] == 'R'))) {
                arr[y - 2][x + 1] = 2;
            }
        }
        if (figures[index].xcoord < 6 and figures[index].ycoord>0)
        {
            if (board[y - 1][x + 2] == 'o')
            {
                arr[y - 1][x + 2] = 1;
            }
            if ((board[y][x] == 'H' and (board[y - 1][x + 2] == 'p' or board[y - 1][x + 2] == 'h' or board[y - 1][x + 2] == 'k' or board[y - 1][x + 2] == 'q' or board[y - 1][x + 2] == 'b' or board[y - 1][x + 2] == 'r')) or (board[y][x] == 'h' and (board[y - 1][x + 2] == 'P' or board[y - 1][x + 2] == 'H' or board[y - 1][x + 2] == 'K' or board[y - 1][x + 2] == 'Q' or board[y - 1][x + 2] == 'B' or board[y - 1][x + 2] == 'R'))) {
                arr[y - 1][x + 2] = 2;
            }
        }
        if (figures[index].xcoord < 6 and figures[index].ycoord < 7)
        {
            if (board[y + 1][x + 2] == 'o')
            {
                arr[y + 1][x + 2] = 1;
            }
            if ((board[y][x] == 'H' and (board[y + 1][x + 2] == 'p' or board[y + 1][x + 2] == 'h' or board[y + 1][x + 2] == 'k' or board[y + 1][x + 2] == 'q' or board[y + 1][x + 2] == 'b' or board[y + 1][x + 2] == 'r')) or (board[y][x] == 'h' and (board[y + 1][x + 2] == 'P' or board[y + 1][x + 2] == 'H' or board[y + 1][x + 2] == 'K' or board[y + 1][x + 2] == 'Q' or board[y + 1][x + 2] == 'B' or board[y + 1][x + 2] == 'R'))) {
                arr[y + 1][x + 2] = 2;
            }
        }
        if (figures[index].xcoord < 7 and figures[index].ycoord < 6)
        {
            if (board[y + 2][x + 1] == 'o')
            {
                arr[y + 2][x + 1] = 1;
            }
            if ((board[y][x] == 'H' and (board[y + 2][x + 1] == 'p' or board[y + 2][x + 1] == 'h' or board[y + 2][x + 1] == 'k' or board[y + 2][x + 1] == 'q' or board[y + 2][x + 1] == 'b' or board[y + 2][x + 1] == 'r')) or (board[y][x] == 'h' and (board[y + 2][x + 1] == 'P' or board[y + 2][x + 1] == 'H' or board[y + 2][x + 1] == 'K' or board[y + 2][x + 1] == 'Q' or board[y + 2][x + 1] == 'B' or board[y + 2][x + 1] == 'R'))) {
                arr[y + 2][x + 1] = 2;
            }
        }
        if (figures[index].xcoord > 0 and figures[index].ycoord < 6)
        {
            if (board[y + 2][x - 1] == 'o')
            {
                arr[y + 2][x - 1] = 1;
            }
            if ((board[y][x] == 'H' and (board[y + 2][x - 1] == 'p' or board[y + 2][x - 1] == 'h' or board[y + 2][x - 1] == 'k' or board[y + 2][x - 1] == 'q' or board[y + 2][x - 1] == 'b' or board[y + 2][x - 1] == 'r')) or (board[y][x] == 'h' and (board[y + 2][x - 1] == 'P' or board[y + 2][x - 1] == 'H' or board[y + 2][x - 1] == 'K' or board[y + 2][x - 1] == 'Q' or board[y + 2][x - 1] == 'B' or board[y + 2][x - 1] == 'R'))) {
                arr[y + 2][x - 1] = 2;
            }
        }
#pragma endregion

        show_moves(arr);

#pragma region  Выполнение_перемешения
        string answer;
        if (is_empty(arr) == true)
        {
            return true;
        }
        do
        {
            cout << "Введите клетку на которую хотите сдвинуть фигуру(Например е4):" << endl;
            cin >> answer;
        } while (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 0);
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 1)
        {
            figures[index].xcoord = decryption_x(answer) - 1;
            figures[index].ycoord = converter(decryption_y(answer));
            figures[index].was_moved = true;
        }
        if (arr[converter(decryption_y(answer))][decryption_x(answer) - 1] == 2)
        {
            for (int k = 0; k < 32; k++)
            {
                if (figures[k].xcoord == decryption_x(answer) - 1 and converter(figures[k].ycoord) == decryption_y(answer))
                {
                    figures[k].xcoord = -1;
                    figures[k].ycoord = -1;
                    figures[index].xcoord = decryption_x(answer) - 1;
                    figures[index].ycoord = converter(decryption_y(answer));
                    figures[index].was_moved = true;
                }

            }
        }

#pragma endregion

        return false;
    }

#pragma endregion

#pragma region Разные_выводы_доски
    //Обновляет доску
    void refresh_board()
    {

        for (int i = 0; i < 8; i++) {

            for (int j = 0; j < 8; j++) {
                bool occupied = false;
                for (int k = 0; k < 32; k++) {
                    if (figures[k].ycoord == i and figures[k].xcoord == j) {
                        if (figures[k].type == "pawn")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'P';
                            }
                            else {
                                board[i][j] = 'p';
                            }
                        }
                        if (figures[k].type == "rook")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'R';
                            }
                            else {
                                board[i][j] = 'r';
                            }
                        }
                        if (figures[k].type == "horse")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'H';
                            }
                            else {
                                board[i][j] = 'h';
                            }
                        }
                        if (figures[k].type == "bishop")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'B';
                            }
                            else {
                                board[i][j] = 'b';
                            }
                        }
                        if (figures[k].type == "queen")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'Q';
                            }
                            else {
                                board[i][j] = 'q';
                            }
                        }
                        if (figures[k].type == "king")
                        {
                            if (figures[k].color == "white")
                            {
                                board[i][j] = 'K';
                            }
                            else {
                                board[i][j] = 'k';
                            }
                        }
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    board[i][j] = 'o';
                }
            }
        }
    }

    //Выводит доску
    void view_board()
    {
        refresh_board();
        cout << endl << endl << endl << "Доска на данный момент:" << endl;
        cout << "  a b c d e f g h" << endl << "  ---------------" << endl;
        for (int i = 0; i < 8; i++) {
            cout << converter(i) << '|';
            for (int j = 0; j < 8; j++) {
                cout << board[i][j] << ' ';
            }
            cout << '|' << converter(i) << endl;
        }
        cout << "  ---------------" << endl << "  a b c d e f g h" << endl << endl << endl;
    }

    //Отвечает за вывод возможных ходов
    void show_moves(int arr[8][8]) {
        refresh_board();
        cout << "  a b c d e f g h" << endl << "  ---------------" << endl;
        for (int i = 0; i < 8; i++) {
            cout << converter(i) << '|';
            for (int j = 0; j < 8; j++) {
                if (arr[i][j] == 0) {
                    cout << board[i][j] << ' ';
                }
                else {
                    cout << red << board[i][j] << nul << ' ';
                }
            }
            cout << '|' << converter(i) << endl;
        }
        cout << "  ---------------" << endl << "  a b c d e f g h" << endl << endl << endl;
    }
#pragma endregion

#pragma region Дешифраторы_координат
    int converter(int a) {
        return (8 - a);
    }

    int decryption_x(string your_move)
    {
        switch (your_move[0])
        {
        case('a'):
            return(1);
            break;
        case('b'):
            return(2);
            break;
        case('c'):
            return(3);
            break;
        case('d'):
            return(4);
            break;
        case('e'):
            return(5);
            break;
        case('f'):
            return(6);
            break;
        case('g'):
            return(7);
            break;
        case('h'):
            return(8);
            break;
        }
    }

    int decryption_y(string your_move)
    {
        switch (your_move[1]) // Здесь должен быть индекс второго символа
        {
        case('1'):
            return(1);
            break;
        case('2'):
            return(2);
            break;
        case('3'):
            return(3);
            break;
        case('4'):
            return(4);
            break;
        case('5'):
            return(5);
            break;
        case('6'):
            return(6);
            break;
        case('7'):
            return(7);
            break;
        case('8'):
            return(8);
            break;
        }
    }

#pragma endregion

#pragma region Всякие_проверки
    bool proverka(string collector)
    {
        if (collector[0] == 'a' or collector[0] == 'b' or collector[0] == 'c' or collector[0] == 'd' or collector[0] == 'e' or collector[0] == 'f' or collector[0] == 'g' or collector[0] == 'h') {
            if (collector[1] == '1' or collector[1] == '2' or collector[1] == '3' or collector[1] == '4' or collector[1] == '5' or collector[1] == '6' or collector[1] == '7' or collector[1] == '8') {
                return true;
            }
        }
        cout << "Вы ввели неподлежащий исчеслению ход" << endl;
        return false;
    }

    //Проверяет клетку на наличие фигур
    bool is_not_empty(string collector)
    {
        if (board[converter(decryption_y(collector))][decryption_x(collector) - 1] == 'o') {
            cout << "Вы должны выбрать не пустую клетку" << endl;
            return true;
        }
        return false;
    }

    //При начале хода проверяет цвет фигуры которую вы вибираете
    bool is_your_figure(string collector, string color)
    {
        for (int k = 0; k < 32; k++) {
            if (figures[k].color == color) {
                if (figures[k].xcoord == decryption_x(collector) - 1 and figures[k].ycoord == converter(decryption_y(collector)) and figures[k].color == color) {
                    return true;
                }
            }
        }
        cout << "Вы должны выбрать СВОЮ фигуру" << endl;
        return false;
    }

    //В этой функции программа понимает если у фигуры нет вариантов ходов
    bool is_empty(int arr[8][8])
    {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (arr[i][j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }
#pragma endregion

#pragma endregion
};

#pragma endregion

int main() {
    setlocale(LC_ALL, "Russian");
    Gamemod* gamemod = new Gamemod;

    // Вызов функции для отображения доски
    string counter = "white";
    while (gamemod->figures[12].xcoord != -1 and gamemod->figures[28].xcoord != -1) {
        if (counter == "white") {
            gamemod->turn("white");
            counter = "black";
        }
        else {
            gamemod->turn("black");
            counter = "white";
        }
    }
    if (gamemod->figures[12].xcoord == -1)
    {
        cout << "Черные победили" << endl;
    }
    else
    {
        cout << "Белые победили" << endl;
    }
    delete gamemod;
    return 0;
}