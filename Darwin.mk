CFLAGS		+=	-D__unix__ -I/usr/include/malloc/
CPPFLAGS	+=	-D__unix__ -I/usr/include/malloc/
FLTKDIR	    ?=	/usr/local/bin

#post:
#	/usr/local/bin/fltk-config --post virtualt
