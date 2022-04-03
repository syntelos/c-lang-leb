leb vint coding

  An unsigned variable length integer is found in [LEB128].

Implementation

  This package defines a pair of functions to perform LEB
  coding over UINT64.

Discussion

  The variable length integer enables tagged data payload
  coding.

    tagged-data := ( tag vint<m> payload[m] )

  An eight bit band is found in an octet sequence of known
  length.  A typical application is prefixed with an
  associate tag.

References

  [LEB128] https://en.wikipedia.org/wiki/LEB128
  [CPL] https://www.cs.princeton.edu/~bwk/cbook.html
  [CPL] https://www.bell-labs.com/usr/dmr/www/

See also

  https://github.com/syntelos/c-lang-bix
  https://github.com/syntelos/c-endian-bint
  https://github.com/syntelos/lang

Configuration

  Clone with submodule.

    git clone --recurse-submodules <github:syntelos/c-lang-leb>

  Alternatively, run "./sumo.sh init" to initialize submodules.

  Build using "make" (clang SUSv3 POSIX.1-2001).
