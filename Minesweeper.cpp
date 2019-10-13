

#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>


using namespace std;

#define BOARD 10
#define MINES 10

int Array[BOARD][BOARD];

bool open[BOARD][BOARD];

// try mine 
bool mine(int i, int j) {
	if ((i >= 0) && (i < BOARD)) {
		if ((j >= 0) && (j < BOARD)) {
			if (Array[i][j] == -1) return true;
		}
	}
	return false;
}

// try empty
bool empty(int i, int j) {
	if ((i >= 0) && (i < BOARD)) {
		if ((j >= 0) && (j < BOARD)) {
			if (Array[i][j] == 0) return true;
		}
	}
	return false;
}

// fucking shit
void clean(int i, int j) {
	// проверим на выход за пределы массива
	if ((i >= 0) && (i < BOARD)) {
		if ((j >= 0) && (j < BOARD)) {
			// проверим, не было ли открыто поле раньше
			if (!open[i][j]) {
				// откроем
				open[i][j] = true;
				// если поле пустое (=0), просто пооткрываем всех его соседей
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
				// если не пустое (!=0) открываем только пустых (=0) соседей
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


void printmine(HANDLE hConsole) {
	SetConsoleTextAttribute(hConsole, 12);  
	printf ("* ");
	SetConsoleTextAttribute(hConsole, 7);   
}


void draw_Array(HANDLE hConsole) {
	SetConsoleTextAttribute(hConsole, 2);  // 1 
	printf ("  A B C D E F G H I J\n");
	SetConsoleTextAttribute(hConsole, 7);  // 2
	for (int x = 0; x < BOARD; x++) {
		SetConsoleTextAttribute(hConsole, 2);  // 1
		printf ("%d ", x);
		SetConsoleTextAttribute(hConsole, 7);  // 
		for (int y = 0; y < BOARD; y++) {
			if (open[x][y]) {
				SetConsoleTextAttribute(hConsole, 8);  // gray text
				if (Array[x][y] == -1) printmine(hConsole);
				else if (Array[x][y] == 0) printf(". ");
				else cout << Array[x][y] << " ";
				SetConsoleTextAttribute(hConsole, 7);  // white text
			}
			else {

				printf ( "# ");

			}
		}
		printf ("\n");
	}
}


void ENDGAME(HANDLE hConsole, bool loser) {
	COORD coord;
	coord.X = 33;
	coord.Y = 10;
	system("cls");
	draw_Array(hConsole);
	SetConsoleCursorPosition(hConsole, coord);
	if (loser) {
		SetConsoleTextAttribute(hConsole, 12);  // red text
		printf("Л О Х, П И Д Р !");
		SetConsoleTextAttribute(hConsole, 7);  // white text
	}
	else {
		SetConsoleTextAttribute(hConsole, 10);  // red text
		printf("Т У П А  П О В А Р !");
		SetConsoleTextAttribute(hConsole, 7);  // white text
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	_getch();
}

// в случае проигрыша эта функция откроет все мины
void openmines() {
	for (int i = 0; i < BOARD; i++) {
		for (int j = 0; j < BOARD; j++) {
			if (Array[i][j] == -1) open[i][j] = true;
		}
	}
}

// проверяет, все ли поле открыто, кроме мин (таково условие победы =)
bool checkwin() {
	for (int x = 0; x < BOARD; x++) {
		for (int y = 0; y < BOARD; y++) {
			if ((Array[x][y] != -1) && (!open[x][y])) return false;
		}
	}
	return true;
}


int main()
{
	int i, j, k = 0;
	char s[3];
	// хэндл экна необходим для рисования цветного текста
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// инициализация
	setlocale(LC_ALL, "rus");
	srand((int)time(NULL));

	// все чистим
	for (int c = 0; c < 100; c++) { Array[c / 10][c % 10] = 0; open[c / 10][c % 10] = false; }
	// заполняем массив поля минами
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
		// чистим экран от старого рисунка
		system("cls");
		// рисуем поле
		draw_Array(hConsole);
		printf ( "\n");
		// запрашиваем координаты удара
		printf ("Введите координаты предпологаемой свободной клетки : ");
		scanf_s("%s", s);
		// переводим координаты в цифровой вид
		if ((s[0] >= 65) && (s[0] <= 74)) j = s[0] - 65;        // буква в промежутке от A до J
		else if ((s[0] >= 97) && (s[0] <= 106)) j = s[0] - 97;  // буква в промежутке от a до j
		else continue;                              // если введены неверные значения, возврат в начало цикла
		if ((s[1] >= 48) && (s[1] <= 57)) i = s[1] - 48;
		else continue;
		// далее проверяем все восемь окрестных полей на пустые клетки
		// и если надо показываем некий кусок поля (ну, много пустых клеток, например)
		clean(i, j);

		if (mine(i, j)) { openmines(); ENDGAME(hConsole, true); break; }  // программа покидает цикл в случае проигрыша
		if (checkwin()) { ENDGAME(hConsole, false); break; }                 // или победы
	}

	return 0;
}
