#include <stdio.h>

struct instant {
  int hour;
  int minute;
  int second;
};

int instant_parse(const char* str, struct instant *init){
    if(sscanf(str, "%d:%d:%d", &init->hour, &init->minute, &init->second) == 3) return 0;
    else return 1;
}

int instant_check(struct instant i){
    if((i.hour >= 00 && i.hour <= 23) && (i.minute >= 00 && i.minute <= 59) && (i.second >= 00 && i.second <= 59)) {
        return 1;
    } else return 0;
}

int instant_compare(struct instant i1, struct instant i2){
    if (i1.hour != i2.hour) {
        return i1.hour - i2.hour;
    }
    if (i1.minute != i2.minute) {
        return i1.minute - i2.minute;
    }
    return i1.second - i2.second;
}

void instant_read_vector(struct instant *v, int n) {
    int count_validos = 0;
    char str[10];
    while(count_validos < n) {
        struct instant temp;
        if(fgets(str, 10, stdin) == NULL) break;
        if(instant_parse(str, &temp) == 0 && instant_check(temp) != 0) {
            v[count_validos] = temp;
            count_validos++;
        }
    }
}

struct instant instant_largest(const struct instant *v, int n) {
    struct instant maior = v[0];
    for(int i = 1; i < n; i++) {
        if(instant_compare(v[i], maior) > 0) maior = v[i];
    }
    return maior;
}

const int NINSTANTS = 5;

int main(void) {
    struct instant v[NINSTANTS];
    instant_read_vector(v, NINSTANTS);
    struct instant maior = instant_largest(v, NINSTANTS);
    printf("Maior instante: %02d:%02d:%02d\n", maior.hour, maior.minute, maior.second);
    return 0;
}

/*
#include <stdio.h>

struct instant {
  int hour;
  int minute;
  int second;
};

int instant_parse(const char* str, struct instant *init){
    if(sscanf(str, "%d:%d:%d", &init->hour, &init->minute, &init->second) == 3) return 0;
    else return 1;
}

int instant_check(struct instant i){
    int test = 0;
    if(i.hour >= 00 && i.hour <= 23) test++;
    if(i.minute >= 00 && i.hour <= 59) test++;
    if(i.hour >= 00 && i.hour <= 59) test++;
    if(test < 3) return 0;
    else return 1;
}

int instant_compare(struct instant i1, struct instant i2){
    if(i1.hour == i2.hour && i1.minute == i2.minute && i1.second == i2.second) return -1;
    if(i1.hour > i2.hour) return 0;
    if(i1.hour == i2.hour && i1.minute > i2.minute) return 0;
    if(i1.hour == i2.hour && i1.minute == i2.minute && i1.second > i2.second) return 0;
    if(i1.hour < i2.hour) return 1;
    if(i1.hour == i2.hour && i1.minute < i2.minute) return 1;
    if(i1.hour == i2.hour && i1.minute == i2.minute && i1.second < i2.second) return 1;
}

void instant_read_vector(struct instant *v, int n) {
    for(int i = 0; i < n; i++) {
        char str[9];
        scanf("%s", str);
        instant_parse(str, &v[i]);
        while(instant_check(v[i])) {
            while(instant_parse(str, &v[i])) {
                scanf("%s", str);
            }
        }        
    }
}

struct instant instant_largest(const struct instant *v, int n) {
    struct instant maior = v[0];
    for(int i = 1; i < n; i++) {
        if(instant_compare(maior, v[i]) == -1) continue;
        if(instant_compare(maior, v[i]) == 0) continue;
        if(instant_compare(maior, v[i]) == 1) maior = v[i];
    }
}
*/