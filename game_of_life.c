// Copiright 2022 amadopol eckhardt stumptow 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define World_Height 27
#define World_Width 82

int map[World_Height][World_Width];
int newmap[World_Height][World_Width];
void nextstep();
void firstmap();
int nextgen(int x, int y);
void clearnewmap();
void copymap();
void printmap();
void printnewmap();
void prevmap();
int get_bytes();
int input_speed(int *speed);
// void change_buffer (int buffer [][82]);

int main() {
    int c;
    // int buffer [27][82];
    int tmp = 1;
    int speed = 1;
    firstmap();
    printmap();
    freopen("/dev/tty", "r", stdin);
    while (tmp ==1) {
        c = input_speed(&speed);
        if (c != 0)
        break;
        system("clear");
        nextstep();
        printnewmap();
        usleep(1000000/speed);
        prevmap();
        clearnewmap();
        // change_buffer (buffer);
    }
    return 0;
}

void firstmap() {
    for (int i = 0; i < World_Height; i++) {
        for (int j = 0; j < World_Width; j++) {
            map[i][j] = 0;
        }
    }

        for (int i = 1; i < World_Height-1; i++) {
            for (int j = 1; j < World_Width-1; j++) {
                if (scanf("%d%d", &i, &j) == 2) {
                map[i][j] = 1;
                }
                break;
            }
        }
}


void printmap() {
    for (int i = 1; i < World_Height-1; i++) {
        for (int j = 1; j < World_Width-1; j++) {
            if (map[i][j] == 1) {
                printf("*");
            }
            if (map[i][j] == 0) {
                printf(".");
            }
        }
        printf("\n");
    }
}

void printnewmap() {
    for (int i = 1; i < World_Height-1; i++) {
        for (int j = 1; j < World_Width-1; j++) {
             if (newmap[i][j] == 1) {
                printf("*");
            }
            if (newmap[i][j] == 0) {
                printf(".");
            }
        }
        printf("\n");
    }
}

int nextgen(int x, int y) {
    int neighbors = 0;
    for (int k = x - 1; k <= x + 1; k++) {
        for (int m = y - 1; m <= y + 1; m++) {
            if (x == k && y == m) {
                continue;
            }
            neighbors += map[k][m];
        }
    }
    if (neighbors == 3 || (neighbors == 2 && map[x][y])) {
        return 1;
    }
    return 0;
}

void nextstep() {
     for (int i = 1; i < World_Height-1; i++) {
        map[i][0] = map[i][80];
        map[i][81] = map[i][1];
    }
    for (int j = 0; j < World_Width; j++) {
        map[0][j] = map[25][j];
        map[26][j] = map[1][j];
    }
    for (int i = 0; i < World_Height; i++) {
        for (int j = 0; j < World_Width; j++) {
            newmap[i][j] = nextgen(i, j);
        }
    }
}

void  prevmap() {
    // int count = 0;
    // int flag = 0;
    for (int i = 1; i < World_Height-1; i++) {
        for (int j = 1; j < World_Width-1; j++) {
            map[i][j] = newmap[i][j];
            // if (newmap[i][j] == buffer[i][j])
            // count++;
        }
    }
    // if (count == 82*27)
    //     flag = 1;
    // return flag;
}
// void change_buffer (int buffer [][82]){
//     for (int i = 0; i < World_Height; i++) {
//         for (int j = 0; j < 82; j++) {
//             buffer[i][j] = newmap[i][j];
//         }
//     }
// }
void clearnewmap() {
    for (int i = 1; i < World_Height-1; i++) {
        for (int j = 1; j < World_Width-1; j++) {
            newmap[i][j] = 0;
        }
    }
}
int kbhit() {
    int bytes;
    ioctl(0, FIONREAD, &bytes);
    return bytes;
}
int input_speed(int *speed) {
    system("/bin/stty raw");
    char c;
    int flag = 0;
    if (kbhit())  {
        c = getchar();
        if (c == '1')
            *speed = 1;
        if (c == '2')
            *speed = 2;
        if (c == '3')
            *speed = 3;
        if (c == '4')
            *speed = 4;
        if (c == '5')
            *speed = 10;
        if (c == '6')
            *speed = 100;
        if (c == 'q')
            flag++;
    }

    system("/bin/stty cooked");
    return flag;
}
