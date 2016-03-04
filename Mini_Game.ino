//Author: Valentino Vukelic

int polje[4][3];
int sleep = 1000;
int player = 0;

int movedL = 0;
int movedR = 0;

int score = 0;

#define GMOVSIZE 60
int gmov[GMOVSIZE][3] = {
                {0, 1, 0},
                {1, 0, 1},
                {1, 0, 1},
                {1, 0, 1},
                {0, 1, 0},
                {0, 0, 0},

                {0, 1, 0},
                {1, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 0},
                {0, 0, 0},

                {1, 1, 1},
                {0, 0, 1},
                {1, 1, 1},
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0},

                {1, 1, 1},
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0},

                {1, 0, 1},
                {1, 0, 1},
                {1, 1, 1},
                {0, 0, 1},
                {0, 0, 1},
                {0, 0, 0},

                {1, 1, 1},
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0},

                {1, 1, 1},
                {1, 0, 0},
                {1, 1, 1},
                {1, 0, 1},
                {1, 1, 1},
                {0, 0, 0},

                {1, 1, 1},
                {0, 0, 1},
                {0, 1, 0},
                {1, 0, 0},
                {1, 0, 0},
                {0, 0, 0},

                {1, 1, 1},
                {1, 0, 1},
                {1, 1, 1},
                {1, 0, 1},
                {1, 1, 1},
                {0, 0, 0},

                {1, 1, 1},
                {1, 0, 1},
                {1, 1, 1},
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}};

void movee() {
  for(int i = 3; i > 0; i--) {
    for(int j = 0; j < 3; j++) {
      polje[i][j] = polje[i - 1][j];
    }
  }
}

struct point {
  int x;
  int y;
  point(int a, int b) {
    x = a;
    y = b;
  }
};

void closingEffect() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
       digitalWrite(j + (11 - 3*i), LOW);
    }
  }
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(i + (11 - 3*0), HIGH);
    digitalWrite(2 - i + (11 - 3*3), HIGH);
    delay(200);
  }

  for(int i = 0; i < 3; i++) {
    digitalWrite(2 - i + (11 - 3*1), HIGH);
    digitalWrite(i + (11 - 3*2), HIGH);
    delay(200);
  }
}

void openingEffect() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
       digitalWrite(j + (11 - 3*i), HIGH);
    }
  }
  
  for(int i = 0; i < 3; i++) {
    digitalWrite(i + (11 - 3*1), LOW);
    digitalWrite(2 - i + (11 - 3*2), LOW);
    delay(200);
  }

  for(int i = 0; i < 3; i++) {
    digitalWrite(2 - i + (11 - 3*0), LOW);
    digitalWrite(i + (11 - 3*3), LOW);
    delay(200);
  }
}

void dead() {
  int brah[5] = {0};
  int br[5] = {0};
  int brsiz = 0;

  score = score -3;
  
  Serial.println(score);
  
  while(score) {
    brah[brsiz] = score % 10;
    score = score / 10;
    brsiz++;
  }

  if(brsiz == 0) brsiz = 1;

  for(int i = 0; i < brsiz; i++) {
    br[brsiz - 1 - i] = brah[i];
  }

  int sc[5*6][3] = {0};
  int t = 0;
  
  for(int i = 0; i < brsiz * 6; i++) {
    for(int j = 0; j < 3; j++) {
      sc[i][j] = gmov[br[t] * 6 + (i % 6)][j];
      Serial.print(br[t] * 6 + (i % 6));
      Serial.print(", ");
    }
    Serial.println();
    if(i != 0 && i % 6 == 5) t++;
  }

  closingEffect();
  delay(300);
  openingEffect();
  
  int r = -5;
  
  while(1) {
    
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 3; j++) {
        if(r + i < 0 || r > brsiz * 6) digitalWrite(j + (11 - 3*i), LOW);
        else {
          if(sc[i + r][j] == 1) digitalWrite(j + (11- 3*i), HIGH);
          else digitalWrite(j + (11- 3*i), LOW);
        }
      }
    }

    r++;
    if(r == brsiz*6 + 6) r = -5;
    
    delay(250);
   }
}

void addRow() {
  for(int i = 0; i < 3; i++)
    polje[0][i] = 0;
  
  int ran = random(100);
  int chance[3] = {33, 33, 33};
  if(player == 0) {
    chance[0] += 20;
    chance[1] -= 10;
    chance[2] -= 10;
  }
  else if(player == 1) {
    chance[0] -= 10;
    chance[1] += 20;
    chance[2] -= 10;
  }
  else if(player == 2) {
    chance[0] -= 10;
    chance[1] -= 10;
    chance[2] += 20;
  }

  if(polje[1][0] == 1) {
    chance[0] -= 20;
    chance[1] += 10;
    chance[2] += 10;
  }
  else if(polje[1][1] == 1) {
    chance[0] += 10;
    chance[1] -= 20;
    chance[2] += 10;
  }
  else if(polje[1][2] == 1) {
    chance[0] += 10;
    chance[1] += 10;
    chance[2] -= 20;
  }
  
  if(ran <= chance[0]) polje[0][0] = 1;
  else if(ran <= chance[0] + chance[1]) polje[0][1] = 1;
  else polje[0][2] = 1;
 
}

void deleteLastRow() {
  for(int i = 0; i < 3; i++)
    polje[3][i] = 0;
}

void checkDead() {
  if(polje[3][player] == 1) dead();
  score++;
}

void output() {
  int r = 5;
  for(int i = 2; i >= 0; i--) {
    for(int j = 0; j < 3; j++) {
      if(polje[i][j] == 1) digitalWrite(r, HIGH);
      else digitalWrite(r, LOW);
      r++;
    }
  }

  for(int i = 0; i < 3; i++) {
    if(i == player) digitalWrite(i + 2, HIGH);
    else digitalWrite(i + 2, LOW);
  }
}

void checkKeys() {

  if(analogRead(A1) > 500) {
    if(movedL == 0) {
      movedL = 1;
      if(player > 0){player--; output();}
    }
  }
  else movedL = 0;
  if(analogRead(A2) > 500) {
    if(movedR == 0) {
      movedR = 1;
      if(player < 2){player++; output();}
    }
  }
  else movedR = 0;
}

void setup() {
  Serial.begin(9600);
  
  for(int i = 2; i <= 13; i++) 
    pinMode(i, OUTPUT);
  
  randomSeed(analogRead(0));
}

void loop() {
    
    for(int i = 0; i < 100; i++) {
      delay(sleep/100);
      checkKeys();
    }

    movee();
    checkDead();
    deleteLastRow();
    addRow();
    
    if(sleep > 300) sleep -= 10;
    
    output();

}
