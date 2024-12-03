#include "game.h"
#include "header.h"

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

//���������� ����� ���� �߰�
int a = 1; // 0: �� �����, 1: ����� //���ΰ��� ���۽� �վ����� �����ϱ� ���� �ʱⰪ 1�� ����.
int random_function = 0; // ������ ������
int gfSee = 0; // ����ģ�� ���ƺô��� ����. 0 �� �� �� ��, 1 �� �� ��.
int gfTime = 0; // ����ģ���� ���ƺ��� �ִ� �ð�
int score = 0; // ����

// �׷��� ��Ҹ� ǥ���ϱ� ���� ����ü
typedef struct {
    Vector3* points;
    int num_points;
    const char* symbol;
} GraphicElement;

// ȭ�� ��ǥ�� ��ȯ�ϴ� �Լ�
void transformAndDraw(Vector3* point, Matrix3x3 transform) {
    Vector3 transformed = multiply_matrix_vector(transform, *point);
    gotoxy((int)transformed.x, (int)transformed.y);
}

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
        //mainDraw(); // ���°� ����� ������ ȭ�� ���� //
        return SUBMIT;
    }
}

void titleDraw() {
    printf("\n\n\n\n");
    printf("           @@      @     !@*     @      @@         ,.   ,,  *@!  !#*;*#@$  @@   \n");
    printf("   =@@@    @@  ;$**@=*$, !@*  ==*#@*=#  @@         @*   @@  *@;       #@$  @@*  \n");
    printf("   @~ :@   @@    $@,=@ ,@@@*  -!@::@*=  @@@*       @:...@@  *@;. !@@@@@@$  @@@  \n");
    printf("   @=:=@   @@   ,@: *@ .$$@*   $$  @~   @@$*       @@@@@@$  *@@@ !@:       @*   \n");
    printf("   -@@@    @@    *@@@@   !@*   :@@@@-   @@         @$   @=  *@*$ !@@@@@@#. @*   \n");
    printf("           @@    -*@*:   !@*    !#@:    @@         @*   @#  *@:  -;;;;;;;, @#   \n");
    printf(" @@@@@@@@@@@@                           @@         @@@@@@@  *@:                 \n");
    printf(" :!!*@$!   @@   @@@@@@@@@@@*  ,=~       !!         ##==#@=  *@;  !@@@@@@@@@@#   \n");
    printf("    ~@!    @@   @@,......!@*  :@$                           *@;  !@!      .@!   \n");
    printf("    !@!    @@   @@:~~~~~~=@*  :@#~~~~~~~~~                  *@!  !@!~~~~~~~@@   \n");

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
    printf("                   [ ���ӱ�Ģ ]\n\n");
    printf("       ����ģ�� ���� �ٸ� ������ ���� ����!\n\n"); //��ȣ �� ���ӱ�Ģ ���� �߰�
    printf("       ����ģ������ ��Ű�� �ʰ� �������� ������ ä����\n\n");
    printf("       �����̽��� �ѹ� Ŭ��: �� ��� \n\n");
    printf("       �����̽��� �ѹ� �� Ŭ��: �� ���� \n\n");
    printf("       �����̽��ٸ� ������ �ʱ�ȭ������ �̵��մϴ�.");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }
}
void drawBBO(float base_x, float base_y, float scale) {
    Matrix3x3 transform = identity_matrix();
    transform = multiply_matrices(transform, translation_matrix(base_x, base_y));
    transform = multiply_matrices(transform, scale_matrix(scale, scale));

    const char* screen2[] = {
        "            .;;;;                                                                              ",
        "          ,=@@@@@@;.                                 .,,,,                                     ",
        "         .@@@@@@@@@@                                 @@@@@@@                                   ",
        "        ,@@@@@@@@@@@@                              :@@@@@@@@@=                                 ",
        "       -@@@@@@@@@@@@@@.                           ~@@@@@@@@@@@!                                ",
        "       *@@@@@@@@@@@@@@~                          -@@@@@@@@@@@@@!                               ",
        "       @@@@@@@@!.....=@                          @@@@@@@@@@@@@@@                               ",
        "       @@@@@@@@       !                         ~~~@@@@@@@@@@@@@!                              ",
        "      !@@@@*           !                        !       @@@@@@@@$                              ",
        "      !@@@@;     ..  ,* !                      !      . @@@@@@@@$                              ",
        "       @@@@;      '''   !                      ! *...~  ,,,@@@@@@                              ",
        "       @@@@$            !                      !           ;@@@@@                              ",
        "       *@@@@@~.         !                      !           ;@@@@@                              ",
        "       ~@@@@@@          ---------)) ((---------          ,,;@@@@@                              ",
        "        :@@@@@          ---------)) ((---------           !@@@@@@                              ",
        "         ;@@@@          !                      !          @@@@@@@@                             ",
        "          !#@      -!                           !!-      ~@@@@@@@@                             ",
        "            .*@@:@              *@@; ;@@*           :   -@@@@@@@@                              ",
        "            *    @=            *@@@@@@@@@*           : =$@@@@@@@@@                             ",
        "          ~;;;:;.;,;             *@@@@@*                -@@@@@@@@@                             ",
        "         ,@.      .;,             *@@@*              =  -@@@@@@@@@                             ",
        "        *  ;$    #~  #~            .@.             !*   -@@@@@@@@@~                            ",
        "      !~     ~~~~     ,~**                       *~..~**=@@@@@@@@@*                            ",
        "      $                   !;                             @@@@@@@@@@                            ",
        "      $                    -.                            @@@@@@@@@@!                           ",
        "      --                    #                            .@@@@@@@@@!                           ",
        "       :                    :.                           @@@@@@@@@@                            "
    };

    // y ��ǥ�� 40���� �����ϵ��� ����
    for (int i = 0; i < 24; i++) {
        Vector3 pos = { 0, i + 40, 1 }; // y ��ǥ�� 40���� ����
        Vector3 transformed = multiply_matrix_vector(transform, pos);
        gotoxy((int)transformed.x, (int)transformed.y);
        puts(screen2[i]);
    }
}
void drawNotBBO(float base_x, float base_y, float scale) {

    printf(
        "                 ;;;;.\n"
        "              ,#@@@@@@@,                                        ,,,,\n"
        "             ~@@@@@@@@@@;                                     -@@@@@@= \n"
        "            :@@@@@@@@@@@@!                                   #@@@@@@@@@~\n"
        "            @@@@@@@@@@@@@#                                  #@@@@@@@@@@@- \n"
        "           #@@@@@@@@@@@@@@@                                @@@@@@@@@@@@@@.\n"
        "           #@@@@@@@@@@@@@@@                               -@@@@@@@@@@@@@@!\n"
        "          .@@@@@@@@@@@@@@@@-                              =@@@@@@@@@@@@@@@\n"
        "          .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@.\n"
        "          .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@#\n"
        "          .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@#\n"
        "           #@@@@@@@@@@@@@@@                               @@@@@@@@@@@@@@@@#\n"
        "           $@@@@@@@@@@@@@@=                               @@@@@@@@@@@@@@@@$\n"
        "            @@@@@@@@@@@@@@                                @@@@@@@@@@@@@@@@#\n"
        "            !@@@@@@@@@@@@-                               ,@@@@@@@@@@@@@@@@#\n"
        "             *@@@@@@@@@@;                                 @@@@@@@@@@@@@@@@#\n"
        "               =@@@@@@=,                                  @@@@@@@@@@@@@@@@#\n"
        "                :~@@;,                                    @@@@@@@@@@@@@@@@#\n"
        "                ~    -                                    @@@@@@@@@@@@@@@@,\n"
        "               ;;;: -!;;                                  @@@@@@@@@@@@@@@@\n"
        "             .#    ,   ,*                                 @@@@@@@@@@@@@@@@\n"
        "            ~!-$       -;=                                @@@@@@@@@@@@@@@@\n"
        "          *~.   ~-***.~   ~*                             ~@@@@@@@@@@@@@@@@\n"
        "         ;                  !:                        .:!-@@@@@@@@@@@@@@@@!:\n"
        "                              =:                     .!   @@@@@@@@@@@@@@@@  $\n"
        "                               *                      !    @@@@@@@@@@@@@@@* \n"
        "                               *   !                       @@@@@@@@@@@@@@@!\n"
    );
    
}

