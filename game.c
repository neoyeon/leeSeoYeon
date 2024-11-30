#include "game.h"
#include "header.h"

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

//전역변수로 손잡기 상태 추가
int a = 1; // 0: 손 안잡기, 1: 손잡기 //메인게임 시작시 손안잡기로 설정하기 위해 초기값 1로 설정.
int random_function = 0; // 난수의 나머지
int gfSee = 0; // 여자친구 돌아봤는지 여부. 0 일 때 안 봄, 1 일 때 봄.
int gfTime = 0; // 여자친구가 돌아보고 있는 시간

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
        drawNotBBO(0.0f, 10.0f, 1.0f); // a가 0일 때 호출
    }
    else if (a == 1) {
        drawBBO(0.0f, 10.0f, 1.0f);// a가 1일 때 호출
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
    if (gfSee = 0) {
        srand(time(NULL)); // 함수 실행할 때마다 새로운 난수를 뽑음
        random_function = rand() % 100;

        if (random_function < 20) {  // 숫자 확률로 뒤돌아봄
            gfSee = 1;
            girlfriend_see();

            if (a == 1) {  // 손을 잡고 있는 상태라면
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



int score = 0;  
void End1() {
    printf("오빠 집중 제대로 안하네? 저여자봤지 \n");
    }

void End2() {
    printf("역시~ 자기는 나밖에 없지? \n");
}



// 뽀뽀 이벤트 처리 함수
void handleKissEvent() {
    // 스페이스바가 눌렸는지 확인
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        score++; // 점수 1점 증가
        gotoxy(70, 1);
       // printf("현재 점수: %d\n", score); // 점수 출력
        Sleep(300); // 중복 입력 방지 대기 시간
    }
}


void displayScore() {
    gotoxy(2, 2); // 화면 좌측 상단에 점수 표시
    printf("점수: %d", score);
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


    //은진추가
    // 시간 측정을 위한 변수 선언
    int currentGauge = 0; // 초기 게이지 값
    time_t startTime, currentTime;

    // 게임 시작 시간 기록
    startTime = time(NULL);

    while (1)
    {
        // 현재 시간 계산
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
        printf("현재 시간: %d초\n", (int)difftime(currentTime, startTime));
        gotoxy(70, 4);
        printf("점수: %d\n", score); // 점수를 표시하는 부분 (score 변수를 업데이트하는 로직 추가 필요)


        Sleep(100);

        a = 0; // 뽀뽀를 한번씩 끊어 할 수 있도록
        drawNotBBO(0.0f, 0.0f, 1.0f);

       

        /* 게이지 그리기
        drawGauge(10, 5, currentGauge);*/

        // 게임 제한 시간 초과 확인
        if (difftime(currentTime, startTime) >= GAME_TIME_LIMIT) {
            system("cls");
            printf("\n\n");
            printf("       [ 게임 종료 ]\n\n");
            printf("       제한 시간 60초가 초과되었습니다!\n\n");
            printf("       결과를 확인하세요.\n");
            //(500);
            break; // 루프 종료
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


