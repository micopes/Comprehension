#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BlockCipherMode.h"
#define BLOCK_MODE 4	/* 1: CBC, 2: CFB, 3: OFB, 4: CTR */
#include "DES.h"

int main()
{
    int i;
    BYTE p_text[128]={0,};
    BYTE key[9]={0,};
    BYTE IV[9]={0,};
    BYTE c_text[128]={0,};
    BYTE d_text[128]={0,};
    int msg_len;
    UINT64 ctr=0;

    /* �� �Է� */
    printf("�� �Է�: ");
    gets((char *)p_text);
    /* ���Ű �Է� */
    printf("���Ű �Է�: ");
    scanf("%s", key);
    fflush(stdin);

    #if(BLOCK_MODE!=4)
        /* �ʱ�ȭ ���� �Է� */
        printf("�ʱ�ȭ ���� �Է�: ");
        scanf("%s", IV);
        fflush(stdin);
    #else
        /* ī���� �Է� */
        printf("ctr �Է�: ");
        scanf("%u", &ctr);
        fflush(stdin);
    #endif
        /* �޽��� ���� ��� */
        msg_len=(strlen((char *)p_text) % BLOCK_SIZE) ?
                      ((strlen((char *)p_text) / BLOCK_SIZE +1)*8):
                      strlen((char *)p_text);

    printf("Cipher Block Codebook ��ȣȭ ����\n");
    #if(BLOCK_MODE==1)
        DES_CBC_Enc(p_text, c_text, IV, key, msg_len);//DES-CBC ��ȣȭ
    #elif(BLOCK_MODE==2)
        DES_CFB_Enc(p_text, c_text, IV, key, msg_len);//DES-CFB ��ȣȭ
    #elif(BLOCK_MODE==3)
        DES_OFB_Enc(p_text, c_text, IV, key, msg_len);//DES-OFB ��ȣȭ
    #else
        DES_CTR_Enc(p_text, c_text, key, ctr, msg_len);//DES-CTR ��ȣȭ
    #endif
        /* ��ȣ�� ��� */
        printf("\n��ȣ��: ");
        for(i=0; i<msg_len; i++)
            printf("%x", c_text[i]);
        printf("\n");

    printf("Cipher Block Codebook ��ȣȭ ����\n");
    #if(BLOCK_MODE==1)
        DES_CBC_Dec(c_text, d_text, IV, key, msg_len);//DES-CBC ��ȣȭ
    #elif(BLOCK_MODE==2)
        DES_CFB_Dec(c_text, d_text, IV, key, msg_len);//DES-CFB ��ȣȭ
    #elif(BLOCK_MODE==3)
        DES_OFB_Dec(c_text, d_text, IV, key, msg_len);//DES-CFB ��ȣȭ
    #else
        DES_CTR_Dec(c_text, d_text, key, ctr, msg_len);//DES-CTR ��ȣȭ
    #endif
        /* ��ȣ�� ��� */
        printf("\n��ȣ��: ");
        for(i=0; i<msg_len; i++)
            printf("%x", d_text[i]);
        printf("\n");

    return 0;
}
