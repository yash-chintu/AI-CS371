#include <bits/stdc++.h>
using namespace std;

char board[3][3] = {{'-', '-', '-'},
                    {'-', '-', '-'},
                    {'-', '-', '-'}};

int cnt = 0;

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
}

void printBoard()
{
    cout << "========" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========" << endl;
}

bool areMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
                return true;
        }
    }
    return false;
}

int check(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'X')
                return 1;
            else if (board[i][0] == 'O')
                return -1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == 'X')
                return 1;
            else if (board[0][i] == 'O')
                return -1;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
            return 1;
        else if (board[0][0] == 'O')
            return -1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[1][1] == 'X')
            return 1;
        else if (board[1][1] == 'O')
            return -1;
    }
    return 0;
}

int minimax(char b[3][3], bool isMax)
{

    int score = check(b);

    if (score == 1)
        return score;
    if (score == -1)
        return score;
    if (!areMovesLeft(b))
        return 0;

    if (isMax)
    {
        int val = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == '-')
                {
                    b[i][j] = 'X';
                    cnt++;
                    val = max(val, minimax(b, !isMax));
                    b[i][j] = '-';
                }
            }
        }
        return val;
    }
    else
    {
        int val = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (b[i][j] == '-')
                {
                    b[i][j] = 'O';
                    cnt++;
                    val = min(val, minimax(b, !isMax));
                    b[i][j] = '-';
                }
            }
        }
        return val;
    }
}

void bestMove()
{
    cnt = 0;
    int val = INT_MIN;
    pair<int, int> move = {-1, -1};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                board[i][j] = 'X';
                cnt++;
                int temp = minimax(board, false);
                board[i][j] = '-';
                if (temp > val)
                {
                    move.first = i, move.second = j;
                    val = temp;
                }
            }
        }
    }
    board[move.first][move.second] = 'X';
    cout << "Number of states visited : " << cnt << endl;
}

int main()
{

    cout << "Tic-Tac-Toe Game :" << endl;
    int m, n;
    while (1)
    {
        resetBoard();
        for (int i = 0; i < 9; i++)
        {
            if (i % 2)
            {
                cout << "enter your move ( row number seperated by column number , indexing from 0)" << endl;
                cin >> m >> n;
                if (board[m][n] != '-')
                {
                    cout << "invalid Move , Restarting the game" << endl;
                    break;
                }
                board[m][n] = 'O';
                cout << "Your Move" << endl;
                printBoard();
                if (check(board) == -1)
                {
                    cout << "You Won" << endl;
                    break;
                }
            }
            else
            {
                cout << "Computers Move" << endl;
                bestMove();
                printBoard();
                if (check(board) == 1)
                {
                    cout << "You Lost" << endl;
                    break;
                }
            }
        }
        if (!check(board))
            cout << "Game Drawn" << endl;
        cout << "Enter 0 to stop playing , 1 to play again" << endl;
        cin >> m;
        if (!m)
            break;
    }

    return 0;
}