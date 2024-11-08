#include "game.h"

//���������� ����� ���� �߰�
int a = 0; // 0: �� �����, 1: �����
int see = 0;  // ���������� ����ģ���� ���� �ִ��� ���� ����

int keyControl() {
    if (kbhit()) {
        char temp = getch();
        if (temp == ' ') { // �����̽��� �Է� ó���� �ֿ켱����
            a = !a;
            system("cls");
            mainDraw();
            loveGauge();
            return SUBMIT;
        }
        else if (temp == 'w' || temp == 'W') {
            return UP;
        }
        else if (temp == 'a' || temp == 'A') {
            return LEFT;
        }
        else if (temp == 's' || temp == 'S') {
            return DOWN;
        }
        else if (temp == 'd' || temp == 'D') {
            return RIGHT;
        }
    }
    return 0;
}

// ���� ���� �Լ��� //
void start() { //����ȭ��
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            mainScreen();
            return 0;
        }
        else if (menuCode == 1) {
            infoDraw(); // ��������  
        }
        else if (menuCode == 2) {
            return 0; // ����
        }
        system("cls");
    }
    return 0;
}

void mainScreen() { //���ΰ���
    while (1)
    {
        mainDraw();
        loveGauge();
        int n = keyControl();
        if (n == SUBMIT) {
            return 0;
        }
    }
    return 0;
}

void titleDraw() {
    printf("\n\n\n\n");
    printf("             =$            $.           =$                               $:     \n");
    printf("      @@@;   @@  !==@@==!  @.  ===@$==  @@            *@@@,    -$===$#,  @!     \n");
    printf("     !@.!@   @@  $@@@@@@$*:@.  @@@#@@@  @@.,        *@@$~@@@,  ~@@@@@@=  @!     \n");
    printf("     *@ ~@   @@   ;@  @- @@@.   @; ~@   @@@!      *@@;    -@@#       @:  @!     \n");
    printf("     .@@@$   @@   ~@:;@    @.   @@ #@   @@        @*   $@   :@       @;  @!     \n");
    printf("       ;~    @@    =@@$    @.   .@@@-   @@        *;;;;#@;;;;!~      @=  @!     \n");
    printf("   :@@@@@@@@@@@                         @@        @@@@@@@@@@@@* ;;;:~~:;;;      \n");
    printf("    !!!@@!!!!@@   @@@@@@@@@@.  :*       !*        -$            @@@@@@@@@@!     \n");
    printf("       @@    @@   @$*******@.  #@                 ~@            @@@@@@@@@@!     \n");
    printf("       @@    @@   @;      ,@.  #@,.   ..,-        ~@-.    .,--  @@,....,~*      \n");
    printf("       @@    @@   @@@@@@@@@@.  @@@@@@@@@@@,       =@@@@@@@@@@@  @@@@@@@@@@@     \n");

}

int menuDraw() {
    int x = 40;
    int y = 26;

    gotoxy(x - 2, 26);
    printf("> ���ӽ��� ");
    gotoxy(40, 27);
    printf("���ӱ�Ģ ");
    gotoxy(40, 28);
    printf("  ���� ");
    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 26) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 28) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");

            }
            break;
        }
        case SUBMIT: {
            return y - 26;

        }
        }
    }
}

void infoDraw() {
    system("cls");
    printf("\n\n");
    printf("                  [ ���ӱ�Ģ ]\n\n");
    printf("      ����ģ�� ���� �ٸ� ������ ���� ����!\n\n"); //��ȣ �� ���ӱ�Ģ ���� �߰�
    printf("      ����ģ������ ��Ű�� �ʰ� �������� ������ ä����\n\n");
    printf("      �����̽��� �ѹ� Ŭ��: �� ��� \n\n");
    printf("      �����̽��� �ѹ� �� Ŭ��: �� ���� \n\n");
    printf("      �����̽��ٸ� ������ �ʱ�ȭ������ �̵��մϴ�.");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }
}

