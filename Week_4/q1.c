#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main() {
    char buf[BUF_SIZE];
    ssize_t n;

    const char *hardcoded_sentence = "This is a sentence with example word for testing";

    char search_word[BUF_SIZE];
    ssize_t search_word_len = 0;

    while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            if (buf[i] == '\n' || search_word_len >= BUF_SIZE - 1) {
                search_word[search_word_len] = '\0';
                break;
            } else {
                search_word[search_word_len++] = buf[i];
            }
        }
        if (buf[n - 1] == '\n') break;
    }

    if (strstr(hardcoded_sentence, search_word)) {
        write(STDOUT_FILENO, hardcoded_sentence, strlen(hardcoded_sentence));
        write(STDOUT_FILENO, "\n", 1);
    } else {
        const char *msg = "Word not found in the sentence.\n";
        write(STDOUT_FILENO, msg, strlen(msg));
    }

    return 0;
}
