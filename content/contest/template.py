'''
 * Author: Oskar Haarklou Veileborg
 * Description: Fast I/O. Improves performance when reading many ($\geq 10^4$) lines.
	Returns an empty string instead of raising EOFError!
'''
import sys
input = lambda: sys.stdin.readline().rstrip('\r\n')
# Many calls to print is also slow, consider:
print('\n'.join(buffered_output))
