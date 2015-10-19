#  Apache 2.0 License
#  copyright 2015 Speedovation, Yash Pal, yash@speedovation.com

INCLUDEPATH += $$PWD $$PWD/breakpad $$PWD/breakpad/src

# Windows
win32{
   HEADERS +=    $$PWD/breakpad/src/common/windows/string_utils-inl.h \
                 $$PWD/breakpad/src/common/windows/guid_string.h \
                 $$PWD/breakpad/src/client/windows/handler/exception_handler.h \
                 $$PWD/breakpad/src/client/windows/common/ipc_protocol.h \
                 $$PWD/breakpad/src/google_breakpad/common/minidump_format.h \
                 $$PWD/breakpad/src/google_breakpad/common/breakpad_types.h \
                 $$PWD/breakpad/src/client/windows/crash_generation/crash_generation_client.h \
                 $$PWD/breakpad/src/common/scoped_ptr.h


    SOURCES +=  $$PWD/breakpad/src/client/windows/handler/exception_handler.cc \
                $$PWD/breakpad/src/common/windows/string_utils.cc \
                $$PWD/breakpad/src/common/windows/guid_string.cc \
                $$PWD/breakpad/src/client/windows/crash_generation/crash_generation_client.cc

}
# Unix
unix{
     HEADERS += \
            $$PWD/breakpad/src/client/minidump_file_writer-inl.h \
            $$PWD/breakpad/src/client/minidump_file_writer.h \
            $$PWD/breakpad/src/common/using_std_string.h \
            $$PWD/breakpad/src/common/memory.h \
            $$PWD/breakpad/src/common/basictypes.h \
            $$PWD/breakpad/src/common/memory_range.h \
            $$PWD/breakpad/src/common/string_conversion.h \
            $$PWD/breakpad/src/common/convert_UTF.h \
            $$PWD/breakpad/src/google_breakpad/common/minidump_format.h \
            $$PWD/breakpad/src/google_breakpad/common/minidump_size.h \
            $$PWD/breakpad/src/google_breakpad/common/breakpad_types.h \
            $$PWD/breakpad/src/common/scoped_ptr.h \
            $$PWD/breakpad/src/common/md5.h

    SOURCES += \
            $$PWD/breakpad/src/client/minidump_file_writer.cc \
            $$PWD/breakpad/src/common/string_conversion.cc \
            $$PWD/breakpad/src/common/convert_UTF.c \
            $$PWD/breakpad/src/common/md5.cc

    QMAKE_CXXFLAGS+=-g
}
#linux
linux{

 HEADERS += \
        $$PWD/breakpad/src/client/linux/handler/exception_handler.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/cpu_set.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/proc_cpuinfo_reader.h \
        $$PWD/breakpad/src/client/linux/crash_generation/crash_generation_client.h \
        $$PWD/breakpad/src/client/linux/handler/minidump_descriptor.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/minidump_writer.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/line_reader.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/linux_dumper.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/directory_reader.h \
        $$PWD/breakpad/src/client/linux/log/log.h \
        $$PWD/breakpad/src/common/linux/linux_libc_support.h \
        $$PWD/breakpad/src/common/linux/eintr_wrapper.h \
        $$PWD/breakpad/src/common/linux/ignore_ret.h \
        $$PWD/breakpad/src/common/linux/file_id.h \
        $$PWD/breakpad/src/common/linux/memory_mapped_file.h \
        $$PWD/breakpad/src/common/linux/safe_readlink.h \
        $$PWD/breakpad/src/common/linux/guid_creator.h \
        $$PWD/breakpad/src/common/linux/elfutils.h \
        $$PWD/breakpad/src/common/linux/elfutils-inl.h \
        $$PWD/breakpad/src/common/linux/elf_gnu_compat.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/thread_info.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/mapping_info.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/raw_context_cpu.h \
        $$PWD/breakpad/src/client/linux/microdump_writer/microdump_writer.h \
        $$PWD/breakpad/src/client/linux/minidump_writer/minidump_writer.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/ucontext_reader.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/seccomp_unwinder.h \
        $$PWD/breakpad/src/client/linux/dump_writer_common/thread_info.h \
        $$PWD/breakpad/src/third_party/lss/linux_syscall_support.h




SOURCES +=  \
            $$PWD/breakpad/src/client/linux/crash_generation/crash_generation_client.cc \
            $$PWD/breakpad/src/client/linux/handler/exception_handler.cc \
            $$PWD/breakpad/src/client/linux/handler/minidump_descriptor.cc \
            $$PWD/breakpad/src/client/linux/minidump_writer/minidump_writer.cc \
            $$PWD/breakpad/src/client/linux/minidump_writer/linux_dumper.cc \
            $$PWD/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc \
            $$PWD/breakpad/src/client/linux/microdump_writer/microdump_writer.cc \
            $$PWD/breakpad/src/client/linux/dump_writer_common/ucontext_reader.cc \
            $$PWD/breakpad/src/client/linux/dump_writer_common/seccomp_unwinder.cc \
            $$PWD/breakpad/src/client/linux/dump_writer_common/thread_info.cc \
            $$PWD/breakpad/src/client/linux/handler/exception_handler.h \
            $$PWD/breakpad/src/client/linux/log/log.cc \
            $$PWD/breakpad/src/common/linux/linux_libc_support.cc \
            $$PWD/breakpad/src/common/linux/file_id.cc \
            $$PWD/breakpad/src/common/linux/memory_mapped_file.cc \
            $$PWD/breakpad/src/common/linux/safe_readlink.cc \
            $$PWD/breakpad/src/common/linux/guid_creator.cc \
            $$PWD/breakpad/src/common/linux/elfutils.cc \

#breakpad app need debug info inside binaries


}

