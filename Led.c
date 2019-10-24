#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

// 포트 매핑
#define LED1 4
#define SANHAK_1ST 27
#define SANHAK_2ST 28
#define SANHAK_3RD 29

// LookUp Table -> 포트 : SQL number
char Table_GPIO[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 1, 2, 3 };

// 로그 데이터를 저장할 구조체 선언
typedef struct tagLogData
{
    int no;
    char* log_area;
    char* log_name;
    int floor;
}LogData;

void SetLogData(LogData* p_Data, int p_no, char* p_area, char* p_name, int p_floor);
void CurrentTime(char* Dest);
void LoadPositionData(char* p_Data, const int Port_Num);
void SetLog(char* p_Log, int PortNum);
void SaveLog(char* p_Log);
void DestroyLogData(LogData* p_Data);

// 로그 데이터 구조체를 정의하는 함수
void SetLogData(LogData* p_Data, int p_no, char* p_area, char* p_name, int p_floor)
{
    p_Data->no =p_no;
    p_Data->log_area = p_area;
    p_Data->log_name = p_name;
    p_Data->floor = p_floor;
}

void DestroyLogData(LogData* p_Data)
{
	free(p_Data->log_area);
	free(p_Data->log_name);
}

// 현재시간을 문자열로 알려주는 함수
void CurrentTime(char* Dest)
{
    struct tm* date;
    const time_t t = time(NULL);
    date = localtime(&t);

    sprintf(Dest, "%d/%d/%d %d:%d:%d",
    date->tm_year - 100,
    date->tm_mon + 1,
    date->tm_mday,
    date->tm_hour,
    date->tm_min,
    date->tm_sec);

    free(date);
}

// 포트 번호에 따른 데이터를 불러온뒤 이를 문자열
void LoadPositionData(char* p_Data, const int Port_Num)
{
    LogData Data;
    char* sz_area = (char*)calloc(30, sizeof(char));
    char* sz_name = (char*)calloc(30, sizeof(char));

    strcpy(sz_area, "아산-탕정");
    strcpy(sz_name, "산학관");

    switch(Port_Num)
    {
    case SANHAK_1ST:
        SetLogData(&Data, 1, sz_area, sz_name, 1);
        break;
    case SANHAK_2ST:
        SetLogData(&Data, 2, sz_area, sz_name, 2);
        break;
    case SANHAK_3RD:
        SetLogData(&Data, 3, sz_area, sz_name, 3);
        break;
    }

    sprintf(p_Data, "No : %d, Area : %s, Name : %s, Floor : %d", 
                Data.no, Data.log_area, Data.log_name, Data.floor);
	
	DestroyLogData(&Data);
}

void SetLog(char* p_Log, int PortNum)
{
    // Log 초기화
    memset(p_Log, 0, 100);

    // 현재 시간 문자열을 불러온다.
    char Time[30] = { 0 };
    CurrentTime(Time);

    // 위치 데이터를 불러온다.
    char Position[60] = { 0 };
    LoadPositionData(Position, PortNum);

    strcat(p_Log, Time);
    strcat(p_Log, " ");
    strcat(p_Log, Position);
}

void SaveLog(char* p_Log)
{
	char LogLine[120] = { 0 };
	strcpy(LogLine, p_Log);
	strcat(LogLine, "\n");

	FILE* fp;
	fp = fopen("Log", "a");

	fputs(LogLine, fp);

	fclose(fp);
}

int main(void)
{
    char* Log = (char*)calloc(sizeof(char), 100);

    if (wiringPiSetup() == -1)
		return -1;

	pinMode(LED1, OUTPUT);
	pinMode(SANHAK_1ST, INPUT);
	pinMode(SANHAK_2ST, INPUT);
	pinMode(SANHAK_3RD, INPUT);

	int count = 0;
	while(1)
	{
		if (digitalRead(SANHAK_1ST) == 1)
		{
			if (count == 0){
				SetLog(Log, SANHAK_1ST);
                printf("%s\n", Log);
				SaveLog(Log);
				count++;
			}
			digitalWrite(LED1, 1);
			delay(100);
		}
		else if (digitalRead(SANHAK_2ST) == 1)
		{
			if (count == 0){
				SetLog(Log, SANHAK_2ST);
                printf("%s\n", Log);
				SaveLog(Log);
				count++;
			}
			digitalWrite(LED1, 1);
			delay(100);
		}
		else if (digitalRead(SANHAK_3RD) == 1)
		{
			if (count == 0){
				SetLog(Log, SANHAK_3RD);
                printf("%s\n", Log);
				SaveLog(Log);
				count++;
			}
			digitalWrite(LED1, 1);
			delay(100);
		}
		else
		{
			count = 0;
			digitalWrite(LED1,0);
			delay(100);
		}
	}

    return 0;
}
