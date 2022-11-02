#include <stdio.h>
#define ARR_SIZE 100

typedef enum
{
  Success,
  Failure,
} ResultType;

typedef struct
{
  ResultType type;
  union
  {
    void *value;
    char *error;
  };
} Result;

int main(int argc, char *argv[])
{
  Result r = {
      .type = Failure,
      .error = "Something went wrong",
  };

  switch (r.type)
  {
  case Failure:
    printf("Error: %s\n", r.error);
    break;
  case Success:
    printf("Success\n");
    break;
  }
  return 0;
}