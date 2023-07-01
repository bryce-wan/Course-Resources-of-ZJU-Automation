#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student // the struct of student
{
    char str[15]; // the registration card ID string

    char level; // the level of the test

    int site; // the test site number

    int date; // the test date

    int number; // the testee's number

    int score; // the testee's score

} stu;

typedef struct Room // the struct of a test site
{
    int site; // the test site number

    int count; // the number of testees in the site

} room;

stu students[10001];

room rooms[1000];

int N, M;

int cmp_score(const void *a, const void *b); // the comparing function for the qsort (compare the score of two students)

int cmp_count(const void *a, const void *b); // the comparing function for the qsort (compare the count of two rooms)

void Decode(int decode_type, int iter); // decode the queries

int main()
{
    scanf("%d %d", &N, &M); // read the N and M

    for (int i = 0; i < N; i++)
    {
        scanf("%s %d", students[i].str, &students[i].score); // read the ID and the score

        sscanf(students[i].str, "%1c%3d%6d%3d", &students[i].level,
               &students[i].site, &students[i].date, &students[i].number); // extract the related infromation from the ID string
    }

    qsort(students, N, sizeof(struct Student), cmp_score); // sort the students array by scores

    for (int i = 0; i < M; i++)
    {
        int decode_type;

        scanf("%d", &decode_type); // read a query

        Decode(decode_type, i); // decode the query
    }
}

int cmp_score(const void *a, const void *b) // the comparing function for the qsort (compare the score of two students)
{
    stu *stu_a = (stu *)a, *stu_b = (stu *)b;

    if (stu_a->score != stu_b->score)

        return stu_b->score - stu_a->score; // in non-increasing order of the scores

    return strcmp(stu_a->str, stu_b->str); // if there is a tie of the scores, output in increasing alphabetical order of their card numbers
}

int cmp_count(const void *a, const void *b) // the comparing function for the qsort (compare the count of two rooms)
{
    room *room_a = (room *)a, *room_b = (room *)b;

    if (room_a->count != room_b->count)

        return room_b->count - room_a->count; // in non-increasing order of the number of testees

    return room_a->site - room_b->site; // or in increasing order of site numbers if there is a tie
}

void Decode(int decode_type, int iter)
{
    int isempty = 1; // judge if the output is empty, print NA if isempty == 1

    switch (decode_type)
    {

    case 1: // type 1
    {
        char level[2];

        scanf("%s", level); // read the level of query

        printf("Case %d: %d %c\n", iter + 1, decode_type, level[0]);

        for (int i = 0; i < N; i++)
        {
            if (students[i].level == level[0]) // if the i-th student's level is same as the given level
            {
                if (isempty)
                    isempty = 0; // the output is not empty

                printf("%s %d\n", students[i].str, students[i].score);
            }
        }

        if (isempty)
            puts("NA"); // print NA if there is no one meets the requirement

        break;
    }

    case 2: // type 2
    {
        int site;

        int count = 0; // record the numbers of testees in the given site

        long long sum_score = 0; // record the sum of scores

        scanf("%d", &site); // read the site of query

        printf("Case %d: %d %d\n", iter + 1, decode_type, site);

        for (int i = 0; i < N; i++)
        {
            if (students[i].site == site) // if the i-th student's site is same as the given site
            {
                if (isempty)
                    isempty = 0; // the output is not empty

                count += 1;

                sum_score += students[i].score;
            }
        }

        if (isempty)
            puts("NA"); // print NA if there is no one meets the requirement
        else
            printf("%d %lld\n", count, sum_score);

        break;
    }

    case 3: // type 3
    {
        int date;

        scanf("%d", &date);

        printf("Case %d: %d %06d\n", iter + 1, decode_type, date);

        for (int i = 0; i < 1000; i++)
        {
            rooms[i].site = i;

            rooms[i].count = 0;
        }

        for (int i = 0; i < N; i++)
        {
            if (students[i].date == date) // if the i-th student's date is same as the given date
            {
                if (isempty)
                    isempty = 0; // the output is not empty

                rooms[students[i].site].count += 1;
            }
        }

        if (isempty)
            puts("NA"); // print NA if there is no one meets the requirement
        else
        {
            qsort(rooms, 1000, sizeof(struct Room), cmp_count); // sort all the sites by the number of testees

            int i = 0;

            while (rooms[i].count != 0) // output the answers until we meet the first empty site
            {

                printf("%d %d\n", rooms[i].site, rooms[i].count);

                i++;
            }
        }

        break;
    }
    }
}