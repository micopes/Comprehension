#include <stdio.h>

void Vigenere(int, char *, int, char *, int);
int main(void){
    int Key_Size = 0, Str_Size = 0, select = 1;
    char str[50] = { 0, }, key[16] = { 0, };

    printf("��ȣ�� �Ǵ� ���� �Է� : ");
    gets(str);
    printf("��ȣ�� 1��, ��ȣ�� 2�� ���� : ");
    scanf("%d", &select);
    // scanf()���� '\n'�� ǥ�� ������� ���ۿ� �������� �� �����Ƿ� fflush()�� ���� ���۸� ����.
    fflush(stdin);
    printf("Ű �� �Է� : ");
    gets(key);

    Str_Size = strlen(str);
    Key_Size = strlen(key);

    Vigenere(select, str, Str_Size, key, Key_Size);

    printf("\n ��ȣȭ �Ǵ� ��ȣȭ�� ��� ��� :");
    puts(str);

    return 0;
}

void Vigenere(int select, char *str, int Str_Size, char *key, int Key_Size){
    int i = 0, j = 0;

    for(i = 0; i < Str_Size; ++i){
        // �Ҵ�� ���ڿ��� ��ġ�� ����ؼ�. ������ Key_Size�� ���� �������� ���ؼ� cycle�� �ڸ��� ã�´�.
        j = i % Key_Size;

        // ��ȣȭ(Encryption)
        if(select == 1){
            // ��ҹ��� ������ ó���ϱ� ���ϰ� �ƽ�Ű�ڵ�� ���� ���ڷ� ����ϰ� ���Ŀ� ó�����־���.
            if(str[i] >= 'a' && str[i] <= 'z'){
                str[i] -= 'a';
                // gronsfeld������ ���ڸ� �Է��߱� ������ -'a'��ſ� -'0'���� �̵��Ÿ��� �����ش�.
                key[j] -= '0';
                if(str[i] + key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] + key[j]) % 26;
                str[i] += 'a';
                key[j] += '0';
            }else if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] -= 'A';
                // gronsfeld������ ���ڸ� �Է��߱� ������ -'a'��ſ� -'0'���� �̵��Ÿ��� �����ش�.
                key[j] -= '0';
                if(str[i] + key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] + key[j]) % 26;
                str[i] += 'A';
                key[j] += '0';
            }
        }
        // ��ȣȭ(Decryption)
        if(select == 2){
            // ��ҹ��� ������ ó���ϱ� ���ϰ� �ƽ�Ű�ڵ�� ���� ���ڷ� ����ϰ� ���Ŀ� ó�����־���.
            if(str[i] >= 'a' && str[i] <= 'z'){
                str[i] -= 'a';
                // gronsfeld������ ���ڸ� �Է��߱� ������ -'a'��ſ� -'0'���� �̵��Ÿ��� �����ش�.
                key[j] -= '0';
                if(str[i] - key[j] < 0){
                    str[i] += 26;
                }
                str[i] = (str[i] - key[j]) % 26;
                str[i] += 'a';
                key[j] += '0';
            }else if(str[i] >= 'A' && str[i] <= 'Z'){
                str[i] -= 'A';
                // gronsfeld������ ���ڸ� �Է��߱� ������ -'a'��ſ� -'0'���� �̵��Ÿ��� �����ش�.
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
