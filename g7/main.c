#include <stdio.h>
#include <stdlib.h>
#include<time.h>
//ฟังก์ชันล้างหน้าจอ
void cls() {
  system("@cls||clear");
}

void drawBoard(char board[4][4]){
  // cls();
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

void init(char board[4][4],int bonus[2],int player[2],int alphabet){
  int i,j;
  for (i=0;i<4;i++){
    for (j=0;j<4;j++){
      board[i][j] = ' ';
    }
  }
  alphabet = 16;
  player[0]=0;
  player[1]=0;
  srand(time(0));
  bonus[0] = rand()%4;
  bonus[1] = rand()%4;

}

int insertBoard(char board[4][4],int x,int y,int turn,int alphabet){
  if (turn%2==0){
    if(board[x][y]==' '){
      board[x][y]='c';
      alphabet--;
    }
    else if(board[x][y]=='c'){
      board[x][y]='b';
    }
    else if(board[x][y]=='b'){
      board[x][y]='a';
    }
    else{
      printf("P1 can insert only a b and c\n");
      return 1;
    }
  }
  else{
    if(board[x][y]==' '){
      board[x][y]='C';
      alphabet--;
    }
    else if(board[x][y]=='C'){
      board[x][y]='B';
    }
    else if(board[x][y]=='B'){
      board[x][y]='A';
    }
    else{
      printf("P2 can insert only A B and C\n");
      return 1;
    }
  }
  return 0;
}

void checkBoard(char board[4][4],int player[2]){
  int i,j;
  player[0]=0;
  player[1]=0;
  for (i=0;i<4;i++){
    for (j=0;j<4;j++){
      if (board[i][j]==board[i][j+1]&&board[i][j]==board[i][j+2]&&j+2<4){
        if(board[i][j]=='c'){
          player[0]+=3;
        }
        else if(board[i][j]=='b'){
          player[0]+=1;
        }
        else if(board[i][j]=='a'){
          player[0]+=1;
        }

        //player 2
        else if(board[i][j]=='C'){
          player[1]+=3;
        }
        else if(board[i][j]=='B'){
          player[1]+=1;
        }
        else if(board[i][j]=='A'){
          player[1]+=1;
        }
      }
      if (board[i][j]==board[i+1][j]&&board[i][j]==board[i+2][j]&&i+2<4){
        if(board[i][j]=='c'){
          player[0]+=3;
        }
        else if(board[i][j]=='b'){
          player[0]+=1;
        }
        else if(board[i][j]=='a'){
          player[0]+=1;
        }

        //player 2
        else if(board[i][j]=='C'){
          player[1]+=3;
        }
        else if(board[i][j]=='B'){
          player[1]+=1;
        }
        else if(board[i][j]=='A'){
          player[1]+=1;
        }
      }

      if (board[i][j]==board[i+1][j+1]&&board[i][j]==board[i+2][j+2]&&i+2<4&&j+2<4){
        if(board[i][j]=='c'){
          player[0]+=3;
        }
        else if(board[i][j]=='b'){
          player[0]+=1;
        }
        else if(board[i][j]=='a'){
          player[0]+=1;
        }

        //player 2
        else if(board[i][j]=='C'){
          player[1]+=3;
        }
        else if(board[i][j]=='B'){
          player[1]+=1;
        }
        else if(board[i][j]=='A'){
          player[1]+=1;
        }
      }

      if (board[i][j]==board[i+1][j-1]&&board[i][j]==board[i+2][j-2]&&i+2<4&&j-2>=0){
        if(board[i][j]=='c'){
          player[0]+=3;
        }
        else if(board[i][j]=='b'){
          player[0]+=1;
        }
        else if(board[i][j]=='a'){
          player[0]+=1;
        }

        //player 2
        else if(board[i][j]=='C'){
          player[1]+=3;
        }
        else if(board[i][j]=='B'){
          player[1]+=1;
        }
        else if(board[i][j]=='A'){
          player[1]+=1;
        }
      }
    }
  }
}

int main(){
  // int p1;
  int bonus[2];
  int turn = 0;
  char board[4][4];
  int player[2];
  int x,y;
  int alphabet;
  // init(board,bonus);
  init(board,bonus,player,alphabet);
  drawBoard(board);

  while (1)
  {
    printf("Position bonus %d, %d\n",bonus[0],bonus[1]);
    printf("Score: P1 %d, P2 %d\n",player[0],player[1]);
    printf("Player %d insert position of x and y (example: 1 2)> ",turn%2+1);
    scanf(" %d %d",&x,&y);
    // drawBoard(board);
    
    cls();
    int check = insertBoard(board,y-1,x-1,turn,alphabet);
    checkBoard(board,player);
    if(x-1==bonus[0]&&y-1==bonus[1]||check==1){
      if(check==1){
        printf("Player %d insert again\n",turn%2+1);
      }
      else{
        bonus[0]=1000;
        bonus[1]=1000;
        printf("Player %d got bonus you can insert again\n",turn%2+1);
      }
    }
    else{
      turn++;
    }

    if(alphabet<=0){
      if(player[0]>player[1]){
        printf("Player 1 is Winner\nYou want to play again? [y/n]");
      }
      else if(player[1]>player[0]){
        printf("Player 2 is Winner\nYou want to play again? [y/n]");
      }else{
        printf("Tried\nYou want to play again? [y/n]> ");
        char pa;
        scanf(" %c",&pa);
        if(pa=='y'){
          init(board,bonus,player,alphabet);
          turn=0;
        }else{
          break;
        }
      }
    }

    drawBoard(board);
  }  
  return 0;
}