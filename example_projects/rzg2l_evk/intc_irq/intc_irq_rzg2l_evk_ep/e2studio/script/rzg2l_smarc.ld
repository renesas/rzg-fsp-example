/*
                  Linker File for Renesas FSP
*/

/* Memory allocation example using ddr. */
VECTBL_N_START          = 0x00010000;
VECTBL_N_LENGTH         = 0x00000800;
VECTBL_S_START          = 0x1001FF80;
VECTBL_S_LENGTH         = 0x00000080;

CODE_N_START            = 0x60010000;
CODE_N_LENGTH           = 0x00100000;
RAM_N_START             = 0x60110000;
RAM_N_LENGTH            = 0x02DEF440;
CODE_S_START            = 0x72EFF440;
CODE_S_LENGTH           = 0x000003C0;
RAM_S_START             = 0x72EFF800;
RAM_S_LENGTH            = 0x00000800;

DDR_START               = 0x60010000;
DDR_LENGTH              = 0x03EF0000;

OPENAMP_RSCTBL_START    = 0x62F00000;
OPENAMP_RSCTBL_LENGTH   = 0x00001000;
MHU_SHMEM_START         = 0x62F01000;
MHU_SHMEM_LENGTH        = 0x00001000;
OPENAMP_VRING_START     = 0x63000000;
OPENAMP_VRING_LENGTH    = 0x00800000;


