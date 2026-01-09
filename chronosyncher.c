#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define CHRONOS_MAX_LEVEL 10

typedef struct {
    int score;
    int time_a;
    int time_b;
    int user_difference_b;
} chronos;

chronos* chronos_create();
int chronos_run(chronos *instance);
void chronos_reset_time(chronos *instance);
void chronos_create_level(chronos *instance, int level);
void chronos_display_chronometers(chronos *instance, int level);
void chronos_display_score(chronos *instance);
void chronos_flush_leftover_newline();
int chronos_get_random_number(int min, int max);
void chronos_clear();
void chronos_destroy(chronos *instance);

chronos* chronos_create()
{
    chronos *instance = malloc(sizeof(chronos));
    instance->score = 0;
    instance->time_a = 0;
    instance->time_b = 0;
    instance->user_difference_b = 0;
    return instance;
}

int chronos_run(chronos *instance)
{
    int level = 1;
    
    for (int seconds = 20; seconds >= 0; seconds--)
    {
        chronos_clear();    
        printf("\n== Welcome to Chronosyncher ==\n\n");
        printf("As a Chronosyncher contractor you will be tasked to sync our satellites time with our earth station, for some reason unknown to our middle management the time of our satellites is drifting, you will be compesated accordingly for your efforts but also punished for your mistakes.\n\nRemember in Chronosyncher we are all family.\n");
        printf("\nThe work starts in %d days...\n", seconds);

        sleep(1);
    }

    while (1)
    {
        chronos_create_level(instance, level);
        level++;
    }

    return 0;
}

void chronos_create_level(chronos *instance, int level)
{
    int points = level * 10; 
    chronos_reset_time(instance);

    instance->time_a = chronos_get_random_number(level * 10, level * 20);
    instance->time_b = chronos_get_random_number(level * 1, level * 10);

    chronos_clear();
    chronos_display_score(instance);

    chronos_display_chronometers(instance, level);
    printf("--------\n");

    chronos_clear();
    chronos_display_score(instance);

    printf("How much you should increase the satellite's time to synchronize the chronometers?: ");
    scanf("%d", &(instance->user_difference_b));

    instance->time_b = instance->time_b + instance->user_difference_b;

    chronos_display_chronometers(instance, level);

    chronos_flush_leftover_newline();

    chronos_clear();

    if (instance->time_a == instance->time_b)
    {
        instance->score += points;
        chronos_display_score(instance);
        printf("The chronometers are in sync! We have give you a bonus of $%d!\n", points);
        printf("Press enter to continue...\n");
        getchar();

        return;
    }
    
    instance->score -= points;
    chronos_display_score(instance);
    printf("The chronometers were NOT synced! We have to discount -$%d from your salary.\n", points);
    printf("Press enter to continue...\n");
    getchar();

    return;
}

void chronos_display_score(chronos *instance)
{
    printf("Money ($): %d\n\n", instance->score);
}

void chronos_display_chronometers(chronos *instance, int level)
{
    int samples = (CHRONOS_MAX_LEVEL / 2);
    int delay = 1;
    for (int i = 0; i < samples; i++)
    {
        printf("Chronometer Earth: %d secs, Chronometer Satellite: %d secs\n", instance->time_a, instance->time_b);
        instance->time_a++;
        instance->time_b++;
        sleep(delay);
    }
}

void chronos_clear()
{
    printf("\033[2J\033[H");
}

void chronos_flush_leftover_newline()
{
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

int chronos_get_random_number(int min, int max)
{
    srand(time(NULL)); 
    return rand() % (max - min + 1) + min;
}

void chronos_reset_time(chronos *instance)
{
    instance->time_a = 0;
    instance->time_b = 0;
}

void chronos_destroy(chronos *instance)
{
    free(instance);
}

int main()
{
    int err;
    chronos *game = chronos_create();
    
    err = chronos_run(game);
    if (err != 0)
    {
        chronos_destroy(game);
        return err;
    }

    chronos_destroy(game);
    return 0;
}