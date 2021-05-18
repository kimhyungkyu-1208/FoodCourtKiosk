#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define FOODNUM 18
#define FAIL 0
//typedef struct _Food{
//    char food_name[4][19];
//    int price[4];
//}Food;    //후에 배열을 변경할때 쓰일 구조체
int menu[FOODNUM] = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0
};//전역배열, 메뉴 수량 저장
//순서대로 비빔, 된장, 김치, 돼지, 짬뽕, 짜장, 탕수, 볶음, 돈까, 초밥, 우동, 라멘, 크림, 토마토, 목살스테잌, 햄벜, 콜라, 사이다
int price[FOODNUM] = {
    7000,9000,11000,13000,
    7000,9000,11000,13000,
    7000,9000,11000,13000,
    7000,9000,11000,13000,
    1500,1500
};//전역배열, 메뉴 가격 저장
char foodName[FOODNUM][19] = {
    "비빔밥", "된장찌개", "김치찌개", "돼지국밥",
    "짬뽕", "짜장면", "탕수육", "볶음밥",
    "돈까스", "초밥", "우동", "라멘",
    "크림파스타", "토마토파스타", "목살스테이크", "햄버거",
    "콜라", "사이다"
};
int stock[4] = { 50,50,50,50 };//밥 간장 돼지고기 면
int sum_price = 0; //가격 합계
int dc_percent = 0;//회원 할인
int check = 0;
typedef struct _customerInfo
{
    char name[16];   //15자이하로 받기
    char age[4];
    char sex[2];    //M, F
    char phoneNumber[5]; //폰번호 뒤의 4자리, 3자리일 경우엔 맨앞에 'a'
    char grade[2];  //N(ew),S(ilver),G(old),D(iamond)
    int total;   //현재 달 결제 금액
} customerInfo;
int start_view(void);  //startView return:1->orderView, return 2: commandView
int order_view(void);
int command_view(void);
void korean(void);
void print_menu(void);
void check_menu(int i);
void chinese(void);
void japanese(void);
void western(void);
void beverage(void);
int payment_view(void);
void finalpayment_view(void);
int premenu_view(void);
void delete_view(void);
void manageModemenu(void);
int fileLine(FILE* f);
int makeMember(void);
int browseMember(void);
int setStock(void);
int changePrice(void);
void monthcheck(void);
customerInfo* idinfo(int k);
int login_view(customerInfo* info);
void typeOfFood(void);
//=============header.h====================//
//=============FoodCourt.c====================//
//int inpNum(int x, int y){   //숫자입력 받는 함수
//    char inp;
//    int num;
//    while(1){
//        inp = getchar();
//        fflush(stdin);
//        num = (int)inp-48;
//        if(num>=x && num<=y){
//            return num;
//        }
//        else
//            printf("다시 입력하세요\n");
//    }
//} //후에 scanf()를 다시 만들어서 보완하기 위해!! 아직 완벽하지 않아서 나중에 쓰일 함수
void typeOfFood() {
    printf("\n<음식 종류 선택>\n");
    printf("1. 한식\n2. 중식\n3. 일식\n4. 양식\n5. 음료\n6. 결제\n9. 이전 화면\n");
}
int start_view()            // 모드 선택
{
    int inpN;
    while (1) {
        printf("<모드 선택>\n1. 주문 모드\n2. 관리자 모드\n");
        scanf(" %d", &inpN);
        if (inpN == 1 || inpN == 2) { // 주문 모드, 관리자 모드 진입
            return inpN;
        }
        else
            printf("정상적인 입력이 아닙니다. 다시 입력하십시오.\n");
    }
}
int order_view()                // 주문 모드
{
    int inpN;
    while (1)
    {
        typeOfFood();
        scanf(" %d", &inpN);
        switch (inpN) {
        case 1: korean();    break;
        case 2: chinese();    break;
        case 3: japanese();    break;
        case 4: western();    break;
        case 5: beverage();    break;
        case 6: return inpN;    //paymentview()로 진입
        case 9: return 1;       // startview()로 진입
        default: printf("정상적인 입력이 아닙니다. 다시 입력하십시오.\n");
            break;  //다시 orderview실행
        }
    }
    return FAIL;   //비 정상 출력!!
}
int command_view()        // 관리자 모드
{
    int inpN;
    while (1)
    {
        printf("<관리자 모드>\n");
        printf("1. 회원 정보 입력 양식\n2. 회원 정보 열람\n3. 재고 수량 추가 입력\n4. 가격 변경 \n9. 이전 화면\n");
        rewind(stdin);
        scanf(" %d", &inpN);
        switch (inpN) {
        case 1: return inpN;     //makeMember()로 진입
        case 2: return inpN;     //browseMember()로 진입
        case 3: return inpN;     //setStock()로 진입
        case 4: return inpN;     //changePrice()로 진입
        case 9: return 9;        //startview()로 진입
        default: printf("정상적인 입력이 아닙니다. 다시 입력하십시오.\n");
            break; //다시 command_view() 실행
        }
    }
    return FAIL;   //비 정상 출력!!
}
void print_menu() {//약식으로 장바구니 보이게

    int number = 1; //메뉴 앞에 숫자 1. 2. 3.

    for (int i = 0; i < 18; i++) {
        if (menu[i] != 0) {
            printf("%d.%s\t\t\t%d\t%d원\n", number, foodName[i], menu[i], menu[i] * price[i]);
            number++;
        }
    }
}
void korean() {                    // 한식 메뉴 선택
    int inpN;
    while (1) {
        printf("<한식 메뉴 선택>\n");
        for (int i = 0; i < 4; i++) {
            printf("%d. %s: %d원\n", i + 1, foodName[i], price[i]);
        }
        printf("5. 선택 취소\n9. 이전 화면\n");

        // 메뉴 수량 배열 각 하나라도 1 이상의 정수가 있을 때 장바구니 출력
        for (int i = 0; i < 18; i++) {
            if (menu[i] > 0) {
                printf("=======================\n");
                print_menu();
                break;
            }
        }

        scanf(" %d", &inpN);

        switch (inpN) {
        case 1: check_menu(0);  break;
        case 2: check_menu(1);  break;
        case 3: check_menu(2);  break;
        case 4: check_menu(3);  break;
        case 5: delete_view();  break;
        case 9: return;
        }
    }
}
void chinese() {// 중식 메뉴 선택
    int a;
    while (1) {
        printf("<중식 메뉴 선택>\n");
        for (int i = 4; i < 8; i++)
            printf("%d. %s: %d원\n", i - 3, foodName[i], price[i]);

        printf("5. 선택 취소\n9. 이전 화면\n");

        // 메뉴 배열 각각에 1이상의 정수가 있을 때 장바구니 출력하기
        for (int i = 0; i < 18; i++)
        {
            if (menu[i] > 0) {
                printf("=======================\n");
                print_menu();
                break;
            }
        }

        scanf(" %d", &a);

        switch (a) {
        case 1: check_menu(4);  break;
        case 2: check_menu(5);  break;
        case 3: check_menu(6);  break;
        case 4: check_menu(7);  break;
        case 5: delete_view();  break;
        case 9: return;
        }
    }
}
void japanese() {                // 일식 메뉴 선택

    int a;
    while (1) {
        printf("<일식 메뉴 선택>\n");
        for (int i = 8; i < 12; i++)
            printf("%d. %s: %d원\n", i - 7, foodName[i], price[i]);
        printf("5. 선택 취소\n9. 이전 화면\n");

        // 메뉴 배열 각각에 1이상의 정수가 있을 때 장바구니 출력하기
        for (int i = 0; i < 18; i++) {
            if (menu[i] > 0) {
                printf("=======================\n");
                print_menu();
                break;
            }
        }

        scanf(" %d", &a);

        switch (a) {
        case 1: check_menu(8);  break;
        case 2: check_menu(9);  break;
        case 3: check_menu(10);  break;
        case 4: check_menu(11);  break;
        case 5: delete_view();    break;
        case 9: return;
        }
    }
}
void western() {                     // 양식 메뉴 선택
    int a;
    while (1) {
        printf("<양식 메뉴 선택>\n");
        for (int i = 12; i < 16; i++)
            printf("%d. %s: %d원\n", i - 11, foodName[i], price[i]);
        printf("5. 선택 취소\n9. 이전 화면\n");

        // 메뉴 배열 각각에 1이상의 정수가 있을 때 장바구니 출력하기
        for (int i = 0; i < 18; i++)
        {
            if (menu[i] > 0) {
                printf("=======================\n");
                print_menu();
                break;
            }
        }

        scanf(" %d", &a);

        switch (a) {
        case 1: check_menu(12); break;
        case 2: check_menu(13);  break;
        case 3: check_menu(14);  break;
        case 4: check_menu(15);  break;
        case 5: delete_view();    break;
        case 9: return;
        }
    }
}
void beverage() {              // 음료 메뉴 선택{
    int a;
    while (1) {
        printf("<음료 메뉴 선택>\n");
        printf("1. 콜라 \t%d원\n", price[16]);            // 콜라
        printf("2. 사이다\t%d원\n", price[17]);        // 사이다
        printf("5. 선택 취소\n9. 이전 화면\n");

        // 메뉴 배열 각각에 1이상의 정수가 있을 때 장바구니 출력하기
        for (int i = 0; i < 18; i++) {
            if (menu[i] > 0) {
                printf("=======================\n");
                print_menu();
                break;
            }
        }

        scanf(" %d", &a);

        switch (a) {
        case 1: check_menu(16); break;
        case 2: check_menu(17); break;
        case 5: delete_view();  break;
        case 9: return;
        }
    }
}


