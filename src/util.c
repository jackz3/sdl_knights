#include <ctype.h>
#include "util.h"

int rand_int(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

char **string_split(const char *str, const char* delimiter, int *count)
{
  // 计算分割后的字符串个数
  int strLen = strlen(str);
  int delimiterLen = strlen(delimiter);
  int maxSplitCount = strLen / delimiterLen + 1;

  // 分配存储字符串指针的数组
  char **result = (char **)malloc(maxSplitCount * sizeof(char *));
  if (result == NULL)
  {
    printf("内存分配失败\n");
    return NULL;
  }

  // 复制字符串到临时缓冲区
  char *tempStr = (char *)malloc((strLen + 1) * sizeof(char));
  if (tempStr == NULL)
  {
    printf("内存分配失败\n");
    free(result);
    return NULL;
  }
  strcpy(tempStr, str);

  // 逐个分割字符串
  char *token = strtok(tempStr, delimiter);
  int i = 0;
  while (token != NULL)
  {
    result[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
    if (result[i] == NULL)
    {
      printf("内存分配失败\n");
      free(tempStr);
      for (int j = 0; j < i; j++)
      {
        free(result[j]);
      }
      free(result);
      return NULL;
    }
    strcpy(result[i], token);

    i++;
    token = strtok(NULL, delimiter);
  }

  // 释放临时缓冲区并更新分割后的字符串个数
  free(tempStr);
  *count = i;

  return result;
}


char* toLowerCase(const char* str) {
    int i = 0;
    int len = strlen(str);
    char* ret = (char*)malloc(sizeof(char) * (len + 1));
    if (ret == NULL) {
      return NULL;
    }
    while (str[i] != '\0') {
        ret[i++] = tolower(str[i]);
    }
    ret[len] = '\0';
    return ret;
}