/* When using OpenAMP, allocate the length of the OpenAMP relevant region. */
OPENAMP_RSCTBL_START    = DEFINED(OPENAMP_RSCTBL_START) ? OPENAMP_RSCTBL_START  : 0;
OPENAMP_RSCTBL_LENGTH   = DEFINED(OPENAMP_RSCTBL_LENGTH)? OPENAMP_RSCTBL_LENGTH : 0;
MHU_SHMEM_START         = DEFINED(MHU_SHMEM_START)      ?      MHU_SHMEM_START  : 0;
MHU_SHMEM_LENGTH        = DEFINED(MHU_SHMEM_LENGTH)     ?      MHU_SHMEM_LENGTH : 0;
OPENAMP_VRING_START     = DEFINED(OPENAMP_VRING_START)  ?  OPENAMP_VRING_START  : 0;
OPENAMP_VRING_LENGTH    = DEFINED(OPENAMP_VRING_LENGTH) ?  OPENAMP_VRING_LENGTH : 0;
/* Define memory regions. */
MEMORY
{
  RAM_S (rwx)       : ORIGIN = RAM_S_START,         LENGTH = RAM_S_LENGTH
  RAM_N (rwx)       : ORIGIN = RAM_N_START,         LENGTH = RAM_N_LENGTH
  CODE_S (rx)       : ORIGIN = CODE_S_START,        LENGTH = CODE_S_LENGTH
  CODE_N (rx)       : ORIGIN = CODE_N_START,        LENGTH = CODE_N_LENGTH
  VECTTBL_S (rx)    : ORIGIN = VECTBL_S_START,      LENGTH = VECTBL_S_LENGTH
  VECTTBL_N (rx)    : ORIGIN = VECTBL_N_START,      LENGTH = VECTBL_N_LENGTH
  OPENAMP_RSCTBL(rw): ORIGIN = OPENAMP_RSCTBL_START,LENGTH = OPENAMP_RSCTBL_LENGTH
  MHU_SHMEM(rw)     : ORIGIN = MHU_SHMEM_START,     LENGTH = MHU_SHMEM_LENGTH
  OPENAMP_VRING(rw) : ORIGIN = OPENAMP_VRING_START, LENGTH = OPENAMP_VRING_LENGTH
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions CODE, RAM and etc.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler_S : Entry of secure reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */
ENTRY(Warm_Reset_S)
SECTIONS
{
    __tz_VECTBL_S = ABSOLUTE(VECTBL_S_START);
    . = __tz_VECTBL_S;

    .text.secure_vector :
    {
        /* Even though the vector table is not 16 entries (64B) long, we still allocate that much space. */
        KEEP(*(.fixed_secure_vectors*))
    } >VECTTBL_S

    __tz_CODE_S = ABSOLUTE(CODE_S_START);
    . = __tz_CODE_S;

    .text.secure_code :
    {
        *\bsp_security.o (.text)
        *\bsp_security.o (.text.*)
        *\bsp_security.o (.rodata)
        *\bsp_security.o (.rodata.*)
        *\bsp_irqs.o (.text)
        *\bsp_irqs.o (.text.*)
        *\bsp_irqs.o (.rodata)
        *\bsp_irqs.o (.rodata.*)
        *\startups.o (.text)
        *\startups.o (.text.*)
        *\startups.o (.rodata)
        *\startups.o (.rodata.*)
        *\systems.o (.text)
        *\systems.o (.text.*)
        *\systems.o (.rodata)
        *\systems.o (.rodata.*)

        __CODE_S_End = .;
    } >CODE_S

    __tz_RAM_S = ABSOLUTE(RAM_S_START);
    . = __tz_RAM_S;

    /* secure stacks are stored in this section. */
    .stack_dummy (NOLOAD) :
    {
        __S_StackLimit = .;
        /* secure main stack */
        KEEP(*(.s_stack))
        __S_StackTop = .;
    } >RAM_S

    /* start at address VECTBL_N_START */
    __tz_VECTBL_N = ABSOLUTE(VECTBL_N_START);
    . = __tz_VECTBL_N;
    .text.non_secure_vector :
    {
        /* Even though the vector table is not 512 entries (2KB) long, we still allocate that much space. */
        KEEP(*(.fixed_vectors*))
        KEEP(*(.application_vectors*))
        __Vectors_End = .;
    } >VECTTBL_N

    __Vectors_Size = __Vectors_End - __Vectors;

    /* start at address CODE_N_START */
    __tz_CODE_N = ABSOLUTE(CODE_N_START);
    . = __tz_CODE_N;

    .text.non_secure_code :
    {
        *(.text*)
        KEEP(*(.version))
        KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(* crtend?.o * crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        *(.rodata*)
        KEEP(*(.eh_frame*))
    } >CODE_N

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > CODE_N
    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > CODE_N
    __exidx_end = .;
    /* To copy multiple CODE_N to RAM_N sections,
     * uncomment .copy.table section and,
     * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
    /*
     * .copy.table :
     * {
     *     . = ALIGN(4);
     *     __copy_table_start__ = .;
     *     LONG (__etext)
     *     LONG (__data_start__)
     *     LONG (__data_end__ - __data_start__)
     *     LONG (__etext2)
     *     LONG (__data2_start__)
     *     LONG (__data2_end__ - __data2_start__)
     *     __copy_table_end__ = .;
     * } > CODE_N
     */
    /* To clear multiple BSS sections,
     * uncomment .zero.table section and,
     * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
    /*
     * .zero.table :
     * {
     *     . = ALIGN(4);
     *     __zero_table_start__ = .;
     *     LONG (__bss_start__)
     *     LONG (__bss_end__ - __bss_start__)
     *     LONG (__bss2_start__)
     *     LONG (__bss2_end__ - __bss2_start__)
     *     __zero_table_end__ = .;
     * } > CODE_N
     */
    __etext = .;
    __tz_RAM_N = ABSOLUTE(RAM_N_START);
    . = __tz_RAM_N;
    /* Initialized data section. */
    .data :
    {
        __data_start__ = .;
        . = ALIGN(4);
        __Code_In_RAM_Start = .;
        KEEP(*(.code_in_ram*))
        __Code_In_RAM_End = .;
        *(vtable)
        /* Don't use *(.data*) because it will place data meant for .data_flash in this section. */
        *(.data.*)
        *(.data)
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN(__fini_array_end = .);
        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > RAM_N AT > CODE_N
    .bss.noinit (NOLOAD) :
    {
        . = ALIGN(4);
        __noinit_start = .;
        KEEP(*(.noinit*))
        . = ALIGN(8);
        /* Place the FreeRTOS heap here so that the __HeapLimit calculation does not include the freertos heap. */
        KEEP(*(.heap.*))
        __noinit_end = .;
    } > RAM_N
    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM_N
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        __HeapBase = .;
        /* Place the STD heap here. */
        KEEP(*(.heap))
        __HeapLimit = .;
    } > RAM_N
    /* Stacks are stored in this section. */
    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        __StackLimit = .;
        /* Main stack */
        KEEP(*(.stack))
        __StackTop = .;
        /* Thread stacks */
        KEEP(*(.stack*))
        __StackTopAll = .;
    } > RAM_N
    PROVIDE(__stack = __StackTopAll);
    /* This symbol represents the end of user allocated RAM. The RAM after this symbol can be used
     at run time for things such as ThreadX memory pool allocations. */
    __RAM_segment_used_end__ = ALIGN(__StackTopAll , 4);

    PROVIDE(__tz_RAM_C = __RAM_segment_used_end__);

    __tz_OPENAMP_RSCTBL = ABSOLUTE(OPENAMP_RSCTBL_START);
    . = __tz_OPENAMP_RSCTBL;

    /* OpenAMP resource table */
    .bss.resource_table (NOLOAD) :
    {
        PROVIDE(__rsctbl_start = .);
        *(.resource_table)
        PROVIDE(__rsctbl_end = .);
    } > OPENAMP_RSCTBL

    __tz_MHU_SHMEM = ABSOLUTE(MHU_SHMEM_START);
    . = __tz_MHU_SHMEM;

    /* MHU driver shared memory */
    .bss.mhu_shmem (NOLOAD) :
    {
        PROVIDE(__mhu_shmem_start = .);
        . += MHU_SHMEM_LENGTH;
        PROVIDE(__mhu_shmem_end = .);
    } > MHU_SHMEM

    __tz_OPENAMP_VRING = ABSOLUTE(OPENAMP_VRING_START);
    . = __tz_OPENAMP_VRING;

    /* OpenAMP VRINGresource table */
    .bss.vring (NOLOAD) :
    {
        PROVIDE(__vring_start = .);
        . += OPENAMP_VRING_LENGTH;
        PROVIDE(__vring_end = .);
    } > OPENAMP_VRING

}