void check_menu(int i) { // 메뉴 종류 8개 이상이면 새로운 메뉴 못 고르게 하기

    check = 0;
    for (int a = 0; a < 18; a++) {
        if (menu[a] != 0) {
            check += 1;
        }
    }

    if (check >= 8) {
        if (menu[i] == 0) {
            printf("새로운 메뉴를 선택할 수 없습니다. 기존 메뉴 수량 추가만 가능합니다.\n");
        }
        else {
            menu[i] += 1;
        }
    }
    else {
        menu[i] += 1;
    }
}
int payment_view() {
    //음료 + 단품하나는 -1000원
    int dc_price = 0;
    int input = 0;
    int final_price = 0;
    while (1) {
        sum_price = 0;  //sumprice초기값 설정
        for (int i = 0; i < 18; i++) {
            if (menu[i] > 0)
                sum_price += menu[i] * price[i];
        }
        printf("결제모드\n");
        printf("\t원래금액\t\t\t%d원\n", sum_price);

        if (menu[16] != 0 || menu[17] != 0) {
            dc_price = (menu[16] + menu[17]) * -1000;
        }
        printf("\t할인금액\n");
        if (dc_percent != 0) {
            printf("\t\t회원할인\t\t%d원\n", -(sum_price * dc_percent));
        }
        printf("\t\t세트할인\t\t%d원\n", dc_price);
        final_price = sum_price + dc_price - (sum_price * dc_percent);
        sum_price = final_price;
        printf("\t결제금액\t\t\t%d원\n", final_price);
        printf("======================================================\n");

        printf("\t결제하실 금액은\t\t%d원입니다\n\n", final_price);
        printf("결제하실 방법을 선택하세요\n");
        printf("1.카드결제 2.현금결제 3.주문취소\n");

        scanf(" %d", &input);

        if (input >= 1 && input <= 3)
            return input;

        else printf("정상적인 입력이 아닙니다. 다시 입력하십시오.\n");
    }
}
void finalpayment_view() {
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf("%d원결제 완료되었습니다\n", sum_price);
    sleep(1);
    sum_price = 0;  //초기화!
    memset(menu, 0, sizeof(int) * 18);    //결제가 모두 완료 되었으니 초기화!
    //reset_mode();
}
int premenu_view() {
    while (1) {
        printf("\n장바구니\n");
        printf("\t메뉴\t\t수량\t가격(원)\n");
        print_menu();
        sum_price = 0;
        printf("===========================================\n");
        for (int i = 0; i < 18; i++) {
            sum_price += menu[i] * price[i];
        }
        printf("\t합계\t\t\t%d원\n", sum_price);
        printf("1.회원결제 2.비회원결제 3.메뉴삭제 4.추가주문\n");
        int input = 0;
        scanf(" %d", &input);
        if (input == 1) {
            return input;
        }
        else if (input == 2 || input == 4) {
            return input;   //최종 비회원 결제, order view()로 추가 주문 이동!
        }
        else if (input == 3) {
            delete_view();
        }
        else printf("정상적인 입력이 아닙니다. 다시 입력하십시오.");
    }
}
void delete_view() {
    //선택 취소 모드 -구본무 // 새로 함수
    while (1) {
        printf("<선택 취소>\n");
        printf("\t담은 메뉴\t\t수량\t가격(원)\n");
        print_menu();
        int input = 0;
        printf("\n\n9.이전 화면\n");
        printf("삭제할 메뉴의 번호를 입력하거나 9번을 입력하여 장바구니로 돌아가세요\n");
        scanf(" %d", &input);
        if (input == 9)
            return;//다시 장바구니 모드, 결제 모드

        else if (input >= 0 && input <= 8) {
            //메뉴삭제
            //ex) input=2이면 [1,0,0,3,0,2,....]에서 index=3의 수를 1만큼 감소
            int a = 0;
            for (int j = 0; j < 18; j++) {
                if (menu[j] != 0) {
                    a++;
                    if (a == input) {
                        if (menu[j] > 0)
                            menu[j] -= 1;
                        else
                            printf("삭제가 불가능합니다!\n");
                        //재고 추가
                        //재고 제거
                    }
                }
            }
        }
        else printf("정상적인 입력이 아닙니다. 다시 입력하십시오.");
    }
}
void manageModemenu() {
    printf("1. 회원 정보 입력 양식\n");
    printf("2. 회원 정보 열람\n");
    printf("3. 재고 수량 입력\n");
    printf("4. 가격 변경\n");
    printf("9. 이전\n");
}
int fileLine(FILE* f) {
    char c;
    int line = 0;
    while ((c = fgetc(f)) != EOF)
        if (c == '\n')
            line++;
    fclose(f);
    return line;
}
int makeMember() {
    int age = 0, nlen, plen, i, cnt, total;
    char name[16], phoneNumber[5];
    char temp1, temp2, temp3, sex, grade;
    grade = 'N';
    total = 0;
    FILE* afp;
    afp = fopen("idinfo.txt", "a");
    while (1) {
        printf("나이를 입력해주세요 : ");
        rewind(stdin);
        scanf(" %d", &age);
        printf("\n");
        if (age < 100 && age>0) {
            printf("%03d가 입력되었습니다.\n\n", age);
            break;
        }
        else if (age < 150 && age >= 100) {
            printf("%d가 입력되었습니다.\n", age);
            break;
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요.\n\n");
        }
    }
    while (1) {
        printf("성별을 입력해주세요(남성M, 여성F) : ");
        rewind(stdin);
        scanf(" %c", &sex);
        printf("\n");
        if (sex == 'M') {
            printf("남성 M이 입력되었습니다.\n\n");
            break;
        }
        else if (sex == 'F') {
            printf("여성 F가 입력되었습니다.\n\n");
            break;
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요.\n\n");
        }
    }
    while (1) {
        printf("이름을 입력해주세요(소문자 영어 15글자 이하) : ");
        scanf(" %s", name);
        printf("\n");
        nlen = (int)strlen(name);   //strlen의 반환은 unsigned long이라고 나오네요 그래서 강제 형변환 했습니다!
        cnt = 0;
        for (i = 0; i < nlen; i++) {
            if (('a' <= name[i]) && (name[i] <= 'z')) {
            }
            else {
                cnt++;
            }
        }
        if (cnt > 0) {
            printf("잘못 입력하셨습니다. 다시 입력해주세요.\n\n");
        }
        else {
            printf("%s이 입력되었습니다.\n\n", name);
            break;
        }
    }
    while (1) {
        printf("핸드폰 번호 뒷자리 4자리를 입력해주세요 : ");
        rewind(stdin);
        //scanf(" %s", phoneNumber);
        fgets(phoneNumber, 5, stdin);
        printf("\n");
        plen = (int)strlen(phoneNumber);    //strlen의 반환은 unsigned long이라고 나오네요 그래서 강제 형변환 했습니다!
        cnt = 0;
        for (i = 0; i < plen; i++) {
            if ((48 <= phoneNumber[i]) && (phoneNumber[i] <= 57)) {
            }
            else {
                cnt++;
            }
        }
        if (cnt > 0) {
            printf("잘못 입력하셨습니다. 다시 입력해주세요.\n\n");
        }
        else if (cnt == 0) {
            if (plen == 3) {
                temp1 = phoneNumber[0];
                temp2 = phoneNumber[1];
                temp3 = phoneNumber[2];
                phoneNumber[0] = 'a';
                phoneNumber[1] = temp1;
                phoneNumber[2] = temp2;
                phoneNumber[3] = temp3;
            }
            if (plen == 2) {
                temp1 = phoneNumber[0];
                temp2 = phoneNumber[1];
                phoneNumber[0] = 'a';
                phoneNumber[1] = 'a';
                phoneNumber[2] = temp1;
                phoneNumber[3] = temp2;
            }
            if (plen == 1) {
                temp1 = phoneNumber[0];
                phoneNumber[0] = 'a';
                phoneNumber[1] = 'a';
                phoneNumber[2] = 'a';
                phoneNumber[3] = temp1;
            }
            //printf("%s이 입력되었습니다.\n\n",  .phoneNumber);
            printf("%c%c%c%c이 입력되었습니다.\n\n", phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3]);
            break;
        }
    }
    //printf("회원 정보는 %d %c %s %s N입니다.\n\n",  .age,  .sex,  .name,  .phoneNumber);
    printf("회원 정보는 %d %c %s %c%c%c%c N입니다.\n\n", age, sex, name, phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3]);
    fprintf(afp, "%03d %c %s %c%c%c%c %c %d\n", age, sex, name, phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3], grade, total);
    fclose(afp);
    return 1;
}
int browseMember() {
    int age, total, input;
    char name[16], phoneNumber[5];
    char sex, grade;
    int line = 0;
    printf("\n회원 정보\n");
    FILE* rfp;
    rfp = fopen("idinfo.txt", "r");
    if (rfp != NULL) {
        line = fileLine(rfp);
        rfp = fopen("idinfo.txt", "r");
        for (int i = 0; i < line; i++) {
            fscanf(rfp, "%d %c %s %s %c %d", &age, &sex, name, phoneNumber, &grade, &total);
            printf("%03d %c %s %s %c %d\n", age, sex, name, phoneNumber, grade, total);
        }
        fclose(rfp);
    }
    else    printf("파일이 존재하지 않습니다..! 파일을 생성해주세요!\n");
    printf("\n");
    printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
    while (1) {
        rewind(stdin);
        scanf(" %d", &input);
        printf("\n");
        if (input == 9) {
            return 1;
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
        }
    }
}
int setStock() {
    int input;
    printf("1. 밥 수량 : ");
    rewind(stdin);
    scanf("%d", &stock[0]);
    printf("2. 면 수량 : ");
    rewind(stdin);
    scanf("%d", &stock[1]);
    printf("3. 돼지고기 수량 : ");
    rewind(stdin);
    scanf("%d", &stock[2]);
    printf("4. 간장 수량 : ");
    rewind(stdin);
    scanf("%d", &stock[3]);
    //stock[0] : 밥 수량, stock[1] : 면 수량, stock[2] : 돼지고기 수량, stock[3] : 간장 수량
    printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
    while (1) {
        rewind(stdin);
        scanf(" %d", &input);
        printf("\n");
        if (input == 9) {
            return 1;
        }
        else {
            printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
        }
    }
}
int changePrice() {
    int input, input1, input2;
    while (1) {
        printf("\n<음식 종류 선택>\n");
        printf("1. 한식\n2. 중식\n3. 일식\n4. 양식\n5. 음료\n9. 이전 화면\n");
        while (1) {
            rewind(stdin);
            scanf(" %d", &input);
            printf("\n");
            if (input == 1) {  //한식
                for (int i = 0; i < 4; i++)
                    printf("%d. %s\n", i + 1, foodName[i]);
                printf("9. 이전\n");
                printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 3, 4, 9) : ");

                while (1) {
                    rewind(stdin);
                    scanf(" %d", &input1);
                    printf("\n");
                    if (input1 == 1 || input1 == 2 || input1 == 3 || input1 == 4) {
                        printf("%s의 원래 가격 : %d, 변경 가격 : ", foodName[input1 - 1], price[input1 - 1]);
                        scanf(" %d", &price[input1 - 1]);
                        printf("%s의 가격이 %d으로 변경되었습니다.\n", foodName[input1 - 1], price[input1 - 1]);
                        printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
                        while (1) {
                            rewind(stdin);
                            scanf(" %d", &input2);
                            printf("\n");
                            if (input2 == 9)    return 1;
                            else    printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
                        }
                    }
                    else if (input1 == 9) { return 1; }
                    else { printf("잘못 입력하셨습니다. 다시 입력해주세요. "); }
                }
            }
            else if (input == 2) {  //중식
                for (int i = 4; i < 8; i++)
                    printf("%d. %s\n", i - 3, foodName[i]);
                printf("9. 이전\n");
                printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 3, 4, 9) : ");

                while (1) {
                    rewind(stdin);
                    scanf(" %d", &input1);
                    printf("\n");
                    if (input1 == 1 || input1 == 2 || input1 == 3 || input1 == 4) {
                        printf("%s의 원래 가격 : %d, 변경 가격 : ", foodName[3 + input1], price[3 + input1]);
                        scanf(" %d", &price[3 + input1]);
                        printf("%s의 가격이 %d으로 변경되었습니다.\n", foodName[3 + input1], price[3 + input1]);
                        printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
                        while (1) {
                            rewind(stdin);
                            scanf(" %d", &input2);
                            printf("\n");
                            if (input2 == 9)    return 1;
                            else    printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
                        }
                    }
                    else if (input1 == 9) { return 1; }
                    else { printf("잘못 입력하셨습니다. 다시 입력해주세요. "); }
                }
            }
            else if (input == 3) {  //일식
                for (int i = 8; i < 12; i++)
                    printf("%d. %s\n", i - 7, foodName[i]);
                printf("9. 이전\n");
                printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 3, 4, 9) : ");

                while (1) {
                    rewind(stdin);
                    scanf(" %d", &input1);
                    printf("\n");
                    if (input1 == 1 || input1 == 2 || input1 == 3 || input1 == 4) {
                        printf("%s의 원래 가격 : %d, 변경 가격 : ", foodName[7 + input1], price[7 + input1]);
                        scanf(" %d", &price[7 + input1]);
                        printf("%s의 가격이 %d으로 변경되었습니다.\n", foodName[7 + input1], price[7 + input1]);
                        printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
                        while (1) {
                            rewind(stdin);
                            scanf(" %d", &input2);
                            printf("\n");
                            if (input2 == 9)    return 1;
                            else    printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
                        }
                    }
                    else if (input1 == 9) { return 1; }
                    else { printf("잘못 입력하셨습니다. 다시 입력해주세요. "); }
                }
            }
            else if (input == 4) {  //양식
                for (int i = 12; i < 16; i++)
                    printf("%d. %s\n", i - 11, foodName[i]);
                printf("9. 이전\n");
                printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 3, 4, 9) : ");

                while (1) {
                    rewind(stdin);
                    scanf(" %d", &input1);
                    printf("\n");
                    if (input1 == 1 || input1 == 2 || input1 == 3 || input1 == 4) {
                        printf("%s의 원래 가격 : %d, 변경 가격 : ", foodName[11 + input1], price[11 + input1]);
                        scanf(" %d", &price[11 + input1]);
                        printf("%s의 가격이 %d으로 변경되었습니다.\n", foodName[11 + input1], price[11 + input1]);
                        printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
                        while (1) {
                            rewind(stdin);
                            scanf(" %d", &input2);
                            printf("\n");
                            if (input2 == 9)    return 1;
                            else    printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
                        }
                    }
                    else if (input1 == 9) { return 1; }
                    else { printf("잘못 입력하셨습니다. 다시 입력해주세요. "); }
                }
            }
            else if (input == 5) {  //음료
                for (int i = 16; i < 18; i++)
                    printf("%d. %s\n", i - 15, foodName[i]);
                printf("9. 이전\n");
                printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 9) : ");

                while (1) {
                    rewind(stdin);
                    scanf(" %d", &input1);
                    printf("\n");
                    if (input1 == 1 || input1 == 2) {
                        printf("%s의 원래 가격 : %d, 변경 가격 : ", foodName[15 + input1], price[15 + input1]);
                        scanf(" %d", &price[15 + input1]);
                        printf("%s의 가격이 %d으로 변경되었습니다.\n", foodName[15 + input1], price[15 + input1]);
                        printf("초기 모드로 돌아가기위해 9를 입력해주세요. ");
                        while (1) {
                            rewind(stdin);
                            scanf(" %d", &input2);
                            printf("\n");
                            if (input2 == 9)    return 1;
                            else    printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
                        }
                    }
                    else if (input1 == 9) { return 1; }
                    else { printf("잘못 입력하셨습니다. 다시 입력해주세요. "); }
                }
            }
            else if (input == 9) {
                return 1;
            }
            else {
                printf("잘못 입력하셨습니다. 다시 입력해주세요. ");
            }
        }
    }
}
void monthcheck() {
    FILE* f;
    char s[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    f = fopen("time.txt", "w");
    sprintf(s, "%d", tm.tm_mon + 1);
    fprintf(f, "%s", s);
    fclose(f);
}
customerInfo* idinfo(int k) {
    FILE* finfo;
    customerInfo* info;
    info = (customerInfo*)malloc(sizeof(customerInfo) * k);
    finfo = fopen("idinfo.txt", "r");
    for (int i = 0; i < k; i++) {
        fscanf(finfo, "%s %s %s %s %s %d",
            &info[i].age, &info[i].sex, &info[i].name, &info[i].phoneNumber, &info[i].grade, &info[i].total);
    }
    fclose(finfo);
    return info;
}
int login_view(customerInfo* info) {
    char Id[15];
    char grade = 'a';
    char password[5];
    char ans = 'y';
    //    int login = 0;    //아직 사용하지 않는 변수
    while (ans != 'n' && ans != 'N') {
//        system("cls");
        printf("아이디를 입력해주세요 : ");
        rewind(stdin);
        scanf("%s", Id);
        for (int i = 0; i < sizeof(info) / sizeof(struct customerInfo*); i++) {
            if (!strcmp(Id, info[i].name)) {
                printf("비밀번호를 입력해주세요 : ");
                scanf("%s", password);
                if (!strcmp(password, info[i].phoneNumber)) {
                    printf("로그인 성공");
                    printf("회원등급 : %c\n", info[i].grade[0]);
                    grade = info[i].grade[0];  //grade[1]
                    switch (grade) {
                    case 'N':   dc_percent = 0; break;
                    case 'S':   dc_percent = 3; break;
                    case 'G':   dc_percent = 5; break;
                    case 'D':   dc_percent = 7; break;
                    }
                    return 1;
                }
                else {
                    printf("없는 비밀번호입니다\n비회원이시면 관리자에게 문의 주세요\n");
                    printf("다시 입력하시겠습니까?(y/n) : ");
                    scanf(" %c", &ans);
                }
            }
            else {
                printf("없는 아이디입니다\n비회원이시면 관리자에게 문의 주세요\n");
                printf("다시 입력하시겠습니까?(y/n) : ");
                scanf(" %c", &ans);
            }
        }
    }
    return 4;
    //    if(login == 0){} //이전단계, 로그인 실패, 다시로그인 안한 상태!
    //    else    //다음단계    //로그인 성공 다음단계
}

int main(int agrc, char* argv[]) {

    int inp = 0;
    customerInfo* info = NULL;
    int k = 0;
    FILE* f = NULL;
    f = fopen("idinfo.txt", "r");//고객정보 파일
    if (f != NULL) {
        k = fileLine(f);
        info = idinfo(k);
    }
start:
    inp = start_view();   //시작 메뉴 진입시에는 정보를 다 초기화 합시다..! 다른 사람이 쓸수도 있으니..!
    if (inp == 1) {
    addorder:
        inp = order_view(); //추가 주문시!
        if (inp == 1) {
            sum_price = 0;
            memset(menu, 0, sizeof(int) * FOODNUM);   //주문 내역 초기화 후
            goto start; //이전모드인 시작 모드로 점프
        }
        if (inp == 6) {
            inp = premenu_view();
            if (inp == 1 && info != NULL) {
                /*로그인 결제*/
                inp = login_view(info);
                if (inp == 1) {
                    //로그인 성공
                    inp = payment_view();
                    if (inp == 1 || inp == 2) {
                        finalpayment_view();
                        goto start;
                    }
                }
                else {
                    printf("로그인에 실패 하였습니다! 메뉴를 선택해주세요\n");
                    goto addorder;
                }
            }
            else if (inp == 2) {
                inp = payment_view();
                if (inp == 1 || inp == 2) {
                    finalpayment_view();    //최종결제
                    goto start; //최종 결제 후 시작 모드
                }
                else if (inp == 3) {
                    sum_price = 0;
                    memset(menu, 0, sizeof(int) * FOODNUM);   //주문 내역 초기화 후
                    printf("주문내역 초기화후 시작화면으로 돌아갑니다\n");
                    goto start;
                }
            }
            else if (inp == 4) {
                goto addorder;
            }
            else {  //로그인 모드에서 로그인 실패시!
                printf("로그인에 필요한 정보가 없습니다!\n");
                goto addorder;
            }
        }
    }
    else if (inp == 2) {
    command:
        inp = command_view();
        if (inp == 1) {
            inp = makeMember();
            if (inp == 1) {
                goto command;
            }
        }
        else if (inp == 2) {
            inp = browseMember();
            if (inp == 1) {
                goto command;
            }
        }
        else if (inp == 3) {
            inp = setStock();
            if (inp == 1) {
                goto command;
            }
        }
        else if (inp == 4) {
            inp = changePrice();
            if (inp == 1) {
                goto command;
            }
        }
        else if (inp == 9) {
            goto start;
        }
    }
    return 0;
}
//나이를 char[4]
//구조체 포인터를 어디서 넘길지
//grade char[2]
//sex char[2]
//파일로 가격등을 받아오기.
//한식, 중식, 일식, 양식 따로 관리! -> 나중에
//로그인& 관리자 모드에서 main에서 연결.   -> 영석이하고 관주님이 해결좀 해주세요....!
//함수안에서 너무 이동함!-> 각각의 함수들이 함수에 대해 너무 종속적임 디버깅이 어려워짐 -> ver3에서 주문모드쪽은 해결(?)
//scanf함수대신 다른 함수 쓰기!
//아무것도 주문 안했을때 주문 튕기는!
//이전모드로 돌아갈때 저장 없이 시작 화면..!
//ver3수정자: 김형규(이 부분은 헷갈리지 않게..! 꼭 써주세요 만약에 주석말고 큰 변화가 있다면..? 버전도 올려주시구 작은 변화는 ver3.1이렇게 할께요!)
//ver3.2 수정자: 강관주 (제 주석은 시작, 끝 써놓겠습니다.)
//주석 시작
//메인함수 수정
//메인함수에 맞게 command_view, makeMember, browseMember, setStock, changePrice 수정
//rewind(stdin);  //문자열 들어오는 경우 무한출력방지 (입력 버퍼 비우기)
//scanf로 %d받을때 위에 rewind(stdin);을 넣어주면 문자가 들어와도 무한출력되는 문제 해결가능.
//changePrice 함수
//printf("가격 변경을 희망하는 메뉴를 선택해주세요.(1, 2, 3, 4, 9) : ");
//이후 숫자 입력 받는데, 9번을 입력해도 이전으로 되돌아가지 않는 문제 발생.
//일단 9입력시 관리자모드로 가도록 만들었습니다.
//ver3.3 수정자: 구본무( 수정사항: 주문>장바구니>결제 나오도록 순서변경  특이사항: 재고관리를 만들기는 했는데 어디에 넣을지?
/*ver3.4 수정자: 나영석(수정사항: 장바구니 결제 사이에 로그인 추가(%장바구니에서 회원 선택시 리턴을 하고 로그인 모드로이동))
로그인 모드에서 성공시 1반환 한후에 결재모드로이동, 재입력 안한다고 선택시 4반환후에 addorder로 이동으로 만들었음
본무님 수정사항과 관주님 수정사항 취합*/
//약간의 오류수정하고 안전장치 만들어놓음
//ver3.5 수정자: 김형규
//ver3.5.2 수정자: 고민석(수정사항: 장바구니에서 할인된 금액이 최종결제될때 반영이 안되는 문제 수정)
//ver3.6 수정자: 김형규(수정사항: 제고 수량입력을 제고 수량 추가로 변경 하였습니다..!)
//ver3.6.2 수정자: 강관주 (수정사항: comparisonStock()함수 삭제, 보고서와 다른점 수정)
//ver3.6.3 수정자: 구본무 (windows.h추가/ sleep>Sleep 변경)
//ver3.6.4 수정자: 김형규 (로그인 실패시 안내문구 출력 및 되돌아가기!)
//ver3.6.5 수정자: 김형규 (주문취소시 start로 돌아가기!)
