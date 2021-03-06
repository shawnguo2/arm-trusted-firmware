/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <debug.h>
#include <plat_arm.h>
#include <platform_def.h>
#include <sgm_plat_config.h>
#include <sgm_variant.h>
#include <string.h>

static css_plat_config_t *css_plat_info;

/* Interconnect */
const css_inteconn_config_t sgm_inteconn = {
	.ip_type = ARM_CCI,
	.plat_inteconn_desc = NULL
};

/* Special definition for SGM775 */
/* Topology configuration for SGM775 */
const unsigned char sgm775_power_domain_tree_desc[] = {
	/* No of root nodes */
	ARM_SYSTEM_COUNT,
	/* No of children for the root node */
	PLAT_ARM_CLUSTER_COUNT,
	/* No of children for the first cluster node */
	PLAT_ARM_CLUSTER_CORE_COUNT,
};

const css_topology_t sgm775_topology = {
	.power_tree = sgm775_power_domain_tree_desc,
	.plat_cluster_core_count = PLAT_ARM_CLUSTER_CORE_COUNT
};

/* Configuration structure for SGM775 */
css_plat_config_t sgm775_config = {
	.inteconn = &sgm_inteconn,
	.topology = &sgm775_topology
};

/*******************************************************************************
 * This function initializes the platform structure.
 ******************************************************************************/
void plat_config_init(void)
{
	/* Get the platform configurations */
	switch (GET_PLAT_PART_NUM) {
	case SGM775_SSC_VER_PART_NUM:
		css_plat_info = &sgm775_config;

		break;
	default:
		ERROR("Not a valid sgm variant!\n");
		panic();
	}
}

/*******************************************************************************
 * This function returns the platform structure pointer.
 ******************************************************************************/
css_plat_config_t *get_plat_config(void)
{
	assert(css_plat_info != NULL);
	return css_plat_info;
}

#if TRUSTED_BOARD_BOOT && LOAD_IMAGE_V2
int plat_get_mbedtls_heap(void **heap_addr, size_t *heap_size)
{
	assert(heap_addr != NULL);
	assert(heap_size != NULL);

	return arm_get_mbedtls_heap(heap_addr, heap_size);
}
#endif
