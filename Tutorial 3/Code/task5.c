#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct grade
{
    int std_id;
    int marks;
};

void grade_students(struct grade *grades, int num)
{

    FILE *file;
    int sum = 0;
    float average = 0;
    float deviation = 0;
    
    file = fopen("grades.txt", "w");

    for (int i=0; i < (num); i++) // this for loop prints out each student id and grade entered by the user
    {
        int id = (grades+i)->std_id;
        int grade = (grades+i)->marks; 
        sum =sum + grade;

        fprintf(file, "Student ID: %d  |   Grade: %d\n", id, grade);
    }

    average = sum/num;

    for (int i=0; i < num; i++) // This for loop creates the last line with the average student grades and standard deviation
    {
        int grade = (grades+i)->marks; 

        int temp = pow(grade - average, 2);
        deviation = deviation+ temp;
    }
    deviation = sqrt(deviation / num);

    fprintf(file, "Average: %f  |  Standard Deviation: %f\n", average, deviation); // prints the last line in the file grades.txt

    printf("\nOpen grades.txt for Results"); // tells the user when the file is printed
}

int main (void)
{
    char* prof;
    int num;
    struct grade *grades;
    int size=256;

    prof = (char*)calloc(size, sizeof(char));
    if (prof == NULL)
    {
        printf("no memory for professor");
        return 0;
    }

    printf("\n Name of Professor:");
    fgets(prof, size, stdin);
    printf("\nNumber of Students:");
    scanf("%d", &num);

    grades = (struct grade*)malloc(num * sizeof(struct grade));
    if (grades == NULL)
    {
        printf("no memory for grades");
        return 0;
    }
    
   for(int i=0; i<num; i++) // Asks the user to input student id and the mark according to order
    {
        printf("\nEnter the student's Id and grade respectivly: ");
        scanf("%d %d", &(grades+i)->std_id, &(grades+i)->marks);
    }

    grade_students(grades, num);

    free(prof);
    free(grades);
}
