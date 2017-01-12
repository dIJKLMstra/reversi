#include<iostream>
#include<fstream>
#include<memory>
using namespace std;
int x,y,step = 0;
int chessboard[20][20] = {};
bool black[20][20] = { false }, white[20][20] = { false };
bool finish = false;
void menu()   //主菜单
{   
	int i, j;
	int ceil= 2,floor=2;
	cout << "上面可能会有无关紧要的字↑↑↑" << endl;
	cout << "●●●                                       ○○○" << endl;
	while (ceil--)
	cout << "●                                               ○"<<endl;
	cout << "                     黑白棋菜单" << endl;
	cout << "        请选择" << endl;
	cout << "         1.新游戏" <<"                   ";
	cout << "2.存盘" << endl;

	cout << "         3.读盘" << "                     ";
	cout << "4.结束" << endl;
	while (floor--)
		cout << "○                                               ●" << endl;
	cout << "○○○                                       ●●●" << endl;
	cin >> i;
	switch (i)
	{
	case 1:
	{
			  memset(black, false, 400 * sizeof(black[0][0]));
			  memset(white, false, 400 * sizeof(white[0][0]));
			  black[7][7] = black[9][9] = true;
			  white[7][9] = white[9][7] = true;
			  break;
	}
	case 2:
	{
			  ofstream fout("reversi.txt");
			  for (i = 0; i < 17; i++)
			  {
				  for (j = 0; j < 17; j++)
					  fout << black[i][j] << " ";
				  fout << endl;
			  }
			  fout << endl ;
			  for (i = 0; i < 17; i++)
			  {
				  for (j = 0; j < 17; j++)
					  fout << white[i][j] << " ";
				  fout << endl;
			  }
			  fout << step - 1;
			  fout.close();
			  system("cls");
			  cout << "存好了(>▽<) ~~~" << endl;
			  menu();
			  break;
	}
	case 3:
	{
			  ifstream fin("reversi.txt");
			  for (i = 0; i < 17;i++)
			  for (j = 0; j < 17; j++)
				  fin >> black[i][j];
			  for (i = 0; i < 17; i++)
			  for (j = 0; j < 17; j++)
				  fin >> white[i][j];
			  fin >> step;
			  fin.close();
			  break;
	}
	case 4:
	{
			  finish = true;
			  cout << "欢迎再来玩~" << endl;
			  system("pause");
			  break;
	}
	default:
	{
			   system("cls");
			   cout << "你好像选错了吧" << endl;
			   menu();
			   break;
	}
		return;
	}
}
void board()   //棋盘布局
{
	int i, j;
	chessboard[0][0] = 1; chessboard[0][16] = 2; chessboard[16][0] = 3; chessboard[16][16] = 4;
	for (i = 0; i < 17;i++)
	for (j = 0; j < 17; j++)
	{
			if (i % 2 == 0 && j % 2 == 1)
			chessboard[i][j] = 5;
			if (i % 2 == 1 && j % 2 == 0)
			chessboard[i][j] = 6;
			if (i == 0 && j != 0 && j != 16 && j % 2 == 0)
			chessboard[i][j] = 7;
			if (j == 0 && i != 0 && i != 16 && i % 2 == 0)
			chessboard[i][j] = 8;
			if (i == 16 && j != 0 && j != 16 && j % 2 == 0)
			chessboard[i][j] = 9;
		if (j==16 && i != 0 && i != 16 && i % 2 == 0)
			chessboard[i][j] = 10;	
		if (i != 0 && i != 16 && j != 0 && j != 16 && i % 2 == 0 && j % 2 == 0)
			chessboard[i][j] = 11;
	}
	return;
	//cout << "┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;
	//for (i = 0; i < 7; i++)
	//{
	//	cout << "│  │  │  │  │  │  │  │  │" << endl;
		//cout << "├─┼─┼─┼─┼─┼─┼─┼─┤" << endl;
	//}
	//cout << "│  │  │  │  │  │  │  │  │" << endl;
	//cout << "└─┴─┴─┴─┴─┴─┴─┴─┘" << endl;
}
bool turnover(int a, int b, bool po[20][20], bool pa[20][20]) //判断下一个棋子能落的位置  如果可以下 同时翻转棋子
{
	int i, j;
	bool turn = false;
	if (pa[2 * a - 1][2 * b - 1]||po[2 * a - 1][2 * b - 1])
		return false;
	for (i = -7; i < 8; i++)
	{
		if (po[2 * a - 1][2 * (b + i) - 1] == true && b + i > 0 && b + i < 9)   //判断一行能否翻转
		{
			if (i > 0)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (pa[2 * a - 1][2 * (b + j) - 1])   //判断中间的棋子是否全为同一颜色
					{
						if (j == 1)
						{
							for (j = i - 1; j > 0; j--)         //如果中间的均为同一种颜色就把中间的棋子全改变颜色
							{
								pa[2 * a - 1][2 * (b + j) - 1] = false;
								po[2 * a - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
			else
			{
				for (j = i + 1; j < 0; j++)
				{
					if (pa[2 * a - 1][2 * (b + j) - 1])
					{
						if (j == -1)
						{
							for (j = i + 1; j < 0; j++)
							{
								pa[2 * a - 1][2 * (b + j) - 1] = false;
								po[2 * a - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
		}
		if (po[2 * (a + i) - 1][2 * b - 1] == true && a + i > 0 && a + i < 9)   //判断一列能否翻转
		{
			if (i > 0)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (pa[2 * (a + j) - 1][2 * b - 1])
					{
						if (j == 1)
						{
							for (j = i - 1; j > 0; j--)
							{
								pa[2 * (a + j) - 1][2 * b - 1] = false;
								po[2 * (a + j) - 1][2 * b - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
			else
			{
				for (j = i + 1; j < 0; j++)
				{
					if (pa[2 * (a + j) - 1][2 * b - 1])
					{
						if (j == -1)
						{
							for (j = i + 1; j < 0; j++)
							{
								pa[2 * (a + j) - 1][2 * b - 1] = false;
								po[2 * (a + j) - 1][2 * b - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
		}
		if (po[2 * (a - i) - 1][2 * (b + i) - 1] == true && a - i > 0 && a - i < 9 && b + i > 0 && b + i < 9)   //判断斜左对角线上能否翻转
		{
			if (i > 0)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (pa[2 * (a - j) - 1][2 * (b + j) - 1])
					{
						if (j == 1)
						{
							for (j = i - 1; j > 0; j--)
							{
								pa[2 * (a - j) - 1][2 * (b + j) - 1] = false;
								po[2 * (a - j) - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
			else
			{
				for (j = i + 1; j < 0; j++)
				{
					if (pa[2 * (a - j) - 1][2 * (b + j) - 1])
					{
						if (j == -1)
						{
							for (j = i + 1; j < 0; j++)
							{
								pa[2 * (a - j) - 1][2 * (b + j) - 1] = false;
								po[2 * (a - j) - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
		}
		if (po[2 * (a + i) - 1][2 * (b + i) - 1] == true && a + i > 0 && a + i < 9 && b + i > 0 && b + i < 9)   //判断斜右对角线上能否翻转
		{
			if (i > 0)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (pa[2 * (a + j) - 1][2 * (b + j) - 1])
					{
						if (j == 1)
						{
							for (j = i - 1; j > 0; j--)
							{
								pa[2 * (a + j) - 1][2 * (b + j) - 1] = false;
								po[2 * (a + j) - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
			else
			{
				for (j = i + 1; j < 0; j++)
				{
					if (pa[2 * (a + j) - 1][2 * (b + j) - 1])
					{
						if (j == -1)
						{
							for (j = i + 1; j < 0; j++)
							{
								pa[2 * (a + j) - 1][2 * (b + j) - 1] = false;
								po[2 * (a + j) - 1][2 * (b + j) - 1] = true;
								po[2 * a - 1][2 * b - 1] = true;
								turn = true;
							}
						}
					}
					else
						break;
				}
			}
		}
	}
	return turn;
}
void putchess()    //输入黑棋落子
{
	bool turn[20][20] = { false },copyb[20][20],copyw[20][20];
	int able = 0;
	for (x = 1; x < 9;x++)
	for (y = 1; y < 9; y++)
	{
		memcpy(copyb, black, 400 * sizeof(black[0][0]));
		memcpy(copyw, white, 400 * sizeof(white[0][0]));
		turn[x][y] = turnover(x, y, copyb, copyw);
		if (turn[x][y]) able++;
	}
	if (able == 0)
	{
		cout << "这轮你没有地方走了" << endl;
		system("pause");
		return;
	}
	cin.clear();   //如果不小心读了字符
	cin.sync();
	cin >> x >> y;
	{
		if (x == 0 && y == 0)
		{
			system("cls");
			menu();
		}
		else
		{
			if (black[2 * x - 1][2 * y - 1] == false && x > 0 && x < 9 && y > 0 && y < 9)
				turn[x][y] = turnover(x, y, black, white);

			if (turn[x][y])
			{
				black[2 * x - 1][2 * y - 1] = true;
				return;
			}
			if (!turn[x][y] || x > 8 || x < 0 || y > 8 || y < 0)
			{
				cout << "这里并不能下。。。  请重新输入坐标：" << endl;
				putchess();
			}
		}
	}
		return;
}
int getvalue(int m,int n,char color,bool (*b)[20],bool (*w)[20],int depth)   //估值函数
{
	int i, j;
	if (color == 'b')
	{
		int t, bestvalue = 0;
		bool copyb[20][20], copyw[20][20];
		memcpy(copyb, b, 400 * sizeof(b[0][0]));  //先复制棋盘 再模拟
		memcpy(copyw, w, 400 * sizeof(w[0][0]));
		bool turn = turnover(m, n, copyb, copyw);
		if (!turn)  return 0;
		if (depth == 0)
		{
			int value = 0;
			for (i = 0; i < 17;i++)
			for (j = 0; j < 17;j++)
			{
				if (copyb[i][j])   //对黑棋局势的估值
				{
					if (step < 50)
					{
						if ((i == 1 && j == 1) || (i == 1 && j == 15) || (i == 15 && j == 1) || (i == 15 && j == 15))
							value += 109;
						else if ((i == 1 && j != 1 && j != 3 && j != 13 && j != 15) || (i == 15 && j != 1 && j != 3 && j != 13 && j != 15) || (j == 1 && i != 1 && i != 3 && i != 13 && i != 15) || (j == 15 && i != 1 && i != 3 && i != 13 && i != 15))
							value += 40;
						else if ((i == j&&i != 1 && i != 3 && i != 13 && i != 15) || (i + j == 16 && i != 1 && i != 3 && i != 13 && i != 15))
							value += 20;
						else if ((i == 3 && j == 3) || (i == 3 && j == 13) || (i == 13 && j == 3) || (i == 13 && j == 13) || (i == 1 && (j == 3 || j == 13)) || ((i == 3 || i == 13) && j == 1) || (i == 15 && (j == 3 || j == 13)) || (j == 15 && (i == 3 || i == 13)))
							value -= 50;
						else
							value += 10;
					}
					else
					{
						if ((i == 1 && j == 1) || (i == 1 && j == 15) || (i == 15 && j == 1) || (i == 15 && j == 15))
							value += 10;
						else if ((i == 1 && j != 1 && j != 3 && j != 13 && j != 15) || (i == 15 && j != 1 && j != 3 && j != 13 && j != 15) || (j == 1 && i != 1 && i != 3 && i != 13 && i != 15) || (j == 15 && i != 1 && i != 3 && i != 13 && i != 15))
							value += 5;
						else if ((i == j&&i != 1 && i != 3 && i != 13 && i != 15) || (i + j == 16 && i != 1 && i != 3 && i != 13 && i != 15))
							value += 3;
						else if ((i == 3 && j == 3) || (i == 3 && j == 13) || (i == 13 && j == 3) || (i == 13 && j == 13) || (i == 1 && (j == 3 || j == 13)) || ((i == 3 || i == 13) && j == 1) || (i == 15 && (j == 3 || j == 13)) || (j == 15 && (i == 3 || i == 13)))
							value -= 5;
						else
							value += 1;
					}
				}
			}
			return value;
		}
		else
		{
			for (i = 1; i < 9; i++)
			for (j = 1; j < 9; j++)
			{
				t = getvalue(i, j, 'w', copyb, copyw, depth - 1);
				if (t > bestvalue)
					bestvalue = t;	
				memcpy(copyb, b, 400 * sizeof(b[0][0]));
				memcpy(copyw, w, 400 * sizeof(w[0][0]));
				turnover(m,n,copyb, copyw);
			}
			return bestvalue;
		}
	}
	else
		{
			int t, bestvalue = 1000;
			bool copyb[20][20], copyw[20][20];
			memcpy(copyb, b, 400 * sizeof(b[0][0]));  
			memcpy(copyw, w, 400 * sizeof(w[0][0]));
			bool turn = turnover(m, n, copyw, copyb);
			if (!turn) return 0;
			if (depth == 0)
			{
				int value = 0;
				for (i = 0; i < 17; i++)
				for (j = 0; j < 17; j++)
				{
					if (copyw[i][j])  //对白棋局势的估值
					{
						if (step < 50)
						{
							if ((i == 1 && j == 1) || (i == 1 && j == 15) || (i == 15 && j == 1) || (i == 15 && j == 15))
								value += 109;
							else if ((i == 1 && j != 1 && j != 3 && j != 13 && j != 15) || (i == 15 && j != 1 && j != 3 && j != 13 && j != 15) || (j == 1 && i != 1 && i != 3 && i != 13 && i != 15) || (j == 15 && i != 1 && i != 3 && i != 13 && i != 15))
								value += 40;
							else if ((i == j&&i != 1 && i != 3 && i != 13 && i != 15) || (i + j == 16 && i != 1 && i != 3 && i != 13 && i != 15))
								value += 20;
							else if ((i == 3 && j == 3) || (i == 3 && j == 13) || (i == 13 && j == 3) || (i == 13 && j == 13) || (i == 1 && (j == 3 || j == 13)) || ((i == 3 || i == 13) && j == 1) || (i == 15 && (j == 3 || j == 13)) || (j == 15 && (i == 3 || i == 13)))
								value -= 50;
							else
								value += 10;
						}
						else
						{
							if ((i == 1 && j == 1) || (i == 1 && j == 15) || (i == 15 && j == 1) || (i == 15 && j == 15))
								value += 10;
							else if ((i == 1 && j != 1 && j != 3 && j != 13 && j != 15) || (i == 15 && j != 1 && j != 3 && j != 13 && j != 15) || (j == 1 && i != 1 && i != 3 && i != 13 && i != 15) || (j == 15 && i != 1 && i != 3 && i != 13 && i != 15))
								value += 5;
							else if ((i == j&&i != 1 && i != 3 && i != 13 && i != 15) || (i + j == 16 && i != 1 && i != 3 && i != 13 && i != 15))
								value += 3;
							else if ((i == 3 && j == 3) || (i == 3 && j == 13) || (i == 13 && j == 3) || (i == 13 && j == 13) || (i == 1 && (j == 3 || j == 13)) || ((i == 3 || i == 13) && j == 1) || (i == 15 && (j == 3 || j == 13)) || (j == 15 && (i == 3 || i == 13)))
								value -= 5;
							else
								value += 1;
						}
					}
				}
				return value;
			}
			else
			{
				for (i = 1; i < 9; i++)
				for (j = 1; j < 9; j++)
				{
					t = getvalue(i, j, 'b', copyb, copyw, depth - 1);
					if (t < bestvalue && t != 0)     
						bestvalue = t;
					memcpy(copyb, b, 400 * sizeof(b[0][0]));
					memcpy(copyw, w, 400 * sizeof(w[0][0]));
					turnover(m, n, copyw, copyb);
				}
				return bestvalue;
			}
	}
}
void whiterobo()   //AI
{
	if (finish)
		return;
	int i, j;
	int t, best = 0;
	bool copyb[20][20] = {}, copyw[20][20] = {};
	memcpy(copyb, black, 400 * sizeof(black[0][0]));  //把棋盘复制一遍
	memcpy(copyw, white, 400 * sizeof(white[0][0]));
	for (i = 1; i < 9;i++)
	for (j = 1; j < 9;j++)
	{
		t = getvalue(i, j, 'w', copyb, copyw, 2);
		if (t > best)
			best = t;
	}
	for (i = 1; i < 9; i++)
	for (j = 1; j < 9; j++)
	{
		if (best == 0)
		{
			cout << "电脑这轮无路可走" << endl;
			return;
		}
		if (getvalue(i, j, 'w',copyb, copyw, 2) == best && !finish)
		{
			turnover(i, j, white, black);
			cout << "这轮电脑下的是" << i << " " << j << endl;
			i = j = 9;
		}
	}
	return;
}
void outputboard()   //输出棋盘棋子
{
	if (finish)      //考虑选结束的情况
	{
		cout << "再见 欢迎再来玩~" << endl;
		return;
	}
	int i, j,bchess = 0,wchess = 0;
	step++;
	cout << "     ";
	for (i = 1; i < 9; i++)
		cout<< i <<"   ";
	cout << endl;
	for (i = 0; i < 17;i++)
	for (j = 0; j < 17; j++)
	{
		if (black[i][j])
			bchess++;
		if (white[i][j])
			wchess++;
	}
	for (i = 0; i < 17; i++)
	{
		if (i % 2 == 1)
			cout << " " << (i + 1) / 2 << " ";
		else
			cout << "   ";
		for (j = 0; j < 17; j++)
		{
			if (black[i][j])
			{
				cout << "●";
				continue;
			}
			if (white[i][j])
			{
				cout << "○"; 
				continue;
			}
			switch (chessboard[i][j])
			{
			case 1:cout << "┌"; break;
			case 2:cout << "┐"; break;
			case 3:cout << "└"; break;
			case 4:cout << "┘"; break;
			case 5:cout << "─"; break;
			case 6:cout << "│"; break;
			case 7:cout << "┬"; break;
			case 8:cout << "├"; break;
			case 9:cout << "┴"; break;
			case 10:cout << "┤"; break;
			case 11:cout << "┼"; break;
			default:
			{
			if (black[i][j - 1])
				continue;
			else
				cout << "  "; 
			break;
			}
			}	
		}
		if (i == 7)
					cout << "   ●   X   " << bchess;
				if (i == 9)
					cout << "   ○   X   " << wchess;
				if (i == 11)
					cout << " Total  X   " << bchess + wchess;
		cout << endl;
	}
	if ((bchess + wchess == 64 && bchess > wchess)||wchess==0)   //如果最后黑子多于白子 或者白子被吃光 玩家胜
	{
		cout << "你赢了！ 你战胜了AI君！！" << endl;
		finish = true;
		system("pause");
	}
	else if ((bchess + wchess == 64 && bchess < wchess)||bchess==0)  //如果白子多于黑子 或者黑子被吃光 电脑胜
	{
		cout << "很遗憾 你输了 没关系  欢迎继续挑战↖(^ω^)↗" << endl;
		finish = true;
		system("pause");
	}
	else if (bchess + wchess == 64 && bchess == wchess)  //如果子数相等 则为平局
	{
		cout << "draw match!  再来一局不？" << endl;
		finish = true;
		system("pause");
	}
	else
	{
		if (step % 2 == 1)
		{
			cout << "输入0 0返回菜单" << endl;
			cout << "请输入坐标：" << endl;
		}
		else
			system("pause");
	}
	return;
}
int main()
{
	menu();
	board();
	system("cls");
	//outputboard();
	while (!finish)
	{	
		outputboard();
		putchess();
		system("cls");
		outputboard();
		system("cls");
		whiterobo();
		//outputboard();
	}
	system("pause");
	return 0; 
}