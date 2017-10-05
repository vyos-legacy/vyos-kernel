/*******************************************************************************
 *
 * Intel Ethernet Controller XL710 Family Linux Driver
 * Copyright(c) 2013 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 ******************************************************************************/

#ifndef _I40E_ADMINQ_H_
#define _I40E_ADMINQ_H_

#include "i40e_osdep.h"
#include "i40e_adminq_cmd.h"

#define I40E_ADMINQ_DESC(R, i)   \
	(&(((struct i40e_aq_desc *)((R).desc))[i]))

#define I40E_ADMINQ_DESC_ALIGNMENT 4096

struct i40e_adminq_ring {
	void *desc;		/* Descriptor ring memory */
	void *details;		/* ASQ details */

	union {
		struct i40e_dma_mem *asq_bi;
		struct i40e_dma_mem *arq_bi;
	} r;

	u64 dma_addr;		/* Physical address of the ring */
	u16 count;		/* Number of descriptors */
	u16 rx_buf_len;		/* Admin Receive Queue buffer length */

	/* used for interrupt processing */
	u16 next_to_use;
	u16 next_to_clean;

	/* used for queue tracking */
	u32 head;
	u32 tail;
};

/* ASQ transaction details */
struct i40e_asq_cmd_details {
	void *callback; /* cast from type I40E_ADMINQ_CALLBACK */
	u64 cookie;
	u16 flags_ena;
	u16 flags_dis;
	bool async;
	bool postpone;
};

#define I40E_ADMINQ_DETAILS(R, i)   \
	(&(((struct i40e_asq_cmd_details *)((R).details))[i]))

/* ARQ event information */
struct i40e_arq_event_info {
	struct i40e_aq_desc desc;
	u16 msg_size;
	u8 *msg_buf;
};

/* Admin Queue information */
struct i40e_adminq_info {
	struct i40e_adminq_ring arq;    /* receive queue */
	struct i40e_adminq_ring asq;    /* send queue */
	u16 num_arq_entries;            /* receive queue depth */
	u16 num_asq_entries;            /* send queue depth */
	u16 arq_buf_size;               /* receive queue buffer size */
	u16 asq_buf_size;               /* send queue buffer size */
	u16 fw_maj_ver;                 /* firmware major version */
	u16 fw_min_ver;                 /* firmware minor version */
	u16 api_maj_ver;                /* api major version */
	u16 api_min_ver;                /* api minor version */

	struct mutex asq_mutex; /* Send queue lock */
	struct mutex arq_mutex; /* Receive queue lock */

	struct i40e_dma_mem asq_mem;    /* send queue dynamic memory */
	struct i40e_dma_mem arq_mem;    /* receive queue dynamic memory */

	/* last status values on send and receive queues */
	enum i40e_admin_queue_err asq_last_status;
	enum i40e_admin_queue_err arq_last_status;
};

/* general information */
#define I40E_AQ_LARGE_BUF	512
#define I40E_ASQ_CMD_TIMEOUT	100000  /* usecs */

void i40e_fill_default_direct_cmd_desc(struct i40e_aq_desc *desc,
				       u16 opcode);

#endif /* _I40E_ADMINQ_H_ */
