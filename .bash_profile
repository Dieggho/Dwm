#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

export QT_QPA_PLATFORMTHEME=qt5ct
export QT_PLATFORMTHEME=qt5ct
export QT_PLATFORM_PLUGIN=qt5ct

export PATH=$PATH:$HOME/.local/bin

/home/$USER/.fehbg &
xset -dpms s off &
slstatus &
xcompmgr &
devmon &
#xbindkeys &
