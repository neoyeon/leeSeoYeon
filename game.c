#include "game.h"
#include "header.h"
#pragma comment(lib, "winmm.lib") //뽀뽀소리 내려면 필요한 코드

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

//전역변수로 손잡기 상태 추가
int a = 1; // 0: 손 안잡기, 1: 손잡기 //메인게임 시작시 손안잡기로 설정하기 위해 초기값 1로 설정.
int random_function = 0; // 난수의 나머지
int gfSee = 0; // 여자친구 돌아봤는지 여부. 0 일 때 안 봄, 1 일 때 봄.
int gfTime = 0; // 여자친구가 돌아보고 있는 시간
int score = 0; // 점수

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
        //mainDraw(); // 상태가 변경될 때마다 화면 갱신 //
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


#include <stdio.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

void drawBBO() {
    int textHeight = 31; // 텍스트의 높이 (대략적인 줄 수)
    int paddingTop = SCREEN_HEIGHT - textHeight; // 위쪽에 추가할 줄바꿈 개수

    for (int i = 0; i < paddingTop; i++) {
        printf("\n"); // 위쪽에 빈 줄 추가
    }

    printf(
        "            .;;;;                                                                              \n"
        "          ,=@@@@@@;.                                 .,,,,                                     \n"
        "         .@@@@@@@@@@                                 @@@@@@@                                   \n"
        "        ,@@@@@@@@@@@@                              :@@@@@@@@@=                                 \n"
        "       -@@@@@@@@@@@@@@.                           ~@@@@@@@@@@@!                                \n"
        "       *@@@@@@@@@@@@@@~                          -@@@@@@@@@@@@@!                               \n"
        "       @@@@@@@@!.....=@                          @@@@@@@@@@@@@@@                               \n"
        "       @@@@@@@@       !                         ~~~@@@@@@@@@@@@@!                              \n"
        "      !@@@@*           !                        !       @@@@@@@@$                              \n"
        "      !@@@@;     ..  ,* !                      !      . @@@@@@@@$                              \n"
        "       @@@@;      '''   !                      ! *...~  ,,,@@@@@@                              \n"
        "       @@@@$            !                      !           ;@@@@@                              \n"
        "       *@@@@@~.         !                      !           ;@@@@@                              \n"
        "       ~@@@@@@          ---------)) ((---------          ,,;@@@@@                              \n"
        "        :@@@@@          ---------)) ((---------           !@@@@@@                              \n"
        "         ;@@@@          !                      !          @@@@@@@@                             \n"
        "          !#@      -!                           !!-      ~@@@@@@@@                             \n"
        "            .*@@:@              *@@; ;@@*           :   -@@@@@@@@                              \n"
        "            *    @=            *@@@@@@@@@*           : =$@@@@@@@@@                             \n"
        "          ~;;;:;.;,;             *@@@@@*                -@@@@@@@@@                             \n"
        "         ,@.      .;,             *@@@*              =  -@@@@@@@@@                             \n"
        "        *  ;$    #~  #~            .@.             !*   -@@@@@@@@@~                            \n"
        "      !~     ~~~~     ,~**                       *~..~**=@@@@@@@@@*                            \n"
        "      $                   !;                             @@@@@@@@@@                            \n"
        "      $                    -.                            @@@@@@@@@@!                           \n"
        "      --                    #                            .@@@@@@@@@!                           \n"
        "       :                    :.                           @@@@@@@@@@                            \n"
    );
}

