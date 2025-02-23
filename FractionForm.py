def to_fraction(e):
    """Returns the expression e converted to fraction form."""

    if isinstance(e, tuple):
      op, l, r = e
      ll = to_fraction(l)
      rr = to_fraction(r)
      if isinstance(ll, tuple) or isinstance(rr, tuple):
        if isinstance(ll, tuple):
            if ll[0] != '/':
              tll = ('/', ll, 1)
            else:
              tll = ll
        else:
            tll = ('0', ll, 1)

        if isinstance(rr, tuple):
            if rr[0] != '/':
              trr = ('/', rr, 1)
            else:
              trr = rr
        else:
            trr = ('0', rr, 1)
        if tll[2] == 1 and trr[2] == 1:
          return e
        if '/' == tll[0] or '/' == trr[0]:
          if op == '+' or op == '-':
            return ('/', (op, ('*', tll[1], trr[2]), ("*", trr[1], tll[2])), ('*', tll[2], trr[2]))
          elif op == '*':
            return ('/', ('*', tll[1], trr[1]), ("*", tll[2], trr[2]))
          elif op == '/':
            return ('/', ('*', tll[1], trr[2]), ('*', tll[2], trr[1]))
          else:
            return e
        else:
          return e
      else:
        return e
    else:
      return e
    
def main():
   e = ('+', ('/', 'a', 'b'), ('/', 'c', 2))
   print(to_fraction(e))
   e = ('/', ('/', 'a', ('/', 'b', 'v')), ('*', ('+', 'f', 'g'), 'c'))
   print(to_fraction(e))
   e = ('/', ('/', 'a', 3), ('/', 4, 'c'))
   print(to_fraction(e))
   e = ('*', ('/', 'a', 3), ('/', 4, 'c'))
   print(to_fraction(e))
   e = ('-', ('/', 'a', 3), ('/', 4, 'c'))
   print(to_fraction(e))

main()