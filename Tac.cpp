#include <iostream>
#include <vector>
using namespace std;

void createBoard(vector<vector<char>> &b)
{
    b.resize(3, vector<char>(3, '.'));
}

void displayBoard(vector<vector<char>> &b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isWinner(vector<vector<char>> &b, char p)
{
    for (int i = 0; i < 3; i++)
    {
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p)
            return true;

        if (b[0][i] == p && b[1][i] == p && b[2][i] == p)
            return true;
    }

    if (b[0][0] == p && b[1][1] == p && b[2][2] == p)
        return true;

    if (b[0][2] == p && b[1][1] == p && b[2][0] == p)
        return true;

    return false;
}
bool movesLeft(vector<vector<char>> &b)
{
    for (auto &row : b)
        for (auto c : row)
            if (c == '.')
                return true;

    return false;
}
int evaluate(vector<vector<char>> &b)
{
    if (isWinner(b, 'O'))
        return 10;
    if (isWinner(b, 'X'))
        return -10;
    return 0;
}
int minimax(vector<vector<char>> &b, bool isAI)
{
    int score = evaluate(b);

    if (score == 10 || score == -10)
        return score;

    if (!movesLeft(b))
        return 0;

    if (isAI)
    {
        int best = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == '.')
                {
                    b[i][j] = 'O';
                    best = max(best, minimax(b, false));
                    b[i][j] = '.';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == '.')
                {
                    b[i][j] = 'X';
                    best = min(best, minimax(b, true));
                    b[i][j] = '.';
                }
            }
        }
        return best;
    }
}

void aiMove(vector<vector<char>> &b)
{
    int bestScore = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (b[i][j] == '.')
            {
                b[i][j] = 'O';

                int score = minimax(b, false);

                b[i][j] = '.';

                if (score > bestScore)
                {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    b[bestRow][bestCol] = 'O';
}

void startGame(vector<vector<char>> &board)
{
    createBoard(board);

    while (true)
    {
        displayBoard(board);
        int pos, row, col;

        while (true)
        {
            cout << "Your Turn\n";
            cout << "Enter position (1-9): ";
            cin >> pos;

            if (pos < 1 || pos > 9)
            {
                cout << "Invalid move\n";
                continue;
            }

            row = (pos - 1) / 3;
            col = (pos - 1) % 3;

            if (board[row][col] != '.')
            {
                cout << "Already taken\n";
                continue;
            }

            break;
        }

        board[row][col] = 'X';
        displayBoard(board);
        if (isWinner(board, 'X'))
        {
            displayBoard(board);
            cout << "You Win!\n";
            break;
        }

        if (!movesLeft(board))
        {
            displayBoard(board);
            cout << "Tie!\n";
            break;
        }

        cout << "My Turn:\n";
        aiMove(board);

        if (isWinner(board, 'O'))
        {
            displayBoard(board);
            cout << "AI Wins!\n";
            break;
        }

        if (!movesLeft(board))
        {
            displayBoard(board);
            cout << "Tie!\n";
            break;
        }
    }
}
int main()
{
    vector<vector<char>> board;
    startGame(board);
}