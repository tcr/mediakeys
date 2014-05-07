from subprocess import Popen, PIPE

p = Popen("Default\\keylistener.exe", stdout=PIPE, bufsize=1)
for line in iter(p.stdout.readline, ''):
    print line,
p.stdout.close()
if p.wait() != 0:
   raise RuntimeError("%r failed, exit status: %d" % (cmd, p.returncode))