#include "game.h"
#include "header.h"

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

//���������� ����� ���� �߰�
int a = 1; // 0: �� �����, 1: ����� //���ΰ��� ���۽� �վ����� �����ϱ� ���� �ʱⰪ 1�� ����.
int random_function = 0; // ������ ������
int gfSee = 0; // ����ģ�� ���ƺô��� ����. 0 �� �� �� ��, 1 �� �� ��.
int gfTime = 0; // ����ģ���� ���ƺ��� �ִ� �ð�

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
        mainDraw(); // ���°� ����� ������ ȭ�� ���� //
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
    Matrix3x3 transform = identity_matrix();
    transform = multiply_matrices(transform, translation_matrix(base_x, base_y));
    transform = multiply_matrices(transform, scale_matrix(scale, scale));


    const char* screen1[] = {
         "        ;;;;.                                                                                 ",
         "     ,#@@@@@@@,                                        ,,,,                                   ",
         "    ~@@@@@@@@@@;                                     -@@@@@@=                                 ",
         "   :@@@@@@@@@@@@!                                   #@@@@@@@@@~                               ",
         "   @@@@@@@@@@@@@#                                  #@@@@@@@@@@@-                              ",
         "  #@@@@@@@@@@@@@@@                                @@@@@@@@@@@@@@.                             ",
         "  #@@@@@@@@@@@@@@@                               -@@@@@@@@@@@@@@!                             ",
         " .@@@@@@@@@@@@@@@@-                              =@@@@@@@@@@@@@@@                             ",
         " .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@.                            ",
         " .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@#                            ",
         " .@@@@@@@@@@@@@@@@~                              @@@@@@@@@@@@@@@@#                            ",
         "  #@@@@@@@@@@@@@@@                               @@@@@@@@@@@@@@@@#                            ",
         "  $@@@@@@@@@@@@@@=                               @@@@@@@@@@@@@@@@$                            ",
         "   @@@@@@@@@@@@@@                                @@@@@@@@@@@@@@@@#                            ",
         "   !@@@@@@@@@@@@-                               ,@@@@@@@@@@@@@@@@#                            ",
         "    *@@@@@@@@@@;                                 @@@@@@@@@@@@@@@@#                            ",
         "      =@@@@@@=,                                  @@@@@@@@@@@@@@@@#                            ",
         "       :~@@;,                                    @@@@@@@@@@@@@@@@#                            ",
         "       ~    -                                    @@@@@@@@@@@@@@@@,                            ",
         "      ;;;: -!;;                                  @@@@@@@@@@@@@@@@                             ",
         "    .#    ,   ,*                                 @@@@@@@@@@@@@@@@                             ",
         "   ~!-$       -;=                                @@@@@@@@@@@@@@@@                             ",
         " *~.   ~-***.~   ~*                             ~@@@@@@@@@@@@@@@@                             ",
         ";                  !:                        .:!-@@@@@@@@@@@@@@@@!:                           ",
         "                     =:                     .!   @@@@@@@@@@@@@@@@  $                          ",
         "                      *                      !    @@@@@@@@@@@@@@@*                            ",
         "                      *   !                       @@@@@@@@@@@@@@@!                            "

    };

    // y ��ǥ�� 40���� �����ϵ��� ����
    for (int i = 0; i < 24; i++) {
        Vector3 pos = { 0, i + 40, 1 }; // y ��ǥ�� 40���� ����
        Vector3 transformed = multiply_matrix_vector(transform, pos);
        gotoxy((int)transformed.x, (int)transformed.y);
        puts(screen1[i]);
    }
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

#define GIRLFRIEND_HEIGHT 10
#define GIRLFRIEND_WIDTH 15

// ����ģ�� �޸�� �迭
const char girlfriend_back_art[GIRLFRIEND_HEIGHT][GIRLFRIEND_WIDTH] = {
    "       ,~.   ",
    "      . ! ;   ",
    "    .*,..*.=  ",
    "  ,-      ~..~",
    " ;          !~",
    "         .,   ",
    " l        .~  ",
    " .       .-   ",
    "   *,.,=.     ",
    " ~~~:~~~~$~~~ "
};

