#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Subroku.h"

Subroku::Subroku(int size)//constructor for soduku
{
	b_size=size;
	m_size=size*size;
  m_soduku = new int*[m_size];
  m_soduku[0]= new int[m_size*m_size]{};
  for(int i=1; i<m_size; i++)
  {
    m_soduku[i]=m_soduku[i-1]+m_size;
  }
}

Subroku::~Subroku() // destructor
{
    // Dynamically delete the  we allocated earlier
    delete[] m_soduku[0];
    delete[] m_soduku;
}

void Subroku::setValue(int row, int col, int value) { m_soduku[row][col] = value; }
int& Subroku::getValue(int row, int col) { return m_soduku[row][col]; }

//overloads the subscript operator
int* Subroku::operator[](int index)
{
  return m_soduku[index];
}

//overload output operator
std::ostream& operator<<(std::ostream& output, Subroku& z)
{
  for(int i=0;i<z.m_size;i++)
  {
    for(int j=0;j<z.m_size;j++)
    {
      output<<z[i][j]<<" ";
    }
    output<<"\n";
  }
  output<<"\n";
  return output;
}

bool Subroku::checkValid(int row, int col, int num)//checks if this value inputted works
{
	return (checkRow(row, num) && checkCol(col, num) && checkBox(row-row%b_size, col-col%b_size, num)); 
}
void Subroku::createSoduku()//method to create a valid soduku puzzle
{
  removeDigits(); 
}
void Subroku::solvedSoduku()
{
  srand (time(NULL)); 
  fillDiagonal();
  fillRest(0,b_size);
}
//after whole soduku is filled some digits are removed to simulate a real soduku game
void Subroku::removeDigits()
{
  int count=0;
  char input=' ';
  std::cout<<"Enter difficulty:(e(easy),m(medium),h(hard))"<<std::endl;
  std::cin>>input;
  while(input!='e'&&input!='m'&&input!='h')
	{
    std::cout<<"Enter difficulty:(e(easy),m(medium),h(hard))"<<std::endl;
    std::cin>>input;
  }
  if(input=='e')
  {
    count=20;
  }
  else if(input=='m')
  {
    count=25;
  }
  else if(input=='h')
  {
    count=50;
  }
	while(count!=0)
	{
		int randnum=rand()%(m_size*m_size);
		int row=randnum/m_size;
		int col=randnum%m_size;
		if(col!=0&&col>=0)
    {
			col--;
    }
		if(m_soduku[row][col]!=0)
		{
			count--;
			m_soduku[row][col]=0;
		}
	}
}
//this function helps fill diagonal from the top left to the bottom right of the puzzle
void Subroku::fillDiagonal()
{
	for(int i=0;i<m_size;i=i+b_size)
	{
		fillBox(i,i);
	}
}
//this is a helper fuction to fill the diagonals only by satisfying the boxes
//because diagonals don't have problems with row or col
void Subroku::fillBox(int row, int col)
{
	//randomnly generates a number and tests if it satisfies the box check
	int num; 
  for (int i=0; i<b_size; i++) 
  { 
    for (int j=0; j<b_size; j++) 
    { 
      do
      {
        num=rand() % m_size+1;
      } 
      while (!checkBox(row,col,num)); 
      m_soduku[row+i][col+j] = num; 
    } 
  } 
}
//this function checks the row
bool Subroku::checkRow(int row, int num)
{
	for (int i = 0; i<m_size; i++) 
	{
    if (m_soduku[row][i] == num) 
      return false; 
	}
  return true;
}
//this function checks the col
bool Subroku::checkCol(int col, int num)
{
	for (int i = 0; i<m_size; i++) 
	{
    if (m_soduku[i][col] == num) 
      return false; 
	}
  return true;
}
//this function checks the box around the number
bool Subroku::checkBox(int row, int col, int num)
{
	for (int i = 0; i<b_size; i++) 
	{
    for (int j = 0; j<b_size; j++) 
    {
      if (m_soduku[row+i][col+j]==num) 
        return false; 
    }
	}
  return true; 
}
//this is a recursive function to fill the spaces left
//this will return true if the board is totally filled
//false otherwise
bool Subroku::fillRest(int row, int col)
{
	//if the current position column exceeds the board while row doesn't
	//allow the col position to restart from 0 and increment the row to check
	if (col>=m_size && row<m_size-1)
  { 
    row = row + 1; 
    col = 0; 
  } 
	//back track if it exceeds the size of the board
  if (row>=m_size && col>=m_size) 
    return true;
  //when the current position to check is in the first three rows of the soduku puzzle
  if (row < b_size) 
  { 
  	//if it is in the top left box of the soduku puzzle
    if (col < b_size) 
      col = b_size; //set the position to fill to always be after the first box to the right
  } 
  //when current position is in the middle 3 rows of the soduku puzzle
  else if (row < m_size-b_size) 
  { 
  	//if it is in the very left col of the middle box of the soduku puzzle
    if (col==(int)(row/b_size)*b_size) 
      col =  col + b_size; 
  } 
  //When current position is in the last 3 rows of the soduku puzzle
  else
  { 
  	//if it is in the left most col of the bottom right box of the soduku puzzle
    if (col == m_size-b_size) 
    { 
      row = row + 1; 
      col = 0; 
      if (row>=m_size) //if the row exceeds the board size back track and redo
        return true;
    } 
  } 
  //this loop attempts to add a number from 1-9 into the board
  for (int num = 1; num<=m_size; num++) 
  { 
    if (checkValid(row, col, num))//if the number is valid
    { 
      m_soduku[row][col] = num;//insert the given row and col the number
      if (fillRest(row, col+1))// 
        return true; 
      m_soduku[row][col] = 0; 
    } 
  } 	
  return false;//stop the creation
}