#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include "config.h"

#define VERSION "0.0.2"

char *get_pretty_name();
void print_info(const char *type);
void help(char *exec_name);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
                help(argv[0]);
                return 0;
            }
            else if (strcmp("-v", argv[i]) == 0 || strcmp("--version", argv[i]) == 0) {
                printf("sucklessfetch %s\n", VERSION);
                printf("compiled at %s, %s\n", __DATE__, __TIME__);
                printf("original repo - github.com/wcupped/sucklessfetch\n");
                return 0;
            }
        }
    }
    else {
        if (sizeof(modules) / sizeof(modules[0]) == 0) {
            fprintf(stderr, "no modules?\n");
            return 1;
        }
        for (int i = 0; i < sizeof(modules) / sizeof(modules[0]); ++i) {
            print_info(modules[i]);
        }
    }
    
    return 0;
}

void help(char *exec_name) {
    printf("usage: %s [options]\n\n", exec_name);
    printf("    -h, --help      show this help message and exit.\n");
    printf("    -v, --version   show the version of this util and exit.\n");
}

char *get_pretty_name() {
    FILE *f = fopen("/etc/os-release", "r");
    if (!f) return NULL;
    char buf[256];
    while (fgets(buf, sizeof buf, f)) {
        if (strncmp(buf, "PRETTY_NAME=", 12) == 0) {
            char *val = buf + 12;
            size_t n = strlen(val);
            if (n && val[0] == '"' && val[n-1] == '\n') val[n-1] = '\0';
            if (val[0] == '"' && val[strlen(val)-1] == '"') {
                val[strlen(val)-1] = '\0';
                val++;
            }
            char *res = strdup(val);
            fclose(f);
            return res;
        }
    }
    fclose(f);
    return NULL;
}

void print_info(const char *type) {
    if (strcmp("separator", type) == 0) {
        printf("*************************\n");
    }

    else if (strcmp("uah", type) == 0) {
        char *username = getlogin();
        char hostname[256];
        
        if (username == NULL)
            fprintf(stderr, "null");
        else
            printf("%s", username);

        printf("@");

        if (gethostname(hostname, sizeof(hostname)) != 0)
            fprintf(stderr, "null\n");
        else
            printf("%s\n", hostname);
    }

    else if (strcmp("shell", type) == 0) {
        char *shell = getenv("SHELL");
        printf("shell - ");
        if (shell == NULL)
            fprintf(stderr, "(null)\n");
        else
            printf("%s\n", shell);
    }
    
    else if (strcmp("terminal", type) == 0) {
        char *terminal = getenv("TERM");
        printf("terminal - ");
        if (terminal == NULL)
            fprintf(stderr, "(null)\n");
        else
            printf("%s\n", terminal);
    }

    else if (strcmp("distro", type) == 0) {
        char *pretty_distro_name = get_pretty_name();
        struct utsname arch;
        uname(&arch);
        printf("distro - ");

        if (pretty_distro_name == NULL)
            fprintf(stderr, "(null)\n");
        else
            printf("%s %s\n", pretty_distro_name, arch.machine);
    }

    else if (strcmp("locale", type) == 0) {
        char *locale = setlocale(LC_ALL, "");
        printf("locale - ");

        if (locale == NULL)
            fprintf(stderr, "(null)\n");
        else
            printf("%s\n", setlocale(LC_ALL, NULL));
    }

    else if (strcmp("ker_ver", type) == 0) {
        struct utsname buffer;
        printf("kernel version - ");

        if (uname(&buffer) != 0)
            fprintf(stderr, "(null)\n");
        else
            printf("%s\n", buffer.release);
    }

    else if (strcmp("uptime", type) == 0) {
        struct sysinfo info;
        printf("uptime - ");
        if (sysinfo(&info) == 0) {
            int days = info.uptime / 86400;
            int hours = info.uptime / 3600;
            int remaining = info.uptime % 3600;
            int minutes = remaining / 60;
            int seconds = remaining % 60;
            if (days > 0) 
                printf("%dd", days);
            if (hours > 0)
                printf("%dh", hours);
            if (minutes > 0)
                printf("%dm", minutes);
            if (seconds > 0)
                printf("%ds", seconds);
            printf("\n");
        } else
            printf("(null) (failed to get uptime)\n");
    }

    else
        fprintf(stderr, "wrong print_info() usage?\n");
}
