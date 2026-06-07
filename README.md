# WARNING
expect trash and 20 year code from stack overflow, cuz it's me.


# what is this
sucklessfetch - is a fetch utility for linux written on C, it's just ez to configure, because it uses config.h as it's config, it's some kind of "sequel" to my utility - lightfetch, my and maybe ur goal, is to make cool and minimalistic fetch util, that is made in suckless style

# config
there is a `config.def.h` in the root directory of project, cp or mv it as `config.h`
modules explanation:
- uah - username and hostname
- separator - don't u understand it urself??
- distro - distro and its architecture
- shell - current shell
- terminal - current terminal
- ker_ver - kernel version
- locale - current locale
- uptime - system uptime

it looks like
```
cupped@void
**************************
distro - Void Linux x86_64
uptime - 10m10s
shell - /bin/bash
terminal - alacritty
kernel version - 6.18.34_1
locale - C
```

i'll add more modules soon, but you can also help me adding more of them

# compilation
just use `make` command

# installation
just use `doas/sudo make install` command

# uninstallation
just use `doas/sudo make uninstall` command

# clean
HOLY SHIT, just use `make clean` command, and read this 20 line `Makefile` already

plz contribute.
    - cupped
