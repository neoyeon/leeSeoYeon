#include "game.h"

//���������� ����� ���� �߰�
int a = 0; // 0: �� �����, 1: �����

//Ű ����
int keyControl() {
    char temp = getch();
    if (temp == 'w' || temp == 'W') {
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
    else if (temp == ' ') { //�����̽���(����)
        a = (a == 0) ? 1 : 0; // ��Ȯ�� ���� ��ȯ
        //system("cls"); // ȭ�� ����ϰ� �����
        mainDraw(); // ���°� ����� ������ ȭ�� ���� //
        return SUBMIT;
    }
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
//

int see = 0;
void random() {
    srand(time(NULL)); // ���� �ʱ�ȭ
    //maindraw();
    while (1) { // ���� ����

        int random_function = rand() % 2; // 0 �Ǵ� 1 ���� ����
        if (random_function == 0) {
            girlfriend_back();


        }
        else {
            girlfriend_see();
        }
        keyControl(); // ����� �Է��� �ޱ� ���� ȣ��
        randomtime();
        mainDraw();

        // a�� see�� ���� ���ٸ� ����   
        randomtime();
        if (a == see) {
            break; // ������ �����Ǹ� ���� ����
        }

    }

    printf("���״�!\n");

}

void randomtime()// ������ �ð� ���� ���� (1�ʿ��� 3�� ����)
{
    //maindraw();
    int sleep_time = rand() % 5 + 1; // 1�ʿ��� 5�� ������ ���� ��
#ifdef _WIN32
    Sleep(sleep_time * 1000); // Windows�� ���
#else
    sleep(sleep_time); // POSIX �ý����� ���
#endif
}

//����ȭ�� ����ϱ�
void mainDraw() {
    if (a == 1) {
        // ����� ������ �� ����� ����
        //printf("���� ����: �����\n");
        a = 1;
        //printf("\033[H\033[J"); // �ܼ� ȭ�� ����� (ANSI �ڵ�)
        //system("cls");

        //�ܼ�ȭ�麸�� ��±׸��� ���Ƽ� ���Ʒ� �߶���. ���� ���� �ʿ�
        /*
        printf("................................................................................................\n");
        printf("................................................................................................\n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        
        printf("                                                                                                \n");
        printf("                                   ,~.                            ~:,     ,:~.                  \n");
        printf("                                 . ! ;                          ~   :!.*-;~   -.               \n");
        printf("             ,...,             .*,..*.=                         .     .- .      .              \n");
        printf("           ;         :       ,-       ~..~                     .     -. .~!     $                \n");
        printf("          ~         .:      ;         !~                           .:     .::   $               \n");
        printf("          ~          #      =         .,                        - ~;         =, $               \n");
        printf("          ,          $      -         .~                        ; -          .; $               \n");
        printf("          -          #      !         .-                        *..          .-.*               \n");
        printf("             ~,:.*             *,.,=.                                :! =.!,                    \n");
        printf("    -~~~~~~~=~~:~~=~~~~~~~~~~~~:~~~~$~~~~~~~~-.             :,,,,,,=,,-----,,,.............,,,,,\n");
        printf("    *                                        .,              ~                                  \n");
        printf("    * !,                                   ;, .              ~                                . \n");
        printf("    * ~.                                   ;- '              ~                                . \n");
        printf("    *                                         '             .=                                . \n");
        printf("    * -                                    -: '             ~                                 . \n");
        printf("    * =                                    ,,!=             ,                                 . \n");
        printf("    ::::::::::::::::::::::::::::::::::::;;!;::               :::::::::::::::::::::::::::::::::. \n");
        printf("     ;  !$     -=~.            -,.--     ;:  ;                ; : .    ;--;                   . \n");
        printf("     *****!*********!!!!!!!!!!!*****!!!******=,              ;..:.~.....,~..............,,,,,,, \n");
        printf("     ========================================$,              ================================== \n");
        printf("     ~,, ~                                   ,,              !!$                                \n");
        */
        /*
        printf("     ~,, $                                   ,,              ! =                                \n");
        printf("     ~,, $                                   ,,              ! =                                \n");
        printf("................................................................................................\n");
        */
       
       
        //���� ��ǥ�� ���
        int main_hand_x = 20;
        int main_hand_y = 10;
        gotoxy(main_hand_x, main_hand_y);
        printf(" ! ~~~~~~~~~~~~~~~~~~~~~~                ,,,,, ,!!,\n");
        gotoxy(main_hand_x, main_hand_y+1);
        printf(" ,:~                                     ~     ~,. \n");
        gotoxy(main_hand_x, main_hand_y+2);
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
        gotoxy(main_heart_x, main_heart_y+1);
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

    }
    else {
        // �� ����� ������ �� ����� ����
        //printf("���� ����: �� �����\n");
        //printf("\033[H\033[J"); // �ܼ� ȭ�� ����� (ANSI �ڵ�)
        system("cls");

        /*
        printf("................................................................................................\n");
        printf("................................................................................................\n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        printf("                                                                                                \n");
        */
        printf("                                                                                                \n");
        printf("                                   ,~.                            ~:,     ,:~.                  \n");
        printf("                                 . ! ;                          ~   :!.*-;~   -.               \n");
        printf("             ,...,             .*,..*.=                         .     .- .      .              \n");
        printf("           ;         :       ,-       ~..~                     .     -. .~!     $                \n");
        printf("          ~         .:      ;         !~                           .:     .::   $               \n");
        printf("          ~          #      =         .,                        - ~;         =, $               \n");
        printf("          ,          $      -         .~                        ; -          .; $               \n");
        printf("          -          #      !         .-                        *..          .-.*               \n");
        printf("             ~,:.*             *,.,=.                                :! =.!,                    \n");
        printf("    -~~~~~~~=~~:~~=~~~~~~~~~~~~:~~~~$~~~~~~~~-.             :,,,,,,=,,-----,,,.............,,,,,\n");
        printf("    *                                         ,              ~                                  \n");
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
        /*
        printf("     ~,, $                                   ,,              ! =                                \n");
        printf("     ~,, $                                   ,,              ! =                                \n");
        printf("................................................................................................\n");
        */
        random();
        }
}
//����ģ�� �޸�� ��� �Լ�
void girlfriend_back() {

    gotoxy(27, 1);
    printf("       ,~.   \n");
    gotoxy(27, 2);
    printf("      . ! ;   \n");
    gotoxy(27, 3);
    printf("    .*,..*.=   \n");
    gotoxy(27, 4);
    printf("  ,-        ~..~\n");
    gotoxy(27, 5);
    printf(" ;   /          !~\n");
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

void girlfriend_see() {
    see = 1;

    gotoxy(27, 1);
    printf("       ,~.   \n");
    gotoxy(27, 2);
    printf("      . ! ;   \n");
    gotoxy(27, 3);
    printf("    .*,..*.=   \n");
    gotoxy(27, 4);
    printf("  ,-        ~..~\n");
    gotoxy(27, 5);
    printf(" ;              !~\n");
    gotoxy(27, 6);
    printf("             ., \n");
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
        printf("                                                                                "); // ������ �ʱ�ȭ

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



// ���� ���� �Լ��� //
void start() { //����ȭ��
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
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