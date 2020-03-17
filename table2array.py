import re

f = open('../ip').read().replace('\n', '')

matcher = re.compile(r'<td>(?P<data>\d+)</td>')
print(
    'unsigned char[]{',
    ','.join(matcher.findall(f)),
    '}'
)
