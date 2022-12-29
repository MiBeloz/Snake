#include<iostream>
#include<Windows.h>
#include<vector>

const int ROW = 20;
const int COL = 30;
int slTime = 500;
int slTimeStep = 10;
int points = 0;
char S = 'S';
char F = 'F';
char M = '#';
std::string PointsString = "\tОчки: ";
std::string GameOver = "\tИгра закончена!";
//int chek = 0;

short numPath = 3;
bool gameRun = true;
bool foodNext = true;
COORD coordSnake{ 0,0 };
COORD coordFood{ 0,0 };
COORD coordSnakeBlock{ 0,0 };
COORD coordPoints{ 0,0 };

struct Snake {
    short x;
    short y;
};

std::vector<Snake> snakeVector{ {2,ROW / 2} };

void move(std::vector<Snake>& sVector) {
    coordSnake.X = sVector.at(0).x;
    coordSnake.Y = sVector.at(0).y;

    if (coordFood.X == coordSnake.X && coordFood.Y == coordSnake.Y) {
        slTime -= slTimeStep;
        if (slTime < 100) {
            slTime = 100;
        }
        coordPoints.X = 0;
        coordPoints.Y = ROW + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordPoints);
        std::cout << PointsString << ++points;
        //std::cout << std::endl << chek;
        coordFood.X = 1 + rand() % (COL - 2);
        coordFood.Y = 1 + rand() % (ROW - 2);
        foodNext = true;
        while (foodNext) {
            for (int i = 0; i < snakeVector.size(); i++) {
                if ((coordFood.X == snakeVector.at(i).x) && (coordFood.Y == snakeVector.at(i).y)) {
                    coordFood.X = 1 + rand() % (COL - 2);
                    coordFood.Y = 1 + rand() % (ROW - 2);
                    foodNext = true;
                    //chek++;
                }
                else {
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordFood);
                    std::cout << F;
                    foodNext = false;
                }
            }

        }
        snakeVector.push_back(snakeVector.at(0));
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << " ";
    if (snakeVector.size() > 1) {

        coordSnakeBlock.X = snakeVector.back().x;
        coordSnakeBlock.Y = snakeVector.back().y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
        std::cout << " ";
        snakeVector.at(0).x = coordSnake.X;
        snakeVector.at(0).y = coordSnake.Y;
        for (int i = (int)snakeVector.size() - 1, j = 0; i > 0; i--) {
            j = i - 1;
            snakeVector.at(i).x = snakeVector.at(j).x;
            snakeVector.at(i).y = snakeVector.at(j).y;
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
    std::cout << S;
    if (snakeVector.size() > 1) {
        coordSnakeBlock.X = snakeVector.at(0).x;
        coordSnakeBlock.Y = snakeVector.at(0).y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
        std::cout << S;
        for (int i = (int)snakeVector.size() - 1; i > 0; i--) {
            coordSnakeBlock.X = snakeVector.at(i).x;
            coordSnakeBlock.Y = snakeVector.at(i).y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnakeBlock);
            std::cout << S;
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

    if (snakeVector.size() > 2) {
        for (int i = 1; i < snakeVector.size(); i++) {
            if ((snakeVector.at(0).x == snakeVector.at(i).x) && (snakeVector.at(0).y == snakeVector.at(i).y)) {
                gameRun = false;
                coordSnake.X = 0;
                coordSnake.Y = ROW + 2;
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    //system("chcp 1251 > null");
    srand(unsigned int(time(NULL)));

    CONSOLE_CURSOR_INFO curs = { 0 };
    curs.dwSize = sizeof(curs);
    curs.bVisible = FALSE;
    ::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);

    char arr[ROW][COL]{};
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i > 0 && i < ROW - 1 && j > 0 && j < COL - 1) {
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

    std::cout << std::endl << std::endl << PointsString << points;
    //std::cout << std::endl << chek;

    coordFood.X = 6 + rand() % (COL - 8);
    coordFood.Y = 1 + rand() % (ROW - 2);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordFood);
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

        move(snakeVector);
    } while (gameRun);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordSnake);
    std::cout << PointsString << points << std::endl;
    //std::cout << chek << std::endl;
    std::cout << GameOver << std::endl;

    system("pause > null");
    return 0;
}