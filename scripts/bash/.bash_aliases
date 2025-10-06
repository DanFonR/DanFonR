#!/bin/bash

rh () {
    hists=(".lesshst" ".viminfo" ".sudo_as_admin_successful" ".motd_shown")

    rm -f "${HOME}"/.*_history

    for file in "${hists[@]}"; do
        rm -f "${HOME}/${file}"
    done
}

UU () {
	if $(apt --version &> /dev/null); then # Debian/Ubuntu
		sudo apt update && (yes | sudo apt full-upgrade) \
		&& (yes | sudo apt autoremove)
	elif $(pacman --version &> /dev/null); then # Arch
		sudo pacman -Syu
	fi

	if $(snap --version &> /dev/null); then
		sudo snap refresh
	fi

	if $(flatpak --version &> /dev/null); then
		sudo flatpak update
	fi
}

vim () {
	if $(/usr/bin/nvim --version &> /dev/null); then
		/usr/bin/nvim "$@"
	elif $(/usr/bin/vim --version &> /dev/null); then
		/usr/bin/vim "$@"
	else
		nano "$@"
	fi
}

nasml () {
	nasm -f elf64 $1 && ld ${1%.asm}.o -o ${1%.asm} && rm ${1%.asm}.o
}

run () {
	if $(/usr/bin/clang --version &> /dev/null); then
		clang "$@" && ./a.out && rm a.out
	else
		gcc "$@" && ./a.out && rm a.out
	fi
}

battery () {
	printf "%s%%\n" \
    $(cat /sys/class/power_supply/BAT0/capacity 2>/dev/null \
    || cat /sys/class/power_supply/BAT1/capacity 2>/dev/null)
}

venv () {
    if [ -d "./.venv/" ]; then
        . ./.venv/bin/activate
    fi
}

PUU () {
    for pkg in $(pip list -o | tail -n +3 | awk '{print $1}');
    do
		printf "%s " $pkg
        pip install -U "$pkg" &> /dev/null && echo "upgraded" || {
			echo "unable to upgrade"
			break
		}
    done
}

alias CC="rh && history -c"
alias CCC="CC && clear"
alias UCE="UU && CCC && exit"
alias CE="CC && exit"
alias UC="UU && CC"
alias UCC="UU && CCC"
alias la="ls -A"
alias aliases="vim .bash_aliases"