// ���� ȭ�� ��� �Լ�
void mainDraw() {
    system("cls");

    // a�� ���� ���� ������ �Լ� ȣ��
    if (a == 0) {
        drawNotBBO(0.0f, 10.0f, 1.0f); // a�� 0�� �� ȣ��
    }
    else if (a == 1) {
        drawBBO(0.0f, 10.0f, 1.0f);// a�� 1�� �� ȣ��
    }
}

// ����ģ�� ���� �ִ� ���
void girlfriend_see() {

    int x = 32;
    int y = 0;

    gotoxy(x, y);
    printf("       .,..,.\n");

    gotoxy(x, y + 1);
    printf("      *~~~-~~;!\n");

    gotoxy(x, y + 2);
    printf("     #         ;  .  .\n");

    gotoxy(x, y + 3);
    printf("    ;          ,!,:- ;,\n");

    gotoxy(x, y + 4);
    printf("   $             #.   *\n");

    gotoxy(x, y + 5);
    printf("  *              -    *\n");

    gotoxy(x, y + 6);
    printf("  *@@@@@@@@@$    .    *\n");

    gotoxy(x, y + 7);
    printf(" ,~   .::    .    #   .\n");

    gotoxy(x, y + 8);
    printf(" ,~  ##@@#  ,~ :  #!   : \n");

    gotoxy(x, y + 9);
    printf(" ,~ : @@@@=-   ;  #!.  #\n");

    gotoxy(x, y + 10);
    printf(" ,~ ;=@@@@*    ;  # *  # \n");

    gotoxy(x, y + 11);
    printf(" .~   ===.     ~ .   =::\n");

    gotoxy(x, y + 12);
    printf("  *         .==  :.   ,\n");

    gotoxy(x, y + 13);
    printf("   #  .     ,~   :\n");

    gotoxy(x, y + 14);
    printf("   ~- ,     ,~  = \n");

    gotoxy(x, y + 15);
    printf("    ;$.     ,~,* \n");

    gotoxy(x, y + 16);
    printf("     .;*,   !=~ \n");

    gotoxy(x, y + 17);
    printf("        **$,\n");

    gotoxy(x, y + 18);
    printf("        *   .-\n");

    gotoxy(x, y + 19);
    printf("       *:    !.\n");

    gotoxy(x, y + 20);
    printf("    -;-!~   .;;;-;\n");

    gotoxy(x, y + 21);
    printf("  *#     $@@$     $*\n");

    gotoxy(x, y + 22);
    printf(" $                 ,.\n");

    gotoxy(x, y + 23);
    printf(" .                 ~,\n");

    gotoxy(x, y + 24);
    printf(",                  ,.\n");

    gotoxy(x, y + 25);
    printf("=                   ,\n");

}


