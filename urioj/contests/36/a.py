



a = 1
b = 1

cnt = 0

out = "{\n"

while cnt<60:
  a, b = b, a+b
  if b%3==0 or '3' in str(b):
    cnt += 1
    out += '    "%d",\n'  % b

out += "}"

print out
