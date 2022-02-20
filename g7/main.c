#include <stdio.h>
#include <stdlib.h>

//ฟังก์ชันล้างหน้าจอ
void cls() {
  system("@cls||clear");
}

void drawBoard(char board[4][4]){
  int i,j;
  printf("    1 | 2 | 3 | 4 |\n");
  for (i=0;i<4;i++){
    printf("  -----------------\n%d ",i+1);
    for (j=0;j<4;j++){
      printf("| %c ",board[i][j]);
    }
    printf("| \n");
  }
  printf("  -----------------\n");
}

void init(char board[4][4]){
  int i,j;
  for (i=0;i<4;i++){
    for (j=0;j<4;j++){
      board[i][j] = ' ';
    }
  }
}

void insertBoard(char board[4][4],int x,int y,int turn){
  if (turn%2==0){
    if(board[x][y]==' '){
      board[x][y]='c';
    }
    else if(board[x][y]=='c'){
      board[x][y]='b';
    }
    else if(board[x][y]=='b'){
      board[x][y]='a';
    }
    else{
      printf("P1 can insert only a b and c");
    }
  }
  else{
    if(board[x][y]==' '){
      board[x][y]='C';
    }
    else if(board[x][y]=='C'){
      board[x][y]='B';
    }
    else if(board[x][y]=='B'){
      board[x][y]='A';
    }
    else{
      printf("P2 can insert only A B and C");
    }
  }
}

int main(){
  // int p1;
  int turn = 0;
  char board[4][4];
  init(board);
  drawBoard(board);
  insertBoard(board,0,0,turn);
  insertBoard(board,1,1,turn);
  insertBoard(board,1,1,turn);
  drawBoard(board);
  return 0;
}