void mainDraw() {
    // �׻� ��� ���� �׸���
    system("cls");

    // �⺻ ��� �׸���
    printf("                                                                                                \n");
    printf("                                                                   ~:,     ,:~.                  \n");
    printf("                                                                 ~    :,  -;   -.               \n");
    printf("             ,...,,                                             .      .- .      .              \n");
    printf("           ;        :                                           .     -. .~!     $                \n");
    printf("          ~          :                                         *   .:       ::   $               \n");
    printf("          ~          #                                          - ~;         =, $               \n");
    printf("          ,          $                                          ;  -         ;. $               \n");
    printf("          -         #                                            .. '       '.-.*               \n");
    printf("             ~,:.*                                                   :! =.!,                    \n");
    printf("    -~~~~~~~=~~:~~=~~~~~~~~~~~~:~~~~$~~~~~~~~-.             :,,,,,,=,,-----,,,.............,,,, \n");
    printf("    *                                         ,              ~                                . \n");
    printf("    *                                         .              ~                                . \n");
    printf("    *                                         '              ~                                . \n");
    printf("    *                                         '             .=                                . \n");
    printf("    *                                         '             ~                                 . \n");
    printf("    *                                      ,,!=             ,                                 . \n");
    printf("    ::::::::::::::::::::::::::::::::::::;;!;::               :::::::::::::::::::::::::::::::::. \n");
    printf("     ;  !$     -=~.            -,.--     ;:  ;                ; : .    ;--;                   . \n");
    printf("     *****!*********!!!!!!!!!!!*****!!!******=,              ;..:.~.....,~..............,,,,,,, \n");
    printf("     ========================================$,              ================================== \n");
    printf("     ~,, ~                                   ,,              !!$                                \n");


    if (a == 1) {
        // ����� ������ �� �߰��� �հ� ��Ʈ �׸���
        //���� ��ǥ�� ���
        int main_hand_x = 20;
        int main_hand_y = 10;
        gotoxy(main_hand_x, main_hand_y);
        printf(" ! ~~~~~~~~~~~~~~~~~~~~~~                ,,,,, ,!!,\n");
        gotoxy(main_hand_x, main_hand_y + 1);
        printf(" ,:~                                     ~     ~,. \n");
        gotoxy(main_hand_x, main_hand_y + 2);
        printf("  -$..                                   ,@.$-     \n");
        gotoxy(main_hand_x, main_hand_y + 3);
        printf("    .-,!!                              .=;-,       \n");
        gotoxy(main_hand_x, main_hand_y + 4);
        printf("        -*~.--.                ,,,**.~~            \n");
        gotoxy(main_hand_x, main_hand_y + 5);
        printf("            ...~==...,,!===;......---~,            \n");

        // ��Ʈ�� ��ǥ�� ���
        int main_heart_x = 40;
        int main_heart_y = 7;
        gotoxy(main_heart_x, main_heart_y);
        printf("    &&     &&    \n");
        gotoxy(main_heart_x, main_heart_y + 1);
        printf("  &!!!!& &!!!!&  \n");
        gotoxy(main_heart_x, main_heart_y + 2);
        printf("&!!!!!!!&!!!!!!!&\n");
        gotoxy(main_heart_x, main_heart_y + 3);
        printf("  &!!!!!!!!!!!&  \n");
        gotoxy(main_heart_x, main_heart_y + 4);
        printf("    &!!!!!!!&    \n");
        gotoxy(main_heart_x, main_heart_y + 5);
        printf("       &!&       \n");
        gotoxy(main_heart_x, main_heart_y + 6);
        printf("        &        \n");

        // ����ģ���� ����� ��� �׸���
        if (see == 1) {
            girlfriend_see();
            random();// ����ģ���� ���� ���� �ִ� ���
        }
        else {
            girlfriend_back();
            random();// ����ģ���� �ڵ��ƺ� ���
        }
    }
    else {
        // �� ����� ������ ���� random() �Լ� ȣ��
        random();
    }
}


void random() {
    srand(time(NULL));  // ���� �ʱ�ȭ
    while (1) {
        // 0 �Ǵ� 1 ���� ���� (0: �ڵ��ƺ�, 1: ���� ��)
        int random_function = rand() % 2;
        if (random_function == 0) {
            see = 0;  // �ڵ��ƺ� ����
            girlfriend_back();
            randomtime(1);  // �ڵ��ƺ� ���¿����� ��� �ð�
        }
        else {
            see = 1;  // ���� ���� ����
            girlfriend_see();
            randomtime(0);  // ���� ���� ���¿����� ��� �ð�
        }

        // ���� ���� ���� üũ (���� ��� �ִµ� ����ģ���� ���� ������)
        if (a == 1 && see == 1) {
            system("cls");
            gotoxy(40, 15);  // ȭ�� �߾ӿ� ǥ��
            printf("���״�!\n");
            Sleep(2000);  // 2�� ���
            break;
        }

        // Ű �Է� üũ
        if (kbhit()) {
            keyControl();
        }
    }
}

