#ifndef SODUKU_H
#define SODUKU_H

#include <iostream>

class Subroku
{
private:
  int **m_soduku;
  int m_size;
  int b_size;
public:
   Subroku(int size);
   ~Subroku();
   void setValue(int row, int col, int value);
   int& getValue(int row, int col);
   bool checkValid(int row, int col, int num);
   int* operator[](int index);
   friend std::ostream& operator<<(std::ostream& output, Subroku& z);
   void createSoduku();
   void solvedSoduku();
   void fillDiagonal();
   void removeDigits();
   void fillBox(int row, int col);
   bool checkRow(int row, int num);
   bool checkCol(int col, int num);
   bool checkBox(int row, int col, int num);
   bool fillRest(int row, int col);
};

#endif