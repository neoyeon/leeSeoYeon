#include "game.h"

//전역변수로 손잡기 상태 추가
int a = 0; // 0: 손 안잡기, 1: 손잡기

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
//

int see = 0;
void random() {
    srand(time(NULL)); // 난수 초기화
    //maindraw();
    while (1) { // 무한 루프

        int random_function = rand() % 2; // 0 또는 1 랜덤 선택
        if (random_function == 0) {
            girlfriend_back();


        }
        else {
            girlfriend_see();
        }
        keyControl(); // 사용자 입력을 받기 위해 호출
        randomtime();
        mainDraw();

        // a와 see의 값이 같다면 종료   
        randomtime();
        if (a == see) {
            break; // 조건이 만족되면 루프 종료
        }

    }

    printf("들켰다!\n");

}

void randomtime()// 랜덤한 시간 간격 생성 (1초에서 3초 사이)
{
    //maindraw();
    int sleep_time = rand() % 5 + 1; // 1초에서 5초 사이의 랜덤 값
#ifdef _WIN32
    Sleep(sleep_time * 1000); // Windows의 경우
#else
    sleep(sleep_time); // POSIX 시스템의 경우
#endif
}

//메인화면 출력하기
void mainDraw() {
    if (a == 1) {
        // 손잡기 상태일 때 출력할 내용
        //printf("현재 상태: 손잡기\n");
        a = 1;
        //printf("\033[H\033[J"); // 콘솔 화면 지우기 (ANSI 코드)
        //system("cls");

        //콘솔화면보다 출력그림이 많아서 위아래 잘랐음. 추후 수정 필요
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
       
       
        //손의 좌표와 출력
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


        // 하트의 좌표와 출력
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
        // 손 안잡기 상태일 때 출력할 내용
        //printf("현재 상태: 손 안잡기\n");
        //printf("\033[H\033[J"); // 콘솔 화면 지우기 (ANSI 코드)
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
//여자친구 뒷모습 출력 함수
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
            break;
        }

        // 키 입력 확인
        if (kbhit()) {
            keyControl();
        }

        Sleep(300); // 게이지 변화 속도를 더 천천히
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