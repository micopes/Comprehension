#include <stdio.h>

void Encryption(char *str, int key, int size);
void Decryption(char *str, int key, int size);
int main(void){
	char text[100];
	int size = 0, select = 0, key = 0;

    printf("��ȣ�� 1��, ��ȣ�� 2�� ���� : ");
    scanf("%d", &select);
    if(select == 1){
        printf("�� �Է� : ");
        fflush(stdin);
        scanf("%s", text);

        printf("Ű �Է� : ");
        scanf("%d", &key);

        size = strlen(text);
        Encryption(text, key, size);
    }else if(select == 2){
        printf("�� �Է� : ");
        fflush(stdin);
        scanf("%s", text);

        printf("Ű �Է� : ");
        scanf("%d",&key);

        size = strlen(text);
        Decryption(text, key, size);
    }
	return 0;
}

void Encryption(char *str, int key, int size){
	// Rail Matrix
	char R[key][size];
	// ����� ǥ��
	for(int i = 0; i < key; ++i)
        for(int j = 0; j < size; ++j)
            R[i][j] = '_';
	// ������׷� ���ϴ� ��ġ�� encoding ��Ű�� ����
	int flag = 1;
	for(int i = 0, j = 0; j < size; i+=flag, ++j){
		if(i == 0)
			flag = 1;
		else if(i == key-1)
			flag = -1;
		R[i][j] = str[j];
	}
	// ���
	printf("��ȣ�� : ");
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
	// ����� ǥ��
	for(int i = 0; i < key; ++i)
        for(int j = 0; j < size; ++j)
            R[i][j] = '_';
	// ������׷� ���ϴ� ��ġ�� decoding ��Ű�� ����
	int flag = 1;
	for(int i = 0, j = 0; j < size; i+=flag, ++j){
		if(i == 0)
			flag = 1;
		else if(i == key-1)
			flag = -1;
		R[i][j] = '@';
	}
	// '@'�� ǥ�õ� ������ ciphertext�� ä���ش�.
	int k = 0;
	for(int i = 0; i < key; ++i){
		for(int j = 0; j < size; ++j){
			if(R[i][j] == '@'){
				R[i][j] = str[k];
				k += 1;
			}
		}
	}
	// ���
	printf("��ȣ�� : ");
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < key; ++j){
			if(R[j][i] != '_'){
				printf("%c", R[j][i]);
			}
		}
	}
	printf("\n");

}
