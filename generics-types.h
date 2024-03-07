typedef struct ints {
    int a;
    int b;
} ints;

int handle_ints(ints arg) {
    return arg.a + arg.b;
}

typedef struct strings {
    char *a;
    char *b;
} strings;

char result[20];
char *handle_strings(strings arg) {
    strcat(result,arg.a);
    strcat(result," plus ");
    strcat(result,arg.b);
    return result;
}