void drawNotBBO() {
    int textHeight = 31; // 텍스트의 높이
    int paddingTop = SCREEN_HEIGHT - textHeight; // 위쪽에 추가할 줄바꿈 개수

    for (int i = 0; i < paddingTop; i++) {
        printf("\n"); // 위쪽에 빈 줄 추가
    }

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


// 메인 화면 출력 함수
void mainDraw() {
    system("cls");

    // a의 값에 따라 적절한 함수 호출
    if (a == 0) {
        drawNotBBO(); // a가 0일 때 호출
    }
    else if (a == 1) {
        BBOSound();
        drawBBO();// a가 1일 때 호출
    }
}
//뽀뽀소리
void BBOSound() {
    PlaySound(TEXT("KissSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// 여자친구 보고 있는 모습
void girlfriend_see() {

    int x = 29;
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

    /*gotoxy(x, y + 22);
    printf(" $                 ,.\n");

    gotoxy(x, y + 23);
    printf(" .                 ~,\n");

    gotoxy(x, y + 24);
    printf(",                  ,.\n");

    gotoxy(x, y + 25);
    printf("=                   ,\n");*/

}


// 여자친구 뒷모습
void girlfriend_back() {
    int x = 29;
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

    /*   gotoxy(x, y + 22);
    printf(" $                 ,.\n");

    gotoxy(x, y + 23);
    printf(" .                 ~,\n");

    gotoxy(x, y + 24);
    printf(",                  ,.\n");

    gotoxy(x, y + 25);
    printf("=                   ,\n");*/
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
    if (gfSee == 0) { // 여친이 보고 있지 않을 때
        girlfriend_back();

        srand(time(NULL)); // 함수 실행할 때마다 새로운 난수!를 뽑음
        random_function = rand() % 100;

        if (random_function < 50) {  // 숫자 확률로 뒤돌아봄
            gfSee = 1;
        }
    }
}

void girlFriendTime() {
    gfTime += 1; // 여친이 보고 있는 시간 1씩 추가

    girlfriend_see();

    if (a == 1) {  // 손을 잡고 있는 상태라면
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
    printf("들켰다!\n");
    exit(0);
}


/*
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
*/



// 뽀뽀 이벤트 처리 함수
void handleKissEvent() {
    // 점수 증가
    score++;
   // gotoxy(70, 1);
   // printf("현재 점수: %d\n", score); // 점수 출력
}



// 엔딩1
void End1() {
    printf("흠 먼가 아쉬운데엥~\n");
}

// 엔딩2
void End2() {
    printf("역시~ 자기는 나밖에 없지?\n");
}

// 기본 엔딩 (Optional)
void DefaultEnding() {
    printf("오빠 집중 제대로 안하네? 저 여자 봤지\n");
}

void End() {
    system("cls"); // 콘솔 화면 지우기

    if (score <= 10) {
        DefaultEnding(); // 점수가 10 이하
    }
    else if (score <= 15) {
        End2(); // 점수가 11 이상 15 이하
    }
    else {
        End1(); // 점수가 16 이상
    }
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

//시간 점수 표시
void Info(int elapsedTime, int score) {
    gotoxy(70, 3); // 시간 표시
    printf("현재 시간: %d초\n", elapsedTime);

    gotoxy(70, 4); // 점수 표시
    printf("점수: %d\n", score);
}

//게임 종료 조건
bool checkGameTimeLimit(time_t startTime) {
    time_t currentTime = time(NULL);
    return difftime(currentTime, startTime) >= GAME_TIME_LIMIT;
}

int updateTimeAndGauge(time_t startTime, int* currentGauge) {
    time_t currentTime = time(NULL); // 현재 시간 가져오기
    *currentGauge = difftime(currentTime, startTime) * GAUGE_SPEED;

    if (*currentGauge > MAX_GAUGE) {
        *currentGauge = MAX_GAUGE; // 게이지가 최대값을 넘지 않도록 제한
    }

    return (int)difftime(currentTime, startTime); // 경과 시간 반환
}


void mainScreen() { //메인게임
    // 전역변수 초기화
    a = 0; // 0: 손 안잡기, 1: 손잡기 //메인게임 시작시 손안잡기로 설정하기 위해 초기값 1로 설정.
    random_function = 0; // 난수의 나머지
    gfSee = 0; // 여자친구 돌아봤는지 여부. 0 일 때 안 봄, 1 일 때 봄.
    gfTime = 0; // 여자친구가 돌아보고 있는 시간
    score = 0; // 점수
    
 // 시간 측정을 위한 변수 선언
    int currentGauge = 0; // 초기 게이지 값
    time_t startTime, currentTime;
     
    //게임 시작 시간 기록
    startTime = time(NULL);
    int elapsedTime = 0; // 경과 시간
    
    while (1)
    {
        elapsedTime = updateTimeAndGauge(startTime, &currentGauge);
        //handleKissEvent();
        a = 0; // 뽀뽀를 한번씩 끊어 할 수 있도록 매번 초기화
        // 키 입력 확인
        if (kbhit()) {
            keyControl();
            handleKissEvent();
        }
        
        mainDraw();
        //loveGauge();
        random(); // gfSee = 0 일 때만 랜덤으로 gfSee = 1 로 만듦

        if (gfSee == 1) {
            girlFriendTime(); // gfSee = 1 일 때만 변수 gfSee 1씩 늘려 5일 때 gfSee = 0 으로 만듦
        }
        
        

        Info(elapsedTime, score);


        Sleep(700);


           // 게임 종료 조건
        if (elapsedTime >= GAME_TIME_LIMIT) {
            break;

        }
    }
       
    End();
    return 0;

    }

