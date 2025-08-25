; ===============================
; Ascii & Syscall mapings
; ===============================

%ifndef MAP_INC
%define MAP_INC
; Ensure this file is only included once

; ASCII mappings


%idefine newline 0x0A         ; (\n) 

%idefine tab 0x09             ; (\t) 

%idefine bell 0x07            ; (\a)

%idefine backspace 0x08       ; (\b)

%idefine vertical_tab 0x0B    ; (\v)

%idefine escape 0x1B          ; (\e)

%idefine form_feed 0x0C       ; (\f)

%idefine carrige_return 0x0D  ; (\r)

%idefine delete 0x7F          ; (DEL)



; Digits

%idefine zero 0x30            ; '0'

%idefine one 0x31             ; '1'

%idefine two 0x32             ; '2'

%idefine three 0x33           ; '3'

%idefine four 0x34            ; '4'

%idefine five 0x35            ; '5'

%idefine six 0x36             ; '6'

%idefine seven 0x37           ; '7'

%idefine eight 0x38           ; '8'

%idefine nine 0x39            ; '9'



; Punctuation

%idefine exclamation 0x21     ; '!'

%idefine quote 0x22           ; '"'

%idefine hash 0x23            ; '#'

%idefine dollar 0x24          ; '$'

%idefine percent 0x25         ; '%'

%idefine ampersand 0x26       ; '&'

%idefine space 0x20           ; ' ' 

%idefine backslash 0x5C       ; \

%idefine doublequote 0x22     ; "

%idefine singlequote 0x27     ; '

