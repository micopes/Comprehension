#include <stdio.h>

void Encryption(char *str, int key, int size);
void Decryption(char *str, int key, int size);
int main(void){
	char text[100];
	int size = 0, select = 0, key = 0;

    printf("암호는 1번, 복호는 2번 선택 : ");
    scanf("%d", &select);
    if(select == 1){
        printf("평문 입력 : ");
        fflush(stdin);
        scanf("%s", text);

        printf("키 입력 : ");
        scanf("%d", &key);

        size = strlen(text);
        Encryption(text, key, size);
    }else if(select == 2){
        printf("평문 입력 : ");
        fflush(stdin);
        scanf("%s", text);

        printf("키 입력 : ");
        scanf("%d",&key);

        size = strlen(text);
        Decryption(text, key, size);
    }
	return 0;
}

void Encryption(char *str, int key, int size){
	// Rail Matrix
	char R[key][size];
	// 빈공간 표현
	for(int i = 0; i < key; ++i)
        for(int j = 0; j < size; ++j)
            R[i][j] = '_';
	// 지그재그로 원하는 위치에 encoding 시키기 위해
	int flag = 1;
	for(int i = 0, j = 0; j < size; i+=flag, ++j){
		if(i == 0)
			flag = 1;
		else if(i == key-1)
			flag = -1;
		R[i][j] = str[j];
	}
	// 출력
	printf("암호문 : ");
	for(int i = 0; i < key; ++i){
		for(int j = 0; j < size; ++j){
			if(R[i][j] != '_'){
				printf("%c", R[i][j]);
			}
		}
	}
	printf("\n");
}

void Decryption(char *str, int key, int size){
	// Rail Matrix
	char R[key][size];
	// 빈공간 표현
	for(int i = 0; i < key; ++i)
        for(int j = 0; j < size; ++j)
            R[i][j] = '_';
	// 지그재그로 원하는 위치에 decoding 시키기 위해
	int flag = 1;
	for(int i = 0, j = 0; j < size; i+=flag, ++j){
		if(i == 0)
			flag = 1;
		else if(i == key-1)
			flag = -1;
		R[i][j] = '@';
	}
	// '@'로 표시된 공간을 ciphertext를 채워준다.
	int k = 0;
	for(int i = 0; i < key; ++i){
		for(int j = 0; j < size; ++j){
			if(R[i][j] == '@'){
				R[i][j] = str[k];
				k += 1;
			}
		}
	}
	// 출력
	printf("복호문 : ");
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < key; ++j){
			if(R[j][i] != '_'){
				printf("%c", R[j][i]);
			}
		}
	}
	printf("\n");

}