// ����ģ�� �޸��
void girlfriend_back() {
    int x = 32;
    int y = 0;

    gotoxy(x, y);
    printf("       .,..,.\n");

    gotoxy(x, y + 1);
    printf("      *~~~-~~;!\n");

    gotoxy(x, y + 2);
    printf("     #   =-=   ;        \n");

    gotoxy(x, y + 3);
    printf("    ;   :  ~;  ,!       \n");

    gotoxy(x, y + 4);
    printf("   $    *   $    !       \n");

    gotoxy(x, y + 5);
    printf("  *     *   $    ,     \n");

    gotoxy(x, y + 6);
    printf("        *   $    .     \n");

    gotoxy(x, y + 7);
    printf(" ,~     *   $     #     \n");

    gotoxy(x, y + 8);
    printf(" ,~     *   $     #     \n");

    gotoxy(x, y + 9);
    printf(" ,~     :   $     #     \n");

    gotoxy(x, y + 10);
    printf(" ,~     ~. !.     #     \n");

    gotoxy(x, y + 11);
    printf(" .~     ~, ;     .        \n");

    gotoxy(x, y + 12);
    printf("  *     .:,-     :.       \n");

    gotoxy(x, y + 13);
    printf("   #     =;      :\n");

    gotoxy(x, y + 14);
    printf("   ~-    =,     =\n");

    gotoxy(x, y + 15);
    printf("    ; . ~.    ,*\n");

    gotoxy(x, y + 16);
    printf("     .;*,   ;!~\n");

    gotoxy(x, y + 17);
    printf("        **$,\n");

    gotoxy(x, y + 18);
    printf("        *   .-\n");

    gotoxy(x, y + 19);
    printf("       *:    !.\n");

    gotoxy(x, y + 20);
    printf("    -;-!~   .;;;-;\n");

    gotoxy(x, y + 21);
    printf("  *#     $@@$     $*\n");

    gotoxy(x, y + 22);
    printf(" $                 ,.\n");

    gotoxy(x, y + 23);
    printf(" .                 ~,\n");

    gotoxy(x, y + 24);
    printf(",                  ,.\n");

    gotoxy(x, y + 25);
    printf("=                   ,\n");
}


/*
void display_array(const char art[GIRLFRIEND_HEIGHT][GIRLFRIEND_WIDTH], int x, int y) {
    for (int i = 0; i < GIRLFRIEND_HEIGHT; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < GIRLFRIEND_WIDTH; j++) {
            printf("%c", art[i][j]);
        }
        printf("\n");
    }
}
*/


/*
void girlfriend_back() {
    display_array(girlfriend_back_art, 27, 1);
}

void girlfriend_see() {
    display_array(girlfriend_side_art, 27, 1);
}
*/

void random() {
    if (gfSee == 0) { // ��ģ�� ���� ���� ���� ��
        girlfriend_back();

        srand(time(NULL)); // �Լ� ������ ������ ���ο� ������ ����
        random_function = rand() % 100;

        if (random_function < 50) {  // ���� Ȯ���� �ڵ��ƺ�
            gfSee = 1;
        }
    }
}

