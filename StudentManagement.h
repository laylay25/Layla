#include <stdio.h>
#include <string.h>
typedef struct {

	int id;
	char name[10];
	char address[50];
	char phone[20];

} Student;

void load_file(Student students[], int * studentsNum);
void view_list(Student students[], int studentsNum);
void save_file(Student students[], int studentsNum);
void add_stu(Student students[], int *studentsNum);
void search_stu(Student students[], int *studentsNum);
void edit_stu(Student students[], int *studentsNum);
void del_stu(Student students, int *studentsNum);
void print_main_ui();
void input_order(int *order);
int exec_order(int order, Student students[], int *studentsNum);