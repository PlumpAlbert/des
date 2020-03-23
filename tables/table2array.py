import re
from sys import argv

if len(argv) < 2:
  print("USAGE:")
  print("table2array FILE")
  exit()

f = open(argv[1]).read().replace('\n', '')
matcher = re.compile(r'<td>(?P<data>\d+)</td>')
print(
    'unsigned char[]{',
    ','.join(matcher.findall(f)),
    '}'
)
