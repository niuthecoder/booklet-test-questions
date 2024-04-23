#include <stdio.h>
#include <string.h>

#include <stdlib.h>

void generateExam(char *line, int *Qcount, int booklet, FILE *questionsFile, FILE *answersFile);

struct Question
{
    int questionNumber;
    char questionBody[500];
    char optionA[100];
    char optionB[100];
    char optionC[100];
    char optionD[100];
    char answer;
};

struct QuestionBank
{
    struct Question questions[1000];
    int count;
};

int main()
{

    FILE *inputFile;
    char line[100];

    int booklet;
    int questions;
    int Qcount = 0;
    FILE *questionsFile;
    FILE *answersFile;
    int bookletNumber = 1;

    struct QuestionBank questionBank;
    /**/
    inputFile = fopen("sample.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    printf("enter how many booklets you want:");
    scanf("%d", &booklet);
    printf("enter how many questions you want:");
    scanf("%d", &questions);

    while (fgets(line, sizeof(line), inputFile) != NULL && Qcount < questions)
    {

        char questionsFileName[20], answersFileName[20];
        sprintf(questionsFileName, "booklet_%d_questions.txt", bookletNumber);
        sprintf(answersFileName, "booklet_%d_answers.txt", bookletNumber);

        questionsFile = fopen(questionsFileName, "w");
        answersFile = fopen(answersFileName, "w");

        if (questionsFile == NULL || answersFile == NULL)
        {
            printf("Error opening output files.\n");
            return 1;
        }
        for (int i = 0; i < booklet && Qcount < questions; i++)
        {
            processQuestion(questionsFile, answersFile, line, &Qcount, booklet);
            if (fgets(line, sizeof(line), inputFile) == NULL)
            {
                break;
            }
        }
        fclose(questionsFile);
        fclose(answersFile);
        bookletNumber++;
    }
    fclose(inputFile);
    /**/

    return 0;
}

void generateExam(char *line, int *Qcount, int booklet, FILE *questionsFile, FILE *answersFile)
{
    char questions[1000];
    char Correct_answer;
    scanf(line, "[^\t]\t%c", questions, &Correct_answer);
    fprintf(questionsFile, "%s\n", questions);

    fprintf(answersFile, "%c\n", Correct_answer);
    *Qcount++;
    if (*Qcount % booklet == 0)
    {
        printf("Booklet generated with %d questions.\n", booklet);
    }
}
void readQuestionsFromFile(char *filename, struct QuestionBank *questionBank)
{
    FILE *inputFile = fopen(filename, "r");
    if (!inputFile)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }
    while (fscanf(inputFile, "%d\n", &questionBank->questions[questionBank->count].questionNumber) == 1)
    {
        fgets(questionBank->questions[questionBank->count].questionBody, sizeof(questionBank->questions[questionBank->count].questionBody), inputFile);
        fgets(questionBank->questions[questionBank->count].optionA, sizeof(questionBank->questions[questionBank->count].optionA), inputFile);
        fgets(questionBank->questions[questionBank->count].optionB, sizeof(questionBank->questions[questionBank->count].optionB), inputFile);
        fgets(questionBank->questions[questionBank->count].optionC, sizeof(questionBank->questions[questionBank->count].optionC), inputFile);
        fgets(questionBank->questions[questionBank->count].optionD, sizeof(questionBank->questions[questionBank->count].optionD), inputFile);
        fscanf(inputFile, " %c\n", &questionBank->questions[questionBank->count].answer);

        questionBank->count++;
    }

    fclose(inputFile);
}
