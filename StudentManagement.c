#define _CRT_SECURE_NO_WARNINGS
#include "StudentManagement.h"

int main(void){
	int order;
	int flag = 1;
	int stuNum;

	Student students[100] = { 0, };

	load_file(students, &stuNum);
	//view_list(students, stuNum);
	//save_file(students,stuNum);
	
	while (flag) {
		print_main_ui();
		input_order(&order);
		flag = exec_order(order, students, &stuNum);
	}
	return 0;
}

void view_list(Student students[], int studentsNum) {

	printf("%5s %7s %16s %18s","�� ��","�� ��","�� ��","����ó\n");
	for (int i = 0; i<studentsNum; i++) {
		printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
	}
}


void load_file(Student students[], int * studentsNum) {

	char line[256];
	int i = 0;
	FILE * fp = fopen("data.txt", "rt");
	
	if (fp == NULL) {
		printf("error");
	}

	fgets(line, sizeof(line), fp);
	while (fgets(line, sizeof(line), fp)) {

		sscanf(line, "%d\t%s\t%[^\n]\t%s", &students[i].id, students[i].name, students[i].address, students[i].phone);
		i++;
	}

	*studentsNum = i;
	fclose(fp);
}

void save_file(Student students[], int studentsNum){
	
	FILE * fp = fopen("data.txt", "wt");
	
	for (int i = 0; i < studentsNum; i++){
		fprintf(fp, "%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
	}

	fclose(fp);
}


void add_stu(Student students[],int *studentsNum){

	Student stu = { 0, };
	int maxid = 0;
	printf("�л� ���������� ����ϼ���.\n");

	for (int i = 0; i < *studentsNum; i++){
		if (maxid>students[i].id){
			maxid = maxid;
		}
		else{
			maxid = students[i].id;
		}
	}
	stu.id = maxid + 1;

	printf("���� �Է��� �̸� : ");
	scanf("%s", stu.name);
	getchar();
	printf("���� �Է��� �ּ� : ");
	fgets(stu.address, 100, stdin);
	for (int i = 0; i < 100; i++){
		if (stu.address[i] == '\n'){
			stu.address[i] = '\0';
			break;
		}
	}

	printf("���� �Է��� ����ó : (***-****-****)");
	scanf("%s", stu.phone);
	getchar();
	while (strlen(stu.phone) != 13){
		printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
		scanf("%s", stu.phone);
		getchar();
	}
	while ((stu.phone[3] != '-') && (stu.phone[9] != '-')){
		printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
		scanf("%s", stu.phone);
		getchar();
	}
	students[*studentsNum] = stu;
	(*studentsNum)++;

}

void search_stu(Student students[], int *studentsNum){
	int opt = 0;
	int i = 0;
	int flag = 0;
	Student search;
	char search_name[10];
	char search_address[100];
	char search_phone[20];
	int search_id;

	printf("�˻��� ������ ��ȣ�� �Է��ϼ���.\n");
	printf("1. ��  ��\n2. ��  ��\n3. ��  �� \n4. ����ó\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("�й��� �Է��ϼ���.\n");
		scanf("%d", &search_id);
		for (i = 0; i < *studentsNum; i++){
			if (students[i].id == search_id){
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			}
		}
		break;
	case 2:
		printf("�̸��� �Է��ϼ���.\n");
		scanf("%s", search_name);
		getchar();
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].name, search_name) == 0){
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			}
		}
		break;
	case 3:
		printf("�ּҸ� �Է��ϼ���.\n");
		fgets(search_address, 100, stdin);
		search_address[strlen(search_address) - 1] = '\0';
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].address, search_address) == 0){
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			}
		}
		break;
	case 4:
		printf("����ó�� �Է��ϼ���.\n");
		scanf("%s", search_phone);
		getchar();
		while (strlen(search.phone) != 13){
			printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
			scanf("%s", students[i].phone);
			getchar();
		}
		while ((search.phone[3] != '-') && (search.phone[9] != '-')){
			printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
			scanf("%s", search.phone);
			getchar();
		}
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].phone, search_phone) == 0){
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				}
		}
		break;
	default:
		printf("�߸� �Է��ϼ̽��ϴ�. 1~4 �� �ϳ��� �����ϼ���.\n");
	}	
	if (flag == 0){
		printf("ã���ô� �˻� ����� �����ϴ�.\n");
	}
}

