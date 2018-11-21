# @(#)local.profile 1.8 99/03/26 SMI

## setting PATH
PATH="/usr/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local:/usr/local/sbin:/usr/ucb:/etc:."
export PATH
export PATH="$PATH:/usr/local/bin:/bin:/usr/bin:/usr/sbin:/sbin:/usr/local:/usr/local/sbin:/usr/local/lib:/usr/local/share:/usr/local/samba/bin:/usr/ucb:/opt/SUNWspro/bin/cc:/etc:."

## setting library path
export LD_LIBRARY_PATH="/usr/lib:/usr/local/lib:/usr/openwin/lib:/opt/SUNWspro/lib:/usr/dt/lib"

## MANPATH  03/09/03
export MANPATH=/usr/share/man:/usr/local/man

## setting terminal 
stty istrip
stty erase ^H
stty -parenb -istrip cs8 -ixon defeucw

## setting library path
export LD_LIBRARY_PATH="/usr/lib:/usr/local/lib:/usr/openwin/lib:/opt/SUNWspro/lib:/usr/dt/lib"

    
### set prompt shape: [user@hostname current-directory]%
#set prompt=\[`id -nu`@`hostname -s`\]\%\ 
### another 
#set prompt="`whoami`% "
### the other
### set prompt shape s.t. hostname[current directory]%
#alias setprompt='set prompt = "bird[$cwd:t]%"'
alias setprompt='set prompt="[`hostname`@`whoami`:$cwd:t]% "'
alias cd='set back = $cwd; chdir \!*;setprompt'
setprompt
### or 
#alias setprompt='set prompt="[`hostname`@`whoami`:$cwd \! ]# "'

## setting alias 
#alias ls='ls -aFi'
alias df='df -k'
#alias so='source ~/.cshrc'
alias k='kill -9'
alias h='history'
alias vi='/usr/local/bin/vim'
alias ls='/usr/local/bin/ls -aF --color'
alias ll='/usr/local/bin/ls -alF --color'
alias useradd='/usr/sbin/useradd'
alias edquota='/usr/sbin/edquota'
alias dict='$HOME/myDic/dict'

export TERM=vt100
export LANG=ko
#export EDITOR=vim
export EDITOR=emacs

#
# If possible, start the windows system
#
if [ "`tty`" = "/dev/console" ] ; then
	if [ "$TERM" = "sun" -o "$TERM" = "sun-color" -o "$TERM" = "AT386" ]; then
		if [ ${OPENWINHOME:-""} = "" ] ; then
			OPENWINHOME=/usr/openwin
			export OPENWINHOME
		fi

		echo ""
		echo "Starting OpenWindows in 5 seconds (type Control-C to interrupt)"
		sleep 5
		echo ""
		$OPENWINHOME/bin/openwin

		clear       # get rid of annoying cursor rectangle
		exit        # logout after leaving windows system
	fi
fi

umask 022

if [ $prompt ]; then
    set history=32
fi

