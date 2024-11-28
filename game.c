#include "game.h"
#include "header.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 80

//전역변수로 손잡기 상태 추가
int a = 1; // 0: 손 안잡기, 1: 손잡기 //메인게임 시작시 손안잡기로 설정하기 위해 초기값 1로 설정.
int random_function = 0; //난수의 나머지

// 그래픽 요소를 표현하기 위한 구조체
typedef struct {
    Vector3* points;
    int num_points;
    const char* symbol;
} GraphicElement;

// 화면 좌표로 변환하는 함수
void transformAndDraw(Vector3* point, Matrix3x3 transform) {
    Vector3 transformed = multiply_matrix_vector(transform, *point);
    gotoxy((int)transformed.x, (int)transformed.y);
}

//키 조종
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
    else if (temp == ' ') { //스페이스바(공백)
        a = (a == 0) ? 1 : 0; // 명확한 상태 전환
        //system("cls"); // 화면 깔끔하게 지우기
        mainDraw(); // 상태가 변경될 때마다 화면 갱신 //
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
    printf("> 게임시작 ");
    gotoxy(40, 27);
    printf("게임규칙 ");
    gotoxy(40, 28);
    printf("  종료 ");
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
    printf("                   [ 게임규칙 ]\n\n");
    printf("       여자친구 몰래 다른 여자의 손을 잡자!\n\n"); //괄호 안 게임규칙 내용 추가
    printf("       여자친구에게 들키지 않고 게이지를 끝까지 채우자\n\n");
    printf("       스페이스바 한번 클릭: 손 잡기 \n\n");
    printf("       스페이스바 한번 더 클릭: 손 떼기 \n\n");
    printf("       스페이스바를 누르면 초기화면으로 이동합니다.");

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
        "          ,=@@@@@@;.               .,,,,                                                       ",
        "         .@@@@@@@@@@               @@@@@@@                                                     ",
        "        ,@@@@@@@@@@@@            :@@@@@@@@@=                                                   ",
        "       -@@@@@@@@@@@@@@.         ~@@@@@@@@@@@!                                                  ",
        "       *@@@@@@@@@@@@@@~        -@@@@@@@@@@@@@!                                                 ",
        "       @@@@@@@@!.....=@        @@@@@@@@@@@@@@@                                                 ",
        "       @@@@@@@@       !       ~~~@@@@@@@@@@@@@!                                                ",
        "      !@@@@*           !      !       @@@@@@@@$                                                ",
        "      !@@@@;     ..  ,* !    !      . @@@@@@@@$                                                ",
        "       @@@@;      '''   !    ! *...~  ,,,@@@@@@                                                ",
        "       @@@@$            !    !           ;@@@@@                                                ",
        "       *@@@@@~.         !    !           ;@@@@@                                                ",
        "       ~@@@@@@           )  (          ,,;@@@@@                                                ",
        "        :@@@@@           )  (           !@@@@@@                                                ",
        "         ;@@@@          !    !          @@@@@@@@                                               ",
        "          !#@      -! ,,  ,,  !!-      ~@@@@@@@@                                               ",
        "            .*@@:@    *@@, ,@@*    :   -@@@@@@@@                                               ",
        "            *    @=  *@@@@@@@@@*    : =$@@@@@@@@@                                              ",
        "          ~;;;:;.;,;   =@@@@@*         -@@@@@@@@@                                              ",
        "         ,@.      .;,   .@@@.       =  -@@@@@@@@@                                              ",
        "        *  ;$    #~  #~  .@.      !*   -@@@@@@@@@~                                             ",
        "      !~     ~~~~     ,~**     *~..~**=@@@@@@@@@*                                              ",
        "      $                   !;           @@@@@@@@@@                                              ",
        "      $                    -.          @@@@@@@@@@!                                             ",
        "      --                    #          .@@@@@@@@@!                                             ",
        "       :                    :.         @@@@@@@@@@                                              "
    };

    // y 좌표를 40부터 시작하도록 조정
    for (int i = 0; i < 24; i++) {
        Vector3 pos = { 0, i + 40, 1 }; // y 좌표가 40부터 시작
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
            "     ,#@@@@@@@,                      ,,,,                                                     ",
            "    ~@@@@@@@@@@;                   -@@@@@@=                                                   ",
            "   :@@@@@@@@@@@@!                 #@@@@@@@@@~                                                 ",
            "   @@@@@@@@@@@@@#                #@@@@@@@@@@@-                                                ",
            "  #@@@@@@@@@@@@@@@              @@@@@@@@@@@@@@.                                               ",
            "  #@@@@@@@@@@@@@@@             -@@@@@@@@@@@@@@!                                               ",
            " .@@@@@@@@@@@@@@@@-            =@@@@@@@@@@@@@@@                                               ",
            " .@@@@@@@@@@@@@@@@~            @@@@@@@@@@@@@@@@.                                              ",
            " .@@@@@@@@@@@@@@@@~            @@@@@@@@@@@@@@@@#                                              ",
            " .@@@@@@@@@@@@@@@@~            @@@@@@@@@@@@@@@@#                                              ",
            "  #@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@#                                              ",
            "  $@@@@@@@@@@@@@@=             @@@@@@@@@@@@@@@@$                                              ",
            "   @@@@@@@@@@@@@@              @@@@@@@@@@@@@@@@#                                              ",
            "   !@@@@@@@@@@@@-             ,@@@@@@@@@@@@@@@@#                                              ",
            "    *@@@@@@@@@@;               @@@@@@@@@@@@@@@@#                                              ",
            "      =@@@@@@=,                @@@@@@@@@@@@@@@@#                                              ",
            "       :~@@;,                  @@@@@@@@@@@@@@@@#                                              ",
            "       ~    -                  @@@@@@@@@@@@@@@@,                                              ",
            "      ;;;: -!;;                @@@@@@@@@@@@@@@@                                               ",
            "    .#    ,   ,*               @@@@@@@@@@@@@@@@                                               ",
            "   ~!-$       -;=              @@@@@@@@@@@@@@@@                                               ",
            " *~.   ~-***.~   ~*           ~@@@@@@@@@@@@@@@@                                               ",
            ";                  !:      .:!-@@@@@@@@@@@@@@@@!:                                             ",
            "                     =:   .!   @@@@@@@@@@@@@@@@  $                                            ",
            "                      *   !    @@@@@@@@@@@@@@@*                                               ",
            "                      *   !    @@@@@@@@@@@@@@@!                                               "

    };

    // y 좌표를 40부터 시작하도록 조정
    for (int i = 0; i < 24; i++) {
        Vector3 pos = { 0, i + 40, 1 }; // y 좌표가 40부터 시작
        Vector3 transformed = multiply_matrix_vector(transform, pos);
        gotoxy((int)transformed.x, (int)transformed.y);
        puts(screen1[i]);
    }
}

