	.text
	.file	"thread.c"
	.globl	thread_routine                  # -- Begin function thread_routine
	.p2align	4, 0x90
	.type	thread_routine,@function
thread_routine:                         # @thread_routine
.Lfunc_begin0:
	.file	1 "/home/adjelili/Desktop/M3/Philosophers" "thread.c"
	.loc	1 26 0                          # thread.c:26:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
.Ltmp0:
	.loc	1 32 8 prologue_end             # thread.c:32:8
	callq	pthread_self
	.loc	1 32 6 is_stmt 0                # thread.c:32:6
	movq	%rax, -16(%rbp)
	.loc	1 33 26 is_stmt 1               # thread.c:33:26
	movq	-8(%rbp), %rax
	.loc	1 33 8 is_stmt 0                # thread.c:33:8
	movq	%rax, -24(%rbp)
	.loc	1 37 11 is_stmt 1               # thread.c:37:11
	movq	-16(%rbp), %rdx
	.loc	1 37 17 is_stmt 0               # thread.c:37:17
	movq	-24(%rbp), %rax
	.loc	1 37 16                         # thread.c:37:16
	movl	(%rax), %ecx
	.loc	1 36 2 is_stmt 1                # thread.c:36:2
	movabsq	$.L.str, %rdi
	movabsq	$.L.str.1, %rsi
	movabsq	$.L.str.2, %r8
	movb	$0, %al
	callq	printf
	.loc	1 38 4                          # thread.c:38:4
	movl	$0, -28(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	.loc	1 39 11                         # thread.c:39:11
	cmpl	$21000, -28(%rbp)               # imm = 0x5208
	.loc	1 39 2 is_stmt 0                # thread.c:39:2
	jae	.LBB0_3
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
.Ltmp1:
	.loc	1 43 5 is_stmt 1                # thread.c:43:5
	movq	-24(%rbp), %rax
	.loc	1 43 11 is_stmt 0               # thread.c:43:11
	movl	(%rax), %ecx
	addl	$1, %ecx
	movl	%ecx, (%rax)
	.loc	1 44 4 is_stmt 1                # thread.c:44:4
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
.Ltmp2:
	.loc	1 39 2                          # thread.c:39:2
	jmp	.LBB0_1
.LBB0_3:
	.loc	1 49 12                         # thread.c:49:12
	movq	-16(%rbp), %rdx
	.loc	1 49 18 is_stmt 0               # thread.c:49:18
	movq	-24(%rbp), %rax
	.loc	1 49 17                         # thread.c:49:17
	movl	(%rax), %ecx
	.loc	1 48 2 is_stmt 1                # thread.c:48:2
	movabsq	$.L.str.3, %rdi
	movabsq	$.L.str.4, %rsi
	movabsq	$.L.str.2, %r8
	movb	$0, %al
	callq	printf
	.loc	1 50 2                          # thread.c:50:2
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp3:
.Lfunc_end0:
	.size	thread_routine, .Lfunc_end0-thread_routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
.Lfunc_begin1:
	.loc	1 54 0                          # thread.c:54:0
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movl	$0, -4(%rbp)
.Ltmp4:
	.loc	1 62 8 prologue_end             # thread.c:62:8
	movl	$0, -68(%rbp)
	.loc	1 63 2                          # thread.c:63:2
	leaq	-64(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_mutex_init
	.loc	1 67 2                          # thread.c:67:2
	movabsq	$.L.str.5, %rdi
	movabsq	$.L.str.6, %rsi
	movl	$42000, %edx                    # imm = 0xA410
	movabsq	$.L.str.2, %rcx
	movb	$0, %al
	callq	printf
	.loc	1 70 46                         # thread.c:70:46
	leaq	-68(%rbp), %rcx
	.loc	1 70 2 is_stmt 0                # thread.c:70:2
	leaq	-16(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	movabsq	$thread_routine, %rdx
	callq	pthread_create
	.loc	1 71 53 is_stmt 1               # thread.c:71:53
	movq	-16(%rbp), %rsi
	.loc	1 71 2 is_stmt 0                # thread.c:71:2
	movabsq	$.L.str.7, %rdi
	movb	$0, %al
	callq	printf
	.loc	1 72 46 is_stmt 1               # thread.c:72:46
	leaq	-68(%rbp), %rcx
	.loc	1 72 2 is_stmt 0                # thread.c:72:2
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	movabsq	$thread_routine, %rdx
	callq	pthread_create
	.loc	1 73 52 is_stmt 1               # thread.c:73:52
	movq	-24(%rbp), %rsi
	.loc	1 73 2 is_stmt 0                # thread.c:73:2
	movabsq	$.L.str.8, %rdi
	movb	$0, %al
	callq	printf
	.loc	1 75 15 is_stmt 1               # thread.c:75:15
	movq	-16(%rbp), %rdi
	.loc	1 75 2 is_stmt 0                # thread.c:75:2
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	.loc	1 76 50 is_stmt 1               # thread.c:76:50
	movq	-16(%rbp), %rsi
	.loc	1 76 2 is_stmt 0                # thread.c:76:2
	movabsq	$.L.str.9, %rdi
	movb	$0, %al
	callq	printf
	.loc	1 77 15 is_stmt 1               # thread.c:77:15
	movq	-24(%rbp), %rdi
	.loc	1 77 2 is_stmt 0                # thread.c:77:2
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	.loc	1 78 49 is_stmt 1               # thread.c:78:49
	movq	-24(%rbp), %rsi
	.loc	1 78 2 is_stmt 0                # thread.c:78:2
	movabsq	$.L.str.10, %rdi
	movb	$0, %al
	callq	printf
.Ltmp5:
	.loc	1 80 12 is_stmt 1               # thread.c:80:12
	cmpl	$42000, -68(%rbp)               # imm = 0xA410
.Ltmp6:
	.loc	1 80 6 is_stmt 0                # thread.c:80:6
	je	.LBB1_2
# %bb.1:
.Ltmp7:
	.loc	1 81 59 is_stmt 1               # thread.c:81:59
	movl	-68(%rbp), %edx
	.loc	1 81 3 is_stmt 0                # thread.c:81:3
	movabsq	$.L.str.11, %rdi
	movabsq	$.L.str.12, %rsi
	movabsq	$.L.str.2, %rcx
	movb	$0, %al
	callq	printf
	jmp	.LBB1_3
.LBB1_2:
	.loc	1 83 58 is_stmt 1               # thread.c:83:58
	movl	-68(%rbp), %edx
	.loc	1 83 5 is_stmt 0                # thread.c:83:5
	movabsq	$.L.str.13, %rdi
	movabsq	$.L.str.6, %rsi
	movabsq	$.L.str.2, %rcx
	movb	$0, %al
	callq	printf
.Ltmp8:
.LBB1_3:
	.loc	1 84 2 is_stmt 1                # thread.c:84:2
	xorl	%eax, %eax
	addq	$80, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Ltmp9:
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%sThread [%ld]: compte au depart = %u.%s\n"
	.size	.L.str, 42

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"\033[33m"
	.size	.L.str.1, 6

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"\033[0m"
	.size	.L.str.2, 5

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"%sThread [%ld]: Compte final = %u.%s\n"
	.size	.L.str.3, 38

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"\033[1;33m"
	.size	.L.str.4, 8

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"Main: Le compte attendu est de %s%u%s\n"
	.size	.L.str.5, 39

	.type	.L.str.6,@object                # @.str.6
.L.str.6:
	.asciz	"\033[32m"
	.size	.L.str.6, 6

	.type	.L.str.7,@object                # @.str.7
.L.str.7:
	.asciz	"Main: Creation du premier thread [%ld]\n"
	.size	.L.str.7, 40

	.type	.L.str.8,@object                # @.str.8
.L.str.8:
	.asciz	"Main: Creation du second thread [%ld]\n"
	.size	.L.str.8, 39

	.type	.L.str.9,@object                # @.str.9
.L.str.9:
	.asciz	"Main: Union du premier thread [%ld]\n"
	.size	.L.str.9, 37

	.type	.L.str.10,@object               # @.str.10
.L.str.10:
	.asciz	"Main: Union du second thread [%ld]\n"
	.size	.L.str.10, 36

	.type	.L.str.11,@object               # @.str.11
.L.str.11:
	.asciz	"%sMain: ERREUR ! Le compte est de %u%s\n"
	.size	.L.str.11, 40

	.type	.L.str.12,@object               # @.str.12
.L.str.12:
	.asciz	"\033[31m"
	.size	.L.str.12, 6

	.type	.L.str.13,@object               # @.str.13
.L.str.13:
	.asciz	"%sMain: OK. Le compte est de %u%s\n"
	.size	.L.str.13, 35

	.file	2 "/usr/include/x86_64-linux-gnu/bits" "pthreadtypes.h"
	.file	3 "/usr/include/x86_64-linux-gnu/bits" "struct_mutex.h"
	.file	4 "/usr/include/x86_64-linux-gnu/bits" "thread-shared-types.h"
	.section	.debug_abbrev,"",@progbits
	.byte	1                               # Abbreviation Code
	.byte	17                              # DW_TAG_compile_unit
	.byte	1                               # DW_CHILDREN_yes
	.byte	37                              # DW_AT_producer
	.byte	14                              # DW_FORM_strp
	.byte	19                              # DW_AT_language
	.byte	5                               # DW_FORM_data2
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	16                              # DW_AT_stmt_list
	.byte	23                              # DW_FORM_sec_offset
	.byte	27                              # DW_AT_comp_dir
	.byte	14                              # DW_FORM_strp
	.byte	17                              # DW_AT_low_pc
	.byte	1                               # DW_FORM_addr
	.byte	18                              # DW_AT_high_pc
	.byte	6                               # DW_FORM_data4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	2                               # Abbreviation Code
	.byte	15                              # DW_TAG_pointer_type
	.byte	0                               # DW_CHILDREN_no
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	3                               # Abbreviation Code
	.byte	36                              # DW_TAG_base_type
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	62                              # DW_AT_encoding
	.byte	11                              # DW_FORM_data1
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	4                               # Abbreviation Code
	.byte	15                              # DW_TAG_pointer_type
	.byte	0                               # DW_CHILDREN_no
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	5                               # Abbreviation Code
	.byte	46                              # DW_TAG_subprogram
	.byte	1                               # DW_CHILDREN_yes
	.byte	17                              # DW_AT_low_pc
	.byte	1                               # DW_FORM_addr
	.byte	18                              # DW_AT_high_pc
	.byte	6                               # DW_FORM_data4
	.byte	64                              # DW_AT_frame_base
	.byte	24                              # DW_FORM_exprloc
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	39                              # DW_AT_prototyped
	.byte	25                              # DW_FORM_flag_present
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	63                              # DW_AT_external
	.byte	25                              # DW_FORM_flag_present
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	6                               # Abbreviation Code
	.byte	5                               # DW_TAG_formal_parameter
	.byte	0                               # DW_CHILDREN_no
	.byte	2                               # DW_AT_location
	.byte	24                              # DW_FORM_exprloc
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	7                               # Abbreviation Code
	.byte	52                              # DW_TAG_variable
	.byte	0                               # DW_CHILDREN_no
	.byte	2                               # DW_AT_location
	.byte	24                              # DW_FORM_exprloc
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	8                               # Abbreviation Code
	.byte	22                              # DW_TAG_typedef
	.byte	0                               # DW_CHILDREN_no
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	9                               # Abbreviation Code
	.byte	23                              # DW_TAG_union_type
	.byte	1                               # DW_CHILDREN_yes
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	10                              # Abbreviation Code
	.byte	13                              # DW_TAG_member
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	56                              # DW_AT_data_member_location
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	11                              # Abbreviation Code
	.byte	19                              # DW_TAG_structure_type
	.byte	1                               # DW_CHILDREN_yes
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	12                              # Abbreviation Code
	.byte	1                               # DW_TAG_array_type
	.byte	1                               # DW_CHILDREN_yes
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	13                              # Abbreviation Code
	.byte	33                              # DW_TAG_subrange_type
	.byte	0                               # DW_CHILDREN_no
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	55                              # DW_AT_count
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	14                              # Abbreviation Code
	.byte	36                              # DW_TAG_base_type
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	62                              # DW_AT_encoding
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	0                               # EOM(3)
	.section	.debug_info,"",@progbits
.Lcu_begin0:
	.long	.Ldebug_info_end0-.Ldebug_info_start0 # Length of Unit
.Ldebug_info_start0:
	.short	4                               # DWARF version number
	.long	.debug_abbrev                   # Offset Into Abbrev. Section
	.byte	8                               # Address Size (in bytes)
	.byte	1                               # Abbrev [1] 0xb:0x1e1 DW_TAG_compile_unit
	.long	.Linfo_string0                  # DW_AT_producer
	.short	12                              # DW_AT_language
	.long	.Linfo_string1                  # DW_AT_name
	.long	.Lline_table_start0             # DW_AT_stmt_list
	.long	.Linfo_string2                  # DW_AT_comp_dir
	.quad	.Lfunc_begin0                   # DW_AT_low_pc
	.long	.Lfunc_end1-.Lfunc_begin0       # DW_AT_high_pc
	.byte	2                               # Abbrev [2] 0x2a:0x5 DW_TAG_pointer_type
	.long	47                              # DW_AT_type
	.byte	3                               # Abbrev [3] 0x2f:0x7 DW_TAG_base_type
	.long	.Linfo_string3                  # DW_AT_name
	.byte	7                               # DW_AT_encoding
	.byte	4                               # DW_AT_byte_size
	.byte	4                               # Abbrev [4] 0x36:0x1 DW_TAG_pointer_type
	.byte	5                               # Abbrev [5] 0x37:0x52 DW_TAG_subprogram
	.quad	.Lfunc_begin0                   # DW_AT_low_pc
	.long	.Lfunc_end0-.Lfunc_begin0       # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string4                  # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	25                              # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	54                              # DW_AT_type
                                        # DW_AT_external
	.byte	6                               # Abbrev [6] 0x50:0xe DW_TAG_formal_parameter
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	120
	.long	.Linfo_string7                  # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	25                              # DW_AT_decl_line
	.long	54                              # DW_AT_type
	.byte	7                               # Abbrev [7] 0x5e:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	112
	.long	.Linfo_string8                  # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	28                              # DW_AT_decl_line
	.long	227                             # DW_AT_type
	.byte	7                               # Abbrev [7] 0x6c:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	104
	.long	.Linfo_string11                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	29                              # DW_AT_decl_line
	.long	42                              # DW_AT_type
	.byte	7                               # Abbrev [7] 0x7a:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	100
	.long	.Linfo_string12                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	30                              # DW_AT_decl_line
	.long	47                              # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	5                               # Abbrev [5] 0x89:0x53 DW_TAG_subprogram
	.quad	.Lfunc_begin1                   # DW_AT_low_pc
	.long	.Lfunc_end1-.Lfunc_begin1       # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	86
	.long	.Linfo_string5                  # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	53                              # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	220                             # DW_AT_type
                                        # DW_AT_external
	.byte	7                               # Abbrev [7] 0xa2:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	112
	.long	.Linfo_string13                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	55                              # DW_AT_decl_line
	.long	227                             # DW_AT_type
	.byte	7                               # Abbrev [7] 0xb0:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	104
	.long	.Linfo_string14                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	56                              # DW_AT_decl_line
	.long	227                             # DW_AT_type
	.byte	7                               # Abbrev [7] 0xbe:0xe DW_TAG_variable
	.byte	2                               # DW_AT_location
	.byte	145
	.byte	64
	.long	.Linfo_string15                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	57                              # DW_AT_decl_line
	.long	245                             # DW_AT_type
	.byte	7                               # Abbrev [7] 0xcc:0xf DW_TAG_variable
	.byte	3                               # DW_AT_location
	.byte	145
	.ascii	"\274\177"
	.long	.Linfo_string11                 # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	60                              # DW_AT_decl_line
	.long	47                              # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	3                               # Abbrev [3] 0xdc:0x7 DW_TAG_base_type
	.long	.Linfo_string6                  # DW_AT_name
	.byte	5                               # DW_AT_encoding
	.byte	4                               # DW_AT_byte_size
	.byte	8                               # Abbrev [8] 0xe3:0xb DW_TAG_typedef
	.long	238                             # DW_AT_type
	.long	.Linfo_string10                 # DW_AT_name
	.byte	2                               # DW_AT_decl_file
	.byte	27                              # DW_AT_decl_line
	.byte	3                               # Abbrev [3] 0xee:0x7 DW_TAG_base_type
	.long	.Linfo_string9                  # DW_AT_name
	.byte	7                               # DW_AT_encoding
	.byte	8                               # DW_AT_byte_size
	.byte	8                               # Abbrev [8] 0xf5:0xb DW_TAG_typedef
	.long	256                             # DW_AT_type
	.long	.Linfo_string36                 # DW_AT_name
	.byte	2                               # DW_AT_decl_file
	.byte	72                              # DW_AT_decl_line
	.byte	9                               # Abbrev [9] 0x100:0x29 DW_TAG_union_type
	.byte	40                              # DW_AT_byte_size
	.byte	2                               # DW_AT_decl_file
	.byte	67                              # DW_AT_decl_line
	.byte	10                              # Abbrev [10] 0x104:0xc DW_TAG_member
	.long	.Linfo_string16                 # DW_AT_name
	.long	297                             # DW_AT_type
	.byte	2                               # DW_AT_decl_file
	.byte	69                              # DW_AT_decl_line
	.byte	0                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x110:0xc DW_TAG_member
	.long	.Linfo_string31                 # DW_AT_name
	.long	458                             # DW_AT_type
	.byte	2                               # DW_AT_decl_file
	.byte	70                              # DW_AT_decl_line
	.byte	0                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x11c:0xc DW_TAG_member
	.long	.Linfo_string34                 # DW_AT_name
	.long	484                             # DW_AT_type
	.byte	2                               # DW_AT_decl_file
	.byte	71                              # DW_AT_decl_line
	.byte	0                               # DW_AT_data_member_location
	.byte	0                               # End Of Children Mark
	.byte	11                              # Abbrev [11] 0x129:0x69 DW_TAG_structure_type
	.long	.Linfo_string30                 # DW_AT_name
	.byte	40                              # DW_AT_byte_size
	.byte	3                               # DW_AT_decl_file
	.byte	22                              # DW_AT_decl_line
	.byte	10                              # Abbrev [10] 0x131:0xc DW_TAG_member
	.long	.Linfo_string17                 # DW_AT_name
	.long	220                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	24                              # DW_AT_decl_line
	.byte	0                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x13d:0xc DW_TAG_member
	.long	.Linfo_string18                 # DW_AT_name
	.long	47                              # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	25                              # DW_AT_decl_line
	.byte	4                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x149:0xc DW_TAG_member
	.long	.Linfo_string19                 # DW_AT_name
	.long	220                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	26                              # DW_AT_decl_line
	.byte	8                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x155:0xc DW_TAG_member
	.long	.Linfo_string20                 # DW_AT_name
	.long	47                              # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	28                              # DW_AT_decl_line
	.byte	12                              # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x161:0xc DW_TAG_member
	.long	.Linfo_string21                 # DW_AT_name
	.long	220                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	32                              # DW_AT_decl_line
	.byte	16                              # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x16d:0xc DW_TAG_member
	.long	.Linfo_string22                 # DW_AT_name
	.long	402                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	34                              # DW_AT_decl_line
	.byte	20                              # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x179:0xc DW_TAG_member
	.long	.Linfo_string24                 # DW_AT_name
	.long	402                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	35                              # DW_AT_decl_line
	.byte	22                              # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x185:0xc DW_TAG_member
	.long	.Linfo_string25                 # DW_AT_name
	.long	409                             # DW_AT_type
	.byte	3                               # DW_AT_decl_file
	.byte	36                              # DW_AT_decl_line
	.byte	24                              # DW_AT_data_member_location
	.byte	0                               # End Of Children Mark
	.byte	3                               # Abbrev [3] 0x192:0x7 DW_TAG_base_type
	.long	.Linfo_string23                 # DW_AT_name
	.byte	5                               # DW_AT_encoding
	.byte	2                               # DW_AT_byte_size
	.byte	8                               # Abbrev [8] 0x199:0xb DW_TAG_typedef
	.long	420                             # DW_AT_type
	.long	.Linfo_string29                 # DW_AT_name
	.byte	4                               # DW_AT_decl_file
	.byte	55                              # DW_AT_decl_line
	.byte	11                              # Abbrev [11] 0x1a4:0x21 DW_TAG_structure_type
	.long	.Linfo_string28                 # DW_AT_name
	.byte	16                              # DW_AT_byte_size
	.byte	4                               # DW_AT_decl_file
	.byte	51                              # DW_AT_decl_line
	.byte	10                              # Abbrev [10] 0x1ac:0xc DW_TAG_member
	.long	.Linfo_string26                 # DW_AT_name
	.long	453                             # DW_AT_type
	.byte	4                               # DW_AT_decl_file
	.byte	53                              # DW_AT_decl_line
	.byte	0                               # DW_AT_data_member_location
	.byte	10                              # Abbrev [10] 0x1b8:0xc DW_TAG_member
	.long	.Linfo_string27                 # DW_AT_name
	.long	453                             # DW_AT_type
	.byte	4                               # DW_AT_decl_file
	.byte	54                              # DW_AT_decl_line
	.byte	8                               # DW_AT_data_member_location
	.byte	0                               # End Of Children Mark
	.byte	2                               # Abbrev [2] 0x1c5:0x5 DW_TAG_pointer_type
	.long	420                             # DW_AT_type
	.byte	12                              # Abbrev [12] 0x1ca:0xc DW_TAG_array_type
	.long	470                             # DW_AT_type
	.byte	13                              # Abbrev [13] 0x1cf:0x6 DW_TAG_subrange_type
	.long	477                             # DW_AT_type
	.byte	40                              # DW_AT_count
	.byte	0                               # End Of Children Mark
	.byte	3                               # Abbrev [3] 0x1d6:0x7 DW_TAG_base_type
	.long	.Linfo_string32                 # DW_AT_name
	.byte	6                               # DW_AT_encoding
	.byte	1                               # DW_AT_byte_size
	.byte	14                              # Abbrev [14] 0x1dd:0x7 DW_TAG_base_type
	.long	.Linfo_string33                 # DW_AT_name
	.byte	8                               # DW_AT_byte_size
	.byte	7                               # DW_AT_encoding
	.byte	3                               # Abbrev [3] 0x1e4:0x7 DW_TAG_base_type
	.long	.Linfo_string35                 # DW_AT_name
	.byte	5                               # DW_AT_encoding
	.byte	8                               # DW_AT_byte_size
	.byte	0                               # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	"Ubuntu clang version 12.0.1-19ubuntu3" # string offset=0
.Linfo_string1:
	.asciz	"thread.c"                      # string offset=38
.Linfo_string2:
	.asciz	"/home/adjelili/Desktop/M3/Philosophers" # string offset=47
.Linfo_string3:
	.asciz	"unsigned int"                  # string offset=86
.Linfo_string4:
	.asciz	"thread_routine"                # string offset=99
.Linfo_string5:
	.asciz	"main"                          # string offset=114
.Linfo_string6:
	.asciz	"int"                           # string offset=119
.Linfo_string7:
	.asciz	"data"                          # string offset=123
.Linfo_string8:
	.asciz	"tid"                           # string offset=128
.Linfo_string9:
	.asciz	"long unsigned int"             # string offset=132
.Linfo_string10:
	.asciz	"pthread_t"                     # string offset=150
.Linfo_string11:
	.asciz	"count"                         # string offset=160
.Linfo_string12:
	.asciz	"i"                             # string offset=166
.Linfo_string13:
	.asciz	"tid1"                          # string offset=168
.Linfo_string14:
	.asciz	"tid2"                          # string offset=173
.Linfo_string15:
	.asciz	"mutex"                         # string offset=178
.Linfo_string16:
	.asciz	"__data"                        # string offset=184
.Linfo_string17:
	.asciz	"__lock"                        # string offset=191
.Linfo_string18:
	.asciz	"__count"                       # string offset=198
.Linfo_string19:
	.asciz	"__owner"                       # string offset=206
.Linfo_string20:
	.asciz	"__nusers"                      # string offset=214
.Linfo_string21:
	.asciz	"__kind"                        # string offset=223
.Linfo_string22:
	.asciz	"__spins"                       # string offset=230
.Linfo_string23:
	.asciz	"short"                         # string offset=238
.Linfo_string24:
	.asciz	"__elision"                     # string offset=244
.Linfo_string25:
	.asciz	"__list"                        # string offset=254
.Linfo_string26:
	.asciz	"__prev"                        # string offset=261
.Linfo_string27:
	.asciz	"__next"                        # string offset=268
.Linfo_string28:
	.asciz	"__pthread_internal_list"       # string offset=275
.Linfo_string29:
	.asciz	"__pthread_list_t"              # string offset=299
.Linfo_string30:
	.asciz	"__pthread_mutex_s"             # string offset=316
.Linfo_string31:
	.asciz	"__size"                        # string offset=334
.Linfo_string32:
	.asciz	"char"                          # string offset=341
.Linfo_string33:
	.asciz	"__ARRAY_SIZE_TYPE__"           # string offset=346
.Linfo_string34:
	.asciz	"__align"                       # string offset=366
.Linfo_string35:
	.asciz	"long int"                      # string offset=374
.Linfo_string36:
	.asciz	"pthread_mutex_t"               # string offset=383
	.ident	"Ubuntu clang version 12.0.1-19ubuntu3"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym thread_routine
	.addrsig_sym pthread_self
	.addrsig_sym printf
	.addrsig_sym pthread_mutex_init
	.addrsig_sym pthread_create
	.addrsig_sym pthread_join
	.section	.debug_line,"",@progbits
.Lline_table_start0:
