#include <stdio.h>

char *CaesarCipher(char *, int, int); // 암호화 Encryption
char *CaesarCipher2(char *, int, int); // 복호화 Decryption
int main(void){
    int i = 0, key = 0, str_size = 0;
    char str[50] = { 0, };

    printf("평문을 입력하시오.");
    gets(str);

    printf("키 값을 입력하시오.");
    scanf("%d", &key);

    str_size = strlen(str);

    CaesarCipher(str, str_size, key);
    // 암호화 결과 출력
    printf("\n 암호화된 결과 출력");
    puts(str);
    // 암호화 시킨 것 다시 복호화.
    CaesarCipher2(str, str_size, key);

    printf("\n 복호화된 결과 출력");
    puts(str);

    return 0;
}

// 암호화
char *CaesarCipher(char *str, int str_size, int key){
    int i;

    for(int i = 0; i < str_size; ++i){
        // 문자가 알파벳 범위 안에 있으면 아스키코드에 해당하는 숫자로 변경시켜준다. A -> 0 Z -> 25
        // 대소문자 구분없이 처리되게 하기 위해서 이런 방식을 사용.
        if(str[i] > 'A' && str[i] <= 'Z'){
            str[i] -= 'A';

            if((str[i] + key) < 0)
                str[i] += 26;

            str[i] = (str[i] + key) % 26;
            // 다시 알파벳 형식으로 변경.
            str[i] += 'A';
        // 마찬가지 방식으로 소문자 처리.
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 'a';

            if((str[i] +key) < 0)
                str[i] += 26;

            str[i] = (str[i] + key) % 26;
            str[i] += 'a';
        }
    }
}

// 복호화
char *CaesarCipher2(char *str, int str_size, int key){
    int i;

    for(int i = 0; i < str_size; ++i){
        // 문자가 알파벳 범위 안에 있으면 아스키코드에 해당하는 숫자로 변경시켜준다. A -> 0 Z -> 25
        // 대소문자 구분없이 처리되게 하기 위해서 이런 방식을 사용.
        if(str[i] > 'A' && str[i] <= 'Z'){
            str[i] -= 'A';

            // 복호화의 경우 음수가 될 수 있으므로 이를 방지하고 cycle처럼 처리되도록 하기 위해서 음수가 될 경우에는 26를 더한다.
            if((str[i] - key) < 0)
                str[i] += 26;

            str[i] = (str[i] - key) % 26;
            // 다시 알파벳 형식으로 변경.
            str[i] += 'A';
        // 마찬가지 방식으로 소문자 처리.
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 'a';

            if((str[i] - key) < 0)
                str[i] += 26;

            str[i] = (str[i] - key) % 26;
            str[i] += 'a';
        }
    }
}