mac{

HEADERS += \
        $$PWD/breakpad/src/client/mac/handler/exception_handler.h \
        $$PWD/breakpad/src/client/mac/handler/minidump_generator.h \
        $$PWD/breakpad/src/client/mac/handler/dynamic_images.h \
        $$PWD/breakpad/src/client/mac/handler/breakpad_nlist_64.h \
        $$PWD/breakpad/src/client/mac/crash_generation/crash_generation_client.h \
        $$PWD/breakpad/src/common/mac/bootstrap_compat.h \
        $$PWD/breakpad/src/common/mac/macho_utilities.h \
        $$PWD/breakpad/src/common/mac/scoped_task_suspend-inl.h \
        $$PWD/breakpad/src/common/mac/file_id.h \
        $$PWD/breakpad/src/common/mac/macho_id.h \
        $$PWD/breakpad/src/common/mac/macho_id.h \
        $$PWD/breakpad/src/common/mac/macho_walker.h \
        $$PWD/breakpad/src/common/mac/string_utilities.h \
        $$PWD/breakpad/src/google_breakpad/common/minidump_exception_mac.h \

SOURCES += \
        $$PWD/breakpad/src/client/mac/handler/exception_handler.cc \
        $$PWD/breakpad/src/client/mac/handler/minidump_generator.cc \
        $$PWD/breakpad/src/client/mac/handler/dynamic_images.cc \
        $$PWD/breakpad/src/client/mac/crash_generation/crash_generation_client.cc \
        $$PWD/breakpad/src/client/mac/handler/breakpad_nlist_64.cc \
        $$PWD/breakpad/src/common/mac/file_id.cc \
        $$PWD/breakpad/src/common/mac/macho_utilities.cc \
        $$PWD/breakpad/src/common/mac/macho_id.cc \
        $$PWD/breakpad/src/common/mac/macho_reader.cc \
        $$PWD/breakpad/src/common/mac/string_utilities.cc \
        $$PWD/breakpad/src/common/mac/bootstrap_compat.cc \
        $$PWD/breakpad/src/common/mac/macho_walker.cc \


OBJECTIVE_HEADERS += \
        $$PWD/breakpad/src/common/mac/MachIPC.h \

OBJECTIVE_SOURCES += \
        $$PWD/breakpad/src/common/mac/MachIPC.mm \

}
