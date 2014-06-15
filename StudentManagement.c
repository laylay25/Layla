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

	printf("%5s %7s %16s %18s","학 번","이 름","주 소","연락처\n");
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
	printf("학생 인적사항을 등록하세요.\n");

	for (int i = 0; i < *studentsNum; i++){
		if (maxid>students[i].id){
			maxid = maxid;
		}
		else{
			maxid = students[i].id;
		}
	}
	stu.id = maxid + 1;

	printf("새로 입력할 이름 : ");
	scanf("%s", stu.name);
	getchar();
	printf("새로 입력할 주소 : ");
	fgets(stu.address, 100, stdin);
	for (int i = 0; i < 100; i++){
		if (stu.address[i] == '\n'){
			stu.address[i] = '\0';
			break;
		}
	}

	printf("새로 입력할 연락처 : (***-****-****)");
	scanf("%s", stu.phone);
	getchar();
	while (strlen(stu.phone) != 13){
		printf("***-****-**** 형태로 다시 입력하세요.\n");
		scanf("%s", stu.phone);
		getchar();
	}
	while ((stu.phone[3] != '-') && (stu.phone[9] != '-')){
		printf("***-****-**** 형태로 다시 입력하세요.\n");
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

	printf("검색할 사항의 번호를 입력하세요.\n");
	printf("1. 학  번\n2. 이  름\n3. 주  소 \n4. 연락처\n");
	scanf("%d", &opt);

	switch (opt){
	case 1:
		printf("학번을 입력하세요.\n");
		scanf("%d", &search_id);
		for (i = 0; i < *studentsNum; i++){
			if (students[i].id == search_id){
				flag = 1;
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			}
		}
		break;
	case 2:
		printf("이름을 입력하세요.\n");
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
		printf("주소를 입력하세요.\n");
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
		printf("연락처를 입력하세요.\n");
		scanf("%s", search_phone);
		getchar();
		while (strlen(search.phone) != 13){
			printf("***-****-**** 형태로 다시 입력하세요.\n");
			scanf("%s", students[i].phone);
			getchar();
		}
		while ((search.phone[3] != '-') && (search.phone[9] != '-')){
			printf("***-****-**** 형태로 다시 입력하세요.\n");
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
		printf("잘못 입력하셨습니다. 1~4 중 하나를 선택하세요.\n");
	}	
	if (flag == 0){
		printf("찾으시는 검색 결과가 없습니다.\n");
	}
}

void edit_stu(Student students[], int *studentsNum){
	int opt = 0;
	int i = 0;
	char search_name[10];
	char search_address[100];
	char search_phone[20];
	int search_id;

	printf("수정할 자료의 번호를 입력하세요.\n");
	printf("1. 학  번\n2. 이  름\n3. 주  소 \n4. 연락처\n");
	scanf("%d", &opt);
	getchar();

	switch (opt){
	case 1:
		printf("학번을 입력하세요.\n");
		scanf("%d", &search_id);
		for (i = 0; i < *studentsNum; i++){
			if (students[i].id == search_id){			
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("새롭게 부여할 학번을 입력하세요.\n");
				scanf("%d", &students[i].id);
				getchar();
			}
		}
		break;
	case 2:
		printf("이름을 입력하세요.\n");
		scanf("%s", search_name);
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].name, search_name) == 0){
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("수정할 이름을 입력하세요.\n");
				scanf("%s", students[i].name);
				getchar();
			}
		}
		break;
	case 3:
		printf("주소를 입력하세요.\n");
		fgets(students[i].address, 100, stdin);
		search_address[strlen(search_address) - 1] = '\0';
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].address, search_address) == 0){			
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("수정할 주소를 입력하세요.\n");
				fgets(students[i].address, 100, stdin);
				students[i].address[strlen(students[i].address) - 1] = '\0';
			}
		}
		break;
	case 4:
		printf("연락처를 입력하세요.\n");
		scanf("%s", search_phone);
		getchar();
		for (i = 0; i < *studentsNum; i++){
			if (strcmp(students[i].phone, search_phone) == 0){
				printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
				printf("수정할 번호를 입력하세요.\n");
				scanf("%s", students[i].phone);
				getchar();
				while (strlen(students[i].phone) != 13){
					printf("***-****-**** 형태로 다시 입력하세요.\n");
					scanf("%s", students[i].phone);
					getchar();
				}
				while ((students[i].phone[3] != '-') && (students[i].phone[9] != '-')){
					printf("***-****-**** 형태로 다시 입력하세요.\n");
					scanf("%s", students[i].phone);
					getchar();
				}

			}
		}
		break;
	default:
		printf("잘못 입력하셨습니다. 1~4 중 하나를 선택하세요.\n");
	}
}

void del_stu(Student students[], int *studentsNum){
	char del_name[10];
	int i = 0;
	int select = 0;

	printf("자료를 삭제할 학생의 이름을 입력하세요.\n");
	scanf("%s", del_name);
	getchar();
	for (i = 0; i < *studentsNum; i++){
		if (strcmp(students[i].name, del_name)==0){
			printf("%d\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].address, students[i].phone);
			
			printf("이 학생의 모든 자료를 삭제하시겠습니까? (1:삭제 2:취소)\n");
			scanf("%d", &select);
			getchar();
			switch (select){
			case 1:
				printf("모두 삭제 되었습니다.\n");
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
	printf("  =============2학년 3반 학생 관리===========\n");
	printf("================================================\n");
	printf("              1: 전체 학생 보기 \n");
	printf("              2: 학생 등록 하기 \n");
	printf("              3: 학생 검색 하기 \n");
	printf("              4: 자료 수정 하기 \n");
	printf("              5: 자료 삭제 하기 \n");
	printf("              6: 자료 저장 하기 \n");
	printf("              0: 종료\n");
	printf("================================================\n");
	printf("                            담임 : 양나리\n");
	printf("================================================\n");
}

void input_order(int *order){

	printf("원하는 메뉴 번호를 입력하세요.\n");
	scanf("%d", order);

	while (*order < 0 || *order > 6)
	{
		printf("올바르지 않은 입력입니다. 다시 입력해주세요.\n");
		scanf("%d", order);
	}
}

int exec_order(int order, Student students[], int *studentsNum) {

	int select;

	if (order == 0){
		printf("변경 사항을 저장하시겠습니까? (1:네 2: 아니오)\n");
		scanf("%d", &select);
		if (select == 1){
			save_file(students, *studentsNum);
			printf("변경 사항이 저장되었습니다.\n");

		}
		else if (select == 2){
			printf("프로그램을 종료합니다. \n");
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
		printf("변경 사항이 저장되었습니다.\n");
		return 1;
	}

}