// 메인 화면 출력 함수
void mainDraw() {
    system("cls");

    // a의 값에 따라 적절한 함수 호출
    if (a == 0) {
        drawNotBBO(0.0f, 0.0f, 1.0f); // a가 0일 때 호출
    }
    else if (a == 1) {
        drawBBO(0.0f, 0.0f, 1.0f);// a가 1일 때 호출
    }
}

#define GIRLFRIEND_HEIGHT 10
#define GIRLFRIEND_WIDTH 15

// 여자친구 뒷모습 배열
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

// 여자친구 옆모습 배열
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
    // srand(time(NULL)) 제거
    random_function = rand() % 100;

    if (random_function < 30) {  // 30% 확률로 뒤돌아봄
        girlfriend_see();
        if (a == 1) {  // 손을 잡고 있는 상태라면
            badEnd();
            return;
        }
        Sleep(1500);  // 1.5초 대기
        girlfriend_back();  // 다시 뒤돌아섬
    }
    else {
        girlfriend_back();
    }
}

void badEnd() {
    system("cls");
    printf("들켰다!\n");
    exit(0);
}

int currentGauge = 0; // 초기 게이지 값

// 게이지 구현
void loveGauge() {
    int x = 10; // 게이지 위치 x
    int y = 27; // 게이지 위치 y


    // 틀 그리기
    gotoxy(x - 2, y - 1);
    printf("====================================================================================\n");
    gotoxy(x - 2, y);
    printf("||");
    gotoxy(100 - x, y);
    printf("||");
    gotoxy(x - 2, y + 1);
    printf("====================================================================================\n");

    // 게이지 업데이트
    gotoxy(x, y);
    printf("                                                                                "); // 게이지 초기화

    if (a == 1) {
        // 손잡기 상태일 때 게이지 증가
        if (currentGauge < 80) {
            currentGauge += 1; // 게이지 증가
        }
    }
    else {
        // 손 안잡기 상태일 때 게이지 감소
        if (currentGauge > 0) {
            currentGauge -= 1; // 게이지 감소
        }
    }

    // 게이지 그리기
    gotoxy(x, y);
    for (int i = 0; i < currentGauge; i++) {
        printf("#");
    }

    // 게이지가 다 찼을 때
    if (currentGauge >= 80) {
        gotoxy(30, 10);
        printf("다음 스테이지");
        return 0;
    }

    // 키 입력 확인
    if (kbhit()) {
        keyControl();
    }

    Sleep(300); // 게이지 변화 속도를 더 천천히

}



// 게임 실행 함수들 //
void start() { //시작화면
    while (1) {
        titleDraw();
        int menuCode = menuDraw();

        if (menuCode == 0) {
            return 0;
        }
        else if (menuCode == 1) {
            infoDraw(); // 게임정보  
        }
        else if (menuCode == 2) {
            return 0; // 종료
        }
        system("cls");
    }
    return 0;
}

void mainScreen() { //메인게임
    srand(time(NULL));  // 게임 시작 시 한 번만 난수 초기화
    while (1)
    {
        mainDraw();
        loveGauge();
        random();
    }
    return 0;
}