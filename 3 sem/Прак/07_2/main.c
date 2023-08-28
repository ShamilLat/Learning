#include <stdlib.h>
#include <stdio.h>

enum
{
    MULTIPLIE = 1103515245,
    CHANGE = 12345,
    MOD = 2147483648
};

typedef struct RandomGenerator RandomGenerator;

typedef struct RandomOperations
{
    void (*destroy)(RandomGenerator *);
    int (*next)(RandomGenerator *);
} RandomOperations;

struct RandomGenerator
{
    int key;
    RandomOperations *ops;
};

void
destroy(RandomGenerator *rr)
{
    free(rr->ops);
    free(rr);
}

int
next(RandomGenerator *rr)
{
    rr->key = ((long long)MULTIPLIE * rr->key + (long long)CHANGE) % (long long)MOD;
    return rr->key;
}

RandomGenerator
*random_create(int seed)
{
    RandomGenerator *test = malloc(sizeof(RandomGenerator));
    test->ops = malloc(sizeof(RandomOperations));
    test->key = seed;
    test->ops->destroy = destroy;
    test->ops->next = next;
    return test;
}
