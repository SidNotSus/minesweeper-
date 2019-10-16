

#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>


using namespace std;

#define BOARD 10
#define MINES 10


int Array[BOARD][BOARD];

bool open[BOARD][BOARD];

// открытие мин
void openmines(bool secondTime) 
{
	if (secondTime)
	{
		for (int i = 0; i < BOARD; i++) 
		{
			for (int j = 0; j < BOARD; j++) 
			{
				
				if (Array[i][j] == -1) open[i][j] = true;
			}
		}
	}
	for (int i = 0; i < BOARD; i++) {
		for (int j = 0; j < BOARD; j++) {
			if (Array[i][j] == -1) open[i][j] = true;
		}
	}
}


// try mine 
bool mine(int i, int j) 
{
	
	if ((i >= 0) && (i < BOARD)) 
	{
		if ((j >= 0) && (j < BOARD)) 
		{
			if (Array[i][j] == -1) return true;
		}
	}
	return false;
}

// try empty
bool empty(int i, int j) 
{
	if ((i >= 0) && (i < BOARD)) 
	{
		if ((j >= 0) && (j < BOARD)) 
		{
			if (Array[i][j] == 0) return true;
		}
	}
	return false;
}

// fucking shit
void clean(int i, int j) 
{
	if ((i >= 0) && (i < BOARD)) 
	{
		if ((j >= 0) && (j < BOARD)) 
		{
			if (!open[i][j]) 
			{
				open[i][j] = true;
				//пустое
				if (Array[i][j] == 0) {
					clean(i - 1, j - 1);
					clean(i - 1, j);
					clean(i - 1, j + 1);
					clean(i, j - 1);
					clean(i, j + 1);
					clean(i + 1, j - 1);
					clean(i + 1, j);
					clean(i + 1, j + 1);
				}
				// не пустое
				else {
					if (empty(i - 1, j - 1)) clean(i - 1, j - 1);
					if (empty(i - 1, j)) clean(i - 1, j);
					if (empty(i - 1, j + 1)) clean(i - 1, j + 1);
					if (empty(i, j - 1)) clean(i, j - 1);
					if (empty(i, j + 1)) clean(i, j + 1);
					if (empty(i + 1, j - 1)) clean(i + 1, j - 1);
					if (empty(i + 1, j)) clean(i + 1, j);
					if (empty(i + 1, j + 1)) clean(i + 1, j + 1);
				}
			}
		}
	}
}


void printmine(HANDLE hConsole) 
{
	SetConsoleTextAttribute(hConsole, 12);  
	printf ("* ");
	SetConsoleTextAttribute(hConsole, 7);   
}


void draw_Array(HANDLE hConsole,bool secondTime) 
{
	SetConsoleTextAttribute(hConsole, 2);  // 1 
	printf ("  A B C D E F G H I J\n");
	SetConsoleTextAttribute(hConsole, 7);  // 2

	if (secondTime)
	{
		for (int x = 0; x < BOARD; x++) 
		{
			printf("                                                 ");
			SetConsoleTextAttribute(hConsole, 2);  // 1
			printf("%d ", x);
			SetConsoleTextAttribute(hConsole, 7);  // 
			for (int y = 0; y < BOARD; y++) 
			{
				
				if (open[x][y]) {
					SetConsoleTextAttribute(hConsole, 8);  // gray text
					if (Array[x][y] == -1) printmine(hConsole);
					else if (Array[x][y] == 0) printf(". ");
					else cout << Array[x][y] << " ";
					SetConsoleTextAttribute(hConsole, 7);  // white text
				}
				else 
				{

					printf("# ");

				}
			}
			printf("\n");
		}

	}
	else 
	{
		for (int x = 0; x < BOARD; x++) 
		{
			SetConsoleTextAttribute(hConsole, 2);  // 1
			printf("%d ", x);
			SetConsoleTextAttribute(hConsole, 7);  // 
			for (int y = 0; y < BOARD; y++) 
			{
				if (open[x][y]) 
				{
					SetConsoleTextAttribute(hConsole, 8);  // gray text
					if (Array[x][y] == -1) printmine(hConsole);
					else if (Array[x][y] == 0) printf(". ");
					else cout << Array[x][y] << " ";
					SetConsoleTextAttribute(hConsole, 7);  // white text
				}
				else 
				{

					printf("# ");

				}
			}
			printf("\n");
		}
	}
}


