## Antivirus Evaluation Framework
This framework is designed to test the abilities of anti virus products. All of the tests are performed using the EICAR string.

The EICAR Standard Anti-Virus Test File or EICAR test file is a computer file that was developed by the European Institute for Computer Antivirus Research (EICAR) and Computer Antivirus Research Organization (CARO), to test the response of computer antivirus (AV) programs. Instead of using real malware, which could do real damage, this test file allows people to test anti-virus software without having to use a real computer virus.

The EICAR string:
```
X5O!P%@AP[4\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*
```

Heuristic anti virus scans employ either weight-based systems and/or rule-based systems. A heuristic engine based on a weight-based system, which is a quite old styled approach, rates every functionality that is detected with a certain weight according to the degree of danger it may pose. If the sum of those weights reaches a certain threshold, also an alarm can be triggered. 

Anti-virus emulators supply heuristic analyzers with information on programs conduct, with no risk to the security of a protected computer. The emulator doesn’t scan files using the usual antivirus signatures, it actually executes them in an artificial environment that emulates a real operating system. This environment contains its own virtual memory, hard drive, registry, network, processes, all possible subsystems.

Emulators can be evaluated by prodding its virtual environment with specific tests to check if it’s real or not. This is where the precision of the emulator is shown up, depending on how accurately and comprehensively it replicates the original environment. This is the goal of this project, the evaluate the capabilities of these virtual environments.
