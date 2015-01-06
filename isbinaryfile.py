
textchars = bytearray([7,8,9,10,12,13,27]) + bytearray(range(0x20, 0x100))
is_binary_string = lambda bytes: bool(bytes.translate(None, textchars))
is_binary_file = lambda file_name: is_binary_string(open(file_name, 'rb').read(1024))


def test():
  print(is_binary_string('rmbinaryfile.sh'))

if __name__ == '__main__':
  test()
