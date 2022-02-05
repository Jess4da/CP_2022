#include <stdio.h>
#include <stdlib.h>

//ฟังก์ชันล้างหน้าจอ
void cls() {
  system("@cls||clear");
}

//ฟังก์ชันล้างเขียนหน้าจอ
void drawBoard(char board[4][4]){
  int i,j;
  printf("\n     1   2   3   4   x\n");
  printf("   -----------------\n");
  
  //วนลูปเพิ่อสร้างตาราง 4*4
  for(i=0;i<4;i++){
    printf(" %d |",i+1);
    for(j=0;j<4;j++){
      printf(" %c |",board[i][j]);
    }
    printf("\n   -----------------\n");
  }
  printf(" y\n\n");
}

//ฟังก์ชั่นกำหนดค่าเริ่มต้น
void init(char board[4][4],int player[2][5],int scoreBoard[4][4],int boardAlpha[4][4]){
  int i,j;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      board[i][j] = ' '; //ตั้งค่าในกระดานเป็นช่องว่าง
      scoreBoard[i][j]=0; // ตั้งค่าให้แต่ละช่องมีคะแนนเป็น 0
      boardAlpha[i][j]=0; // ตั้งค่าให้แต่ละช่องมีคะแนนเป็น 0
    }
  }
  // ตั้งค่าเกี่ยวกับผู้เล่น
  for(i=0;i<2;i++){
    player[i][0]=3; // ให้ผู้เล่นมีจำนวน a,A เท่ากับ 3 ตัว
    player[i][1]=6; // ให้ผู้เล่นมีจำนวน b,B เท่ากับ 6 ตัว
    player[i][2]=8; // ให้ผู้เล่นมีจำนวน c,C เท่ากับ 8 ตัว
    player[i][3]=0; // ให้ผู้เล่นมีคะแนนเริ่มต้นที่ 0
    player[i][4]=0; // 
  }
}

// ฟังก์ชั่นอัปเดตกระดาน
int updateBoard(char board[4][4],int player[2][5],int x,int y,char alphabet,int scoreBoard[4][4],int turn,int boardAlpha[4][4]){
  if (turn%2==0){
    // ให้ c ลงได้ในช่องที่ว่าง
    if(alphabet=='c'&&board[x][y]==' '&&player[0][2]>0){
      player[0][2]-=1;
      scoreBoard[x][y]=2;
      board[x][y]=alphabet;
      boardAlpha[x][y]=1;
    }
    // ให้ b ลงทับได้ c
    else if(alphabet=='b'&&board[x][y]=='c'&&player[0][1]>0){
      player[0][1]-=1;
      scoreBoard[x][y]=2;
      board[x][y]=alphabet;
      boardAlpha[x][y]=2;
    }
    // ให้ a ลงทับได้ b
    else if(alphabet=='a'&&board[x][y]=='b'&&player[0][0]>0){
      player[0][3]-=1;
      scoreBoard[x][y]=2;
      board[x][y]=alphabet;
      boardAlpha[x][y]=3;
    }else{
      printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
      printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
      drawBoard(board);
      printf("turn of player 1 you can insert a or b or c\n");
      return 1;
    }
  }else{
    // ให้ C ลงได้ในช่องที่ว่าง
    if(alphabet=='C'&&board[x][y]==' '&&player[1][2]>0){
      player[1][2]-=1;
      scoreBoard[x][y]=1;
      board[x][y]=alphabet;
      boardAlpha[x][y]=1;
    }
    // ให้ B ลงทับได้ C
    else if(alphabet=='B'&&board[x][y]=='C'&&player[1][1]>0){
      player[1][1]-=1;
      scoreBoard[x][y]=1;
      board[x][y]=alphabet;
      boardAlpha[x][y]=2;
    }
    // ให้ A ลงทับได้ B
    else if(alphabet=='A'&&board[x][y]=='B'&&player[1][0]>0){
      player[1][3]-=1;
      scoreBoard[x][y]=1;
      board[x][y]=alphabet;
      boardAlpha[x][y]=3;
    }else{
      printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
      printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
      drawBoard(board);
      printf("turn of player 2 you can insert A or B or C\n");
      return 1;
    }
  }
  drawBoard(board);  
  printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
  printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
}