void ENDGAME(HANDLE hConsole, bool loser) 
{
	COORD coord;
	coord.X = 33;
	coord.Y = 10;
	system("cls");
	draw_Array(hConsole, false);
	SetConsoleCursorPosition(hConsole, coord);
	if (loser) 
	{
		SetConsoleTextAttribute(hConsole, 12); 
		// red text
		printf("\n\n\n\n\n\n\n");
		for (int delay=0; delay<18; delay++)
		{
			Sleep(100);
			printf("\n");
		}
		system("cls");
		for (int delay = 0; delay < 10; delay++)
		{
			Sleep(70);
			printf("\n");
		}
		printf("                                                  К А К  Т А К  ТО ?!\n");
		printf("                                               Проиграл в простейшую игру\n");
		printf("                                                     Вот все мины\n");
		SetConsoleTextAttribute(hConsole, 7);  // white text
	}
	else 
	{
		SetConsoleTextAttribute(hConsole, 10);  // red text
		printf("\n\n\n\n\n\n\n");
		for (int delay = 0; delay < 18; delay++)
		{
			Sleep(100);
			printf("\n");
		}
		system("cls");
		for (int delay = 0; delay < 10; delay++)
		{
			Sleep(70);
			printf("\n");
		}
		printf("                                                   ПРОСТО КРАСАВЧИК!\n");
		printf("                                        Тут должна была быть пасхалка про postal4 \n");
		printf("                                           Но тут только мордочка котика ^^\n");
		SetConsoleTextAttribute(hConsole, 7);  // white text
	}
	for (int delay = 0; delay < 4; delay++)
	{
		Sleep(50);
		printf("\n");
	}
	printf("                                                 ");
	openmines(true);
	draw_Array(hConsole,true);
	_getch();
}

//// открытие мин
//void openmines() {
//	for (int i = 0; i < BOARD; i++) {
//		for (int j = 0; j < BOARD; j++) {
//			if (Array[i][j] == -1) open[i][j] = true;
//		}
//	}
//}

// проверка выйгрыша
bool checkwin() 
{
	for (int x = 0; x < BOARD; x++) 
	{
		for (int y = 0; y < BOARD; y++) 
		{
			if ((Array[x][y] != -1) && (!open[x][y])) return false;
		}
	}
	return true;
}


int main()
{
	int i, j, k = 0;
	char s[3];
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, "rus");
	srand((int)time(NULL));

	for (int c = 0; c < 100; c++) { Array[c / 10][c % 10] = 0; open[c / 10][c % 10] = false; }
	// ставим мины
	for (int c = 0; c < MINES; c++) {
		do {
			i = rand() % BOARD; j = rand() % BOARD;
		} while (Array[i][j] != 0);
		Array[i][j] = -1;
	}
	// заполняем массив поля цифрами
	for (i = 0; i < BOARD; i++) {
		for (j = 0; j < BOARD; j++) {
			if (Array[i][j] != -1) {
				k = 0;
				if (mine(i - 1, j - 1)) k++;
				if (mine(i - 1, j)) k++;
				if (mine(i - 1, j + 1)) k++;
				if (mine(i, j - 1)) k++;
				if (mine(i, j + 1)) k++;
				if (mine(i + 1, j - 1)) k++;
				if (mine(i + 1, j)) k++;
				if (mine(i + 1, j + 1)) k++;
				Array[i][j] = k;
			}
		}
	}

	// главный игровой цикл
	while (true) {
		// чистка
		system("cls");
		// поле
		draw_Array(hConsole,false);
		printf ( "\n");
		// где ! мина 
		printf ("Введите координаты предпологаемой свободной клетки (БуваЦифра) : ");
		cin >> s;
		//scanf_s("%s", s);
		//////////////////////////////////////////////////////////////////////////////
		if ((s[0] >= 65) && (s[0] <= 74)) j = s[0] - 65;        //заглавные
		else if ((s[0] >= 97) && (s[0] <= 106)) j = s[0] - 97;  //маленькие
		else continue;                              
		if ((s[1] >= 48) && (s[1] <= 57)) i = s[1] - 48;
		else continue;
		//////////////////////////////////////////////////////////////////////////////

		clean(i, j);

		if (mine(i, j)) { openmines(false); ENDGAME(hConsole, true); break; }  // вызов проигрыша
		if (checkwin()) { ENDGAME(hConsole, false); break; }                 // вызов победы
	}

	return 0;
}
