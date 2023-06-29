#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 100 //максимальное колво студентов в базе 

typedef struct {// структура с параметрами 
    char id[50], firstName[50], lastName[50], middleName[50], faculty[50], specialization[50];
} Student;

Student students[MAX_STUDENTS];//массив 
int numStudents = 0;//колво студентов изначально 

void addStudent() {
    printf("Number: ");//ввод для номера 
    char id[50];//максимальное колво символов 
    fgets(id, sizeof(id), stdin);//ввод с клавы,сохраняем в id, sizeof размер  
    id[strcspn(id, "\n")] = '\0';//ищем символ новой строки заменяя его на нулевой 

    // Проверяем, существует ли студент с таким ID
    for (int i = 0; i < numStudents; i++) {//цикл для перебора каждого студента 
        if (strcmp(students[i].id, id) == 0) {//сравниаем две строки 
            printf("Student with ID already exists\n");

            // Обновляем данные существующего студента
            strcpy(students[i].id, id);//заменяет  старую инфу на новую 

            printf("First Name: ");
            fgets(students[i].firstName, sizeof(students[i].firstName), stdin);//считываем новое имя 
            students[i].firstName[strcspn(students[i].firstName, "\n")] = '\0';//удаляем символ новой строки и добавляем в массив 
            printf("Last Name: ");
            fgets(students[i].lastName, sizeof(students[i].lastName), stdin);
            students[i].lastName[strcspn(students[i].lastName, "\n")] = '\0';
            printf("Middle Name: ");
            fgets(students[i].middleName, sizeof(students[i].middleName), stdin);
            students[i].middleName[strcspn(students[i].middleName, "\n")] = '\0';
            printf("Faculty: ");
            fgets(students[i].faculty, sizeof(students[i].faculty), stdin);
            students[i].faculty[strcspn(students[i].faculty, "\n")] = '\0';
            printf("Specialization: ");
            fgets(students[i].specialization, sizeof(students[i].specialization), stdin);
            students[i].specialization[strcspn(students[i].specialization, "\n")] = '\0';

            return;
        }
    }
    
    
    strcpy(students[numStudents].id, id);//добавляем нового студента

    printf("First Name: ");
    fgets(students[numStudents].firstName, sizeof(students[numStudents].firstName), stdin);
    students[numStudents].firstName[strcspn(students[numStudents].firstName, "\n")] = '\0';
    printf("Last Name: ");
    fgets(students[numStudents].lastName, sizeof(students[numStudents].lastName), stdin);
    students[numStudents].lastName[strcspn(students[numStudents].lastName, "\n")] = '\0';
    printf("Middle Name: ");
    fgets(students[numStudents].middleName, sizeof(students[numStudents].middleName), stdin);
    students[numStudents].middleName[strcspn(students[numStudents].middleName, "\n")] = '\0';
    printf("Faculty: ");
    fgets(students[numStudents].faculty, sizeof(students[numStudents].faculty), stdin);
    students[numStudents].faculty[strcspn(students[numStudents].faculty, "\n")] = '\0';
    printf("Specialization: ");
    fgets(students[numStudents].specialization, sizeof(students[numStudents].specialization), stdin);
    students[numStudents].specialization[strcspn(students[numStudents].specialization, "\n")] = '\0';

    numStudents++;//увеличиваем колво студентов 

    printf("Student added\n");
}

void removeStudent() {
    printf("Enter student numer to remove: ");
    char id[50];
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < numStudents; i++) {//перебираем всех студентов
        if (strcmp(students[i].id, id) == 0) {//сравниваем номера студентов 
            found = 1; //если нашли

            students[i] = students[numStudents - 1];//перемещаем последнего студента вместо удаляемого
            numStudents--;//уменьшаем колво их

            printf("Student with ID %s removed\n", id);
            break;
        }
    }
    if (found == 0) {
        printf("No student with ID %s.\n", id);
    }
}

void createBackup() {
    char filename[50];//массив для имени файла 
    time_t t = time(NULL);
    struct tm *timeinfo = localtime(&t);
    strftime(filename, sizeof(filename), "students_%Y%m%d%H%M.csv", timeinfo);//создаем имя где год, месяц, дата, время 
    //открываем файл
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < numStudents; i++) {//перебор элементов массива 
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", students[i].id, students[i].firstName, students[i].lastName,
                students[i].middleName, students[i].faculty, students[i].specialization);//хаписываем данные через , 
    }

    fclose(file);
    printf("Backup created %s\n", filename);
}

void searchStudent() {
    printf("Last name to search: ");
    char lastName[50];
    fgets(lastName, sizeof(lastName), stdin);
    lastName[strcspn(lastName, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {//сравниваем фамилию 
            found = 1;
            printf("Student:\n");
            printf("Numer: %s\n", students[i].id);
            printf("First Name: %s\n", students[i].firstName);
            printf("Last Name: %s\n", students[i].lastName);
            printf("Middle Name: %s\n", students[i].middleName);
            printf("Faculty: %s\n", students[i].faculty);
            printf("Specialization: %s\n", students[i].specialization);
            printf("\n");
        }
    }

    if (found == 0) {
        printf("No student %s.\n", lastName);
    }
}

void saveDatabase() {
    char filename[] = "students.csv";//задаем имя файла 
    FILE *file = fopen(filename, "w");//открываем его 
    if (file == NULL) {
        return;
    }
    for (int i = 0; i < numStudents; i++) {//циклом записываем всех студентов в файл 
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", students[i].id, students[i].firstName, students[i].lastName,
                students[i].middleName, students[i].faculty, students[i].specialization);
    }

    fclose(file);

    printf("Saved\n");
}

int main() {
    int choice;//для выбора действия 

    while (1) {
        printf("Menu:\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Create Backup\n");
        printf("4. Search Student\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("What do you want? ");
        scanf("%d", &choice);
        getchar(); //убираем символ новой строки 

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                removeStudent();
                break;
            case 3:
                createBackup();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                saveDatabase();
                break;
            case 6:
                printf("Exiting\n");
                return 0;
            default:
                printf("Error\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
