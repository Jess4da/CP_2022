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
void init(char board[4][4],int player[2][4],int scoreBoard[4][4]){
  int i,j;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      board[i][j] = ' '; //ตั้งค่าในกระดานเป็นช่องว่าง
      scoreBoard[i][j]=0; // ตั้งค่าให้แต่ละช่องมีคะแนนเป็น 0
    }
  }
  // ตั้งค่าเกี่ยวกับผู้เล่น
  for(i=0;i<2;i++){
    player[i][0]=3; // ให้ผู้เล่นมีจำนวน a,A เท่ากับ 3 ตัว
    player[i][1]=6; // ให้ผู้เล่นมีจำนวน b,B เท่ากับ 6 ตัว
    player[i][2]=8; // ให้ผู้เล่นมีจำนวน c,C เท่ากับ 8 ตัว
    player[i][3]=0; // ให้ผู้เล่นมีคะแนนเริ่มต้นที่ 0
  }
}

// ฟังก์ชั่นอัปเดตกระดาน
int updateTable(char board[4][4],int player[2][4],int turn, char c,int x,int y,int scoreBoard[4][4]){
  cls();

  if(turn%2==0){
    // ให้ a ลงทับได้ b
    if(c=='a'&&player[0][0]>0&&board[x][y]=='b'){
      player[0][0]--;
      board[x][y]=c;
      scoreBoard[x][y]=6;
    }
    // ให้ b ลงทับได้ c
    else if(c=='b'&&player[0][1]>0&&board[x][y]=='c'){
      player[0][1]--;
      board[x][y]=c;
      scoreBoard[x][y]=4;
    }
    // ให้ c ลงได้ในช่องที่ว่าง
    else if(c=='c'&&player[0][2]>0&&board[x][y]==' '){
      player[0][2]--;
      board[x][y]=c;
      scoreBoard[x][y]=2;
    }
    else{
      printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
      printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
      drawBoard(board);
      printf("turn of player 1 you can insert a or b or c\n");
      return 1;
    }
  }
  else{
    // ให้ a ลงทับได้ b
    if(c=='A'&&player[1][0]>0&&board[x][y]=='B'){
      player[1][0]--;
      board[x][y]=c;
      scoreBoard[x][y]=5;

    }
    // ให้ b ลงทับได้ c
    else if(c=='B'&&player[1][1]>0&&board[x][y]=='C'){
      player[1][1]--;
      board[x][y]=c;
      scoreBoard[x][y]=3;
    }
    // ให้ c ลงได้ในช่องที่ว่าง
    else if(c=='C'&&player[1][2]>0&&board[x][y]==' '){
      player[1][2]--;
      board[x][y]=c;
      scoreBoard[x][y]=1;
    }
    else{
      printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
      printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
      drawBoard(board);
      printf("turn of player 2 you can insert A or B or C\n");
      return 1;
    }
  }
  printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
  printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
  drawBoard(board);
  
}

