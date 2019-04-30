/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief LPC84X SCT �û������ļ�
 * \sa am_hwconf_lpc84x_sct0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  hgo, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc_sct.h"
#include "hw/amhw_lpc_sct.h"
#include "hw/amhw_lpc84x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_sct0
 * \copydoc am_hwconf_lpc84x_sct0.c
 * @{
 */

/**
 * \brief SCT �¼� ISR ��Ϣ����
 *
 * �û����Ը���Ӧ����ʵ������Ҫ�õ����¼��жϸ�����������֧�� 8 ����ͨ���޸ĸú�
 * ֵ���Դﵽ���˷��ڴ��Ŀ��
 */
#define __SCT_EVT_ISRINFO_COUNT    8

/** \brief SCT ���ͨ������ */
#define __SCT_OUTPUT_COUNT    6

/** \brief SCT DAM ����ͨ������ */
#define __SCT_DMA_REQ_COUNT    2

/** \brief �洢�û��жϻص���Ϣ */
am_local
struct am_lpc_sct_evt_isr_info __sct_evt_isr_info[__SCT_EVT_ISRINFO_COUNT];

/**
 * \brief �洢�жϺ������Ӧ�� __sct_evt_isr_info �жϻص���Ϣ��λ�õ�ӳ�䣬����
 *        ��Сһ���� SCT ��֧�ֵ�����¼������� __SCT_EVT_ISRINFO_COUNT ��ȡ�
 */
am_local uint8_t __sct_evt_isr_map[__SCT_EVT_ISRINFO_COUNT];

/**
 * \brief SCT0 ƽ̨��ʼ��
 */
am_local void __lpc84x_sct0_plfm_init (void)
{
	amhw_lpc84x_sct_clk_sel_set( AMHW_LPC84X_CLK_SCT_MAIN_CLK, 2);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SCT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SCT);
}

/**
 * \brief SCT0 ƽ̨���ʼ��
 */
am_local void __lpc84x_sct0_plfm_deinit (void)
{
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SCT);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_SCT);
}

/** \brief SCT �豸��Ϣ */
am_local am_const am_lpc_sct_devinfo_t __g_lpc84x_sct0_devinfo = {
    LPC84X_SCT0_BASE,             /* SCT0 �Ĵ��������ַ */
    INUM_SCT0,                    /* SCT0 �жϺ� */
    CLK_SCT,                      /* SCT0 ʱ�Ӻ� */
    __SCT_EVT_ISRINFO_COUNT,      /* ���ж����� */
    __sct_evt_isr_map,            /* ISR ��Ϣӳ���ڴ�(��С�� evt_isr_cnt һ��) */
    __SCT_EVT_ISRINFO_COUNT,      /* ISR ��Ϣ���� */
    __sct_evt_isr_info,           /* ISR ��Ϣ�ڴ�(��С�� isrinfo_cnt һ��) */

    __SCT_OUTPUT_COUNT,           /* 8 ��ͨ����� */
    __SCT_DMA_REQ_COUNT,          /* 2 �� DMA ����ͨ�� */
    __lpc84x_sct0_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc84x_sct0_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief SCT�豸ʵ�� */
am_local am_lpc_sct_dev_t __g_lpc84x_sct0_dev;

/**
 * \brief SCT0 ʵ����ʼ��
 */
am_lpc_sct_handle_t am_lpc84x_sct0_inst_init (void)
{
    return am_lpc_sct_init(&__g_lpc84x_sct0_dev, &__g_lpc84x_sct0_devinfo);
}

/**
 * \brief SCT0 ʵ�����ʼ��
 */
void am_lpc84x_sct0_inst_deinit (am_lpc_sct_handle_t handle)
{
    am_lpc_sct_deinit(handle);
}

/**
 * @}
 */

/* end of file */