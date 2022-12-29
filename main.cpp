#include<iostream>
#include<Windows.h>
#include<vector>

struct Snake {
    short x;
    short y;
};

struct Food{
    short x;
    short y;
};

void foodCheck(std::vector<Snake>& sVector, Food& food, int& slTime, const int slTimeStep, int& points, const int rows, const int cols, std::string pointsString, char F);

void move(std::vector<Snake>& sVector, COORD& coordSnake, const int ROW, const int COL, int numPath, bool& gameRun, char S);

int main()
{
    setlocale(LC_ALL, "ru");
    //system("chcp 1251 > null");
    srand(unsigned int(time(NULL)));

    const int rows = 20;
    const int cols = 30;
    int slTime = 500;
    int slTimeStep = 10;
    int points = 0;
    char S = 'S';
    char F = 'F';
    char M = '#';
    std::string pointsString = "\tОчки: ";
    std::string gameOver = "\tИгра закончена!";
    //int chek = 0;

    short numPath = 3;
    bool gameRun = true;
    bool foodNext = true;
    COORD coordSnake{ 0,0 };

    Food food{};
    food.x = 3;//6 + rand() % (COL - 8);
    food.y = rows / 2;//1 + rand() % (ROW - 2);
    std::vector<Snake> snakeVector{ {2,rows / 2} };

    CONSOLE_CURSOR_INFO curs = { 0 };
    curs.dwSize = sizeof(curs);
    curs.bVisible = FALSE;
    ::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);

    char arr[rows][cols]{};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0 && i < rows - 1 && j > 0 && j < cols - 1) {
                arr[i][j] = ' ';
                std::cout << arr[i][j];
            }
            else {
                arr[i][j] = M;
                std::cout << arr[i][j];
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << pointsString << points;
    //std::cout << std::endl << chek;

    coordSnake.X = food.x;
    coordSnake.Y = food.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << F;

    do
    {
        Sleep(slTime);

        if (GetAsyncKeyState(VK_UP)) {
            if (numPath != 1) {
                numPath = 0;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            if (numPath != 0) {
                numPath = 1;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            if (numPath != 3) {
                numPath = 2;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            if (numPath != 2) {
                numPath = 3;
            }
        }
        else if (GetAsyncKeyState(VK_F12)) {
            system("pause > null");
        }

        foodCheck(snakeVector, food, slTime, slTimeStep, points, rows, cols, pointsString, F);
        move(snakeVector, coordSnake, rows, cols, numPath, gameRun, S);
    } while (gameRun);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << pointsString << points << std::endl;
    //std::cout << chek << std::endl;
    std::cout << gameOver << std::endl;

    system("pause > null");
    return 0;
}

void foodCheck(std::vector<Snake>& sVector, Food& food, int& slTime, const int slTimeStep, int& points, const int rows, const int cols, std::string pointsString, char F) {
    bool foodNext = true;
    COORD snake{};
    snake.X = sVector.at(0).x;
    snake.Y = sVector.at(0).y;

    if (food.x == snake.X && food.y == snake.Y) {
        slTime -= slTimeStep;
        if (slTime < 100) {
            slTime = 100;
        }
        snake.X = 0;
        snake.Y = rows + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake);
        std::cout << pointsString << ++points;
        food.x = 1 + rand() % (cols - 2);
        food.y = 1 + rand() % (rows - 2);
        foodNext = true;
        while (foodNext) {
            for (int i = 0; i < sVector.size(); i++) {
                if ((food.x == sVector.at(i).x) && (food.y == sVector.at(i).y)) {
                    food.x = 1 + rand() % (cols - 2);
                    food.y = 1 + rand() % (rows - 2);
                    foodNext = true;
                }
                else {
                    snake.X = food.x;
                    snake.Y = food.y;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake);
                    std::cout << F;
                    foodNext = false;
                }
            }

        }
        sVector.push_back(sVector.at(0));
    }
}

void move(std::vector<Snake>& sVector, COORD& coordSnake, const int ROW, const int COL, int numPath, bool& gameRun, char S) {
    COORD coordSnakeBlock{ 0,0 };

    coordSnake.X = sVector.at(0).x;
    coordSnake.Y = sVector.at(0).y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << " ";
    if (sVector.size() > 1) {

        coordSnakeBlock.X = sVector.back().x;
        coordSnakeBlock.Y = sVector.back().y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
        std::cout << " ";
        sVector.at(0).x = coordSnake.X;
        sVector.at(0).y = coordSnake.Y;
        for (int i = (int)sVector.size() - 1, j = 0; i > 0; i--) {
            j = i - 1;
            sVector.at(i).x = sVector.at(j).x;
            sVector.at(i).y = sVector.at(j).y;
        }
    }

    if (numPath == 0) {
        coordSnake.Y -= 1;
    }
    else if (numPath == 1) {
        coordSnake.Y += 1;
    }
    else if (numPath == 2) {
        coordSnake.X -= 1;
    }
    else if (numPath == 3) {
        coordSnake.X += 1;
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << "S";
    if (sVector.size() > 1) {
        coordSnakeBlock.X = sVector.at(0).x;
        coordSnakeBlock.Y = sVector.at(0).y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
        std::cout << "S";
        for (int i = (int)sVector.size() - 1; i > 0; i--) {
            coordSnakeBlock.X = sVector.at(i).x;
            coordSnakeBlock.Y = sVector.at(i).y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
            std::cout << "S";
        }
    }

    sVector.at(0).x = coordSnake.X;
    sVector.at(0).y = coordSnake.Y;

    if (coordSnake.X == COL - 1) {
        gameRun = false;
        coordSnake.X = 0;
        coordSnake.Y = ROW + 2;
    }
    if (coordSnake.X == 0) {
        gameRun = false;
        coordSnake.X = 0;
        coordSnake.Y = ROW + 2;
    }
    if (coordSnake.Y == ROW - 1) {
        gameRun = false;
        coordSnake.X = 0;
        coordSnake.Y = ROW + 2;
    }
    if (coordSnake.Y == 0) {
        gameRun = false;
        coordSnake.X = 0;
        coordSnake.Y = ROW + 2;
    }

    if (sVector.size() > 2) {
        for (int i = 1; i < sVector.size(); i++) {
            if ((sVector.at(0).x == sVector.at(i).x) && (sVector.at(0).y == sVector.at(i).y)) {
                gameRun = false;
                coordSnake.X = 0;
                coordSnake.Y = ROW + 2;
            }
        }
    }
}