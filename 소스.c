#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXWORD 200000

char *WORD[MAXWORD];
char *word_mean[MAXWORD];

int size = 0;

int search(char word[], int begin, int end)
{
	if (begin > end)
		return begin - 1;
	int middle = (begin + end) / 2;

	if (strcmp(word, WORD[middle]) == 0)
		return middle;
	else if (strcmp(word, WORD[middle]) < 0)
		return search(word, begin, middle - 1);
	else
		return search(word, middle + 1, end);

}
void read_dic()
{
	char file[1000];
	scanf("%s", file);//�ּ� �Է�
	FILE *fp = fopen(file, "r"); 

	char str[1000];
	char a[] = "()";
	while (!feof(fp)) {
		read_line(fp, str, 1000);
		if (strcmp(str, "\0")) {
			char *token = strtok(str, a);
			WORD[size] = strdup(token);
			WORD[size][strlen(WORD[size]) - 1] = '\0';
			token = strtok(NULL, a);
			token = strtok(NULL, a);
			word_mean[size] = strdup(token);
			size++;
		}
	}
	fclose(fp);
}

int read_line(FILE *fp, char str[], int length) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {  
		if (i < length - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void find(char word[]) {
	int index = search(word, 0, size - 1);
	if (index == -1) {
		printf("�ܾ ã�� ���߽��ϴ�.\n\n");
	}
	else if (strcmp(WORD[index], word) != 0) {
		printf("�ܾ ã�� ���߽��ϴ�.\n");
		printf("%s\n", WORD[index]);
		printf("%s \n", WORD[index - 1]);
	}
	else {
		int count = -1, i = index;

		while (i < size && strcmp(WORD[i++], word) == 0) {
			count++;
		}
		printf("%d���� �ܾ ã�ҽ��ϴ�.\n", count + 1);
		printf("%s (%s)\n", WORD[index], word_mean[index]);
		for (int i = index + 1; i <= index + count; i++) {
			printf("%s (%s)\n", WORD[i], word_mean[i]);
		}
	}
}

void print() {
	char command[1000];
	while (1) {
		printf("��ɾ �Է����ּ��� (1.���� �ҷ����� 2. ���� �ܾ� ���� ��� 3.�ܾ� �˻� 4. ����  \n");
		scanf("%s", command);
		if (strcmp(command, "1") == 0)
		{
			printf("������ �̸��� �Է����ּ��� : ");
			read_dic();
			printf("���� �ҷ����� ����\n\n");
		}
		else if (strcmp(command, "2") == 0)
			printf("�ܾ��� ���� %d��\n\n ", size);
		else if (strcmp(command, "3") == 0) {
			char word[1000];
			printf("�ܾ �Է����ּ���\n");
			scanf("%s", word);
			word[0] = word[0] - 32;
			find(word);
		}
		else if (strcmp(command, "4") == 0)
			break;
		else printf("�ٽ� �Է����ּ���\n");
	}
}
int main() {
	print();
	return 0;
}