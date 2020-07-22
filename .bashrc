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
PS1='\[\033[01;34m\]\u@\h\[\033[00m\]:\[\033[01;38m\]\w\[\033[00m\]\$ '



## Colorize the ls output ##
alias ls='ls --color=auto'

# Remove orphan packages
alias pacro="/usr/bin/pacman -Qtdq > /dev/null && sudo /usr/bin/pacman -Rns \$(/usr/bin/pacman -Qtdq | sed -e ':a;N;$!ba;s/\n/ /g')"


##
alias pac="sudo /usr/bin/pacman -S"			# default action	- install one or more packages
alias pacup="sudo /usr/bin/pacmatic -Syyu"	        # '[u]pdate'		- upgrade all packages to their newest version
alias pacr="sudo /usr/bin/pacman -Rns"			# '[r]emove'		- uninstall one or more packages
alias pacs="/usr/bin/pacman -Ss"			# '[s]earch'		- search for a package using one or more keywords
alias paci="/usr/bin/pacman -Si"			# '[i]nfo'		- show information about a package
alias paclo="/usr/bin/pacman -Qdt"			# '[l]ist [o]rphans'	- list all packages which are orphaned
alias pacc="sudo /usr/bin/pacman -Scc"			# '[c]lean cache'	- delete all not currently installed package files
alias paclf="/usr/bin/pacman -Ql"			# '[l]ist [f]iles'	- list all files installed by a given package
alias pacexpl="sudo /usr/bin/pacman -D --asexp"		# 'mark as [expl]icit'	- mark one or more packages as explicitly installed 
alias pacimpl="sudo /usr/bin/pacman -D --asdep"		# 'mark as [impl]icit'	- mark one or more packages as non explicitly installed
alias pacdi="pacman -Q"					# Display all installed packages
alias pacdf="pacman -Qm"				# Display foreign packages
alias pacde="pacman -Qet"				# Display explicit packages

##
alias fpk="flatpak install"
alias fpkup="flatpak update"
alias fpkr="flatpak remove"
alias fpks="flatpak search"
alias fpkl="flatpak list"
alias fpkrn="flatpak run"

##
#alias qemu="qemu-system-x86_64 -m 1524 -vga std -enable-kvm -cpu host"
alias xclass="xprop | grep CLASS"
alias shrc="nano ~/.bashrc"
alias myip="curl ident.me;echo"
alias weather="curl -4 http://wttr.in/Sao-Paulo"

alias myarch="archey3;pacman --version"
alias myip="curl ifconfig.co"

export QT_QPA_PLATFORMTHEME=qt5ct
export QT_PLATFORMTHEME=qt5ct
export QT_PLATFORM_PLUGIN=qt5ct