void checkScore(char boardAlpha[4][4],int scoreBoard[4][4],int player[2][5]){
  int i,j;
  player[0][3]=0;
  player[1][3]=0;
  for (i=0;i<4;i++){
    for (j=0;j<4;j++){
      // เช็คแนวตั้ง
      if (scoreBoard[i][j]!=0&&scoreBoard[i][j]==scoreBoard[i][j+1]&&scoreBoard[i][j]==scoreBoard[i][j+2]&&j+2<4){
        int winAlpha = boardAlpha[i][j]+boardAlpha[i][j+1]+boardAlpha[i][j+2];
        if (scoreBoard[i][j]%2==0){
          player[0][3]+=1;
          if(winAlpha>5){
            player[0][4]=1;
          }
        }else{
          player[1][3]+=1; 
          if(winAlpha>5){
            player[1][4]=1;
          }
        }
      }
      // เช็คแนวนอน
      if (scoreBoard[i][j]!=0&&scoreBoard[i][j]==scoreBoard[i+1][j]&&scoreBoard[i][j]==scoreBoard[i+2][j]&&i+2<4){
        int winAlpha = boardAlpha[i][j]+boardAlpha[i+1][j]+boardAlpha[i+2][j];
        if (scoreBoard[i][j]%2==0){
          player[0][3]+=1;
          if(winAlpha>5){
            player[0][4]=1;
          }
        }else{
          player[1][3]+=1; 
          if(winAlpha>5){
            player[1][4]=1;
          }
        }
      }
      // เช็คแนวทะแยงลงชวา
      if (scoreBoard[i][j]!=0&&scoreBoard[i][j]==scoreBoard[i+1][j+1]&&scoreBoard[i][j]==scoreBoard[i+2][j+2]&&i+2<4&&j+2<4){
        int winAlpha = boardAlpha[i][j]+boardAlpha[i+1][j+1]+boardAlpha[i+1][j+2];
        if (scoreBoard[i][j]%2==0){
          player[0][3]+=1;
          if(winAlpha>5){
            player[0][4]=1;
          }
        }else{
          player[1][3]+=1; 
          if(winAlpha>5){
            player[1][4]=1;
          }
        }
      }
      // เช็คแนวทะแยงลซ้าย
      if (scoreBoard[i][j]!=0&&scoreBoard[i][j]==scoreBoard[i+1][j-1]&&scoreBoard[i][j]==scoreBoard[i+2][j-2]&&i+2<4&&j-2>=0){
        int winAlpha = boardAlpha[i][j]+boardAlpha[i+1][j-1]+boardAlpha[i+2][j-2];
        if (scoreBoard[i][j]%2==0){
          player[0][3]+=1;
          if(winAlpha>5){
            player[0][4]=1;
          }
        }else{
          player[1][3]+=1; 
          if(winAlpha>5){
            player[1][4]=1;
          }
        }
      }
    }
  }
  printf("\nscore player 1: %d\n",player[0][3]);
  printf("score player 2: %d\n",player[1][3]);
}

//เช็คถ้าไมมีช่องว่าเหลือให้จบเกม
int checkGame(char board[4][4]){
  int i,j;
  for (i=0;i<4;i++){
    for (j=0;j<4;j++){
      if (board[i][j]==' '){
        return 1;
      }
    }
  }
}

int main()
{
  int turn = 0;
  char board[4][4];
  int scoreBoard[4][4];
  int boardAlpha[4][4];
  int player[2][5];
  init(board,player,scoreBoard,boardAlpha);
  drawBoard(board);
  printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
  printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
  
  while (1){
    char alphabet ;
    int x,y;
    printf("turn of player %d\n",turn%2==0?1:2);
    printf("insert alphabet> ");
    scanf(" %c",&alphabet);
    printf("insert position of x and y (example: 1 2)> ");
    scanf(" %d %d",&x,&y);

    int checkBoard = updateBoard(board,player,y-1,x-1,alphabet,scoreBoard,turn,boardAlpha);
    if (checkGame(board)!=1||player[0][4]==1||player[1][4]==1){
      if (player[0][4]==1||player[1][4]==1){
        printf("Player %d is winer",turn%2+1);
      }else{
        printf("Player %d is winner\nPlay again? (Y/N)> ",player[0][3]>player[1][3]?1:2);
      }
      char pg;
      scanf(" %c",&pg);
      if (pg!='y'||pg!='Y'){
        break;
      }
      init(board,player,scoreBoard,boardAlpha);

    }else{
      turn+=1;
    }
  }
  return 0;
}