// ฟังก์ชั่นเช็คคะแนน
void checkScore(char board[4][4],int player[2][4],int scoreBoard[4][4]){
  int i,j;
  player[0][3]=0;
  player[1][3]=0;
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      // เช็คแนวนอน
      if(scoreBoard[i][j]%2==0&&scoreBoard[i][j+1]%2==0&&scoreBoard[i][j+2]%2==0&&j+2<4){
        int s0 = scoreBoard[i][j] == 0 ? 0 : scoreBoard[i][j] == 2 ? 1 : scoreBoard[i][j] == 4 ? 2 : 3;
        int s1 = scoreBoard[i][j+1] == 0 ? 0 : scoreBoard[i][j+1] == 2 ? 1 : scoreBoard[i][j+1] == 4 ? 2 : 3;
        int s2 = scoreBoard[i][j+2] == 0 ? 0 : scoreBoard[i][j+2] == 2 ? 1 : scoreBoard[i][j+2] == 4 ? 2 : 3;
        player[0][3] = s0==0||s1==0||s2==0 ? player[0][3] : player[0][3]+s0+s1+s2;
        // printf("-score: %d %d,%d %c %c %c\n",player[0][3],i,j,board[i][j],board[i][j+1],board[i][j+2]);
      }
      // เช็คแนวตั้ง
      if(scoreBoard[i][j]%2==0&&scoreBoard[i+1][j]%2==0&&scoreBoard[i+2][j]%2==0&&i+2<4){
        int s0 = scoreBoard[i][j] == 0 ? 0 : scoreBoard[i][j] == 2 ? 1 : scoreBoard[i][j] == 4 ? 2 : 3;
        int s1 = scoreBoard[i+1][j] == 0 ? 0 : scoreBoard[i+1][j] == 2 ? 1 : scoreBoard[i+1][j] == 4 ? 2 : 3;
        int s2 = scoreBoard[i+2][j] == 0 ? 0 : scoreBoard[i+2][j] == 2 ? 1 : scoreBoard[i+2][j] == 4 ? 2 : 3;
        player[0][3] = s0==0||s1==0||s2==0 ?  player[0][3] : player[0][3]+ s0+s1+s2;
        // printf("|score: %d %d,%d %c %c %c\n",player[0][3],i,j,board[i][j],board[i+1][j],board[i+2][j]);
      }
      // เช็คแนวทะแยงลงขวา
      if(scoreBoard[i][j]%2==0&&scoreBoard[i+1][j+1]%2==0&&scoreBoard[i+2][j+2]%2==0&&i+2<4&&j+2<4){
        int s0 = scoreBoard[i][j] == 0 ? 0 : scoreBoard[i][j] == 2 ? 1 : scoreBoard[i][j] == 4 ? 2 : 3;
        int s1 = scoreBoard[i+1][j+1] == 0 ? 0 : scoreBoard[i+1][j+1] == 2 ? 1 : scoreBoard[i+1][j+1] == 4 ? 2 : 3;
        int s2 = scoreBoard[i+2][j+2] == 0 ? 0 : scoreBoard[i+2][j+2] == 2 ? 1 : scoreBoard[i+2][j+2] == 4 ? 2 : 3;
        player[0][3] = s0==0||s1==0||s2==0 ?  player[0][3] : player[0][3]+ s0+s1+s2;
        // printf(">score: %d %d,%d %c %c %c\n",player[0][3],i,j,board[i][j],board[i+1][j+1],board[i+2][j+2]);
      }
      // เช็คแนวทะแยงลงซ้าย
      if(scoreBoard[i][j]%2==0&&scoreBoard[i+1][j-1]%2==0&&scoreBoard[i+2][j-2]%2==0&&i+2<4&&j-2>=0){
        int s0 = scoreBoard[i][j] == 0 ? 0 : scoreBoard[i][j] == 2 ? 1 : scoreBoard[i][j] == 4 ? 2 : 3;
        int s1 = scoreBoard[i+1][j-1] == 0 ? 0 : scoreBoard[i+1][j-1] == 2 ? 1 : scoreBoard[i+1][j-1] == 4 ? 2 : 3;
        int s2 = scoreBoard[i+2][j-2] == 0 ? 0 : scoreBoard[i+2][j-2] == 2 ? 1 : scoreBoard[i+2][j-2] == 4 ? 2 : 3;
        player[0][3] = s0==0||s1==0||s2==0 ?  player[0][3] : player[0][3]+ s0+s1+s2;
        // printf("<score: %d %d,%d %c %c %c\n",player[0][3],i,j,board[i][j],board[i+1][j-1],board[i+2][j-2]);
      }
      
      //player 2
      // เช็คแนวนอน
      if(scoreBoard[i][j]%2!=0&&scoreBoard[i][j+1]%2!=0&&scoreBoard[i][j+2]%2!=0&&j+2<4){
        int s0 = scoreBoard[i][j] == 1 ? 1 : scoreBoard[i][j] == 3 ? 2 : 3;
        int s1 = scoreBoard[i][j+1] == 1 ? 1 : scoreBoard[i][j+1] == 3 ? 2 : 3;
        int s2 = scoreBoard[i][j+2] == 1 ? 1 : scoreBoard[i][j+2] == 3 ? 2 : 3;
        player[1][3] = player[1][3]+s0+s1+s2;
        // printf("-score: %d %d,%d %c %c %c\n",player[1][3],i,j,board[i][j],board[i][j+1],board[i][j+2]);
      }
      // เช็คแนวตั้ง
      if(scoreBoard[i][j]%2!=0&&scoreBoard[i+1][j]%2!=0&&scoreBoard[i+2][j]%2!=0&&i+2<4){
        int s0 = scoreBoard[i][j] == 1 ? 1 : scoreBoard[i][j] == 3 ? 2 : 3;
        int s1 = scoreBoard[i+1][j] == 1 ? 1 : scoreBoard[i+1][j] == 3 ? 2 : 3;
        int s2 = scoreBoard[i+2][j] == 1 ? 1 : scoreBoard[i+2][j] == 3 ? 2 : 3;
        player[1][3] = player[1][3]+ s0+s1+s2;
        // printf("|score: %d %d,%d %c %c %c\n",player[1][3],i,j,board[i][j],board[i+1][j],board[i+2][j]);
      }
      // เช็คแนวทะแยงลงขวา
      if(scoreBoard[i][j]%2!=0&&scoreBoard[i+1][j+1]%2!=0&&scoreBoard[i+2][j+2]%2!=0&&i+2<4&&j+2<4){
        int s0 = scoreBoard[i][j] == 1 ? 1 : scoreBoard[i][j] == 3 ? 2 : 3;
        int s1 = scoreBoard[i+1][j+1] == 1 ? 1 : scoreBoard[i+1][j+1] == 3 ? 2 : 3;
        int s2 = scoreBoard[i+2][j+2] == 1 ? 1 : scoreBoard[i+2][j+2] == 3 ? 2 : 3;
        player[1][3] = player[1][3]+ s0+s1+s2;
        // printf(">score: %d %d,%d %c %c %c\n",player[1][3],i,j,board[i][j],board[i+1][j+1],board[i+2][j+2]);
      }
      // เช็คแนวทะแยงลงซ้าย
      if(scoreBoard[i][j]%2!=0&&scoreBoard[i+1][j-1]%2!=0&&scoreBoard[i+2][j-2]%2!=0&&i+2<4&&j-2>=0){
        int s0 = scoreBoard[i][j] == 1 ? 1 : scoreBoard[i][j] == 3 ? 2 : 3;
        int s1 = scoreBoard[i+1][j-1] == 1 ? 1 : scoreBoard[i+1][j-1] == 3 ? 2 : 3;
        int s2 = scoreBoard[i+2][j-2] == 1 ? 1 : scoreBoard[i+2][j-2] == 3 ? 2 : 3;
        player[1][3] = player[1][3]+ s0+s1+s2;
        // printf("<score: %d %d,%d %c %c %c\n",player[1][3],i,j,board[i][j],board[i+1][j-1],board[i+2][j-2]);
      }
    }
  }
  printf("\nscore player 1: %d\n",player[0][3]);
  printf("score player 2: %d\n",player[1][3]);
}