void girlFriendTime() {
    gfTime += 1; // ��ģ�� ���� �ִ� �ð� 1�� �߰�

    girlfriend_see();

    if (a == 1) {  // ���� ��� �ִ� ���¶��
        Sleep(5000);
        badEnd();
        return;
    }

    if (gfTime = 5) {
        //girlfriend_back();
        gfSee = 0;
        gfTime = 0;
    }
}


void badEnd() {
    system("cls");
    printf("���״�!\n");
    exit(0);
}


/*
int currentGauge = 0; // �ʱ� ������ ��

// ������ ����
void loveGauge() {
    int x = 10; // ������ ��ġ x
    int y = 27; // ������ ��ġ y


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
        return 0;
    }

    // Ű �Է� Ȯ��
    if (kbhit()) {
        keyControl();
    }

    Sleep(300); // ������ ��ȭ �ӵ��� �� õõ��

}
*/



// �ǻ� �̺�Ʈ ó�� �Լ�
void handleKissEvent() {
    // �����̽��ٰ� ���ȴ��� Ȯ��
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        score++; // ���� 1�� ����
        gotoxy(70, 1);
       // printf("���� ����: %d\n", score); // ���� ���
        //Sleep(300); // �ߺ� �Է� ���� ��� �ð�
    }
}

// ����1
void End1() {
    printf("�� �հ� �ƽ����~\n");
}

// ����2
void End2() {
    printf("����~ �ڱ�� ���ۿ� ����?\n");
}

// �⺻ ���� (Optional)
void DefaultEnding() {
    printf("���� ���� ����� ���ϳ�? �� ���� ����\n");
}

void End() {
    system("cls"); // �ܼ� ȭ�� �����

    if (score <= 10) {
        DefaultEnding(); // ������ 10 ����
    }
    else if (score <= 15) {
        End2(); // ������ 11 �̻� 15 ����
    }
    else {
        End1(); // ������ 16 �̻�
    }
}

//�̾߿�
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

//�ð� ���� ǥ��
void Info(int elapsedTime, int score) {
    gotoxy(70, 3); // �ð� ǥ��
    printf("���� �ð�: %d��\n", elapsedTime);

    gotoxy(70, 4); // ���� ǥ��
    printf("����: %d\n", score);
}

//���� ���� ����
bool checkGameTimeLimit(time_t startTime) {
    time_t currentTime = time(NULL);
    return difftime(currentTime, startTime) >= GAME_TIME_LIMIT;
}

int updateTimeAndGauge(time_t startTime, int* currentGauge) {
    time_t currentTime = time(NULL); // ���� �ð� ��������
    *currentGauge = difftime(currentTime, startTime) * GAUGE_SPEED;

    if (*currentGauge > MAX_GAUGE) {
        *currentGauge = MAX_GAUGE; // �������� �ִ밪�� ���� �ʵ��� ����
    }

    return (int)difftime(currentTime, startTime); // ��� �ð� ��ȯ
}


void mainScreen() { //���ΰ���
    // �������� �ʱ�ȭ
    a = 0; // 0: �� �����, 1: ����� //���ΰ��� ���۽� �վ����� �����ϱ� ���� �ʱⰪ 1�� ����.
    random_function = 0; // ������ ������
    gfSee = 0; // ����ģ�� ���ƺô��� ����. 0 �� �� �� ��, 1 �� �� ��.
    gfTime = 0; // ����ģ���� ���ƺ��� �ִ� �ð�
    score = 0; // ����
    
 // �ð� ������ ���� ���� ����
    int currentGauge = 0; // �ʱ� ������ ��
    time_t startTime, currentTime;
     
    //���� ���� �ð� ���
    startTime = time(NULL);
    int elapsedTime = 0; // ��� �ð�
    
    while (1)
    {
        elapsedTime = updateTimeAndGauge(startTime, &currentGauge);

        a = 0; // �ǻǸ� �ѹ��� ���� �� �� �ֵ��� �Ź� �ʱ�ȭ

        // Ű �Է� Ȯ��
        if (kbhit()) {
            keyControl();
        }

        mainDraw();
        //loveGauge();
        random(); // gfSee = 0 �� ���� �������� gfSee = 1 �� ����

        if (gfSee == 1) {
            girlFriendTime(); // gfSee = 1 �� ���� ���� gfSee 1�� �÷� 5�� �� gfSee = 0 ���� ����
        }
        
        handleKissEvent();
        Info(elapsedTime, score);


        Sleep(700);


           // ���� ���� ����
        if (elapsedTime >= GAME_TIME_LIMIT) {
            break;

        }
    }
       
    End();
    return 0;

    }

