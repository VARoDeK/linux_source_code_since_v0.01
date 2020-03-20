/*
 *	ultrastor.c	(C) 1991 David B. Gentzel
 *	Low-level scsi driver for UltraStor 14F
 *	by David B. Gentzel, Whitfield Software Services, Carnegie, PA
 *	    (gentzel@nova.enet.dec.com)
 *  scatter/gather added by Scott Taylor (n217cg@tamuts.tamu.edu)
 *	Thanks to UltraStor for providing the necessary documentation
 */

#ifndef _ULTRASTOR_H
#define _ULTRASTOR_H

/* ??? These don't really belong here */
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

int ultrastor_detect(int);
const char *ultrastor_info(void);
int ultrastor_queuecommand(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *));
int ultrastor_abort(Scsi_Cmnd *, int);
int ultrastor_reset(void);
int ultrastor_biosparam(int, int, int *);

#define ULTRASTOR_14F_MAX_CMDS 1 /*???*/
#define ULTRASTOR_14F_MAX_SG 16  /* Should be 32, but 32 doesn't work */
#define ULTRASTOR_14F_MAX_CMDS_PER_LUN 1 /*???*/

#define ULTRASTOR_14F \
    { "UltraStor 14F", ultrastor_detect, ultrastor_info, 0, \
      ultrastor_queuecommand, ultrastor_abort, ultrastor_reset, \
      0, ultrastor_biosparam, ULTRASTOR_14F_MAX_CMDS, 0, \
      ULTRASTOR_14F_MAX_SG, ULTRASTOR_14F_MAX_CMDS_PER_LUN, 0, 0 }

#ifdef ULTRASTOR_PRIVATE

#define UD_ABORT 0x0001
#define UD_COMMAND 0x0002
#define UD_DETECT 0x0004
#define UD_INTERRUPT 0x0008
#define UD_RESET 0x0010

/* #define PORT_OVERRIDE 0x330 */

/* Port addresses (relative to the base address) */
#define LCL_DOORBELL_MASK(port) ((port) + 0x0)
#define LCL_DOORBELL_INTR(port) ((port) + 0x1)
#define SYS_DOORBELL_MASK(port) ((port) + 0x2)
#define SYS_DOORBELL_INTR(port) ((port) + 0x3)
#define PRODUCT_ID(port) ((port) + 0x4)
#define CONFIG(port) ((port) + 0x6)
#define OGM_DATA_PTR(port) ((port) + 0x8)
#define ICM_DATA_PTR(port) ((port) + 0xC)

/* Values for the PRODUCT_ID ports for the 14F */
#define US14F_PRODUCT_ID_0 0x56
#define US14F_PRODUCT_ID_1 0x40		/* NOTE: Only upper nibble is used */

/* Subversion values */
#define U14F 0
#define U34F 1

/* MSCP field values */

/* Opcode */
#define OP_HOST_ADAPTER 0x1
#define OP_SCSI 0x2
#define OP_RESET 0x4

/* Date Transfer Direction */
#define DTD_SCSI 0x0
#define DTD_IN 0x1
#define DTD_OUT 0x2
#define DTD_NONE 0x3

/* Host Adapter command subcodes */
#define HA_CMD_INQUIRY 0x1
#define HA_CMD_SELF_DIAG 0x2
#define HA_CMD_READ_BUFF 0x3
#define HA_CMD_WRITE_BUFF 0x4

#endif

#endif
