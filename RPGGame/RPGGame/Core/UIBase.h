#ifndef __UIBASE_H__
#define __UIBASE_H__

#include <windows.h>
#include <stdio.h>

/**
* @brief 将控制台光标移动指定位置
*/
void gotoxy(int x, int y);

/**
* @brief 控制台输出字符
*/
void print(char c);

/**
* @brief 控制台指定位置输出字符
*/
void print(int x, int y, char c);

/**
* @brief 控制台指定位置输出字符串
*/
void print(int x, int y, char *buffer);

/**
* @brief 清理控制台指定位置字符
*/
void clearxy(int x, int y);

/**
* @brief 清理控制台指定位置之间的字符
*/
void clearxy(int x1, int y1, int x2, int y2);

/**
* @brief 清理控制台所有字符
*/
void clear();

/**
* @brief 读取控制台指定位置字符
*/
void readxy(int x, int y, char &character);

/**
* @brief 设置控制台颜色
*/
void setcolor(int fg,int bg);


#endif