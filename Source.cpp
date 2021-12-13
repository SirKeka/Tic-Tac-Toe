// ��������� �������� ������
// ��������� ������ � "��������-������" ������ ������������
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ���������� ���������
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions()
{
	std::cout << "����� ���������� �� ��������� ����� ������� - ������: ��������-������.\n";
	std::cout << "--��� ������������ ���� ������������ ����������� ����������\n\n";
	std::cout << "������ � ����� ����, ����� ����� 0 - 8. �����\n";
	std::cout << "������������� ��������� ��������� �����, ��� �������� �� �������:\n\n";
	std::cout << " 0 | 1 | 2\n";
	std::cout << " ---------\n";
	std::cout << " 3 | 4 | 5\n";
	std::cout << " ---------\n";
	std::cout << " 6 | 7 | 8\n\n";
	std::cout << "�����������, �������. ����� ��� - ��� ��������.\n\n";
}

char AskYesNo(std::string question)
{
	char response;
	do
	{
		std::cout << question << " (y/n): ";
		std::cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}

int AskNumber(std::string question, int hight, int low = 0)
{
	int number;
	do
	{
		std::cout << question << " (" << low << " - " << hight << "): ";
		std::cin >> number;
	} while (number > hight || number < low);
	return number;
}

char HumanPiece()
{
	char go_first = AskYesNo("�� ������ ������ ������?");
	if (go_first == 'y')
	{
		std::cout << "\n����� ������ ������ ���. ���� ��� �����������.\n";
			return X;
	}
	else
	{
	std::cout << "\n���� ��������� �������� ���� � ������ ... � ����� ������\n";
	return O;
	}
}

char Opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}

void DisplayBoard(const std::vector<char>& board)
{
	std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	std::cout << "\n\t" << "---------";
	std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	std::cout << "\n\t" << "---------";
	std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	std::cout << "\n\n";
}

char Winner(const std::vector<char>& board)
{
	// ��� ��������� ���������� ����
	const int WINNING_ROWS[8][3] = { {0, 1, 2},
									 {3, 4, 5},
									 {6, 7, 8},
									 {0, 3, 6},
									 {1, 4, 7},
									 {2, 5, 8},
									 {0, 4, 8},
									 {2, 4, 6} };
	const int TOTAL_ROWS = 8;
	// ���� � ����� �� ���������� ����� ��� ������������ ��� ����������  �������� 
	// (������ ��� �� ����� EMPTY), �� ���������� �����������
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}
	// ��������� ���������� �� �����������, ��������� �� ��������� �� �����
	// (�������� �� �� ���� ������ ������)
	if (std::count(board.begin(), board.end(), EMPTY) == 0)
		return TIE;
	// ��������� ���������� �� �����������, �� � ����� ��� �� ����������
	// ���� ������������
	return NO_ONE;
}
inline bool IsLegal(int move, const std::vector<char>& board)
{
	return (board[move] == EMPTY);
}

int HumanMove(const std::vector<char>& board, char human)
{
	int move = AskNumber("���� �������!", (board.size() - 1));
	while (!IsLegal(move, board))
	{
		std::cout << "\n���� ������� ��� �����, ������ �������.\n";
		move = AskNumber("���� �� �������?", (board.size() - 1));
	}
	std::cout << "������...\n";
	return move;
}

int ComputerMove(std::vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	// ���� ��������� ����� �������� ��������� �����, �� �� ������ ���
	while (!found && move < board.size())
	{
		if (IsLegal(move, board))
		{
			board[move] = computer;
			found = Winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}
	// �����, ���� ������� ����� �������� ��������� �����, ����������� ���� ���
	if (!found)
	{
		move = 0;
		char human = Opponent(computer);
		while (!found && move < board.size())
		{
		if (IsLegal(move, board))
		{
			board[move] = human;
			found = Winner(board) == human;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
		}
	}
	// ����� ������ ��������� ����� ����������� ��������� ������
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		// ������� ����������� ��������� ������
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (IsLegal(move, board))
			{
				found = true;
			}
			++i;
		}
	}
	std::cout << "� ������ ���� � ������ ����� " << move << std::endl;
	return move;
}

void AnnounceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		std::cout << "��� � � ������������, �������. � �������� ��� ��� �������,\n";
		std::cout << "��� ���������� ����������� ����� �� ���� ����������.\n";
	}
	else if (winner == human)
	{
		std::cout << winner << "�� �������!\n";
		std::cout << "���. ���! ����� �� ����� ����! �����-�� ������� �� ������� ����, �������.\n";
		std::cout << "�� ������ �������! �, ���������, ��� ������� � ����!\n";
	}
	else
	{
		std::cout << "��� �����.\n";
		std::cout << "���� ����� �������, �������, � ���-�� ��������� ������� �� ���� ������.\n";
		std::cout << "��������... ��� ��� ������, ���� �� �����-���� ����������.\n";
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int move;
	const int NUM_SQUARES = 9;
	std::vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = HumanPiece();
	char computer = Opponent(human);
	char turn = X;
	DisplayBoard(board);
	while (Winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = HumanMove(board, human);
				board[move] = human;
		}
		else
		{
			move = ComputerMove(board, computer);
			board[move] = computer;
		}
		DisplayBoard(board);
		turn = Opponent(turn);
	}
	AnnounceWinner(Winner(board), computer, human);
	return 0;
}