#!/bin/bash
# The script must be used on DWM with the "ewmhtags" patch applied
# it's a workaround for the case you can't apply the patch "nextprev"  
#

desk=$(xprop -root | grep "_NET_CURRENT_DESKTOP(CARDINAL)" | awk '{print $3}')

case $1 in
	next)
		xdo key_press -k 133; xdo key_press -k `expr $desk + 11`; xdo key_release -k 133;  xdo key_release -k `expr $desk + 11`
	;;
	prev)
		xdo key_press -k 133; xdo key_press -k `expr $desk + 9`; xdo key_release -k 133;  xdo key_release -k `expr $desk + 9`
	;;
esac