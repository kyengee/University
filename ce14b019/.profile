# @(#)local.profile 1.8	99/03/26 SMI

setenv LANG ko_KR.UTF-8
stty erase  
PATH=.:/usr/bin:/usr/ucb:/usr/local/bin:/usr/local:/usr/local/share:/opt/SUNWspro/bin/cc:/usr/ccs/bin:/opt/vim-7.2/bin
export PATH
MANPATH=/usr/share/man:/usr/local/man

stty -istrip -parenb cs8
/bin/cat -s /etc/motd

#
# If possible, start the windows system
#
if [ "`tty`" = "/dev/console" ] ; then
	if [ "$TERM" = "sun" -o "$TERM" = "sun-color" -o "$TERM" = "AT386" ]
	then

		if [ ${OPENWINHOME:-""} = "" ] ; then
			OPENWINHOME=/usr/openwin
			export OPENWINHOME
		fi

		echo ""
		echo "Starting OpenWindows in 5 seconds (type Control-C to interrupt)"
		sleep 5
		echo ""
		$OPENWINHOME/bin/openwin

		clear		# get rid of annoying cursor rectangle
		exit		# logout after leaving windows system

	fi
fi
stty -istrip -parenb cs8