// ����ģ�� ����� �迭
const char girlfriend_side_art[GIRLFRIEND_HEIGHT][GIRLFRIEND_WIDTH] = {
    "       ,~.   ",
    "      . ! ;   ",
    "    .*,..*.=  ",
    "  ,-      ~..~",
    " ;   /      !~",
    " =   =    .,  ",
    " l        .~  ",
    " .       .-   ",
    "   *,.,=.     ",
    " ~~~:~~~~$~~~ "
};

void display_array(const char art[GIRLFRIEND_HEIGHT][GIRLFRIEND_WIDTH], int x, int y) {
    for (int i = 0; i < GIRLFRIEND_HEIGHT; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < GIRLFRIEND_WIDTH; j++) {
            printf("%c", art[i][j]);
        }
        printf("\n");
    }
}

void girlfriend_back() {
    display_array(girlfriend_back_art, 27, 1);
}

void girlfriend_see() {
    display_array(girlfriend_side_art, 27, 1);
}

void random() {
    if (gfSee = 0) {
        srand(time(NULL)); // �Լ� ������ ������ ���ο� ������ ����
        random_function = rand() % 100;

        if (random_function < 20) {  // ���� Ȯ���� �ڵ��ƺ�
            gfSee = 1;
            girlfriend_see();

            if (a == 1) {  // ���� ��� �ִ� ���¶��
                badEnd();
                return;
            }
        }
    }
}

void girlFriendTime() {
    if (gfSee = 1) {
        gfTime += 1;
        girlfriend_see();

        if (gfTime = 5) {
            girlfriend_back();
            gfSee = 0;
        }
    }
}


void badEnd() {
    system("cls");
    printf("���״�!\n");
    exit(0);
}

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



int score = 0;  
void End1() {
    printf("���� ���� ����� ���ϳ�? �����ں��� \n");
    }

void End2() {
    printf("����~ �ڱ�� ���ۿ� ����? \n");
}



// �ǻ� �̺�Ʈ ó�� �Լ�
void handleKissEvent() {
    // �����̽��ٰ� ���ȴ��� Ȯ��
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        score++; // ���� 1�� ����
        gotoxy(70, 1);
       // printf("���� ����: %d\n", score); // ���� ���
        Sleep(300); // �ߺ� �Է� ���� ��� �ð�
    }
}


void displayScore() {
    gotoxy(2, 2); // ȭ�� ���� ��ܿ� ���� ǥ��
    printf("����: %d", score);
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
    srand(time(NULL));  // ���� ���� �� �� ���� ���� �ʱ�ȭ


    //�����߰�
    // �ð� ������ ���� ���� ����
    int currentGauge = 0; // �ʱ� ������ ��
    time_t startTime, currentTime;

    // ���� ���� �ð� ���
    startTime = time(NULL);

    while (1)
    {
        // ���� �ð� ���
        currentTime = time(NULL);
        currentGauge = difftime(currentTime, startTime) * GAUGE_SPEED;
        if (currentGauge > MAX_GAUGE) {
            currentGauge = MAX_GAUGE;
        }

        mainDraw();
        //loveGauge();
        random();
        girlFriendTime();
        handleKissEvent();
        gotoxy(70, 3);
        printf("���� �ð�: %d��\n", (int)difftime(currentTime, startTime));
        gotoxy(70, 4);
        printf("����: %d\n", score); // ������ ǥ���ϴ� �κ� (score ������ ������Ʈ�ϴ� ���� �߰� �ʿ�)


        Sleep(100);

        a = 0; // �ǻǸ� �ѹ��� ���� �� �� �ֵ���
        drawNotBBO(0.0f, 0.0f, 1.0f);

       

        /* ������ �׸���
        drawGauge(10, 5, currentGauge);*/

        // ���� ���� �ð� �ʰ� Ȯ��
        if (difftime(currentTime, startTime) >= GAME_TIME_LIMIT) {
            system("cls");
            printf("\n\n");
            printf("       [ ���� ���� ]\n\n");
            printf("       ���� �ð� 60�ʰ� �ʰ��Ǿ����ϴ�!\n\n");
            printf("       ����� Ȯ���ϼ���.\n");
            //(500);
            break; // ���� ����
        }

    }
    system("cls");
    displayScore();
    {if (score >= 20) {
        End1();
    }
    else if (score >= 10) {
        End2();
    }}
    return 0;

    }


