//
// Created by AdminPC on 14.05.2016.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE *mf;
struct book {
    int id;
    char *name;
    char *phone;
};
struct book* person;
size_t bookSize;
int used[10000000];

char *readingFile() {
    char *str = NULL;
    size_t size = 32;
    str = (char *) malloc(size);
    int n = 0;
    while (!feof(mf)) {
        char s = fgetc(mf);
        if (s == '\n' || s == ' ' || s == EOF) {
            str[n] = '\0';
            return str;
        }
        if (size == n + 1) {
            str = (char *) realloc(str, size *= 2);
        }
        str[n++] = s;
        n++;

    }
    str[n] = '\0';
    return str;
}

char *readString() {
    char *str = NULL;
    size_t size = 32;
    str = (char *) malloc(size);
    int n = 0;
    for (; ;) {
        char s = getchar();
        if (s == '\n' || s == ' ') {
            str[n++] = '\0';
            return str;
        }
        if (size == n + 1) {
            str = (char *) realloc(str, size *= 2);
        }
        str[n++] = s;
        n++;

    }
}

int correctName(char *s) {
    for(int j = 0; j < strlen(s); ++j)
        if (!isalpha(s[j]))
            return 0;
    return 1;
}

int correctPhone(char *s) {
    int b, bb;
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] == '(')
            ++b;
        if (s[i] == ')')
            bb++;
        if (b - bb < 0 || (i != 0 && s[i] == '+') || b > 1 || (s[i] == '-' && s[i + 1] == '-') ||
            (isdigit(s[i]) && s[i] != '-' && s[i] != '+' && s[i] != '(' && s[i] != ')'))
            return 0;
    }
    return 1;
}
char* toLow(char* name){
    for(int i = 0; i < strlen(name); i++)
        name[i] = tolower(name[i]);
    return name;

}
void findName(char *name) {
    name = toLow(name);
    for (int i = 0; i < bookSize; i++) {
        if (used[i] == 0)continue;
        char *curName = person[i].name;
        curName = toLow(curName);
        if (strstr(curName, name) != NULL) {
            printf("%d %s %s \n", i, person[i].name, person[i].phone);
        }
    }

}

void findPhone(char *phone) {
    for (int i = 0; i < bookSize; i++) {
        if (used[i] == 0)continue;
        int l = 0, r = 0;
        int k = 0;
        while (l < strlen(phone) || r < strlen(person[i].phone)) {
            if (l >= strlen(phone) && isdigit(person[i].phone[r]))break; else {
                r++;
            }
            if (r >= strlen(person[i].phone) && isdigit(phone[l]))break; else {
                l++;
            }
            if (isdigit(phone[l]) & isdigit(person[i].phone[r])) {
                if (phone[l] != person[i].phone[r]) break;
                l++;
                r++;
            }
            if (!isdigit(phone[l]))l++;
            if (!isdigit(person[i].phone[r]))r++;
        }
        if (l >= strlen(phone) && r >= strlen(person[i].phone)) {
            printf("%d %s %s\n", i, person[i].name, person[i].phone);
            return;
        }
    }
}

void create(char *name, char *phone) {
    for (int i = 0; i < bookSize; i++) {
        if (used[i] == 0) {
            person[i].name = name;
            person[i].phone = phone;
            used[i] = 1;
            return;
        }
    }
    int cur = bookSize;
    person = (struct book* ) realloc(person, bookSize *= 2);
    person[cur].name = name;
    person[cur].phone = phone;
    used[cur] = 1;
}

void read() {
    if (feof(mf) == true) {
        return;
    }
    while (!feof(mf)) {
        int index;
        fscanf(mf, "%d", &index);
        while (index >= bookSize)
            person = (book *) realloc(person, bookSize *= 2);
        person[index].name = readingFile();
        person[index].phone = readingFile();

    }

}

void write() {
    for (int i = 0; i < bookSize; i++) {
        if (used[i] == 1)
            fprintf(mf, "%d %s %s\n", i, person[i].name, person[i].phone);

    }
}

int main(int argc, char *argv[]) {


    mf = fopen(argv[1], "r+");
    if (mf == NULL) {
        mf = fopen(argv[1], "w+");
    }
    bookSize = 10;
    struct book *person = (struct book* )malloc(sizeof(struct book) * bookSize);

    //read from file

    for (; ;) {
        char *command = readString();

        if (strcmp(command, "find") == 0) {
            char *string1 = readString();
            if (isalpha(string1[0])) {
                if (!correctName(string1)) {
                    printf("Error, try again \n");
                    continue;
                }
                findName(string1);
            } else {
                if (!correctPhone(string1)) {
                    printf("Error, try again \n");
                    continue;
                }
                findPhone(string1);

            }

        }
        if (strcmp(command, "delete") == 0) {
            int index;
            scanf("%d", &index);
            used[index] = 0;
            person[index].phone = NULL;
            person[index].name = NULL;
        }
        if (strcmp(command, "change") == 0) {
            int index;
            scanf("%d", &index);
            char *string1 = readString();
            if (strcmp(string1, "name") == 0) {
                string1 = readString();
                person[index].name = string1;
            } else {
                string1 = readString();
                person[index].phone = string1;
            }

        }
        if (strcmp(command, "create") == 0) {
            char *name = readString();
            char *phone = readString();
            if (!correctName(name) || !correctPhone(phone)) {
                printf("Error, try again \n");
                continue;
            }
            create(name, phone);
        }

        fclose(mf);
        mf = fopen(argv[1], "w+");
        write();

        if (strcmp(command, "exit") == 0) {
            fclose(mf);
            return 0;
        }
        fflush(stdout);


    }


}