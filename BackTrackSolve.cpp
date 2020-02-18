bool Soduku::solveSoduku(int **soduku)
{
	int row,col;
	if(FindUnassignedLocation(row,col))
		return true;
	for(int num=1;num<=9;num++)
	{
		if(checkValid(row,col,num))
		{
			m_soduku[row][col]=num;
			if(solveSoduku(m_soduku))
				return true;
			m_soduku[row][col]=0;
		}
	}
	return false;
}
bool Soduku::checkValid(int row, int col, int num)//checks if this value inputted works
{
	return 	!UsedInRow(row, num) && 
         	!UsedInCol(col, num) && 
         	!UsedInBox(row - row%3 , col - col%3, num)&& 
					m_soduku[row][col]==0;
}
bool Soduku::FindUnassignedLocation(int &row, int &col) 
{ 
    for (row = 0; row < m_size; row++) 
        for (col = 0; col < m_size; col++) 
            if (m_soduku[row][col] == 0) 
                return true; 
    return false; 
}
bool Soduku::UsedInRow(int row, int num)
{
	for (int col = 0; col < m_size; col++) 
        if (m_soduku[row][col] == num) 
            return true; 
    return false; 
}
bool Soduku::UsedInCol(int col, int num) 
{ 
  for (int row = 0; row < m_size; row++) 
    if (m_soduku[row][col] == num) 
      return true; 
  return false; 
} 
bool Soduku::UsedInBox(int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++) 
        for (int col = 0; col < 3; col++) 
            if (m_soduku[row+boxStartRow][col+boxStartCol] == num) 
                return true; 
    return false; 
}