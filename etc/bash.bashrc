# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=
export EDITOR=nano
export PATH=$PATH:$HOME/.sh

# User specific aliases and functions
PS1='\[\033[01;31m\]\u@\h\[\033[00m\]:\[\033[01;38m\]\w\[\033[00m\]\$ '



## Colorize the ls output ##
alias ls='ls --color=auto'

# Remove orphan packages
alias pacro="/usr/bin/pacman -Qtdq > /dev/null &&  /usr/bin/pacman -Rns \$(/usr/bin/pacman -Qtdq | sed -e ':a;N;$!ba;s/\n/ /g')"


##
alias pac="/usr/bin/pacman -S"			        # default action	- install one or more packages
alias pacup="/usr/bin/pacmatic -Syyu"	                # '[u]pdate'            - upgrade all packages to their newest version
alias pacr="/usr/bin/pacman -Rns"			# '[r]emove'		- uninstall one or more packages
alias pacs="/usr/bin/pacman -Ss"			# '[s]earch'		- search for a package using one or more keywords
alias paci="/usr/bin/pacman -Si"			# '[i]nfo'		- show information about a package
alias paclo="/usr/bin/pacman -Qdt"			# '[l]ist [o]rphans'	- list all packages which are orphaned
alias pacc="/usr/bin/pacman -Scc"			# '[c]lean cache'	- delete all not currently installed package files
alias paclf="/usr/bin/pacman -Ql"			# '[l]ist [f]iles'	- list all files installed by a given package
alias pacexpl="/usr/bin/pacman -D --asexp"		# 'mark as [expl]icit'	- mark one or more packages as explicitly installed 
alias pacimpl="/usr/bin/pacman -D --asdep"		# 'mark as [impl]icit'	- mark one or more packages as non explicitly installed
alias pacdi="pacman -Q"					# Display all installed packages
alias pacdf="pacman -Qm"				# Display foreign packages
alias pacde="pacman -Qet"				# Display explicit packages

##
#alias qemu="qemu-system-x86_64 -m 1524 -vga std -enable-kvm -cpu host"
alias xclass="xprop | grep CLASS"
alias myip="curl ident.me;echo"
alias clean="rm -vr /home/$USER/.cache/* && rm -vr /home/$USER/.thumbnails/*"
alias weather="curl -4 http://wttr.in/Sao-Paulo"


export QT_QPA_PLATFORMTHEME=qt5ct
export QT_PLATFORMTHEME=qt5ct
export QT_PLATFORM_PLUGIN=qt5ct
#printf '\033[?1h\033=' >/dev/tty
