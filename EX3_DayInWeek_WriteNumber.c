#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*==============INITIALIZE GLOBAL VARIABLE==============*/
typedef enum
{
    JAN = 1,
    FEB = 2,
    MAR = 3,
    APR = 4,
    MAY = 5,
    JUN = 6,
    JUL = 7,
    AUG = 8,
    SEPT = 9,
    OCT = 10,
    NOV = 11,
    DEC = 12,
} Month;

typedef enum
{
    SUN = 0,
    MON = 1,
    TUE = 2,
    WED = 3,
    THU = 4,
    FRI = 5,
    SAT = 6,
} DaysOfWeek;

typedef struct
{
    uint8_t day;
    Month month;
    uint16_t year;
    DaysOfWeek dayOfWeek;
} Date;

const Date originDate = {28, 3, 2023, 2}; // Saturday

char *ones[] = {"Khong", "Mot", "Hai", "Ba", "Bon", "Nam", "Sau", "Bay", "Tam", "Chin"};

/*==============INITIALIZE FUNCTION==============*/
int is_leap_year(uint16_t year);
int days_in_month(int month, uint16_t year);
uint32_t days_between_jun11(Date date);
void days_of_week(Date date);
void convert(int n);
void read_num(uint32_t n);

/*==============USER CODE==============*/
void main()
{
    // Date date = {1, 1, 1};
    // days_of_week(date);
    
    read_num(7004000);
}

/*==============FUNCTION==============*/
// Function to check leap year: leap year return 1
int is_leap_year(uint16_t year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Function to calculate the number of days in a month
int days_in_month(int month, uint16_t year)
{
    int days[12] = {31, 28 + is_leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

// Function to calculate the days from 1/1/1 to input date
uint32_t days_between_jun11(Date date)
{
    uint32_t days = date.day - 1;
    for (int i = 1; i < date.month; i++)
    {
        days += days_in_month(i, date.year);
    }
    return days + ((date.year - 1) * 365) + ((date.year - 1) / 4);
}

// Function return days of week of input date
void days_of_week(Date date)
{
    char *daysInWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    if (date.year > originDate.year || (date.year == originDate.year && date.month > originDate.month) ||
        (date.year == originDate.year && date.month == originDate.month && date.day > originDate.day))
    {
        printf("\n%s", daysInWeek[(days_between_jun11(date) - days_between_jun11(originDate) + (originDate.dayOfWeek)) % 7]);
    }
    else
        printf("\n%s", daysInWeek[6 + (((int32_t)days_between_jun11(date) - (int32_t)days_between_jun11(originDate) + (int)originDate.dayOfWeek + 1) % 7)]);
}

// Function to print number
void convert(int n)
{
    if (n >= 100)
    {
        printf("%s Tram ", ones[n / 100]);
        n %= 100;
    }
    if (n >= 10 && n <= 99)
    {
        printf("%s Muoi ", ones[n / 10]);
        n %= 10;
    }
    if (n >= 1 && n <= 9)
    {
        if (n == 4)
        {
            printf("Tu ");
        }
        else if (n == 5)
        {
            printf("Lam ");
        }
        else
        {
            printf("%s ", ones[n]);
        }
    }
}

//Function to split unit, send to convert function and print unit
void read_num(uint32_t n)
{
    int mil = n / 1000000;
    int thsd = (n % 1000000) / 1000;
    int dong = n % 1000;
    if (mil > 0)
    {
        convert(mil);
        printf("Trieu ");
    }
    if (thsd > 0)
    {
        if (thsd < 10)
        {
            printf("Khong Tram Linh ");
        }
        else if ((thsd % 100) / 10 == 0)
        {
            printf("Linh ");
        }
        convert(thsd);
        printf("Nghin ");
    }
    if (dong > 0)
    {
        if (dong < 10)
        {
            printf("Khong Tram Linh ");
        }
        else if ((dong % 100) / 10 == 0)
        {
            printf("Linh ");
        }
        convert(dong);
    }
    printf("Dong");
}

