// Copyright 2022 Jarrodca Howardmi Loganhea
#include <stdio.h>

void Window(int plot1_y, int plot2_y, int ball_x, int ball_y);
void Introduce();
int MovePlot1(int plot1_y, char buf);
int MovePlot2(int plot2_y, char buf);
int BallEnX(int ball_x, int ball_vx);
int BallEnY(int ball_y, int ball_vy);
int BallEnVx(int ball_x, int ball_y, int ball_vx, int plot1_y, int plot2_y);
int BallEnVy(int ball_y, int ball_vy);
int CheckScore1(int ball_x, int score_1);
int CheckScore2(int ball_x, int score_2);
int CheckInput(char buf);

int main() {
  Introduce();
  int plot1_y = 12;
  int plot2_y = 12;
  int ball_x = 40;
  int ball_y = 22;
  int ball_vx = 1;
  int ball_vy = 1;
  int score_1 = 0;
  int score_2 = 0;

  char buf = 'o';
  printf("                                    %2d  : %2d\n", score_1, score_2);
  Window(plot1_y, plot2_y, ball_x, ball_y);
  while (buf != 'q') {
    buf = getchar();
    CheckInput(buf);
    if (CheckInput(buf) == 1) {
      plot1_y = MovePlot1(plot1_y, buf);
      plot2_y = MovePlot2(plot2_y, buf);
      ball_vx = BallEnVx(ball_x, ball_y, ball_vx, plot1_y, plot2_y);
      ball_vy = BallEnVy(ball_y, ball_vy);
      ball_x = BallEnX(ball_x, ball_vx);
      ball_y = BallEnY(ball_y, ball_vy);
      score_1 = CheckScore1(ball_x, score_1);
      score_2 = CheckScore2(ball_x, score_2);
      if (ball_x < 0 || ball_x > 80) {
        ball_x = 40;
        ball_y = 12;
        ball_vx = -ball_vx;
        ball_vy = -ball_vy;
      }
      printf("\33[2J");
      printf("\033[0;0f");
      printf("                                    %2d  : %2d\n", score_1,
             score_2);
      Window(plot1_y, plot2_y, ball_x, ball_y);

      if (score_1 == 21) {
        printf("First Player wins!!!");
        buf = 'q';
      }
      if (score_2 == 21) {
        printf("Second Player wins!!!");
        buf = 'q';
      }
      fflush(stdin);
    }
  }
  if (score_1 > score_2) {
    printf("\nFirst Player wins!!!");
  } else if (score_1 < score_2) {
    printf("\nSecond Player wins!!!");
  } else {
    printf("\nDRAW!!!");
  }
  return 0;
}


void Introduce() {
  printf("------------------------------------------------------------\n");
  printf("|               Welcome to the Pong game!                  |\n");
  printf("|           First player: up - 'A', down - 'Z'             |\n");
  printf("|          Second player: up - 'K', down - 'M'             |\n");
  printf("|               Skip an action - 'space bar'               |\n");
  printf("|        The first player to score 21 points win           |\n");
  printf("|               GOOD LUCK HAVE FUN!!!!!!!!!!               |\n");
  printf("------------------------------------------------------------\n");
}

void Window(int plot1_y, int plot2_y, int ball_x, int ball_y) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j <= 80; j++) {
      if (i == 0 || i == 24) {
        printf("#");
      } else if ((i == plot1_y || i == plot1_y - 1 || i == plot1_y + 1) &&
                 (j == 0)) {
        printf("|");
      } else if ((i == plot2_y || i == plot2_y - 1 || i == plot2_y + 1) &&
                 (j == 80)) {
        printf("|");
      } else if (i == ball_y && j == ball_x) {
        printf("O");
      } else if (i > 0 && i < 24 && j == 40) {
        printf("|");
      } else if (i > 0 && i < 24 && (j != 0 || j != 80)) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int MovePlot1(int plot1_y, char button) {
  int max_hight = 24;
  switch (button) {
  case 'a': {
    ((plot1_y - 2) != 0) ? plot1_y -= 1 : plot1_y;
    return plot1_y;
  }
  case 'z': {
    ((plot1_y + 2) != max_hight) ? plot1_y += 1 : plot1_y;
    return plot1_y;
  }
  case 'A': {
    ((plot1_y - 2) != 0) ? plot1_y -= 1 : plot1_y;
    return plot1_y;
  }
  case 'Z': {
    ((plot1_y + 2) != max_hight) ? plot1_y += 1 : plot1_y;
    return plot1_y;
  }
  case 'q':
    return button;
  }
  return plot1_y;
}

int MovePlot2(int plot2_y, char button) {
  int max_hight = 24;
  switch (button) {
  case 'k': {
    ((plot2_y - 2) != 0) ? plot2_y -= 1 : plot2_y;
    return plot2_y;
  }
  case 'm': {
    ((plot2_y + 2) != max_hight) ? plot2_y += 1 : plot2_y;
    return plot2_y;
  }
  case 'K': {
    ((plot2_y - 2) != 0) ? plot2_y -= 1 : plot2_y;
    return plot2_y;
  }
  case 'M': {
    ((plot2_y + 2) != max_hight) ? plot2_y += 1 : plot2_y;
    return plot2_y;
  }
  case 'q':
    return button;
  }
  return plot2_y;
}

int BallEnX(int ball_x, int ball_vx) {
  ball_x += ball_vx;
  return ball_x;
}

int BallEnY(int ball_y, int ball_vy) {
  ball_y += ball_vy;
  return ball_y;
}
int BallEnVx(int ball_x, int ball_y, int ball_vx, int plot1_y, int plot2_y) {
  if ((ball_x == 1 && ball_y == plot1_y + 1) ||
      (ball_x == 1 && ball_y == plot1_y - 1) ||
      (ball_x == 1 && ball_y == plot1_y)) {
    ball_vx = -ball_vx;
  }
  if ((ball_x == 79 && ball_y == plot2_y) ||
      (ball_x == 79 && ball_y == plot2_y + 1) ||
      (ball_x == 79 && ball_y == plot2_y - 1)) {
    ball_vx = -ball_vx;
  }
  return ball_vx;
}

int BallEnVy(int ball_y, int ball_vy) {
  if (ball_y == 1 || ball_y == 23) {
    ball_vy = -ball_vy;
  }
  return ball_vy;
}

int CheckScore1(int ball_x, int score_1) {
  if (ball_x > 80) {
    score_1 += 1;
  }
  return score_1;
}

int CheckScore2(int ball_x, int score_2) {
  if (ball_x < 0) {
    score_2 += 1;
  }
  return score_2;
}

int CheckInput(char buf) {
  if (buf == 'A' || buf == 'Z' || buf == 'a' || buf == 'z' || buf == 'K' ||
      buf == 'M' || buf == 'k' || buf == 'm' || buf == ' ') {
    return 1;
  }
  return 0;
}
