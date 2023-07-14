#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PI 3.141592654

// bottom ------> top
double stack[32];
int sp = 0;

void exec(char *txt) {
    size_t tlen = strlen(txt);

    char *current = malloc(100);
    int cp = 0;
    for (int i = 0; i < tlen; ++i) {
        char c = txt[i];

        if (c == ' ' || c == '\n') {
            current[cp] = 0;
            char *e;
            double v = strtod(current, &e);
            if (strlen(e) == 0) {
                if (sp > 31) {
                    printf("Error: stack overflow!\n");
                    return;
                }

                stack[sp] = v;
                sp ++;

                cp = 0;
                continue;
            }
            if (strcmp(current, "pi") == 0) {
                if (sp > 31) {
                    printf("Error: stack overflow!\n");
                    return;
                }

                stack[sp] = PI;
                sp ++;

                cp = 0;
                continue;
            }
            const char c0 = current[0];
            bool ip = c0 == '+';
            bool im = c0 == '-';
            bool imu = c0 == '*';
            bool id = c0 == '/';
            bool is = ip || im || imu || id;
            if (is && sp < 2) {
                printf("Error: empty stack!\n");
                return;
            }
            if (ip) {
                stack[sp-2] = stack[sp-1] + stack[sp-2];
            }
            else if (im) {
                stack[sp-2] = stack[sp-1] - stack[sp-2];
            }
            else if (imu) {
                stack[sp-2] = stack[sp-1] * stack[sp-2];
            }
            else if (id) {
                stack[sp-2] = stack[sp-1] / stack[sp-2];
            }
            else if (c0 == 0) {}
            else {
                printf("Invalid expression: \"%s\"!\n", current);
                return;
            }

            if (is) {
                sp--;
            }

            cp = 0;
        }
        else {
            current[cp] = c;
            cp ++;
        }
    }
    free(current);
}

int main() {
    while (true) {
        char *inp = malloc(256);
        printf("> ");
        fgets(inp, 255, stdin);

        if (inp[0] == '\n') {

        } else if (inp[0] == 'q') {
            return 0;
        } else if (inp[0] == 's') {
            printf("TOP\n");
            for (int i = sp - 1; i >= 0; --i) {
                printf("pos %i: %f\n", i, stack[i]);
            }
            printf("BOTTOM\n");
        } else {
            exec(inp);
            printf("%f\n", stack[sp - 1]);
        }

        free(inp);
    }
}
