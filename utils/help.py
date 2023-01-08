help_clean_message: str =  "\nmake clean               Remove all the build files."
help_debian_install: str = "make install-debian      Install all the dependencies on debian-based platforms."
help_arch_install: str =   "make install-arch        Install all the dependencies on arch-based platforms."
help_run_message: str =    "make run                 Launch Qemu with the compiled kernel."

print(help_clean_message)
print(help_debian_install)
print(help_arch_install)
print(help_run_message)
