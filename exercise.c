#include <stdio.h>

struct Match {  //keeping track of all the...
    char *start;  //...adjustments to be made
    char *end;
};

void repstr(char *buf, char *sub, char *rep) {
    struct Match matches[256];
    int match_count = 0;
    char *scan = buf; //FORWARD SCAN:
    while (*scan && match_count < 256) {
        char *match_start = scan;
        char *match_end = scan;
        const char *sub_ptr = sub;  // try to match sub at this position:
        while (*match_end && *sub_ptr && *match_end == *sub_ptr) {
            match_end++;
            sub_ptr++;
        }
        if (*sub_ptr == '\0') { // found a complete match
            matches[match_count].start = match_start;
            matches[match_count].end   = match_end;
            match_count++;
            scan = match_end;   // matched chars saved and skipped
        } else {  // move forward one char and try again
            scan++;
        }
    }
    int len_diff  = strlen(rep) - strlen(sub); //BACKWARD EDIT:
    int final_len = strlen(buf) + match_count * len_diff;
    if (final_len >= 256) return; //starting editing all matches if possible
    for (int i = match_count - 1; i >= 0; i--) {  //making sure there's space if rep's longer than sub...
        memmove(matches[i].end + len_diff, matches[i].end, strlen(matches[i].end) + 1);
        for (int j = 0; rep[j]; j++) {  //...for rep extra chars to be copied onto sub and buf
            matches[i].start[j] = rep[j];
            }
    }
}
