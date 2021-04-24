#include <stdio.h>

void Vigenere(int, char *, int, char *, int);
int main(void){
    int Key_Size = 0, Str_Size = 0, select = 1;
    char str[50] = { 0, }, key[16] = { 0, };

    printf("암호문 또는 평문을 입력 : ");
    gets(str);
    printf("암호는 1번, 복호는 2번 선택 : ");
    scanf("%d", &select);
    // scanf()에서 '\n'이 표준 입출력의 버퍼에 남아있을 수 있으므로 fflush()를 통해 버퍼를 비운다.
    fflush(stdin);
    printf("키 값 입력 : ");
    gets(key);

    Str_Size = strlen(str);
    Key_Size = strlen(key);

    Vigenere(select, str, Str_Size, key, Key_Size);

    printf("\n 암호화 또는 복호화되 결과 출력 :");
    puts(str);

    return 0;
}

void Vigenere(int select, char *str, int Str_Size, char *key, int Key_Size){
    int i = 0, j = 0;

    for(i = 0; i < Str_Size; ++i){
        // 할당된 문자열의 위치를 고려해서. 넘으면 Key_Size에 대한 나머지를 구해서 cycle의 자리를 찾는다.
        j = i % Key_Size;

        // 암호화(Encryption)
        if(select == 1){
            // 대소문자 나눠서 처리하기 편하게 아스키코드로 빼서 숫자로 계산하고 이후에 처리해주었다.
            if(str[i] >= 'a' && str[i] <= 'z'){
                str[i] -= 'a';
                // gronsfeld에서는 숫자를 입력했기 때문에 -'a'대신에 -'0'으로 이동거리를 맞춰준다.
                key[j] -= '0';
                if(str[i] + key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] + key[j]) % 26;
                str[i] += 'a';
                key[j] += '0';
            }else if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] -= 'A';
                // gronsfeld에서는 숫자를 입력했기 때문에 -'a'대신에 -'0'으로 이동거리를 맞춰준다.
                key[j] -= '0';
                if(str[i] + key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] + key[j]) % 26;
                str[i] += 'A';
                key[j] += '0';
            }
        }
        // 복호화(Decryption)
        if(select == 2){
            // 대소문자 나눠서 처리하기 편하게 아스키코드로 빼서 숫자로 계산하고 이후에 처리해주었다.
            if(str[i] >= 'a' && str[i] <= 'z'){
                str[i] -= 'a';
                // gronsfeld에서는 숫자를 입력했기 때문에 -'a'대신에 -'0'으로 이동거리를 맞춰준다.
                key[j] -= '0';
                if(str[i] - key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] - key[j]) % 26;
                str[i] += 'a';
                key[j] += '0';
            }else if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] -= 'A';
                // gronsfeld에서는 숫자를 입력했기 때문에 -'a'대신에 -'0'으로 이동거리를 맞춰준다.
                key[j] -= '0';
                if(str[i] - key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] - key[j]) % 26;
                str[i] += 'A';
                key[j] += '0';
            }
        }
    }
}