void randomtime(int is_looking_back)
{
    int sleep_time;
    if (is_looking_back) {
        // �ڵ��ƺ� ������ ���� 1~3�� ���� ����
        sleep_time = (rand() % 2000) + 1000;  // 1000ms(1��) ~ 3000ms(3��)
    }
    else {
        // ���� ���� ���� ���� 2~6�� �Ŀ� �ڵ��ƺ�
        sleep_time = (rand() % 4000) + 2000;  // 2000ms(2��) ~ 6000ms(6��)
    }
#ifdef _WIN32
    Sleep(sleep_time);
#else
    sleep(sleep_time);
#endif
}

// ����ģ�� �޸�� �Լ� ����
void girlfriend_back() {
    // ���� ��ǥ�� �׸��� ���� �ش� ���� �����
    for (int i = 1; i <= 10; i++) {
        gotoxy(27, i);
    }

    gotoxy(27, 1);
    printf("       ,~.   \n");
    gotoxy(27, 2);
    printf("      . ! ;   \n");
    gotoxy(27, 3);
    printf("    .*,..*.=   \n");
    gotoxy(27, 4);
    printf("  ,-        ~..~\n");
    gotoxy(27, 5);
    printf(" ;   /         !~\n");
    gotoxy(27, 6);
    printf(" =   =       ., \n");
    gotoxy(27, 7);
    printf(" l           .~ \n");
    gotoxy(27, 8);
    printf(" .          .- \n");
    gotoxy(27, 9);
    printf("   *,.,=.   \n");
    gotoxy(27, 10);
    printf(" ~~~:~~~~$~~~\n");
}

// ����ģ���� ���� ��� �Լ� ����
void girlfriend_see() {
    // ���� ��ǥ�� �׸��� ���� �ش� ���� �����
    for (int i = 1; i <= 10; i++) {
        gotoxy(27, i);
    }

    gotoxy(27, 1);
    printf("       ,~.   \n");
    gotoxy(27, 2);
    printf("      . ! ;   \n");
    gotoxy(27, 3);
    printf("    .*,..*.=   \n");
    gotoxy(27, 4);
    printf("  ,-        ~..~\n");
    gotoxy(27, 5);
    printf(" ;             !~\n");
    gotoxy(27, 6);
    printf("            ., \n");
    gotoxy(27, 7);
    printf(" l           .~ \n");
    gotoxy(27, 8);
    printf(" .          .- \n");
    gotoxy(27, 9);
    printf("   *,.,=.   \n");
    gotoxy(27, 10);
    printf(" ~~~:~~~~$~~~\n");
}
// ������ ����
void loveGauge() {
    int x = 10; // ������ ��ġ x
    int y = 27; // ������ ��ġ y
    int currentGauge = 0; // �ʱ� ������ ��

    while (1) {
        // Ʋ �׸���
        gotoxy(x - 2, y - 1);
        printf("====================================================================================\n");
        gotoxy(x - 2, y);
        printf("||");
        gotoxy(100 - x, y);
        printf("||");
        gotoxy(x - 2, y + 1);
        printf("====================================================================================\n");

        // ������ ������Ʈ
        gotoxy(x, y);
        //printf("                                                                                "); // ������ �ʱ�ȭ

        if (a == 1) {
            // ����� ������ �� ������ ����
            if (currentGauge < 80) {
                currentGauge += 1; // ������ ����
            }
        }
        else {
            // �� ����� ������ �� ������ ����
            if (currentGauge > 0) {
                currentGauge -= 1; // ������ ����
            }
        }

        // ������ �׸���
        gotoxy(x, y);
        for (int i = 0; i < currentGauge; i++) {
            printf("#");
        }

        // �������� �� á�� ��
        if (currentGauge >= 80) {
            gotoxy(30, 10);
            printf("���� ��������");
            break;
        }

        // Ű �Է� Ȯ��
        if (kbhit()) {
            keyControl();
        }

        Sleep(300); // ������ ��ȭ �ӵ��� �� õõ��
    }
}