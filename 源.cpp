#include<iostream>
#include<fstream>
#include<memory>
using namespace std;
int x,y,step = 0;
int chessboard[20][20] = {};
bool black[20][20] = { false }, white[20][20] = { false };
bool finish = false;
void menu()   //���˵�
{   
	int i, j;
	int ceil= 2,floor=2;
	cout << "������ܻ����޹ؽ�Ҫ���֡�����" << endl;
	cout << "����                                       ����" << endl;
	while (ceil--)
	cout << "��                                               ��"<<endl;
	cout << "                     �ڰ���˵�" << endl;
	cout << "        ��ѡ��" << endl;
	cout << "         1.����Ϸ" <<"                   ";
	cout << "2.����" << endl;

	cout << "         3.����" << "                     ";
	cout << "4.����" << endl;
	while (floor--)
		cout << "��                                               ��" << endl;
	cout << "����                                       ����" << endl;
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
			  cout << "�����(>��<) ~~~" << endl;
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
			  cout << "��ӭ������~" << endl;
			  system("pause");
			  break;
	}
	default:
	{
			   system("cls");
			   cout << "�����ѡ���˰�" << endl;
			   menu();
			   break;
	}
		return;
	}
}
void board()   //���̲���
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
	//cout << "�����Щ��Щ��Щ��Щ��Щ��Щ��Щ���" << endl;
	//for (i = 0; i < 7; i++)
	//{
	//	cout << "��  ��  ��  ��  ��  ��  ��  ��  ��" << endl;
		//cout << "�����੤�੤�੤�੤�੤�੤�੤��" << endl;
	//}
	//cout << "��  ��  ��  ��  ��  ��  ��  ��  ��" << endl;
	//cout << "�����ة��ة��ة��ة��ة��ة��ة���" << endl;
}
bool turnover(int a, int b, bool po[20][20], bool pa[20][20]) //�ж���һ�����������λ��  ��������� ͬʱ��ת����
{
	int i, j;
	bool turn = false;
	if (pa[2 * a - 1][2 * b - 1]||po[2 * a - 1][2 * b - 1])
		return false;
	for (i = -7; i < 8; i++)
	{
		if (po[2 * a - 1][2 * (b + i) - 1] == true && b + i > 0 && b + i < 9)   //�ж�һ���ܷ�ת
		{
			if (i > 0)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (pa[2 * a - 1][2 * (b + j) - 1])   //�ж��м�������Ƿ�ȫΪͬһ��ɫ
					{
						if (j == 1)
						{
							for (j = i - 1; j > 0; j--)         //����м�ľ�Ϊͬһ����ɫ�Ͱ��м������ȫ�ı���ɫ
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
		if (po[2 * (a + i) - 1][2 * b - 1] == true && a + i > 0 && a + i < 9)   //�ж�һ���ܷ�ת
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
		if (po[2 * (a - i) - 1][2 * (b + i) - 1] == true && a - i > 0 && a - i < 9 && b + i > 0 && b + i < 9)   //�ж�б��Խ������ܷ�ת
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
		if (po[2 * (a + i) - 1][2 * (b + i) - 1] == true && a + i > 0 && a + i < 9 && b + i > 0 && b + i < 9)   //�ж�б�ҶԽ������ܷ�ת
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
void putchess()    //�����������
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
		cout << "������û�еط�����" << endl;
		system("pause");
		return;
	}
	cin.clear();   //�����С�Ķ����ַ�
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
				cout << "���ﲢ�����¡�����  �������������꣺" << endl;
				putchess();
			}
		}
	}
		return;
}
int getvalue(int m,int n,char color,bool (*b)[20],bool (*w)[20],int depth)   //��ֵ����
{
	int i, j;
	if (color == 'b')
	{
		int t, bestvalue = 0;
		bool copyb[20][20], copyw[20][20];
		memcpy(copyb, b, 400 * sizeof(b[0][0]));  //�ȸ������� ��ģ��
		memcpy(copyw, w, 400 * sizeof(w[0][0]));
		bool turn = turnover(m, n, copyb, copyw);
		if (!turn)  return 0;
		if (depth == 0)
		{
			int value = 0;
			for (i = 0; i < 17;i++)
			for (j = 0; j < 17;j++)
			{
				if (copyb[i][j])   //�Ժ�����ƵĹ�ֵ
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
					if (copyw[i][j])  //�԰�����ƵĹ�ֵ
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
	memcpy(copyb, black, 400 * sizeof(black[0][0]));  //�����̸���һ��
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
			cout << "����������·����" << endl;
			return;
		}
		if (getvalue(i, j, 'w',copyb, copyw, 2) == best && !finish)
		{
			turnover(i, j, white, black);
			cout << "���ֵ����µ���" << i << " " << j << endl;
			i = j = 9;
		}
	}
	return;
}
void outputboard()   //�����������
{
	if (finish)      //����ѡ���������
	{
		cout << "�ټ� ��ӭ������~" << endl;
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
				cout << "��";
				continue;
			}
			if (white[i][j])
			{
				cout << "��"; 
				continue;
			}
			switch (chessboard[i][j])
			{
			case 1:cout << "��"; break;
			case 2:cout << "��"; break;
			case 3:cout << "��"; break;
			case 4:cout << "��"; break;
			case 5:cout << "��"; break;
			case 6:cout << "��"; break;
			case 7:cout << "��"; break;
			case 8:cout << "��"; break;
			case 9:cout << "��"; break;
			case 10:cout << "��"; break;
			case 11:cout << "��"; break;
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
					cout << "   ��   X   " << bchess;
				if (i == 9)
					cout << "   ��   X   " << wchess;
				if (i == 11)
					cout << " Total  X   " << bchess + wchess;
		cout << endl;
	}
	if ((bchess + wchess == 64 && bchess > wchess)||wchess==0)   //��������Ӷ��ڰ��� ���߰��ӱ��Թ� ���ʤ
	{
		cout << "��Ӯ�ˣ� ��սʤ��AI������" << endl;
		finish = true;
		system("pause");
	}
	else if ((bchess + wchess == 64 && bchess < wchess)||bchess==0)  //������Ӷ��ں��� ���ߺ��ӱ��Թ� ����ʤ
	{
		cout << "���ź� ������ û��ϵ  ��ӭ������ս�I(^��^)�J" << endl;
		finish = true;
		system("pause");
	}
	else if (bchess + wchess == 64 && bchess == wchess)  //���������� ��Ϊƽ��
	{
		cout << "draw match!  ����һ�ֲ���" << endl;
		finish = true;
		system("pause");
	}
	else
	{
		if (step % 2 == 1)
		{
			cout << "����0 0���ز˵�" << endl;
			cout << "���������꣺" << endl;
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