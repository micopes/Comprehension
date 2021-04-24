#include <stdio.h>

char *CaesarCipher(char *, int, int); // ��ȣȭ Encryption
char *CaesarCipher2(char *, int, int); // ��ȣȭ Decryption
int main(void){
    int i = 0, key = 0, str_size = 0;
    char str[50] = { 0, };

    printf("���� �Է��Ͻÿ�.");
    gets(str);

    printf("Ű ���� �Է��Ͻÿ�.");
    scanf("%d", &key);

    str_size = strlen(str);

    CaesarCipher(str, str_size, key);
    // ��ȣȭ ��� ���
    printf("\n ��ȣȭ�� ��� ���");
    puts(str);
    // ��ȣȭ ��Ų �� �ٽ� ��ȣȭ.
    CaesarCipher2(str, str_size, key);

    printf("\n ��ȣȭ�� ��� ���");
    puts(str);

    return 0;
}

// ��ȣȭ
char *CaesarCipher(char *str, int str_size, int key){
    int i;

    for(int i = 0; i < str_size; ++i){
        // ���ڰ� ���ĺ� ���� �ȿ� ������ �ƽ�Ű�ڵ忡 �ش��ϴ� ���ڷ� ��������ش�. A -> 0 Z -> 25
        // ��ҹ��� ���о��� ó���ǰ� �ϱ� ���ؼ� �̷� ����� ���.
        if(str[i] > 'A' && str[i] <= 'Z'){
            str[i] -= 'A';

            if((str[i] + key) < 0)
                str[i] += 26;

            str[i] = (str[i] + key) % 26;
            // �ٽ� ���ĺ� �������� ����.
            str[i] += 'A';
        // �������� ������� �ҹ��� ó��.
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 'a';

            if((str[i] +key) < 0)
                str[i] += 26;

            str[i] = (str[i] + key) % 26;
            str[i] += 'a';
        }
    }
}

// ��ȣȭ
char *CaesarCipher2(char *str, int str_size, int key){
    int i;

    for(int i = 0; i < str_size; ++i){
        // ���ڰ� ���ĺ� ���� �ȿ� ������ �ƽ�Ű�ڵ忡 �ش��ϴ� ���ڷ� ��������ش�. A -> 0 Z -> 25
        // ��ҹ��� ���о��� ó���ǰ� �ϱ� ���ؼ� �̷� ����� ���.
        if(str[i] > 'A' && str[i] <= 'Z'){
            str[i] -= 'A';

            // ��ȣȭ�� ��� ������ �� �� �����Ƿ� �̸� �����ϰ� cycleó�� ó���ǵ��� �ϱ� ���ؼ� ������ �� ��쿡�� 26�� ���Ѵ�.
            if((str[i] - key) < 0)
                str[i] += 26;

            str[i] = (str[i] - key) % 26;
            // �ٽ� ���ĺ� �������� ����.
            str[i] += 'A';
        // �������� ������� �ҹ��� ó��.
        }else if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 'a';

            if((str[i] - key) < 0)
                str[i] += 26;

            str[i] = (str[i] - key) % 26;
            str[i] += 'a';
        }
    }
}