%idefine apostrophe 0x27      ; '''

%idefine left_paren 0x28      ; '('

%idefine right_paren 0x29     ; ')'

%idefine asterisk 0x2A        ; '*'

%idefine plus 0x2B            ; '+'

%idefine comma 0x2C           ; ','

%idefine minus 0x2D           ; '-'

%idefine period 0x2E          ; '.'

%idefine slash 0x2F           ; '/'

%idefine colon 0x3A           ; ':'

%idefine semicolon 0x3B       ; ';'

%idefine less_than 0x3C       ; '<'

%idefine equal 0x3D           ; '='

%idefine greater_than 0x3E    ; '>'

%idefine question 0x3F        ; '?'

%idefine at 0x40              ; '@'

%idefine left_bracket 0x5B    ; '['

%idefine right_bracket 0x5D   ; ']'

%idefine caret 0x5E           ; '^'

%idefine underscore 0x5F      ; '_'

%idefine grave 0x60           ; '`'

%idefine left_brace 0x7B      ; '{'

%idefine pipe 0x7C            ; '|'

%idefine right_brace 0x7D     ; '}'

%idefine tilde 0x7E           ; '~'

%idefine start_quote 0xE2, 0x80, 0x9C ; “

%idefine end_quote 0xE2, 0x80, 0x9D   ; ”





; Syscall mappings

%idefine sys_restart                        0

%idefine sys_exit                           1

%idefine sys_fork                           2

%idefine sys_read                           3

%idefine sys_write                          4

%idefine sys_open                           5

%idefine sys_close                          6

%idefine sys_waitpid                        7

%idefine sys_creat                          8

%idefine sys_link                           9

%idefine sys_unlink                         10

%idefine sys_execve                         11

%idefine sys_chdir                          12

%idefine sys_time                           13

%idefine sys_mknod                          14

%idefine sys_chmod                          15

%idefine sys_lchown                         16

%idefine sys_break                          17

%idefine sys_oldstat                        18

%idefine sys_lseek                          19

%idefine sys_getpid                         20

%idefine sys_mount                          21

%idefine sys_umount                         22

%idefine sys_setuid                         23

%idefine sys_getuid                         24

%idefine sys_stime                          25

%idefine sys_ptrace                         26

%idefine sys_alarm                          27

%idefine sys_oldfstat                       28

%idefine sys_pause                          29

%idefine sys_utime                          30

%idefine sys_stty                           31

%idefine sys_gtty                           32

%idefine sys_access                         33

%idefine sys_nice                           34

%idefine sys_ftime                          35

%idefine sys_sync                           36

%idefine sys_kill                           37

%idefine sys_rename                         38

%idefine sys_mkdir                          39

%idefine sys_rmdir                          40

%idefine sys_dup                            41

%idefine sys_pipe                           42

%idefine sys_times                          43

%idefine sys_prof                           44

%idefine sys_brk                            45

%idefine sys_setgid                         46

%idefine sys_getgid                         47

%idefine sys_signal                         48

%idefine sys_geteuid                        49

%idefine sys_getegid                        50

%idefine sys_acct                           51

%idefine sys_umount2                        52

%idefine sys_lock                           53

%idefine sys_ioctl                          54

%idefine sys_fcntl                          55

%idefine sys_mpx                            56

%idefine sys_setpgid                        57

%idefine sys_ulimit                         58

%idefine sys_oldolduname                    59

%idefine sys_umask                          60

%idefine sys_chroot                         61

%idefine sys_ustat                          62

%idefine sys_dup2                           63

%idefine sys_getppid                        64

%idefine sys_getpgrp                        65

%idefine sys_setsid                         66

%idefine sys_sigaction                      67

%idefine sys_sgetmask                       68

%idefine sys_ssetmask                       69

%idefine sys_setreuid                       70

%idefine sys_setregid                       71

%idefine sys_sigsuspend                     72

%idefine sys_sigpending                     73

%idefine sys_sethostname                    74

%idefine sys_setrlimit                      75

%idefine sys_getrlimit                      76

%idefine sys_getrusage                      77

%idefine sys_gettimeofday                   78

%idefine sys_settimeofday                   79

%idefine sys_getgroups                      80

%idefine sys_setgroups                      81

%idefine sys_select                         82

%idefine sys_symlink                        83

%idefine sys_oldlstat                       84

%idefine sys_readlink                       85

%idefine sys_uselib                         86

%idefine sys_swapon                         87

%idefine sys_reboot                         88

%idefine sys_readdir                        89

%idefine sys_mmap                           90

%idefine sys_munmap                         91

%idefine sys_truncate                       92

%idefine sys_ftruncate                      93

%idefine sys_fchmod                         94

%idefine sys_fchown                         95

%idefine sys_getpriority                    96

%idefine sys_setpriority                    97

%idefine sys_profil                         98

%idefine sys_statfs                         99

%idefine sys_fstatfs                        100

%idefine sys_ioperm                         101

%idefine sys_socketcall                     102

%idefine sys_syslog                         103

%idefine sys_setitimer                      104

%idefine sys_getitimer                      105

%idefine sys_stat                           106

%idefine sys_lstat                          107

%idefine sys_fstat                          108

%idefine sys_olduname                       109

%idefine sys_iopl                           110

%idefine sys_vhangup                        111

%idefine sys_idle                           112

%idefine sys_vm86old                        113

%idefine sys_wait4                          114

%idefine sys_swapoff                        115

%idefine sys_sysinfo                        116

%idefine sys_ipc                            117

%idefine sys_fsync                          118

%idefine sys_sigreturn                      119

%idefine sys_clone                          120

%idefine sys_setdomainname                  121

%idefine sys_uname                          122

%idefine sys_modify_ldt                     123

%idefine sys_adjtimex                       124

%idefine sys_mprotect                       125

%idefine sys_sigprocmask                    126

%idefine sys_create_module                  127

%idefine sys_init_module                    128

%idefine sys_delete_module                  129

%idefine sys_get_kernel_syms                130

%idefine sys_quotactl                       131

%idefine sys_getpgid                        132

%idefine sys_fchdir                         133

%idefine sys_bdflush                        134

%idefine sys_sysfs                          135

%idefine sys_personality                    136

%idefine sys_afs_syscall                    137

%idefine sys_setfsuid                       138

%idefine sys_setfsgid                       139

%idefine sys__llseek                        140

%idefine sys_getdents                       141

%idefine sys__newselect                     142

%idefine sys_flock                          143

%idefine sys_msync                          144

%idefine sys_readv                          145

%idefine sys_writev                         146

%idefine sys_getsid                         147

%idefine sys_fdatasync                      148

%idefine sys__sysctl                        149

%idefine sys_mlock                          150

%idefine sys_munlock                        151

%idefine sys_mlockall                       152

%idefine sys_munlockall                     153

%idefine sys_sched_setparam                 154

%idefine sys_sched_getparam                 155

%idefine sys_sched_setscheduler             156

%idefine sys_sched_getscheduler             157

%idefine sys_sched_yield                    158

%idefine sys_sched_get_priority_max         159

%idefine sys_sched_get_priority_min         160

%idefine sys_sched_rr_get_interval          161

%idefine sys_nanosleep                      162

%idefine sys_mremap                         163

%idefine sys_setresuid                      164

%idefine sys_getresuid                      165

%idefine sys_vm86                           166

%idefine sys_query_module                   167

%idefine sys_poll                           168

%idefine sys_nfsservctl                     169

%idefine sys_setresgid                      170

%idefine sys_getresgid                      171

%idefine sys_prctl                          172

%idefine sys_rt_sigreturn                   173

%idefine sys_rt_sigaction                   174

%idefine sys_rt_sigprocmask                 175

%idefine sys_rt_sigpending                  176

%idefine sys_rt_sigtimedwait                177

%idefine sys_rt_sigqueueinfo                178

%idefine sys_rt_sigsuspend                  179

%idefine sys_pread64                        180

%idefine sys_pwrite64                       181

%idefine sys_chown                          182

%idefine sys_getcwd                         183

%idefine sys_capget                         184

%idefine sys_capset                         185

%idefine sys_sigaltstack                    186

%idefine sys_sendfile                       187

%idefine sys_getpmsg                        188

%idefine sys_putpmsg                        189

%idefine sys_vfork                          190

%idefine sys_ugetrlimit                     191

%idefine sys_mmap2                          192

%idefine sys_truncate64                     193

%idefine sys_ftruncate64                    194

%idefine sys_stat64                         195

%idefine sys_lstat64                        196

%idefine sys_fstat64                        197

%idefine sys_lchown32                       198

%idefine sys_getuid32                       199

%idefine sys_getgid32                       200

%idefine sys_geteuid32                      201

%idefine sys_getegid32                      202

%idefine sys_setreuid32                     203

%idefine sys_setregid32                     204

%idefine sys_getgroups32                    205

%idefine sys_setgroups32                    206

%idefine sys_fchown32                       207

%idefine sys_setresuid32                    208

%idefine sys_getresuid32                    209

%idefine sys_setresgid32                    210

%idefine sys_getresgid32                    211

%idefine sys_chown32                        212

%idefine sys_setuid32                       213

%idefine sys_setgid32                       214

%idefine sys_setfsuid32                     215

%idefine sys_setfsgid32                     216

%idefine sys_pivot_root                     217

%idefine sys_mincore                        218

%idefine sys_madvise                        219

%idefine sys_getdents64                     220

%idefine sys_fcntl64                        221

%idefine sys_gettid                         224

%idefine sys_readahead                      225

%idefine sys_setxattr                       226

%idefine sys_lsetxattr                      227

%idefine sys_fsetxattr                      228

%idefine sys_getxattr                       229

%idefine sys_lgetxattr                      230

%idefine sys_fgetxattr                      231

%idefine sys_listxattr                      232

%idefine sys_llistxattr                     233

%idefine sys_flistxattr                     234

%idefine sys_removexattr                    235

%idefine sys_lremovexattr                   236

%idefine sys_fremovexattr                   237

%idefine sys_tkill                          238

%idefine sys_sendfile64                     239

%idefine sys_futex                          240

%idefine sys_sched_setaffinity              241

%idefine sys_sched_getaffinity              242

%idefine sys_set_thread_area                243

%idefine sys_get_thread_area                244

%idefine sys_io_setup                       245

%idefine sys_io_destroy                     246

%idefine sys_io_getevents                   247

%idefine sys_io_submit                      248

%idefine sys_io_cancel                      249

%idefine sys_fadvise64                      250

%idefine sys_exit_group                     252

%idefine sys_lookup_dcookie                 253

%idefine sys_epoll_create                   254

%idefine sys_epoll_ctl                      255

%idefine sys_epoll_wait                     256

%idefine sys_remap_file_pages               257

%idefine sys_set_tid_address                258

%idefine sys_timer_create                   259

%idefine sys_timer_settime                  260

%idefine sys_timer_gettime                  261

%idefine sys_timer_getoverrun               262

%idefine sys_timer_delete                   263

%idefine sys_clock_settime                  264

%idefine sys_clock_gettime                  265

%idefine sys_clock_getres                   266

%idefine sys_clock_nanosleep                267

%idefine sys_statfs64                       268

%idefine sys_fstatfs64                      269

%idefine sys_tgkill                         270

%idefine sys_utimes                         271

%idefine sys_fadvise64_64                   272

%idefine sys_vserver                        273

%idefine sys_mbind                          274

%idefine sys_get_mempolicy                  275

%idefine sys_set_mempolicy                  276

%idefine sys_mq_open                        277

%idefine sys_mq_unlink                      278

%idefine sys_mq_timedsend                   279

%idefine sys_mq_timedreceive                280

%idefine sys_mq_notify                      281

%idefine sys_mq_getsetattr                  282

%idefine sys_kexec_load                     283

%idefine sys_waitid                         284

%idefine sys_add_key                        286

%idefine sys_request_key                    287

%idefine sys_keyctl                         288

%idefine sys_ioprio_set                     289

%idefine sys_ioprio_get                     290

%idefine sys_inotify_init                   291

%idefine sys_inotify_add_watch              292

%idefine sys_inotify_rm_watch               293

%idefine sys_migrate_pages                  294

%idefine sys_openat                         295

%idefine sys_mkdirat                        296

%idefine sys_mknodat                        297

%idefine sys_fchownat                       298

%idefine sys_futimesat                      299

%idefine sys_fstatat64                      300

%idefine sys_unlinkat                       301

%idefine sys_renameat                       302

%idefine sys_linkat                         303

%idefine sys_symlinkat                      304

%idefine sys_readlinkat                     305

%idefine sys_fchmodat                       306

%idefine sys_faccessat                      307

%idefine sys_pselect6                       308

%idefine sys_ppoll                          309

%idefine sys_unshare                        310

%idefine sys_set_robust_list                311

%idefine sys_get_robust_list                312

%idefine sys_splice                         313

%idefine sys_sync_file_range                314

%idefine sys_tee                            315

%idefine sys_vmsplice                       316

%idefine sys_move_pages                     317

%idefine sys_getcpu                         318

%idefine sys_epoll_pwait                    319

%idefine sys_utimensat                      320

%idefine sys_signalfd                       321

%idefine sys_timerfd_create                 322

%idefine sys_eventfd                        323

%idefine sys_fallocate                      324

%idefine sys_timerfd_settime                325

%idefine sys_timerfd_gettime                326

%idefine sys_signalfd4                      327

%idefine sys_eventfd2                       328

%idefine sys_epoll_create1                  329

%idefine sys_dup3                           330

%idefine sys_pipe2                          331

%idefine sys_inotify_init1                  332

%idefine sys_preadv                         333

%idefine sys_pwritev                        334

%idefine sys_rt_tgsigqueueinfo              335

%idefine sys_perf_event_open                336

%idefine sys_recvmmsg                       337

%idefine sys_fanotify_init                  338

%idefine sys_fanotify_mark                  339

%idefine sys_prlimit64                      340

%idefine sys_name_to_handle_at              341

%idefine sys_open_by_handle_at              342

%idefine sys_clock_adjtime                  343

%idefine sys_syncfs                         344

%idefine sys_sendmmsg                       345

%idefine sys_setns                          346

%idefine sys_process_vm_readv               347

%idefine sys_process_vm_writev              348

%idefine sys_kcmp                           349

%idefine sys_finit_module                   350

%idefine sys_sched_setattr                  351

%idefine sys_sched_getattr                  352

%idefine sys_renameat2                      353

%idefine sys_seccomp                        354

%idefine sys_getrandom                      355

%idefine sys_memfd_create                   356

%idefine sys_bpf                            357

%idefine sys_execveat                       358

%idefine sys_socket                         359

%idefine sys_socketpair                     360

%idefine sys_bind                           361

%idefine sys_connect                        362

%idefine sys_listen                         363

%idefine sys_accept4                        364

%idefine sys_getsockopt                     365

%idefine sys_setsockopt                     366

%idefine sys_getsockname                    367

%idefine sys_getpeername                    368

%idefine sys_sendto                         369

%idefine sys_sendmsg                        370

%idefine sys_recvfrom                       371

%idefine sys_recvmsg                        372

%idefine sys_shutdown                       373

%idefine sys_userfaultfd                    374

%idefine sys_membarrier                     375

%idefine sys_mlock2                         376

%idefine sys_copy_file_range                377

%idefine sys_preadv2                        378

%idefine sys_pwritev2                       379

%idefine sys_pkey_mprotect                  380

%idefine sys_pkey_alloc                     381

%idefine sys_pkey_free                      382

%idefine sys_statx                          383

%idefine sys_arch_prctl                     384

%idefine sys_io_pgetevents                  385

%idefine sys_rseq                           386

%idefine sys_semget                         393

%idefine sys_semctl                         394

%idefine sys_shmget                         395

%idefine sys_shmctl                         396

%idefine sys_shmat                          397

%idefine sys_shmdt                          398

%idefine sys_msgget                         399

%idefine sys_msgsnd                         400

%idefine sys_msgrcv                         401

%idefine sys_msgctl                         402

%idefine sys_clock_gettime64                403

%idefine sys_clock_settime64                404

%idefine sys_clock_adjtime64                405

%idefine sys_clock_getres_time64            406

%idefine sys_clock_nanosleep_time64         407

%idefine sys_timer_gettime64                408

%idefine sys_timer_settime64                409

%idefine sys_timerfd_gettime64              410

%idefine sys_timerfd_settime64              411

%idefine sys_utimensat_time64               412

%idefine sys_pselect6_time64                413

%idefine sys_ppoll_time64                   414

%idefine sys_io_pgetevents_time64           416

%idefine sys_recvmmsg_time64                417

%idefine sys_mq_timedsend_time64            418

%idefine sys_mq_timedreceive_time64         419

%idefine sys_semtimedop_time64              420

%idefine sys_rt_sigtimedwait_time64         421

%idefine sys_futex_time64                   422

%idefine sys_sched_rr_get_interval_time64   423

%idefine sys_pidfd_send_signal              424

%idefine sys_io_uring_setup                 425

%idefine sys_io_uring_enter                 426

%idefine sys_io_uring_register              427

%idefine sys_open_tree                      428

%idefine sys_move_mount                     429

%idefine sys_fsopen                         430

%idefine sys_fsconfig                       431

%idefine sys_fsmount                        432

%idefine sys_fspick                         433

%idefine sys_pidfd_open                     434

%idefine sys_clone3                         435

%idefine sys_close_range                    436

%idefine sys_openat2                        437

%idefine sys_pidfd_getfd                    438

%idefine sys_faccessat2                     439

%idefine sys_process_madvise                440

%idefine sys_epoll_pwait2                   441

%idefine sys_mount_setattr                  442

%idefine sys_quotactl_fd                    443

%idefine sys_landlock_create_ruleset        444

%idefine sys_landlock_add_rule              445

%idefine sys_landlock_restrict_self         446

%idefine sys_memfd_secret                   447

%idefine sys_process_mrelease               448

%idefine sys_futex_waitv                    449

%idefine sys_set_mempolicy_home_node        450

%idefine sys_cachestat                      451

%idefine sys_fchmodat2                      452

%idefine sys_map_shadow_stack               453

%idefine sys_futex_wake                     454

%idefine sys_futex_wait                     455

%idefine sys_futex_requeue                  456

%idefine sys_statmount                      457

%idefine sys_listmount                      458

%idefine sys_lsm_get_self_attr              459

%idefine sys_lsm_set_self_attr              460

%idefine sys_lsm_list_modules               461

%idefine sys_mseal                          462

%idefine sys_setxattrat                     463

%idefine sys_getxattrat                     464

%idefine sys_listxattrat                    465

%idefine sys_removexattrat                  466

%idefine sys_open_tree_attr                 467


%endif ; MAP_INC