void edit_stu(Student students[], int *studentsNum){
	int opt = 0;
	int i = 0;
	char search_name[10];
	char search_address[100];
	char search_phone[20];
	int search_id;

	printf("������ �ڷ��� ��ȣ�� �Է��ϼ���.\n");
	printf("1. ��  ��\n2. ��  ��\n3. ��  �� \n4. ����ó\n");
	scanf("%d", &opt);
	getchar();

	switch (opt){
	case 1:
		printf("�й��� �Է��ϼ���.\n");
		scanf("%d", &search_id);
		for (i = 0; i < *studentsNum; i++){
			if (students[i].id == search_id){			
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("���Ӱ� �ο��� �й��� �Է��ϼ���.\n");
				scanf("%d", &students[i].id);
				getchar();
			}
		}
		break;
	case 2:
		printf("�̸��� �Է��ϼ���.\n");
		scanf("%s", search_name);
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].name, search_name) == 0){
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("������ �̸��� �Է��ϼ���.\n");
				scanf("%s", students[i].name);
				getchar();
			}
		}
		break;
	case 3:
		printf("�ּҸ� �Է��ϼ���.\n");
		fgets(students[i].address, 100, stdin);
		search_address[strlen(search_address) - 1] = '\0';
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].address, search_address) == 0){			
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("������ �ּҸ� �Է��ϼ���.\n");
				fgets(students[i].address, 100, stdin);
				students[i].address[strlen(students[i].address) - 1] = '\0';
			}
		}
		break;
	case 4:
		printf("����ó�� �Է��ϼ���.\n");
		scanf("%s", search_phone);
		getchar();
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].phone, search_phone) == 0){
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("������ ��ȣ�� �Է��ϼ���.\n");
				scanf("%s", students[i].phone);
				getchar();
				while (strlen(students[i].phone) != 13){
					printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
					scanf("%s", students[i].phone);
					getchar();
				}
				while ((students[i].phone[3] != '-') && (students[i].phone[9] != '-')){
					printf("***-****-**** ���·� �ٽ� �Է��ϼ���.\n");
					scanf("%s", students[i].phone);
					getchar();
				}

			}
		}
		break;
	default:
		printf("�߸� �Է��ϼ̽��ϴ�. 1~4 �� �ϳ��� �����ϼ���.\n");
	}
}

void del_stu(Student students[], int *studentsNum){
	char del_name[10];
	int i = 0;
	int select = 0;

	printf("�ڷḦ ������ �л��� �̸��� �Է��ϼ���.\n");
	scanf("%s", del_name);
	getchar();
	for (i = 0; i < *studentsNum; i++){
		if (strcmp(students[i].name, del_name)==0){
			printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			
			printf("�� �л��� ��� �ڷḦ �����Ͻðڽ��ϱ�? (1:���� 2:���)\n");
			scanf("%d", &select);
			getchar();
			switch (select){
			case 1:
				printf("��� ���� �Ǿ����ϴ�.\n");
				(*studentsNum)--;
				students[i] = students[*studentsNum];
				break;
			case 2:
				break;
			}

		}
	}

}

void print_main_ui(){
	printf("================================================\n");
	printf("  =============2�г� 3�� �л� ����===========\n");
	printf("================================================\n");
	printf("              1: ��ü �л� ���� \n");
	printf("              2: �л� ��� �ϱ� \n");
	printf("              3: �л� �˻� �ϱ� \n");
	printf("              4: �ڷ� ���� �ϱ� \n");
	printf("              5: �ڷ� ���� �ϱ� \n");
	printf("              6: �ڷ� ���� �ϱ� \n");
	printf("              0: ����\n");
	printf("================================================\n");
	printf("                            ���� : �糪��\n");
	printf("================================================\n");
}

void input_order(int *order){

	printf("���ϴ� �޴� ��ȣ�� �Է��ϼ���.\n");
	scanf("%d", order);

	while (*order < 0 || *order > 6)
	{
		printf("�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		scanf("%d", order);
	}
}

int exec_order(int order, Student students[], int *studentsNum) {

	int select;

	if (order == 0){
		printf("���� ������ �����Ͻðڽ��ϱ�? (1:�� 2: �ƴϿ�)\n");
		scanf("%d", &select);
		if (select == 1){
			save_file(students, *studentsNum);
			printf("���� ������ ����Ǿ����ϴ�.\n");

		}
		else if (select == 2){
			printf("���α׷��� �����մϴ�. \n");
		}

		return 0;
	}


	else if (order == 1) {
		view_list(students, *studentsNum);
	}
	else if (order == 2){
		add_stu(students, studentsNum);
	}
	else if (order == 3){
		search_stu(students, studentsNum);
	}
	else if (order == 4){
		edit_stu(students, studentsNum);
	}
	else if (order == 5){
		del_stu(students, studentsNum);
	}
	else if (order == 6){
		save_file(students, *studentsNum);
		printf("���� ������ ����Ǿ����ϴ�.\n");
		return 1;
	}

}