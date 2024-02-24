void start(int x)
{
    system("Color B5");
    switch (x)
    {
    case 0:
        int ss;
        system("cls");

        cout << "         HOW TO PLAY:" << endl << "Use your arrow keys to move the tiles and they will merge into one!" << endl << "W:up  S : down A : left  D : right  N : new game  X : exit" << endl << "    Add them up to reach 2048!" << endl;
        cout << "Press any key to play" << endl;
        _getch();
        system("cls");
        break;
    case 1:
        system("cls");
        break;
    }

}
void startingconsole()
{
    system("Color B4");
    cout << "      LET'S PLAY 2048" << endl << "Press anywhere to Continue"
        << endl;
    _getch();
    system("cls");
    int step1;
    system("Color B2");
    cout << "PRESS 1 OR 0" << endl << "0: INSTRUCTIONS" << endl << "1: START" << endl;
    cin >> step1;
    start(step1);
}


void contgame(int gr[4][4])
{
    system("Color B3");
    int flag = 1;


    while (flag)
    {
        srand(time(0));
        int i = rand() % 4;
        int j = rand() % 4;
        int l = rand() % 3 + 1;


        if (gr[i][j] == 0)
        {
            if (l % 2 == 0)
            {
                gr[i][j] = l;
                flag = 0;
                break;
            }
            else {
                gr[i][j] = l + 1;
                flag = 0;
                break;
            }
        }
        else
        {
            continue;
        }
    }
    cout << "  ___________________________________" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << " | ";
            if (gr[i][j] == 0)
            {
                cout << setw(4) << " " << "  ";
            }
            else
            {
                cout << setw(4) << gr[i][j] << "  ";
            }
        }
        cout << " |" << endl;
        cout << " |________|________|________|________|" << endl;
    }
    cout << " _________________________" << endl << endl;
}
// game beginning


void down(int gr[4][4])
{
    int i;
    for (int j = 0; j < 4; j++)
    {
        i = 2;
        while (true)
        {
            while (gr[i][j] == 0)
            {
                if (i == -1)
                    break;
                i--;
            }
            if (i == -1)
                break;
            while (i < 4 - 1 && (gr[i + 1][j] == 0 || gr[i][j] == gr[i +
                1][j]))
            {
                if (gr[i][j] == gr[i + 1][j])
                {
                    int scor = gr[i + 1][j] + gr[i][j];

                    score = score + scor;
                }
                gr[i + 1][j] += gr[i][j];
                gr[i][j] = 0;

                i++;

            }
            i--;
        }
    }
}

void up(int gr[4][4])
{
    int i;
    for (int j = 0; j < 4; j++)
    {
        i = 1;
        while (true)
        {
            while (gr[i][j] == 0)
            {
                if (i == 4)
                    break;
                i++;
            }
            if (i == 4)
                break;
            while (i > 0 && (gr[i - 1][j] == 0 || gr[i][j] == gr[i - 1][j]))
            {
                if (gr[i][j] == gr[i - 1][j])
                {
                    int scor = gr[i - 1][j] + gr[i][j];

                    score = score + scor;
                }
                gr[i - 1][j] += gr[i][j];
                gr[i][j] = 0;
                i--;

            }
            i++;
        }
    }
}

void right(int gr[4][4])
{
    int j;
    for (int i = 0; i < 4; i++)
    {
        j = 2;
        while (true)
        {
            while (gr[i][j] == 0)
            {
                if (j == -1)
                    break;
                j--;
            }
            if (j == -1)
                break;
            while (j < 4 - 1 && (gr[i][j + 1] == 0 || gr[i][j] == gr[i][j +
                1]))
            {
                if (gr[i][j] == gr[i][j + 1])
                {
                    int scor = gr[i][j + 1] + gr[i][j];

                    score = score + scor;
                }
                gr[i][j + 1] += gr[i][j];
                gr[i][j] = 0;
                j++;

            }
            j--;
        }
    }
}

void left(int gr[4][4])
{
    int j;
    for (int i = 0; i < 4; i++)
    {
        j = 1;
        while (true)
        {
            while (gr[i][j] == 0)
            {
                if (j == 4)
                    break;
                j++;
            }
            if (j == 4)
                break;
            while (j > 0 && (gr[i][j - 1] == 0 || gr[i][j] == gr[i][j - 1]))
            {
                if (gr[i][j] == gr[i][j - 1])
                {
                    int scor = gr[i][j - 1] + gr[i][j];

                    score = score + scor;
                }
                gr[i][j - 1] += gr[i][j];
                gr[i][j] = 0;
                j--;
            }
            j++;

        }
    }
}

void scorerec(int x)
{
    system("Color B3");
    cout << "          score: " << score << endl << endl;
    cout << " _________________________" << endl;
}

void startnum(int grid[][4])
{

    for (int l = 0; l < 2; l++)
    {
        int i = rand() % 4;
        int j = rand() % 4;


        grid[i][j] = 4;
    }


    for (int l = 0; l < 2; l++)
    {
        int i = rand() % 4;
        int j = rand() % 4;

        grid[i][j] = 2;
    }
    system("Color B3");
    cout << "  ___________________________________" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << " | ";
            if (grid[i][j] == 0)
            {
                cout << setw(4) << " " << "  ";
            }
            else
            {
                cout << setw(4) << grid[i][j] << "  ";
            }
        }cout << " |" << endl;
        cout << " |________|________|________|________|" << endl;
    }
    system("Color B3");
    cout << " _________________________" << endl << endl;
    cout << "          score: " << score << endl << endl;
    cout << " _________________________" << endl;
}  // second apperance

void resetgame()
{
    int grid[4][4] =
    { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
    startnum(grid);
}

void wincheck(int grid[4][4])
{
    system("Color B3");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grid[i][j] == 2048)
            {
                char x;
                system("cls");
                cout << "you won" << endl << "total score: " << score <<
                    endl;

                cout << "do u wanna play again?" << " y/n" << endl;
                cin >> x;
                system("cls");
                if (tolower(x) == 'y')
                {
                    resetgame();


                }
                else
                {
                    system("cls");
                    exit(x);
                    break;
                }
                break;
            }
        }
    }
}

int gameover(int gr[4][4])
{
    system("Color B3");
    int movepossible = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (gr[i][j] == 0 || (gr[i][j] == gr[i][j - 1] || gr[i][j] ==
                gr[i][j + 1] || gr[i][j] == gr[i - 1][j] || gr[i][j] == gr[i + 1][j]))
            {
                movepossible++;
            }
        }
    }
    if (movepossible == 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}
void arrowkeys(int grid[4][4])
{

    for (int i = 0; i < 10000; i++)
    {
        char x;
        cin >> x;


        if (toupper(x) == 'W')
        {
            system("cls");
            up(grid);
        }
        else if (toupper(x) == 'A')
        {
            system("cls");
            left(grid);
        }
        else if (toupper(x) == 'S')
        {
            system("cls");
            down(grid);
        }
        else if (toupper(x) == 'D')
        {
            system("cls");
            right(grid);
        }
        else if (toupper(x) == 'N')
        {
            system("cls");
            resetgame();
            arrowkeys(grid);
            continue;
        }
        else if (toupper(x) == 'X')
        {
            system("cls");
            exit(x);

        }
        else
        {
            continue;
        }
        contgame(grid);
        scorerec(score);
        wincheck(grid);
        if (gameover(grid))
        {
            system("Color B4");
            system("cls");
            cout << "gameover" << endl << "total score : " << score << endl;
            break;
        }
    }
}

