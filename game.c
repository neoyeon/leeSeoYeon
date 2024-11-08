#include "game.h"

//전역변수로 손잡기 상태 추가
int a = 0; // 0: 손 안잡기, 1: 손잡기
int see = 0;  // 전역변수로 여자친구가 보고 있는지 상태 저장

int keyControl() {
    if (kbhit()) {
        char temp = getch();
        if (temp == ' ') { // 스페이스바 입력 처리를 최우선으로
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

// 게임 실행 함수들 //
void start() { //시작화면
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            mainScreen();
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
    printf("                  [ 게임규칙 ]\n\n");
    printf("      여자친구 몰래 다른 여자의 손을 잡자!\n\n"); //괄호 안 게임규칙 내용 추가
    printf("      여자친구에게 들키지 않고 게이지를 끝까지 채우자\n\n");
    printf("      스페이스바 한번 클릭: 손 잡기 \n\n");
    printf("      스페이스바 한번 더 클릭: 손 떼기 \n\n");
    printf("      스페이스바를 누르면 초기화면으로 이동합니다.");

    while (1) {
        if (keyControl() == SUBMIT) {
            break;
        }
    }
}

void mainDraw() {
    // 항상 배경 먼저 그리기
    system("cls");

    // 기본 배경 그리기
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
        // 손잡기 상태일 때 추가로 손과 하트 그리기
        //손의 좌표와 출력
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

        // 하트의 좌표와 출력
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

        // 여자친구의 모습을 계속 그리기
        if (see == 1) {
            girlfriend_see();
            random();// 여자친구가 앞을 보고 있는 경우
        }
        else {
            girlfriend_back();
            random();// 여자친구가 뒤돌아본 경우
        }
    }
    else {
        // 손 안잡기 상태일 때는 random() 함수 호출
        random();
    }
}


void random() {
    srand(time(NULL));  // 난수 초기화
    while (1) {
        // 0 또는 1 랜덤 선택 (0: 뒤돌아봄, 1: 앞을 봄)
        int random_function = rand() % 2;
        if (random_function == 0) {
            see = 0;  // 뒤돌아본 상태
            girlfriend_back();
            randomtime(1);  // 뒤돌아본 상태에서의 대기 시간
        }
        else {
            see = 1;  // 앞을 보는 상태
            girlfriend_see();
            randomtime(0);  // 앞을 보는 상태에서의 대기 시간
        }

        // 게임 오버 조건 체크 (손을 잡고 있는데 여자친구가 보고 있으면)
        if (a == 1 && see == 1) {
            system("cls");
            gotoxy(40, 15);  // 화면 중앙에 표시
            printf("들켰다!\n");
            Sleep(2000);  // 2초 대기
            break;
        }

        // 키 입력 체크
        if (kbhit()) {
            keyControl();
        }
    }
}

void randomtime(int is_looking_back)
{
    int sleep_time;
    if (is_looking_back) {
        // 뒤돌아본 상태일 때는 1~3초 동안 유지
        sleep_time = (rand() % 2000) + 1000;  // 1000ms(1초) ~ 3000ms(3초)
    }
    else {
        // 앞을 보고 있을 때는 2~6초 후에 뒤돌아봄
        sleep_time = (rand() % 4000) + 2000;  // 2000ms(2초) ~ 6000ms(6초)
    }
#ifdef _WIN32
    Sleep(sleep_time);
#else
    sleep(sleep_time);
#endif
}

// 여자친구 뒷모습 함수 수정
void girlfriend_back() {
    // 기존 좌표에 그리기 전에 해당 영역 지우기
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

// 여자친구가 보는 모습 함수 수정
void girlfriend_see() {
    // 기존 좌표에 그리기 전에 해당 영역 지우기
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
// 게이지 구현
void loveGauge() {
    int x = 10; // 게이지 위치 x
    int y = 27; // 게이지 위치 y
    int currentGauge = 0; // 초기 게이지 값

    while (1) {
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
        //printf("                                                                                "); // 게이지 초기화

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
            break;
        }

        // 키 입력 확인
        if (kbhit()) {
            keyControl();
        }

        Sleep(300); // 게이지 변화 속도를 더 천천히
    }
}