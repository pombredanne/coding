import subprocess
import os
import logging
import json
import string
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)
# js = json.dumps(ssst, sort_keys=True, indent=4, separators=(',', ':'))# format json output


class shell(object):
    def runCmd(self, cmd):
        res = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        sout, serr = res.communicate()
        return res.returncode, sout, serr, res.pid

    def initPin(self, cmd):
        res = subprocess.Popen(cmd, shell=True, stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        self.res = res

    def pinWrite(self, input):
        self.res.stdin.write(input)

    def pinRun(self):
        sout, serr = self.res.communicate()
        return sout, serr


filename = "/home/jeb/Documents/pin-in-CTF/examples/NDH2k13-crackme-500/crackme"
cmd = "/opt/pin-3.7-97619-g0d0c92f4f-gcc-linux/pin -t " + \
    "/opt/pin-3.7-97619-g0d0c92f4f-gcc-linux/source/tools/ManualExamples/obj-intel64/inscount0.so" + " -- " + filename
# print shell.runCmd(cmd)
# for s in string.letters
#     res  = subprocess.Popen(cmd,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
#     res.stdin.write("a"*i+'\n')
#     sout,serr = res.communicate()
#     cout = sout.split("Count ")[1]
#     cout_sub= int(cout) - cout_old
#     cout_old = int(cout)
#     print ("current len ", i,"current count:",cout,"sub_count ",cout_sub)


#### brup args ascii
# dic = string.letters+'_{}'+string.digits
# cur='hxp{'
# shell = shell()
# cout_old=5
# start_time = time.time()
# for i in range(0x27):
#     for s in dic:
#         pwd = cur+s+'?'*(0x29-len(cur))
#         print len(pwd)
#         rcmd = cmd+' '+pwd
#         shell.initPin(rcmd)
#         sout,serr = shell.pinRun()
#         cout = sout.split("Count ")[1]
#         cout_sub= int(cout) - cout_old
#         cout_old = int(cout)
#         if cout_sub == 1 :
#             cur=cur+s
#         print ("current flag ", pwd,"current count:",cout,"sub_count ",cout_sub)
# end_time=time.time()
# times= end_time-start_time
# print "need times :",times,'s'


#### get args len
# shell = shell()
# cout_old=0
# for i in range(1,30):
#     rcmd = cmd+' '+'a'*i
#     shell.initPin(rcmd)
#     sout,serr = shell.pinRun()
#     cout = sout.split("Count ")[1]
#     cout_sub= int(cout) - cout_old
#     cout_old = int(cout)
#     print ("current len ", i,"current count:",cout,"sub_count ",cout_sub)


####get simple_input len
# shell = shell()
# cout_old=0
# for i in range(30):
#     shell.initPin(cmd)
#     shell.pinWrite("a"*i)
#     sout,serr = shell.pinRun()
#     cout = sout.split("Count ")[1]
#     cout_sub= int(cout) - cout_old
#     cout_old = int(cout)
#     print ("current len ", i,"current count:",cout,"sub_count ",cout_sub)



####burp know len ascii
# dic = string.letters+'_+'+string.digits
# cur=''
# for i in range(8):
#     for s in dic:
#         shell.initPin(cmd)
#         pwd = cur+s+'?'*(7-len(cur))
#         print pwd
#         shell.pinWrite(pwd+'\n')
#         sout,serr = shell.pinRun()
#         cout = sout.split("Count ")[1]
#         cout_sub= int(cout) - cout_old
#         cout_old = int(cout)
#         if cout_sub > 2000 and cout_sub < 10000:
#             cur=cur+s
#             break
#         print ("current cur ", cur,"current count:",cout,"sub_count ",cout_sub)
