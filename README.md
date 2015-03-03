# antivirus-evaluation-framework
## Antivirus Evaluation Framework
This framework is designed to test the abilities of anti virus products. All of the tests are performed using the EICAR string.

The EICAR Standard Anti-Virus Test File or EICAR test file is a computer file that was developed by the European Institute for Computer Antivirus Research (EICAR) and Computer Antivirus Research Organization (CARO), to test the response of computer antivirus (AV) programs. Instead of using real malware, which could do real damage, this test file allows people to test anti-virus software without having to use a real computer virus.

The EICAR string:
```
X5O!P%@AP[4\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*
```

Heuristic scans employ either weight-based systems and/or rule-based systems. A heuristic engine based on a weight-based system, which is a quite old styled approach, rates every functionality that is detected with a certain weight according to the degree of danger it may pose. If the sum of those weights reaches a certain threshold, also an alarm can be triggered. Nearly all nowadays utilized heuristic approaches implement rule-based systems.

What the emulator does is supply our heuristic analyzer with information on programs conduct, allowing the analyzer to discover what in fact programs get up to, with no risk to the security of a protected computer. The emulator doesn’t scan files using the usual antivirus signatures, it actually executes them. It does this in an artificial environment that emulates a real operating system. This environment contains its own virtual memory, hard drive, registry, network, processes, all possible subsystems.

The most widespread trick used is prodding an environment with specific tests to check if it’s real or not. And it is here where the precision of the emulator is shown up, depending on how accurately and comprehensively it replicates the original environment.

The EICAR Standard Anti-Virus Test File or EICAR test file is a computer file that was developed by the European Institute for Computer Antivirus Research (EICAR) and Computer Antivirus Research Organization (CARO), to test the response of computer antivirus (AV) programs. Instead of using real malware, which could do real damage, this test file allows people to test anti-virus software without having to use a real computer virus.

## Compiling
All of these applications are cross compiled using MinGW running in Wine.

**Create the C drive in wine (first time only, you need to use the GUI for this)**
winecfg

**Download MinGW GCC cross compiler into the wine directory**
wget 'http://downloads.sourceforge.net/project/mingw/Installer/mingw-get-setup.exe?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fmingw%2Ffiles%2FInstaller%2Fmingw-get-setup.exe%2Fdownload%3Fuse_mirror%3Dheanet&ts=1424985120&use_mirror=heanet' -O ~/.wine/drive_c/mingw-get-setup.exe

**Launch the MinGW installer (you need to use the GUI for this)**
wine ~/.wine/drive_c/mingw-get-setup.exe
Tick the checkbox beside "mingw32-base".
Press "Installation" => "Update Catalogue".

**Update the wine PATH variable (you need to use the GUI for this)**
wine regedit
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment

**Append the following to the PATH variable:**
;C:\MinGW\bin
