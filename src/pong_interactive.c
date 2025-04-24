#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
void Table(int racket_l, int racket_r, int ball_x, int ball_y, int points_l, int points_r);
int Racket_l(int racket_l, char command);
int Racket_r(int racket_r, char command);
int ball_rack_x(int ball_x, int ball_y, int racket_l, int racket_r, int ball_dir_x);
int ball_vn_y(int ball_y, int ball_dir_y);
int ball_sten_x(int ball_x, int ball_dir_x);
int points_1(int ball_x, int points_l);
int points_2(int ball_x, int points_r);
int main() {
    initscr();
    noecho();
    int racket_l = 12;
    int racket_r = 12;
    int points_l = 0;
    int points_r = 0;
    int ball_x = 39;
    int ball_y = 12;
    int ball_dir_x = 1;
    int ball_dir_y = 1;
    Table(racket_l, racket_r, ball_x, ball_y, points_l, points_r);
    while ((points_l != 21) && (points_r != 21)) {
        clear();
        char command = getch();
        racket_l = Racket_l(racket_l, command);
        racket_r = Racket_r(racket_r, command);
        if (command != '\n')  // движение мяча
        {
            ball_x += ball_dir_x;
            ball_y += ball_dir_y;
            ball_dir_x = ball_sten_x(ball_x, ball_dir_x);  // стенки
            points_l = points_1(ball_x, points_l);         // очки 1 игрока
            points_r = points_2(ball_x, points_r);         // очки 2 игрока
            ball_dir_x = ball_rack_x(ball_x, ball_y, racket_l, racket_r, ball_dir_x);  // ракетки
            ball_dir_y = ball_vn_y(ball_y, ball_dir_y);  // верхние/нижние
        }
        Table(racket_l, racket_r, ball_x, ball_y, points_l, points_r);
        timeout(0);
        refresh();
        usleep(100000);
    }
    if (points_l == 21) mvprintw(26, 20, "Сongratulations on your victory player1\n");
    if (points_r == 21) mvprintw(26, 20, "Сongratulations on your victory player2\n");
    refresh();
    endwin();
    if (points_l == 21) printf("Сongratulations on your victory player1\n");
    if (points_r == 21) printf("Сongratulations on your victory player2\n");
    return 0;
}

void Table(int racket_l, int racket_r, int ball_x, int ball_y, int points_l, int points_r) {
    clear();
    for (int h = 0; h < 25; h++) {
        for (int w = 0; w < 80; w++) {
            if (w == 37 && h == 1)
                mvprintw(h, w, "%d |", points_l);
            else if (w == 41 && h == 1)
                mvprintw(h, w, "%d", points_r);
            else if ((h == 0 || h == 24) && (w != 39))
                mvprintw(h, w, "-");
            else if (h == ball_y && w == ball_x)
                mvprintw(h, w, "o");
            else if (w == 39 && h != 1)
                mvprintw(h, w, "|");
            else if ((w == 0) && ((h == racket_l) || (h == (racket_l + 1)) || (h == (racket_l - 1))))
                mvprintw(h, w, "%s", "|");
            else if ((w == 79) && ((h == racket_r) || (h == (racket_r + 1)) || (h == (racket_r - 1))))
                mvprintw(h, w, "%s", "|");
            else if (w != 39 && h != 1)
                mvprintw(h, w, " ");
        }
    }
    refresh();
}
int Racket_l(int racket_l, char command) {
    if (command == 'a') {
        if (racket_l != 3) {
            racket_l -= 1;
            return racket_l;
        }
    } else if (command == 'z') {
        if (racket_l != 22) {
            racket_l += 1;
            return racket_l;
        }
    } else if (command == ' ') {
    }
    return racket_l;
}
int Racket_r(int racket_r, char command) {
    if (command == 'k') {
        if (racket_r != 3) {
            racket_r -= 1;
            return racket_r;
        }
    } else if (command == 'm') {
        if (racket_r != 22) {
            racket_r += 1;
            return racket_r;
        }
    } else if (command == ' ') {
    }
    return racket_r;
}
int ball_rack_x(int ball_x, int ball_y, int racket_l, int racket_r, int ball_dir_x) {
    if ((ball_y == racket_l || ball_y == racket_l - 1 || ball_y == racket_l + 1) && (ball_x == 1))
        ball_dir_x = 1;
    else if ((ball_y == racket_r || ball_y == racket_r - 1 || ball_y == racket_r + 1) && (ball_x == 78))
        ball_dir_x = -1;
    return ball_dir_x;
}
int ball_vn_y(int ball_y, int ball_dir_y) {
    if (ball_y == 2)
        ball_dir_y *= -1;
    else if (ball_y == 23)
        ball_dir_y *= -1;
    return ball_dir_y;
}
int ball_sten_x(int ball_x, int ball_dir_x) {
    if (ball_x == 0)
        ball_dir_x *= -1;
    else if (ball_x == 79)
        ball_dir_x *= -1;
    return ball_dir_x;
}
int points_1(int ball_x, int points_l) {
    if (ball_x == 79) points_l++;
    return points_l;
}
int points_2(int ball_x, int points_r) {
    if (ball_x == 0) points_r++;
    return points_r;
}