int checkWin(int player[2][4]){
  int i,j;
  for(i=0;i<2;i++){
    if(player[i][0]==0){
      return 1;
    }
  }
}

int main()
{
  int turn = 0;
  char board[4][4];
  int scoreBoard[4][4];
  int player[2][4];
  init(board,player,scoreBoard);
  printf("a: %d, b: %d, c: %d\n",player[0][0],player[0][1],player[0][2]);
  printf("A: %d, B: %d, C: %d\n",player[1][0],player[1][1],player[1][2]);
  // turn+=1;
  drawBoard(board);
  while (1)
  {
    char alphabet ;
    int x,y;
    printf("turn of player %d\n",turn%2==0?1:2);
    printf("insert alphabet> ");
    scanf(" %c",&alphabet);
    printf("insert position of x > ");
    scanf(" %d",&x);
    printf("insert position of y > ");
    scanf(" %d",&y);
    
    int checkBoard = updateTable(board,player,turn,alphabet,y-1,x-1,scoreBoard);
    checkScore(board,player,scoreBoard);
    
    int check = checkWin(player);
    if(check==1){
      char pg;
      printf("Player %d is winner\nPlay again? (Y/N)> ",player[0][3]>player[1][3]?1:2);
      scanf(" %c",&pg);
      if (pg!='y'||pg!='Y'){
        break;
      }
    init(board,player,scoreBoard);

    }
    if(checkBoard!=1){
      turn+=1;
    }
    // printf("turn of player %d\n",turn%2==0?1:2);

  }
 
  return 0;
}