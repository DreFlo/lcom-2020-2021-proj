PROG=proj

SRCS = proj.c timer.c utils.c graphics.c keyboard.c gamePlay.c devices.c asprite.c entity.c tiles.c game_physics.c mouse.c game.c file.c rtc.c proj_utils.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
